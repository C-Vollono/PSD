/*ATTENZIONE: Nel codice sono presenti comandi system
              Implementati per la pulizia del terminale
              Potrebbero creare conflitti o problemi di vari natura
              "Annullarli" nel caso della presenza di quest'ultimi*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Veicolo.h"
#include "Utile.h"


/*-- DEFINIZIONE STRUCT ORARIO --*/
typedef struct Orario {
    float inizio;
    float fine;
    int Disponibilita; // 0 = disponibile oppure 1 = non disponibile
}Orario;

/*-- DEFINIZIONE STRUCT VETTURA --*/
struct Vettura{
    char* tipoVeicolo;
    char* modello;
    char* colore;
    char* targa;
    Orario orari[8]; //Struct annidata per gli orari
    int postiOmologati;
    char* Combustibile;
    int annoDiImmatricolazione;
    float CostoNoleggioOrario;
};

/*-- FUNZIONI RELATIVE AI VEICOLI --*/

/*---------------------------------------------------------------------------------------------------------------- 
 * Funzione: riempiVeicoli
 * -----------------------
 * Riempie la struct veicolo con i dati contenuti nel file Veicolo.txt  
 * 
 * Specifica sintattica:
 *      riempiVeicoli(veicolo) -> int
 *
 * Parametri:
 *      v: struct veicolo
 * 
 * Specifica semantica:
 *      riempiVeicoli(v) -> 0 se chiusura del file corretta altrimenti 1
 * 
 * Pre-condizione:
 *      Veicolo.txt deve esistere e contenere i dati dei veicoli
 *      La struct veicolo deve esistere
 *      controlloToken, chiudiFile, riempiOrari devono essere implemetate correttamente
 * 
 * Post-condizione:
 *      La struct veicolo e` riempita con successo
 * 
 * Ritorna:
 *      0 se chiusura del file corretta altrimenti 1
 * 
 * Effetti collaterali:
 *      Modifica il contenuto nella struct veicolo
 *      Se il file è vuoto, la struct veicolo risulta NULL
 *      Stampa errore per apertura del file fallita, per l'allocazione dei vari campi della struct e riempimento fallito
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
 * Funzione: stampaVeicolo
 * -----------------------
 * Stampa a video i dati della struct veicolo
 * 
 * Specifica sintattica:
 *      stampaVeicoli(veicolo) -> void
 *
 * Parametri:
 *      v: struct veicolo
 * 
 * Specifica semantica:
 *      stampaVeicoli(v) -> void
 * 
 * Pre-condizione:
 *      La struct veicolo deve contenere dei dati diversi da NULL
 *      
 * Post-condizione:
 *      Non ritorna nessun valore
 * 
 * Ritorna:
 *      Nessun valore 
 * 
 * Effetti collaterali:
 *      Stampa a video i dati della struct veicolo
 * ---------------------------------------------------------------------------------------------------------------- 
 */

 void stampaVeicolo (veicolo v){
    printf("Tipo Veicolo: %s\nModello: %s\nColore: %s\nTarga: %s\nPosti Omologati: %d\nCombustibile: %s\nAnno di immatricolazione: %d\nCosto Noleggio: %.2f euro/h\n\n", v->tipoVeicolo, v->modello, v->colore, v->targa, v->postiOmologati, v->Combustibile,v->annoDiImmatricolazione, v->CostoNoleggioOrario);
}

/*---------------------------------------------------------------------------------------------------------------- 
 * Funzione: liberaVeicolo
 * -----------------------
 *  Libera la memoria della struct veicolo
 * 
 * Specifica sintattica:
 *      liberaVeicolo(veicolo) -> void
 *
 * Parametri:
 *      v: struct veicolo
 *  
 * Specifica semantica:
 *      liberaVeicolo(v) -> void
 * 
 * Pre-condizione:
 *      Memoria allocata per la struct veicolo
 * 
 * Post-condizione:
 *      Memoria liberata correttamente
 * 
 * Ritorna:
 *      Nessun valore 
 * 
 * Effetti collaterali:
 *      La struct veicolo non ha più dati presenti in memoria
 * ---------------------------------------------------------------------------------------------------------------- 
 */

 void liberaVeicolo (veicolo v){
    if (v->colore) { free(v->colore); }
    if (v->Combustibile) { free(v->Combustibile); }
    if (v->modello) { free(v->modello); }
    if (v->targa){ free(v->targa); }
    if (v->tipoVeicolo){ free(v->tipoVeicolo); }
}

