#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TabellaHash.h"
#include "Prenotazione.h"

#define HASH_TAGLIA 30

/*DEFIZIONE TABELLA HASH*/
struct hash{
    int taglia;
    struct item **tabella; 
};

/*-- FUNZIONI RELATIVE ALLA TABELLA HASH --*/

/*---------------------------------------------------------------------------------------------------------------- 
 * Funzione: ottieniTaglia
 * -----------------------
 * Restituisce la taglia della tabella hash.
 *  
 * Specifica sintattica:
 *      ottieniTaglia (TabellaHash) -> int
 *      
 * Parametri:
 *      t: Tabella hash
 *      
 * Specifica semantica:
 *      ottieniTaglia (t) -> int
 *      
 * Pre-condizione:
 *      t deve esistere e diversa da NULL
 *      
 * Post-condizione:
 *      Taglia della tabella hash ottenuta correttamente
 *      
 * Ritorna:
 *      un intero che è la taglia della tabella hash.
 *      
 * Effetti collaterali:
 *      Nessun effetto collaterale.
 * ---------------------------------------------------------------------------------------------------------------- 
 */

int ottieniTaglia (TabellaHash t){
    return t->taglia;
}

/*---------------------------------------------------------------------------------------------------------------- 
 * Funzione: NuovaTabellaHash
 * -----------------------
 * Alloca memoria per una nuova tabella hash.
 * 
 * Specifica sintattica:
 *      NuovaTabellaHash (int) -> TabellaHash
 *      
 * Parametri:
 *      taglia: grandezza della tabella hash.
 *      
 * 
 * Specifica semantica:
 *      NuovaTabellaHash (taglia) -> tabellahash se allocata correttamente altrimenti NULL
 *      
 * Pre-condizione:
 *     La taglia deve essere maggiore di 0.
 *      
 * 
 * Post-condizione:
 *      La tabella hash allocata correttamente altrimenti NULL
 *      
 * 
 * Ritorna:
 *      TabellaHash allocata correttamente
 *      
 * 
 * Effetti collaterali:
 *      Stampa un messaggio di errore se l'allocazione fallisce.
 * ---------------------------------------------------------------------------------------------------------------- 
 */



TabellaHash NuovaTabellaHash (int taglia){
    TabellaHash t = malloc (sizeof (struct hash)); //Alloco memoria per la tabella hash
    if (t == NULL){
        system("cls | clear");
        perror ("ERRORE: Allocazione della memoria per la tabella hash fallita.\n");
        return NULL;
    }

    t->taglia = taglia+HASH_TAGLIA;
    t->tabella = calloc ((taglia+HASH_TAGLIA), sizeof (struct item *)); 

    if (t->tabella == NULL){
        free (t);
        return NULL;
    }

    return t;
}

/*---------------------------------------------------------------------------------------------------------------- 
 * Funzione: FunzioneHash
 * -----------------------
 * Calcola l'indice della tabella hash.
 * 
 * Specifica sintattica:
 *      FunzioneHash (int, int) -> int
 *      
 * Parametri:
 *      ID: codice univoco della prenotazione
 *      taglia: grandezza della tabella hash
 *      
 * Specifica semantica:
 *      FunzioneHash (ID, taglia) -> indice tabella hash
 *      
 * Pre-condizione:
 *      La taglia deve essere maggiore di zero.
 * 
 * Post-condizione:
 *      Ottenuto l'indice della tabella hash
 * 
 * Ritorna:
 *      Intero che è l'indice della tabella hash
 *      
 * Effetti collaterali:
 *      Nessun effetto collaterale.
 *      
 * ---------------------------------------------------------------------------------------------------------------- 
 */

int FunzioneHash(int ID, int taglia) {
    return ((31 * ID) % taglia);
}

/*---------------------------------------------------------------------------------------------------------------- 
 * Funzione: InserisciPrenotazione
 * -----------------------
 * Inserisce una prenotazione nella tabella hash
 * 
 * Specifica sintattica:
 *      InserisciPrenotazione (TabellaHash, Prenotazione) -> int
 *      
 * Parametri:
 *      t: Tabella hash
 *      p: struct prenotazione
 *      
 * Specifica semantica:
 *      InserisciPrenotazione (t, p) -> 1 a buon fine altrimenti 0 gia` presente     
 * 
 * Pre-condizione:
 *      t deve essere allocata correttamente
 *      p deve essere diversa da NULL
 *      ottieniID, ottieniNext, FunzioneHash devono essere implemetate correttamente
 * 
 * Post-condizione:
 *      Se l'inserimento ha avuto successo restituisce un 1 (inserimento effettuato correttamente) altrimenti zero
 *      
 * Ritorna:
 *      0 se la prenotazione è già presente nella tabella hash, 1 altrimenti.
 *      
 * 
 * Effetti collaterali:
 *      Modifica il contenuto della tabella hash aggiungendo una prenotazione.      
 * ---------------------------------------------------------------------------------------------------------------- 
 */

