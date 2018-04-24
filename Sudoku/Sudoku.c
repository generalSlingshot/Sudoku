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
#define _CRT_SECURE_NO_DEPRECATE 1

/*
========================================================================
Include Dateien
========================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sqlite3.h"

/*
========================================================================
Defines
========================================================================
*/
#define LEICHT 1
#define MITTEL 2
#define SCHWER 3

#define SUDOKU_WIN 1
#define SUDOKU_LOSE 0

#define HAUPTMENUE_SPIEL 1
#define HAUPTMENUE_REGEL 2
#define HAUPTMENUE_LISTE 3
#define HAUPTMENUE_LOGOUT 4
#define HAUPTMENUE_END 0

#define STARTMENUE_LOGIN 1
#define STARTMENUE_REGISTER 2
#define STARTMENUE_END 0

#define NAME_MAX 20
#define NAME_MIN 5
#define PASSWORT_MAX 20
#define PASSWORT_MIN 5

#define TRUE 1
#define FALSE 0

#define NICHT_GESETZT -1
#define ZEIT_MAX 8

#define BESTENLISTE_ANZAHL 3
#define BESTENLISTE_TOPSCORE_ANZAHL 10

#define DATABASE_FILE "sudoku_omar.sqlite3"

/*
========================================================================
Structdefinitionen
========================================================================
*/
typedef struct Bestenlisteneintrag {
	char sNutzername[NAME_MAX];
	char sSpielzeit[ZEIT_MAX];
	int iSchwierigkeit;
} Bestenlisteneintrag;

typedef struct Nutzer {
	char sNutzername[NAME_MAX];
	char sVorname[NAME_MAX];
	char sNachname[NAME_MAX];
	char sPasswort[PASSWORT_MAX];
} Nutzer;

typedef struct UebergabeLeseBestenliste {
	struct Bestenlisteneintrag eintraege[BESTENLISTE_TOPSCORE_ANZAHL];
	int curVal;
} UebergabeLeseBestenliste;

/*
========================================================================
Prototypen
========================================================================
*/
int StartMenue(void); // Chung
void RegistrierungMenue(void); // Henning
void LoginMenue(void); // Omar
int HauptMenue(void); // Sven
int SchwierigkeitMenue(void); // Chung
void Regelwerk(void); // Sven
void Bestenliste(); // Tom
void Abmelden(void);
void LoginMenue(void);
struct Bestenlisteneintrag* liesBestenlisteneintraege(int iSchwierigkeitsgrad);
int SudokuSpiel(int schwierigkeitsgrad);
int** InitSudoku(int schwierigkeitsgrad);
void fillBestenlisteneintraege(void* data, int argColumn, char** argVertical, char** columnName);
Nutzer liesLogindaten(char* sNutzername);
void printRegistrierungMenue1(void);
void printRegistrierungMenue2(void);
void printRegistrierungMenue3(void);


