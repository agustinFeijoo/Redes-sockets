#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
//Definidas por mi
#include "conversacion.h"

#define SIZE_OF_BUFFER 1024
 
char buffer[SIZE_OF_BUFFER];



int main()
{
    int sockfd, newSockFd, port;
    int words, nWords;

    socklen_t addrlen;
    struct sockaddr_in serv_addr, client_addr;
    //AF_INET voy a usar los protocolos ARPA de internet
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        error("Error al crear el socket");
    }

    printf("Ingrese el puerto ");
    scanf("%d", &port);
    
    bzero((char *)&serv_addr.sin_zero, 8); //Para que sirve limpiar la var en este caso?
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(port);
    if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr))) // Por que no hay error de parseo?
        error("error en el enlace");

    if (listen(sockfd, 5))
        error("Error on listen()");

    addrlen = sizeof(struct sockaddr);
    newSockFd = accept(sockfd, (struct sockaddr *)&client_addr, &addrlen);
    if (newSockFd == -1)
        error("Error on accept");
    printf("Para salir del chat escribir 'chau'\n");
    printf("Y para enviar un archivo escribir T\n");
    /*
        Se inicia la conversación
    
*/
    while (strncmp(buffer, "chau", 4)!=0)
    {
        printf("\nCliente:");
        printf("%s",modoRecibir(newSockFd,buffer));
        //Modo recibir también hace la llamada a recibirArchivo(...)
        printf("\n Server:");
        printf("%s",modoEnvio(newSockFd,buffer));
        //Modo envio también hace la llamada a transferirArchivo(...)
    }
    close(sockfd);
    close(newSockFd);
}
