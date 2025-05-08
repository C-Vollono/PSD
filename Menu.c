#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Menu.h"

void menu_accesso(){
 char *nome_utente;
 char* ptr_utente;
 int corretto;
 char buffer[1024];
 while (1){
     corretto = 1;
     printf("=== Menu di accesso utente ===\n");
     printf("Inserisca il suo nome utente: ");
     fgets(buffer, sizeof(buffer), stdin);
     buffer[strcspn(buffer, "\n")] = '\0';
     if (strlen(buffer) > 25){
         corretto = 0;
         printf("!!! Nome non valido, lunghezza massima consentita di 25 caratteri alfanumerici \n\n");
         break;
     } else {
         for (ptr_utente = buffer; *ptr_utente != '\0'; ptr_utente++){
             if (!((*ptr_utente  >= 'a' && *ptr_utente  <= 'z') ||
                   (*ptr_utente  >= 'A' && *ptr_utente  <= 'Z') ||
                   (*ptr_utente  >= '0' && *ptr_utente  <= '9')))
             {
                 corretto = 0;
                 printf("!!! Nome non valido, utilizzare solo caratteri alfanumerici! \n\n");
                 break;
             }
         }
       }
     if (corretto) {
         nome_utente = malloc((strlen(buffer) + 1) * sizeof(char));
         if (nome_utente == NULL) {
           printf("!!! Nome utente non memorizzato correttamente");
           exit(1)
         }
         strcpy(nome_utente, buffer);
         break;
     }
 }
  menu_utente(nome_utente, v, indice_veicolo);
}

/* void menu_utente(nome_utente, veicolo v, int indice_veicolo){
     int op_utente;
     while (1){
     printf("=== Menu utente - Benvenuto %s ==\n", nome_utente);
     printf("1. Nuova prenotazione \n");
     printf("2. Visualizza veicoli disponibili\n");
     printf("3. Visualizza storico prenotazioni\n");
     printf("4. Visualizza sconti\n");
     printf("5. Elimina prenotazione \n");
     printf("6. Esci dalla sessione utente\n");
     // Considerare una 7. opzione per un preventivo del noleggio
     switch(op_utente){
       case 1: prenotazione(nome_utente); break;
       case 2: {
              for (int i=0; i < indice_veicolo; i++){
                  stampaVeicolo(v[i]);
              }
       } break;
       case 3: visualizzastorico(nome_utente, ...); break;
       case 4: da discutere; break;
       case 5: hashdelete(hashtable, char* key);
       case 6: return;
       default: printf("Operazione non consentita"); break;
      }
     }
} */


