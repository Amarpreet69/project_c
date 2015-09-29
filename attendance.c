#include<stdio.h>
#include<mysql/mysql.h>
#include<string.h>

int main() {
	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
	int i, mis, dec = 1, choice;
	char *u, *p;
	char user[10], password[10], sub[10], name[30];
	char *database = "temp", *server = "localhost";
	conn = mysql_init(NULL);
	printf("username : ");
	scanf("%s", &user);
	printf("password : ");
	scanf("%s", &password);
	u = &user;
	p = &password;
   
	if (!mysql_real_connect(conn, server, u, p, database, 0, NULL, 0)) 
		finish_with_error(conn); 
	

	
	//if(mysql_query(conn,"insert into student(srno, name) values(1, 'Honey');"))
	//	finish_with_error(conn);	

	while(dec) {
		printf("1. Add Subject\n2. Show Subject List\n3. Add Student\n4. Show Student\n5. Exit\n");
		scanf("%d", &choice);
		switch(choice) {
			
			case 1 :
				printf("Enter subject : ");
				scanf("%s", &sub);
				sub = strcat(strcat("create table ",sub)," (mis int, name varchar(20);)");
				printf("%s",sub);
				if(mysql_query(conn,strcat(strcat("create table ",sub)," (mis int, name varchar(20);)")))
					finish_with_error(conn);
				printf("\ncreated\n");
				break;
			case 2:
				if (mysql_query(conn, "show tables"))
      					finish_with_error(conn);
   				res = mysql_use_result(conn);
   

   				printf("Subjects:\n");
   				while ((row = mysql_fetch_row(res)) != NULL)
      					printf("%s \n", row[0]);
				break;
			case 3:
				printf("Enter subject : ");
				scanf("%s", &sub);
				printf("Enter mis and name of student : ");
				scanf("%d%s", &mis, &name);
				if(mysql_query(conn,strcat(strcat(strcat(strcat(strcat(strcat("insert into ", sub),"(mis, name) values ("), mis),","),name),");")))
					finish_with_error(conn);
				printf("Added successfulyy\n");
				break;	
	
			
			case 4:
				printf("Enter subject : ");
				scanf("%s", &sub);
				if(mysql_query(conn,strcat("select * from ",sub)));
					finish_with_error(conn);
				res = mysql_store_result(conn);
  
				if (res == NULL) {
      					finish_with_error(conn);
 				}			

  				int num_fields = mysql_num_fields(res);

  				while ((row = mysql_fetch_row(res))) { 
      					for(i = 0; i < num_fields; i++) { 
          					printf("%s ", row[i] ? row[i] : "NULL"); 
      					} 
          			printf("\n"); 
  				}
				break;
				
			case 5:
				dec = 0;

				break;
			default :
				break;
		}	
	}


	
   mysql_free_result(res);
   mysql_close(conn);
return 0;
}

void finish_with_error(MYSQL *conn)
{
  fprintf(stderr, "%s\n", mysql_error(conn));
  mysql_close(conn);
  exit(1);        
}
