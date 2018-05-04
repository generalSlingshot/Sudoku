#if !defined (VAR)
#define VAR

char* toZeitstring(int iSekundenGesamt);
int isAngemeldet(void);
void Abmelden(void);
char* trim(char* sZeichenkette);
int toKoordinate(char* sKoordinaten, Koordinate* koordinate);
int isSudokuGrossBuchstabe(int iZeichen);
int isSudokuKleinBuchstabe(int iZeichen);
int isSudokuZiffer(int iZeichen);
int isZiffer(char* sZeichenkette);
int Pruef_isalpha(char *Teststring);
int Pruef_isalnum(char *Teststring);
void Anmelden(char *Username);

#endif
