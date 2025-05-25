/*ATTENZIONE: Nel codice sono presenti comandi system
              Implementati per la pulizia del terminale
              Potrebbero creare conflitti o problemi di vari natura
              "Annullarli" nel caso della presenza di quest'ultimi*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Veicolo.h"

/*-- FUNZIONI RELATIVE AI VEICOLI --*/

/*---------------------------------------------------------------------------------------------------------------- 
 * Funzione: riempiVeicoli
 * -----------------------
 * Prende in input l'oggetto veicolo e il puntatore al file .txt contenente i dati dei veicoli
 * Riempie l'oggetto veicolo con i dati contenuti nel file 
 * 
 * Specifica sintattica:
 *      void riempiVeicoli(veicolo, char*) -> void
 *
 * Parametri:
 *      v:        oggetto veicolo
 *      nomefile: file Veicoli.txt
 * 
 * Specifica semantica:
 *      riempiVeicoli(v, nomefile) -> void
 * 
 * Pre-condizione:
 *      Il file txt deve contenere i vari dati dei Veicoli e l'oggetto veicolo esistere
 * 
 * Post-condizione:
 *      Non ritorna nessun valore, oggetto veicolo riempito
 * 
 * Ritorna:
 *      Nessun valore 
 * 
 * Effetti collaterali:
 *      Modifica il contenuto nell'oggetto veicolo
 *      Se il file è vuoto, la funzione potrebbe dare comportamento indefinito senza opportuni controlli
 * ---------------------------------------------------------------------------------------------------------------- 
 */

 int riempiVeicoli (veicolo v){

    FILE *file;
    char buffer [1024];
    static int indiceVeicolo=0; 
    int j = 0;

    file = fopen ("Veicoli.txt", "r");
    if (file == NULL){
        system("cls | clear");
        perror ("ERRORE: Apertura file veicoli fallita.\n");
        return 0;
    }

    do {
        fgets (buffer, sizeof (buffer), file);
        j++;
    } while (j <= indiceVeicolo);

    char* token = strtok (buffer, ";");
    if (!(controlloToken (token))){
        chiudiFile(file);
        return 0;
    }

    v->tipoVeicolo = malloc ( (strlen (token)+1) * sizeof (char));
    if (v->tipoVeicolo == NULL){
        perror ("ERRORE: Allocazione memoria per il tipo del veicolo fallita.\n");
        chiudiFile(file);
        return 0;
    }
    strcpy (v->tipoVeicolo, token);

    token = strtok (NULL, ";");
    if (!(controlloToken (token))){
        chiudiFile(file);
        return 0;
    }

    v->modello = malloc ( (strlen (token)+1) * sizeof (char));
    if (v->modello == NULL){
        chiudiFile(file);
        perror ("ERRORE: Allocazione memoria per il modello del veicolo fallita.\n");
        return 0;
    }
    strcpy (v->modello, token);

    token = strtok (NULL, ";");
    if (!(controlloToken (token))){
        chiudiFile(file);
        return 0;
    }

    v->colore = malloc ( (strlen (token)+1) * sizeof (char));
    if (v->colore == NULL){ 
        chiudiFile(file);
        perror ("ERRORE: Allocazione memoria per il colore del veicolo fallita.\n");
        return 0;
    }
    strcpy (v->colore, token);

    token = strtok (NULL, ";");
    if (!(controlloToken (token))){
        chiudiFile(file);
        return 0;
    }

    v->targa = malloc ( (strlen (token)+1) * sizeof (char));
    if (v->targa == NULL){
        chiudiFile(file);
        perror ("ERRORE: Allocazione memoria per la targa del veicolo fallita.\n");
        return 0;
    }
    strcpy (v->targa, token);

    token = strtok (NULL, ";");
    if (!(controlloToken (token))){
        chiudiFile(file);
        return 0;
    }

    v->postiOmologati = atoi (token);
    
    token = strtok (NULL, ";");
    if (!(controlloToken (token))){
        chiudiFile(file);
        return 0;
    }

    v->Combustibile = malloc ( (strlen(token)+1) * sizeof (char));
    if (v->Combustibile == NULL){
        chiudiFile(file);
        perror ("ERRORE: Allocazione memoria per il tipo di combustibile del veicolo fallita.\n");
        return 0;
    }
    strcpy (v->Combustibile, token);

    token = strtok (NULL, ";");
    if (!(controlloToken (token))){
        chiudiFile(file);
        return 0;
    }

    v->annoDiImmatricolazione = atoi (token);

    token = strtok (NULL, ";");
    if (!(controlloToken (token))){
        chiudiFile(file);
        return 0;
    }

    v->CostoNoleggioOrario = atoi (token);
    
    if (!(riempiOrari (v))){
        chiudiFile(file);
        perror("ERRORE: Riempimento degli orari dei veicoli fallito.");
        return 0;
    };

    indiceVeicolo++;

    return chiudiFile(file);
}

