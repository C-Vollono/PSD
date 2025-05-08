-- ADT Veicolo --
	
	struct Vettura{
	Tipo di veicolo: Stringa
	Modello: Stringa
	Colore: Stringa
	Targa: Stringa
	struct Orari disponibili{  //array di struct delle fascie orarie
		float inizio
		float fine
		int disponibilità (booleano)
	}  
	Posti omologati: Intero
	Tipo di combustibile: Stringa
	Anno di immatricolazione: Intero
	Costo noleggio: Float (Costo orario)
	}

-- Funzioni ADT Veicolo --
	
	stampaVeicolo(veicolo) -> void;  //stampa i dati del veicolo e la sua disponibilità

	modificaDisponibilita(veicolo, int k) -> void; // Cambia la disponibilità di una fascia oraria occupata nella struct Orari

	CostoNoleggio (veicolo, int k) -> float; //Calcola il costo complessivo del noleggio con eventuali sconti applicati all'orario

	riempiVeicoli (veicolo, char* nomefile) -> void; //prende i dati dal file Veicoli.txt e li inserisce nell'array di struct dell'ADT Veicolo

	riempiOrari(veicolo, char*file) -> void; //prende i dati dal file Orari.txt e li inserisce nella struct annidata Orari dell'ADT Veicolo
	
	stampaOrari(veicolo) -> void // stampa gli orari disponibili del veicolo

	verificaDisponibilità(veicolo, int k) -> void //stampa a video se un veicolo è disponibile o meno in una determinata fascia oraria

	verificaSconto(veicolo, int k) -> float //Restituisce la percentuale di sconto da applicare nel costo del noleggio in determinati orari altrimenti nessuno

	aggiornaOrari(veicolo, char* nomefile, int i, int k) -> void //Aggiorna gli orari nel file Orari.txt dopo una prenotazione effettuata

	liberaVeicoli(veicolo) -> void //Deallocazione della memoria

---------------------------------------------------------------------------------------------------------------------------------------------

 -- ADT Prenotazione --
	
	struct item {

		char* key; //ID prenotazione
		char* NomeUtente;
		veicolo v;
		char* OrarioScelto; //Da valutare il tipo di dato del campo
		Float CostoNoleggioFinale;

	}

-- Funzioni ADT Prenotazione --

	// Da discutere

---------------------------------------------------------------------------------------------------------------------------------------------

--PSEUDOCODICE--
	-Chiedere se si è un nuovo utente e si è già registrati.
	-Se si è un nuovo utente, creare account e salvare le credenziali in un file txt esterno.
	-Se si è già registrati, accedere e confrontare le credenziali con quelle salvate nel file txt.
	-Apertura del menu

	-Scelte disponibili nel menu principale: (da fare con uno switch)
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
	-Stampa direttamente tutte le prenotazioni effettuate dal cliente //Chiedere per il salvataggio
	-Chiedi all'utente se vuole tornare al menu principale

	-Caso 3 (Visualizza sconti): 
	- Chiedi all'utente se vuole vedere gli sconti per orari specifici
	- Mostri all'utente gli sconti in base a cosa ha scelto
	-Chiedi all'utente se vuole tornare al menu principale

	-Caso 4 (Visualizza veicoli): 
	-Stampa le caratteristiche di tutti i veicoli disponibili in catalogo //Implementare dopo la ricerca dei veicoli per caratteristiche (Tipo di conbustibile, anno di immatricolazione, posti omologati ecc...)
	- Torna al menu principale

	-Caso 5 (Logout): 
	-Interrompi l'esecuzione del programma

	-Caso 6 (Annulla prenotazione):
	-Chiedi all'utente di inserire l'ID della prenotazione da concellare
	-Cancella prenotazione e torna al menu principale //aggiornare file txt