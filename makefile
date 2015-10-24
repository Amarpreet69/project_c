c_messenger : 	server.c client.c messenger.c
		gcc -Wall server.c messenger.c -o server;
		gcc -Wall client.c messenger.c -o client;
