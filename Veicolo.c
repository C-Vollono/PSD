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

<<<<<<< HEAD

void stampaVeicolo (veicolo v, int i){

    printf ("VEICOLO:\nTipo Veicolo: %s\nModello: %s\nColore: %s\nTarga: %s\nPosti Omologati: %d\nCombustibile: %s\nAnno di immatricolazione: %d\nCosto Noleggio: %.2f€/h", v->tipoVeicolo, v[i].modello, v[i].colore, v[i].targa, v[i].postiOmologati, v[i].Combustibile,v[i].annoDiImmatricolazione, v[i].CostoNoleggioOrario);

    printf ("Fasce Orarie: ");
    
    stampaOrari (v, i);
}

void stampaOrari (veicolo v, int i){

        for (int k=0; k<8; k++){

        printf ("%.2f-%.2f ", v[i].orari[k].inizio, v[i].orari[k].fine);

        verificaDisponibilità(v, i, k);
        }
}

void verificaDisponibilità (veicolo v, int i, int k){

    if ((v[i].orari[k].Disponibilità)%2 == 1){

        printf ("Non Disponibile\n");
    }
    else{

        printf ("Disponibile\n");
    } 
}

float costoNoleggio (veicolo v, int i, int k){

    int ore, minuti, tempoNoleggio;

    float inizio = v[i].orari[k].inizio, fine = v[i].orari[k].fine;

    minuti = (inizio - (int)inizio)*100;

    ore = (int)inizio;

    tempoNoleggio = ore*3600 + minuti*60;

    minuti = (fine - (int)fine)*100;

    ore = (int)fine;

    tempoNoleggio = ((ore*3600 + minuti*60) - tempoNoleggio)/3600;

    return (tempoNoleggio * v[i].CostoNoleggioOrario) * verificaSconto(v);
}

void modificaDisponibilità (veicolo v, int i, int k){

    v[i].orari[k].Disponibilità = 1;
}
=======
// -- FUNZIONI RELATIVE AI VEICOLI --
>>>>>>> d8999f68e23ce8a11d2ee8e96a39899dbfe05952

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
/* Discuterne l'utilitá e la non rindondanza
void aggiornaVeicoli (veicolo v, char* nomefile){
    FILE *file = fopen(nomefile, "r+");

} */

void stampaVeicolo (veicolo v, int i){

    printf("VEICOLO:\nTipo Veicolo: %s\nModello: %s\nColore: %s\nTarga: %s\nPosti Omologati: %d\nCombustibile: %s\nAnno di immatricolazione: %d\nCosto Noleggio: %.2f€/h", v[i].tipoVeicolo, v[i].modello, v[i].colore, v[i].targa, v[i].postiOmologati, v[i].Combustibile,v[i].annoDiImmatricolazione, v[i].CostoNoleggioOrario);

    printf ("Fasce Orarie: ");
    stampaOrari (v, i);
}

void liberaVeicoli (veicolo v){

    for (int i=0; i<10; i++){

        free (v[i].annoDiImmatricolazione);
        free (v[i].colore);
        free (v[i].Combustibile);
        free (v[i].modello);
        free (v[i].targa);
        free (v[i].tipoVeicolo);
        free (v[i].orari);
    }

    free (v);
}
// -- FUNZIONI RELATIVE AL NOLEGGIO --

float costoNoleggio (veicolo v, int i, int k){

    int ore, minuti, tempoNoleggio;

    float inizio = v[i].orari[k].inizio, fine = v[i].orari[k].fine;

    minuti = (inizio - (int)inizio)*100;

    ore = (int)inizio;

    tempoNoleggio = ore*3600 + minuti*60;

    minuti = (fine - (int)fine)*100;

    ore = (int)fine;

    tempoNoleggio = ((ore*3600 + minuti*60) - tempoNoleggio)/3600;

    return (tempoNoleggio * v[i].CostoNoleggioOrario) * verificaSconto(v);
}

float verificaSconto (veicolo v, int i, int k){ // Restituisce float tra 0.0 a 1.0 che corrisponde alla percentuale di sconto (1- verificaSconto);
      float orario = v[i].orari[k].inizio;
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
    if ( token_int != v[i].orari[k].Disponibilità){

        token = itoa (token_int, v[i].orari[k].Disponibilità, 10);

        fprintf (file, "%s", token);
    }

    if ( (fclose (file)) == 1){

        perror ("Errore nella chiusura del file.");
        exit (1);
    }
}

void verificaDisponibilità (veicolo v, int i, int k){

    if ((v[i].orari[k].Disponibilità)%2 == 1){

        printf ("Non Disponibile\n");
    }
    else{

        printf ("Disponibile\n");
    }
}

void modificaDisponibilità (veicolo v, int i, int k){

    v[i].orari[k].Disponibilità = 1;
}

void stampaOrari (veicolo v, int i){

        for (int k=0; k<8; k++){

        printf ("%.2f-%.2f ", v[i].orari[k].inizio, v[i].orari[k].fine);

        verificaDisponibilità(v, i, k);
        }
}











