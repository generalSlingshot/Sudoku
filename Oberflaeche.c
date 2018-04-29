#include "Sudoku.h"
#include "Oberflaeche.h"
#include "Datenbank.h"

int StartMenue(void); // Chung
void RegistrierungMenue(void); // Henning
void LoginMenue(void); // Omar
int HauptMenue(void); // Sven
void Regelwerk(void); // Sven
void Bestenliste(); // Tom
Koordinate* getFeld(Koordinate** ptKoordinate, int iSpalte, int iReihe);
int SudokuSpiel(int schwierigkeitsgrad);
void printRegistrierungMenue1(void);
void printRegistrierungMenue2(void);
void printRegistrierungMenue3(void);
void RegelwerkPrint(void);
void printSchwierigkeitsAuswahl(void);
void printStartMenue(void);
void printAnmeldung1(void);
void printAnmeldung2(void);
void printSudokuReihe(int iReihe);
void printHorizontale(void);
void printSudokuZeile(int iZeile, int iReihe);
void printVertikale(void);
void printSudoku(int iSchwierigkeitsgrad);

void RegistrierungMenue(void) {
	Nutzer benutzer;
	char sEingabe[65],
		//sVorname[20],
		//sNachname[20],
		sPasswort[20],
		sPassconfirm[20];
	char cBestaetigung = 'z';
	int bFalscheingabe = FALSE;
	do {
		do {
			system("cls");
			printRegistrierungMenue1();
			if (bFalscheingabe == TRUE) {
				printf("  Falscheingabe!\n");
			}
			printf("  Ihre Eingabe: ");
			fflush(stdin);
			scanf("%s", sEingabe);
			if (strlen(sEingabe) < 6) {
				bFalscheingabe = TRUE;
			}
			else {
				bFalscheingabe = FALSE;
			}
		} while (bFalscheingabe == TRUE);
		do {
			system("cls");
			printRegistrierungMenue2();
			if (bFalscheingabe == TRUE) {
				printf("  Falscheingabe!\n");
			}
			printf("  Ihre Eingabe: ");
			fflush(stdin);
			scanf("%c", &cBestaetigung);
			if (cBestaetigung != 'y' && cBestaetigung != 'n') {
				bFalscheingabe = TRUE;
			}
			else {
				bFalscheingabe = FALSE;
			}
		} while (bFalscheingabe == TRUE);
		if (cBestaetigung == 'y') {
			do {
				do {
					system("cls");
					printRegistrierungMenue3();
					if (bFalscheingabe == TRUE) {
						printf("\n  Falscheingabe!\n");
					}
					printf("  Ihre Eingabe: ");
					fflush(stdin);
					scanf("%s", sPasswort);
					if (strlen(sPasswort) < 8 || strlen(sPasswort) > 20) {
						bFalscheingabe = TRUE;
					}
					else {
						bFalscheingabe = FALSE;
					}
				} while (bFalscheingabe == TRUE);
				printf("\nBitte wiederholen Sie Ihr Passwort.\n\n");
				printf("  Ihre Eingabe: ");
				fflush(stdin);
				scanf("%s", sPassconfirm);
				if (strcmp(sPasswort, sPassconfirm) != 0) {
					bFalscheingabe = TRUE;
				}
				else {
					bFalscheingabe = FALSE;
				}
			} while (bFalscheingabe == TRUE);
		}
		else {
		}
	} while (cBestaetigung == 'n');
	// registriereNutzer()
}

