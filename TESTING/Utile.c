#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Veicolo.h"
#include "Prenotazione.h"
#include "TabellaHash.h"
#include "Utile.h"

/*-- FUNZIONI DI UTILITA` --*/

/*---------------------------------------------------------------------------------------------------------------- 
 * Funzione: ottieniData
 * -----------------------
 *  Funzione per ottenere la data locale della macchina formattata gg/mm/aaaa
 * 
 * Specifica sintattica:
 *      ottieniData()-> char*
 *
 * Parametri:
 *      Nessun parametro
 * 
 * Specifica semantica:
 *      ottieniData() -> data locale formattata
 * 
 * Pre-condizione:
 *      Includere la libreria time.h
 * 
 * Post-condizione:
 *      Data locale della macchina ottenuta con successo
 * 
 * Ritorna:
 *      Una stringa della data locale formattata gg/mm/aaaa
 * 
 * Effetti collaterali:
 *      Stampa un messaggio di errore in caso di allocazione della memoria per la stringa fallita
 * ---------------------------------------------------------------------------------------------------------------- 
 */

char* ottieniData(){ 
    time_t t = time (NULL); //ottengo i secondi dal 1 gennaio 1970
    struct tm* data = localtime (&t); //ottengo la data corrente, ma bisogna formattarla
    char buffer[20];
    strftime (buffer, sizeof (buffer), "%d/%m/%Y", data); //formatta la data nel buffer
    char* dataFormattata = malloc (strlen(buffer) + 1);

    if(dataFormattata == NULL){
        system("cls|clear");
        perror("ERRORE: Allocazione memoria data formattata fallita.\n");
        return NULL;
    }

    strcpy(dataFormattata, buffer);
    return dataFormattata;
}

/*---------------------------------------------------------------------------------------------------------------- 
 * Funzione: AggiornaStorico
 * -----------------------
 *  Aggiorna il file TC1_output.txt in appending con una nuova prenotazione
 * 
 * Specifica sintattica:
 *      AggiornaStorico(Prenotazione, int, int)-> int
 *
 * Parametri:
 *      p: struct Prenotazione
 *      indiceVeicolo: indice del veicolo
 *      indiceOrario: indice dell'orario
 * 
 * Specifica semantica:
 *      AggiornaStorico(p, indiceVeicolo, indiceOrario) -> 0 se chiudiFile fallito altrimenti 1
 * 
 * Pre-condizione:
 *      Struct Prenotazione deve esistere e diversa da NULL
 *      Indici validi
 *      chiudiFile, ottieniNomeUtente, ottieniDataPrenotazione, ottieniInizioPrenotazione, ottieniFinePrenotazione, ottieniID, ottieniModelloPrenotazione, ottieniTargaPrenotazione devono essere implementate correttamente
 * Post-condizione:
 *      Dati scritti correttamente su file
 *      Chiusura file avvenuta con successo
 * 
 * Ritorna:
 *      0 se la chiusura del file e` fallita altrimenti 1
 * 
 * Effetti collaterali:
 *      In caso di fallimento nell'apertura del file viene stampato un messaggio di errore
 * ---------------------------------------------------------------------------------------------------------------- 
 */

int AggiornaStorico (Prenotazione p, int indiceVeicolo, int indiceOrario){
    FILE* file;
    file = fopen ("TC1_output.txt", "a");

    if (file == NULL){
        system("cls | clear");
        perror ("ERRORE: Aggiornamento dello storico da file fallito.\n");
        return 0;
    }

    fprintf(file, "\n%s-%.2f-%.2f-%s-%s-%d-%d\n",ottieniNomeUtente(p), ottieniInizioPrenotazione(p), ottieniFinePrenotazione(p), ottieniModelloPrenotazione(p), ottieniTargaPrenotazione(p), indiceVeicolo, indiceOrario);

    return chiudiFile(file);
}

