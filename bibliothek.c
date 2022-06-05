#include "bibliothek.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>


/**
 * TODO: Beim Verusch des Benutzers in ein Feld zu schreiben, muss die aktuelle Cursorposition
 * mit den "0-Feldern" (schreibbare Felder) abgeglichen werden. Nur dann darf in ein Array
 * geschrieben werden (vlt. ein neues Array anlegen).
 * Die Nullfelder ergeben sich aus der Formatierung in "level_anzeige()" (am besten eigene Funktion
 * für Nullfelder schreiben damit ein einfacher Abruf zum Vergleich stattfinden kann):
 *  +1y , erste Zeile besteht aus Trennern
 *  erste 3 Zahlen liegen in (2,1)(4,1)(6,1), dann wegen des Trenners in (10,1)(12,1)(14,1) und in (18,1)(20,1)(22,1) usw.
 *  bis zur dritten Zeile setzt sich das für y jeweils mit +1 fort
 *  dann aufgrund des Trenners y+=2
**/

/**
 * Quelle: Code von Herrn Wichmann zum Setzen des Konsolencursors (CursorKeys in Moodle)
 * \ingroup KonsolenDemo
 * \brief Sets cursor to a given position on the current console.
 *
 * \param x x-coordinate to be set
 * \param y y-coordinate to be set
 * \return 0 if cursor was set, 1 if failed
 */
int set_cursor(const int x, const int y)
{
    int set_position_failed = 0;
    int return_value = 0;

    HANDLE hstdout;

    COORD coordinates;
    coordinates.X= x;
    coordinates.Y= y;

    hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
    set_position_failed = SetConsoleCursorPosition(hstdout, coordinates);
    // reverse "wrong" return value from Windows API
    if (set_position_failed)
    {
        return_value = 0;
    }
    else
    {
        return_value = 1;
    }

    return return_value;
}



/**
 * main-Funktion aus CursorKeys (von Herrn Wichmann) übernommen und leicht angepasst.
 * getch() fängt Tastatureingaben ab und reagiert auf Pfeiltasten,
 * ruft bei entsprechendem Event set_cursor auf und speichert
 * aktuelle Cursorposition in current_cursor_position x oder y.
**/
int move_cursor()
{
    int set_cursor(const int x, const int y);
    set_cursor(2, 1);
    int current_cursor_position_x = 21;
    int current_cursor_position_y = 1;

    while(1)
    {
        //Keycode-Quelle: "https://docs.microsoft.com/en-us/previous-versions/visualstudio/visual-studio-6.0/aa299374(v=vs.60)"
        switch(_getch())
        {
        case 72:
            current_cursor_position_y -= 1;
            set_cursor(current_cursor_position_x, current_cursor_position_y);
            break;
        case 80:
            current_cursor_position_y += 1;
            set_cursor(current_cursor_position_x, current_cursor_position_y);
            break;
        case 77:
            current_cursor_position_x += 1;
            set_cursor(current_cursor_position_x, current_cursor_position_y);
            break;
        case 75:
            current_cursor_position_x -= 1;
            set_cursor(current_cursor_position_x, current_cursor_position_y);
            break;
        }
    }
    return 0;
}


/*
int ausgabe(int endergebnis[][32])
{
    for (i=0; i<9;i++)
    {
        for (j=0;i<9; i++)
        {
           if (endergebnis[i][j] == 0)
           {printf("_");}
           else
           {
           printf("%i",endergebnis[i][j]);
           }
        }
        printf("\n");
    }
    return 0;
}
*/

int level_anzeige(int level_aufbau[9][9])
{
    int i, j, k;
    for (k=0; k<9; k++)
    {
        //Trenner am Anfang und jeweils nach drei Zahlen einfügen (spaltenweise)
        if (k==0 || k==3 || k==6)
        {
            printf("+");
            for (j=0; j<3; j++)
            {
                printf("-------+");
            }
            printf("\n");
        }
        //Beginn die nächste Zeile mit "| "
        printf("| ");

        for (i=0; i<9; i++)
        {
            //Trenner nach drei Zahlen einfügen (zeilenweise)
            if (i==3 || i==6)
            {
                printf("| ");
            }
            //Nullen als Punkt ausgeben
            if (level_aufbau[k][i] == 0)
            {
                printf(". ");
            }
            //Sonst Zahlenwerte einfügen
            else
            {
                printf("%d ", level_aufbau[k][i]);
            }
        }
        //Trenner und Absatz am Zeilenende
        printf("|\n");
    }
    //Trenner am unteren Rand
    printf("+");
    for (j=0; j<3; j++)
    {
        printf("-------+");
    }
    move_cursor();
    return 0;
}




int sodoku_level(int level)
{
    if (level == 1)
    {
    //Vorlage: https://www.raetseldino.de/sudoku-einfach/sudoku-01-einsteiger.pdf
        int loesung_leicht[9][9]={
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
        int bearbeitung_leicht[9][9]={
                    {6,4,0,2,9,8,5,0,7},
                    {0,5,2,1,0,6,9,8,4},
                    {7,9,8,0,4,5,0,6,2},
                    {9,0,3,6,1,4,8,7,0},
                    {0,8,6,5,3,0,4,2,9},
                    {5,7,4,0,8,2,6,0,3},
                    {8,3,0,7,6,9,2,4,1},
                    {4,1,9,8,0,3,7,5,6},
                    {2,0,7,4,5,1,3,0,8},
                 };
        level_anzeige(bearbeitung_leicht);
        return 0;
    }
    else if (level == 2)
    {

    }
    else if (level == 3)
    {

    }
}

