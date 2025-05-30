#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TabellaHash.h"
#include "Prenotazione.h"

#define HASH_TAGLIA 30

struct hash{
    int taglia;
    struct item **tabella; 
};

/*---------------------------------------------------------------------------------------------------------------- 
 * Funzione: ottieniTaglia
 * -----------------------
 * Restituisce la taglia della tabella hash.
 *  
 * 
 * Specifica sintattica:
 *      ottieniTaglia (TabellaHash) -> int
 *      
 *
 * Parametri:
 *      t: Tabella hash
 *      
 * 
 * Specifica semantica:
 *      ottieniTaglia (t) -> int
 *      
 * 
 * Pre-condizione:
 *      t deve esistere e non deve essere vuota.
 *      
 * 
 * Post-condizione:
 *      ottengo la taglia della tabella hash.
 *      
 * 
 * Ritorna:
 *      un intero che è la taglia della tabella hash.
 *      
 * 
 * Effetti collaterali:
 * 
 * Nessun effetto collaterale.
 *      
 * ---------------------------------------------------------------------------------------------------------------- 
 */

int ottieniTaglia (TabellaHash t){
    return t->taglia;
}

/*---------------------------------------------------------------------------------------------------------------- 
 * Funzione: NuovaTabellaHash
 * -----------------------
 *  La funzione alloca memoria per una nuova tabella hash.
 * 
 * Specifica sintattica:
 *      NuovaTabellaHash (int) -> TabellaHash
 *      
 *
 * Parametri:
 *      taglia: grandezza della tabella hash.
 *      
 * 
 * Specifica semantica:
 *      NuovaTabellaHash (taglia) -> TabellaHash
 *      
 * 
 * Pre-condizione:
 *     taglia: deve essere maggiore di 0.
 *      
 * 
 * Post-condizione:
 *      La tabella hash non deve essere vuota.
 *      
 * 
 * Ritorna:
 *      Una variabile di tipo TabellaHash che è la tabella hash allocata.
 *      
 * 
 * Effetti collaterali:
 *      Stampa un messaggio di errore se l'allocazione fallisce.
 *      
 * 
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
 *  La funzione calcola l'indice della tabella hash.
 * 
 * Specifica sintattica:
 *      FunzioneHash (int, int) -> int
 *      
 *
 * Parametri:
 *      ID: codice univoco della prenotazione
 *      taglia: grandezza della tabella hash
 *      
 * 
 * Specifica semantica:
 *      FunzioneHash (ID, taglia) -> int
 *      
 * 
 * Pre-condizione:
 *      taglia deve essere maggiore di zero.
 * 
 * 
 * Post-condizione:
 *      Nessuna post condizione.
 * 
 * Ritorna:
 *      ritorna un intero che è l'indice della tabella hash associato alla prenotazione.
 *      
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
 *  La funzione inserisce una prenotazione nella tabella hash
 * 
 * Specifica sintattica:
 *      InserisciPrenotazione (TabellaHash, Prenotazione) -> int
 *      
 *
 * Parametri:
 *      t: Tabella hash
 *      p: prenotazione
 *      
 * 
 * Specifica semantica:
 *      InserisciPrenotazione (t, p) -> int     
 * 
 * 
 * Pre-condizione:
 *      t deve essere allocata correttamente
 *      p deve essere diversa da NULL
 *      
 * 
 * Post-condizione:
 *      Nessuna post condizione.
 *      
 * 
 * Ritorna:
 *      0 se la prenotazione è già presente nella tabella hash, 1 altrimenti.
 *      
 * 
 * Effetti collaterali:
 *      Modifica il contenuto della tabella hash aggiungendo una prenotazione.
 *      
 * ---------------------------------------------------------------------------------------------------------------- 
 */

int InserisciPrenotazione (TabellaHash t, Prenotazione p){
    int indice = FunzioneHash (ottieniID(p), t->taglia);
    Prenotazione corrente, testa, temp;
    corrente = testa = t->tabella[indice];
    while (corrente){
        if (ottieniID(corrente) == ottieniID(p)){
            return 0;
        }
        corrente = ottieniNext(corrente);
    }
    
    t->tabella[indice] = p;
    temp = ottieniNext(t->tabella[indice]);
    temp = testa;


    return 1;
}

/*---------------------------------------------------------------------------------------------------------------- 
 * Funzione: LiberaTabellaHash
 * -----------------------
 *  La funzione dealloca la memoria occupata dalla tabella hash.
 * 
 * Specifica sintattica:
 *      LiberaTabellaHash (TabellaHash) -> void
 *      
 *
 * Parametri:
 *      t: tabella hash
 *      
 * 
 * Specifica semantica:
 *      LiberaTabellaHash (t) -> void
 *      
 * 
 * Pre-condizione:
 *      t non deve essere vuota.
 *      
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
 * 
 *      
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
 *  La funzione stampa a video le prenotazioni dell'utente scelto.
 * 
 * Specifica sintattica:
 *      StampaPrenotazioneTabellaHash (TabellaHash, char*) -> void
 *      
 *
 * Parametri:
 *      t: tabella hash
 *      nomeUtente: variabile con cui effettuare la ricerca delle prenotazioni
 *      
 * 
 * Specifica semantica:
 *      StampaPrenotazioneTabellaHash (t, nomeUtente) -> void     
 * 
 * 
 * Pre-condizione:
 *      t non deve essere vuota.
 *      
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
 *      Stampa a video i dettagli delle prenotazioni presenti nella tabella hash dell'utente scelto.
 *      
 * ---------------------------------------------------------------------------------------------------------------- 
 */

void StampaPrenotazioneTabellaHash (TabellaHash t, char* nomeUtente){
    int g = ottieniTaglia(t);
    int prenotazioniEffettuate = 0;

    for (int i=0; i < g; i++){
        if (t->tabella[i] != NULL){
            Prenotazione P = t->tabella[i];
            if (strcmp (ottieniNomeUtente(P), nomeUtente) == 0){
                prenotazioniEffettuate++;
                stampaPrenotazione (P);
            }
        } 
    }

    if (prenotazioniEffettuate == 0){
        printf ("Non risultano presenti prenotazioni a suo nome.\n");
    }
}

/*---------------------------------------------------------------------------------------------------------------- 
 * Funzione: TrovaPrenotazione
 * -----------------------
 *  La funzione ricerca all'iterno della tabella hash la prenotazione associata all'ID inserito da tastiera.
 * 
 * Specifica sintattica:
 *      TrovaPrenotazione (TabellaHash, int, int) -> Prenotazione
 *      
 *
 * Parametri:
 *      t: tabella hash
 *      ID: codice univoco della Prenotazione
 *      taglia: grandezza della tabella hash
 *      
 * 
 * Specifica semantica:
 *      TrovaPrenotazione: (t, ID, taglia) -> Prenotazione
 *      
 * 
 * Pre-condizione:
 *      t non deve essere vuota.
 *      taglia deve essere maggiore di 0.
 *      
 * 
 * Post-condizione:
 *      Restituisce una variabile di tipo prenotazione che contiene i dati della prenotazione cercata.
 *      
 * 
 * Ritorna:
 *      Una variabile di tipo Prenotazione, altrimenti NULL se la ricerca ha dato esito negativo.
 *      
 * 
 * Effetti collaterali:
 *      La variabile restituita contiene i dati della prenotazione cercata.
 * 
 *      
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