char* sNutzernameAngemeldet = NULL;
/*
========================================================================
Funktion main()
========================================================================
*/
int main(void) {
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

void RegistrierungMenue(void) {
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
	liesBestenlisteneintraege(SCHWER);
}

struct Bestenlisteneintrag* liesBestenlisteneintraege(int iSchwierigkeitsgrad) {
	char* sql;
	sqlite3* db_handle;
	int rc;
	struct UebergabeLeseBestenliste uebergabe;
	uebergabe.curVal = 0;

	sql = sqlite3_mprintf(
		"SELECT A.FK_Nutzer, A.Spielzeit, B.Programmwert FROM Bestenliste AS A "
		"LEFT JOIN Schwierigkeit AS B "
		"ON A.FK_Schwierigkeit = B.ID "
		"ORDER BY B.Programmwert, A.Spielzeit "
		"WHERE B.Programmwert = %i;", iSchwierigkeitsgrad);

	rc = sqlite3_open(DATABASE_FILE, &db_handle);
	if (rc != SQLITE_OK) {
		sqlite3_close(db_handle);
		exit(-1);
	}

	rc = sqlite3_exec(db_handle, sql, *fillBestenlisteneintraege, &uebergabe, NULL);
	// TODO errormessage
	return uebergabe.eintraege;
}

void fillBestenlisteneintraege(void* data, int maxCol, char** value, char** columnName) {
	char sNutzername[NAME_MAX];
	char sSpielzeit[ZEIT_MAX];
	struct UebergabeLeseBestenliste* uebergabe = (struct UebergabeLeseBestenliste*)data;
	struct Bestenlisteneintrag eintrag;
	int iSchwierigkeit;
	if (maxCol == 3) {
		return;
	}

	strcpy(eintrag.sNutzername, (char*)value++);
	strcpy(eintrag.sSpielzeit, (char*)value++);
	eintrag.iSchwierigkeit = atoi((char*)value++);
	uebergabe->eintraege[uebergabe->curVal] = eintrag;
	if (uebergabe->curVal < BESTENLISTE_TOPSCORE_ANZAHL) {
		uebergabe->curVal++;
	}


}

Nutzer liesLogindaten(char* sNutzername) {
	Nutzer benutzer;
	char* sql;
	sqlite3* db_handle;
	sqlite3_stmt* statement;
	char *zErrMessage;
	int iSpalte;
	int iReturncode;
	UebergabeLeseBestenliste uebergabe;
	uebergabe.curVal = 0;

	sql = sqlite3_mprintf(
		"SELECT Nutzername, Vorname, Nachname, Passwort FROM Benutzer "
		"WHERE Nutzername = '%s'", sNutzername);

	iReturncode = sqlite3_open(DATABASE_FILE, &db_handle);

	if (iReturncode != SQLITE_OK) {
		sqlite3_close(db_handle);
		exit(-1);
	}

	iReturncode = sqlite3_prepare_v2(db_handle, sql, strlen(sql), &statement, NULL);
	

	if (sqlite3_step(statement) != SQLITE_ROW) {
		printf("FUCKFUCKFUCK");
		// Fehler
	}

	iSpalte = 0;
	strcpy(benutzer.sNutzername, sqlite3_column_text(statement, iSpalte++));
	strcpy(benutzer.sVorname, sqlite3_column_text(statement, iSpalte++));
	strcpy(benutzer.sNachname, sqlite3_column_text(statement, iSpalte++));
	strcpy(benutzer.sPasswort, sqlite3_column_text(statement, iSpalte++));
	sqlite3_close(db_handle);

	sqlite3_free(sql);
	sqlite3_finalize(statement);

	return benutzer;
}

void LoginMenue(void) {

	int bFalscheingabe = FALSE;
	char cUsernameEingabe[NAME_MAX];
	char cPasswortEingabe[PASSWORT_MAX];
	int iArrayLength;
	int Passcorrect;
	Nutzer benutzer;

	do {

		system("cls");
		printf("\n\n  A N M E L D U N G\n");
		printf("  = = = = = = = = =\n\n");
		printf("  Bitte geben Sie den Nutzernamen und"
			" das Passwort Ihres registrierten Kontos ein.\n\n");
		printf("  Bitte Nutzernamen eingeben: ");
		scanf("%s", cUsernameEingabe);
		iArrayLength = sizeof(cUsernameEingabe) / sizeof(cUsernameEingabe[0]);

	} while (iArrayLength >= NAME_MAX && iArrayLength <= NAME_MIN);

	benutzer = liesLogindaten(cUsernameEingabe);
	do {

		system("cls");
		printf("\n\n  A N M E L D U N G\n");
		printf("  = = = = = = = = =\n\n");
		printf("  Bitte geben Sie den Nutzernamen und"
			" das Passwort Ihres registrierten Kontos ein.\n\n");
		printf("  Bitte Nutzernamen eingeben: %s\n\n", &cUsernameEingabe);
		if (bFalscheingabe == TRUE) {
			printf("  Bitte versuchen sie es erneut!\n");
			bFalscheingabe = FALSE;
		}
		printf("  Bitte Passwort eingeben: ");
		scanf("%s", cPasswortEingabe);
		Passcorrect = strcmp(cPasswortEingabe, benutzer.sPasswort);
		if (Passcorrect == 1) {
			bFalscheingabe = TRUE;
		}

	} while (Passcorrect == 1);

	sNutzernameAngemeldet = cUsernameEingabe;
	system("cls");

	printf("\n\n  Sie werden eingeloggt und zum Hauptmenue weitergeleitet...\n\n");
	printf("  ");
	system("pause");
}


void RegelwerkAufruf(void) {
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
int HauptmenueAufruf(void) {

	char cUserEingabe;
	int bFalscheingabe = FALSE;

	do {
		system("cls");
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

		case '1': printf("Test 1"); //Schwierigkeitsmenue(void);
			system("pause"); bFalscheingabe = FALSE;
			break;

		case '2': printf("Test 2"); //Regelwerk(void);
			system("pause"); bFalscheingabe = FALSE;
			break;

		case '3': printf("Test 3"); //Bestenliste(void);
			system("pause"); bFalscheingabe = FALSE;
			break;

		case '4': printf("Test 4"); //return HAUPTMENUE_LOGOUT;
			system("pause"); bFalscheingabe = FALSE;
			break;

		case 'x': printf("Test X");//HAUPTMENUE_END
			system("pause"); bFalscheingabe = FALSE;
			break;
		default: bFalscheingabe = TRUE;
		}
	} while (bFalscheingabe == TRUE);
}

void printSchwierigkeitsAuswahl(void);
void printStartMenue(void);

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
	else if (cAuswahl == 'x') {
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