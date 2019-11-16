#include <stdio.h>
#include <string.h>
#include <iostream>

using namespace std;
int main(){
    FILE* f;
    char fichero[255],buffer[255],c;
    int nCaracteresFichero=0,cMensajeFichero=6,nLetra;

    
    printf("ingrese el fichero a buscar:");

    while (strncmp(buffer,"chau",3)!=0)
    {
        bzero(buffer,sizeof(buffer));
        printf("\n Cliente: ");
        cin.getline(buffer,255);
        
        if(strncmp(buffer,"enviar",6)==0){
            while(buffer[cMensajeFichero]!='\0'){
            //código lector del titulo del fichero
                fichero[nCaracteresFichero]=buffer[cMensajeFichero+1];//cMensajeFichero=6(letras de enviar)+1 por el espacio
                nCaracteresFichero++;
                cMensajeFichero++;
            }
            f=fopen(fichero,"r");
            int longitud,size;
            
            //longitud=lenghtof(buffer);
            size=sizeof(buffer);

            bzero(buffer,sizeof(buffer));
            while((c=fgetc(f))!=EOF){
                buffer[nLetra]=c;
                nLetra++;
             }
        printf("%s",buffer);

    }
    }
}