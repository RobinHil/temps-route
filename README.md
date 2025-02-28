# 🚗 Temps de Route (Travel Time)

Application permettant de calculer le temps de trajet entre différentes villes.

## 📝 Description

Temps-Route est une application desktop développée en C++ avec Qt qui permet de :
- Calculer le temps de trajet entre deux villes
- Visualiser une matrice des temps de trajet entre plusieurs villes
- Identifier le diamètre du réseau routier (plus long trajet entre deux villes)

## ✨ Fonctionnalités

- 🔄 Interface graphique intuitive
- 📊 Affichage des temps sous forme de tableau
- 🔍 Sélection multiple de villes
- 📈 Calcul automatique des chemins optimaux (algorithme de Floyd-Warshall)
- 🎯 Calcul du diamètre du réseau
- 💾 Chargement des données depuis des fichiers CSV

## 🛠️ Technologies utilisées

- C++ 17
- Qt 6
- Interface utilisateur Qt Designer
- Format de données CSV

## 📦 Structure du projet

```
temps-route/
├── data/
│   ├── temps.csv      # Données des temps entre villes
│   └── villes.csv     # Liste des villes
├── app/
│   ├── main.cpp
│   ├── mainwindow.cpp
│   ├── mainwindow.h
│   └── mainwindow.ui
└── temps_route.pro    # Fichier projet Qt
```

## 🚀 Installation

1. Assurez-vous d'avoir Qt 6 et un compilateur C++ compatible C++17 installés
2. Clonez le repository
3. Ouvrez le fichier `temps_route.pro` dans Qt Creator
4. Compilez et exécutez le projet

## 📖 Utilisation

1. Lancez l'application
2. Sélectionnez une ville de départ dans la liste de gauche
3. Sélectionnez une ville d'arrivée dans la liste de droite
4. Cliquez sur "Calculer le temps de route"
5. Le temps de trajet s'affiche en minutes
6. Pour voir tous les temps de trajet, consultez le tableau à droite

## 🔧 Configuration des données

Les données sont stockées dans deux fichiers CSV :
- `villes.csv` : Liste des villes avec leur identifiant
- `temps.csv` : Temps de trajet entre les villes au format "ville1,ville2,temps"

## 👨‍💻 Développement

Le projet utilise l'algorithme de Floyd-Warshall pour calculer les plus courts chemins entre toutes les paires de villes. Les temps sont stockés dans une matrice d'adjacence et mis à jour au démarrage de l'application.
