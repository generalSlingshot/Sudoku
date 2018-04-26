#include "Sudoku.h"


Bestenlisteneintrag* liesBestenlistendaten(int iSchwierigkeitsgrad);
Nutzer* liesLogindaten(char* sNutzername);
Koordinate* liesSudoku(int id); //TODO
void fuelleKoordinate(Koordinate* koordinate, sqlite3_stmt* statement);

Koordinate* liesSudoku(int id) {
	char* sql;
	sqlite3* db_handle;
	sqlite3_stmt* statement;
	char* zErrMessage;
	int iSpalte;
	int iReihe;
	int iReturncode;
	Koordinate koordinaten[SUDOKU_SPALTE][SUDOKU_REIHE];


	// SQL
	sql = sqlite3_mprintf(
		"SELECT B.KoordinateX, B.KoordinateY, B.Sichtbar FROM Sudoku AS A "
		"LEFTJOIN Kooridnaten AS B "
		"ON A.ID = Koordinaten.FK_Sudoku "
		"WHERE A.ID = %i "
		"ORDER BY B.KoordinateX, B.KoordinateY;", id);

	// Db öffnen
	iReturncode = sqlite3_open(DATABASE_FILE, &db_handle);

	// Bei fehlern sofort schliessen
	if (iReturncode != SQLITE_OK) {
		sqlite3_close(db_handle);
		exit(-1); // TODO check
	}

	iReturncode = sqlite3_prepare_v2(db_handle, sql, strlen(sql), &statement, &zErrMessage);

	// Koordinatenarray füllen
	iReihe = 0;
	iSpalte = 0;

	while (sqlite3_step(statement) == SQLITE_ROW) {
		fuelleKoordinate(koordinaten[iReihe, iSpalte], statement);
		if (iReihe < SUDOKU_REIHE) {
			iReihe++;
		}
		else if (iSpalte < SUDOKU_SPALTE) {
			iSpalte++;
			iReihe = 0;
		}
	}

	return &koordinaten[0][0];

}

void fuelleKoordinate(Koordinate* koordinate, sqlite3_stmt* statement) {
	int i = 0;
	// x-Koordinate
	koordinate->iX = sqlite3_column_int(statement, i++);

	// y-Koordinate
	koordinate->iY = sqlite3_column_int(statement, i++);

	// Sichtbar
	koordinate->bSichtbar = sqlite3_column_int(statement, i++);
}

Bestenlisteneintrag* liesBestenlistendaten(int iSchwierigkeitsgrad) {
	char* sql;
	sqlite3* db_handle;
	sqlite3_stmt* statement;
	char *zErrMessage;
	int iSpalte;
	int iReturncode;
	Bestenlisteneintrag eintraege[BESTENLISTE_TOPSCORE_ANZAHL];
	Bestenlisteneintrag eintrag;

	// SQL
	sql = sqlite3_mprintf(
		"SELECT C.Nutzername, A.Spielzeit, B.Programmwert FROM Bestenliste AS A "
		"LEFT JOIN Schwierigkeit AS B "
		"ON A.FK_Schwierigkeit = B.ID "
		"LEFTJOIN Nutzer AS C "
		"ON A.FK_Nutzer = C.ID"
		"ORDER BY B.Programmwert, A.Spielzeit "
		"WHERE B.Programmwert = %i ", iSchwierigkeitsgrad);

	// Db öffnen
	iReturncode = sqlite3_open(DATABASE_FILE, &db_handle);

	// Bei fehlern sofort schliessen
	if (iReturncode != SQLITE_OK) {
		sqlite3_close(db_handle);
		exit(-1); // TODO check
	}

	iReturncode = sqlite3_prepare_v2(db_handle, sql, strlen(sql), &statement, &zErrMessage);

	while (sqlite3_step(statement) == SQLITE_ROW) {
		iSpalte = 0;
		// Nutzername
		strcpy(eintrag.sNutzername, sqlite3_column_text(statement, iSpalte++));

		// Spielzeit
		strcpy(eintrag.sSpielzeit, sqlite3_column_text(statement, iSpalte++));

		// Schwierigkeit
		eintrag.iSchwierigkeit =sqlite3_column_int(statement, iSpalte++);

		eintraege[iSpalte] = eintrag;
	}
}

Nutzer* liesLogindaten(char* sNutzername) {
	Nutzer* ptBenutzer = NULL;
	Nutzer benutzer;
	char* sql;
	sqlite3* db_handle;
	sqlite3_stmt* statement;
	char *zErrMessage;
	int iSpalte;
	int iReturncode;

	sql = sqlite3_mprintf(
		"SELECT Nutzername, Vorname, Nachname, Passwort FROM Benutzer "
		"WHERE Nutzername = '%s'", sNutzername);

	iReturncode = sqlite3_open(DATABASE_FILE, &db_handle);

	if (iReturncode != SQLITE_OK) {
		sqlite3_close(db_handle);
		exit(-1);
	}

	iReturncode = sqlite3_prepare_v2(db_handle, sql, strlen(sql), &statement, &zErrMessage);


	if (sqlite3_step(statement) == SQLITE_ROW) {
		iSpalte = 0;
		strcpy(benutzer.sNutzername, sqlite3_column_text(statement, iSpalte++));
		strcpy(benutzer.sVorname, sqlite3_column_text(statement, iSpalte++));
		strcpy(benutzer.sNachname, sqlite3_column_text(statement, iSpalte++));
		strcpy(benutzer.sPasswort, sqlite3_column_text(statement, iSpalte++));
		sqlite3_close(db_handle);
		ptBenutzer = &benutzer;
	}

	sqlite3_free(sql);
	sqlite3_finalize(statement);

	return ptBenutzer;
}