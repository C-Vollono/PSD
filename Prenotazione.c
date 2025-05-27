/*ATTENZIONE: Nel codice sono presenti comandi system
              Implementati per la pulizia del terminale
              Potrebbero creare conflitti o problemi di vari natura
              "Annullarli" nel caso della presenza di quest'ultimi*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Veicolo.h"
#include "Prenotazione.h"
#include "Utile.h"

struct item { // STRUTTURA PRENOTAZIONE DA RIMANERE
    int ID; //chiave dell'item prenotazione
    char* nomeUtente;
    veicolo v;
    char* data;
    float CostoNoleggioFinale;
    float OrarioSceltoInizio;
    float OrarioSceltoFine;
    struct item *next; 
};

<<<<<<< HEAD
=======
/*---------------------------------------------------------------------------------------------------------------- 
 * Funzione: NuovaPrenotazione
 * -----------------------
 *  
 * 
 * Specifica sintattica:
 *      
 *
 * Parametri:
 *      
 * 
 * Specifica semantica:
 *      
 * 
 * Pre-condizione:
 *      
 * 
 * Post-condizione:
 *      
 * 
 * Ritorna:
 *      
 * 
 * Effetti collaterali:
 *      
 * ---------------------------------------------------------------------------------------------------------------- 
 */

>>>>>>> 5fc77bdd29a79ca64eba61161764cec944d2e7bc
Prenotazione NuovaPrenotazione (int ID, char* NomeUtente, veicolo c, int i, char* dataPrenotazione){

    Prenotazione p = malloc (sizeof (struct item));
    if (p == NULL){
        system("cls | clear");
        perror ("ERRORE: Creazione della prenotazione fallita.\n");
        return NULL;
    }

    p->ID = ID;
    p->nomeUtente = malloc (strlen (NomeUtente)+1);

    if (p->nomeUtente == NULL){
        system("cls | clear");
        perror ("ERRORE: Allocazione del nome utente per la prenotazione fallita.\n");
        return NULL;
    }
    strcpy (p->nomeUtente, NomeUtente);

    p->v = c;
    p->data = strdup (dataPrenotazione);

    if (p->data == NULL){
        perror ("ERRORE: Allocazione data per la prenotazione fallita.\n");
        free (p->nomeUtente);
        free (p);
        return NULL;
    }
    
<<<<<<< HEAD
    p->OrarioSceltoInizio = p->v->orari[i].inizio; // DA METTERE GETORARIOINIZIO
    p->OrarioSceltoFine = p->v->orari[i].fine; // GETORARIOFINE
=======
    p->OrarioSceltoInizio = ottieniOrarioInizio(c, i);
    p->OrarioSceltoFine = ottieniOrarioFine(c, i);
>>>>>>> 5fc77bdd29a79ca64eba61161764cec944d2e7bc
    p->CostoNoleggioFinale = costoNoleggio (c, i);
    p->next = NULL;

    return p;
}

