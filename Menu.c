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

int operazioneAccesso (int operazione, char **nomeUtente){
  char bufferUtente[1024];
  char bufferFileUtente[1024];
  FILE *utentiRegistrati = fopen("utente.txt", "r");
  FILE *nuovoUtente;
  int corretto; //variabile che verifica la correttezza del nome utente
  int utenteCorrisponde = 0;
  char* ptrUtente;

  if (utentiRegistrati == NULL){
    printf("Errore nell'apertura dei file utenti");
    return -1;
 }

  if (operazione == 3){

	system("cls | clear");
    printf("Uscita dal programma\n");
    exit(0);
 } 
 else if (operazione < 1 || operazione > 3){

	system("cls | clear");
	return 3;
 }

  while (1){

  	corretto = 1;

 	printf("Inserisca il suo nome utente: "); // Ottiene il nome utente

    fgets(bufferUtente, sizeof(bufferUtente), stdin);
	bufferUtente[strcspn(bufferUtente, "\n")] = '\0';

    if (strlen(bufferUtente) > 25) {

    	corretto = 0;
		system("cls | clear");
    	printf("Nome non valido, lunghezza massima consentita di 25 caratteri alfanumerici \n\n");

    } else {
    	for (ptrUtente = bufferUtente; *ptrUtente != '\0'; ptrUtente++){
        	if (!((*ptrUtente  >= 'a' && *ptrUtente  <= 'z') ||
            	(*ptrUtente  >= 'A' && *ptrUtente  <= 'Z') ||
            	(*ptrUtente  >= '0' && *ptrUtente  <= '9')))
			{
            	corretto = 0;
				system("cls | clear");
            	printf("Nome non valido, utilizzare solo caratteri alfanumerici! \n\n");
            	break;
            }
        }
    }

    if (corretto) { //controllo se l'utente è già registrato

    	while (fgets(bufferFileUtente, sizeof(bufferFileUtente), utentiRegistrati) != NULL){

    		bufferFileUtente[strcspn(bufferFileUtente, "\n")] = '\0';

    		if (strcmp(bufferFileUtente, bufferUtente) == 0){

            	utenteCorrisponde = 1;
                break;
            }
        }

        if (fclose(utentiRegistrati) !=0){

			system("cls | clear");
        	perror ("Errore nella chiusura del file.");
        	exit (1);
		}

    	switch (operazione){
    		case 1:
      			if (utenteCorrisponde){

					system("cls | clear");
       				return 0;

       			} else {

            		*nomeUtente = malloc((strlen(bufferUtente) + 1) * sizeof(char));

         			if (*nomeUtente == NULL) {

						system("cls | clear");
        	   			printf("Nome utente non memorizzato correttamente\n\n");
        	   			return -1;
         			}

        			strcpy(*nomeUtente, bufferUtente);

					nuovoUtente = fopen("utente.txt", "a");

             		if (nuovoUtente == NULL){

					system("cls | clear");
            		printf("Errore nell'apertura dei file utente\n\n");
					free(*nomeUtente);
            		return -1;
            	}

            	fprintf(nuovoUtente, "%s\n", *nomeUtente);

				if (fclose(nuovoUtente) != 0){

					system("cls | clear");
       				perror ("Errore nella chiusura del file.");
       				exit (1);
				}
				system("cls | clear");

        		return 1;

            }
       	    case 2: 
        		if (utenteCorrisponde){ 

         		*nomeUtente = malloc((strlen(bufferUtente) + 1) * sizeof(char));

         			if (*nomeUtente == NULL) {

					system("cls | clear");
        	   		printf("Nome utente non memorizzato correttamente\n\n");
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
	char inputOperazione[10];
	int operazione;
	int risultatoOperazione;

	while (1){

    	printf("=== Menu di accesso utente ===\n");
    	printf(" (1) Registrazione\n");
    	printf(" (2) Login\n");
    	printf(" (3) Esci\n");

 		printf("Digiti l'operazione da effettuare: ");

		fgets(inputOperazione, sizeof(inputOperazione), stdin);

		inputOperazione[strlen(inputOperazione)-1] = '\0';

		operazione = atoi(inputOperazione);

		risultatoOperazione = operazioneAccesso(operazione, &nomeUtente);

    	switch (risultatoOperazione){
			case 1: {
				return nomeUtente;
			}
			case 0: {
				printf("L'utente risulta gia' registrato, effettuare il login\n\n");
				break;
			}
			case 2: {
				printf("L'utente non risulta registrato, effettuare la registrazione\n\n");
				break;
			}
			case 3: {
				printf("L'operazione da lei scelta non e' valida, riprovare\n\n");
				break;
			}
			default: {
				printf("Ci scusiamo per il disagio, e' pregato di riprovare l'accesso\n\n");
				break;
			}

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

int menuPrincipale(char scelta){

	printf ("\nVuole tornare al menu principale? (Y o N): ");

	while (1){
        if (scanf (" %c", &scelta) != 1 || getchar() != '\n'){

			printf("Scelta non valida, riprova: ");
			for (; getchar() != '\n';);

		} else if (scelta == 'Y' || scelta == 'y'){

			system("cls | clear");
            return 0;

        } else if (scelta == 'N' || scelta == 'n') {

                printf ("Quando vuole tornare al menu principale inserisca 'Y': ");

        } else {
			
                printf ("Scelta non valida, riprova: ");
        }
    }
}