/*---------------------------------------------------------------------------------------------------------------- 
 * Funzione: RiempiTabellaHashDaFile
 * -----------------------
 *  La funzione legge il file TC1_input.txt o TC4_input.txt (Storico = 1 o Storico = 4), conta il numero di prenotazioni
 *  e crea una tabella hash per contenere tutte le prenotazioni
 *  Se la data corrente corrisponde alla data locale viene aggiornata la disponibilita
 * 
 * Specifica sintattica:
 *      RiempiTabellaHashDaFile(veicolo, int) -> TabellaHash
 *
 * Parametri:
 *      *v: puntatore a un array di struct veicolo
 * 
 * Specifica semantica:
 *      RiempiTabellaHashDaFile(*v, STORICO) -> tabella hash aggiornata o NULL (non ci sono prenotazioni)
 * 
 * Pre-condizione:
 *      Il puntatore deve essere diverso da NULL e deve puntare all'array di struct veicolo
 *      La struct veicolo deve esistere e diversa da NULL
 *      Tabella hash allocata correttamente
 *      Formattazione del file corretta
 * 
 * Post-condizione:
 *      Tabella hash creata correttamente con le prenotazioni
 *      Disponibilita` aggiornata in caso data corrente sia uguale a quella locale
 *      Chiusura del file avvenuta correttamente
 *      NuovaTabellaHash, chiudiFile, ottieniData, LiberaTabellaHash, controllotoken, NuovaPrenotazione, modificaDisponibilita devono essere implemetate correttamente    
 * 
 * Ritorna:
 *      La tabella hash aggiornata con i dati o a NULL in caso non vi siano prenotazioni
 * 
 * Effetti collaterali:
 *      Allocata memoria per la tabella hash
 *      Stampa messaggi di errore in caso di: lettura fallita del file, memoria non allocata correttamente, ottenimento data locale fallita, inserimento fallito
 *      Viene liberata memoria in caso di tokenizzazione non corretta
 * ---------------------------------------------------------------------------------------------------------------- 
 */

TabellaHash RiempiTabellaHashDaFile (veicolo *v, int STORICO){
    FILE *file;
    if (STORICO == 1){
        file = fopen ("TC1_input.txt", "r");
    }
    
    if (STORICO == 4){
        file = fopen ("TC4_input.txt", "r");
    }
    if (file == NULL){
        perror ("ERRORE: Lettura dello storico da file fallito.\n");
        return NULL;
    }

    char buffer [1024];
    int contatorePrenotazioni=0;

    while (fgets (buffer, sizeof (buffer), file) != NULL){ contatorePrenotazioni++; }
    rewind (file);

    TabellaHash t = NuovaTabellaHash (contatorePrenotazioni);
    if (t == NULL){
        return NULL;
    }

    if (contatorePrenotazioni == 0){
        if (!(chiudiFile(file))){
            return NULL;
        }
        return t;
    }

    char* dataCorrente = ottieniData();
    if (dataCorrente == NULL){
        printf("ERRORE: Ottenimento data locale fallito.\n");
        LiberaTabellaHash(t);
        return NULL;
    }
    
    fgets(buffer, sizeof(buffer), file); // Leggo a vuoto per partire dalla riga contenente la prenotazione (line 1: "\n")
    while (fgets (buffer, sizeof (buffer), file) != NULL){
        char* token = strtok (buffer, "-");
        if (!(controlloToken (token))){
            free(dataCorrente);
            LiberaTabellaHash(t);
            chiudiFile(file);
            return NULL;
        }
        
        char* nomeUtente = strdup (token);
        if (nomeUtente == NULL){
            free(dataCorrente);
            LiberaTabellaHash(t);
            chiudiFile(file);
            perror ("ERRORE: Inserimento del nome utente della prenotazione nella tabella hash fallito.\n");
            return NULL;
        }

        token = strtok (NULL, "-");
        if (!(controlloToken (token))){
            free(dataCorrente);
            LiberaTabellaHash(t);
            chiudiFile(file);
            free(nomeUtente);
            return NULL;
        }
        
        char* dataPrenotazione = strdup (token);
        if (dataPrenotazione == NULL){
            free(dataCorrente);
            LiberaTabellaHash(t);
            free(nomeUtente);
            chiudiFile(file);
            perror ("ERRORE: Inserimento della data della prenotazione nella tabella hash fallito.\n");
            return NULL;
        }

        for (int k=0; k < 3; k++){
            token = strtok (NULL, "-");
            if (!(controlloToken (token))){
                free(dataCorrente);
                LiberaTabellaHash(t);
                chiudiFile(file);
                free(nomeUtente);
                free(dataPrenotazione);
                return NULL;
            }
        }

        int ID = atoi (token);

        for (int k=0; k < 3; k++){
            token = strtok (NULL, "-");
            if (!(controlloToken (token))){
                free(dataCorrente);
                LiberaTabellaHash(t);
                chiudiFile(file);
                free(nomeUtente);
                free(dataPrenotazione);
                return NULL;
            }
        }

        int IndiceVeicoloScelto = atoi (token);

        token = strtok (NULL, "-");
        if (!(controlloToken (token))){
            free(dataCorrente);
            LiberaTabellaHash(t);
            chiudiFile(file);
            free(nomeUtente);
            free(dataPrenotazione);
            return NULL;
        }

        int IndiceOrarioScelto = atoi (token);

        Prenotazione p = NuovaPrenotazione (ID, nomeUtente, v[IndiceVeicoloScelto], IndiceOrarioScelto, dataPrenotazione);
        if (p == NULL){
            printf("ERRORE: Caricamento della prenotazione da file fallito.\n");
            free(dataCorrente);
            LiberaTabellaHash(t);
            chiudiFile(file);
            free(nomeUtente);
            free(dataPrenotazione);
            return NULL;
        }
        InserisciPrenotazione(t,p);

        if (strcmp(dataCorrente, dataPrenotazione) == 0){
            modificaDisponibilita(v[IndiceVeicoloScelto], IndiceOrarioScelto);
        }
        free(nomeUtente);
        free(dataPrenotazione);
        }

        if (!(chiudiFile(file))){
            free(dataCorrente);
            LiberaTabellaHash(t);
            return NULL;
        }

        free(dataCorrente);

    return t;    
}

