#include "bibliothek.h"
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

int main()
{

    struct Level level;

    int choosed_level = Difficulty();                        // Level abfragen

    system("cls");                                              // Console leeren

    level = sudoku_level_initialisition(choosed_level);                         // = array mit den bekannten Zahlen des Sudokus; Level holen, welches bearbeitet werden soll

    level_anzeige(level);
    printf("\n\n");
    printf("Beenden und Ueberpruefen: F3\n");
    printf("Zahl zuruecksetzen:       0");

    long start = GetTickCount()/1000.0;                                 // start Zeitmessung


    int ausgefuelltes_Sudoku;
    level = Array_ausfuellen_lassen(level);    //play

    system("cls");




    long end = GetTickCount()/1000.0;                                   // Ende Zeitmessung
    long needed_time = end - start;  // Gesamter Zeitverbrauch

    // Ausgabe der Zeit
    if (needed_time > 300) // Zeitumrechnung in Minuten ab 5 Minuten
    {
        printf("\n\nBenoetigte Zeit: %ld Minuten\n", needed_time / 60);
    }
    else // ansonsten ausgabe in Sekunden
    {
        printf("\n\nBenoetigte Zeit: %ld Sekunden\n", needed_time);
    }


    Ueberpruefung_der_Loesung(level);

    return 0;
}