int InserisciPrenotazione (TabellaHash t, Prenotazione p){
    int indice;
    Prenotazione testa, corrente;
    indice = FunzioneHash (ottieniID(p), t->taglia);
    corrente = testa = t->tabella[indice];
    while (corrente){
        if (ottieniID(corrente) == ottieniID(p)){
            return 0;
        }
        corrente = ottieniNext(corrente);
    }
    
    t->tabella[indice] = p;
    assegnaNext(p, testa);


    return 1;
}

/*---------------------------------------------------------------------------------------------------------------- 
 * Funzione: LiberaTabellaHash
 * -----------------------
 * Dealloca la memoria occupata dalla tabella hash.
 * 
 * Specifica sintattica:
 *      LiberaTabellaHash (TabellaHash) -> void
 *      
 * Parametri:
 *      t: tabella hash
 *      
 * Specifica semantica:
 *      LiberaTabellaHash (t) -> void
 *      
 * Pre-condizione:
 *      TabellaHash deve esistere e diversa da NULL
 *      LiberaLista implementata correttamente
 * 
 * Post-condizione:
 *      Memoria liberata correttamente.
 *      
 * 
 * Ritorna:
 *      Non ritorna nessun valore.
 *      
 * 
 * Effetti collaterali:
 *      La tabella hash non contiene più i dati presenti in memoria.     
 * ---------------------------------------------------------------------------------------------------------------- 
 */

void LiberaTabellaHash (TabellaHash t){

    for (int i=0; i< t->taglia; i++){
        LiberaLista (t->tabella[i]);
    }

    free (t->tabella);
    free (t);
}

/*---------------------------------------------------------------------------------------------------------------- 
 * Funzione: StampaPrenotazioneTabellaHash
 * -----------------------
 * Stampa a video le prenotazioni dell'utente
 * 
 * Specifica sintattica:
 *      StampaPrenotazioneTabellaHash (TabellaHash, char*) -> void
 *      
 * Parametri:
 *      t: tabella hash
 *      nomeUtente: stringa nomeUtente
 *      
 * Specifica semantica:
 *      StampaPrenotazioneTabellaHash (t, nomeUtente) -> void     
 * 
 * Pre-condizione:
 *      TabellaHash deve esistere e diversa da NULL
 *      nomeUtente allocato correttamente
 *      ottieniTaglia, ottieniNomeUtente, stampaPrenotazione implementate correttamente
 *      
 * Post-condizione:
 *      Nessuna post-condizione.
 *      
 * 
 * Ritorna:
 *      Non ritorna nessun valore.
 *      
 * 
 * Effetti collaterali:
 *      Stampa a video i dati della prenotazione dell'utente, se non presenti un avviso      
 * ---------------------------------------------------------------------------------------------------------------- 
 */

void StampaPrenotazioneTabellaHash (TabellaHash t, char* nomeUtente){
    int g = ottieniTaglia(t);
    int prenotazioniEffettuate = 0;

    for (int i=0; i < g; i++){
        Prenotazione corrente = t->tabella[i];
        while (corrente != NULL){
            if (strcmp (ottieniNomeUtente(corrente), nomeUtente) == 0){
                prenotazioniEffettuate++;
                stampaPrenotazione (corrente);
            }
        corrente = ottieniNext(corrente);
        } 
    }

    if (prenotazioniEffettuate == 0){
        printf ("Non risultano presenti prenotazioni a suo nome.\n");
    }
}

/*---------------------------------------------------------------------------------------------------------------- 
 * Funzione: TrovaPrenotazione
 * -----------------------
 *  Cerca all'interno della tabella hash la prenotazione attraverso l'ID
 * 
 * Specifica sintattica:
 *      TrovaPrenotazione (TabellaHash, int, int) -> Prenotazione
 *      
 *
 * Parametri:
 *      t: tabella hash
 *      ID: chiave Prenotazione
 *      taglia: grandezza tabella hash
 *      
 * 
 * Specifica semantica:
 *      TrovaPrenotazione: (t, ID, taglia) -> prenotazione se ID trovato altrimenti NULL
 *      
 * 
 * Pre-condizione:
 *      TabellaHash deve esistere e diverso da NULL
 *      Taglia deve essere maggiore di 0.
 *      FunzioneHash, ottieniID, ottieniNext implementate correttamente
 * 
 * Post-condizione:
 *      Restituisce prenotazione se l'ID coincide altrimenti NULL
 *      
 * 
 * Ritorna:
 *      Prenotazione se l'ID coincide altrimenti NULL
 *      
 * 
 * Effetti collaterali:
 *      Prenotazione contiene dati della struct Prenotazione   
 * ---------------------------------------------------------------------------------------------------------------- 
 */

Prenotazione TrovaPrenotazione (TabellaHash t, int ID, int taglia){
    int indice = FunzioneHash (ID, taglia);
    Prenotazione p = t->tabella[indice];
    while (p != NULL){
        if (ottieniID(p) == ID){
            return p;
        }
        p = ottieniNext(p);
    }
    return NULL;
}

//Utilizzata solo per il testing
Prenotazione ottieniPrenotazione(TabellaHash t, int indice){
    return t->tabella[indice];
}