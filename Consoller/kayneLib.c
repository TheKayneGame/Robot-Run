/*
 * kayneLibs.c
 *
 *  Created on: May 11, 2018
 *      Author: Kayne
 */
#include "kayneLib.h"

int leesInteger() {
	char text[80];
	unsigned char input = atoi(fgets(text, 80, stdin));
	return input;
}

void printfln(const char *format, ...) {
	va_list arg;

	va_start(arg, format);
	vfprintf(stdout, format, arg);
	va_end(arg);
	printf("\n");
	//return done;
}

const char* getfield(char* line, int num)
{
	char* tok;

	for (tok = strtok(line, ";"); tok && *tok; tok = strtok(NULL, ";\n"))
	{
		if (!--num)
			return tok;
	}
	return NULL;
}
