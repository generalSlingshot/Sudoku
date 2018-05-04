

#if !defined (VAR)
#define VAR

// Prototypen
int StartMenue(void); // Chung
void RegistrierungMenue(void); // Henning
int SchwierigkeitMenue(void);
void LoginMenue(void); // Omar
int HauptMenue(void); // Sven
void Regelwerk(void); // Sven
void Bestenliste(void); // Tom
// int SudokuSpiel(int schwierigkeitsgrad);
void printRegistrierungMenue1(void);
void printRegistrierungMenue2(void);
void printRegistrierungMenue3(void);
void RegelwerkPrint(void);
void LoginMenue(void);
void printSchwierigkeitsAuswahl(void);
void printStartMenue(void);
void initSudoku(void);
void eingabeSudoku(Koordinate* nutzereingabe, int iSchwierigkeitsgrad);

#endif