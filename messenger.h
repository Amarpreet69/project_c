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



