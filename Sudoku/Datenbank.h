/*
   ========================================================================
   Include Dateien
   ========================================================================
*/

#include "Sudoku.h"

/*
   ========================================================================
   Defines
   ========================================================================
*/
#define DATENBANK_FEHLER 3

Nutzer* liesLogindaten(char* sNutzername);
int registriereNutzer(Nutzer* ptBenutzer);
Bestenlisteneintrag* liesBestenlistendaten(int iSchwierigkeitsgrad);