<<<<<<< HEAD
static void LiberaLista (Prenotazione p){ // DA METTERE IN PRENOTAZIONE.C 
=======
/*---------------------------------------------------------------------------------------------------------------- 
 * Funzione: LiberaLista
 * -----------------------
 *  
 * 
 * Specifica sintattica:
 *      
 *
 * Parametri:
 *      
 * 
 * Specifica semantica:
 *      
 * 
 * Pre-condizione:
 *      
 * 
 * Post-condizione:
 *      
 * 
 * Ritorna:
 *      
 * 
 * Effetti collaterali:
 *      
 * ---------------------------------------------------------------------------------------------------------------- 
 */

void LiberaLista (Prenotazione p){
>>>>>>> 5fc77bdd29a79ca64eba61161764cec944d2e7bc
    Prenotazione nuovap;
    while (p != NULL){
        nuovap = p->next;

        free(p->nomeUtente);
        free(p->data);
        free (p);

        p = nuovap;
    }
}

<<<<<<< HEAD

void stampaPrenotazione (Prenotazione p){ // GET SOPRA DA METTERE IN PRENOTAZIONE.C
    printf("\nID Prenotazione: %d\nData: %s\nModello: %s\nOrario selezionato: %.2f/%.2f\nCosto noleggio: %.2f euro\n", p->ID, p->data, p->v->modello, p->OrarioSceltoInizio, p->OrarioSceltoFine, p->CostoNoleggioFinale);
}

=======
/*---------------------------------------------------------------------------------------------------------------- 
 * Funzione: stampaPrenotazione
 * -----------------------
 *  
 * 
 * Specifica sintattica:
 *      
 *
 * Parametri:
 *      
 * 
 * Specifica semantica:
 *      
 * 
 * Pre-condizione:
 *      
 * 
 * Post-condizione:
 *      
 * 
 * Ritorna:
 *      
 * 
 * Effetti collaterali:
 *      
 * ---------------------------------------------------------------------------------------------------------------- 
 */


void stampaPrenotazione (Prenotazione p){ 
    printf("\nID Prenotazione: %d\nData: %s\nModello: %s\nOrario selezionato: %.2f/%.2f\nCosto noleggio: %.2f euro\n", p->ID, p->data, ottieniModelloPrenotazione(p), p->OrarioSceltoInizio, p->OrarioSceltoFine, p->CostoNoleggioFinale);
}

/*---------------------------------------------------------------------------------------------------------------- 
 * Funzione: ottieniID
 * -----------------------
 *  
 * 
 * Specifica sintattica:
 *      
 *
 * Parametri:
 *      
 * 
 * Specifica semantica:
 *      
 * 
 * Pre-condizione:
 *      
 * 
 * Post-condizione:
 *      
 * 
 * Ritorna:
 *      
 * 
 * Effetti collaterali:
 *      
 * ---------------------------------------------------------------------------------------------------------------- 
 */

int ottieniID (Prenotazione p){
    if(p!=NULL){
        return p->ID;
    }
    return -1;
}

/*---------------------------------------------------------------------------------------------------------------- 
 * Funzione: ottieniNext
 * -----------------------
 *  
 * 
 * Specifica sintattica:
 *      
 *
 * Parametri:
 *      
 * 
 * Specifica semantica:
 *      
 * 
 * Pre-condizione:
 *      
 * 
 * Post-condizione:
 *      
 * 
 * Ritorna:
 *      
 * 
 * Effetti collaterali:
 *      
 * ---------------------------------------------------------------------------------------------------------------- 
 */

struct item *ottieniNext(Prenotazione p){
    if(p!=NULL){
        return p->next;
    }
    return NULL;
}

/*---------------------------------------------------------------------------------------------------------------- 
 * Funzione: ottieniNomeUtente
 * -----------------------
 *  
 * 
 * Specifica sintattica:
 *      
 *
 * Parametri:
 *      
 * 
 * Specifica semantica:
 *      
 * 
 * Pre-condizione:
 *      
 * 
 * Post-condizione:
 *      
 * 
 * Ritorna:
 *      
 * 
 * Effetti collaterali:
 *      
 * ---------------------------------------------------------------------------------------------------------------- 
 */

char* ottieniNomeUtente(Prenotazione p){
    if(p!=NULL){
        return p->nomeUtente;
    }
    return NULL;
}

/*---------------------------------------------------------------------------------------------------------------- 
 * Funzione: ottieniDataPrenotazione
 * -----------------------
 *  
 * 
 * Specifica sintattica:
 *      
 *
 * Parametri:
 *      
 * 
 * Specifica semantica:
 *      
 * 
 * Pre-condizione:
 *      
 * 
 * Post-condizione:
 *      
 * 
 * Ritorna:
 *      
 * 
 * Effetti collaterali:
 *      
 * ---------------------------------------------------------------------------------------------------------------- 
 */

char* ottieniDataPrenotazione(Prenotazione p){
    if(p!=NULL){
        return p->data;
    }
    return NULL;
}

/*---------------------------------------------------------------------------------------------------------------- 
 * Funzione: ottieniInizioPrenotazione
 * -----------------------
 *  
 * 
 * Specifica sintattica:
 *      
 *
 * Parametri:
 *      
 * 
 * Specifica semantica:
 *      
 * 
 * Pre-condizione:
 *      
 * 
 * Post-condizione:
 *      
 * 
 * Ritorna:
 *      
 * 
 * Effetti collaterali:
 *      
 * ---------------------------------------------------------------------------------------------------------------- 
 */

float ottieniInizioPrenotazione(Prenotazione p){
    if(p!=NULL){
        return p->OrarioSceltoInizio;
    }
    return -1;
}

/*---------------------------------------------------------------------------------------------------------------- 
 * Funzione: ottieniFinePrenotazione
 * -----------------------
 *  
 * 
 * Specifica sintattica:
 *      
 *
 * Parametri:
 *      
 * 
 * Specifica semantica:
 *      
 * 
 * Pre-condizione:
 *      
 * 
 * Post-condizione:
 *      
 * 
 * Ritorna:
 *      
 * 
 * Effetti collaterali:
 *      
 * ---------------------------------------------------------------------------------------------------------------- 
 */

float ottieniFinePrenotazione(Prenotazione p){
    if(p!=NULL){
        return p->OrarioSceltoFine;
    }
    return -1;
}

/*---------------------------------------------------------------------------------------------------------------- 
 * Funzione: ottineiModelloPrenotazione
 * -----------------------
 *  
 * 
 * Specifica sintattica:
 *      
 *
 * Parametri:
 *      
 * 
 * Specifica semantica:
 *      
 * 
 * Pre-condizione:
 *      
 * 
 * Post-condizione:
 *      
 * 
 * Ritorna:
 *      
 * 
 * Effetti collaterali:
 *      
 * ---------------------------------------------------------------------------------------------------------------- 
 */

char* ottieniModelloPrenotazione(Prenotazione p){
    veicolo temp = p->v;

    if(p!=NULL){
        return ottieniModello(temp);
    }
    return NULL;
}

/*---------------------------------------------------------------------------------------------------------------- 
 * Funzione: ottieniTargaPrenotazione
 * -----------------------
 *  
 * 
 * Specifica sintattica:
 *      
 *
 * Parametri:
 *      
 * 
 * Specifica semantica:
 *      
 * 
 * Pre-condizione:
 *      
 * 
 * Post-condizione:
 *      
 * 
 * Ritorna:
 *      
 * 
 * Effetti collaterali:
 *      
 * ---------------------------------------------------------------------------------------------------------------- 
 */

char* ottieniTargaPrenotazione(Prenotazione p){
    veicolo temp = p->v;

    if(p!=NULL){
        return ottieniTarga(temp);
    }
    return NULL;
}

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
 *      costoNoleggio(v, k) -> Costo del noleggio
 * 
 * Pre-condizione:
 *      L'oggetto veicolo deve esistere e contenere dati sugli intervalli orari
 *      La funzione verificaSconto deve esistere (oppure eliminata in caso di sconti non applicabili) e inclusa
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
    float inizio = ottieniOrarioInizio(v , k), fine = ottieniOrarioFine(v , k);

    ore = (int)inizio;
    minuti = round((inizio-ore)*100);
    minutiTotali = (ore*60) + minuti; // MINUTI TOTALI SOLO INIZIALI

    ore = (int)fine;
    minuti = round((fine-ore)*100);
    minutiTotali = (ore*60)+minuti - minutiTotali; // MINUTI TOTALI DEL TEMPO DI NOLEGGIO

    return minutiTotali * ((ottieniCostoOrario(v))/60) * verificaSconto(v,k);
}
>>>>>>> 5fc77bdd29a79ca64eba61161764cec944d2e7bc
