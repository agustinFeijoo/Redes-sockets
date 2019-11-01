#include<stdlib.h>
#include<stdio.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<unistd.h>

#include<string.h>

void error(const char *msg){
	perror(msg);
	exit(1);
}
int main(int argc,char *argv[]){
	if(argc<2)
		fprintf(stderr,"Port No not provided.Error");

		int sockfd,newsockfd,portno,n;
		char buffer[255];
		struct sockaddr_in serv_addr,cli_addr;//
		socklen_t clilen;
		sockfd=socket(AF_INET,SOCK_STREAM,0);//porque no af_unit? es para la comunicacion interna
		if(sockfd<0)
			error("Error opening socket");
		bzero((char*)&serv_addr,sizeof(serv_addr));
		portno=atoi(argv[1]);

		serv_addr.sin_family=AF_INET;
		serv_addr.sin_addr.s_addr=INADDR_ANY;
		serv_addr.sin_port=htons(portno);
		printf("sockfd: %d creado con los parametros AF_INET=%d y SOCK_STREAM %d",sockfd,AF_INET,SOCK_STREAM);

        // printf("\n serv_addr.sin_family=AF_INET osea %d.",AF_INET);
        // printf("\n serv_addr.sin_addr.s_addr=INADDR_ANY osea %d.",INADDR_ANY);
        printf("\n serv_addr.sin_port=htons(portno) osea %d.",htons(portno));
		printf("\n clilen %d",clilen);
		if(bind(sockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr))<0) //clilen
			error("Binding failed");
			
		newsockfd=listen(sockfd,5);
		clilen=sizeof(cli_addr);

		printf("clilen pre accept %u ",clilen);
		newsockfd=accept(sockfd,(struct sockaddr*)&cli_addr,&clilen);

		printf("clilen post accept %u ",clilen);

		printf("\n new sock fd: %d",newsockfd);
		
		if(newsockfd<0)
			error("Error on accept");

		
		while(1){
			bzero(buffer,255);
			fgets(buffer,255,stdin);

			n=write(sockfd,buffer,255);
			if(n<0)
				error("error on writting");
			bzero(buffer,255);
			
			n=read(sockfd,buffer,255);
			if(n<0)
				error("error on reading");
			
		
		int i=strcmp("Bye",buffer);
		if(i==0)
			break;
		}
		close(newsockfd);
		close(sockfd);
		return 0;
}








