/*
 * Vittorio Picone - 0124002584
 * PROGETTO D’ESAME DI LABORATORIO DI PROGRAMMAZIONE I 12 CFU - Parte 2 - Dizionario dei contrari
 *
 * Si crei un dizionario ordinato contenente come elementi delle parola e
 * ed i suoi contrari, massimo cinque.Si svolga un programma che permetta
 * all'utente di inserire una frase e cambiare le parole della frase con i
 * contrari delle stesse a proprio piacimento.
*/

#include "headers.h"

#define SIZE_DICTIONARY 15
#define SIZE_INPUT      512
#define TRUE            1
#define FALSE           0

/* struct parola
 * La struct contiene una stringa generica
 * di massimo 128 caratteri.
*/
struct parola{
    char text[128];
};

/* struct elementoDizionario
* La struct invece si riferisce
* effetivamente alla parola contenuta all'interno
* del nostro dizionario. Ho deciso di basarmi su una
* struct per semplificare poi la gestione dei contrari.
*/
struct elementoDizionario{
    struct parola sostantivo;
    struct parola contrari[5];
    int n_contrari;
};
//-----------------------------------------------

/*
 * void printDizionario(in struct elementoDizionario Dizionario[], in const int n_parole)
 * Funzione che stampa gli elementi del dizionario e i contrari
 * come elenco puntato
 * Complessità:
 * T(n*m) - O(n*m) - S(n)
*/
void printDizionario(in struct elementoDizionario Dizionario[], in const int n_parole){
    for(int i = 0; i < n_parole; i++){
        printf("%d. %s\n", i+1, Dizionario[i].sostantivo.text);
        for(int k = 0; k < Dizionario[i].n_contrari; k++) {
            printf(" %d. %s\n", k+1, Dizionario[i].contrari[k].text);
        }
        printf("\n");
    }
}

/*
 * void swapAntonyms(in struct parola *xp, in struct parola *yp)
 * Funzione di swap creato per l'ordinamento
 * con selezione di minimo per i contrari
 * delle parole
 * Complessità:
 * T(1) - O(1) - S(1)
*/
void swapAntonyms(in struct parola *xp, in struct parola *yp){
    struct parola temp = *xp;
    *xp = *yp;
    *yp = temp;
}

/*
 * void sortAntonyms(inout struct parola arr[], in int n_contrari)
 * Funzione che ordina un array di parole, usato all'interno
 * del programma per il sorting dei contrari con algoritmo con
 * selezione di minimo.
 * Complessità:
 * T(n*n) - O(n*n) - S(n)
*/
void sortAntonyms(inout struct parola arr[], in int n_contrari){
    int min_idx;

    for (int i = 0; i < n_contrari-1; i++){
        min_idx = i;
        for (int j = i + 1; j < n_contrari; j++){
            if (strcmp(arr[j].text, arr[min_idx].text) < 0) {
                min_idx = j;
            }
        }

        swapAntonyms(&arr[min_idx], &arr[i]);
    }
}

/*
 * void sortAllAntonyms(inout struct elementoDizionario arr[], in int n)
 * Funzione che ordina tutti i contrari di tutte la parole
 * nel dizionario.
 * Complessità:
 * T(n) - O(n) - S(n)
*/
void sortAllAntonyms(inout struct elementoDizionario arr[], in int n){
    for(int i = 0; i < n; i++){
        sortAntonyms(arr[i].contrari, arr[i].n_contrari);
    }
}

/*
 * void swapWords(in struct elementoDizionario *xp, in struct elementoDizionario *yp)
 * Funzione di swap creato per l'ordinamento
 * con selezione di minimo per gli elementi
 * del dizionario
 * Complessità:
 * T(1) - O(1) - S(1)
*/
void swapWords(in struct elementoDizionario *xp, in struct elementoDizionario *yp)
{
    struct elementoDizionario temp = *xp;
    *xp = *yp;
    *yp = temp;
}

/*
 * void sortWords(inout struct elementoDizionario arr[], in int n, in int antonymsSort)
 * Funzione che ordina gli elementi nel dizionario tramite
 * algoritmo di ordinamento di selezione di minimo.
 * Come input richiede anche una variabile in funzione di flag "antonymsSort"
 * dove se viene passato un numero diverso da 0, ad ogni passaggio
 * di elemento ordinera' i suoi contrari
 * Complessità:
 * T(n*n) - O(n*n) - S(n)
*/
void sortWords(inout struct elementoDizionario arr[], in int n, in int antonymsSort){
    int min_idx;
    switch (antonymsSort) {
        case 0:
            for (int i = 0; i < n - 1; i++) {
                min_idx = i;
                for (int j = i + 1; j < n; j++) {
                    if (strcmp(arr[j].sostantivo.text, arr[min_idx].sostantivo.text) > 0) {
                        min_idx = j;
                    }
                }
                swapWords(&arr[min_idx].sostantivo.text, &arr[i].sostantivo.text);
            }
            break;
        default:
            for (int i = 0; i < n - 1; i++) {
                min_idx = i;
                for (int j = i + 1; j < n; j++) {
                    if (strcmp(arr[j].sostantivo.text, arr[min_idx].sostantivo.text) < 0) {
                        min_idx = j;
                    }
                }
                swapWords(&arr[min_idx].sostantivo.text, &arr[i].sostantivo.text);
                sortAntonyms(arr[i].contrari, arr[i].n_contrari);
            }
            sortAntonyms(arr[n - 1].contrari, arr[n - 1].n_contrari);
            break;
    }
}

