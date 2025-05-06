#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Veicolo.h"

typedef struct Orario {

    float inizio;

    float fine;

    int Disponibilità;

}Orario;

struct Vettura{

    char* tipoVeicolo;

    char* modello;

    char* colore;

    char* targa;

    Orario orari[8];

    int postiOmologati;

    char* Combustibile;

    int annoDiImmatricolazione;

    float CostoNoleggioOrario;
};


void stampaVeicolo (veicolo v){

    printf ("VEICOLO:\nTipo Veicolo: %s\nModello: %s\nColore: %s\nTarga: %s\nPosti Omologati: %d\nCombustibile: %s\nAnno di immatricolazione: %d\nCosto Noleggio: %.2f€/h", v->tipoVeicolo, v->modello, v->colore, v->targa, v->postiOmologati, v->Combustibile,v->annoDiImmatricolazione, v->CostoNoleggioOrario);

    printf ("Fasce Orarie: ");
    
    stampaOrari (v);
}

void stampaOrari (veicolo v){

    for (int i=0; i<8; i++){

        printf ("%.2f-%.2f ", v->orari->inizio, v->orari->fine);

        verificaDisponibilità(v);
    }
}

void verificaDisponibilità (veicolo v){

    if ((v->orari->Disponibilità)%2 == 1){

        printf ("Non Disponibile\n");
    }
    else{

        printf ("Disponibile\n");
    } 
}

float costoNoleggio (veicolo v){

    int ore, minuti, tempoNoleggio;

    float inizio = v->orari->inizio, fine = v->orari->fine;

    minuti = (inizio - (int)inizio)*100;

    ore = (int)inizio;

    tempoNoleggio = ore*3600 + minuti*60;

    minuti = (fine - (int)fine)*100;

    ore = (int)fine;

    tempoNoleggio = ((ore*3600 + minuti*60) - tempoNoleggio)/3600;

    return (tempoNoleggio * v->CostoNoleggioOrario) * verificaSconto(v);
}

void modificaDisponibilità (veicolo v){

    v->orari->Disponibilità = 1;
}

void riempiVeicoli (veicolo v, char* nomefile){

    FILE *file;
    char buffer [200];

    file = fopen ("nomefile", "r");

    if (file == NULL){

        printf ("Errore nell'apertura del file.");
        exit (1);
    }

    while (fgets (buffer, sizeof (buffer), file) != '\n'){

        for (int i=0; i<10; i++){

        char* token = strtok (buffer, ";");

        v[i].tipoVeicolo = malloc (strlen (token)+1 * sizeof (char));

        if (v[i].tipoVeicolo == NULL){
            
            perror ("ERRORE TIPO VEICOLO");
            exit (1);
        }

        strcpy (v[i].tipoVeicolo, token);

        token = strtok (NULL, ";");

        v[i].modello = malloc (strlen (token)+1 * sizeof (char));

        if (v[i].modello == NULL){

            perror ("ERRORE MODELLO");
            free (v[i].tipoVeicolo);
            exit(1);
        }

        strcpy (v[i].modello, token);

        token = strtok (NULL, ";");

        v[i].colore = malloc (strlen (token)+1 * sizeof (char));

        if (v[i].colore == NULL){

            perror ("ERRORE COLORE");
            free (v[i].modello);
            free (v[i].tipoVeicolo);
            exit (1);
        }

        strcpy (v[i].colore, token);

        token = strtok (NULL, ";");

        v[i].targa = malloc (strlen (token)+1 * sizeof (char));

        if (v[i].targa == NULL){

            perror ("ERRORE TARGA");
            free (v[i].modello);
            free (v[i].tipoVeicolo);
            free (v[i].colore);
            exit (1);
        }

        strcpy (v[i].targa, token);

        token = strtok (NULL, ";");

        v[i].postiOmologati = atoi (token);

        token = strtok (NULL, ";");

        v[i].Combustibile = malloc (strlen(token)+1 * sizeof (char));

        if (v[i].Combustibile == NULL){

            perror ("ERRORE COMBUSTIBILE");
            free (v[i].modello);
            free (v[i].tipoVeicolo);
            free (v[i].colore);
            free (v[i].targa);
            exit (1);
        }

        token = strtok (NULL, ";");

        v[i].annoDiImmatricolazione = atoi (token);

        token = strtok (NULL, ";");

        v[i].CostoNoleggioOrario = atoi (token);
    }
}

    file = fclose (file);

    if (file != EOF){

        perror ("Errore nella chiusura del file.");
        exit (1);
    }
}

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

        for (int i=0; i<10; i++){
            
            for (int k=0; k<8; k++){

                v[i].orari[k].inizio = atof (token);

                token = strtok (NULL, ";");

                v[i].orari[k].fine = atof (token);

                token = strtok (NULL, ";");

                v[i].orari[k].Disponibilità = atoi (token);
            }
        }

        file = fclose (file);

        if (file != EOF){

            perror ("Errore nella chiusura del file.");
            exit (1);
        }
    }
}