/*---------------------------------------------------------------------------------------------------------------- 
 * Funzione: stampaVeicoli
 * -----------------------
 * Stampa a video i dati di un oggetto veicolo tra cui anche gli intervalli orari con la loro disponibilità (richiamo ad altre due funzioni) 
 * 
 * Specifica sintattica:
 *      void stampaVeicoli(veicolo) -> void
 *
 * Parametri:
 *      v: oggetto veicolo
 * 
 * Specifica semantica:
 *      stampaVeicoli(v) -> void
 * 
 * Pre-condizione:
 *      L'oggetto veicolo deve contenere dei dati diversi da NULL
 *      La funzione stampaOrari deve esistere
 * 
 * Post-condizione:
 *      Non ritorna nessun valore
 * 
 * Ritorna:
 *      Nessun valore 
 * 
 * Effetti collaterali:
 *      Nessun effetto collaterale
 * ---------------------------------------------------------------------------------------------------------------- 
 */

 void stampaVeicolo (veicolo v){
    printf("Tipo Veicolo: %s\nModello: %s\nColore: %s\nTarga: %s\nPosti Omologati: %d\nCombustibile: %s\nAnno di immatricolazione: %d\nCosto Noleggio: %.2f euro/h\n\n", v->tipoVeicolo, v->modello, v->colore, v->targa, v->postiOmologati, v->Combustibile,v->annoDiImmatricolazione, v->CostoNoleggioOrario);
}

/*---------------------------------------------------------------------------------------------------------------- 
 * Funzione: liberaVeicolo
 * -----------------------
 *  Libera la memoria dell'oggetto veicolo
 * 
 * Specifica sintattica:
 *      void liberaVeicolo(veicolo) -> void
 *
 * Parametri:
 *      v: oggetto veicolo
 *  
 * Specifica semantica:
 *      liberaVeicolo(v) -> void
 * 
 * Pre-condizione:
 *      Memoria allocata per l'oggetto veicolo
 * 
 * Post-condizione:
 *      Memoria liberata correttamente
 * 
 * Ritorna:
 *      Nessun valore 
 * 
 * Effetti collaterali:
 *      L'oggetto veicolo non ha più dati presenti in memoria
 * ---------------------------------------------------------------------------------------------------------------- 
 */

 void liberaVeicolo (veicolo v){
    if (v->colore) { free(v->colore); }
    if (v->Combustibile) { free(v->Combustibile); }
    if (v->modello) { free(v->modello); }
    if (v->targa){ free(v->targa); }
    if (v->tipoVeicolo){ free(v->tipoVeicolo); }
}

/*-- FUNZIONI RELATIVE AL NOLEGGIO --*/

/*---------------------------------------------------------------------------------------------------------------- 
 * Funzione: costoNoleggio
 * -----------------------
 * Calcola quanto costa il noleggio in un orario scelto dall'utente con eventuale sconto 
 * 
 * Specifica sintattica:
 *      float costoNoleggio(veicolo, int) -> float
 *
 * Parametri:
 *      v: oggetto veicolo
 *      k: indice dell'orario scelto
 * 
 * Specifica semantica:
 *      costoNoleggio(v, k) -> costo_del_Noleggio
 * 
 * Pre-condizione:
 *      L'oggetto veicolo deve esistere e contenere dati sugli intervalli orari
 *      La funzione verificaSconto deve esistere (oppure eliminata in caso di sconti non applicabili)
 * 
 * Post-condizione:
 *      Restituisce il costo totale del noleggio dell'orario scelto dall'utente
 * 
 * Ritorna:
 *      Ritorna un tipo float del costo totale
 * 
 * Effetti collaterali: 
 *      Nessun effetto collaterale
 * ---------------------------------------------------------------------------------------------------------------- 
 */

float costoNoleggio (veicolo v, int k){

    int minutiTotali, ore, minuti;
    float inizio = v->orari[k].inizio, fine = v->orari[k].fine;

    ore = (int)inizio;
    minuti = round((inizio-ore)*100);
    minutiTotali = (ore*60) + minuti; // MINUTI TOTALI SOLO INIZIALI

    ore = (int)fine;
    minuti = round((fine-ore)*100);
    minutiTotali = (ore*60)+minuti - minutiTotali; // MINUTI TOTALI DEL TEMPO DI NOLEGGIO

    return minutiTotali * ((v->CostoNoleggioOrario)/60) * verificaSconto(v,k);
}