/*
 * void loadDictionaryFromFile(out struct elementoDizionario Dizionario[], in const int n_parole, in char nome_file[], in int printLog)
 * Funzione che stampa riempe il dizionario tramite file con questa struttura:
 *
 * Parola
 * Numero contrari
 * Contrario
 * eg:
 * abile
 * 2
 * inabile
 * inefficiente
 *
 * Come input richiede anche una variabile in funzione di flag "printLog"
 * dove se viene passato un numero diverso da 0, stamperà ogni riga
 * letta dal file
 *
 * Complessità:
 * T(n) - O(n) - S(n+m)
*/
void loadDictionaryFromFile(out struct elementoDizionario Dizionario[], in const int n_parole, in char nome_file[], in int printLog){
    FILE* filePointer;
    const int bufferLength = 255;
    char buffer[255];

    filePointer = fopen(nome_file, "r");

    int i = -1;
    int checkAntonyms = 0;
    int startCheckAntonyms = 0;
    int indexAntonyms = 0;

    while(fgets(buffer, bufferLength, filePointer)) {
        if(buffer[0] >= '0' && buffer[0] <= '5'){
            checkAntonyms = atoi(buffer);
            checkAntonyms;
            indexAntonyms = 0;
            Dizionario[i].n_contrari = 0;
        }
        else if(checkAntonyms == 0){
            i++;
            buffer[strcspn(buffer, "\n")] = 0;
            strcpy(Dizionario[i].sostantivo.text, buffer);
        }
        else if(checkAntonyms != 0) {
            buffer[strcspn(buffer, "\n")] = 0;
            strcpy(Dizionario[i].contrari[indexAntonyms].text, buffer);
            Dizionario[i].n_contrari++;
            indexAntonyms++;
            checkAntonyms--;
        }

        if(printLog != 0) {
            printf("%s\n", buffer);
        }
    }

    fclose(filePointer);
}

/*
 * int searchBinaryWord(char chiave[], struct elementoDizionario Dizionario[], int primo, int ultimo)
 * Funzione ricorsiva che applica l'algoritmo di ricerca binaria
 * per cercare una parola all'interno del dizionario restituendo l'indice.
 * Se la funzione ritorna -1, allora la parola non è presente nel dizionario
 * Complessità:
 * T(log(n)) - O(log(n)) - S(n+m)
*/
int searchBinaryWord(in char chiave[], in struct elementoDizionario Dizionario[], in int primo, in int ultimo){
    int mediano;
    if (primo > ultimo){
        return -1;
    }
    else{
        mediano = (primo + ultimo) / 2;
        int app = strcmp(chiave, Dizionario[mediano].sostantivo.text);
        if (app == 0) {
            return mediano;
        } else if (app < 0) {
            return searchBinaryWord(chiave, Dizionario, primo, mediano - 1);
        } else {
            return searchBinaryWord(chiave, Dizionario, mediano + 1, ultimo);
        }
    }
}

