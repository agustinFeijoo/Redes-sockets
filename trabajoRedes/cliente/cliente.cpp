#include <netinet/in.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <iostream>

using namespace std;
void error(const char *error)
{
    perror(error);
    exit(1);
}

int main()
{
    int sockfd, newSockFd, port, nPalabras = 0, cMensajeFichero = 6, nCaracteresFichero, words = 0;
    char buffer[255], c, fichero[100], ch = ' ';
    socklen_t addrlen;

    hostent *he;
    sockaddr_in serv_addr;
    FILE *f;

    printf("Ingrese el puerto ");
    scanf("%d", &port);

    he = gethostbyname2("127.0.0.1", AF_INET);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    // serv_addr.sin_addr.s_addr=;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);

    if (connect(sockfd, (sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) // porque no da err de parseo?
        error((char *)"Error al conectar");
    printf("Se conecto exitosamente con el servidor");
    printf("Para salir del chat escribir 'chau'\n");

    while (strncmp(buffer, "chau", 4) != 0)
    {
        bzero(buffer, sizeof(buffer));
        printf("\n Cliente: ");
        cin.getline(buffer, 255);

        write(sockfd, &buffer, sizeof(buffer));

        bzero(buffer, sizeof(buffer));
        read(sockfd, buffer, sizeof(buffer));

        printf("\n Servidor: %s", buffer);
        
    }
    // Para enviar archivo

    f = fopen("texto", "r");
    while ((c = getc(f)) != EOF)
    {
        fscanf(f, "%s ", buffer);
        if ((isspace(c)) || c == '\t')
            words++;
    }
    write(sockfd, &words, sizeof(int));
    rewind(f);
    while (ch != EOF)
    { 
        fscanf(f, "%s", buffer);
        write(sockfd, buffer, 255);
        ch = fgetc(f);
    }
    printf("el archivo texto se envió correctamente");

    close(sockfd);
    fclose(f);
}
