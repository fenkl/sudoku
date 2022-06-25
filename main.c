#include "bibliothek.h"
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>


int main()
{
    int level_difficulty = Difficulty();                        // Level abfragen

    system("cls");                                              // Console leeren


    int* bekannte_Zahlen;                                       // Pointer wird erstellt, indem die Speicheradresse des Array gespeichert wird
    //int* loesung_Sudoku;  //!!! Hier muss irgendwie das Lösungs_Sudoku noch rein, passend zu dem auszufüllenden Sudoku
            static int loesung_Sudoku[9][9]={
                    {6,4,1,2,9,8,5,3,7},
                    {3,5,2,1,7,6,9,8,4},
                    {7,9,8,3,4,5,1,6,2},
                    {9,2,3,6,1,4,8,7,5},
                    {1,8,6,5,3,7,4,2,9},
                    {5,7,4,9,8,2,6,1,3},
                    {8,3,5,7,6,9,2,4,1},
                    {4,1,9,8,2,3,7,5,6},
                    {2,6,7,4,5,1,3,9,8},
                 };

    bekannte_Zahlen = sudoku_level(1);                          // = array mit den bekannten Zahlen des Sudokus; Level holen, welches bearbeitet werden soll

    // Kopie des Arrays erstellen
    int array_zur_Bearbeitung[9][9];
    int zaehler_aufbau_fuellen = 0;

    for (int i=0; i<9; i++)
    {
        for (int j=0; j<9; j++)
        {
            array_zur_Bearbeitung[i][j] = *(bekannte_Zahlen + zaehler_aufbau_fuellen);
            //printf("%d\n", array_zur_Bearbeitung[i][j]);
            zaehler_aufbau_fuellen += 1;
        }
    }

    level_anzeige(bekannte_Zahlen);

    printf("\n\nZum endgueltigen Beenden und Ueberpruefen ENTER druecken");

    long start = GetTickCount()/1000.0;                                 // start Zeitmessung


    int* ausgefuelltes_Sudoku;
    ausgefuelltes_Sudoku = Array_ausfuellen_lassen(bekannte_Zahlen, array_zur_Bearbeitung);    //play

    system("cls");

    long end = GetTickCount()/1000.0;                                   // Ende Zeitmessung
    long needed_time = end - start;  // Gesamter Zeitverbrauch

    // Ausgabe der Zeit
    if (needed_time > 60) // Zeitumrechnung in Minuten, wenn notwendig
    {
        printf("\n\nBenoetigte Zeit: %ld Minuten", needed_time / 60);
    }
    else // ansonsten ausgabe in Sekunden
    {
        printf("\n\nBenoetigte Zeit: %ld Sekunden", needed_time);
    }


    Ueberpruefung_der_Loesung(ausgefuelltes_Sudoku, loesung_Sudoku);


    return 0;
}
