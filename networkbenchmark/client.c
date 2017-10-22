// Client side C/C++ program to demonstrate Socket programming
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#define STR_SIZE 1000000
#define SIZE_IN_MB 80000
#define THREAD_SIZE 8
#define STR_SIZE 1000000

int connectionSocket;
struct sockaddr_in serv_addr,clientAddr;
int checkIsNumeric(char *string){
        int indx = 0;

        for(indx = 0; indx < strlen(string); indx++){
                if(!isdigit(string[indx])){
                        return 0;
                }
        }

        return 1;
}


int make_connection(int serverPort, char *serverIP)
{
	
	
	
	int sock = socket(AF_INET, SOCK_DGRAM, 0);
	
	if ((sock) < 0)
	{
		printf("\n Socket creation error \n");
		return -1;
	}

	memset(&serv_addr, '0', sizeof(serv_addr));
	

	int length= sizeof(serv_addr);
	bzero((char *) &clientAddr, sizeof(clientAddr));

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = INADDR_ANY;
	serv_addr.sin_port=htons(serverPort);
	// Convert IPv4 and IPv6 addresses from text to binary form

	if(bind(sock, (struct sockaddr *)&clientAddr, length)<0) 
		error("binding");

	return sock;
}

int send_message(char *msg){
	//char msg[1024];
	
	//fgets(msg, 1023, stdin);	
        


sendto(connectionSocket, msg, (int)strlen(msg), 0, (struct sockaddr_in *)&serv_addr, sizeof(serv_addr));



        return 0;
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
                        //recieve_message(user, sizeof(user));
        }

        return NULL;
}

int main(int argc, char const *argv[])
{
	
	//int valread;
	char buffer[STR_SIZE];
	char strPortNo[8];
	int indx;
	int serverPort = 12345;
	char serverIP[100];

		strncpy(strPortNo, argv[2], sizeof(strPortNo)-1);

		if(!checkIsNumeric(strPortNo))
		{
			fprintf(stderr, "Non Numeric Port Number not allowed");
			exit(EXIT_FAILURE);
		}

		serverPort = atoi(strPortNo);

		if(serverPort < 1024 || serverPort > 65535){
			fprintf(stderr, "Invalid Port Number");
			exit(EXIT_FAILURE);
		}

		strncpy(serverIP, argv[1], sizeof(serverIP)-1);
		//ip se ip aaya h 

		
	

	connectionSocket = make_connection(serverPort, serverIP);

		pthread_t tid[THREAD_SIZE];


//	*memset(buffer, '\0', sizeof(buffer));


	for(indx = 0; indx < SIZE_IN_MB; indx++){
		//valread = read( connectionSocket , buffer, STR_SIZE);
		


        int i;
        for(i =0; i<THREAD_SIZE; i++)
        {
                //create thread herer e;;;;
                pthread_create(&tid[indx], NULL, open_thread, NULL);
        }



	}
//	printf("%s",buffer );
//	fflush(stdout);



	
        for(indx = 0; indx < THREAD_SIZE; indx++)
        {
                pthread_join(tid[indx], NULL);
        }




	return 0;
}

