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
int processusIndice = 1; 

Processus idleP = {.nomProcessus = "idle", .pid = 0, .etat = elu};
// Processus proc1P = {.nomProcessus = "proc1", .pid = 1, .etat = activable};

/*end -premiere etape*/


int cree_processus(void(*code)(void),char* nom){
    
    if(processusIndice == TABLEAU_PROCESSUS_LENGTH+1){
        return -1;
    }
    // Processus p = {.pid = processusIndice, .etat=activable};
    // strcpy(p.nomProcessus,nom);
    Processus* ptr_processus = (Processus*)malloc(sizeof(Processus));
    ptr_processus->pid = processusIndice;
    ptr_processus->etat = activable;
    strcpy(ptr_processus->nomProcessus,nom);
    ptr_processus = ptr_processus;
    processus[processusIndice] = ptr_processus;
    processus[processusIndice]->contexteDExecution[1] = (int)&(processus[1]->pileDExecution[PILE_DEXECUTION_LENGTH - 1]);
    processus[processusIndice]->pileDExecution[PILE_DEXECUTION_LENGTH - 1] = (int)code;
    processusIndice++;
    return 0;
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