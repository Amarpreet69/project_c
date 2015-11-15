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
void current_time() {
	time_t t;
	char buffer[20];
	struct tm * timeinfo;
	time (&t);
	timeinfo = localtime(&t);
	char ti[40];
  	sprintf(buffer,"%d/%d/%d %d:%d:%d ", timeinfo->tm_year+1900, timeinfo->tm_mon+1, timeinfo->tm_mday, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
	strcpy(ti, buffer);
	strcpy(c_time, ti);
}

void error(const char *msg) {
    perror(msg);
    exit(0);
}

void strip(char *s) {
    char *p2 = s;
    while(*s != '\0') {
    	if(*s != '\n') {
    		*p2++ = *s++;
    	} else {
    		++s;
    	}
    }
    *p2 = '\0';
}

int file_size(char *f) {
	int size;
	struct stat st;
	stat(f, &st);
	size = st.st_size;
return size;
}
