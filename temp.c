#include <stdio.h>
#include <stdbool.h>
#include <inttypes.h>
#include "cpu.h"
#include "temp.h"
#include "ecran.h"
#include "segment.h"

#define INTERRUPTION_NUMBER 32
#define QUARTZ 0X1234DD
#define CLOCKFREQ 50
#define NUM_IRQ 0
int     ticCounter = 0;
float ss = 0;
float mm = 0;
float hh = 0;
// char time[8];
extern void traitant_IT_32(void);



uint16_t frequency;

//punto 1

// how i receive that list

void show_time(char* string){
    int col_selected = 80-8;
    int row_selected = 0;
    char* temp_string = string;
    while(*temp_string !='\0'){
        ecrit_car(row_selected,col_selected,*temp_string,15,0);
        col_selected++;
        temp_string++;
    }
}


//punto 2
 void tic_PIT(void){
   outb(0x20,0x20);
   ticCounter++;
   if(ticCounter==CLOCKFREQ){
        ss++;
   }
   if(ss==60){
        mm++;
        ss=0;
   }
   if(mm==60){
    hh++;
    mm=0;
   }
   char time[8];
   sprintf(time,"%1.0f:%1.0f:%1.0f",hh,mm,ss);
   show_time(time);
 }

//punto 3
void init_traitant_IT(uint32_t num_IT, void (*traitant)(void)){
    uint32_t* table_de_vecteurs = (uint32_t*)0X1000;
    table_de_vecteurs += num_IT;
    *table_de_vecteurs = ((uint32_t)KERNEL_CS)<<16| ((uint32_t) traitant<<16)>>16;
    table_de_vecteurs++;
    *table_de_vecteurs = ((uint32_t)traitant>>16)<<16|(uint32_t)0X8E00;
    
}

void initialisations(void){
    init_traitant_IT(INTERRUPTION_NUMBER, traitant_IT_32);
    fix_frequency();
    masque_IRQ(NUM_IRQ,0);
}

// void test(){
//     init_traitant_IT(32,traitant_IT_32);
// }

void masque_IRQ(uint32_t num_IRQ, uint8_t masque ){
    
    uint8_t octect_recupere = inb(0X21);
    uint8_t mask = 1<<num_IRQ;
    if(masque==1){
        octect_recupere|=mask; 
    }else{
        octect_recupere&=~mask;
    }
    outb(octect_recupere,0x21);
}
void fix_frequency(){
    outb(0X34,0X43);
    outb((QUARTZ/CLOCKFREQ)&0XFF,0X40);
    outb((QUARTZ/CLOCKFREQ)>>8,0X40);
}


