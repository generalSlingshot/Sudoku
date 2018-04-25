/*
========================================================================
Autor       : Team 3
Firma       : HHBKSudokuSoft AG
Dateiname   : Sudoku.c
Datum       : 23.04.2018
Beschreibung: Die Hauptdatei des Sudokuprogramms.
Compiler    : Visual Studio 2012 Compiler
Version     : 1.0
Programmschnittstelle: int main(void)
Das Programm gibt den Wert 0 oder 1 zurueck.
Das Programm erwartet beim Aufruf keine Argumente
========================================================================
*/


#include "Sudoku.h"

/*
========================================================================
Prototypen
========================================================================
*/
void Abmelden(void);
int** InitSudoku(int schwierigkeitsgrad);
void fullscreen(void);


char sNutzernameAngemeldet[NAME_MAX] = "";

/*
========================================================================
Funktion main()
========================================================================
*/
int main(void) {
	fullscreen();
	/*int iRueckgabeStart = -1;
	int iRueckgabeHauptMenue = -1;
	int iSchwierigkeitsgrad = -1;
	do {
	iRueckgabeStart = StartMenue();
	if (iRueckgabeStart == STARTMENUE_LOGIN) {
	LoginMenue();
	}
	else if (iRueckgabeStart == STARTMENUE_REGISTER) {
	RegistrierungMenue();
	}
	else if (iRueckgabeStart != STARTMENUE_END) {
	do {
	iRueckgabeHauptMenue = HauptMenue();
	if (iRueckgabeHauptMenue == HAUPTMENUE_SPIEL) {
	iSchwierigkeitsgrad = SchwierigkeitMenue();
	SudokuSpiel(iSchwierigkeitsgrad);
	}
	else if (iRueckgabeHauptMenue == HAUPTMENUE_REGEL) {
	Regelwerk();
	}
	else if (iRueckgabeHauptMenue == HAUPTMENUE_LISTE) {
	Bestenliste();
	}
	} while (iRueckgabeHauptMenue != HAUPTMENUE_LOGOUT);
	}
	} while (iRueckgabeStart != STARTMENUE_END);*/
	LoginMenue();
	return 0;
}

void Abmelden() {
}

void fullscreen()
{
	keybd_event(VK_MENU, 0x38, 0, 0);
	keybd_event(VK_RETURN, 0x1c, 0, 0);
	keybd_event(VK_RETURN, 0x1c, KEYEVENTF_KEYUP, 0);
	keybd_event(VK_MENU, 0x38, KEYEVENTF_KEYUP, 0);
}




