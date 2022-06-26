/**
* Programm zum Spielen eines Sudokus innerhalb der Konsole
* Autoren: Klara von Lehmden, Francisco Fenkl und Henry Hamker
* Vollendet am: 26.06.2022
**/

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



    long start = GetTickCount()/1000.0;                 //Start der Zeitmesssung
   
    do  //Start der Schleife zum möglichen weiterspielen
    {
        int zero = anzahl_nullen(level);
        system("cls");                                              // Console leeren

        level_anzeige(level);

        printf("\n\n");
        printf("Beenden und Ueberpruefen: ENTER\n");
        printf("Zahl zuruecksetzen:       0\n");
        printf("Cursorsteuerung:          Pfeiltasten");

        level = Array_ausfuellen_lassen(level);    //play

        system("cls");   // Console leeren



        //Variable, zur überprüfung ob Level gelöst wurde
        int finish = Ueberpruefung_der_Loesung(level, zero);

        long end = GetTickCount()/1000.0; //Ende der Zeitmessung


        if(finish==0)   //lösung ist nicht richtig
            {
                printf("\n\n [0]Weiterspielen      [1]Beenden \n");
                scanf("%i",&exit);
                if(exit==0)
                {

                    level=weiterspielen(level);   
                }
                else
                {
                    //level ist nicht gelöst wird aber dennoch beendet
                    zeit_berechnen(start,end); //Bearbeitungszeit wird berechnet und ausgegeben
                    exit = 1;   //Endkriterium ist nun erfüllt
                }
            }
            else    //Lösung ist richtig
                {
                exit = 1;   //Endkriterium ist nun erfüllt
                zeit_berechnen(start,end);     //Bearbeitungszeit wird berechnet und ausgegeben 
                printf("\n Herzlichen Glueckwunsch, Du hast das Sudoku erfolgreich geloest!");
                }
    }
    while(exit == 0 );//Falls weiterspielen erwünscht ist wird die Schleife weiter ausgeführt


    return 0;
}
