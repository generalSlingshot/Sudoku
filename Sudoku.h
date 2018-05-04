
#if !defined (VAR)
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
#include <time.h>
#include "Utils.h"

/*
========================================================================
Defines
========================================================================
*/

/*
Allgemein
*/
#define TRUE 1
#define FALSE 0

#define NICHT_GESETZT -1

#define ZEIT_MAX 9

// Namen- und Passwortlänge
#define NUTZERNAME_MAX 20
#define NUTZERNAME_MIN 5
#define NAME_MAX 20
#define NAME_MIN 3
#define PASSWORT_MAX 20
#define PASSWORT_MIN 5

// Zeit
#define MINUTEN_PRO_STUNDE 60
#define SEKUNDEN_PRO_MINUTE 60

/*
	Sudokuspiel
*/
// Schwierigkeitsgrad
#define LEICHT 1
#define MITTEL 2
#define SCHWER 3


// Reihen-/Spaltenlänge
#define SUDOKU_REIHE 9
#define SUDOKU_SPALTE 9

/*
	Rückgaben
*/
// Sudoku
#define SUDOKU_WIN 1
#define SUDOKU_LOSE 0

// Hauptmenü
#define HAUPTMENUE_SPIEL 1
#define HAUPTMENUE_REGEL 2
#define HAUPTMENUE_LISTE 3
#define HAUPTMENUE_LOGOUT 4
#define HAUPTMENUE_END 0

// Startmenü
#define STARTMENUE_LOGIN 1
#define STARTMENUE_REGISTER 2
#define STARTMENUE_END 0

// Login + Register
#define LOGIN_SUCCESS 1
#define REGISTER_BACK 2

/*
	Bestenliste
*/
#define BESTENLISTE_ANZAHL 3
#define BESTENLISTE_TOPSCORE_ANZAHL 10

/*
	Datenbank
*/
// File
#define DATABASE_FILE "sudoku.sqlite3"

// Fehlerrückgabe
#define DATENBANK_FEHLER 3
#define DATENBANK_OK 2

// Rückgabe SQL ist leer
#define SQL_LEER 0

/*
	ASCII-Zeichen
*/
// Buchstaben
#define GROSS_A 65
#define GROSS_I 73
#define KLEIN_A 97
#define KLEIN_I 105

// Ziffern
#define ZIFFER_EINS 49
#define ZIFFER_NEUN 57



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

extern char* sNutzernameAngemeldet[NAME_MAX];
extern Koordinate sudoku[SUDOKU_REIHE][SUDOKU_SPALTE];

/*
========================================================================
Prototypen
========================================================================
*/
void Abmelden(void);

#endif