#pragma once
#ifndef __DEFS
#define __DEFS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_TEXT 10000 
#define MAX_LEX 21 // ������������ ����� �������
#define MAX_KEYW 8 // ����� �������� ����
typedef char TypeLex[MAX_LEX];
typedef char TypeMod[MAX_TEXT];
// �������� �����
#define TWhile 1
#define TInt 2
#define TShort 3
#define TLong 4
#define TMain 6
#define TStruct 7
#define TConst 8
// �������������� � ���������
#define TIdent 20
#define TConsInt 30
#define TConsIntHex 31
#define TConsLong 32
#define TConsLongHex 33
// ����������� �����
#define TToch 40
#define TZpt 41
#define TTZpt 42
#define TLS 43
#define TPS 44
#define TFLS 45
#define TFPS 46
// ����� ��������
#define TLIf 50
#define TLAnd 51
#define TEQ 52
#define TNEQ 53
#define TGT 54
#define TGE 55
#define TLT 56
#define TLE 57
#define TPlus 58
#define TMinus 59
#define TMult 60
#define TDiv 61
#define TNeg 62
#define TSave 63
// ����� ��������� ������
#define TEnd 100
// ��������� ������
#define TErr 200
#endif