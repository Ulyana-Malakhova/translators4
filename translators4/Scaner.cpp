#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include "defs.h"
#include "Scaner.h"


TScaner::TScaner(char* FileName) {
	GetData(FileName);
	PutUK(0);
}

TypeLex Keyword[MAX_KEYW] = { "while", "int", "short",
"long", "main",
"struct", "const"
};

int IndexKeyword[MAX_KEYW] = { TWhile, TInt, TShort,
TLong, TMain,TStruct, TConst
};

void TScaner::PutUK(int i) { uk = i; } //восстановить указатель
int TScaner::GetUK(void) { return uk; } // запомнить указатель

void TScaner::PrintError(const char* err,const char* a) {
	if (a[0] == '\0')
		printf("Ошибка : %s %s\n", err, a);
	else
		printf("Ошибка : %s. Неверный символ %s\n", err, a);
	exit(0);
}

int TScaner::Scaner(TypeLex l) {
	int i; 
	for (i = 0; i < MAX_LEX; i++) l[i] = 0; 
	i = 0;
start: // все игнорируемые элементы:
	while ((t[uk] == ' ') || (t[uk] == '\n') || (t[uk] == '\t')) uk++;
	if ((t[uk] == '/') && (t[uk + 1] == '/'))
	{ 
		uk = uk + 2;
		while (t[uk] != '\n') uk++;
		goto start;
	}
	if (t[uk] == '\0') { l[0] = '#'; return TEnd; }
	if (((t[uk] == '0')&&(t[uk+1] == 'x'))||((t[uk] == '0') && (t[uk + 1] == 'X')))
	{
		l[i++] = t[uk++];
		l[i++] = t[uk++];
		int el1=0;
		int el2 = 0;
		while (((t[uk] <= '9') && (t[uk] >= '0')) || ((t[uk] <= 'f') && (t[uk] >= 'a')) || ((t[uk] <= 'F') && (t[uk] >= 'A'))) {
			el1++;
			if (i < MAX_LEX - 1) l[i++] = t[uk++]; 
			else {
				uk++;
				el2 = 1;
			}
		}
		if (el2 == 1) {
			printf("Слишком длинная лексема, она будет обрезана до 20 символов\n");
		}
		el2 = 0;
		if (el1 == 0) {
			uk++;
			return TErr;
		}
		else {
			if ((t[uk] == 'L') || (t[uk] == 'l')) {
				l[i++] = t[uk++]; return TConsLongHex;
			}
			return TConsIntHex;
		}
	}
	else if ((t[uk] <= '9') && (t[uk] >= '0'))
	{
		l[i++] = t[uk++];
		int el2 = 0;
		while ((t[uk] <= '9') && (t[uk] >= '0'))
			if (i < MAX_LEX - 1) l[i++] = t[uk++]; 
			else {
				uk++;
				el2 = 1;
			}
		if (el2 == 1) {
			printf("Слишком длинная лексема, она будет обрезана до 20 символов\n");
		}
		el2 = 0;
		if ((t[uk] == 'L') || (t[uk] == 'l')) { l[i++] = t[uk++]; return TConsLong;
		}
		return TConsInt;
	}
	else if ((t[uk] >= 'a') && (t[uk] <= 'z') ||
		(t[uk] >= 'A') && (t[uk] <= 'Z') || (t[uk] == '_'))
	{ // начинается идентификатор
		l[i++] = t[uk++];
		int el2 = 0;
		while ((t[uk] <= '9') && (t[uk] >= '0') ||
			(t[uk] >= 'a') && (t[uk] <= 'z') ||
			(t[uk] >= 'A') && (t[uk] <= 'Z') || (t[uk] == '_'))
			if (i < MAX_LEX - 1) l[i++] = t[uk++]; 
			else {
				uk++;
				el2 = 1;
			}
		if (el2 == 1) {
			printf("Слишком длинная лексема, она будет обрезана до 20 символов\n");
		}
		el2 = 0;
		// длинный идентификатор обрезали
		int j; 
		int uk1 = uk;
		int i1 = 0;
		char l1[30];
		for (j = 0; j < MAX_KEYW; j++)			if (strcmp(l, Keyword[j]) == 0) {
				return IndexKeyword[j];
			}
		return TIdent;
	}
	else if (t[uk] == '.')
	{
		l[i++] = t[uk++];
		return TToch;
	}
	else if (t[uk] == ',')
	{
		l[i++] = t[uk++]; return TZpt;
	}
	else if (t[uk] == ';')
	{
		l[i++] = t[uk++]; return TTZpt;
	}
	else if (t[uk] == '(')
	{
		l[i++] = t[uk++]; return TLS;
	}
	else if (t[uk] == ')')
	{
		l[i++] = t[uk++]; return TPS;
	}
	else if (t[uk] == '{')
	{
	 l[i++] = t[uk++]; return TFLS;
   }
	else if (t[uk] == '}')
	{
		l[i++] = t[uk++]; return TFPS;
	}
	else if (t[uk] == '+')
	{
		l[i++] = t[uk++]; return TPlus;
	}
	else if (t[uk] == '-')
	{
		l[i++] = t[uk++];
		return TMinus;
	}
	else if (t[uk] == '/')
	{
		l[i++] = t[uk++]; return TDiv;
	}	else if (t[uk] == '*')
	{
		l[i++] = t[uk++]; return TMult;
	}
	else if (t[uk] == '<')
	{
		l[i++] = t[uk++];
		if (t[uk] == '=') { l[i++] = t[uk++]; return TLE; }
		return TLT;
	}
	else if (t[uk] == '>')
	{
		l[i++] = t[uk++];
		if (t[uk] == '=') { l[i++] = t[uk++]; return TGE; }
		else return TGT;
	}
	else if (t[uk] == '!')
	{
		l[i++] = t[uk++];
		if (t[uk] == '=') { l[i++] = t[uk++]; return TNEQ; }
		else return TNeg;
	}
	else if (t[uk] == '=')
	{
		l[i++] = t[uk++];
		if (t[uk] == '=') { l[i++] = t[uk++]; return TEQ; }
		else return TSave;
	}
	else if ((t[uk] == '|') && (t[uk + 1] == '|'))
	{
		l[i++] = t[uk++];
		l[i++] = t[uk++];
		return TLIf;
	}
	else if ((t[uk] == '&') && (t[uk + 1] == '&'))
	{
		l[i++] = t[uk++];
		l[i++] = t[uk++];
		return TLAnd;
	}
	else {
		PrintError("Неверный символ", l);
		uk++;
		return TErr;
	}
} 

void TScaner::GetData(char* FileName) {
	char* nil;
	char aa;
	FILE* in = fopen(FileName, "r");
	if (in == NULL) { PrintError("Отсутствует входной файл", ""); exit(1); }
	int i = 0;
	while (!feof(in))
	{
		fscanf(in, "%c", &aa);
		if (!feof(in)) t[i++] = aa;
		if (i >= MAX_TEXT - 1)
		{
			PrintError("Слишком большой размер исходного модуля", "");
			break;
		}
	}
	t[i] = '\0'; 
	fclose(in);
}