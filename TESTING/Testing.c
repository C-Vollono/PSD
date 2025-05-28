#include <stdio.h>
#include <stdlib.h>
#include "Prenotazione.h"
#include "TabellaHash.h"
#include "Utile.h"

/*---------------------------------------------------------------------------------------------------------------- 
 * Funzione: StampaVeicoliFile
 * -----------------------
 *  Stampa su file di output le rispettive disponibilità per tutte le fasce orarie del veicolo (riferimento indice)
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


int StampaVeicoliFile (){

    FILE* file = fopen ("TC3_input.txt", "r");
    FILE* output = fopen("TC3_output.txt", "w");
    if (file == NULL){
        perror ("Errore apertura file input.");
        return 0;
    }

    int indiceVeicolo, indiceOrario, disponibile;
    int i = 0;
    fscanf (file, "%d", &indiceVeicolo);
    while (indiceVeicolo != 10){
    fprintf(output, "%d ", indiceVeicolo);
    while (i < 8){
        fscanf(file, "%d", &indiceOrario);
        fscanf(file, "%d", &disponibile);
        fprintf(output, "%d %d ", indiceOrario, disponibile);
        i++;
    }
    fputc('\n', output);
    fscanf (file, "%d", &indiceVeicolo);
    i = 0;
    }
    return (chiudiFile(output) && chiudiFile(file));
}

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

int confrontofile(char *nomefileoutput,char *nomefileoracle, int OPERAZIONE){
    int status;
    FILE *fileOutput = fopen(nomefileoutput,"r");
    if(fileOutput == NULL){
        perror("ERRORE: Apertura del file di output fallita.\n");
        return 0;
    }
    
    FILE *fileOracle = fopen(nomefileoracle, "r");

    if(fileOracle == NULL){
        perror("ERRORE: Apertura del file di oracolo fallita.\n");
        return 0;
    }

    char output[250];
    char oracle[250];

    while (fgets(output, sizeof(output), fileOutput) != NULL && fgets(oracle, sizeof(oracle), fileOracle )!=NULL){
            output[strcspn(output, "\n")] = '\0';
            oracle[strcspn(oracle, "\n")] = '\0';
            if(strcmp(output, oracle)==0){
                status = 1; //PASS
            } else {
                status = 0;
                break;
            }
        }
    
    FILE* fileResult = fopen("result.txt", "a");
        if(fileResult == NULL){
            perror("ERRORE: Apertura file result fallita.\n");
            return 0;
        }

        if(status){
            fprintf(fileResult, "TC%d-PASS\n", OPERAZIONE);
        } else {
            fprintf(fileResult,"TC%d-FAIL\n", OPERAZIONE);
        }
        return (chiudiFile(fileOutput) && chiudiFile(fileOracle) && chiudiFile(fileResult));
}

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

int stampaCostofile(Prenotazione p) {
    FILE *fileOutput= fopen("TC2_output.txt", "w");
    if(fileOutput == NULL){
        perror("ERRORE: Apertura file output fallita.\n");
        return 0;
    }
    fprintf(fileOutput, "%.2f\n", ottieniCostoNoleggio(p));
    printf("Ecco il costo del noleggio: %.2f\n", ottieniCostoNoleggio(p));
    return chiudiFile(fileOutput);
}

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

int controlloStorico(TabellaHash t){
    FILE *storicoOutput = fopen("TC4_output.txt", "w");
    if (storicoOutput == NULL) {
        printf("Errore nell'apertura del file.\n");
        return 0;
    }
    int g = ottieniTaglia(t);
    for(int i = 0; i < g; i++) {
        Prenotazione p = ottieniPrenotazione(t,i);
        while (p != NULL) {
            fprintf(storicoOutput, "\n%s-%s-%.2f-%.2f-%s-%s", 
                    ottieniNomeUtente(p), ottieniDataPrenotazione(p), 
                    ottieniInizioPrenotazione(p), ottieniFinePrenotazione(p), 
                    ottieniModelloPrenotazione(p), ottieniTargaPrenotazione(p));
                    printf("HO STAMPATO LA PRENOTAZIONE ID %d\n", i);
            p = ottieniNext(p);  // Passa alla prossima prenotazione nella lista collegata
        }
    }
    return chiudiFile(storicoOutput);
}


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
int stampaDisponibilitaFile (veicolo v, int indiceOrario){
    FILE *file = fopen("TC1_output.txt", "a");
    if(file==NULL){
        perror("ERRORE APERTURA DEL FILE!");
        return 0;
    }

    if ((ottieniDisponibilita(v,indiceOrario))%2 == 1){
        fprintf(file, "Ora: %.2f-%.2f Non disponibile ", ottieniOrarioInizio(v,indiceOrario), ottieniOrarioFine(v,indiceOrario));
    }
    else{
        fprintf(file, "Ora: %.2f-%.2f Disponibile ", ottieniOrarioInizio(v,indiceOrario), ottieniOrarioFine(v,indiceOrario));
    }
    return chiudiFile(file);
}