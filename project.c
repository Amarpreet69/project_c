#include<stdio.h>
#include<stdlib.h>
#include<mysql/mysql.h>
#include<string.h>

	
	int *port = 3306;
	char *username, *password, *database = "attendance", *server = "localhost";
	
int main() {
	MYSQL *con;
	MYSQL *res;
	MYSQL *row;
	int mis;
	char name[20], smis[20];
	int dec = 1, choice;
	char subject[10], user[10], pass[10], create1[100] = "create table ", create2[30] = "(srno int, name varchar(10))", drop1[30] = "drop table if exists ", insert1[50] = "insert into ", insert2[25] = " (srno, name) values(" ;
	printf("Username : ");
	scanf("%s", &user);
	printf("Password : ");
	scanf("%s", &pass);
	username = &user;
	password = &pass;
	con = mysql_init(NULL);	

	if(mysql_real_connect(con, server, username, password, database, port, NULL, 0))
		printf("Connected to temp..\n");
	else
		printf("Not Connected\n");

	
	while(dec) {
		printf("1.Add Subject\n2.Add Student\n3.Exit\n");
		scanf("%d", &choice);
		switch(choice) {
		case 1: 
			printf("Enter Subject name : ");
			scanf("%s", &subject);
			if(mysql_query(con, strcat(strcat(create1, subject), create2)))
				finish_with_error(con);
			else
				printf("Subject added\n");
  			
			break;
		case 2:
			printf("Enter Subject : ");
			scanf("%s", subject);
			printf("Enter MIS and Name : ");
			scanf("%d%s", &mis, &name);
			sprintf(smis, "%d", mis);
			if (mysql_query(con, strcat(strcat(strcat(strcat(strcat(strcat(insert1,subject),insert2),smis), ", '"), name), "');")))
				finish_with_error(con);
			else
				printf("Student added.\n");
				   
				
				break;
		case 3:
			dec = 0;
			break;
		}
			
	}	

mysql_close(con);
	
return 0;
}

void finish_with_error(MYSQL *con)
{
  fprintf(stderr, "%s\n", mysql_error(con));
  mysql_close(con);
  exit(1);        
}
