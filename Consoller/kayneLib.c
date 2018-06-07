/*
 * kayneLibs.c
 *
 *  Created on: May 11, 2018
 *      Author: Kayne
 *      Comment:True
 */
#include "kayneLib.h"

int inputInteger()  //fucntie voor integer input Thanks bert
{
	char text[80];
	unsigned char input = atoi(fgets(text, 80, stdin));
	return input;
}

void printfln(const char *format, ...) //functie om niet een \n te hoeven schrijven...
{
	va_list arg;

	va_start(arg, format);
	vfprintf(stdout, format, arg);
	va_end(arg);
	printf("\n");
	//return done;
}

const char* getfield(char* line, int num)
{ //funcite om een lijn van een csv te ontleden
	char* tok;

	for (tok = strtok(line, ";"); tok && *tok; tok = strtok(NULL, ";\n"))//gaat text tot delimiters langs totdat deze bij het einde is
	{
		if (!--num) //eindigd de functie en geeft de gewenste waarde terug
			return tok;
	}
	return NULL;
}
