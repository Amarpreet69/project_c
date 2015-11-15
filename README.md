Title of Project : "C Messenger"
Name : Amarpreet Singh Arora
MIS ID : 141508002


Overview :
"C Messenger". Communication between two devices/machines, one can send messages/data to another machine in a network.
C messenger basically contains messaging/texting between two communicating devices over network. This also includes sending of files between devices. It uses TCP/IP protocol for sending/recieving data. It also makes a log of messages for acknowlegdment.

Usability :
For running this, directory contained of two files that is for two devices, both the file should be at running state.
One file will act as server and another as client. For running server, you will be prompted to enter HostAddress (Address of pc) and port no (as of your choice) of respective pc. For running, client you will be prompted to enter HostAddress (Address of Server) and port no (port no of server).

STEPS :
1. type "make" command in terminal. (make sure that you are in directory that contain its Makefile and all project files.)
2. It will create "project_server.o" and "project_client.o".
3. Open these two executables in two terminals or pc.
4. First run "./project_server" command and enter HostAddress (on which your server is) and Portno (between 1000-65536).
5. Then run "./project_client" command and enter HostAddress (of server) and port(of server).
6. Thus you will see "Status : Online".
7. For sending files enter "SENDFILE", from either side you want to send file.
8. For exiting enter "CLOSE". It will terminate both programs.
9. You will see "Status : Offline".

NOTE : You should send the message only when you are prompted with "you :". This means that one is at sending state while other is in recieving state. For communication both computers should be on same network.

"Communication Matters."
