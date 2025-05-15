#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Menu.h"
#include "Prenotazione.h"
#include "Veicolo.h"

// REGISTRAZIONE LOGIN ESCI
int operazioneAccesso (int operazione, char **nome_utente){
  char buffer[1024];
  char buffer_file[1024];
  FILE *utenti = fopen("utente.txt", "r");
  FILE *nuovo_utente;
  int corretto;
  int utente_corrisponde = 0;
  char* ptr_utente;

  if (utenti == NULL){
    printf("Errore nell'apertura dei file utenti");
    return 0;
  }

  while (1){
         corretto = 1;
 		 printf("Inserisca il suo nome utente: "); // Ottiene il nome utente
    	 fgets(buffer, sizeof(buffer), stdin);
    	 buffer[strcspn(buffer, "\n")] = '\0';
      if (strlen(buffer) > 25) {
         corretto = 0;
         printf("Nome non valido, lunghezza massima consentita di 25 caratteri alfanumerici \n\n"); // Controlla se il nome utente >25
      } else {
         for (ptr_utente = buffer; *ptr_utente != '\0'; ptr_utente++){ // Controllo alfanumerico
             if (!((*ptr_utente  >= 'a' && *ptr_utente  <= 'z') ||
                   (*ptr_utente  >= 'A' && *ptr_utente  <= 'Z') ||
                   (*ptr_utente  >= '0' && *ptr_utente  <= '9')))
             {
                 corretto = 0;
                 printf("Nome non valido, utilizzare solo caratteri alfanumerici! \n\n");
                 break;
             }
         }
       }

     if (corretto) { // Username segue le condizioni
            while (fgets(buffer_file, sizeof(buffer_file), utenti) != NULL){
              buffer_file[strcspn(buffer_file, "\n")] = '\0';
              if (strcmp(buffer_file, buffer) == 0){
                utente_corrisponde = 1;
                break;
              }
            }
     switch (operazione){
       case 1:
      	 if (utente_corrisponde){
        	 printf("L'utente risulta gia' registrato\n");
       		 fclose(utenti);
       		 return 0;
       } else {
            nome_utente = malloc((strlen(buffer) + 1) * sizeof(char));
         	if (nome_utente == NULL) {
        	   printf("Nome utente non memorizzato correttamente\n");
               fclose(utenti);
        	   exit(1);
         	}
        	 strcpy(nome_utente, buffer);
			 nuovo_utente = fopen("utente.txt", "a");
             if (nuovo_utente == NULL){
               printf("Errore nell'apertura dei file utente");
               exit(1);
             }
             fprintf(nuovo_utente, "%s", nome_utente);
             fclose(utenti);
        	 return 1;
       }
       case 2: // Operazione per il login
       if (utente_corrisponde){ // Utente gia' registrato
         nome_utente = malloc((strlen(buffer) + 1) * sizeof(char));
         	if (nome_utente == NULL) {
        	   printf("Nome utente non memorizzato correttamente\n");
               fclose(utenti);
        	   exit(1);
         	}
        	 strcpy(nome_utente, buffer);
             fclose(utenti);
        	 return 1; // Valore per azione con successo
       } else {
         printf("L'utente non risulta registrato\n");
         fclose(utenti);
         return 0; // Valore per azione fallita
       }
       case 3:
       printf("Uscita dal programma\n");
       fclose(utenti);
       exit(1);
       default:
       printf("Operazione non valida\n");
       fclose(utenti);
       return 0;
     }
     }
	}
        }


char* menu_accesso() {
 char *nome_utente;
 int operazione;
 while (1){
     printf("=== Menu di accesso utente ===\n");
     printf(" (1) Registrazione\n");
     printf(" (2) Login\n");
     printf(" (3) Esci\n");
 	 printf("Digiti l'operazione da effettuare: \n");
     scanf("%d", &operazione);
     if (operazioneAccesso(operazione, &nome_utente)){
        break;
      } else {
        printf("Effettuare l'accesso\n");
     }
  return nome_utente;
}
}