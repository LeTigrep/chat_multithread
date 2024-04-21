#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>

#define MESSAGE 500

pthread_mutex_t mutex; // mutex 
int clients[20];
int n=0;


/* fonction qui permet d'envoyer un message 
*@param msg un tableau pour le message 
*@param curr ... fonction courrant 
*/
void envoyer(char *msg,int curr){
    int i;
    pthread_mutex_lock(&mutex);
    for(i = 0; i < n; i++) {
        if(clients[i] != curr) {
            if(send(clients[i],msg,strlen(msg),0) < 0) {
                printf("l'envoie a échoué \n");
            }
        }
    }
    pthread_mutex_unlock(&mutex);
}

/* fonction qui permet de recevoir des messages
*@param Client_sock socket du client 
*/
void *recvmg(void *client_sock){
    int sock = *((int *)client_sock);
    char msg[500];
    int len;
    while((len = recv(sock,msg,500,0)) > 0) { // recv permet de lire in ensemnle d'
        msg[len] = '\0';
        envoyer(msg,sock);
    }
}

/*
void sauvegarde(unsigned long int  resultat[MESSAGE]){
    FILE*fichier=fopen("save.log","w");     
    if(fichier==NULL){                  
      printf("impossible d'ouvrir le fichier");
    }
    else{
      for(int i=0;  i<MESSAGE; i++){
        fprintf(fichier,"%lu\n",resultat[i]);
      }
    }   
    fclose(fichier);  
  }*/



int main(){
    struct sockaddr_in serveur; // initialisation du serveur
    pthread_t recvt;
    int sock=0;                 // socket de communication tcp
    int Client_sock=0;

      char msg[1492];   

    serveur.sin_family = AF_INET;       // on présise que c'est une socket réseau 
    serveur.sin_port = htons(1234);     // on initialise au port 1234
    serveur.sin_addr.s_addr = inet_addr("127.0.0.1");  //on accepte une communication avec l'adresse ip 127.0.0.1

    sock = socket( AF_INET , SOCK_STREAM, 0 );   // lier les informations de la socket déjà existante, on rajoute SOCK_STREAM pour signifier qu'il s'agit d'un socket TCP
    if( bind( sock, (struct sockaddr *)&serveur, sizeof(serveur))<0){
        perror("erreur de bind de côté serveur");
        return EXIT_FAILURE;
      }
      else{
        printf("****************************\n");
        printf("*Bienvenue au serveur ghcr*\n");
        printf("****************************\n");
      }

    if(listen(sock,20)<0){          // marque une socket comme une socket de connexion 
      perror("erreur lors de l'ecoute");
      return EXIT_FAILURE;
    }


    while(1){
        if( (Client_sock = accept(sock, (struct sockaddr *)NULL,NULL)) < 0 ) // accept() vas permettre d'accépter la connexion 
            printf("accept a échoué  \n"); // message d'erreur 
        pthread_mutex_lock(&mutex); // verrou pour accépter plusieurs clients 
        clients[n]= Client_sock;
        n++;
        // creation d'un thread pour chaque client
        pthread_create(&recvt,NULL,(void *)recvmg,&Client_sock);
        pthread_mutex_unlock(&mutex); 
    }
    return 0;
}
