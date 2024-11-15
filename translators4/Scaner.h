#pragma once
#ifndef __SCANER
#define __SCANER
#include "defs.h"
class TScaner {
private:
	TypeMod t;
	int uk; // указатель текущей позиции в исходном тексте
public:
	void PutUK(int i);
	int GetUK(void);
	void PrintError(const char*, const char*);
	int Scaner(TypeLex l);
	void GetData(char*);
	TScaner( char*);
	~TScaner() {}
};
#endif