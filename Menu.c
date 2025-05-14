#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Menu.h"
#include "Prenotazione.h"
#include "Veicolo.h"

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
       // aggiungere la funzione che verifica se l'utente è gia registrato
     if (corretto) {
         nome_utente = malloc((strlen(buffer) + 1) * sizeof(char));
         if (nome_utente == NULL) {
           printf("!!! Nome utente non memorizzato correttamente");
           exit(1);
         }
         strcpy(nome_utente, buffer);
         break;
     }
 }

}

void main (char* nome_utente){

    printf ("===== BENVENUT* %s NEL NOSTRO CAR-SHARING =====", nome_utente);
    printf ("=== MENU ===");

    printf ("1) Nuova Prenotazione\n2) Visualizza storico prenotazione\n3) Visualizza Sconti\n4) Visualizza Veicoli\n5) Annulla Prenotazione\n6) Logout\n");

    int scelta;

    printf ("Scelga l'operazione da effettuare (da 1-6): ");
    scanf ("%d", &scelta);

    switch (scelta){

        case 1:
            printf ("Bene, innanzitutto scelga il veicolo che le interessa: ");

            for (int i=0; i<10; i++){

                stampaVeicolo ()
            }
    }







}



