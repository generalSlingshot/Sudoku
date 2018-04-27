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

char sNutzernameAngemeldet[NAME_MAX] = "";

/*
========================================================================
Funktion main()
========================================================================
*/
int main(void) {
	int iRueckgabeStart = NICHT_GESETZT;
	int iRueckgabeRegister = NICHT_GESETZT;
	int iRueckgabeHauptMenue = NICHT_GESETZT;
	int iSchwierigkeitsgrad = NICHT_GESETZT;
	system("mode con: cols=500 lines=500");
	fullscreen();
	do {
		do {
			iRueckgabeStart = StartMenue();
			if (iRueckgabeStart == STARTMENUE_LOGIN) {
				iRueckgabeRegister = LoginMenue();
			}
			else if (iRueckgabeStart == STARTMENUE_REGISTER) {
				iRueckgabeRegister = RegistrierungMenue();
			}
		}while(iRueckgabeRegister != SUCCESS && iRueckgabeStart != STARTMENUE_END );
		if (iRueckgabeStart != STARTMENUE_END) {
			do {
				iRueckgabeHauptMenue = HauptMenue();
				if (iRueckgabeHauptMenue == HAUPTMENUE_SPIEL) {
					iSchwierigkeitsgrad = SchwierigkeitMenue();
					//SudokuSpiel(iSchwierigkeitsgrad);
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
	} while (iRueckgabeStart != STARTMENUE_END);
	return 0;
}

void fullscreen(void)
{
	keybd_event(VK_MENU, 0x38, 0, 0);
	keybd_event(VK_RETURN, 0x1c, 0, 0);
	keybd_event(VK_RETURN, 0x1c, KEYEVENTF_KEYUP, 0);
	keybd_event(VK_MENU, 0x38, KEYEVENTF_KEYUP, 0);
}




