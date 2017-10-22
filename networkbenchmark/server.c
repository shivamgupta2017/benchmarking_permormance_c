#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <time.h>
#include <netinet/in.h>
#include <ctype.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#define STR_SIZE 1000000
#define SIZE_IN_MB 8000000000
#define MAX_CLIENT 1000
#define MAX_FILESIZE 1000
#define THREAD_SIZE 8
int communicationSocket;

int check_numeric(char *string){
        int indx = 0;

        for(indx = 0; indx < strlen(string); indx++){
                if(!isdigit(string[indx])){
                        return 0;
                }
        }

        return 1;
}



int send_message(char *msg){
	

        if(send(communicationSocket, msg, strlen(msg) , 0))

	return 0;
}

char *trim(char *str){
        int indx = 0;

        for(indx = strlen(str)-1; indx >= 0; indx--){
                if(str[indx] != ' ' && str[indx] != '\t' && str[indx] != '\r' && str[indx] != '\n'){
                        break;
                }
        }

        str[indx+1] = '\0';

        return str;
}


int createConnection(int serverPort)
{
	int serverFd, newSocket;
        struct sockaddr_in address, clientAddr;
        int opt = 1;
        int addrlen = sizeof(address);

	// Creating socket file descriptor
        serverFd = socket(AF_INET, SOCK_DGRAM, 0);

        memset((char *) &address, 0, sizeof(address));

        address.sin_family = AF_INET;
        address.sin_addr.s_addr = inet_addr(INADDR_ANY);
        address.sin_port = htons( serverPort );
        // Forcefully attaching socket to the port
        if (bind(serverFd, &address, sizeof(address))<0)
        {
                perror("bind failed");
                exit(EXIT_FAILURE);
        }

      

	return serverFd;
}


int recieve_message(char *buffer, int length)
{
  //      socklen_t len=sizeof(address);
//	recvfrom(communicationSocket, buffer, (int)strlen(buffer) + 1, 0, (struct sockaddr *)&address, &len)



	return 1;
}

void *open_thread(void *args)
{

        char str[STR_SIZE];
        memset(str, 'a', sizeof(str));
        str[STR_SIZE] = '\0';
        int indx=0;
        
        for(indx = 0; indx < SIZE_IN_MB; indx++)
        {       
                send_message(str);
               // recieve_message(user, sizeof(user));
                //memset(buffer, '\0', sizeof(buffer));
                //printf("recieve_message :%s",buffer);
        }

        return NULL;

}



int main(int argc, char const *argv[])
{
	int serverPort = 12345;
	char strPortNo[8];
	char user[100];
	int indx = 0;

	if(argc == 2){
		if(strlen(argv[1]) > 5){
			printf("Invalid Port Number");
			exit(EXIT_FAILURE);
		}

		strncpy(strPortNo, argv[1], sizeof(strPortNo)-1);	

		if(!check_numeric(strPortNo)){
			printf("Non Numeric Port Number not allowed");
                        exit(EXIT_FAILURE);
		}

		serverPort = atoi(strPortNo);
	
		if(serverPort < 1024 || serverPort > 65535)
                {
			printf("Invalid Port Number");
                        exit(EXIT_FAILURE);
		}
	
	}


	int serverFd=createConnection(serverPort);
        printf("serverFd : %d",serverFd);
        
        
                
        //1 mb ki string 
        pthread_t tid[THREAD_SIZE];

        int i;
        for(i =0; i<THREAD_SIZE; i++)
        {
                //create thread herer e;;;;
                pthread_create(&tid[indx], NULL, open_thread, NULL);
        }

        for(indx = 0; indx < THREAD_SIZE; indx++)
        {
                pthread_join(tid[indx], NULL);
        }

	printf("finish");
        


	return 0;



}

