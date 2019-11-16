#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <iostream>
#include <string.h>
using namespace std;
void error(const char *error)
{
    perror(error);
    exit(1);
}

int main()
{
    int sockfd, newSockFd, port;
    int words,nWords;
    char buffer[255];

    socklen_t addrlen;
    FILE* f;
    sockaddr_in serv_addr, client_addr;
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
    if (bind(sockfd, (sockaddr *)&serv_addr, sizeof(serv_addr))) // Por que no hay error de parseo?
        error("error en el enlace");

    if (listen(sockfd, 5))
        error("Error on listen()");

    addrlen = sizeof(sockaddr);
    newSockFd = accept(sockfd, (sockaddr*)&client_addr, &addrlen);
    if (newSockFd == -1)
        error("Error on accept");
    printf("Para salir del chat escribir 'chau'\n");
    while (strncmp(buffer, "chau", 4))
    {
        bzero(buffer, sizeof(buffer));

        if (read(newSockFd, buffer, sizeof(buffer)) < 0)
            error("error en read()");
       
            printf("Cliente :%s", buffer);

        bzero(buffer, sizeof(buffer));

        printf("\n Server:");
        cin.getline(buffer, 255);
        if (write(newSockFd, &buffer, sizeof(buffer)) < 0)
            error("Error en write()");
    }

    f=fopen("archivoRecibido.txt","a");
    read(newSockFd,&words,sizeof(int));
    bzero(buffer,sizeof(buffer));
    for(int ch=0;ch<words;ch++){
        read(newSockFd,buffer,255);
        fprintf(f,"%s ",buffer);
    }
    printf("Archivo guardado con el nombre de 'archivoRecibido'");
    fclose(f);
    close(sockfd);
    close(newSockFd);
}