int main(){
    srand(time(NULL));

    char input_str_user[512];
    char output_str_user[512];
    int scelta = 0;

    struct elementoDizionario dizionario[SIZE_DICTIONARY];
    loadDictionaryFromFile(dizionario, SIZE_DICTIONARY, "words.txt", FALSE);
    sortWords(dizionario, SIZE_DICTIONARY, TRUE);

    /*
     * Ciclo per il funzionamento del programma, dove viene stampata
     * il menu su schermo per selezionare le varie funzioni del programma
     *
     * 1. Stamperà il tutti gli elementi del dizionario e i suoi contrari
     * 2. Permette di cercare la parola inserita all'interno del dizionario
     * 3. Permette di inserire una frase e di scambiare le parole (se presenti
     *    nel dizionario) con i propri contrari.
     * 4. Il programma termina.
    */
    while(scelta != 4){
        clearScreen();
        printf("|----- PROGETTO D'ESAME DI LABORATORIO DI PROGRAMMAZIONE I - 12 CFU -----|\n"
               "|--------------------- Vittorio Picone - 0124002584 ---------------------|\n"
               "|------------------ Parte 2 - Dizionario dei contrari -------------------|\n"
               "1. Stampa Dizionario\n"
               "2. Cerca parola\n"
               "3. Sostituzione parole in una frase\n"
               "4. Esci\n");
        scanf("%d", &scelta);
        printf("\n\n\n");
        switch(scelta){
            case 1:
                clearScreen();

                printDizionario(dizionario, SIZE_DICTIONARY);

                getchar();
                break;
            case 2:
                clearScreen();
                getchar();

                printf("|----- 2. Cerca parola  -----|\n"
                       "Inserisci parola da cercare:");
                scanf("%s", input_str_user);

                int i = searchBinaryWord(input_str_user, dizionario, 0, SIZE_DICTIONARY-1);

                if(i == -1){
                    printf("\nParola non trovata nel dizionario!\n");
                }
                else{
                    printf("\n%s\n",dizionario[i].sostantivo.text);
                    for(int k = 0; k < dizionario[i].n_contrari; k++){
                        printf(" %d. %s\n", k+1, dizionario[i].contrari[k].text);
                    }
                    printf("\n");
                }
                getchar();
                break;
            case 3:
                int ntoken = 0;
                char app_input_str_usr[512];

                clearScreen();
                getchar();

                printf("|----- 3. Sostituzione parole in una frase  -----|\n"
                       "Inserisci stringa da sostiuire:");
                fgets(input_str_user, SIZE_INPUT, stdin);
                strcpy(app_input_str_usr, input_str_user);


                /*
                 * Ciclo di funzionamento per -la funzione della sostituzione della parola
                 * 1. La frase viene separata in vari pezzi separati
                 *    contenenti le singole parole.
                 *
                 * 2. Cerca la parola nel dizionario, se la parola
                 *    è stata trovata allora restiisce l'indice
                 *    altrimenti restituisce -1, terminando la
                 *    funzione con errore di parola non trovata
                 *
                 * 3. Se la paorla è stata trovata allora procede a
                 *    mostrare i vari contrari, chiedendo cosa fare:
                 *
                 *    0: Non sostiuire la parola
                 *    n: Sostiuisci la parola con il numero del contrario
                 *    6: Scegli un contrario a caso
                 *
                 *    Ho scelto 0 e 6 come numeri operativi "jolly", poiché
                 *    il massimo che di contrari è 5 e il minimo è 1, quindi
                 *    0 e 6 sono sicuramente inutilizzati.
                 *
                 *    La nuova parola viene aggiunta alla stringa finale.
                 *
                 * 4. Una volta arrivato a fine frase, il programma stamperà
                 *    la frase originale e la nuova frase modificata.
                */
                char *token;
                token = strtok(input_str_user, " ");

                while(token != NULL) {
                    token[strcspn(token, "\n")] = 0;

                    int i = searchBinaryWord(token, dizionario, 0, SIZE_DICTIONARY-1);

                    printf("\n");

                    if(i != -1){
                        printf("%s\n",dizionario[i].sostantivo.text);
                        for(int k = 0; k < dizionario[i].n_contrari; k++){
                            printf(" %d. %s\n", k+1, dizionario[i].contrari[k].text);
                        }

                        int sceltaContrario = 0;
                        int indexContrario = 0;

                        printf("\n"
                               "Con quale contrario vuoi sostiuirla?\n"
                               "0 per non sosituirla, 6 per scegliere un contrario casuale: ");

                        scanf("%d", &sceltaContrario);

                        if(sceltaContrario > dizionario[i].n_contrari && sceltaContrario != 6){
                            sceltaContrario = 0;
                        }
                        else if(sceltaContrario == 6){
                            indexContrario = randGen(0, dizionario[i].n_contrari-1);
                        }
                        else{
                            indexContrario = sceltaContrario-1;
                        }

                        if(sceltaContrario != 0){
                            if(ntoken == 0){
                                strcpy(output_str_user, dizionario[i].contrari[indexContrario].text);
                                strcat(output_str_user," ");
                                ntoken++;
                            }
                            else{
                                strcat(output_str_user,dizionario[i].contrari[indexContrario].text);
                                strcat(output_str_user," ");
                            }
                        }
                        else{
                            if(ntoken == 0){
                                strcpy(output_str_user, token);
                                strcat(output_str_user," ");
                                ntoken++;
                            }
                            else{
                                strcat(output_str_user,token);
                                strcat(output_str_user," ");
                            }
                        }

                    }
                    else{
                        printf("La parola \"%s\" non e' presente nel dizionario!\n", token);
                        if(ntoken == 0){
                            strcpy(output_str_user, token);
                            strcat(output_str_user," ");
                            ntoken++;
                        }
                        else{
                            strcat(output_str_user,token);
                            strcat(output_str_user," ");
                        }
                    }
                    token = strtok(NULL, " ");
                }
                printf("\n"
                       "Frase originale: %s"
                       "Frase formata : %s\n", app_input_str_usr, output_str_user);
                getchar();
                break;
        }
        getchar();
    }
    return 0xA113;
}