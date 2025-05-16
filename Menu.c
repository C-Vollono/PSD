#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Menu.h"
// (1) REGISTRAZIONE (2) LOGIN (3) ESCI
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
    return 0;
  }

  // da sistemare l'opzione 3 del menu di accesso
  while (1){
  	corretto = 1;
 	printf("Inserisca il suo nome utente: "); // Ottiene il nome utente
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    if (strlen(buffer) > 25) {
    	corretto = 0;
    	printf("Nome non valido, lunghezza massima consentita di 25 caratteri alfanumerici \n\n"); // Controlla se il nome utente >25
    } else {
    	for (ptrUtente = buffer; *ptrUtente != '\0'; ptrUtente++){ // Controllo alfanumerico
        	if (!((*ptrUtente  >= 'a' && *ptrUtente  <= 'z') ||
            	(*ptrUtente  >= 'A' && *ptrUtente  <= 'Z') ||
            	(*ptrUtente  >= '0' && *ptrUtente  <= '9')))
			{
            	corretto = 0;
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
        			printf("L'utente risulta gia' registrato\n");
       				return 0;
       			} else {
            		*nomeUtente = malloc((strlen(buffer) + 1) * sizeof(char));
         			if (*nomeUtente == NULL) {
        	   			printf("Nome utente non memorizzato correttamente\n");
        	   			return 0;
         			}
        		strcpy(*nomeUtente, buffer);
				nuovoUtente = fopen("utente.txt", "a");
             	if (nuovoUtente == NULL){
            		printf("Errore nell'apertura dei file utente");
					free(*nomeUtente);
            		return 0;
            	}
            	fprintf(nuovoUtente, "%s\n", *nomeUtente);
				fclose(nuovoUtente);
        		return 1;
                }
       	    case 2: // Operazione per il login
        		if (utenteCorrisponde){ // Utente gia' registrato
         			*nomeUtente = malloc((strlen(buffer) + 1) * sizeof(char));
         			if (*nomeUtente == NULL) {
        	   			printf("Nome utente non memorizzato correttamente\n");
        	   			return 0;
         			}
        	 		strcpy(*nomeUtente, buffer);
        	 		return 1; // Valore per azione con successo
       			} else {
         			printf("L'utente non risulta registrato\n");
         			return 0; // Valore per azione fallita
       			}
       		case 3:
       			printf("Uscita dal programma\n");
       			exit(0);
       		default:
       			printf("Operazione non valida\n");
       			return 0;
     	}
    }
  }
}

char* menuAccesso(){
	char *nomeUtente;
	int operazione;
	while (1){
    	printf("=== Menu di accesso utente ===\n");
    	printf(" (1) Registrazione\n");
    	printf(" (2) Login\n");
    	printf(" (3) Esci\n");
 		printf("Digiti l'operazione da effettuare: ");
    	scanf("%d", &operazione);
		getchar ();
    	if (operazioneAccesso(operazione, &nomeUtente)){
        	break;
      	} else {
        	printf("Effettuare l'accesso\n");
        }
	}
	return nomeUtente;
}


