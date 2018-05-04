#include "Sudoku.h"
#include "Utils.h"

char* toZeitstring(int iSekundenGesamt) {
	char sZeit[ZEIT_MAX];
	int iStunden = 0;
	int iMinuten = 0;
	// Stunden
	while (iStunden * MINUTEN_PRO_STUNDE * SEKUNDEN_PRO_MINUTE <= iSekundenGesamt) {
		iStunden++;
	}
	iSekundenGesamt = iSekundenGesamt - iStunden * MINUTEN_PRO_STUNDE * SEKUNDEN_PRO_MINUTE;

	// Minuten
	while (iMinuten * SEKUNDEN_PRO_MINUTE <= iSekundenGesamt) {
		iMinuten++;
	}
	iSekundenGesamt = iSekundenGesamt - iMinuten * SEKUNDEN_PRO_MINUTE;

	
	sprintf(sZeit, "%s:%s:%s", iStunden, iMinuten, iSekundenGesamt);
	return sZeit;
}

int isAngemeldet(void) {
	int bErgebnis;
	if (strcmp != 0) {
		bErgebnis = TRUE;
	}
	else {
		bErgebnis = FALSE;
	}
	return bErgebnis;
}

/*
========================================================================
Funktion Abmelden(char *Teststring)
Beschreibung:				Globalen Usernamen leeren
Uebergebene Daten:			char Array
Returnwert:					-
========================================================================
*/

void Abmelden(void) {
	strcpy(sNutzernameAngemeldet, "");;
}

/*
========================================================================
Funktion Anmelden(char *)
Beschreibung:				Globalen Usernamen leeren
Uebergebene Daten:			char Array
Returnwert:					-
========================================================================
*/

void Anmelden(char *Username) {

	strcpy(sNutzernameAngemeldet, Username);

}

char* trim(char* sZeichenkette) {
	char* sZeichenketteTrim = sZeichenkette;
	while (isspace(*sZeichenketteTrim)) {
		sZeichenketteTrim++;
	}
	char* sLetztesZeichen = sZeichenketteTrim + strlen(sZeichenketteTrim);
	while ((isspace(*sLetztesZeichen)) && (sLetztesZeichen >= sZeichenketteTrim)) {
		*sLetztesZeichen = '\0';
		sLetztesZeichen--;
	}
}

int isZiffer(char* sZeichenkette) {
	int bErgebnis = FALSE;
	sZeichenkette = trim(sZeichenkette);
	if ((strlen(sZeichenkette) == 1) && (isSudokuZiffer(sZeichenkette) == TRUE)) {
		bErgebnis = TRUE;
	}
	return bErgebnis;
}

int toKoordinate(char* sKoordinaten, Koordinate* koordinate) {
	char* ptZeichen = trim(sKoordinaten);
	int bZiffer = FALSE;
	int bBuchstabe = FALSE;
	char iZeichen;
	int bErgebnis = FALSE;

	// Es handelt sich nicht um eine gültige Koordinate, wenn die Eingabe zu lang ist
	if (strlen(ptZeichen) <= 2) {
		while (ptZeichen != '\0') {
			iZeichen = (int)*ptZeichen;
			// überprüfen ob Zeichen in a-iA-I und Koordinate setzen, falls der Fall
			if (isSudokuGrossBuchstabe(iZeichen) == TRUE) {
				bBuchstabe = TRUE;
				koordinate->iX = iZeichen - GROSS_A + 1;
			}
			if (isSudokuKleinBuchstabe(iZeichen) == TRUE) {
				bBuchstabe = TRUE;
				koordinate->iX = iZeichen - KLEIN_A + 1;
			}

			// überprüfen ob Ziffer 1 bis 9 und Koordinate setzen, falls der Fall
			if (isSudokuZiffer(iZeichen)) {
				bZiffer = TRUE;
				koordinate->iY = iZeichen - ZIFFER_EINS + 1;

			}
			ptZeichen++;
		}

		// Nur wenn sowohl Ziffer als auch Buchstabe vertreten sind, handelt es sich 
		// bei der Eingabe um eine gültige Koordinate
		if (bBuchstabe == TRUE && bZiffer == TRUE) {
			bErgebnis = TRUE;
		}
	}

	return bErgebnis;
}

int isSudokuGrossBuchstabe(int iZeichen) {
	int bErgebnis = FALSE;
	if (iZeichen >= GROSS_A && iZeichen <= GROSS_I) {
		bErgebnis = TRUE;
	}
	return bErgebnis;
}

int isSudokuKleinBuchstabe(int iZeichen) {
	int bErgebnis = FALSE;
	if (iZeichen >= KLEIN_A && iZeichen <= KLEIN_I) {
		bErgebnis = TRUE;
	}
	return bErgebnis;
}

int isSudokuZiffer(int iZeichen) {
	int bErgebnis = FALSE;
	if (iZeichen >= ZIFFER_EINS && iZeichen <= ZIFFER_NEUN) {
		bErgebnis = TRUE;
	}
	return bErgebnis;
}

/*
========================================================================
Funktion Pruef_isalnum(char *)
Beschreibung:				Pruefung der Eingabe ob das eingegebene
Ausschliesslich aus Zahlen und Buchstaben
besteht
Uebergebene Daten:			char Array
Returnwert:					1 Falls String korrekt, 0 Falls nicht
========================================================================
*/

int Pruef_isalnum(char *Teststring) {
	while (isalnum(*Teststring))
		++Teststring;
	return *Teststring == 0;
}

/*
========================================================================
Funktion Pruef_isalpha(char *)
Beschreibung:				Pruefung der Eingabe ob das eingegebene
Ausschliesslich aus Buchstaben besteht
Uebergebene Daten:			char Array
Returnwert:					1 Falls String korrekt, 0 Falls nicht
========================================================================
*/

int Pruef_isalpha(char *Teststring) {
	while (isalpha(*Teststring))
		++Teststring;
	return *Teststring == 0;
}