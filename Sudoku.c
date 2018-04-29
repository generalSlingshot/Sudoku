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


char sNutzernameAngemeldet[NAME_MAX] = "";

Koordinate sudoku [SUDOKU_REIHE][SUDOKU_SPALTE];

/*
========================================================================
Funktion main()
========================================================================
*/
int main(void) {
	/*system("mode con: lines=500 cols=500");
	int iRueckgabeStart = NICHT_GESETZT;
	int iRueckgabeHauptMenue = NICHT_GESETZT;
	int iSchwierigkeitsgrad = NICHT_GESETZT;
	do {
		iRueckgabeStart = StartMenue();
		if (iRueckgabeStart == STARTMENUE_LOGIN) {
			LoginMenue();
		}
		else if (iRueckgabeStart == STARTMENUE_REGISTER) {
			RegistrierungMenue();
		}
		if (iRueckgabeStart != STARTMENUE_END) {
			do {
				iRueckgabeHauptMenue = HauptMenue();
				if (iRueckgabeHauptMenue == HAUPTMENUE_SPIEL) {
					iSchwierigkeitsgrad = SchwierigkeitMenue();
					sudokuSpielablauf(iSchwierigkeitsgrad);
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
	initSudoku();
	system("pause");
	return 0;
}

void sudokuSpielablauf(int iSchwierigkeitsgrad) {
	int iRueckgabeSudoku = NICHT_GESETZT;
	clock_t start;
	clock_t end;
	start = clock();
	iRueckgabeSudoku = SudokuSpiel(iSchwierigkeitsgrad);
	while (iRueckgabeSudoku == SUDOKU_NONE) {
		iRueckgabeSudoku = SudokuSpiel(iSchwierigkeitsgrad);
	}
	end = clock();
	if (iRueckgabeSudoku == SUDOKU_WIN) {
		// TODO
	}
	else  if (iRueckgabeSudoku == SUDOKU_LOSE) {
		// TODO
	}
}

void Abmelden() {
}





