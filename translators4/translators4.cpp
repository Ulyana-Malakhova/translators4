#define _CRT_SECURE_NO_WARNINGS
#include <locale.h>
#include <stdio.h>
#include <string>
#include "defs.h"
#include "Scaner.h"

int main(int argc, char* argv[]) {
	setlocale(LC_ALL, "Rus");
	TScaner* sc;
	int type; 
	TypeLex l;
	char fileName[] = "input.txt";
	if (argc <= 1) sc = new TScaner(fileName);
	else sc = new TScaner(argv[1]); 
	do {
		type = sc->Scaner(l);
		printf("%s - тип %d \n", l, type);
	} while (type != TEnd);
	return 0;
}
