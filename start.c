#include <cpu.h>
#include <inttypes.h>
#include "ecran.h"
#include "temp.h"
#include "gProcessus.h"
#include <stdio.h>
extern Processus* processus[];
extern Processus idleP;
// #include<sys/wait.h>

// on peut s'entrainer a utiliser GDB avec ce code de base
// par exemple afficher les valeurs de x, n et res avec la commande display

// une fonction bien connue

void kernel_start(void)
{
    
    // initialisationStructures(&proc1);
    processus[0] = &idleP;
    cree_processus(&proc1,"proc1");
    efface_ecran();
    initialisations();
    idle();
    
    // sti();
    while (1) {
        // cette fonction arrete le processeur
        hlt();
    }
}