/*---------------------------------------------------------------------------------------------------------------- 
 * Funzione: riempiOrari
 * -----------------------
 * Prende in input la struct veicolo
 * Riempi la struct annidata Orari con i dati contenuti nel file Orari.txt
 * 
 * Specifica sintattica:
 *      riempiOrari(veicolo) -> int
 *
 * Parametri:
 *      v: struct veicolo
 *      
 * Specifica semantica:
 *      riempiOrari(v) -> 0 se chiusura del file corretta altrimenti 1
 *       
 * Pre-condizione:
 *      La struct veicolo esistere
 *      Orari.txt deve esistere e contenere i dati degli intervalli orari e il loro status di disponibilita`
 *      controlloToken, chiudiFile devono essere implemetate correttamente
 *      
 * Post-condizione:
 *      La struct annidata Orari riempito con successo
 * 
 * Ritorna: 
 *      0 se chiusura del file corretta altrimenti 1
 * 
 * Effetti collaterali:
 *      Modifica il contenuto nella struct annidata orari
 *      Se il file è vuoto, la struct veicolo risulta NULL
 *      File viene chiuso in caso in cui controllotoken fallisce
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
 * Funzione: stampaDisponibilita
 * -----------------------
 * Stampa a video lo status di disponibilita di un veicolo
 * 
 * Specifica sintattica:
 *      stampaDisponibilita(veicolo, int) -> void
 *
 * Parametri:
 *      v: struct veicolo
 *      indiceOrario: indice orario scelto
 * 
 * Specifica semantica:
 *       stampaDisponibilità(v, indiceOrario) -> void
 * 
 * Pre-condizione:
 *      La struct veicolo deve esistere e contenere dati della struct annidata Orari
 *       
 * Post-condizione:
 *      Non ritorna nessun valore
 * 
 * Ritorna: 
 *      Nessun valore
 * 
 * Effetti collaterali:
 *       Stampa a video la disponibilita ("Non disponibile" o "Disponibile")
 * ---------------------------------------------------------------------------------------------------------------- 
 */

void stampaDisponibilita (veicolo v, int indiceOrario){
    if ((v->orari[indiceOrario].Disponibilita)%2 == 1){
        printf ("Non Disponibile\n");
    }
    else {
        printf ("Disponibile\n");
    }
}

/*---------------------------------------------------------------------------------------------------------------- 
 * Funzione: modificaDisponibilità
 * -----------------------
 * Va a modificare nel campo disponibilità il suo valore a 1 quando chiamata
 * 
 * Specifica sintattica:
 *      modificaDisponibilità(veicolo, int) -> void
 *
 * Parametri:
 *      v: struct veicolo
 *      indiceOrario: indice orario scelto
 * 
 * Specifica semantica:
 *       modificaDisponibilità(v, indiceOrario) -> void
 * 
 * Pre-condizione:
 *      La struct veicolo deve esistere e contenere dati nella struct annidata Orari
 *       
 * Post-condizione:
 *      Non ritorna nessun valore, Campo Disponibilità cambiato
 * 
 * Ritorna: 
 *      Nessun valore
 * 
 * Effetti collaterali:
 *       Cambiato il valore nel campo Disponibilità della struct annidata Orari
 * ---------------------------------------------------------------------------------------------------------------- 
 */

void modificaDisponibilita (veicolo v, int indiceOrario){
    v->orari[indiceOrario].Disponibilita = 1;
}

