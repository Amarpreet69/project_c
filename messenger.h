#ifndef unix
#define WIN32
#include <windows.h>
#include <winsock.h>

#else
#define closesocket close
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/stat.h>
#include <time.h>

#endif
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#define PROTOPORT 5193 /* default protocol port number */

extern int errno;

char c_time[256];