void LoginMenue(void) {
	int iArrayLength;
	int bPasskorrekt;
	int bFalscheingabe = FALSE;
	char sNutzernameEingabe[NAME_MAX];
	char cPasswortEingabe[PASSWORT_MAX];
	Nutzer* ptBenutzer;

	// Bildschirmausgabe von Loginstart
	do {
		printAnmeldung1();
		if (bFalscheingabe == TRUE) {
			printf("  Es existiert kein Nutzer mit dem Nutzernamen '%s'.\n",
				sNutzernameEingabe);
		}
		bFalscheingabe = TRUE;
		printf("  Bitte Nutzernamen eingeben: ");
		scanf("%s", &sNutzernameEingabe);

		// Datenbank lesen
		ptBenutzer = liesLogindaten(sNutzernameEingabe);

		// Schleifenexit, wenn Nutzer korrekt
		if (ptBenutzer != NULL) {
			bFalscheingabe = FALSE;
		}
	} while (bFalscheingabe == TRUE);

	bFalscheingabe = FALSE;

	// Bildschirmausgabe vom 2. Loginbildschirm
	do {
		printAnmeldung2();

		if (bFalscheingabe == TRUE) {
			printf("  Ihre Passw�rter stimmen nicht beide mit dem registrierten Passwort �berein!\n");
		}
		bFalscheingabe = FALSE;

		// 2. Passworteingabe vergleichen
		printf("  Bitte Passwort eingeben: ");
		scanf("%s", cPasswortEingabe);
		bPasskorrekt = strcmp(cPasswortEingabe, ptBenutzer->sPasswort);
		if (bPasskorrekt == TRUE) {
			bFalscheingabe = FALSE;
		}
		else {
			bFalscheingabe = TRUE;
		}
	} while (bPasskorrekt == TRUE);

	// Angemeldeten Nutzer setzen
	strcpy(&sNutzernameAngemeldet, sNutzernameEingabe);
}

void printAnmeldung2(void) {
	system("cls");
	printf("\n\n  A N M E L D U N G\n");
	printf("  = = = = = = = = =\n\n");
	printf("  Bitte geben Sie den Nutzernamen und"
		" das Passwort Ihres registrierten Kontos ein.\n\n");
}

void printAnmeldung1(void) {
	system("cls");
	printf("\n\n  A N M E L D U N G\n");
	printf("  = = = = = = = = =\n\n");
	printf("  Bitte geben Sie den Nutzernamen und"
		" das Passwort Ihres registrierten Kontos ein.\n\n");
} //TODO

void Regelwerk(void) {
	char bFalscheingabe = FALSE;
	char cUserEingabe;

	do {
		system("cls");
		RegelwerkPrint();

		// Falscheingabenpruefung
		if (bFalscheingabe == TRUE) {
			printf("  Bitte 'x' eingeben.\n");
		}
		printf("  Ihre Eingabe:  ");

		// Eingabe
		fflush(stdin);
		scanf("%c", &cUserEingabe);

		// Switch
		switch (cUserEingabe) {

		case 'x': bFalscheingabe = FALSE;
			break;
		default: bFalscheingabe = TRUE;
		}
	} while (bFalscheingabe == TRUE);
}
void RegelwerkPrint(void) {

	printf("\n\n  R E G E L W E R K\n");
	printf("  = = = = = = = = =\n\n");
	printf("  1. Jede Ziffer von 1 bis 9 darf nur einmal pro Zeile"
		", Spalte und 3x3-Block vorhanden sein.\n");
	printf("  2. Jeder 3x3-Block ist dick umrandet\n");
	printf("  3. Das Spiel ist gewonnen sobald alle Felder gefuellt"
		" sind. Es gibt nur eine Ergebnis\n");
	printf("  4. Die Hilfsfunktion zeigt moegliche Ziffern fuer alle"
		" ungefuellten Felder an.\n");
	printf("  5. Sobald kein Feld mehr richtig gefuellt werden kann"
		" verlieren Sie.\n");
	printf("  6. Schnelligkeit zahlt sich aus. Stellen Sie eine der"
		" zehn besten Zeiten fuer Ihre ausgewaehlte Schwierigkeitsstufe"
		" auf, erzielen Sie einen Platz auf der Bestenliste.\n\n");
	printf("  Geben Sie 'x' ein um den Dialog zu beenden.\n\n");

}

