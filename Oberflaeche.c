#include "Sudoku.h"
#include "Oberflaeche.h"
#include "Datenbank.h"
#include "Utils.h"

int StartMenue(void);
int RegistrierungMenue(void); 
int LoginMenue(void); 
int HauptMenue(void); 
void Regelwerk(void); 
void Bestenliste(); 
int SudokuSpiel(int schwierigkeitsgrad);
void printRegisterWelcome(void);
void printRegistrierungMenueNutzername(void);
void printRegistrierungMenueNachname(void);
void printRegistrierungMenueVorname(void);
void printRegistrierungsMenueBestaetigung(
	char NutzerName, char NachName, char VorName);
void printRegistrierungsMenuePasswort(void);
void printRegistrierungsMenuePasswortPruef(void);
void printRegisterComplete(void);
void printAnmeldung1(void);
void printRegisterComplete(void);
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
void eingabeSudoku(Koordinate* nutzereingabe, int iSchwierigkeitsgrad);

/*
========================================================================
Funktion RegistrierungMenue(void)
Beschreibung:				Abspeichern von Userdaten zur Uebermittlung
							an die Datenbank
Uebergebene Daten:			-
Returnwert:					LOGIN_SUCCESS bei erfolg, REGISTER_BACK falls der
							User vorher abgebrochen hat
========================================================================
*/

int RegistrierungMenue(void) {
	// Struct fuer Userdaten
	Nutzer benutzer;
	// Variablen fuer RegistrierungMenue
	char sUsername[NUTZERNAME_MAX],
		sVorname[NAME_MAX],
		sNachname[NAME_MAX],
		sPasswort[NAME_MAX],
		sPassconfirm[PASSWORT_MAX];

	char cBestaetigung = ' ';
	char cRegisterOn = ' ';
	int bFalscheingabe = FALSE;
	int length;

	// Ausgaben fuer RegistrierungMenue	
	printRegisterWelcome();
	// Einlesen User Entscheidung 1
	fflush(stdin);
	scanf("%c", &cRegisterOn);
	// Falls cRegisterON == 'x' spring zu ende und return REGISTER_BACK
	if (cRegisterOn != 'x') {
		// Solange bei der Bestaetigung 'n' angegeben wird wiederholen
		do {
			// Solange die Eingabe nicht korrekt ist wiederholen
			do {
				printRegistrierungMenueNutzername();
				fflush(stdin);
				scanf("%s", &sUsername);
				length = strlen(sUsername);
			} while ((length < NUTZERNAME_MIN || length > NUTZERNAME_MAX) ||
				Pruef_isalnum(sUsername) == FALSE);
			// length wieder null setzen
			length = 0;
			// Solange die Eingabe nicht korrekt ist wiederholen
			do {
				printRegistrierungMenueNachname();
				fflush(stdin);
				scanf("%s", &sNachname);
				length = strlen(sNachname);
			} while ((length < NAME_MIN || length > NAME_MAX) ||
				Pruef_isalpha(sNachname) == FALSE);
			// length wieder null setzen
			length = 0;
			// Solange die Eingabe nicht korrekt ist wiederholen
			do {
				printRegistrierungMenueVorname();
				fflush(stdin);
				scanf("%s", &sVorname);
				length = strlen(sVorname);
			} while ((length < 5 || length > 20) ||
				Pruef_isalpha(sVorname) == FALSE);
			do {
				printRegistrierungsMenueBestaetigung
					(sUsername, sNachname, sVorname);
				fflush(stdin);
				scanf("%c", &cBestaetigung);
			} while (cBestaetigung != 'y' && cBestaetigung != 'n');
		} while (cBestaetigung == 'n');
		// length wieder null setzen
		length = 0;
		// Solange die Eingabe nicht korrekt ist wiederholen
		do {
			printRegistrierungsMenuePasswort();
			fflush(stdin);
			scanf("%s", &sPasswort);
			length = strlen(sPasswort);
		} while (length < PASSWORT_MIN || length > PASSWORT_MAX);
		// Solange die Passwoerter nicht uebereinstimmen wiederholen
		do {
			printRegistrierungsMenuePasswortPruef();
			fflush(stdin);
			scanf("%s", &sPassconfirm);
		} while (strcmp(sPasswort, sPassconfirm) != 0);

		// Ausgabe der printRegisterComplete();
		printRegisterComplete();

		// Befuellen des Structs Nutzer
		strcpy(benutzer.sNutzername, sUsername);
		strcpy(benutzer.sNachname, sNachname);
		strcpy(benutzer.sVorname, sVorname);
		strcpy(benutzer.sPasswort, sPasswort);

		// Start registriereNutzer(Struct benutzer)
		registriereNutzer(&benutzer);

		// Start Anmelden(char sUsername)
		Anmelden(sUsername);

		return LOGIN_SUCCESS;
	}
	return REGISTER_BACK;
}


