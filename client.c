#include "messenger.h"

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[])
{
	int sockfd, sd2, portno, n;
	struct sockaddr_in serv_addr;
	struct hostent *server;
	char buffer[256], temp[256];
	char output[256];
	//struct hostent *ptrh; /* pointer to a host table entry */
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
	//memset((char *)&serv_addr,0,sizeof(serv_addr)); /* clear sockaddr structure */
	//sad.sin_family = AF_INET; /* set family to Internet */
	/* Check command-line argument for protocol port and extract */
	/* port number if one is specified. Otherwise, use the default */
	/* port value given by constant PROTOPORT */

	if (argc < 3) {
		fprintf(stderr,"usage %s hostname port\n", argv[0]);
		exit(0);
	}

	portno = atoi(argv[2]);
	

	if ( ((int)(ptrp = getprotobyname("tcp"))) == 0) {
		fprintf(stderr, "cannot map \"tcp\" to protocol number");
		exit(1);
	}
	
	sockfd = socket(AF_INET, SOCK_STREAM, ptrp -> p_proto);
	
	sd2 = sockfd;	
	
	if (sockfd < 0) 
        	error("ERROR opening socket");
	server = gethostbyname(argv[1]);

	if (server == NULL) {
		fprintf(stderr,"ERROR, no such host\n");
		exit(0);
	}

	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr,server->h_length);
	serv_addr.sin_port = htons(portno);

	if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
		error("ERROR connecting");
	
	printf("\n------------------------You are Connected----------------------\n");

WMESSAGE:	printf("You : ");
		bzero(buffer,256);
		fgets(buffer,255,stdin);
		n = write(sockfd, buffer, strlen(buffer));
		if(strcmp(buffer, "SENDFILE\n") == 0){
			goto SENDFILE;		
		}
		if((strcmp(buffer, "CLOSE\n") != 0)){
		}
		else {
			goto EXIT;
		}
	
		if (n < 0) 
			error("ERROR writing to socket");
RMESSAGE:	bzero(output, 256);
		n = read(sockfd, output, 255);
		if (n < 0) 
			error("ERROR reading from socket");
		
		if((strcmp(output, "SENDFILE\n") == 0)) {
			goto RECIEVEFILE;
		}		


		if((strcmp(output, "CLOSE\n") != 0)) {
			 printf("                                           %s\n", output);
			goto WMESSAGE;
		}
		else
			goto EXIT;

SENDFILE : 	
		printf("Enter Filename in current directory : ");
		scanf("%s", file_buffer);
		
		write(sockfd, file_buffer, strlen(file_buffer));

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

		send(sockfd, file_buffer, strlen(file_buffer), 0);
		
		printf("File sent.\n");
		
		goto RMESSAGE;

RECIEVEFILE :
		n = recv(sd2, temp, sizeof(file_buffer), 0);
	
		n = recv(sd2, file_buffer, sizeof(file_buffer), 0);
		file_buffer[n] = '\0';
		//printf("%s %d\n",file_buffer,n);
		fflush(stdout);
		
		fp = fopen("DOWNLOADED.TXT", "w");

		fputs(file_buffer, fp);
		
		printf("File recieved (Name : %s, Size : %d bytes)\n", temp, n);
		
		fclose(fp);
		
		goto WMESSAGE;
	
	
EXIT :		printf("\n-----------------------You are Disconnected--------------------\n");	
		close(sockfd);
return 0;
}
