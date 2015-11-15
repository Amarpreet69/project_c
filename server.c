/*  C Messenger

    Copyright (C) 2015 Amarpreet Singh Arora

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#include "messenger.h"
int main(int argc, char *argv[]) {
	int server_port = 0;
	int sockfd, newsockfd, portno;
	socklen_t clilen;
	char buffer[256], temp[256], ti[256], temp2[256];
	char output[256], s_addr[20];
	struct sockaddr_in serv_addr, cli_addr;
	int n, filesize;
	struct protoent *ptrp; 					/* pointer to a protocol table entry */
	char file_buffer[10000], f_buffer;
	FILE *fp, *logs;

#ifdef WIN32
	
	WSADATA wsaData;
	WSAStartup(0x0101, &wsaData);

#endif

	memset((char *)&serv_addr,0,sizeof(serv_addr)); 	/* clear sockaddr structure */
	write(1,"\E[H\E[2J",7);
	printf("HostAddress : ");				
	scanf("%s", s_addr);
	printf("Port : ");
	scanf("%d", &server_port);
	write(1,"\E[H\E[2J",7);

	if (server_port == 0) {
		fprintf(stderr,"ERROR, no port provided\n");
		exit(1);
	}

	if ( ((int)(ptrp = getprotobyname("tcp"))) == 0) {
		fprintf(stderr, "cannot map \"tcp\" to protocol number");
		exit(1);
	}
	sockfd = socket(AF_INET, SOCK_STREAM, ptrp->p_proto);	/*Creating Socket for accepting connections*/
	
	if (sockfd < 0) 
		error("ERROR opening socket");
	bzero((char *) &serv_addr, sizeof(serv_addr));
	portno = server_port;					
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(s_addr);
	serv_addr.sin_port = htons(portno);
	
	if (bind(sockfd, (struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
		error("ERROR on binding");	

	listen(sockfd,5);
	clilen = sizeof(cli_addr);

	newsockfd = accept(sockfd,(struct sockaddr *) &cli_addr, &clilen);	/*Creating new socket for communication*/
	if (newsockfd < 0) 
		error("ERROR on accept");
	
	logs = fopen("Log1", "a+");

	printf("\n\t\t\t\t\t\t\tStatus : Online\t\t\t\t\t\n");
	
	
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

		printf("\t\t\t\t\t\t\t\t\t\t\t%s\n",output);
		current_time();
		strip(output);
		strcat(strcat(strcat(c_time, "\t"), output), "\n");
		fputs(c_time, logs);
		memset(&c_time, 0, sizeof(c_time));

WMESSAGE:	printf("\tYou : ");	
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
			strcpy(temp2, buffer);
			current_time();
			strip(temp2);
			strcat(strcat(strcat(c_time, "\tYou : "), temp2), "\n");
			fputs(c_time, logs);
			memset(&c_time, 0, sizeof(c_time));
			memset(&temp2, 0, sizeof(temp2));			
		goto RMESSAGE;
		}
		else
			goto EXIT;

RECIEVEFILE : 	n = recv(newsockfd, temp, sizeof(file_buffer), 0);
	
		n = recv(newsockfd, file_buffer, sizeof(file_buffer), 0);
		file_buffer[n] = '\0';
		fflush(stdout);
		if(strcmp(file_buffer, "fail") == 0) {
			printf("%s", "\t\t\t\t\t\t\t\t\t\t\tFile recieving failed.\n");
			goto WMESSAGE;
		} 
		
		fp = fopen("DOWNLOADED.TXT", "w");

		fputs(file_buffer, fp);
		
		printf("\t\t\t\t\t\t\t\t\t\t\tFile recieved (Name : %s, Size : %d bytes)\n", temp, n);
		sprintf(ti, "File recieved (Name : %s, Size : %d bytes)", temp, n);
		current_time();
		strcat(strcat(strcat(c_time, "\t"), ti), "\n");
		fputs(c_time, logs);
		memset(&c_time, 0, sizeof(c_time));
		memset(&ti, 0, sizeof(ti));

		fclose(fp);
		
		goto WMESSAGE;

SENDFILE :	printf("\tEnter Filename in current directory : ");
		scanf("%s", file_buffer);
		strcpy(temp2, file_buffer);
		
		write(newsockfd, file_buffer, strlen(file_buffer));

		if (n < 0) 
			error("ERROR writing to socket");		
		
		if((fp = fopen(file_buffer, "r")) == NULL){
			printf("\tFile not found.\n");
			write(newsockfd, "fail", 5);
			goto RMESSAGE;
		}
		else
			printf("\tSending file......\n");
		memset(&file_buffer, 0, sizeof(file_buffer));

		while(!feof(fp)){
			f_buffer = fgetc(fp);
			if (feof(fp))
			break;
			strncat(file_buffer, &f_buffer, 1);

		}

		fclose(fp);

		send(newsockfd, file_buffer, strlen(file_buffer), 0);
		
		printf("\tFile sent.\n");		
		filesize = file_size(temp2);
		sprintf(ti, "You : File sent (Name : %s, Size : %d bytes)", temp2, filesize);
	
		current_time();
		strcat(strcat(strcat(c_time, "\t"), ti), "\n");
		fputs(c_time, logs);
		memset(&c_time, 0, sizeof(c_time));
		memset(&ti, 0, sizeof(ti));
		memset(&temp2, 0, sizeof(temp2));
	
		goto RMESSAGE;

		

EXIT :		printf("\n\t\t\t\t\t\t\tStatus : Offline\t\t\t\t\t\n\n");	
		close(newsockfd);
		close(sockfd);
		fclose(logs);
return 0; 
}
