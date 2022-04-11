#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>

#define in
#define out
#define inout

/* const char* defineOS()
 * defineOS() è stata creata per determinare il
 * sistema operativo dell'utente cosi' da permettere
 * una migliore compatibilia' del programma con alcune istruzioni.
 * La funzione ritorna 1 se il sistema operativo rilevato è
 * Windows, ritorna 2 se il sistema operativo è un sistema
 * Apple e infine ritorna 3 se il sistema operativo rilevato
 * è un sistema Unix-Based. Questi tre ifdef ci permettono
 * di identificare la maggioranza dello spettro dei sistemi
 * operativi maggiormente utilizzati e totalmente lo spettro
 * degli OS per PC.
 * Complessità:
 * T(1) - O(1) - S(1)
*/
int defineOS(){
    return
#ifdef _WIN32
            1;
#elif __APPLE__
    2;
    #elif __unix__
        3;
#endif
}

/* void clearScreen()
 * clearScreen() è stata creata per effettuare una pulizia dello schermo.
 * La funzione funziona in tandem con defineOS(), poiche', a seconda del
 * sistema operativo rilevato eseguira un comando di sistema adatto
 * al sistema operativo rilevato: se Windows è rilevato allora
 * verra' usato "cls" come comando, se rilevato un sistema operativo
 * Apple allora verrà utilizzato "clear" infine se viene rilevato
 * un sistema operativo Unix-based allora userà "clr".
 * Complessità:
 * T(1) - O(1) - S(1)
*/
void clearScreen(){
    char clear[] = "   ";
    int os = defineOS();
    switch(os){
        case 1:
            strcpy(clear, "cls");
            break;
        case 2:
            strcpy(clear, "clear");
            break;
        case 3:
            strcpy(clear, "clr");
            break;
    }
    system(clear);
}

/*
 * int randGen(in const int min, in const int max)
 * funzione che richiede in input un range di numeri
 * e che resituisce un numero casuale nell'intervallo
 * tra min e max (compreso min e max) -> n appartenente a [min; max]
 * Complessità:
 * T(1) - O(1) - S(1)
*/
int randGen(in const int min, in const int max){
    return rand() % (max + 1 - min) + min;
}