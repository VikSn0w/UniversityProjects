/*
 * Vittorio Picone - 0124002584
 * PROGETTO D’ESAME DI LABORATORIO DI PROGRAMMAZIONE I 12 CFU- Parte 1 - Classificazione
 * Data una Matrice 30x30, riempire la matrice con 50 elementi in posizioni casuali rappresentando
 * con una 'X' le celle della matrice occupate e con ' ' le celle della matrice non occupate.
 *
 * Si posizionino altri due elementi, centro1 e centro2, in posizioni casuali rappresentando
 * questi due nuovi elementi con '1' e '2'. L'obiettivo dell'algoritmo è quello di determinare
 * due insiemi, A e B, dove ad A appartengono gli elementi più vicini al centro1 che al centro2 e
 * dove a B appartengono gli elementi più vicini al centro2 che al centro1. Come vicinanza s'intende
 * la minor distanza geometrica euclidea tra i due punti in considerazione.
 *
 * Dopo aver eseguito i calcoli di determinazione delle vicinanze, gli oggetti appartenenti all'insieme A
 * verranno rappresentati con una 'A', quelli appartenenti all'insieme B con una 'B', mentre gli elementi
 * che sono equidistanti sia da centro1 che da centro2, quindi non appartenenti a nessun insieme,
 * verranno indicati con 'U'
*/

#include "headers.h"

#define SIZE 30
#define SPAWN 50
#define CENTRI 2

//dichiariazione della struct per gli elementi, contenente le coordinate dell'elemento
struct elemento{
    int x;
    int y;
};

/*
 * void printCentersPositions (in struct elemento Centri[], in size_t n_centri)
 * Stampa i centri presenti nella matrice e la loro posizione
 * Complessità:
 * T(n) - O(n) - S(n)
*/
void printCentersPositions (in struct elemento Centri[], in size_t n_centri){
    for(int i = 0; i < n_centri; i++) {
        printf("Centro %d: {%d; %d}\n", i+1, Centri[i].x, Centri[i].y);
    }
}

/*
 * void printCharMatrix(inout char *Matrix, in const size_t rows, in const size_t cols)
 * Data in input una matrice, il numero di colonne e di righe
 * stamperà su schermo la matrice con il numero della
 * riga e gli elementi, dove quest'ultimi sono
 * stampati all'interno di due parentesi graffe, per migliorare
 * la leggibilità di una cella. eg. 12 {A}
 * Complessità:
 * T(n*m) - O(n*m) - S(n*m)
*/
void printCharMatrix(inout char *Matrix, in const size_t rows, in const size_t cols){
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("{%c} ", *(Matrix + i*cols + j));
        }
        printf("\n");
    }
}

/*
 * void printAllSets (in char *Matrix, in size_t cols, in struct elemento elementi[], in size_t n_elementi, in struct elemento centri[], in size_t n_centri)
 * Stampa tutti gli insiemi (incluso U) della matrice,
 * i relativi elementi e il numero degli elementi (da fare)
 * Complessità:
 * T(e*c) - O(e*c) - S((n*m)+e+c)
*/
void printAllSets (in char *Matrix, in size_t cols, in struct elemento elementi[], in size_t n_elementi, in struct elemento centri[], in size_t n_centri){
    char sets[1024] = {0};
    char equi[1024];
    strcpy(equi, "U = ");
    int startFoo = 0;

    int u = 0;
    for(int k = 0; k < n_centri; k++){
        char afoo[] = "  = \0";
        char bfoo[1] = {*(Matrix + centri[k].x*cols +centri[k].y)};

        startFoo = atoi(bfoo);
        startFoo = (int)'A'+(startFoo-1);
        afoo[0] = (char)startFoo;

        strcpy(sets, afoo);

        int n = 0;

        for(int i = 0; i < n_elementi; i++) {
            int prevx = 0;
            int prevy = 0;
            char foo[32];
            int x = elementi[i].x;
            int y = elementi[i].y;
            char debug = *(Matrix + x*cols + y);

            switch (debug) {
                case 'X':
                    printf("\nErrore nella matrice!\nInizializzare la matrice e riprovare!\n");
                    break;
                case 'U':
                    if(k == 0){
                        strcat(equi, "{");
                        sprintf(foo, "%d", x);
                        strcat(equi, foo);
                        strcat(equi, "; ");
                        sprintf(foo, "%d", y);
                        strcat(equi, foo);
                        strcat(equi, "} ");
                        u++;
                    }
                    break;
            }
            if(debug == (char)startFoo){
                strcat(sets, "{");
                sprintf(foo, "%d", x);
                strcat(sets, foo);
                strcat(sets, "; ");
                sprintf(foo, "%d", y);
                strcat(sets, foo);
                strcat(sets, "} ");
                n++;
            }
            if((i%10) == 9){
                strcat(sets, "\n   ");
            }
        }
        printf("%s", sets);
        printf("Numero elementi: %d\n\n", n);
    }
    printf("%s\n", equi);
    printf("   Numero elementi: %d\n\n", u);
}