void Hauptmenueprint(void) {
	char USERNAME[] = "User";
	system("cls");
	// Ueberschrift
	printf("\n\n  H A U P T M E N U E\n");
	printf("  - - - - - - - - - -\n\n");

	// Usergruss
	printf("  Hallo, %s!\n", &USERNAME);

	// Userhinweis
	printf("  Geben Sie bitte zum Ausfuehren einer Aktion eins der"
		" eingeblendeten Zeichen ein.\n\n");

	// Auswahl im Hauptmenue
	printf("  1: Spiel starten\n"
		"  2: Regeln\n"
		"  3: Bestenliste\n"
		"  4: Abmelden\n"
		"  x: Beenden\n\n");

}
int HauptMenue(void) {

	char cUserEingabe;
	int bFalscheingabe = FALSE;
	int iReturnValue;

	do {
		Hauptmenueprint();

		// Falscheingabenpruefung
		if (bFalscheingabe == TRUE) {
			printf("  Ihre Angabe %c war leider falsch,"
				" bitte versuchen sie es erneut!\n", cUserEingabe);
		}
		printf("  Ihre Eingabe:  ");

		// Eingabe
		fflush(stdin);
		scanf("%c", &cUserEingabe);

		// Switch
		switch (cUserEingabe) {

		case '1': 
			iReturnValue = HAUPTMENUE_LISTE;
			bFalscheingabe = FALSE;
			break;

		case '2':
			iReturnValue = HAUPTMENUE_REGEL;

			system("pause"); bFalscheingabe = FALSE;
			break;

		case '3':
			iReturnValue = HAUPTMENUE_LISTE;
			bFalscheingabe = FALSE;
			break;

		case '4': 
			iReturnValue = HAUPTMENUE_LOGOUT;
			bFalscheingabe = FALSE;
			break;

		case 'x':
			iReturnValue = HAUPTMENUE_END;
			bFalscheingabe = FALSE;
			break;
		default: bFalscheingabe = TRUE;
		}
	} while (bFalscheingabe == TRUE);
	return iReturnValue;
}

int StartMenue() {
	char cAuswahl;
	int bFalscheingabe = FALSE;

	do {
		system("cls");
		printStartMenue();
		if (bFalscheingabe == TRUE) {
			printf("\n  Falschangabe, ihre Eingabe war: %c", cAuswahl);
		}

		printf("\n  Ihre Eingabe: ");
		fflush(stdin);
		scanf("%c", &cAuswahl);

		switch (cAuswahl) {
		case '1':
		case '2':
		case 'x': bFalscheingabe = FALSE;
			break;
		default:bFalscheingabe = TRUE;
		}
	} while (bFalscheingabe == TRUE);

	if (cAuswahl == '1') {
		return STARTMENUE_LOGIN;
	}
	else if (cAuswahl == '2') {
		return STARTMENUE_REGISTER;
	}
	else {
		return STARTMENUE_END;
	}
}

void printStartMenue(void) {
	printf("\n\n");
	printf("  S U D O K U S T A R T\n");
	printf("  = = = = = = = = = = =\n\n");

	printf("  Geben sie zum Ausfuehren einer Aktion eins der angegebenen Zeichen ein.\n");
	printf("  1: In einem bereits existierenden Nutzerkonto einloggen.\n");
	printf("  2: Einen neuen Benutzer registrieren.\n");
	printf("  x: Das Programm beenden.\n");
}

int SchwierigkeitMenue(void) {
	char cAuswahl;
	int bFalscheingabe = FALSE;

	do {
		system("cls");
		printSchwierigkeitsAuswahl();
		if (bFalscheingabe == TRUE) {
			printf("\n  Falschangabe, ihre Eingabe war: %c", cAuswahl);
		}

		printf("\n  Ihre Eingabe: ");
		fflush(stdin);
		scanf("%c", &cAuswahl);

		switch (cAuswahl) {
		case '1':
		case '2':
		case '3': bFalscheingabe = FALSE;
			break;
		default:bFalscheingabe = TRUE;

		}
	} while (bFalscheingabe == TRUE);

	if (cAuswahl == '1') {
		return LEICHT;
	}
	else if (cAuswahl == '2') {
		return MITTEL;
	}
	else if (cAuswahl == '3') {
		return SCHWER;
	}
	else return NICHT_GESETZT;
}

void printSchwierigkeitsAuswahl(void) {
	printf("\n\n");
	printf("  S C H W I E R I G K E I T S A U S W A H L\n");
	printf("  = = = = = = = = = = = = = = = = = = = = =\n\n");

	printf("  Bitte waehlen Sie ein Schwierigkeitsgrad aus.\n");
	printf("  1: Leicht\n");
	printf("  2: Mittel\n");
	printf("  3: Schwer\n");
}

