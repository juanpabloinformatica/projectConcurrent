//#include <stdint.h>
#include <inttypes.h>
#include "ecran.h"
#include <stdio.h>
#include "cpu.h"
#include <string.h> 

uint32_t row = 0 ;
uint32_t col = 0 ;



//returns the location of the graphical memory
uint16_t *ptr_mem(uint32_t lig,uint32_t col){
    uint16_t *position = (uint16_t*)(0xB8000 + 2 * (lig * 80 + col));
    return position;
}

void ecrit_car(uint32_t lig, uint32_t col, char c,int color,int bck){
    uint16_t* position = ptr_mem(lig,col);
    *position = c |(color << 8)|(bck << 12)|(0<<15);
}

void efface_ecran(void){

    for(int i = 0 ; i < 25 ; i++){
        for(int j = 0 ; j < 80; j++){
            ecrit_car(i,j,' ', 15,0);
        }
    }
    row = 0;
    col = 0;
    place_curseur(row,col);
    
}

void place_curseur(uint32_t lig,uint32_t col){
    uint16_t pos = (col+lig*80);
    uint16_t commandPort = 0x3D4;
    uint16_t dataPort = 0x3D5;
    uint8_t instruction1 = 0X0F;
    uint8_t instruction2 = 0X0E;
    uint8_t posMbits = (pos>>8);
    uint8_t posLbits = ((pos<<8)>>8);
    outb(instruction1,commandPort);
    outb(posLbits,dataPort);
    outb(instruction2,commandPort);
    outb(posMbits,dataPort);
    return ;
}

void traite_car(char c,int color,int bck){
    
    if(c>=32 && c<=126){
        ecrit_car(row,col,c,color,bck);
        if(col==79){
            col = 0;
            row+=1;
        }else{
            col+=1;
        }
        place_curseur(row,col);
    }else{

        if(c == 8){
            if(col!=0){
                col-=1;
                place_curseur(row,col);
            }
        }else if(c == 9){
            if(col<80){
                col = (col+(8-col%8));
                place_curseur(row,col); 
            }
        }else if(c == 10){
            row+=1;
            place_curseur(row,col);
        }else if(c == 12){
            efface_ecran();
            row = 0;
            col = 0;
            place_curseur(row,col);
        }else if(c == 13){
            col=0;
            place_curseur(row,col);
        }


    }
}

void defilement(){
    for(int i = 0;i<25;i+=1){
        memmove(ptr_mem(i,0),ptr_mem(i+1,0),sizeof('a')*80);
    }
    row-=1;
    place_curseur(row,col);

}

void console_putbytes(const char* s){
    while(*s!='\0'){
        traite_car(*s,15,0);
        s+=1;
    }
}
