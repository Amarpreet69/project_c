/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
#include "messenger.h"

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
	int sockfd, newsockfd, portno;
	socklen_t clilen;
	char buffer[256], temp[256];
	char output[256];
	struct sockaddr_in serv_addr, cli_addr;
	int n;
	struct hostent *ptrh; /* pointer to a host table entry */
	struct protoent *ptrp; /* pointer to a protocol table entry */
	//struct sockaddr_in sad; /* structure to hold an IP address */
	//int sd; /* socket descriptor */
	//int port; /* protocol port number */
	char *host; /* pointer to host name */
	//int n; /* number of characters read */
	//char buf_recv[1000],buf_send[100]; /* buffer for data from the server */
	char *filename;
	char file_buffer[10000], f_buffer[256];
	FILE *fp;

#ifdef WIN32
	
	WSADATA wsaData;
	WSAStartup(0x0101, &wsaData);

#endif

	memset((char *)&serv_addr,0,sizeof(serv_addr)); /* clear sockaddr structure */
	//sad.sin_family = AF_INET; /* set family to Internet */

	/* Check command-line argument for protocol port and extract */
	/* port number if one is specified. Otherwise, use the default */
	/* port value given by constant PROTOPORT */

	if (argc < 2) {
		fprintf(stderr,"ERROR, no port provided\n");
		exit(1);
	}

	if ( ((int)(ptrp = getprotobyname("tcp"))) == 0) {
		fprintf(stderr, "cannot map \"tcp\" to protocol number");
		exit(1);
	}
	
	sockfd = socket(AF_INET, SOCK_STREAM, ptrp->p_proto);
	
	if (sockfd < 0) 
		error("ERROR opening socket");
	bzero((char *) &serv_addr, sizeof(serv_addr));
	portno = atoi(argv[1]);
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);
	
	if (bind(sockfd, (struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
		error("ERROR on binding");	
	listen(sockfd,5);
	clilen = sizeof(cli_addr);
	newsockfd = accept(sockfd,(struct sockaddr *) &cli_addr, &clilen);

	if (newsockfd < 0) 
		error("ERROR on accept");
	
	printf("\n------------------------You are Connected----------------------\n");
	
RMESSAGE :	bzero(output,256);
		n = read(newsockfd,output,255);
		
		if(strcmp(output, "SENDFILE\n") == 0) {
			goto RECIEVEFILE;					
		}
	
		if((strcmp(output, "CLOSE\n") != 0)){
		}
		else
			goto EXIT;	
               
		if (n < 0) 
			error("ERROR reading from socket");

		printf("                                           %s\n",output);
WMESSAGE:	printf("You : ");	
		fgets(buffer, 255, stdin);
		n = write(newsockfd, buffer, strlen(buffer));
		
		if((strcmp(buffer, "SENDFILE\n") == 0)){
			if (n < 0)
				error("ERROR writing to socket");
		goto SENDFILE;
		}
		
		if((strcmp(buffer, "CLOSE\n") != 0)){
			if (n < 0)
				error("ERROR writing to socket");
		goto RMESSAGE;
		}
		else
			goto EXIT;
RECIEVEFILE : 	
		n = recv(newsockfd, temp, sizeof(file_buffer), 0);
	
		n = recv(newsockfd, file_buffer, sizeof(file_buffer), 0);
		file_buffer[n] = '\0';
		//printf("%s %d\n",file_buffer,n);
		fflush(stdout);
		
		fp = fopen("DOWNLOADED.TXT", "w");

		fputs(file_buffer, fp);
		
		printf("File recieved (Name : %s, Size : %d bytes)\n", temp, n);
		
		fclose(fp);
		
		goto WMESSAGE;

SENDFILE :	
		printf("Enter Filename in current directory : ");
		scanf("%s", file_buffer);
		
		write(newsockfd, file_buffer, strlen(file_buffer));

		if (n < 0) 
			error("ERROR writing to socket");		
		
		if((fp = fopen(file_buffer, "r")) == NULL){
			printf("File not found.\n");
			goto RMESSAGE;
		}
		else
			printf("Sending file......\n");
		memset(&file_buffer, 0, sizeof(file_buffer));

		while(!feof(fp)){
			fgets(f_buffer,1000,fp);
			if (feof(fp))
			break;
			strcat(file_buffer,f_buffer);

		}

		fclose(fp);

		send(newsockfd, file_buffer, strlen(file_buffer), 0);
		
		printf("File sent.\n");
	
		goto RMESSAGE;

		

EXIT :		printf("\n-----------------------You are Disconnected--------------------\n");	
	close(newsockfd);
	close(sockfd);
return 0; 
}
