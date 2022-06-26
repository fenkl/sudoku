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
    int exit=0;



    long start = GetTickCount()/1000.0;
    do{
    int zero = anzahl_nullen(level);
    system("cls");                                              // Console leeren

    level_anzeige(level);

    printf("\n\n");
    printf("Beenden und Ueberpruefen: ENTER\n");
    printf("Zahl zuruecksetzen:       0");



    int ausgefuelltes_Sudoku;


    level = Array_ausfuellen_lassen(level);    //play

    system("cls");




    int finish = Ueberpruefung_der_Loesung(level, zero);

    long end = GetTickCount()/1000.0;

    if(finish==0)
        {
            printf("\n\n [0]Weiterspielen      [1]Beenden \n");
            scanf("%i",&exit);
            if(exit==0)
            {

                level=weiterspielen(level);
            }
            else
            {
                zeit_berechnen(start,end);
            }
        }
        else
            {
            exit = 1;
            zeit_berechnen(start,end);
            printf("\n Herzlichen Glueckwunsch, Du hast das Sudoku erfolgreich geloest!");
            }
    }
    while(exit == 0 );


    return 0;
}
