#if  !defined (VAR) 
#define VAR

#define _CRT_SECURE_NO_DEPRECATE 1
#define _CRT_SECURE_NO_WARNINGS 1

/*
========================================================================
Include Dateien
========================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include "sqlite3.h"
#include "Oberflaeche.h"

/*
========================================================================
Defines
========================================================================
*/
#define LEICHT 1
#define MITTEL 2
#define SCHWER 3

#define SUDOKU_WIN 1
#define SUDOKU_LOSE 0

#define SUDOKU_REIHE 9
#define SUDOKU_SPALTE 9

#define HAUPTMENUE_SPIEL 1
#define HAUPTMENUE_REGEL 2
#define HAUPTMENUE_LISTE 3
#define HAUPTMENUE_LOGOUT 4
#define HAUPTMENUE_END 0

#define STARTMENUE_LOGIN 1
#define STARTMENUE_REGISTER 2
#define STARTMENUE_END 0

#define NAME_MAX 20
#define NAME_MIN 5
#define PASSWORT_MAX 20
#define PASSWORT_MIN 5

#define SQL_LEER 0

#define TRUE 1
#define FALSE 0

#define NICHT_GESETZT -1
#define ZEIT_MAX 8

#define BESTENLISTE_ANZAHL 3
#define BESTENLISTE_TOPSCORE_ANZAHL 10

#define DATABASE_FILE "sudoku.sqlite3"


/*
========================================================================
Structdefinitionen
========================================================================
*/
typedef struct Bestenlisteneintrag {
	char sNutzername[NAME_MAX];
	char sSpielzeit[ZEIT_MAX];
	int iSchwierigkeit;
} Bestenlisteneintrag;

typedef struct Nutzer {
	char sNutzername[NAME_MAX];
	char sVorname[NAME_MAX];
	char sNachname[NAME_MAX];
	char sPasswort[PASSWORT_MAX];
} Nutzer;

typedef struct UebergabeLeseBestenliste {
	struct Bestenlisteneintrag eintraege[BESTENLISTE_TOPSCORE_ANZAHL];
	int curVal;
} UebergabeLeseBestenliste;

typedef struct Koordinate {
	int iX;
	int iY;
	int bSichtbar;
	int iZiffer;
} Koordinate;

typedef struct LoginReturn {
	Nutzer benutzer;
	int iFehlercode;
} LoginReturn;

extern char sNutzernameAngemeldet[NAME_MAX];

#endif
