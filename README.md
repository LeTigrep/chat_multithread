# Chat Multithread Serveur/Client

## Présentation du projet : 

Ce projet été réalisé lors de ma deuxième année de Licence informatique. Il met en œuvre une communication réseau de base entre un serveur et plusieurs clients utilisant des sockets TCP, des threads, et des mutex pour gérer l'envoi et la réception de messages. Le serveur peut accepter plusieurs clients simultanément, chacun communiquant avec le serveur via des threads dédiés.


## Structure du Projet

Le projet est composé de deux principaux fichiers :

- `rs_serveur.c`: Code source du serveur.
- `rs_client.c`: Code source du client.

## Compilation et Exécution

pour compiler avec le makefile 

    make Makefile compile 

si le makefile ne fonctionne pas, utiliser les commandes suivantes 


Pour compiler le serveur 

    ```gcc rs_serveur.c -o rs_serveur -lpthread```  

pour executer le serveur 

    ```./rs_serveur 1234``` 

Pour compiler le client 

    ```gcc rs_client.c -o rs_client -lpthread``` 

pour execturer le client 

    ```./rs_client un_nom``` 

## Fonctionnalités

Le serveur écoute sur le port 1234 pour les connexions entrantes des clients.
Chaque client a un thread dédié pour gérer la communication avec le serveur.
Le serveur diffuse les messages reçus de chaque client à tous les autres clients connectés.
Les mutex sont utilisés pour assurer la synchronisation entre les threads lors de la manipulation de ressources partagées.