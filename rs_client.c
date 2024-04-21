#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>


char msg[500];

/* fonction qui permet d'envoyer un message 
*@param la_socket correspond à la socket du client 
*/
void *recvmg(void *la_socket) // ma socket 
{
    int sock = *((int *)la_socket);
    int len;

    // le thread du client est toujours prêt à envoyer un message
    while((len = recv(sock,msg,500,0)) > 0) {
        msg[len] = '\0';
        fputs(msg,stdout);
    }

}

int main(int argc,char *argv[]){
    pthread_t recvt;
    int len, sock;

    char send_msg[500];
    struct sockaddr_in serveur;
    char client_name[100];
    strcpy(client_name, argv[1]);
    sock = socket( AF_INET, SOCK_STREAM,0);
    serveur.sin_port = htons(1234);
    serveur.sin_family= AF_INET;
    serveur.sin_addr.s_addr = inet_addr("127.0.0.1");
    if( (connect( sock ,(struct sockaddr *)&serveur,sizeof(serveur))) == -1 )
        printf("\n echec de la connexion au socket  \n");

    //création d'un thread client qui attend toujours un message
    pthread_create(&recvt,NULL,(void *)recvmg,&sock);



    //prêt à lire un message de la console
    while(fgets(msg,500,stdin) > 0) {
       
        strcpy(send_msg,client_name);
        strcat(send_msg,":");
        strcat(send_msg,msg);
        len = write(sock,send_msg,strlen(send_msg)); // la fonction write() est utilisé pour écrire dans la socket 
        if(len < 0)
            printf("\n le message n'a pas été envoyé  \n");
    }
    //fermeture du thread
    pthread_join(recvt,NULL);
    close(sock);

    return 0;
}