/*
========================================================================
Funktion LoginMenue(void)
Beschreibung:				falls der User angemeldet werden konnte
Uebergebene Daten:			-
Returnwert:					LOGIN_SUCCESS
========================================================================
*/
int LoginMenue(void) {

	// Variablen für das Loginmenue
	int iArrayLength;
	int bPasskorrekt;
	int bFalscheingabe = FALSE;
	char sNutzernameEingabe[NAME_MAX];
	char cPasswortEingabe[PASSWORT_MAX];
	Nutzer* ptBenutzer;

	// Bildschirmausgabe von Loginstart
	do {
		printAnmeldung1();
		// Falls etwas falsches eingegeben wurde Fehler ausgeben
		if (bFalscheingabe == TRUE) {
			// Ausgabe an den User dass, das kein Profil mit dem 
			// Namen vorhanden ist
			printf("  Es existiert kein Nutzer mit dem Nutzernamen '%s'.\n",
				sNutzernameEingabe);
		}
		bFalscheingabe = TRUE;
		// Nutzernamen einlesen
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
		printAnmeldung1();
		// Falls etwas Falsches eingegeben wurde Fehler ausgeben gesetzt
		if (bFalscheingabe == TRUE) {
			printf("  Ihre Passwörter stimmen nicht beide mit dem "
				" registrierten Passwort überein!\n");
		}
		bFalscheingabe = FALSE;

		// 2. Passworteingabe vergleichen
		printf("  Bitte Passwort eingeben: ");
		scanf("%s", cPasswortEingabe);
		bPasskorrekt = strcmp(cPasswortEingabe, ptBenutzer->sPasswort);
		// Falls Passwörter gleich
		if (bPasskorrekt == TRUE) {
			// bFalscheingabe FALSE setzten zum Schleifenabbruch
			bFalscheingabe = FALSE;
		}
		else {
			// bFalscheingabe TRUE setzten zum Wiederholen der Schleife
			bFalscheingabe = TRUE;
		}
	} while (bPasskorrekt == TRUE);

	// Angemeldeten Nutzer setzen
	Anmelden(sNutzernameEingabe);
	// War alle in Ordnung SUCCESS return
	return LOGIN_SUCCESS;
}

void printAnmeldung2(void) {
	system("cls");
	printf("\n\n  A N M E L D U N G\n");
	printf("  = = = = = = = = =\n\n");
	printf("  Bitte geben Sie den Nutzernamen und"
		" das Passwort Ihres registrierten Kontos ein.\n\n");
}

/*
========================================================================
Funktion printAnmeldung1(void)
Beschreibung:				Ausgaben des Anmelden Menues
Uebergebene Daten:			-
Returnwert:					-
========================================================================
*/

void printAnmeldung1(void) {
	// Screen clear
	system("cls");
	// Ausgabe fuer das Anmelden Menue
	printf("\n\n  A N M E L D U N G\n");
	printf("  = = = = = = = = =\n\n");
	printf("  Bitte geben Sie den Nutzernamen und"
		" das Passwort Ihres registrierten Kontos ein.\n\n");
}

/*
========================================================================
Funktion Regelwerk(void)
Beschreibung:				Gibt das Regelwerk aus und Prueft ob der
							User 'x' zum zurueckkehren eingegeben hat.
Uebergebene Daten:			-
Returnwert:					-
========================================================================
*/

void Regelwerk(void) {
	// Variablen fuer das Regelwerk-Menue
	char bFalscheingabe = FALSE;
	char cUserEingabe;

	do {
		// Screen clear
		system("cls");
		// Ausgabe fuer das Regelwerk-Menue
		RegelwerkPrint();

		// Falscheingabenpruefung
		if (bFalscheingabe == TRUE) {
			printf("  Bitte 'x' eingeben.\n");
		}
		printf("  Ihre Eingabe:  ");

		// Eingabe
		fflush(stdin);
		scanf("%c", &cUserEingabe);

		// Switch ( x -> Menue zurueck / alles andere im Menue bleiben )
		switch (cUserEingabe) {

		case 'x': bFalscheingabe = FALSE;
			break;
		default: bFalscheingabe = TRUE;
		}
	} while (bFalscheingabe == TRUE);
}