/*
 * void fillMatrixInitialize(inout char *Matrix, in const size_t rows, in const size_t cols)
 * Data in input una matrice, il numero di colonne e di righe,
 * la funzione ha il compito di scorrere la matrice e riempire
 * le celle di quest'ultima con il carattere ' '.
 *  Complessità:
 * T(n*m) - O(n*m) - S(n*m)
*/
void fillMatrixInitialize(inout char *Matrix, in const size_t rows, in const size_t cols){
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            *(Matrix + i*cols + j) = ' ';
        }
    }
}

/*
 * void fillMatrixCenter(in char *Matrix, in const size_t rows, in const size_t cols, in struct elemento centriMatrix[], in const size_t n_centri)
 * Data in input una matrice, il numero di colonne, di righe, un array
 * dei centri da inserire e il numero di centri, la funzione ha il compito
 * di mettere in posizioni casuali i centri specificati da n_centri. L'array
 * centriMatrix[] è stato creato ai fini di semplificare il salvataggio delle coordinate
 * dei centri.
 * Complessità:
 * T(c) - O(c) - S(c)
*/
void fillMatrixCenter(in char *Matrix, in const size_t rows, in const size_t cols, inout struct elemento centriMatrix[], in const size_t n_centri){
    for (int i = 0; i < n_centri; i++){
        int check = 0;
        while(check != 1){                              //esegui il while finché la flag check non è settata ad 1
            int row = randGen(0, SIZE-1);
            int col = randGen(0, SIZE-1);
            if (*(Matrix + row * cols + col) == ' '){   //se nella cella in posizione Matrix[row][col]
                *(Matrix + row * cols + col) = '1'+i;   //non è occupata da un elemento, allora il centro può
                centriMatrix[i].x = row;                //essere posizionato in questa posizione
                centriMatrix[i].y = col;                //e la flag check può essere settata a 1. Se la posizione
                check = 1;                              //è gia occupata allora si ripete la generazione casuale finché
            }                                           //non viene trovata una casella libera
        }
    }
}

/*
 * void fillMatrixElement(in char *Matrix, in const size_t rows, in const size_t cols, in const size_t n_elementi, inout struct elemento elementiMatrix[])
 * Data in input una matrice, il numero di colonne, di righe, un array
 * degli elementi da inserire e il numero di elementi, la funzione ha il compito
 * di mettere in posizioni casuali gli elementi specificati da spawn. L'array
 * elementiMatrix[] è stato creato ai fini di semplificare il salvataggio delle coordinate
 * degli elementi, poiché se non sapessimo la posizione degli elementi sarebbe necessario
 * scorrere tutta la matrice alla ricerca di elementi da determinare, mentre così facendo
 * riduciamo la complessita di tempo da SIZE*SIZE ad n_elementi.
 * Complessità:
 * T(e) - O(e) - S(e)
*/
void fillMatrixElement(in char *Matrix, in const size_t rows, in const size_t cols, in const size_t n_elementi, inout struct elemento elementiMatrix[]){
    for (int i = 0; i < n_elementi; i++){
        int check = 0;
        while(check != 1){                              //esegui il while finché la flag check non è settata ad 1
            int row = randGen(0, SIZE-1);
            int col = randGen(0, SIZE-1);
            if (*(Matrix + row * cols + col) == ' '){   //se nella cella in posizione Matrix[row][col]
                *(Matrix + row * cols + col) = 'X';     //non è occupata da un elemento, allora l'elemento può
                elementiMatrix[i].x = row;              //essere posizionato in questa posizione
                elementiMatrix[i].y = col;              //e la flag check può essere settata a 1. Se la posizione
                check = 1;                              //è gia occupata allora si ripete la generazione casuale finché
            }                                           //non viene trovvta una casella libera
        }
    }
}

