Overview :
"C Messenger". Communication between two devices/machines, one can send messages/data to another machine in a network.
C messenger basically contains messaging/texting between two communicating devices over network. This also includes sending of files between devices. It uses TCP/IP protocol for sending/recieving data. It also makes a log of messages for acknowlegdment.

Usability :
For running this, directory contained of two files that is for two devices, both the file should be at running state.
One file will act as server and another as client. For running server, port number must be specify using command line and while running client hostname (generally it will be your pc name) and port number of server must be specify in command line to work. Enjoy communication.

STEPS :
1. type "make" command in terminal.
2. It will create "server.o" and "client.o".
3. Open these two executables in two terminals or pc.
4. First run "./server" command and enter port no.
5. Then run "./client" command and enter hostname(name of your pc) and port(of server).
6. Thus you will see "connected".
7. For sending files enter "SENDFILE", from either side you want to send file.
8. For exiting enter "CLOSE". It will terminate both programs.

NOTE : You should send the message only when you are prompted with "you :". This means that one is at sending state while other is in recieving state.

"Communication Matters."