void printRegistrierungMenue1(void) {
	printf("  R E G I S T R I E R U N G\n");
	printf("  = = = = = = = = = = = = =\n\n");
	printf("  Bitte geben Sie in dem unten eingeblendeten Format Ihren "
		"Nutzernamen, Nachnamen und Vornamen ein.\n");
	printf("  Beachten Sie bitte, dass der Nutzername eine Laenge von 5 bis 20"
		" Zeichen aufweisen muss. Sonderzeichen werden nicht akzeptiert.\n\n");
	printf("  FORMAT\n");
	printf("  Nutzername Nachname Vorname (mit Leerzeichen getrennt)\n\n");
}
void printRegistrierungMenue2(void) {
	printf("  R E G I S T R I E R U N G\n");
	printf("  = = = = = = = = = = = = =\n\n");
	printf("  Ueberpruefen Sie bitte die folgenden Daten.\n\n");
	printf("  Nutzername: Testnutzer0815\n"); //Nutzername
	printf("  Nachname: Mustermann\n"); //Nachname
	printf("  Vorname: Max\n\n"); //Vorname
	printf("  Bestaetigen Sie diese Daten? (y/n)");
}
void printRegistrierungMenue3(void) {
	printf("  R E G I S T R I E R U N G\n");
	printf("  = = = = = = = = = = = = =\n\n");
	printf("  Nutzername: Testnutzer0815\n"); //Nutzername
	printf("  Nachname: Mustermann\n"); //Nachname
	printf("  Vorname: Max\n\n"); //Vorname
	printf("  Bitte geben Sie Ihr zukuenftiges Kontopasswort ein.\n");
	printf("  Beachten Sie, dass das Passwort eine Laenge von 8 bis 20 Zeichen aufweisen muss.\n\n");
}

void Bestenliste() {
	/*liesBestenlisteneintraege(SCHWER);*/

}
void initSudoku(void) {
	liesSudoku(1);
	printSudoku(LEICHT);
}

int SudokuSpiel(int iSchwierigkeitsgrad) {
	int bEnde = FALSE;
	Koordinate* koordinateEingabe;
	while (bEnde == FALSE) {
		/*eingabeSudoku(koordinateEingabe, iSchwierigkeitsgrad);*/
		sudoku[koordinateEingabe->iX];
	}
}

// x = Reihe; y = Spalte
void eingabeSudoku(Koordinate* nutzereingabe, int iSchwierigkeitsgrad) {
	char* sKoordinaten;
	int bFalscheingabe = FALSE;
	while (bFalscheingabe == FALSE) {
		printSudoku(iSchwierigkeitsgrad);
		if (bFalscheingabe == TRUE) {
			printf("  Sie haben eine ung�ltige Koordinate eingegeben.\n");
			printf("  Bitte geben Sie eine der im Spielfeld dargestellten Koordinaten ein.\n\n");
		}
		// Falscheingabe resetten
		bFalscheingabe = FALSE;
		// Normale Eingabe
		printf("Ihre Auswahl: ");
		fflush(stdin);
		scanf("%s", &sKoordinaten);
		if (isKoordinate(sKoordinaten) == FALSE) {

		}
	}
}

int isKoordinate(char* sKoordinaten) {
	char* ptZeichen = sKoordinaten;
	while (ptZeichen != '\0') {
		if (*ptZeichen ) //TODO
		ptZeichen++;
	}
}


