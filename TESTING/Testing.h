#include <stdio.h>
#include <stdlib.h>

/*---------------------------------------------------------------------------------------------------------------- 
 * Funzione: StampaVeicoliFile
 * -----------------------
 *  Stampa su file di output le informazioni relative alla disponibilità del veicolo in base alla fascia oraria
 * 
 * Specifica sintattica:
 *      
 *      StampaVeicoliFile() -> int
 * 
 * Parametri:
 * 
 *      Nessuno.
 * 
 * Specifica semantica:
 *
 *      StampaVeicoliFile() -> 0/1      
 * 
 * Pre-condizione:
 *      
 *      Il file "TC3_input.txt" deve esistere ed essere formattato come: indiceVeicolo indiceOrario Disponibilità
 * 
 * Post-condizione:
 *      
 *      Il file "TC3_output.txt" conterrà i veicoli con i rispettivi indici per gli orari e la rispettive disponibilità
 * 
 * Ritorna:
 *      0 se i file non vengono aperti o chiusi correttamente.
 *      1 se i file vengono chiusi correttamente
 * 
 * Effetti collaterali:
 * 
 *      Il file "TC3_output.txt" viene modificato.
 *      Stampa su schermo eventuali messaggi di errore nel caso in cui i file non vengono aperti o chiusi correttamente.
 *      
 * ---------------------------------------------------------------------------------------------------------------- 
 */


int StampaVeicoliFile ();

/*---------------------------------------------------------------------------------------------------------------- 
 * Funzione: confrontoFile
 * -----------------------
 *  Confronta i rispettivi file di output e file di oracolo
 * 
 * Specifica sintattica:
 *      
 *      confrontoFile(char*, char*, int) -> int
 * 
 * Parametri:
 * 
 *      nomefileoutput: nome del file di output 
 *      nomefileoracle: nome del file di oracolo
 *      OPERAZIONE: numero per il corretto riferimento di stampa su result.txt
 * 
 * Specifica semantica:
 *
 *      confrontoFile(nomefileoutput, nomefileoracle, OPERAZIONE) -> 0/1    
 * 
 * Pre-condizione:
 *      
 *      Il file "nomefileoutput.txt" deve esistere.
 *      Il file "nomefileoracle.txt" deve esistere.
 * 
 * Post-condizione:
 *      
 *      Il file "result.txt" conterrá il PASS o FAIL del Test Case.
 * 
 * Ritorna:
 *      0 se i file non vengono aperti o chiusi correttamente.
 *      1 se i file vengono chiusi correttamente
 * 
 * Effetti collaterali:
 * 
 *      Il file "result.txt" viene modificato.
 *      Stampa su schermo eventuali messaggi di errore nel caso in cui i file non vengono aperti o chiusi correttamente.
 *      Lo status del test viene aggiornato ogni riga letta da file.
 *      
 * ---------------------------------------------------------------------------------------------------------------- 
 */

int confrontofile(char *nomefileoutput,char *nomefileoracle, int OPERAZIONE);

/*---------------------------------------------------------------------------------------------------------------- 
 * Funzione: stampaCostofile
 * -----------------------
 * Scrive il costo del noleggio del veicolo
 * 
 * Specifica sintattica:
 *      
 *      stampaCostofile(Prenotazione) -> int
 * 
 * Parametri:
 * 
 *      p: prenotazione di cui trovare il costo noleggio
 * 
 * Specifica semantica:
 *
 *      stampaCostofile(p) -> 0/1
 * 
 * Pre-condizione:
 *      
 *      La prenotazione deve esistere, essere allocata correttamente.
 * 
 * Post-condizione:
 *      
 *      Il file "TC2_output.txt" conterrà il costo del noleggio della prenotazione considerata.
 * 
 * Ritorna:
 * 
 *      0 se i file non vengono aperti o chiusi correttamente.
 *      1 se i file vengono chiusi correttamente
 * 
 * Effetti collaterali:
 * 
 *      Il file "TC2_output.txt" viene modificato.
 *      Stampa su schermo eventuali messaggi di errore nel caso in cui i file non vengono aperti o chiusi correttamente.
 *      Stampa su schermo il resoconto relativo al costo del noleggio per la prenotazione.
 *      
 * ---------------------------------------------------------------------------------------------------------------- 
 */

int stampaCostofile(Prenotazione p);

/*---------------------------------------------------------------------------------------------------------------- 
 * Funzione: controlloStorico
 * -----------------------
 * Scorre la tabella Hash al fine di vedere tutte le prenotazioni effettivamente caricate.
 * 
 * Specifica sintattica:
 *      
 *      controlloStorico(TabellaHash) -> int
 * 
 * Parametri:
 * 
 *      t: tabella hash contenente le prenotazioni effettuate dai clienti
 * 
 * Specifica semantica:
 *
 *      controlloStorico(t) -> 0/1
 * 
 * Pre-condizione:
 *      
 *      La tabella hash deve essere allocata correttamente.
 * 
 * Post-condizione:
 *      
 *      Il file "TC4_output.txt" conterrà lo storico delle prenotazioni caricate effettivamente nella tabella Hash.
 * 
 * Ritorna:
 * 
 *      0 se i file non vengono aperti o chiusi correttamente.
 *      1 se i file vengono chiusi correttamente
 * 
 * Effetti collaterali:
 * 
 *      Il file "TC4_output.txt" viene modificato.
 *      Stampa su schermo eventuali messaggi di errore nel caso in cui i file non vengono aperti o chiusi correttamente.
 *      
 * ---------------------------------------------------------------------------------------------------------------- 
 */


int controlloStorico(TabellaHash t);

/*---------------------------------------------------------------------------------------------------------------- 
 * Funzione: stampaDisponibilitaFile
 * -----------------------
 *  Stampa su file di output le rispettive disponibilità per tutte le fasce orarie del veicolo 
 * 
 * Specifica sintattica:
 *      
 *      stampaDisponibilitaFile(veicolo, int) -> int
 * 
 * Parametri:
 * 
 *      v: veicolo di cui considerare le fasce orarie
 *      indiceOrario: indica di quale orario considerare le disponibilità 
 * 
 * Specifica semantica:
 *
 *      stampaDisponibilitaFile(v,indiceOrario) -> 0/1      
 * 
 * Pre-condizione:
 *      
 *      Il veicolo deve essere allocato correttamente, insieme alle sue fasce orarie e quindi anche le rispettive disponibilità
 * 
 * Post-condizione:
 *      
 *      Il file "TC1_output.txt" conterrà le fasce orarie e le rispettive disponibilità del veicolo
 * 
 * Ritorna:
 *      0 se i file non vengono aperti o chiusi correttamente.
 *      1 se i file vengono chiusi correttamente
 * 
 * Effetti collaterali:
 * 
 *      Il file "TC1_output.txt" viene modificato.
 *      Stampa su schermo eventuali messaggi di errore nel caso in cui i file non vengono aperti o chiusi correttamente.
 *
 * ---------------------------------------------------------------------------------------------------------------- 
 */

int stampaDisponibilitaFile (veicolo v, int indiceOrario);