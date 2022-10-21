
#ifndef __TIMER__
#define __TIMER__
    void show_time(char* string);
    void tic_PIT(void);
    void masque_IRQ(uint32_t num_IRQ, uint8_t masque );
    void init_traitant_IT(uint32_t num_IT, void (*traitant)(void));
    void initialisations(void);
    void fix_frequency(void);

#endif
