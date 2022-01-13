# Projet SAÉ algo C

Ce projet C réponds aux cahier des charges d'un annuaire classique de gestion de clients.

Toutes les fonctionnalitées sont opérationnelles.

Vous retrouverez sur ce dépot GITLAB 8 fichiers :
* l'exectuable "sae algo c.exe" du code dans sa globalitée,
* un fichier c main.c,
* trois fichiers c : fonctionnalitées.c entree-sortie.c et interface.c contentant respectivement le code de ce que leur titre indique,
* un fichier fonction.h pour donner les specifications formelles et relier tout le code,
* un fichier ansi.c et ansi.h qui sont des codes récupérés et non modifiés,
    * voici la source : https://github.com/sol-prog/ansi-escape-codes-windows-posix-terminals-c-programming-examples/tree/article

La répartition est globalement : 60% mathis Guerin / 40% Mathis Toinon.

Certains problemes ont été rencontrés par rapport au dépot git compte tenu du fait qu'il s'agit de notre premier, qui font que les commit manquent de clarté parfois.
Les logiciels utilisés pour devlopper sont Visual Studio 2022 pour Mathis Guerin, et Visual Studio Code pour Mathis Toinon.

A noter que l'application est en presque totalité portable exepté la fonctionnalitée d'effacage qui fonctionne seulement sur Windows.
Les fonctions sont également organisées avec les fonctions metier contenues dans fonctionnalitées et entree-sortie, et les fonctions d'interface avec l'intercation utilisateur dans interface. C'est une architecture modulaire qui permet l'implémentation facilement d'une interface graphique.

Les details d'utilisations sont implémentés dans le code afin que l'utilisateur puisse directement utiliser l'application.