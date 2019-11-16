#include <netinet/in.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>

void error(const char *error)
{
    perror(error);
    exit(1);
}

int main()
{
    int sockfd, newSockFd, port, nPalabras = 0, cMensajeFichero = 6, nCaracteresFichero = 0, words = 0;
    char buffer[255], c, fichero[100], ch;
    socklen_t addrlen;
    char *modoEnvio;

    modoEnvio = "se va a enviar un archivo";

    struct hostent *he;
    struct sockaddr_in serv_addr;
    FILE *f;

    printf("Ingrese el puerto");
    scanf("%d", &port);
    he = gethostbyname2("127.0.0.1", AF_INET);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);

    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) // porque no da err de parseo?
        error((char *)"Error al conectar");

    printf("Para salir del chat escribir 'chau'\n");
    printf("Para enviar un archivo escribir 'enviar' y el nombre del archivo \n");

    while (strncmp(buffer, "chau", 4) != 0)
    {
        bzero(buffer, sizeof(buffer));
        printf("\n Cliente: ");
        fgets(buffer, 255, stdin);
        int resp = strncmp(buffer, "enviar", 6);
        if (strncmp(buffer, "enviar", 6) == 0)
        {   //6 por letras de enviar
            //error {
/*
            while (buffer[cMensajeFichero] != '\0')
            {

                //código lector del titulo del fichero
                fichero[nCaracteresFichero] = buffer[cMensajeFichero + 1]; //cMensajeFichero=6(letras de enviar)+1 por el espacio
                nCaracteresFichero++;

                cMensajeFichero++;
            }
            //f = fopen(fichero, "r");
            while ((c = getc(f)) != EOF)
            {
                fscanf(f, "%s", buffer);
                if ((isspace(c)) || (c = '\t'))
                    words++;
            }
            write(sockfd, modoEnvio, sizeof(modoEnvio));
            write(sockfd, fichero, sizeof(fichero));

            write(sockfd, &words, sizeof(int));
            rewind(f);
            bzero(&ch,sizeof(ch));
            while (ch != EOF)
            {
                fscanf(f, "%s", buffer);
                write(sockfd, buffer, 255);
                ch = fgetc(f);
            }

            printf("Archivo enviado con exito!");
            */
            // }error
        }
    }

    write(sockfd, &buffer, sizeof(buffer));

    bzero(buffer, sizeof(buffer));
    read(sockfd, buffer, sizeof(buffer));

    printf("\n Servidor: %s", buffer);

    close(sockfd);
    fclose(f);
}
