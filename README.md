# Car Sharing – Sistema per il noleggio di veicoli  

## Descrizione  
**Car Sharing** (progettato per un esame di Programmazione e strutture dati) è un sistema software progettato per la gestione e l’ottimizzazione del servizio di car sharing. L’applicazione consente agli utenti di visualizzare la disponibilità dei veicoli, effettuare prenotazioni e consultare lo storico dei noleggi in modo strutturato ed efficiente oltre che ricercare prenotazioni precedenti con un ID apposito.  

## Caratteristiche principali  
- **Gestione dei veicoli**: Monitoraggio dei mezzi disponibili per il noleggio.  
- **Sistema di prenotazione**: Registrazione delle prenotazioni con verifica della disponibilità.  
- **Storico delle prenotazioni**: Consultazione delle prenotazioni passate.
- **Ricerca veloce delle prenotazioni**: Possibilita` di trovare prenotazioni singole velocemente tramite ID univoco.
- **Sistema di visualizzazione degli sconti**: Consultazione degli sconti applicabili in determinate circostanze.
- **Interfaccia interattiva**: Struttura intuitiva per facilitare l’uso del sistema.  

## Modalità di utilizzo  
1. **Avvio dell’applicazione** e accesso al menu di autenticazione (Registrazione o Login).  
2. **Accesso al menu principale** e scelta del servizio richiesto.
3. **Prenotare un veicolo** tramite scelta di quest'ultimo e orario a seconda della disponibilita`.
4. **Visualizza catalogo veicoli** e avere una lista completa di tutti i veicoli presenti.
5. **Visualizza storico delle prenotazioni** e avere una lista di tutte le prenotazioni effettuate con tutte le informazioni.
6. **Aggiornamento sugli sconti** cosi` da sapere quando e dove vengono applicati eventuali sconti.
7. **Ricerca di una prenotazione** se si vuol leggere le informazioni di una determinata prenotazione.
8. **Uscita dal software** concluse tutte le operazioni richieste.

## Implementazione  
Il sistema è sviluppato in linguaggio C e utilizza strutture dati avanzate per ottimizzare la gestione delle prenotazioni e dei veicoli. I moduli principali includono:  
- `Veicolo.c/h`: Definizione e gestione dei veicoli.  
- `Prenotazione.c/h`: Implementazione del sistema di prenotazione.  
- `TabellaHash.c/h`: Struttura dati per l’archiviazione efficiente delle prenotazioni.  
- `Menu.c/h`: Interfaccia per l’interazione con l’utente.
- `Utile.c/h`: Implementazione di funzioni aggiuntive utili al software

## Installazione e utilizzo  
1. Clonare il repository del progetto.  
2. Compilare il codice utilizzando il `Makefile`.  
3. Avviare l’applicazione ed esplorare le funzionalità disponibili.  

## Autori  
Progetto sviluppato da **FrancescoGaetanoVentriglia**, **CristianVollono**, **AntonioRuotolo**. 

---

📌 **Nota**: Per ulteriori dettagli tecnici, consultare la documentazione e i file sorgente presenti nel repository. 