void printSudoku(int iSchwierigkeitsgrad) {
	char* sSchwierigkeitsgrad = "FEHLER";
	system("cls");
	printf("\n");
	printf("  S U D O K U\n");
	printf("  = = = = = =\n\n");
	switch (iSchwierigkeitsgrad ) {
	case LEICHT:
		sSchwierigkeitsgrad = "Leicht"; 
		break;
	case MITTEL:
		sSchwierigkeitsgrad = "Mittel";
		break;
	case SCHWER:
		sSchwierigkeitsgrad = "Schwer";
		break;
	}
	printf("  Schwierigkeit: %s", sSchwierigkeitsgrad);
	
	printf("\n");
	// Formatierungsausgaben
	printf("\n");
	printf("\n");
	printf("       "); 
	printf("  A  "); printf(" "); 
	printf("  B  "); printf(" "); 
	printf("  C  "); printf("   "); 
	printf("  D  "); printf(" "); 
	printf("  E  "); printf(" "); 
	printf("  F  "); printf("   ");
	printf("  G  "); printf(" "); 
	printf("  H  "); printf(" "); 
	printf("  I  "); printf("\n");
	for (int i = 1; i <= 2; i++) {
		printf("    ");
		printf("\xC5\xC4");
		printf("\xC5\xC4\xC4\xC4\xC4\xC4");
		printf("\xC5\xC4\xC4\xC4\xC4\xC4");
		printf("\xC5\xC4\xC4\xC4\xC4\xC4");
		printf("\xC5\xC4");
		printf("\xC5\xC4\xC4\xC4\xC4\xC4");
		printf("\xC5\xC4\xC4\xC4\xC4\xC4");
		printf("\xC5\xC4\xC4\xC4\xC4\xC4");
		printf("\xC5\xC4");
		printf("\xC5\xC4\xC4\xC4\xC4\xC4");
		printf("\xC5\xC4\xC4\xC4\xC4\xC4");
		printf("\xC5\xC4\xC4\xC4\xC4\xC4");
		printf("\xC5\xC4\xC5\n");
	}

	for (int iReihe = 1; iReihe <= SUDOKU_REIHE; iReihe++) {
		printSudokuReihe(iReihe);
	}

	printf("\n");
	printf("  Die Koordinate 'y' �ffnet das Regelwerk.\n");
	printf("  Sie koennen mit der Koordinate 'x' die Hilfsfunktion aufrufen.\n\n");

}

void printSudokuReihe(int iReihe) {
	for (int iZeile = 1; iZeile <= 3; iZeile++) {

		// Formatierung: Zeilenanfang
		// Wenn Zeile 1 oder 3 im Feld -> leere Formatierung
		if (iZeile == 1 || iZeile == 3) {
			printf("    ");
		}
		// Sonst Reihennummer andrucken
		else {
			printf("  %i ", iReihe);
		}
		// Restliche Zeile printen
		printSudokuZeile(iZeile, iReihe);
	}
	// Formatierung: doppelte Horizontale in 3x3 Block
	if (((iReihe -2) % 3) == 1) {
		printHorizontale();
	}
	printHorizontale();
}
void printHorizontale(void) {
	printf("    ");
	for (int iSpalte = 1; iSpalte <= SUDOKU_SPALTE; iSpalte++) {
		if (iSpalte % 3 == 1) {
			printf("\xC5\xC4");
		}
		printf("\xC5\xC4\xC4\xC4\xC4\xC4");
	}
	printf("\xC5\xC4\xC5");
	printf("\n");
}

void printSudokuZeile(int iZeile, int iReihe) {
	// Alle Spalten durchlaufen
	for (int iSpalte = 1; iSpalte <= SUDOKU_SPALTE; iSpalte++) {

		// Formatierung: doppelte Vertikale in 3x3 Block
		if (iSpalte % 3 == 1) {
			printVertikale();
			printf(" ");
		}
		printVertikale();

		// Wenn es sich um die erste oder letzte Zeile handelt, wird 
		// die Ziffer des Feldes nicht angedruckt
 		if ((sudoku[iReihe - 1][iSpalte-1].bSichtbar == FALSE) 
				|| (iZeile == 1) 
				|| (iZeile == 3)) {
			printf("     ");
		}
		// Nur wenn 2. Zeile und Koordinate sichtbar die Ziffer andrucken
		else if ((iZeile == 2)) {
			printf("  %i  ", sudoku[iReihe - 1][iSpalte - 1].iZiffer);
		}

	}
	// Endzeichen, da in Schleife immer Vorzeichen gesetzt wird
	printf("\xB3\ \xB3");
	// n�chste Zeile
	printf("\n");
}

void printVertikale(void) {
	printf("\xB3");
}
