# Simulation d'un aquarium de poissons
Projet de réseaux réalisé à l'ENSEIRB-MATMECA réalisé par :

- Asmae ZIANI

- Reda CHAGUER

- Zayd ZERRAD

- Houssam BAHHOU

Les sources que vous pourrez trouver ici se découpent en deux projets :

- Controler : Partie du contrôleur de l'Aquarium, écrit en C

- Aquarium : Partie de l'affichage , écrit en Java et utilisant la bibliothèque JavaFX.

## Compilation et éxecution

pour compiler et éxecuter on a créer un `Makefile` qui contient les commandes suivantes :

- `make` : Compile tout le projet

- `make controler_run` : compile la partie controleur si elle n'est pas encore compilée puis l'éxecute.

- `make controler_debug` : lance la commande précedente avec valgrind

- `make client_runX` : compile et éxecute le client associé à la vue X, en choisisant le fichier de configuration correspondant

- `make lib_config` : lance le script `lib_config.sh` qui copie les fichiers .jar de JavaFX de la version Linux vers /lib 

- `make clean` : nettoie le répértoire du projet en supprimant les fichiers et dossiers inutiles crées au moment du build
## Quelques détails d'utilisation

Lorsque vous lancerez le projet il ne disposera d'aucun aquarium en place.
C'est pourquoi, avant de tenter une quelconque authentification avec un quelconque client , il vaudra mieux charger
un aquarium côté serveur.

Lors de la connction d'un client, un fichier de log `log_Nid.txt` est crée, il va contenir l'ensemble des échanges entre le client et le serveur.
De même, il existe un fichier `server_log.txt` qui fait la même chose mais du côté serveur.



## A propos des tests

Nous avons réalisé des tests sur la partie controleur uniquement, permettant de vérifier le bon fonctionnement de nos algorithmes de mobilité,
et d'autres fonctionnalités (parsing du fichier de configuration, chargement de l'aquarium)   