/*
 * void fillMatrix(in char *Matrix, in const size_t rows, in const size_t cols, in const size_t n_elementi, in struct elemento centriMatrix[], in const size_t n_centri, inout struct elemento elementiMatrix[])
 * Questa funzione ha il compito di assemblare la matrice di inizio, quindi
 * pone il contenuto di tutte le celle uguale a ' ', poi riempie la matrice in modo casuale
 * di elementi 'X' e infine inserisce in modo casuale i centri. Come paramentri richiede
 * l'insieme di tutti i paramentri delle tre funzioni chiamate, quindi la matrice, il numero
 * di colonne, di righe, il numero di elementi, l'array degli elementi, il numero di centri e l'array dei centri.
 * Complessità:
 * T((n*m)+e+c) - O((n*m)+e+c) - S((n*m)+e+c)
*/
void fillMatrix(in char *Matrix, in const size_t rows, in const size_t cols, in const size_t n_elementi, in struct elemento centriMatrix[], in const size_t n_centri, inout struct elemento elementiMatrix[]){
    fillMatrixInitialize(Matrix, rows, cols);
    fillMatrixElement(Matrix, rows, cols, n_elementi, elementiMatrix);
    fillMatrixCenter(Matrix, rows, cols, centriMatrix, n_centri);
}

/*
 * float calculateEuclideanDistance(int x1, int y1, int x2, int y2)
 * Date in input le coordinate di due punti, la funzione ritorna
 * la distanza geometrica euclidea tra i due punti.
 * Complessità:
 * T(1) - O(1) - S(1)
*/
float calculateEuclideanDistance(int x1, int y1, int x2, int y2){
    int difx = x2-x1;
    int dify = y2-y1;
    return sqrt((difx*difx) + (dify*dify));
}

/*
 * int calculateElementDistanceFromCenter(in size_t x, in size_t y, in struct elemento centriMatrix[], in const size_t n_centri)
 * Date in input le coordinate di un punto, l'array dei centri e il numero
 * dei centri, la funzione determina il centro più vicino al punto esaminato,
 * ritornando poi il numero del centro (relativo all'array). Se i centri
 * sono tutti equidistanti, allora la funzione ritornerà -1.
 * Complessità:
 * T(c) - O(c) - S(c)
*/
int calculateElementDistanceFromCenter(in size_t x, in size_t y, in struct elemento centriMatrix[], in const size_t n_centri){
    float delta = 0.001;
    int centroVicino = 0;
    float app = 0.0;
    float distance = 0.0;

    distance = calculateEuclideanDistance(centriMatrix[0].x, centriMatrix[0].y, x, y);  //Calcola la distanza tra il punto e il primo centro contenuto nell'array
    for(int i = 1; i < n_centri; i++) {                                                               //il primo centro contenuto nell'array l'indice parte ad 1
        app = calculateEuclideanDistance(centriMatrix[i].x, centriMatrix[i].y, x, y);  //poiché il primo elemento già è stato calcolato. Se la distanza precedentemente calcolata
        if (distance > app) {                                                                         //è maggiore della distanza appena calcolata allora aggiorna il centro più vicino
            distance = app;                                                                           //e aggiorna la distanza precedente alla distanza appena calcolata.
            centroVicino = i;                                                                         //Poiché non disponiamo della certezza assoluta per quanto riguarda la precisione dei numeri float
        } else if (abs(distance - app) < delta) {                                                  //eseguiamo un'approssimazione dove poniamo come valore delta un valore arbitrario
            centroVicino = -1;                                                                        //ed eseguiamo un confronto con il valore assoluto (che ci assicura un valore positivo) della differenza delle distanze e il delta.
        }                                                                                             //Se la differenza risulta minore del delta, vuol dire che i valori sono relativamente simili e vicini da essere definiti uguali.
    }                                                                                                 //Se questa condizione si verifica per tutti i confronti dei centri allora vuol dire che il valore è equidistante da tutti i centri.
    return centroVicino;
}

