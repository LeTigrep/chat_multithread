compile :
    gcc -Wall -g3 -pthread serveur/rs_serveur.c -o serveur/rs_serveur
    gcc -Wall -g3 -pthread client/rs_client.c -o client/rs_client 