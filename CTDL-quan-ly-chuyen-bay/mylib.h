
#include <conio.h>

#include <stdio.h>
#include <stdlib.h>
#include <dos.h>
#include <string.h>
#include <windows.h>

#define Enter 13
//const int WHITE=15;
#define PASSWORD "abcdef"
//const int WHITE=15;

char* Pwd () ;

int CheckPwd () ;

void gotoxy(short x,short y); 

int wherex( void );

int wherey( void );
void clreol( );

void SetColor(WORD color);
void SetBGColor(WORD color);
void clrscr() ;