/*---------------------------------------------------------------------------------------------------------------- 
 * Funzione: verificaSconto
 * -----------------------
 * La funzione verifica la possibilità di un sconto in determinati intervalli orari prestabiliti e restituisce un tipo float
 * riguardante lo sconto da applicare al calcolo del costo totale del noleggio
 * 
 * Specifica sintattica:
 *      float verificaSconto(veicolo, int) -> float
 *
 * Parametri:
 *      v: oggetto veicolo
 *      k: indice dell'orario scelto
 * 
 * Specifica semantica:
 *      verificaSconto(v, k) -> Percentuale_di_Sconto
 * Pre-condizione:
 *      L'oggetto veicolo deve esistere e contenere i dati sugli intervalli orari
 *      
 * Post-condizione:
 *      Restituisce la percentuale di sconto se l'orario della prenotazione corrisponde all'intervallo
 *      Altrimenti restituisce 1
 * 
 * Ritorna:
 *      Restituisce un tipo float della percentuale di sconto
 *      Altrimenti float di 1.0
 *      
 * Effetti collaterali:
 *      Nessun effetto collaterale 
 * ---------------------------------------------------------------------------------------------------------------- 
 */

float verificaSconto (veicolo v, int k){
      float orario = v->orari[k].inizio;
      if (orario >= 20.00 ){
        return 0.7; //Sconto del 30% se l'orario prenotato è dalle 20.00 in poi
      } else if (orario < 9) {
        return 0.85; //Sconto del 15% se l'orario prenotato è prima delle 9.00
      } else return 1.0;
}

/*-- FUNZIONI RELATIVE AGLI ORARI --*/

/*---------------------------------------------------------------------------------------------------------------- 
 * Funzione: riempiOrari
 * -----------------------
 * Prende in input l'oggetto veicolo e il puntatore al file .txt contenente i dati degli intervalli orari
 * Riempie l'oggetto veicolo con i dati contenuti nel file 
 * 
 * Specifica sintattica:
 *      void riempiOrari(veicolo,char*)->void
 *
 * Parametri:
 *             v: oggetto veicolo
 *      nomefile: file Orari.tx
 * 
 * Specifica semantica:
 *      riempiOrari(v, nomefile)-> void
 *       
 * Pre-condizione:
 *       Il file txt deve contenere i vari dati degli Orari e l'oggetto veicolo esistere
 * 
 * Post-condizione:
 *      Non ritorna nessun valore, oggetto Orari riempito
 * 
 * Ritorna: 
 *      Nessun valore
 * 
 * Effetti collaterali:
 *      Modifica il contenuto nell'oggetto veicolo
 *      Se il file è vuoto, la funzione potrebbe dare comportamento indefinito senza opportuni controlli
 * ---------------------------------------------------------------------------------------------------------------- 
 */

int riempiOrari (veicolo v){
    FILE *file;
    char buffer [1024];

    file = fopen ("Orari.txt", "r");
    if (file == NULL){
        system("cls | clear");
        perror ("ERRORE: Apertura file degli orari fallita.\n");
        return 0;
    }

    while (fgets (buffer, sizeof (buffer), file) != NULL){
        char* token = strtok (buffer, ";");
        if (!(controlloToken (token))){
            chiudiFile(file);
            return 0;
        }

        for (int k=0; k<8; k++){
            v->orari[k].inizio = atof (token);
            
            token = strtok (NULL, ";");
            if (!(controlloToken (token))){
                chiudiFile(file);
                return 0;
            }

            v->orari[k].fine = atof (token);

            token = strtok (NULL, ";");
            if (!(controlloToken (token))){
                chiudiFile(file);
                return 0;
            }

            v->orari[k].Disponibilita = atoi (token);

            token = strtok (NULL, ";");
            if (!(controlloToken (token))){
                chiudiFile(file);
                return 0;
            }
        }
    }
    return chiudiFile(file); 
}


