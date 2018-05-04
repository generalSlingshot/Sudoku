#include "Sudoku.h"
#include "Datenbank.h"
#include "sqlite3.h"



Bestenlisteneintrag* liesBestenlistendaten(int iSchwierigkeitsgrad);
Nutzer* liesLogindaten(char* sNutzername);
void fuelleKoordinate(Koordinate* koordinate, sqlite3_stmt* statement);

void liesSudoku(int id) {
	char* sql;
	sqlite3* db_handle;
	sqlite3_stmt* statement;
	int iSpalte;
	int iReihe;
	int iReturncode;
	Koordinate koordinate;


	// SQL
	sql = sqlite3_mprintf(
		"SELECT B.KoordinateX, B.KoordinateY, B.Sichtbar, B.Ziffer "
		"FROM Sudoku AS A "
		"LEFT JOIN Koordinate AS B "
		"ON A.ID = B.FK_Sudoku "
		"WHERE A.ID = %i "
		"ORDER BY B.KoordinateX, B.KoordinateY; ", id);

	// Db öffnen
	iReturncode = sqlite3_open(DATABASE_FILE, &db_handle);

	// Bei fehlern sofort schliessen
	if (iReturncode != SQLITE_OK) {
		sqlite3_close(db_handle);
		exit(-1); // TODO check
	}

	iReturncode = sqlite3_prepare_v2(db_handle, sql, strlen(sql), &statement, NULL);

	// Koordinatenarray füllen
	iReihe = 0;
	iSpalte = 0;

	while (sqlite3_step(statement) == SQLITE_ROW) {
		fuelleKoordinate(&koordinate, statement);
		sudoku[iSpalte][iReihe] = koordinate;
		
		if (iReihe+1 < SUDOKU_REIHE) {
			iReihe++;
		}
		else if (iSpalte < SUDOKU_SPALTE) {
			iSpalte++;
			iReihe = 0;
		}
	}
}

int registriereNutzer(Nutzer* ptBenutzer) {
	sqlite3* db_handle;
	int iReturncode;
	char* sql = sqlite3_mprintf(
		"INSERT INTO Benutzer (Vorname, Nachname, Nutzername, Passwort) "
		"VALUES ('%s', '%s', '%s', '%s')",
		ptBenutzer->sVorname,
		ptBenutzer->sNachname,
		ptBenutzer->sNutzername,
		ptBenutzer->sPasswort);

	// Db öffnen
	iReturncode = sqlite3_open(DATABASE_FILE, &db_handle);

	// Bei fehlern sofort schliessen
	if (iReturncode != SQLITE_OK) {
		sqlite3_close(db_handle);
		return DATENBANK_FEHLER;
	}

	iReturncode = sqlite3_exec(db_handle, sql, NULL, NULL, NULL);

	if (iReturncode != SQLITE_OK) {
		return DATENBANK_FEHLER;
	}
	return DATENBANK_OK;
}

void fuelleKoordinate(Koordinate* koordinate, sqlite3_stmt* statement) {
	int i = 0;
	// x-Koordinate
	koordinate->iX = sqlite3_column_int(statement, i++);

	// y-Koordinate
	koordinate->iY = sqlite3_column_int(statement, i++);

	// Sichtbar
	koordinate->bSichtbar = sqlite3_column_int(statement, i++);

	// Ziffer
	koordinate->iZiffer = sqlite3_column_int(statement, i++);
}

Bestenlisteneintrag* liesBestenlistendaten(int iSchwierigkeitsgrad) {
	char* sql;
	sqlite3* db_handle;
	sqlite3_stmt* statement;
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
		"ORDER BY A.Spielzeit "
		"WHERE B.Programmwert = %i "
		"LIMIT 10; ", iSchwierigkeitsgrad);

	// Db öffnen
	iReturncode = sqlite3_open(DATABASE_FILE, &db_handle);

	// Bei fehlern sofort schliessen
	if (iReturncode != SQLITE_OK) {
		sqlite3_close(db_handle);
		exit(-1); // TODO check
	}

	iReturncode = sqlite3_prepare_v2(db_handle, sql, strlen(sql), &statement, NULL);

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

int speicherBestenlistendaten(Bestenlisteneintrag* daten) {
	sqlite3* db_handle;
	int iReturncode;
	int iErgebnis;
	char* sql;
	if (isAngemeldet()) {
		sql = sqlite3_mprintf(
			"INSERT INTO Bestenliste (Spielzeit, FK_Nutzer, FK_Schwierigkeit) "
			"SELECT '%s', "
			"(SELECT Benutzer.ID FROM Benutzer "
			"WHERE Benutzer.Nutzername = '%s' LIMIT 1), "
			"(SELECT Schwierigkeit.ID FROM Schwierigkeit "
			"WHERE Schwierigkeit.Programmwert = %i LIMIT 1); ",
			daten->sSpielzeit,
			daten->sNutzername,
			daten->iSchwierigkeit);

		// Db öffnen
		iReturncode = sqlite3_open(DATABASE_FILE, &db_handle);

		// Bei fehlern sofort schliessen
		if (iReturncode != SQLITE_OK) {
			sqlite3_close(db_handle);
			exit(-1); // TODO check
		}

		iReturncode = sqlite3_exec(db_handle, sql, NULL, NULL, NULL);

		if (iReturncode != SQLITE_OK) {
			iErgebnis = DATENBANK_FEHLER;
		}
		else {
			iErgebnis = DATENBANK_OK;
		}
	}
	else {
		iErgebnis = DATENBANK_FEHLER;
	}
	return iErgebnis;
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
		"SELECT ID, Nutzername, Vorname, Nachname, Passwort FROM Benutzer "
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