/*---------------------------------------------------------------------------------------------------------------- 
 * Funzione: LimitaOrariDisponibili
 * -----------------------
 *  Modifica la disponibilita` degli orari disponibili durante una prenotazione confrontandoli con l'orario locale
 * 
 * 
 * Specifica sintattica:
 *      LimitaOrariDisponibili(veicolo) -> void
 *
 * Parametri:
 *      *v: puntatore a un array di struct veicolo
 * 
 * Specifica semantica:
 *      LimitaOrariDisponibili(*v) -> void
 * 
 * Pre-condizione:
 *      Il puntatore deve essere diverso da NULL e deve puntare all'array di struct veicolo
 *      La struct veicolo deve esistere e diversa da NULL
 *      modificaDisponibilita, ottieniOrarioInizio implementate correttamente
 * 
 * Post-condizione:
 *      Disponibilita` modificata in tempo reale
 * 
 * Ritorna:
 *      Nessun valore
 * 
 * Effetti collaterali:
 *      La disponibilita` viene modificata
 * ---------------------------------------------------------------------------------------------------------------- 
 */

void LimitaOrariDisponibili (veicolo *v){
    time_t t = time (NULL); //ottengo i secondi dal 1 gennaio 1970
    struct tm* data = localtime (&t); //ottengo la data corrente, ma bisogna formattarla
    int oraCorrente = data->tm_hour;
    int minutoCorrente = data->tm_min;

    for (int i=0; i<10; i++){
        for (int k=0; k<8; k++){
            if (ottieniOrarioInizio(v[i], k) <= oraCorrente){
                modificaDisponibilita (v[i], k);
            }
        }
    }
}

/*---------------------------------------------------------------------------------------------------------------- 
 * Funzione: verificaSconto
 * -----------------------
 * La funzione verifica la possibilità di un sconto in determinati intervalli orari prestabiliti e restituisce un tipo float
 * riguardante lo sconto da applicare al calcolo del costo totale del noleggio
 * 
 * Specifica sintattica:
 *      verificaSconto(veicolo, int) -> float
 *
 * Parametri:
 *      v: oggetto veicolo
 *      indiceOrario: indice dell'orario scelto
 * 
 * Specifica semantica:
 *      verificaSconto(v, indiceOrario) -> Percentuale di Sconto
 * 
 * Pre-condizione:
 *      L'oggetto veicolo deve esistere e contenere i dati sugli intervalli orari
 *      IndiceOrario deve essere valido
 *      OttieniOrarioInizio implementato correttamente
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

float verificaSconto (veicolo v, int indiceOrario){
      float orario = ottieniOrarioInizio(v , indiceOrario);
      if (orario >= 20.00 ){
        return 0.7; //Sconto del 30% se l'orario prenotato è dalle 20.00 in poi
      } else if (orario < 9) {
        return 0.85; //Sconto del 15% se l'orario prenotato è prima delle 9.00
      } else return 1.0;
}

/*---------------------------------------------------------------------------------------------------------------- 
 * Funzione: verificaDisponibilità
 * -----------------------
 * Verifica la disponibilita` di un veicolo in un determinato orario
 * 
 * Specifica sintattica:
 *      int verificaDisponibilità (veicolo, int) -> void
 *
 * Parametri:
 *      v: oggetto veicolo
 *      indiceOrario: indice orario scelto
 * 
 * Specifica semantica:
 *      verificaDisponibilità(v, indiceOrario) -> 1 se ottieniDisponibilita restituisce 0 altrimenti 0
 *       
 * Pre-condizione:
 *      L'oggetto veicolo deve esistere e contenere i dati dell'oggetto orari
 *      IndiceOrario valido
 *       ottieniDisponibilita implemetata correttamente 
 * Post-condizione:
 *      Restituisce un intero se ottieniDisponibilita e` 0 o diverso da 0
 * 
 * Ritorna: 
 *      1 se ottieniDisponibilita restituisce 0 altrimenti 0
 * 
 * Effetti collaterali:
 *      Nessun effetto collaterale   
 * ----------------------------------------------------------------------------------------------------------------     
 */

