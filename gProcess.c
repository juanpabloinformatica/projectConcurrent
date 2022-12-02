#include "gProcessus.h"
#include <stdio.h>
#include <string.h>
#include "cpu.h"
#include "tinyalloc.h"
#include <stdlib.h>
/*premiere etape*/
#define TABLEAU_PROCESSUS_LENGTH 2
void ctx_sw(int *, int *);
Processus* ptrProcessusActif;
 

Processus* processus[TABLEAU_PROCESSUS_LENGTH];

Processus idleP = {.nomProcessus = "idle", .pid = 0, .etat = elu};
Processus proc1P = {.nomProcessus = "proc1", .pid = 1, .etat = activable};

/*end -premiere etape*/


void initialisationStructures(void (*proccesFunction)())
{
    processus[0] = &idleP;
    processus[1] = &proc1P;
    // // ptrProcessusActif = &processus[0];
    processus[1]->contexteDExecution[1] = (int)&(processus[1]->pileDExecution[PILE_DEXECUTION_LENGTH - 1]);
    processus[1]->pileDExecution[PILE_DEXECUTION_LENGTH-1] = (int)proccesFunction;
    // processus[1].contexteDExecution[1] = (int)&(processus[1].pileDExecution[PILE_DEXECUTION_LENGTH - 1]);
    // processus[1].pileDExecution[PILE_DEXECUTION_LENGTH - 1] = (int)proccesFunction;
}
// void idle(){

//     printf("[idle] je tente de passer la main a proc1...\n");
//     ctx_sw(processus[0].contexteDExecution,processus[1].contexteDExecution);
// }

// void proc1(){
//     printf("[proc1] idle m’a donne la main\n");
//     printf("[proc1] j’arrete le systeme\n");
//     hlt();
// }

// allex retour
// void idle(void)
// {
//     for (int i = 0; i < 3; i++)
//     {
//         printf("[idle] je tente de passer la main a proc1...\n");
//         ctx_sw(processus[0].contexteDExecution,processus[1].contexteDExecution);
//         printf("[idle] proc1 m’a redonne la main\n");
//     }
//     printf("[idle] je bloque le systeme\n");
//     hlt();
// }


void idle(void)
{
    for (;;)
    {
        ptrProcessusActif = processus[0];
        printf("[%s] pid = %i\n", mon_nom(), mon_pid());
        ordonnance();
    }
}
void proc1(void)
{
    for (;;)
    {
        ptrProcessusActif = processus[1];
        printf("[%s] pid = %i\n", mon_nom(), mon_pid());
        ordonnance();
    }
}

void ordonnance(){
    Processus* tempProcessus;
    for(int i = 0 ; i < TABLEAU_PROCESSUS_LENGTH ; i++){
        if(processus[i]->etat==activable){
            processus[i]->etat=elu;
            tempProcessus = processus[i];
            break;
        }
    }
    ptrProcessusActif->etat = activable;
    ctx_sw(ptrProcessusActif->contexteDExecution,tempProcessus->contexteDExecution);
}

int mon_pid(){
    return ptrProcessusActif->pid;
}
char* mon_nom(){
    return ptrProcessusActif->nomProcessus;
}
void augmenterCapacite(){

}