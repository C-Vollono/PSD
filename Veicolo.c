#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Veicolo.h"

// DEFINIZIONE STRUTTURA ORARIO
typedef struct Orario {

    float inizio;
    float fine;
    int Disponibilità; // 0 non disponibile 1 disponibile

}Orario;
// DEFINIZIONE STRUCT VETTURA
struct Vettura{

    char* tipoVeicolo;
    char* modello;
    char* colore;
    char* targa;
    Orario orari[8];
    int postiOmologati;
    char* Combustibile;
    int annoDiImmatricolazione;
    float CostoNoleggioOrario; // Costo ad ORA
};

// -- FUNZIONI RELATIVE AI VEICOLI --

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

void stampaVeicolo (veicolo v){

    printf("VEICOLO:\nTipo Veicolo: %s\nModello: %s\nColore: %s\nTarga: %s\nPosti Omologati: %d\nCombustibile: %s\nAnno di immatricolazione: %d\nCosto Noleggio: %.2f€/h", v->tipoVeicolo, v->modello, v->colore, v->targa, v->postiOmologati, v->Combustibile,v->annoDiImmatricolazione, v->CostoNoleggioOrario);

    printf ("Fasce Orarie: ");
    stampaOrari (v);
}

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
// -- FUNZIONI RELATIVE AL NOLEGGIO --

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

float verificaSconto (veicolo v, int k){ // Restituisce float tra 0.0 a 1.0 che corrisponde alla percentuale di sconto (1- verificaSconto);
      float orario = v->orari[k].inizio;
      if (orario >= 20.00 ){
        return 0.7;
      } else if (orario < 9) {
        return 0.85;
      } else return 1.0;

}

// -- FUNZIONI RELATIVE AGLI ORARI --

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

        file = fclose (file);

        if (file != EOF){

            perror ("Errore nella chiusura del file.");
            exit (1);
        }
    }


void aggiornaOrari (veicolo v, char* nomefile, int i, int k){

    FILE *file;
    char buffer [600];
    int token_int;

    file = fopen (nomefile, "r+");

    if (file == NULL){

        perror ("Errore nell'apertura del file.");
        exit (1);
    }

    for (int j=0; j <= i; j++){

        fgets (buffer, sizeof (buffer), file);
    }

    char* token = strtok (buffer, ";");

    for (int j=0; j < k*3+1; j++){  // Parte dalla prima colonna (;) si muove x3 (formato inizio/fine/disponibilita), +1 per stare sempre sulla disponibilitá

        token = strtok (NULL, ";");
    }

    token_int = atoi (token);
    if ( token_int != v->orari[k].Disponibilità){

        token = itoa (token_int, v->orari[k].Disponibilità, 10);

        fprintf (file, "%s", token);
    }

    if ( (fclose (file)) == 1){

        perror ("Errore nella chiusura del file.");
        exit (1);
    }
}

void verificaDisponibilità (veicolo v, int k){

    if ((v->orari[k].Disponibilità)%2 == 1){

        printf ("Non Disponibile\n");
    }
    else{

        printf ("Disponibile\n");
    }
}

void modificaDisponibilità (veicolo v, int k){

    v->orari[k].Disponibilità = 1;
}

void stampaOrari (veicolo v){

        for (int k=0; k<8; k++){

        printf ("%.2f-%.2f ", v->orari[k].inizio, v->orari[k].fine);

        verificaDisponibilità(v, k);
        }
}











