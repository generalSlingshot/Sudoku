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
#include "Oberflaeche.h"
#include "Utils.h"
#include "Datenbank.h"

/*
========================================================================
Prototypen
========================================================================
*/
void sudokuSpielablauf(int iSchwierigkeitsgrad);


char* sNutzernameAngemeldet[NAME_MAX];

Koordinate sudoku [SUDOKU_REIHE][SUDOKU_SPALTE];

/*
========================================================================
Funktion main()
========================================================================
*/
int main(void) {
	Bestenliste(1);
	/*int iRueckgabeStart = NICHT_GESETZT;
	int iRueckgabeHauptMenue = NICHT_GESETZT;
	int iSchwierigkeitsgrad = NICHT_GESETZT;
	int iRueckgabeRegister = NICHT_GESETZT;
	system("mode con: lines=500 cols=500");
	do {
		do {
			iRueckgabeStart = StartMenue();
			if (iRueckgabeStart == STARTMENUE_LOGIN) {
				iRueckgabeRegister = LoginMenue();
			}
			else if (iRueckgabeStart == STARTMENUE_REGISTER) {
				iRueckgabeRegister = RegistrierungMenue();
			}
		} while (iRueckgabeRegister != LOGIN_SUCCESS && iRueckgabeStart != STARTMENUE_END);
		if (iRueckgabeStart != STARTMENUE_END) {
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
					iSchwierigkeitsgrad = SchwierigkeitMenue();
					Bestenliste(iSchwierigkeitsgrad);
				}
			} while (iRueckgabeHauptMenue != HAUPTMENUE_LOGOUT);
		}
	} while (iRueckgabeStart != STARTMENUE_END);*/
	return 0;
}

void sudokuSpielablauf(int iSchwierigkeitsgrad) {
	int iRueckgabeSudoku = NICHT_GESETZT;
	int iDauerSekunden;
	clock_t start;
	clock_t end;
	Bestenlisteneintrag eintrag;
	start = clock();
	end = clock();

	// Wenn gewonnen, Bestenlistendaten abspeichern
	if (iRueckgabeSudoku == SUDOKU_WIN) {
		iDauerSekunden = (end - start) / CLOCKS_PER_SEC;
		// Werte des Bestenlisteneintrags setzen
		eintrag.iSchwierigkeit = iSchwierigkeitsgrad;
		strcpy(eintrag.sNutzername, sNutzernameAngemeldet);
		strcpy(eintrag.sSpielzeit, toZeitstring(iDauerSekunden));

		// Bestenlisteneintrag abspeichern
		if (speicherBestenlistendaten(&eintrag) == DATENBANK_FEHLER) {
			printf("DATENBANK FEHLER");
		}
	}
	// Wenn Spiel verloren
	else  if (iRueckgabeSudoku == SUDOKU_LOSE) {
		// TODO
	}
}





