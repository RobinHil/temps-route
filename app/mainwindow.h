
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QListWidgetItem>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QVector<QVector<int>> temps;
    QVector<QString> villes;

    void chargerTemps();
    void chargerVilles();

    void FWarshall();

    void tableauDefaut();
    void tableauModif(const QVector<QString>&);
    void diametre();

    QVector<QString> villesSelectionnees();
    bool isSelectionDepartArrivee();

private slots:
    void aPropos();
    void tempsRoute();
    void tableau();
    void reinitialiser();
};

#endif // MAINWINDOW_H