/*---------------------------------------------------------------------------------------------------------------- 
 * Funzione: verificaDisponibilità
 * -----------------------
 * Verifica che un veicolo in un determinato orario sia disponibile attraverso un modulo 2 (se 1 allora non disponibile altrimenti disponibile)
 * Stampa a video disponibile o meno
 * 
 * Specifica sintattica:
 *      void verificaDisponibilità (veicolo, int) -> void
 *
 * Parametri:
 *      v: oggetto veicolo
 *      k: indice orario scelto
 * 
 * Specifica semantica:
 *      verificaDisponibilità(v, k) -> void
 *       
 * Pre-condizione:
 *      L'oggetto veicolo deve esistere e contenere i dati della struct Orari
 *       
 * Post-condizione:
 *      Non ritorna nessun valore
 * 
 * Ritorna: 
 *      Nessun valore
 * 
 * Effetti collaterali:
 *      Nessun effetto collaterale   
 * ----------------------------------------------------------------------------------------------------------------     
 */

void stampaDisponibilita (veicolo v, int k){
    if ((v->orari[k].Disponibilita)%2 == 1){
        printf ("Non Disponibile\n");
    }
    else {
        printf ("Disponibile\n");
    }
}

int verificaDisponibilita(veicolo v, int indiceOrario){
    if (v->orari[indiceOrario].Disponibilita == 0){
        return 1;
    }
        return 0;
}
/*---------------------------------------------------------------------------------------------------------------- 
 * Funzione: modificaDisponibilità
 * -----------------------
 * Va a modificare nel campo disponibilità il suo valore a 1 quando chiamata
 * 
 * Specifica sintattica:
 *      void modificaDisponibilità(veicolo, int) -> void
 *
 * Parametri:
 *      v: oggetto veicolo
 *      k: indice orario scelto
 * 
 * Specifica semantica:
 *       modificaDisponibilità(v, k) -> void
 * 
 * Pre-condizione:
 *      L'oggetto veicolo deve esistere e contenere dati nella struct Orari
 *       
 * Post-condizione:
 *      Non ritorna nessun valore, Campo Disponibilità cambiato
 * 
 * Ritorna: 
 *      Nessun valore
 * 
 * Effetti collaterali:
 *       Cambiato il valore nel campo Disponibilità della struct Orario
 * ---------------------------------------------------------------------------------------------------------------- 
 */

void modificaDisponibilita (veicolo v, int k){
    v->orari[k].Disponibilita = 1;
}

/*-----------------------------------------------------------------------------------------------------------------
 * Funzione: stampaOrari
 * ----------------------------------------------------------------------------------------------------------------
 * Stampa a video l'intervallo orario scelto dall'utente con la sua disponibilità (Non disponibile o Disponibile)
 * 
 * Specifica sintattica:
 *      void stampaOrari(veicolo) -> void
 *
 * Parametri:
 *      v: oggetto veicolo
 * 
 * Specifica semantica:
 *      stampaOrari(v) -> void
 *       
 * Pre-condizione:
 *      L'oggetto deve esistere e contenere dati
 *      verificaDisponibilità deve esistere 
 *       
 * Post-condizione:
 *      Nessun valore di ritorno
 * 
 * Ritorna: 
 *      Nessun valore
 * 
 * Effetti collaterali:
 *      Nessun effetto collaterale     
 * ---------------------------------------------------------------------------------------------------------------- 
 */

void stampaOrari (veicolo v){
        printf("\nLista degli orari del veicolo scelto\n\n");
        for (int k=0; k<8; k++){
            printf (" (%d) %.2f-%.2f ", k, v->orari[k].inizio, v->orari[k].fine);
        stampaDisponibilita(v, k);
        }
}

/*--Funzioni di supporto--*/

/*-----------------------------------------------------------------------------------------------------------------
 * Funzione: controllotoken
 * ----------------------------------------------------------------------------------------------------------------
 * Controllo di eventuali errori nella funzione strtok della libreria string.h 
 * 
 * Specifica sintattica:
 *      void controllotoken(char*, veicolo, FILE*)-> void
 *
 * Parametri:
 *      token: stringa
 *      v: oggetto veicolo
 *      file: puntatore a file
 * 
 * Specifica semantica:
 *      controllotoken(token, v, file)-> void 
 *       
 * Pre-condizione:
 *      token deve esistere
 *       
 * Post-condizione:
 *      Se token == NULL, libera memoria e chiude file
 * 
 * Ritorna: 
 *      Nessun valore     
 * 
 * Effetti collaterali:
 *      Nessun effetto collaterale
 * ---------------------------------------------------------------------------------------------------------------- 
 */

int controlloToken (char* token){ 
    if (token == NULL){
        system("cls | clear");
        printf("ERRORE: Ottenimento token fallito.\n");
        return 0;
    }
    return 1;
}

int chiudiFile(FILE* file){ 
    if (fclose (file) != 0){
        perror ("ERRORE: Chiusura del file fallita.\n");
        return 0;
    }
    return 1;
}