/*-----------------------------------------------------------------------------------------------------------------
 * Funzione: ottieniModello
 * ----------------------------------------------------------------------------------------------------------------
 *  Restituisce la stringa del campo modello della struct veicolo 
 * 
 * Specifica sintattica:
 *      ottieniModello(veicolo) -> char*
 *
 * Parametri:
 *      v: struct veicolo
 * 
 * Specifica semantica:
 *       ottieniModello(v) -> stringa del modello veicolo
 *        
 * Pre-condizione:
 *      La struct veicolo deve esistere
 *       
 * Post-condizione:
 *      Ottenuta la stringa nel campo modello della struct veicolo
 * 
 * Ritorna: 
 *      Una stringa del campo modello della struct veicolo altrimenti NULL
 * 
 * Effetti collaterali:
 *      Nessun effetto collaterale
 * ---------------------------------------------------------------------------------------------------------------- 
 */

char* ottieniModello(veicolo v){
    if(v!=NULL){
        return v->modello;
    }
    return NULL;
}

/*-----------------------------------------------------------------------------------------------------------------
 * Funzione: ottieniTarga
 * ----------------------------------------------------------------------------------------------------------------
 *  Restituisce la stringa del campo targa della struct veicolo 
 * 
 * Specifica sintattica:
 *      ottieniTarga(veicolo) -> char*
 *
 * Parametri:
 *      v: struct veicolo
 * 
 * Specifica semantica:
 *       ottieniTarga(v) -> stringa della targa veicolo
 *        
 * Pre-condizione:
 *      La struct veicolo deve esistere
 *       
 * Post-condizione:
 *      Ottenuta la stringa nel campo targa della struct veicolo
 * 
 * Ritorna: 
 *      Una stringa del campo targa della struct veicolo altrimenti NULL
 * 
 * Effetti collaterali:
 *      Nessun effetto collaterale
 * ---------------------------------------------------------------------------------------------------------------- 
 */

char* ottieniTarga(veicolo v){
    if(v!=NULL){
        return v->targa;
    }
    return NULL;
}

/*-----------------------------------------------------------------------------------------------------------------
 * Funzione: ottieniOrarioInizio
 * ----------------------------------------------------------------------------------------------------------------
 *  Restituisce il float del campo inizio della struct annidata orari
 * 
 * Specifica sintattica:
 *      ottieniOrariInizio(veicolo, int) -> float
 *
 * Parametri:
 *      v: struct veicolo
 *      indiceOrario: indice orario scelto
 * 
 * Specifica semantica:
 *       ottieniOrariInizio(v , indiceOrario ) -> float della struct annidata orari
 *        
 * Pre-condizione:
 *      La struct veicolo deve esistere
 *       
 * Post-condizione:
 *      Ottenuto il float del campo inizio della struct annidata orari
 * 
 * Ritorna: 
 *      Un float del campo inzio della struct annidata orari altrimenti -1 
 * 
 * Effetti collaterali:
 *      Nessun effetto collaterale
 * ---------------------------------------------------------------------------------------------------------------- 
 */

float ottieniOrarioInizio(veicolo v, int indiceOrario){
    if(v!=NULL){
        return v->orari[indiceOrario].inizio;
    }
    return -1;
}

/*-----------------------------------------------------------------------------------------------------------------
 * Funzione: ottieniOrarioFine
 * ----------------------------------------------------------------------------------------------------------------
 *  Restituisce il float del campo fine della struct annidata orari
 * 
 * Specifica sintattica:
 *      ottieniOrariFine(veicolo, int) -> float
 *
 * Parametri:
 *      v: struct veicolo
 *      indiceOrario: indice orario scelto
 * 
 * Specifica semantica:
 *       ottieniOrariFine(v , indiceOrario ) -> float della struct annidata orari
 *        
 * Pre-condizione:
 *      La struct veicolo deve esistere
 *       
 * Post-condizione:
 *      Ottenuto il float del campo fine della struct annidata orari
 * 
 * Ritorna: 
 *      Un float del campo fine della struct annidata orari altrimenti -1 
 * 
 * Effetti collaterali:
 *      Nessun effetto collaterale
 * ---------------------------------------------------------------------------------------------------------------- 
 */

