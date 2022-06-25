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
    printf("Beenden und Ueberpruefen: ENTER\n");
    printf("Zahl zuruecksetzen:       0");

    long start = GetTickCount()/1000.0;                                 // start Zeitmessung


    int ausgefuelltes_Sudoku;
    level = Array_ausfuellen_lassen(level);    //play

    system("cls");

    long end = GetTickCount()/1000.0;                                   // Ende Zeitmessung
    long needed_time = end - start;  // Gesamter Zeitverbrauch
    long needed_minutes, needed_seconds;
    needed_seconds = needed_time;
    // Ausgabe der Zeit
    if (needed_seconds >= 60) // Zeitumrechnung in Minuten ab 5 Minuten
    {
        needed_minutes = needed_time / 60;
        needed_seconds = needed_time - (needed_minutes * 60);
        if (needed_minutes == 1)
        {
            printf("\n\nBenoetigte Zeit insgesamt: %ld Minute und %ld Sekunden\n", needed_minutes, needed_seconds);
        }
        else
        {
            printf("\n\nBenoetigte Zeit insgesamt: %ld Minuten und %ld Sekunden\n", needed_minutes, needed_seconds);
        }
    }
    else // ansonsten ausgabe in Sekunden
    {
        printf("\n\nBenoetigte Zeit insgesamt: %ld Sekunden\n", needed_seconds);
    }


    Ueberpruefung_der_Loesung(level);

    return 0;
}
