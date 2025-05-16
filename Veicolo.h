#ifndef VEICOLO_H
#define VEICOLO_H
#include <stdio.h>

/*DEFINIZIONE STRUCT ORARIO*/
typedef struct Orario {

    float inizio; //inizio dell'intervallo orario della possibile prenotazione
    float fine; //fine dell'intervallo orario della possibile prenotazione
    int Disponibilità; // 0 = non disponibile oppure 1 = disponibile

}Orario;

/*DEFINIZIONE STRUCT VETTURA*/
struct Vettura{

    char* tipoVeicolo;
    char* modello;
    char* colore;
    char* targa;
    Orario orari[8]; //Struct annidata per gli orari
    int postiOmologati;
    char* Combustibile;
    int annoDiImmatricolazione;
    float CostoNoleggioOrario; // Costo ad ORA
};

typedef struct Vettura *veicolo;

void stampaVeicolo (veicolo v);

void modificaDisponibilità (veicolo v, int k);

float costoNoleggio (veicolo v, int k);

void riempiVeicoli (veicolo v);

void riempiOrari (veicolo v);

void stampaOrari (veicolo v);

void verificaDisponibilità (veicolo v, int k);

float verificaSconto (veicolo v, int k);

void liberaVeicoli (veicolo v);

void controlloToken (char* token, veicolo v, FILE* file);

#endif