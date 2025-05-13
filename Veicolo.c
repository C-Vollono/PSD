#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Veicolo.h"

/*-- FUNZIONI RELATIVE AI VEICOLI --*/

/*
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
 */

 void riempiVeicoli (veicolo v, char* nomefile){

    FILE *file;
    char buffer [200];

    file = fopen ("nomefile", "r");

    if (file == NULL){

        printf ("Errore nell'apertura del file.");
        exit (1);
    }

    while (fgets (buffer, sizeof (buffer), file) != '\n'){

        char* token = strtok (buffer, ";");

        v->tipoVeicolo = malloc (strlen (token)+1 * sizeof (char));

        if (v->tipoVeicolo == NULL){

            perror ("ERRORE TIPO VEICOLO");
            exit (1);
        }

        strcpy (v->tipoVeicolo, token);

        token = strtok (NULL, ";");

        v->modello = malloc (strlen (token)+1 * sizeof (char));

        if (v->modello == NULL){

            perror ("ERRORE MODELLO");
            free (v->tipoVeicolo);
            exit(1);
        }

        strcpy (v->modello, token);

        token = strtok (NULL, ";");

        v->colore = malloc (strlen (token)+1 * sizeof (char));

        if (v->colore == NULL){

            perror ("ERRORE COLORE");
            free (v->modello);
            free (v->tipoVeicolo);
            exit (1);
        }

        strcpy (v->colore, token);

        token = strtok (NULL, ";");

        v->targa = malloc (strlen (token)+1 * sizeof (char));

        if (v->targa == NULL){

            perror ("ERRORE TARGA");
            free (v->modello);
            free (v->tipoVeicolo);
            free (v->colore);
            exit (1);
        }

        strcpy (v->targa, token);

        token = strtok (NULL, ";");

        v->postiOmologati = atoi (token);

        token = strtok (NULL, ";");

        v->Combustibile = malloc (strlen(token)+1 * sizeof (char));

        if (v->Combustibile == NULL){

            perror ("ERRORE COMBUSTIBILE");
            free (v->modello);
            free (v->tipoVeicolo);
            free (v->colore);
            free (v->targa);
            exit (1);
        }

        token = strtok (NULL, ";");

        v->annoDiImmatricolazione = atoi (token);

        token = strtok (NULL, ";");

        v->CostoNoleggioOrario = atoi (token);
    }

    fclose (file);

    if (file != EOF){

        perror ("Errore nella chiusura del file.");
        exit (1);
    }
}

/*
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
 */

 void stampaVeicolo (veicolo v){

    printf("VEICOLO:\nTipo Veicolo: %s\nModello: %s\nColore: %s\nTarga: %s\nPosti Omologati: %d\nCombustibile: %s\nAnno di immatricolazione: %d\nCosto Noleggio: %.2f€/h", v->tipoVeicolo, v->modello, v->colore, v->targa, v->postiOmologati, v->Combustibile,v->annoDiImmatricolazione, v->CostoNoleggioOrario);

    printf ("Fasce Orarie: ");
    stampaOrari (v);
}

/*
 * Funzione: liberaVeicoli
 * -----------------------
 *  Libera la memoria dell'oggetto veicolo
 * 
 * Specifica sintattica:
 *      void liberaVeicoli(veicolo) -> void
 *
 * Parametri:
 *      v: oggetto veicolo
 *  
 * Specifica semantica:
 *      liberaVeicoli(v) -> void
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
 */

void liberaVeicoli (veicolo v){

    for (int i=0; i<10; i++){

        free (v->annoDiImmatricolazione);
        free (v->colore);
        free (v->Combustibile);
        free (v->modello);
        free (v->targa);
        free (v->tipoVeicolo);
        free (v->orari);
    }

    free (v);
}

/*-- FUNZIONI RELATIVE AL NOLEGGIO --*/

/*
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
 */

float costoNoleggio (veicolo v, int k){

    int ore, minuti, tempoNoleggio;

    float inizio = v->orari[k].inizio, fine = v->orari[k].fine;

    minuti = (inizio - (int)inizio)*100;

    ore = (int)inizio;

    tempoNoleggio = ore*3600 + minuti*60;

    minuti = (fine - (int)fine)*100;

    ore = (int)fine;

    tempoNoleggio = ((ore*3600 + minuti*60) - tempoNoleggio)/3600;

    return (tempoNoleggio * v->CostoNoleggioOrario) * verificaSconto(v, k);
}

/*
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
 */

float verificaSconto (veicolo v, int k){ // Restituisce float tra 0.0 a 1.0 che corrisponde alla percentuale di sconto (1- verificaSconto);
      float orario = v->orari[k].inizio;
      if (orario >= 20.00 ){
        return 0.7; //Sconto del 30% se l'orario prenotato è dalle 20.00 in poi
      } else if (orario < 9) {
        return 0.85; //Sconto del 15% se l'orario prenotato è prima delle 9.00
      } else return 1.0;

}

/*-- FUNZIONI RELATIVE AGLI ORARI --*/

/*
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
 */

void riempiOrari (veicolo v, char* nomefile){

    FILE *file;
    char buffer [200];

    file = fopen ("nomefile", "r");

    if (file == NULL){

        perror ("Errore nell'apertura del file.");
        exit (1);
    }

    while (fgets (buffer, sizeof (buffer), file) != '\n'){

        char* token = strtok (buffer, ";");

            for (int k=0; k<8; k++){

                v->orari[k].inizio = atof (token);

                token = strtok (NULL, ";");

                v->orari[k].fine = atof (token);

                token = strtok (NULL, ";");

                v->orari[k].Disponibilità = atoi (token);
            }
    }

        rewind (file);

        file = fclose (file);

        if (file != EOF){

            perror ("Errore nella chiusura del file.");
            exit (1);
        }
    }

/*
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
 */

void verificaDisponibilità (veicolo v, int k){

    if ((v->orari[k].Disponibilità)%2 == 1){

        printf ("Non Disponibile\n");
    }
    else{

        printf ("Disponibile\n");
    }
}

/*
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
 */

void modificaDisponibilità (veicolo v, int k){

    v->orari[k].Disponibilità = 1;
}

/*
 * Funzione: stampaOrari
 * -----------------------
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
 */

void stampaOrari (veicolo v){

        for (int k=0; k<8; k++){

        printf ("%.2f-%.2f ", v->orari[k].inizio, v->orari[k].fine);

        verificaDisponibilità(v, k);
        }
}