/*
   ========================================================================
   Autor       : Gruppe 3
   Firma       : HHBKSpielesoft AG
   Dateiname   : Oberflaeche.c
   Datum       : 27.04.2018
   Beschreibung: Oberflaeche.c beinhaltet die meisten Funktionen die nachher
				 fuer die Ausgabe und Ausfuehrung der Menues verantwortlich
				 sind.
   Version     : 1.0
   ========================================================================
*/

/*
   ========================================================================
   Include Dateien
   ========================================================================
*/
#include "Sudoku.h"
#include "Oberflaeche.h"
#include "Datenbank.h"

/* 
   ========================================================================
   Funktion LoginMenue(void)
   Beschreibung:				falls der User angemeldet werden konnte
   Uebergebene Daten:			-
   Returnwert:					SUCCESS
   ========================================================================
*/

int LoginMenue(void) {
// Variablen fuer das Loginmenue
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
// Ausgabe an den User dass, das kein Profil mit dem Namen vorhanden ist
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
	return SUCCESS;
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
   Beschreibung:				Regelt die verschiedenen Eingabemoeglich-
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
								moeglichkeit das Programm von hier aus zu
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
   Funktion RegistrierungMenue(void)
   Beschreibung:				Abspeichern von Userdaten zur Uebermittlung
								an die Datenbank
   Uebergebene Daten:			-
   Returnwert:					SUCCESS bei erfolg, REGISTER_BACK falls der
								User vorher abgebrochen hat
   ========================================================================
*/

int RegistrierungMenue(void) {
// Struct fuer Userdaten
	Nutzer benutzer;
// Variablen fuer RegistrierungMenue
	char sUsername[NAME_MAX],
		sVorname[NAME_MAX],
		sNachname[NAME_MAX],
		sPasswort[NAME_MAX],
		sPassconfirm[NAME_MAX];
	char cBestaetigung = 'z';
	char cRegisterON = 'h';
	int bFalscheingabe = FALSE;
	int length = 0;
	int comparevalue = 52;
// Ausgaben fuer RegistrierungMenue	
	printRegisterWelcome();
// Einlesen User Entscheidung 1
	fflush(stdin);
	scanf("%c", &cRegisterON);
// Falls cRegisterON == 'x' spring zu ende und return REGISTER_BACK
	if(cRegisterON != 'x') {
// Solange bei der Bestaetigung 'n' angegeben wird wiederholen
		do {
// Solange die Eingabe nicht korrekt ist wiederholen
			do {
				printRegistrierungMenueNutzername();
				fflush(stdin);
				scanf("%s", &sUsername);
				length = strlen(sUsername);
			}while((length < 5 || length > 20) || 
				Pruef_isalnum(sUsername) == FALSE);
// length wieder null setzen
			length = 0;
// Solange die Eingabe nicht korrekt ist wiederholen
			do {
				printRegistrierungMenueNachname();
				fflush(stdin);
				scanf("%s", &sNachname);
				length = strlen(sNachname);
			}while((length < 5 || length > 20) || 
				Pruef_isalpha(sNachname) == FALSE);
// length wieder null setzen
			length = 0;
// Solange die Eingabe nicht korrekt ist wiederholen
			do {
				printRegistrierungMenueVorname();
				fflush(stdin);
				scanf("%s", &sVorname);
				length = strlen(sVorname);
			}while((length < 5 || length > 20) || 
				Pruef_isalpha(sVorname) == FALSE);
			do {
				printRegistrierungsMenueBestaetigung
					(sUsername, sNachname, sVorname);
				fflush(stdin);
				scanf("%c", &cBestaetigung);
			}while(cBestaetigung != 'y' && cBestaetigung != 'n');
		}while(cBestaetigung == 'n');
// length wieder null setzen
			length = 0;
// Solange die Eingabe nicht korrekt ist wiederholen
		do {
			printRegistrierungsMenuePasswort();
			fflush(stdin);
			scanf("%s", &sPasswort);
			length = strlen(sPasswort);
		}while(length < 5 || length > 20);
// Solange die Passwoerter nicht uebereinstimmen wiederholen
		do {
			printRegistrierungsMenuePasswortPruef();
			fflush(stdin);
			scanf("%s", &sPassconfirm);
			comparevalue = strcmp(sPasswort,sPassconfirm);
		}while(comparevalue != 0);

// Ausgabe der printRegisterComplete();
		printRegisterComplete();

// Befuellen des Structs Nutzer
		strcpy(benutzer.sNutzername,sUsername);
		strcpy(benutzer.sNachname, sNachname);
		strcpy(benutzer.sVorname, sVorname);
		strcpy(benutzer.sPasswort, sPasswort);

// Start registriereNutzer(Struct benutzer)
		registriereNutzer(&benutzer);

// Start Anmelden(char sUsername)
		Anmelden(sUsername);

		return SUCCESS;
	}
		return REGISTER_BACK;
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
	(char *NutzerName,char *NachName, char *VorName) {
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
	printf("  Das Passwort sollte ausserdem nicht kuerzer als 5 Zeichen sein!\n\n");
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
		printf("\xC5\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC5\xC5\n");
		for(i = 0;i < 10; i++) {
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
   Funktion Pruef_isalnum(char *)
   Beschreibung:				Pruefung der Eingabe ob das eingegebene
								Ausschliesslich aus Zahlen und Buchstaben
								besteht
   Uebergebene Daten:			char Array
   Returnwert:					1 Falls String korrekt, 0 Falls nicht
   ========================================================================
*/

int Pruef_isalnum(char *Teststring) {
	while(isalnum(*Teststring)) 
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
	while(isalpha(*Teststring)) 
		++Teststring;
		return *Teststring == 0;
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

	strcpy(sNutzernameAngemeldet,Username);

}

/* 
   ========================================================================
   Funktion Abmelden(char *Teststring)
   Beschreibung:				Globalen Usernamen leeren
   Uebergebene Daten:			char Array
   Returnwert:					-
   ========================================================================
*/

void Abmelden(char *Username) {

	strcpy(sNutzernameAngemeldet,Username);

} 