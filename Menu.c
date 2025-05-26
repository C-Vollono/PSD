/*ATTENZIONE: Nel codice sono presenti comandi system
              Implementati per la pulizia del terminale
              Potrebbero creare conflitti o problemi di vari natura
              "Annullarli" nel caso della presenza di quest'ultimi*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Menu.h"
/* (1) REGISTRAZIONE (2) LOGIN (3) ESCI
 * 
 *	LEGENDA VALORI DI RITORNO
 *  
 *  -1: Errore nell'esecuzione
 *  1: Accesso corretto
 *  0: Utente già registrato
 *  2: Utente non registrato
 *  3: Operazione non valida
*/

/*---------------------------------------------------------------------------------------------------------------- 
 * Funzione: operazioneAccesso
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

int operazioneAccesso (char operazione, char **nomeUtente){
  char bufferUtente[1024];
  char bufferFileUtente[1024];
  FILE *utentiRegistrati = fopen("utente.txt", "r");
  FILE *nuovoUtente;
  int corretto; //variabile che verifica la correttezza del nome utente
  int utenteCorrisponde = 0;
  char* ptrUtente;

  if (utentiRegistrati == NULL){
    printf("ERRORE: Apertura del file degli utenti registrati fallita.\n");
    return -1;
 }

  if (operazione == '3'){
	system("cls | clear");
    printf("Uscita dal programma\n");
    exit(0);
  } else if (operazione < '1' || operazione > '3'){
	system("cls | clear");
	return 3;
 }

  while (1){
  	corretto = 1;
	system("cls | clear");
	printf("\nVALIDI SOLO CARATTERI ALFANUMERICI, MAX. 25 CARATTERI\n\n");
 	printf("Inserisca il suo nome utente: "); 
    fgets(bufferUtente, sizeof(bufferUtente), stdin);
	bufferUtente[strcspn(bufferUtente, "\n")] = '\0';

    if (strlen(bufferUtente) > 25) {
    	corretto = 0;
		system("cls | clear");
    	printf("Nome inserito non valido, la lunghezza massima consentita e' di 25 caratteri alfanumerici \n\n");
    } else {
    	for (ptrUtente = bufferUtente; *ptrUtente != '\0'; ptrUtente++){
        	if (!((*ptrUtente  >= 'a' && *ptrUtente  <= 'z') ||
            	(*ptrUtente  >= 'A' && *ptrUtente  <= 'Z') ||
            	(*ptrUtente  >= '0' && *ptrUtente  <= '9'))){
              corretto = 0;
			  system("cls | clear");
              printf("Nome inserito non valido, si possono utilizzare solo caratteri alfanumerici! \n\n");
              break;
            }
        }
    }

    if (corretto) { 
    	while (fgets(bufferFileUtente, sizeof(bufferFileUtente), utentiRegistrati) != NULL){
    		bufferFileUtente[strcspn(bufferFileUtente, "\n")] = '\0';
    		if (strcmp(bufferFileUtente, bufferUtente) == 0){
            	utenteCorrisponde = 1;
                break;
            }
        }

        if (fclose(utentiRegistrati) != 0){
			system("cls | clear");
        	perror ("ERRORE: Chiusura del file degli utenti fallita.\n");
        	return -1;
		}
		int operazioneInt = operazione - '0';

    	switch (operazioneInt){
    		case 1:
      			if (utenteCorrisponde){
					system("cls | clear");
       				return 0;
       			} else {

            		*nomeUtente = malloc((strlen(bufferUtente) + 1) * sizeof(char));
         			if (*nomeUtente == NULL) {
						system("cls | clear");
        	   			printf("ERRORE: Allocazione registrazione nome utente fallita.\n");
        	   			return -1;
         			}
        			strcpy(*nomeUtente, bufferUtente);
					nuovoUtente = fopen("utente.txt", "a");
             		if (nuovoUtente == NULL){
					system("cls | clear");
            		printf("ERRORE: Apertura del file degli utenti registrati per la creazione del nuovo utente fallita.\n");
					free(*nomeUtente);
            		return -1;
            	}
            	fprintf(nuovoUtente, "%s\n", *nomeUtente);
				if (fclose(nuovoUtente) != 0){
					free(*nomeUtente);
					system("cls | clear");
       				perror ("ERRORE: Chiusura del file degli utenti registrati fallita.\n");
       				return -1;
				}
				system("cls | clear");
        		return 1;

            }
       	    case 2: 
        		if (utenteCorrisponde){ 
         			*nomeUtente = malloc((strlen(bufferUtente) + 1) * sizeof(char));
         			if (*nomeUtente == NULL) {
					system("cls | clear");
        	   		printf("ERRORE: Allocazione nome utente per l'accesso fallita.\n");
        	   		return -1;
         			}
        	 		strcpy(*nomeUtente, bufferUtente);
					system("cls | clear");
        	 		return 1; 
       			} else {
					system("cls | clear");
         			return 2; 
       			}
       		default:
				system("cls | clear");
       			return 3;
     	}
    }
  }
}

/*---------------------------------------------------------------------------------------------------------------- 
 * Funzione: menuAccesso
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

char* menuAccesso(){

	char *nomeUtente;
	char operazione;
	int risultatoOperazione;
	system("cls | clear"); // Pulizia dopo la prima run del programma
	while (1){
		int s2;
		char sceltaIndice[1024];
            while (1){
				printf("=== Menu di accesso utente ===\n");
    			printf(" (1) Registrazione\n");
    			printf(" (2) Login\n");
    			printf(" (3) Esci\n");
 				printf("Digiti l'operazione da effettuare: ");
                fgets(sceltaIndice, sizeof(sceltaIndice), stdin);
				int i=0;
                sceltaIndice[strcspn(sceltaIndice, "\n")] = '\0';
                if (strlen(sceltaIndice) == 1 && sceltaIndice[0] >= '0' && sceltaIndice[0] <= '3'){
					operazione = sceltaIndice[0];
                    break;
                } else {
                    system("cls | clear");
					printf("L'operazione scelta non e' valida, riprovare.\n\n");
                }
    	    }

		risultatoOperazione = operazioneAccesso(operazione, &nomeUtente);

    	switch (risultatoOperazione){
			case 1: return nomeUtente;
			case 0: printf("L'utente risulta gia' registrato, effettuare il login.\n\n"); break;
			case 2: printf("L'utente non risulta registrato, effettuare la registrazione.\n\n"); break;
			case 3: printf("L'operazione scelta non e' valida, riprovare.\n\n"); break;
			default: printf("Si e' verificato un errore ci scusiamo per il disagio, la invitiamo a riprovare l'accesso.\n\n"); break;
		}
	}
}

/*---------------------------------------------------------------------------------------------------------------- 
 * Funzione: menuPrincipale
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

int menuPrincipale(){
	printf ("\nVuole tornare al menu principale? (Y o N): ");
	char scelta;
	while (1){
        if (scanf (" %c", &scelta) != 1 || getchar() != '\n'){
			printf("La scelta inserita per il ritorno al menu principale non e' valida, riprova: ");
			while(getchar() != '\n'); 
		} else if (scelta == 'Y' || scelta == 'y'){
			system("cls | clear");
            return 0;
        } else if (scelta == 'N' || scelta == 'n') {
            printf ("Quando vuole tornare al menu principale inserisca 'Y': ");
        } else {
            printf ("La sua scelta per il ritorno al menu principale non e' valida, riprovi: ");
        }
    }
}
