#include "bibliothek.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>


/**
 * Die Nullfelder ergeben sich aus der Formatierung in "level_anzeige()":
 *  +1y , erste Zeile besteht aus Trennern
 *  erste 3 Zahlen liegen in (2,1)(4,1)(6,1), dann wegen des Trenners in (10,1)(12,1)(14,1) und in (18,1)(20,1)(22,1) usw.
 *  bis zur dritten Zeile setzt sich das für y jeweils mit +1 fort
 *  dann aufgrund des Trenners y+=2
 * \param Index des zweidimensionalen Arrays
**/
/*
//81 Zahlen müssen in x und y untergebracht werden, alle Werte zunächst auf 0 setzen
int null_y[81];
int null_x[81];
//Indexzähler für Anhängen von Werten an den richtigen Stellen
int null_y_index = 0;
int null_x_index = 0;

int nullfelder(int array_y, int array_x)
{
    //printf("%i", array_y);

    if (array_y <= 2)
    {
        null_y[null_y_index] = array_y + 1;
        //printf("%d", null_y[null_y_index]);
        null_y_index += 1;
    }
    else if (array_y >= 3 && array_y <= 5)
    {
        null_y[null_y_index] = array_y + 2;
        //printf("%d", null_y[null_y_index]);
        null_y_index += 1;
    }

    printf("%d", null_y[null_y_index]);
}

*/


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
    //Startposition definieren
    set_cursor(2, 1);
    int current_cursor_position_x = 2;
    int current_cursor_position_y = 1;

    while(1)
    {
        //Keycode-Quelle: "https://docs.microsoft.com/en-us/previous-versions/visualstudio/visual-studio-6.0/aa299374(v=vs.60)"
        //Abfangen der Pfeiltasteneingaben
        //Cursorbewegung wird auf das Spielfeld begrenzt
        switch(_getch())
        {
        case 72:
            if (current_cursor_position_y <= 1)
            {
                break;
            }
            current_cursor_position_y -= 1;
            set_cursor(current_cursor_position_x, current_cursor_position_y);
            break;
        case 80:
            if (current_cursor_position_y >= 11)
            {
                break;
            }
            current_cursor_position_y += 1;
            set_cursor(current_cursor_position_x, current_cursor_position_y);
            break;
        case 77:
            if (current_cursor_position_x >= 22)
            {
                break;
            }
            current_cursor_position_x += 1;
            set_cursor(current_cursor_position_x, current_cursor_position_y);
            break;
        case 75:
            if (current_cursor_position_x<=2)
            {
                break;
            }
            current_cursor_position_x -= 1;
            set_cursor(current_cursor_position_x, current_cursor_position_y);
            break;
        }
    }
    return 0;
}


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
                //Nullfelder abspeichern
                //nullfelder(k,i);
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
    return 0;
}


/**
 * Erstellung des "Sudoku-Arrays"
 * \param level = ausgewähltes Level
 * Funktion als Zeiger und int als static, da zweidimensionale Arrays sonst nicht mehr zurück an main gegeben werden können
 * Quelle: https://www.tutorialspoint.com/cprogramming/c_return_arrays_from_function.htm
 * \return aufbau Sudoku als Array
*/

int *sodoku_level(int level)
{
    if (level == 1)
    {
    //Vorlage: https://www.raetseldino.de/sudoku-einfach/sudoku-01-einsteiger.pdf
        static int loesung_leicht[9][9]={
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
        static int bearbeitung_leicht[9][9]={
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

        return *bearbeitung_leicht;
    }
    else if (level == 2)
    {

    }
    else if (level == 3)
    {

    }
    return 0;
}