int verificaDisponibilita(veicolo v, int indiceOrario){
    if (ottieniDisponibilita(v, indiceOrario) == 0){
        return 1;
    }
        return 0;
}

/*-----------------------------------------------------------------------------------------------------------------
 * Funzione: stampaOrari
 * ----------------------------------------------------------------------------------------------------------------
 * Stampa a video l'intervallo orario scelto dall'utente con la sua disponibilità (Non disponibile o Disponibile)
 * 
 * Specifica sintattica:
 *      stampaOrari(veicolo) -> void
 *
 * Parametri:
 *      v: struct veicolo
 * 
 * Specifica semantica:
 *      stampaOrari(v) -> void
 *       
 * Pre-condizione:
 *      La struct veidolo deve esistere e contenere dati
 *      stampaDisponibilita, ottieniOrarioInizio e ottieniOrarioFine devono esssere implementate correttamente
 *       
 * Post-condizione:
 *      Nessun valore di ritorno
 * 
 * Ritorna: 
 *      Nessun valore
 * 
 * Effetti collaterali:
 *      Stampa a video la lista degli orari e la loro disponibilita del veicolo   
 * ---------------------------------------------------------------------------------------------------------------- 
 */

void stampaOrari (veicolo v){
        printf("\nLista degli orari del veicolo scelto\n\n");
        for (int k=0; k<8; k++){
            printf (" (%d) %.2f-%.2f ", k, ottieniOrarioInizio(v, k), ottieniOrarioFine(v, k));
        stampaDisponibilita(v, k);
        }
}

/*-----------------------------------------------------------------------------------------------------------------
 * Funzione: controllotoken
 * ----------------------------------------------------------------------------------------------------------------
 * Controlla se il token e` diverso da NULL (tokenizzazione corretta) 
 * 
 * Specifica sintattica:
 *      void controllotoken(char*)-> int
 *
 * Parametri:
 *      token: stringa
 * 
 * Specifica semantica:
 *      controllotoken(token)-> 1 se token diverso da zero altrimenti 0
 *       
 * Pre-condizione:
 *      token deve esistere
 *       
 * Post-condizione:
 *      Se token diverso NULL restituisce 1 altrimenti 0
 * 
 * Ritorna: 
 *      1 se token e` diverso da NULL altrimenti 0     
 * 
 * Effetti collaterali:
 *      Stampa un messaggio di errore in caso il token sia NULL
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

/*---------------------------------------------------------------------------------------------------------------- 
 * Funzione: chiudiFile
 * -----------------------
 *  Funzione che chiudere un file
 * 
 * Specifica sintattica:
 *      chiudiFile(FILE) -> int
 *
 * Parametri:
 *      *file: puntatore a file
 * 
 * Specifica semantica:
 *      chiudiFile(*file) -> 1 se avvenuto con successo altrimenti 0
 * 
 * Pre-condizione:
 *      Puntatore a file diverso da NULL e deve puntare al file
 * 
 * Post-condizione:
 *      File chiuso correttamente
 * 
 * Ritorna:
 *      1 se avvenuto con successo altrimenti 0
 * 
 * Effetti collaterali:
 *      Stampa un messaggio di errore in caso di fallimento nella chiusura del file
 * ---------------------------------------------------------------------------------------------------------------- 
 */

int chiudiFile(FILE* file){ 
    if (fclose (file) != 0){
        perror ("ERRORE: Chiusura del file fallita.\n");
        return 0;
    }
    return 1;
}