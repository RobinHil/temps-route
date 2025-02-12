
#include<QFile>
#include<QErrorMessage>

#include "mainwindow.h"
#include "ui_mainwindow.h"

#define min(a,b) (a<=b?a:b)

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Calcul de temps de route");

    chargerVilles();
    chargerTemps();

    FWarshall();

    tableauDefaut();
    diametre();
    ui->label_temps_res->setText("non défini.");

    connect(ui->actionA_propos, SIGNAL(triggered()), this, SLOT(aPropos()));
    connect(ui->actionReinitialiser, SIGNAL(triggered()), this, SLOT(reinitialiser()));
    connect(ui->actionQuitter, SIGNAL(triggered()), qApp, SLOT(quit()));
    connect(ui->buttonTemps, SIGNAL(clicked()), this, SLOT(tempsRoute()));
    connect(ui->buttonTab, SIGNAL(clicked()), this, SLOT(tableau()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::aPropos()
{
    QMessageBox a_propos(this);
    a_propos.setWindowTitle("A propos");
    a_propos.setText("Calcul de temps de route.\n\nCe programme permet le calcul du temps de route entre plusieurs villes.\n\npar HILAIRE Robin (c) 2023");
    a_propos.exec();
}

void MainWindow::reinitialiser()
{
    tableauDefaut();
    ui->label_temps_res->setText("non défini.");
    ui->depart->clearSelection();
    ui->arrivee->clearSelection();
}

void MainWindow::chargerTemps()
{
    temps = QVector<QVector<int>>(villes.size(), QVector<int>(villes.size(),std::numeric_limits<int>::max()/2));
    for (int i = 0; i<temps.size(); ++i)
        temps[i][i] = 0;

    QFile fichier("../data/temps.csv");
    QString ligne;
    QVector<QString> liste;

    if (fichier.open(QIODevice::ReadOnly))
        while (!fichier.atEnd()){
            ligne = fichier.readLine();
            liste = ligne.split(",");
            temps[villes.indexOf(liste[0])][villes.indexOf(liste[1])] = liste[2].toInt();
            temps[villes.indexOf(liste[1])][villes.indexOf(liste[0])] = liste[2].toInt();
        }
}

void MainWindow::chargerVilles()
{
    QFile fichier("../data/villes.csv");
    QString ligne;
    QVector<QString> liste;

    if (fichier.open(QIODevice::ReadOnly)){
        fichier.readLine();
        while (!fichier.atEnd()){
            ligne = fichier.readLine();
            liste = ligne.split(",");
            villes.push_back(liste[1]);
        }
    }

    villes.sort();
    foreach (const QString& ville , villes){
        ui->depart->addItem(ville);
        ui->arrivee->addItem(ville);
    }
}

void MainWindow::FWarshall()
{
    for (int k=0; k<temps.size(); ++k)
        for (int u=0; u<temps.size(); ++u)
            for (int v=0; v<temps.size(); ++v)
                temps[u][v] = min(temps[u][v], (temps[u][k]+temps[k][v]));
}

void MainWindow::diametre()
{
    int valeurDiametre=0;
    int indiceVille1=0;
    int indiceVille2=0;
    for (int i=0; i<temps.size(); ++i)
        for (int j=0; j<temps.size(); ++j)
            if (valeurDiametre<temps[i][j]){
                valeurDiametre = temps[i][j];
                indiceVille1 = i;
                indiceVille2 = j;
            }
    ui->label_diametre_result->setText(QString::number(valeurDiametre)+" minutes, entre "+villes[indiceVille1]+" et "+villes[indiceVille2]+".");
}

QVector<QString> MainWindow::villesSelectionnees()
{
    QVector<QString> selection;

    QList<QListWidgetItem*> items(ui->depart->selectedItems());
    foreach (const QListWidgetItem* i , items)
        selection.push_back(i->text());

    items = ui->arrivee->selectedItems();
    foreach (const QListWidgetItem* i , items)
        if (selection.indexOf(i->text())==-1)
            selection.push_back(i->text());

    return selection;
}

bool MainWindow::isSelectionDepartArrivee()
{
    if (ui->depart->selectedItems().size()==0 || ui->arrivee->selectedItems().size()==0)
        return false;
    return true;
}

void MainWindow::tempsRoute()
{
    QVector<QString> selection = villesSelectionnees();
    if (selection.size()==0)
        ui->label_temps_res->setText("non défini.");
    else if (!isSelectionDepartArrivee() || selection.size()<2){
        ui->label_temps_res->setText("erreur de sélection.");
        QMessageBox a_propos(this);
        a_propos.setWindowTitle("Erreur");
        a_propos.setText("Erreur de sélection !\n\nVeuillez sélectionner une ville dans la liste \"Départ\" et une autre dans la liste \"Arrivée\".\n\nIl est également possible de sélectionner plus de deux villes. Dans ce cas utilisez le tableau de temps.");
        a_propos.exec();
    }
    else if (selection.size()==2)
        ui->label_temps_res->setText(QString::number(temps[villes.indexOf(selection[0])][villes.indexOf(selection[1])])+" minutes.");
}

void MainWindow::tableauDefaut()
{
    ui->tableau->clear();
    ui->tableau->setRowCount(villes.size());
    ui->tableau->setColumnCount(villes.size());
    ui->tableau->setHorizontalHeaderLabels(villes);
    ui->tableau->setVerticalHeaderLabels(villes);
    for (int i=0; i<temps.size(); ++i)
        for (int j=0; j<temps.size(); ++j)
            ui->tableau->setItem(i, j, new QTableWidgetItem(QString::number(temps[i][j])));
}

void MainWindow::tableauModif(const QVector<QString>& selection)
{
    QVector<int> index;
    foreach (const QString& s , selection)
        index.push_back(villes.indexOf(s));

    ui->tableau->clear();
    ui->tableau->setRowCount(selection.size());
    ui->tableau->setColumnCount(selection.size());
    ui->tableau->setHorizontalHeaderLabels(selection);
    ui->tableau->setVerticalHeaderLabels(selection);
    for (int i=0; i<index.size(); ++i)
        for (int j=0; j<index.size(); ++j)
            ui->tableau->setItem(i, j, new QTableWidgetItem(QString::number(temps[index[i]][index[j]])));
}

void MainWindow::tableau()
{
    QVector<QString> selection = villesSelectionnees();
    selection.sort();

    if (selection.empty() || selection.size()==villes.size())
        tableauDefaut();
    else
        tableauModif(selection);
}
