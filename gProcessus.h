#if !defined(__GESTION_PROCESSUS__)
#define __GESTION_PROCESSUS__
#define PROCESSUS_NOM_LENGTH 100
#define PILE_DEXECUTION_LENGTH 512
#define CONTEXTE_DEXECUTION_LENGTH 5


typedef struct Processus{
    int pid;
    char nomProcessus[PROCESSUS_NOM_LENGTH];
    int etat;
    int contexteDExecution[CONTEXTE_DEXECUTION_LENGTH];
    int pileDExecution[PILE_DEXECUTION_LENGTH];

}Processus;


enum Etat {elu = 0 , activable = 1, endormi = 2};

void idle(void);
void proc1(void);
void proc2(void);
void proc3(void);
void proc4(void);
void proc5(void);
void proc6(void);
void proc7(void);

int cree_processus(void(*code)(void),char* nom);
void ordonnance(void);
int mon_pid(void);
char* mon_nom(void);

#endif //__GESTION_PROCESSUS__