/*
 * void findMatrixElementGroup(in char *Matrix, in const size_t rows, in const size_t cols, in const size_t n_elementi, struct elemento centriMatrix[], in size_t n_centri, in struct elemento elementiMatrix[])0
 * Questa funzione ha il compito aggiornare il contenuto della cella della matrice
 * relativa alle coordinate dell'elemento preso in considerazione assegnando così
 * l'appartenenza all'insieme a seconda del centro più vicino, ottenuto con
 * la funzione calculateElementDistanceFromCenterCome paramentri richiede la matrice,
 * il numero di colonne, di righe, il numero di elementi, l'array degli elementi,
 * il numero di centri e l'array dei centri.
 * Complessità:
 * T(e) - O(e) - S((n*m)+e+c)
*/
void findMatrixElementGroup(in char *Matrix, in const size_t rows, in const size_t cols, in const size_t n_elementi, struct elemento centriMatrix[], in size_t n_centri, in struct elemento elementiMatrix[]){
    int centroVicino = 0;
    for(int i = 0; i < n_elementi; i++){
        centroVicino = calculateElementDistanceFromCenter(elementiMatrix[i].x, elementiMatrix[i].y, centriMatrix, n_centri);
        //se il la funzione per il calcolo della distanza ha ritornato -1 vuol dire che l'elemento
        //esaminato è equidistante, quinddi la cella va a aggiornata con 'U'
        if(centroVicino == -1){
            *(Matrix + elementiMatrix[i].x*cols + elementiMatrix[i].y) = 'U';
        }
        else{
            //se il la funzione per il calcolo della distanza ha ritornato un risulato diverso da -1 vuol dire che l'elemento
            //esaminato è vicino ad un qualche centro. Visto che il return della funzione calculateElementDistanceFromCenter è
            //l'indice del vettore degli insiemi, quindi un numero che va da 0 a n, è bastato porre la cella uguale ad 'A'+centroVicino
            //poiché anche se centroVicino fosse 0, quindi centro1 (insieme A), la cella sarà uguale a 'A'+0, mentre se centro vicino
            //fosse 1, quindi centro2 (insieme B) la cella sarà uguale a 'A'+1, cioè 65+1, 66, quindi 'B'
            *(Matrix + elementiMatrix[i].x*cols + elementiMatrix[i].y) = 'A'+centroVicino;
        }
    }
}

int main() {
    //srand(0xA113);
    srand(time(NULL));

    //definizione variabili
    char Matrix[SIZE][SIZE];
    struct elemento centriMatrice[CENTRI];
    struct elemento elementiMatrice[SPAWN];

    //inizializzazione matrice e stampa della prima fase
    printf("PROGETTO D'ESAME DI LABORATORIO DI PROGRAMMAZIONE I - 12 CFU"
           "\nVittorio Picone - 0124002584"
           "\nParte 1 - Classificazione"
           "\n\nPremere un pulsante qualsiasi per continuare...\n");
    getchar();

    printf("Inizializzazione Matrice\n");
    fillMatrix(Matrix, SIZE, SIZE, SPAWN, centriMatrice, CENTRI, elementiMatrice);
    printCharMatrix(Matrix, SIZE, SIZE);

    printf("\n");

    getchar();

    printf("Classificazione Elementi\n");
    //esecuzione dell'algoritmo di determinazione dell'appertenenza degli elementi agl'insiemi e stampa della seconda fase
    findMatrixElementGroup(Matrix, SIZE, SIZE, SPAWN, centriMatrice, CENTRI, elementiMatrice);
    printCharMatrix(Matrix, SIZE, SIZE);

    getchar();

    printf("\n|--------------------------------------------------------------------------------------------------------------------|");
    printf("\n");
    printAllSets(Matrix, SIZE, elementiMatrice, SPAWN, centriMatrice, CENTRI);
    printf("\n");
    printCentersPositions(centriMatrice, CENTRI);
    printf("\n\n\n");

    getchar();

    return 0xA113;
}
