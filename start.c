#include <cpu.h>
#include <inttypes.h>
#include <ecran.h>
// #include<sys/wait.h>

// on peut s'entrainer a utiliser GDB avec ce code de base
// par exemple afficher les valeurs de x, n et res avec la commande display

// une fonction bien connue

void kernel_start(void)
{
    
    
    efface_ecran();
    // place_curseur(24,79);

    // traite_car(0,0,'\f',0,0);
    // place_curseur(0,2);
    for(int i=0;i<80;i+=1){
        traite_car('a',15,0);
    }
    for(int i=0;i<80;i+=1){
        traite_car('b',15,0);
    }
     for(int i=0;i<80;i+=1){
        traite_car('c',15,0);
    }
     for(int i=0;i<80;i+=1){
        traite_car('a',15,0);
    }
    for(int i=0;i<80;i+=1){
        traite_car('b',15,0);
    }
     for(int i=0;i<80;i+=1){
        traite_car('c',15,0);
    }
    // console_putbytes("Juan pablo");
    // console_putbytes("Daniel");
    defilement();
    // traite_car('c',15,0);

    while (1) {
        // cette fonction arrete le processeur
        hlt();
    }
}