float ottieniOrarioFine(veicolo v, int indiceOrario){
    if(v!=NULL){
        return v->orari[indiceOrario].fine;
    }
    return -1;
}

/*-----------------------------------------------------------------------------------------------------------------
 * Funzione: ottieniDisponibilita
 * ----------------------------------------------------------------------------------------------------------------
 *  Restituisce l'int del campo Disponibilita della struct annidata orari
 * 
 * Specifica sintattica:
 *      ottieniDisponibilita(veicolo, int) -> int
 *
 * Parametri:
 *      v: struct veicolo
 *      indiceOrario: indice orario scelto
 * 
 * Specifica semantica:
 *       ottieniDisponibilita(v , indiceOrario ) -> int della struct annidata orari
 *        
 * Pre-condizione:
 *      La struct veicolo deve esistere
 *       
 * Post-condizione:
 *      Ottenuto l'int del campo Disponibilita della struct annidata orari
 * 
 * Ritorna: 
 *      Un int del campo Disponibilita della struct annidata orari altrimenti -1 
 * 
 * Effetti collaterali:
 *      Nessun effetto collaterale
 * ---------------------------------------------------------------------------------------------------------------- 
 */

int ottieniDisponibilita(veicolo v, int indiceOrario){
    if(v!=NULL){
        return v->orari[indiceOrario].Disponibilita;
    }
    return -1;
}

/*-----------------------------------------------------------------------------------------------------------------
 * Funzione: ottieniCostoOrario
 * ----------------------------------------------------------------------------------------------------------------
 *  Restituisce il float del campo CostoNoleggioOrario della struct veicolo
 * 
 * Specifica sintattica:
 *      ottieniCostoOrario(veicolo) -> float
 *
 * Parametri:
 *      v: struct veicolo
 * 
 * Specifica semantica:
 *       ottieniCostoOrario(v) -> float della struct veicolo
 *        
 * Pre-condizione:
 *      La struct veicolo deve esistere
 *       
 * Post-condizione:
 *      Ottenuto il float del campo CostoNoleggioOrario della struct veicolo
 * 
 * Ritorna: 
 *      Un float del campo CostoNoleggioOrario della struct veicolo altrimenti -1 
 * 
 * Effetti collaterali:
 *      Nessun effetto collaterale
 * ---------------------------------------------------------------------------------------------------------------- 
 */

float ottieniCostoOrario(veicolo v){
    if(v!=NULL){
        return v->CostoNoleggioOrario;
    }
    return -1;
}

/*-----------------------------------------------------------------------------------------------------------------
 * Funzione: creaVeicolo
 * ----------------------------------------------------------------------------------------------------------------
 *  Alloca memoria per la struct veicolo
 * 
 * Specifica sintattica:
 *      creaVeicolo() -> veicolo
 *
 * Parametri:
 *     
 * 
 * Specifica semantica:
 *       creaVeicolo() -> struct veicolo
 *        
 * Pre-condizione:
 *      Nessuna pre-condizione
 *       
 * Post-condizione:
 *      Memoria allocata correttamente per la struct veicolo
 * 
 * Ritorna: 
 *      La struct veicolo allocata correttamente altrimenti NULL 
 * 
 * Effetti collaterali:
 *      Stampa un messaggio di errore in caso di allocazione fallita
 * ---------------------------------------------------------------------------------------------------------------- 
 */

veicolo creaVeicolo(){
    veicolo v = malloc(sizeof(struct Vettura));
        if (v == NULL){  
            system("cls | clear");
            perror ("ERRORE: Allocazione memoria veicolo fallita\n");
            return NULL;
        }
        return v;
}