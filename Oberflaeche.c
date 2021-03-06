#include "Sudoku.h"
#include "Oberflaeche.h"
#include "Datenbank.h"

int LoginMenue(void) {
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
	strcpy(sNutzernameAngemeldet, sNutzernameEingabe);
	return SUCCESS;
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
int RegistrierungMenue(void) {
	Nutzer benutzer;
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
	
	printRegisterWelcome();
	fflush(stdin);
	scanf("%c", &cRegisterON);

	if(cRegisterON != 'x') {
		do {
			printRegistrierungMenueNutzername();
			fflush(stdin);
			scanf("%s", &sUsername);
			length = sizeof(sUsername) / sizeof(sUsername[0]);
		}while(length >= 5 && length <= 20);
		length = 0;
		do {
			printRegistrierungMenueNachname();
			fflush(stdin);
			scanf("%s", &sNachname);
			length = sizeof(sNachname) / sizeof(sNachname[0]);
		}while(length >= 5 && length <= 20);
		length = 0;
		do {
			printRegistrierungMenueVorname();
			fflush(stdin);
			scanf("%s", &sVorname);
			length = sizeof(sVorname) / sizeof(sVorname[0]);
		}while(length >= 5 && length <= 20);
		do {
			printRegistrierungsMenueBestaetigung(*sUsername, *sNachname, *sVorname);
			fflush(stdin);
			scanf("%c", cBestaetigung);
		}while(cBestaetigung != 'y' && cBestaetigung != 'n');
		do {
			printRegistrierungsMenuePasswort();
			fflush(stdin);
			scanf("%s", sPasswort);
			length = sizeof(sPasswort) / sizeof(sPasswort[0]);
		}while(length >= 5 && length <= 20);
		do {
			printRegistrierungsMenuePasswortPruef();
			fflush(stdin);
			scanf("%s", sPassconfirm);
			length = sizeof(sPassconfirm) / sizeof(sPassconfirm[0]);
			comparevalue = strcmp(sPasswort,sPassconfirm);
		}while(length >= 5 && length <= 20 && comparevalue != 0);
		printRegisterComplete();
		return SUCCESS;
	}
		return REGISTER_BACK;
}
void printRegisterWelcome(void) {
	system("cls");
	printf("  R E G I S T R I E R U N G\n");
	printf("  = = = = = = = = = = = = =\n\n");
	printf("  Wilkommen im Registrierungsmenue!\n");
	printf("  Bitte befolgen sie die Anweisungen um sich zu registrieren\n\n");
	printf("  Sie wollten sich doch nicht registrieren?"
		   " Druecken sie bitte 'x'\n");
	printf("  Jede andere Eingabe laesst sie fortfahren!\n\n");
	printf("  Ihre Eingabe: ");
}
void printRegistrierungMenueNutzername(void) {
	system("cls");
	printf("  R E G I S T R I E R U N G\n");
	printf("  = = = = = = = = = = = = =\n\n");
	printf("  Bitte geben sie Ihren Nutzernamen ein!\n\n");
	printf("  Ihre Eingabe: ");
}
void printRegistrierungMenueNachname(void) {
	system("cls");
	printf("  R E G I S T R I E R U N G\n");
	printf("  = = = = = = = = = = = = =\n\n");
	printf("  Bitte geben sie Ihren Nachnamen ein!\n\n");
	printf("  Ihre Eingabe: ");
}
void printRegistrierungMenueVorname(void) {
	system("cls");
	printf("  R E G I S T R I E R U N G\n");
	printf("  = = = = = = = = = =  = = =\n\n");
	printf("  Bitte geben sie Ihren Vornamen ein!\n\n");
	printf("  Ihre Eingabe: ");
}
void printRegistrierungsMenueBestaetigung(char NutzerName,char NachName, char VorName) {
	system("cls");
	printf("  R E G I S T R I E R U N G\n");
	printf("  = = = = = = = = = =  = = =\n\n");
	printf("  Ueberpruefen Sie bitte die folgenden Daten.\n\n");
	printf("  Nutzername: %s\n", &NutzerName); //Nutzername
	printf("  Nachname: %s\n", &NachName); //Nachname
	printf("  Vorname: %s\n\n", &VorName); //Vorname
	printf("  Bestaetigen Sie diese Daten? (y/n)");
}

void printRegistrierungsMenuePasswort(void) {
	system("cls");
	printf("  R E G I S T R I E R U N G\n");
	printf("  = = = = = = = = = = = = =\n\n");
	printf("  Bitte geben sie nun Ihr Kontopasswort ein!\n");
	printf("  Das Passwort sollte Maximal 20 Zeichen haben.\n");
	printf("  Das Passwort sollte au�erdem nicht kuerzer als 5 Zeichen sein!\n\n");
	printf("  Ihre Eingabe: ");
}
void printRegistrierungsMenuePasswortPruef(void) {
	system("cls");
	printf("  R E G I S T R I E R U N G\n");
	printf("  = = = = = = = = = = = = =\n\n");
	printf("  Zur Pruefung der Richtigkeit geben sie bitte Ihr Passwort"
		   " erneut ein!\n\n");
	printf("  Ihre Eingabe: ");
}
void printRegisterComplete(void) {
	system("cls");
	printf("  R E G I S T R I E R U N G\n");
	printf("  = = = = = = = = = = = = =\n\n");
	printf("  Vielen dank fuer Ihre Registrierung sie werden nun"
		   " zum Hauptmenue weitergeleitet!\n\n");
}
void Bestenliste() {
	/*liesBestenlisteneintraege(SCHWER);*/
}