# Commandes

* __make all__  : Compile tout les fichiers
* __make test__ : Lancement de la série de tests automatiques
* __make lib__ : Génération de la bibliothéque static et dynamique
* __make doc__  : Génération de la documentation (doxygen)
* __make rapport__ : Génération du rapport (latex)
* __make clean__ : Nettoyage du projet (supression des objets et binaires)
* __make demo-1 ligne=X col=X__ : Lancer la démo colimacon
* __make demo-2__: Lancer la démo horizontal
* __make demo-3__: Lancer la démo vertical
* __make demo-4__: Lancer la démo carr
* __make demo-5 ligne=X col=X__ : Lancer la démo colimacon sans print (utile pour le bench)
* __make demo-6 ligne=X col=X__ : Lancer la démo colimacon avec sortie temps (utile pour le bench)
* __make tgz__: Creation de l'achive de rendu
* __make bench echantillon=X fichier=X__: Generation des bench de temps pour le rapport.

# Arborescence

* __bin__ : Binaire exécutable
  * __demo__ : Exécutable de démonstration
  * __test__ : Exécutable de test
* __lib__ : Bibliothéque
* __doc__ : Documentation doxygen sous differents formats
* __rapport__ : Source du rapport
* __res__ : Ressources necessaire au projet (fichier de bdd)
* __script__  : Script utilisé pour les test
* __src__ : Source du projet
  * __colimacon__   : Source de colimacon
  * __demo__  : Sources des differentes démonstrations d'utilisation
  * __test__  : Sources des dufferents tests
* __bench__: Fichier de bench pour le rapport __

* *sujet.pdf*  : Sujet du projet
* *README.md*  : C'est moi
* *rappot.pdf* : Le rapport du projet 

# Tests disponibles

* colimacon 1x1
* colimacon 1x10
* colimacon 10x1
* colimacon 10x2
* colimacon 2x10
* colimacon 10x10
* colimacon 1000x1000 (sans print)
