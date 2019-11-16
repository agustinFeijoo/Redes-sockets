#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
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
    newSockFd = accept(sockfd, (struct sockaddr*)&client_addr, &addrlen);
    if (newSockFd == -1)
        error("Error on accept");
    printf("Para salir del chat escribir 'chau'\n");
    printf("Para enviar un archivo escribir 'enviar' y el nombre del archivo \n");
    while (strncmp(buffer, "chau", 4))
    {
        bzero(buffer, sizeof(buffer));

        if (read(newSockFd, buffer, sizeof(buffer)) < 0)
            error("error en read()");
        //Veo si se trata de enviar un archivo
        
        if (strcmp(buffer, "se va a enviar un archivo") == 0)
        { //entro en modo recibir archivo
            read(newSockFd, buffer, sizeof(buffer));
            //me devuelve el nombre del archivo
            f=fopen(buffer,"a");
            read(newSockFd,&words,sizeof(int));
            for(nWords=0;nWords<words;nWords++){
                read(newSockFd,buffer,255);
                fprintf(f,"%s",buffer);
            }
            printf("Se recibió el archivo con exito");
        }
        
      //  if (strcmp(buffer, "\0"))
            printf("Cliente :%s", buffer);

        bzero(buffer, sizeof(buffer));

        printf("\n Server:");
        fgets(buffer,255,stdin);
        if (write(newSockFd, &buffer, sizeof(buffer)) < 0)
            error("Error en write()");
    }
    close(sockfd);
    close(newSockFd);
}

