#include <cpu.h>
#include <inttypes.h>
#include <ecran.h>
// #include<sys/wait.h>

// on peut s'entrainer a utiliser GDB avec ce code de base
// par exemple afficher les valeurs de x, n et res avec la commande display

// une fonction bien connue

void kernel_start(void)
{
    sti();
    while (1) {
        // cette fonction arrete le processeur
        hlt();
    }
}

