#ifndef ECRAN_FUNCTIONS_
#define ECRAN_FUNCTIONS_
  
    uint16_t *ptr_men(uint32_t lig, uint32_t col);
    void ecrit_car(uint32_t lig, uint32_t col, char c,int color,int bck);
    void efface_ecran();
    void place_curseur(uint32_t lig,uint32_t col);
    void traite_car(char c,int color,int bck);
    // void console_putbytes(const char* s, int len);
    void console_putbytes(const char* s);
    void defilement(void);
    // void controlCoordinates(void);

#endif