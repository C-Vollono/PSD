-- ADT Veicolo: Array di Struct (Veicolo) --
	Tipo di veicolo: Stringa
	Modello: Stringa
	Colore: Stringa
	Targa: Stringa
	Orari disponibili: array di struct che contiene ogni fascia oraria (con inizio e fine come variabili) e disponibilità (bool)  
	Posti omologati: Intero
	Tipo di combustibile: Stringa
	Anno di immatricolazione: Intero
	Costo noleggio: Float (Costo orario)

-- Funzioni ADT Veicolo --
	
	stampaDettagli(veicolo) -> void  //Lo usiamo in modo iterativo per la stampa della disponibilitá dei veicoli

	modificaDisponibilita(veicolo, int (indice dell'orario scelto nell'array di struct degli orari del veicolo)) -> void // Cambia la disponibilità di una fascia oraria occupata

	CostoNoleggio (int inizio, int fine, veicolo) -> int //Calcola il costo complessivo del noleggio con eventuali sconti applicati al veicolo

	riempiArrayStructVeicolo da file txt esterno

	salvaOrari dopo aver confermato o annullato una prenotazione

---------------------------------------------------------------------------------------

 -- ADT Prenotazione: Tabella Hash  --
	
	struct Hash prenotazione {

		int size;
		struct item **table;
	}

	typedef struct hash* hashtable;

	struct item {

		int *key;
		char* NomeCognomeUtente;
		// Da valutare inserimento campi utente (data di nascita, codice fiscale ecc...)
		char* (stampare tutti i dati del veicolo eccetto la disponibilità di orari)
		char* OrarioScelto;
		Float PagamentoNoleggio;
		Char* ID prenotazione;
		struct item *next;

	}

-- Funzioni ADT Prenotazione --

	hashtable NuovaHashtable (int size);

	int InsertHAsh (hashtable, item);

	struct item *hashSearch (hashtable, char *key);

	struct item *HashDelete (hashtable, vhar *key);

	void DestroyHashtable (hashtable);

	confronta orari prenotazione

	// poi devono essere inserite le funzioni richieste nella traccia

---------------------------------------------------------------------------------------

--PSEUDOCODICE--
	-Chiedere se si è un nuovo utente e si è già registrati.
	-Se si è un nuovo utente, creare account e salvare le credenziali in un file txt esterno.
	-Se si è già registrati, accedere e confrontare le credenziali con quelle salvate nel file txt.
	-Apertura del menu

	-Scelte disponibili nel menu principale: (da fare eventualmente con uno switch)
	Nuova prenotazione
	Visualizza Storico Prenotazioni 
	Visualizza Sconti
	Visualizza Veicoli
	Logout
	Elimina prenotazione

	-Caso 1 (Nuova prenotazione): 
	- Chiedi all'utente l'orario in cui vuole prendere un veicolo
	- Una volta chiesto l'orario, verranno mostrate tutti i veicoli disponibili, con accanto un numero che equivale alla posizione nell'array
	- Chiedi all'utente di scegliere un veicolo scrivendo il numero accanto al veicolo scelto
	- Mostri un riepilogo della prenotazione, stampando i dettagli completi del veicolo scelto, il costo totale per l'orario scelto e applichi eventuali sconti associati a quel veicolo
	-Chiedi all'utente di confermare o annullare la prenotazione
	-Se l'utente conferma, inserisci nell'adt la prenotazione effettuata
	-Se l'utente annulla, torni al menu
	-Torna al menu principale
	// Dopo aver creato una prenotazione, bisogna aggiornare i file txt esterni degli orari e del veicolo per quanto riguarda la disponibilità. Basta sovrascrivere i file esterni txt con i dati aggiornati nelle struct del programma

	-Caso 2 (Visualizza storico prenotazioni):
	-Stampa direttamente tutte le prenotazioni effettuate dal cliente
	-Chiedi all'utente se vuole tornare al menu principale

	-Caso 3 (Visualizza sconti): 
	- Chiedi all'utente se vuole vedere gli sconti per orari specifici oppure per giornata intera:
	- Mostri all'utente gli sconti in base a cosa ha scelto
	-Chiedi all'utente se vuole tornare al menu principale

	-Caso 4 (Visualizza veicoli): 
	-Stampa le caratteristiche di tutti i veicoli disponibili in catalogo //Implementare dopo la ricerca dei veicoli per caratteristiche (Tipo di conbustibile, anno di immatricolazione, posti omologati ecc...)
	- Torna al menu principale

	-Caso 5 (Logout): 
	-Interrompi l'esecuzione del programma

	-Caso 6 (Annulla prenotazione):
	-Chiedi all'utente di inserire l'ID della prenotazione da concellare
	-Cancella prenotazione e torna al menu principale

















	