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
	int sockfd, sd2, portno, n;
	struct sockaddr_in serv_addr;
	struct hostent *server;
	char buffer[256], temp[256], ti[256], temp2[256], hostname[256] = "";
	char output[256];
	int filesize, port = 0;
	struct protoent *ptrp;							/* pointer to a protocol table entry */
	char file_buffer[10000], f_buffer[256];
	FILE *fp, *logc;

#ifdef WIN32
	WSADATA wsaData;
	WSAStartup(0x0101, &wsaData);

#endif
	
	write(1, "\E[H\E[2J", 7);
	printf("HostAddress : ");
	scanf("%s", hostname);
	printf("Port : ");
	scanf("%d", &port);
	write(1, "\E[H\E[2J", 7);

	if (strcmp(hostname, "") == 0 && port == 0) {
		fprintf(stderr,"usage %s hostname port\n", argv[0]);
		exit(0);
	}

	portno = port;
	

	if ( ((int)(ptrp = getprotobyname("tcp"))) == 0) {
		fprintf(stderr, "cannot map \"tcp\" to protocol number");
		exit(1);
	}
	
	sockfd = socket(AF_INET, SOCK_STREAM, ptrp -> p_proto);
	
	sd2 = sockfd;	
	
	if (sockfd < 0) 
        	error("ERROR opening socket");
	server = gethostbyname(hostname);

	if (server == NULL) {
		fprintf(stderr,"ERROR, no such host\n");
		exit(0);
	}

	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(hostname);
	serv_addr.sin_port = htons(portno);

	if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) 
		error("ERROR connecting");
	
	logc = fopen("Log2", "a+");
 	
	printf("\n\t\t\t\t\t\t\tStatus : Online\t\t\t\t\t\n\n");

WMESSAGE:	printf("\tYou : ");
		bzero(buffer,256);
		fgets(buffer,255,stdin);
		n = write(sockfd, buffer, strlen(buffer));
		if(strcmp(buffer, "SENDFILE\n") == 0){
			goto SENDFILE;		
		}
		if((strcmp(buffer, "CLOSE\n") != 0)){
			strcpy(temp2, buffer);
			current_time();
			strip(temp2);
			strcat(strcat(strcat(c_time, "\tYou : "), temp2), "\n");
			fputs(c_time, logc);
			memset(&c_time, 0, sizeof(c_time));
			memset(&temp2, 0, sizeof(temp2));			
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
			 printf("\t\t\t\t\t\t\t\t\t\t\t%s\n", output);
			current_time();
		strip(output);
			strcat(strcat(strcat(c_time, "\t"), output), "\n");
			fputs(c_time, logc);
			memset(&c_time, 0, sizeof(c_time));
			goto WMESSAGE;
		}
		else
			goto EXIT;
		
		

SENDFILE : 	printf("\tEnter Filename in current directory : ");
		scanf("%s", file_buffer);
		strcpy(temp2, file_buffer);
		
		write(sockfd, file_buffer, strlen(file_buffer));

		if (n < 0) 
			error("ERROR writing to socket");		
		
		if((fp = fopen(file_buffer, "r")) == NULL){
			printf("\nFile not found.\n");
			write(sockfd, "fail", 5);
			goto RMESSAGE;
		}
		else
			printf("\tSending file......\n");
		memset(&file_buffer, 0, sizeof(file_buffer));

		while(!feof(fp)){
			fgets(f_buffer,1000,fp);
			if (feof(fp))
			break;
			strcat(file_buffer,f_buffer);

		}

		fclose(fp);

		send(sockfd, file_buffer, strlen(file_buffer), 0);
		
		printf("\tFile sent.\n");
		
		filesize = file_size(temp2);
		sprintf(ti, "You : File sent (Name : %s, Size : %d bytes)", temp2, filesize);
	
		current_time();
		strcat(strcat(strcat(c_time, "\t"), ti), "\n");
		fputs(c_time, logc);
		memset(&c_time, 0, sizeof(c_time));
		memset(&ti, 0, sizeof(ti));
		memset(&temp2, 0, sizeof(temp2));
		
		goto RMESSAGE;

RECIEVEFILE :	n = recv(sd2, temp, sizeof(file_buffer), 0);
		n = recv(sd2, file_buffer, sizeof(file_buffer), 0);
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
		fputs(c_time, logc);
		memset(&c_time, 0, sizeof(c_time));
		memset(&ti, 0, sizeof(ti));
		
		fclose(fp);
		
		goto WMESSAGE;
	
	
EXIT :		printf("\n\t\t\t\t\t\t\tStatus : Offline\t\t\t\t\t\n\n");	
		close(sockfd);
		fclose(logc);
return 0;
}