/*
========================================================================
Funktion RegelwerkPrint(void)
Beschreibung:				Die Ausgaben fuer das Regelwerk Menue
Uebergebene Daten:			-
Returnwert:					-
========================================================================
*/

void RegelwerkPrint(void) {
	// Ausgaben fuer das Regelwerk-Menue
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
		" auf,\n  erzielen Sie einen Platz auf der Bestenliste.\n\n");
	printf("  Geben Sie 'x' ein um den Dialog zu beenden.\n\n");

}

/*
========================================================================
Funktion Hauptmenueprint(void)
Beschreibung:				Ausgaben des Hauptmenues
Uebergebene Daten:			-
Returnwert:					-
========================================================================
*/

void Hauptmenueprint(void) {
	// Screen clear
	system("cls");
	// Ausgaben fuer das Hauptmenue
	printf("\n\n  H A U P T M E N U E\n");
	printf("  = = = = = = = = = =\n\n");

	// Usergruss an Global gesetzten User
	printf("  Hallo, %s!\n", sNutzernameAngemeldet);

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


/*
========================================================================
Funktion Hauptmenue(void)
Beschreibung:				Regelt die verschiedenen Eingabemöglich-
							keiten im Hauptmenue und dessen Unter-
							funktionen
Uebergebene Daten:			-
Returnwert:					returnvalue
========================================================================
*/

int HauptMenue(void) {

	// Variablen fuer das Hauptmenue
	char cUserEingabe;
	char cUserReset[20] = "";
	int bFalscheingabe = FALSE;
	int iReturnValue;

	// Schleife solange eine falsche Option gewaehlt wurde
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

		/* Switch mit den Optionen:
		1 -> Hauptmenue Spielstarten
		2 -> Hauptmenue Regeln
		3 -> Hauptmenue Bestenliste
		4 -> Hauptmenue Abmelden
		x -> Programm beenden
		*/
		switch (cUserEingabe) {

		case '1':
			iReturnValue = HAUPTMENUE_LISTE;
			bFalscheingabe = FALSE;
			break;

		case '2':
			iReturnValue = HAUPTMENUE_REGEL;
			bFalscheingabe = FALSE;
			break;

		case '3':
			iReturnValue = HAUPTMENUE_LISTE;
			bFalscheingabe = FALSE;
			break;

		case '4':
			iReturnValue = HAUPTMENUE_LOGOUT;
			bFalscheingabe = FALSE;
			Abmelden(cUserReset);
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

/*
========================================================================
Funktion StartMenue(void)
Beschreibung:				Auswahl zwischen Login und Register mit
							Möglichkeit das Programm von hier aus zu
beenden
Uebergebene Daten:			-
Returnwert:					STARTMENUE_LOGIN,STARTMENUE_REGISTER,
STARTMENUE_END
========================================================================
*/

int StartMenue(void) {
	// Variablen
	char cAuswahl;
	int bFalscheingabe = FALSE;

	// Schleife solange eine falsche Auswahl getroffen wurde
	do {
		// Screen clear
		system("cls");
		// Ausgaben
		printStartMenue();
		if (bFalscheingabe == TRUE) {
			printf("\n  Falschangabe, ihre Eingabe war: %c", cAuswahl);
		}
		printf("\n  Ihre Eingabe: ");
		// Einlesen der Usereingabe
		fflush(stdin);
		scanf("%c", &cAuswahl);
		/* switch mit den Optionen:
		1 -> Login
		2 -> Registrieren
		x -> Exit
		*/
		switch (cAuswahl) {
		case '1': bFalscheingabe = FALSE;
			return STARTMENUE_LOGIN;
		case '2': bFalscheingabe = FALSE;
			return STARTMENUE_REGISTER;
		case 'x': bFalscheingabe = FALSE;
			return STARTMENUE_END;
		default:bFalscheingabe = TRUE;
		}

	} while (bFalscheingabe == TRUE);

}

/*
========================================================================
Funktion SchwierigkeitMenue(void)
Beschreibung:				Ausgaben fuer das Start-Menue
Uebergebene Daten:			-
Returnwert:					LEICHT,MITTEL,SCHWER
========================================================================
*/

int SchwierigkeitMenue(void) {
	// Variablen fuer das Schwierigkeitsmenue
	char cAuswahl;
	int bFalscheingabe = FALSE;
	// Schleife solange eine falsche Auswahl getroffen wurde
	do {
		// Screen clear
		system("cls");
		// Ausgaben fuer das Schwierigkeitsmenue
		printSchwierigkeitsAuswahl();
		if (bFalscheingabe == TRUE) {
			printf("\n  Falschangabe, ihre Eingabe war: %c", cAuswahl);
		}
		printf("\n  Ihre Eingabe: ");
		// Einlesen der Usereingabe
		fflush(stdin);
		scanf("%c", &cAuswahl);
		/* switch mit den Optionen:
		1 -> LEICHT
		2 -> MITTEL
		3 -> SCHWER
		*/
		switch (cAuswahl) {
		case '1': bFalscheingabe = FALSE;
			return LEICHT;
		case '2': bFalscheingabe = FALSE;
			return MITTEL;
		case '3': bFalscheingabe = FALSE;
			return SCHWER;
		default:bFalscheingabe = TRUE;
		}
	} while (bFalscheingabe == TRUE);

}


void Bestenliste(int iSchwierigkeitsgrad) {
	char bFalscheingabe = FALSE;
	char cUserEingabe;
	int i = 0;
	Bestenlisteneintrag* ptBestenlisteneintraege = NULL;
	ptBestenlisteneintraege = liesBestenlistendaten(iSchwierigkeitsgrad);
	do {
		system("cls");
		printf("  B E S T E N L I S T E\n");
		printf("  = = = = = = = = = = =\n\n\n\n");
		printf("  ");
		printf("   %s\t\t\t\t\n\n"/*, cSchwierigkeit*/);
		printf("  \xB3\xB3 Nutzername\t\t\t\t\xB3");
		printf(" Spielzeit\t");
		printf("\xB3\xB3\n");
		printf("  \xC5\xC5\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4"
			"\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4"
			"\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4");
		printf("\xC5\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4"
			   "\xC4\xC4\xC5\xC5\n");
		for (i = 0; i < 10; i++) {
			printf("  \xB3\xB3 %s\t\t\t\t\xB3"/*,ptBestenlisteneintraege.user*/);
			printf(" %s\t\t"/*,ptBestenlisteneintraege.zeit*/);
			printf("\xB3\xB3\n");
		}
		printf("\n  Zur Rueckkehr zum Hauptmenue bitte 'x' eingeben\n\n");
		// Falscheingabenpruefung
		if (bFalscheingabe == TRUE) {
			printf("  Bitte 'x' eingeben.\n");
		}
		printf("  Ihre Eingabe: ");
		// Eingabe
		fflush(stdin);
		scanf("%c", &cUserEingabe);

		// Switch ( x -> Menue zurueck / alles andere im Menue bleiben )
		switch (cUserEingabe) {

		case 'x': bFalscheingabe = FALSE;
			break;
		default: bFalscheingabe = TRUE;
		}
	} while (bFalscheingabe == TRUE);
}



/*
========================================================================
Funktion printStartMenue(void)
Beschreibung:				Ausgaben fuer das Start-Menue
Uebergebene Daten:			-
Returnwert:					-
========================================================================
*/

void printStartMenue(void) {
	// Ausgaben fuer das StartMenue
	printf("\n\n");
	printf("  S U D O K U S T A R T\n");
	printf("  = = = = = = = = = = =\n\n");

	printf("  Geben sie zum Ausfuehren einer Aktion eins der"
		" angegebenen Zeichen ein.\n");
	printf("  1: In einem bereits existierenden Nutzerkonto einloggen.\n");
	printf("  2: Einen neuen Benutzer registrieren.\n");
	printf("  x: Das Programm beenden.\n");
}

/*
========================================================================
Funktion printSchwierigkeitsAuswahl(void)
Beschreibung:				Ausgaben fuer das Schwierigkeits-Menue
Uebergebene Daten:			-
Returnwert:					-
========================================================================
*/

void printSchwierigkeitsAuswahl(void) {
	// Ausgaben fuer das Schwierigkeitsmenue
	printf("\n\n");
	printf("  S C H W I E R I G K E I T S A U S W A H L\n");
	printf("  = = = = = = = = = = = = = = = = = = = = =\n\n");

	printf("  Bitte waehlen Sie einen Schwierigkeitsgrad aus.\n");
	printf("  1: Leicht\n");
	printf("  2: Mittel\n");
	printf("  3: Schwer\n");
}

/*
========================================================================
Funktion printRegisterWelcome(void)
Beschreibung:				Ausgabe des Wilkommensbildschirms
Uebergebene Daten:			-
Returnwert:					-
========================================================================
*/

void printRegisterWelcome(void) {
	// Screen clear
	system("cls");
	// Ausgaben von printRegisterWelcome
	printf("  R E G I S T R I E R U N G\n");
	printf("  = = = = = = = = = = = = =\n\n");
	printf("  Wilkommen im Registrierungsmenue!\n");
	printf("  Bitte befolgen sie die Anweisungen um sich zu registrieren\n\n");
	printf("  Sie wollten sich doch nicht registrieren?"
		" Druecken sie bitte 'x'\n");
	printf("  Jede andere Eingabe laesst sie fortfahren!\n\n");
	printf("  Ihre Eingabe: ");
}

/*
========================================================================
Funktion printRegistrierungMenueNutzername(void)
Beschreibung:				Ausgabe des Nutzernamen Registrierungs-
menues
Uebergebene Daten:			-
Returnwert:					-
========================================================================
*/

void printRegistrierungMenueNutzername(void) {
	// Screen clear
	system("cls");
	// Ausgaben von printRegistrierungMenueNutzername
	printf("  R E G I S T R I E R U N G\n");
	printf("  = = = = = = = = = = = = =\n\n");
	printf("  Sonderzeichen sind hier nicht erlaubt!\n");
	printf("  Bitte geben sie Ihren Nutzernamen ein!\n\n");
	printf("  Ihre Eingabe: ");
}


/*
========================================================================
Funktion printRegistrierungMenueNachname(void)
Beschreibung:				Ausgabe des Nachnamen Registrierungsmenues
Uebergebene Daten:			-
Returnwert:					-
========================================================================
*/

void printRegistrierungMenueNachname(void) {
	// Screen clear
	system("cls");
	// Ausgaben von printRegistrierungMenueNachname
	printf("  R E G I S T R I E R U N G\n");
	printf("  = = = = = = = = = = = = =\n\n");
	printf("  Bitte geben sie Ihren Nachnamen ein!\n\n");
	printf("  Ihre Eingabe: ");
}


/*
========================================================================
Funktion printRegistrierungMenueVorname(void)
Beschreibung:				Ausgabe des Vornamen Registrierungsmenues
Uebergebene Daten:			-
Returnwert:					-
========================================================================
*/

void printRegistrierungMenueVorname(void) {
	// Screen clear
	system("cls");
	// Ausgaben von printRegistrierungMenueVorname
	printf("  R E G I S T R I E R U N G\n");
	printf("  = = = = = = = = = = = = =\n\n");
	printf("  Bitte geben sie Ihren Vornamen ein!\n\n");
	printf("  Ihre Eingabe: ");
}

/*
========================================================================
Funktion printRegistrierungsMenueBestaetigung(char *,char *,char *)
Beschreibung:				Ausgabe des Vornamen Registrierungsmenues
Uebergebene Daten:			char Array, char Array, char Array
Returnwert:					-
========================================================================
*/

void printRegistrierungsMenueBestaetigung
(char *NutzerName, char *NachName, char *VorName) {
	// Screen clear
	system("cls");
	// Ausgaben von printRegistrierungsMenueBestaetigung
	printf("  R E G I S T R I E R U N G\n");
	printf("  = = = = = = = = = = = = =\n\n");
	printf("  Ueberpruefen Sie bitte die folgenden Daten.\n\n");
	printf("  Nutzername: %s\n", NutzerName); //Nutzername
	printf("  Nachname: %s\n", NachName); //Nachname
	printf("  Vorname: %s\n\n", VorName); //Vorname
	printf("  Bestaetigen Sie diese Daten? (y/n)");
}

/*
========================================================================
Funktion printRegistrierungsMenuePasswort(void)
Beschreibung:				Ausgabe des Passwort Registrierungsmenues
Uebergebene Daten:			-
Returnwert:					-
========================================================================
*/

void printRegistrierungsMenuePasswort(void) {
	// Screen clear
	system("cls");
	// Ausgaben von printRegistrierungsMenuePasswort
	printf("  R E G I S T R I E R U N G\n");
	printf("  = = = = = = = = = = = = =\n\n");
	printf("  Bitte geben sie nun Ihr Kontopasswort ein!\n");
	printf("  Das Passwort sollte Maximal 20 Zeichen haben.\n");
	printf("  Das Passwort sollte ausserdem nicht kuerzer " 
			 "als 5 Zeichen sein!\n\n");
	printf("  Ihre Eingabe: ");
}

/*
========================================================================
Funktion printRegistrierungsMenuePasswortPruef(void)
Beschreibung:				Ausgabe des Passwortpruefungs
Registrierungsmenues
Uebergebene Daten:			-
Returnwert:					-
========================================================================
*/

void printRegistrierungsMenuePasswortPruef(void) {
	// Screen clear
	system("cls");
	// Ausgaben von printRegistrierungsMenuePasswort
	printf("  R E G I S T R I E R U N G\n");
	printf("  = = = = = = = = = = = = =\n\n");
	printf("  Zur Pruefung der Richtigkeit geben sie bitte Ihr Passwort"
		" erneut ein!\n\n");
	printf("  Ihre Eingabe: ");
}

/*
========================================================================
Funktion printRegistrierungsMenuePasswortPruef(void)
Beschreibung:				Ausgabe des Passwortpruefungs
Registrierungsmenues
Uebergebene Daten:			-
Returnwert:					-
========================================================================
*/

void printRegisterComplete(void) {
	// Screen clear
	system("cls");
	// Ausgaben von printRegisterComplete
	printf("  R E G I S T R I E R U N G\n");
	printf("  = = = = = = = = = = = = =\n\n");
	printf("  Vielen dank fuer Ihre Registrierung sie werden nun"
		" zum Hauptmenue weitergeleitet!\n\n");
}

void initSudoku(void) {
	liesSudoku(1);
	printSudoku(LEICHT);
}



int SudokuSpiel(int iSchwierigkeitsgrad) {
	int bEnde = FALSE;
	Koordinate koordinateEingabe;
	while (bEnde == FALSE) {
		eingabeSudoku(&koordinateEingabe, iSchwierigkeitsgrad);
		sudoku[koordinateEingabe.iX][koordinateEingabe.iY] = koordinateEingabe;
	}
}

// x = Reihe; y = Spalte
void eingabeSudoku(Koordinate* nutzereingabe, int iSchwierigkeitsgrad) {
	char* sKoordinaten;
	char* sZiffer;
	char cZiffer;
	int bFalscheingabe = FALSE;
	// Koordinateneingabe
	do {
		printSudoku(iSchwierigkeitsgrad);
		// Falscheingabe
		if (bFalscheingabe == TRUE) {
			printf("  Sie haben eine ungültige Koordinate eingegeben.\n");
			printf("  Bitte geben Sie eine der im Spielfeld "
				     "dargestellten Koordinaten ein.\n\n");
		}
		// Normale Eingabe
		printf("Ihre Auswahl: ");
		fflush(stdin);
		scanf("%s", &sKoordinaten);
		// Falscheingabe prüfen und setzen
		if (toKoordinate(sKoordinaten, nutzereingabe) == FALSE) {
			bFalscheingabe = TRUE;
		}
	} while (bFalscheingabe == TRUE);
	
	// Zifferneingabe
	bFalscheingabe = FALSE;
	do {
		printSudoku(iSchwierigkeitsgrad);
		printf("  Ihre eingegebene Koordinate: '%s'\n\n", sKoordinaten);
		printf("  Bitte geben Sie eine Ziffer von 1 bis 9 an.\n");
		printf("  Ihre Auswahl: ");
		fflush(stdin);
		scanf("%s", &sZiffer);
		// Wenn gültige Ziffer Koordinate füllen
		if (isZiffer(sZiffer) == TRUE) {
			sZiffer = trim(sZiffer);
			cZiffer = *sZiffer;
			nutzereingabe->bSichtbar = TRUE;
			nutzereingabe->iZiffer = cZiffer - ZIFFER_EINS + 1;
		}
		else {
			// Sonst wiederholen
			bFalscheingabe = TRUE;
		}
	} while (bFalscheingabe == TRUE);

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
	printf("  Die Koordinate 'y' öffnet das Regelwerk.\n");
	printf("  Sie koennen mit der Koordinate 'x' "
			 "die Hilfsfunktion aufrufen.\n\n");

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
	// nächste Zeile
	printf("\n");
}

void printVertikale(void) {
	printf("\xB3");
}
