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
int operazioneAccesso (int operazione, char **nomeUtente){
  char buffer[1024];
  char bufferFile[1024];
  FILE *utenti = fopen("utente.txt", "r");
  FILE *nuovoUtente;
  int corretto;
  int utenteCorrisponde = 0;
  char* ptrUtente;

  if (utenti == NULL){
    printf("Errore nell'apertura dei file utenti");
    return -1;
  }

  if (operazione == 3){
			system("cls | clear");
       			printf("Uscita dal programma\n");
       			exit(0);
        } else if (operazione < 1 || operazione > 3){\
			system("cls | clear");
			return 3;
		}

  while (1){
  	corretto = 1;
 	printf("Inserisca il suo nome utente: "); // Ottiene il nome utente
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    if (strlen(buffer) > 25) {
    	corretto = 0;
		system("cls | clear");
    	printf("Nome non valido, lunghezza massima consentita di 25 caratteri alfanumerici \n\n"); // Controlla se il nome utente >25
    } else {
    	for (ptrUtente = buffer; *ptrUtente != '\0'; ptrUtente++){ // Controllo alfanumerico
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
    if (corretto) { // Username segue le condizioni
    	while (fgets(bufferFile, sizeof(bufferFile), utenti) != NULL){
    		bufferFile[strcspn(bufferFile, "\n")] = '\0';
    		if (strcmp(bufferFile, buffer) == 0){
            	utenteCorrisponde = 1;
                break;
            }
        }
        fclose(utenti); // Utilizzato solo per il controllo dell'esistenza
    	switch (operazione){
    		case 1:
      			if (utenteCorrisponde){
					system("cls | clear");
       				return 0;
       			} else {
            		*nomeUtente = malloc((strlen(buffer) + 1) * sizeof(char));
         			if (*nomeUtente == NULL) {
						system("cls | clear");
        	   			printf("Nome utente non memorizzato correttamente\n\n");
        	   			return -1;
         			}
        		strcpy(*nomeUtente, buffer);
				nuovoUtente = fopen("utente.txt", "a");
             	if (nuovoUtente == NULL){
					system("cls | clear");
            		printf("Errore nell'apertura dei file utente\n\n");
					free(*nomeUtente);
            		return -1;
            	}
            	fprintf(nuovoUtente, "%s\n", *nomeUtente);
				fclose(nuovoUtente);
				system("cls | clear");
        		return 1;
                }
       	    case 2: 
        		if (utenteCorrisponde){ 
         			*nomeUtente = malloc((strlen(buffer) + 1) * sizeof(char));
         			if (*nomeUtente == NULL) {
						system("cls | clear");
        	   			printf("Nome utente non memorizzato correttamente\n\n");
        	   			return -1;
         			}
        	 		strcpy(*nomeUtente, buffer);
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

char* menuAccesso(){
	char *nomeUtente;
	char inputAzione[100];
	int operazione;
	int risultatoOperazione;
	while (1){
    	printf("=== Menu di accesso utente ===\n");
    	printf(" (1) Registrazione\n");
    	printf(" (2) Login\n");
    	printf(" (3) Esci\n");
 		printf("Digiti l'operazione da effettuare: ");
		fgets(inputAzione, sizeof(inputAzione), stdin);
		inputAzione[strlen(inputAzione)-1] = '\0';
		operazione = atoi(inputAzione);
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
