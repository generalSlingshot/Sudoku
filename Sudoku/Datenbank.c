#include "Sudoku.h"

struct Bestenlisteneintrag* liesBestenlisteneintraege(int iSchwierigkeitsgrad);
void fillBestenlisteneintraege(void* data, int argColumn, char** argVertical, char** columnName);
Nutzer liesLogindaten(char* sNutzername);


struct Bestenlisteneintrag* liesBestenlisteneintraege(int iSchwierigkeitsgrad) {
	char* sql;
	sqlite3* db_handle;
	int rc;
	UebergabeLeseBestenliste uebergabe;
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