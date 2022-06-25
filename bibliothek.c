#include "bibliothek.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <pthread.h>
#include <time.h>


/**
* Thread für Zeitanzeige, wird aufgerufen von Array_ausfuellen_lassen
*/
void *show_time(void *time_needed)
{
    int *needed_time = (int *) time_needed;
    int needed_minutes, needed_seconds;
    set_cursor(35, 6);

    needed_seconds = *needed_time;

    if (needed_seconds <= 60) // Umrechnung ab 1 Minute in Minuten
    {
       printf("benoetigte Zeit bisher: %i Sekunden", needed_seconds);
    }
    else
    {
        needed_minutes = *needed_time / 60;
        needed_seconds = *needed_time - (needed_minutes * 60);
        if (needed_minutes == 1)
        {
            printf("benoetigte Zeit bisher: %i Minute und %i Sekunden", needed_minutes, needed_seconds);

        }
        else
        {
            printf("benoetigte Zeit bisher: %i Minuten und %i Sekunden", needed_minutes, needed_seconds);
        }
    }
    return NULL;
}

/**
  *
  * Abfrage, welcher Schwierigkeitsgrad gespielt werden möchte
  * Gibt einen Integer von 1 bis 3 zurück
  *
  **/
int Difficulty()
{
    int difficulty_input = 0;
    int input_accepted = 0;

    printf("Welches Schwierigkeitslevel moechten Sie spielen?");
    printf("\n (1) Einfach");
    printf("\n (2) Normal");
    printf("\n (3) Schwer");

    while (input_accepted== 0)
    {
        printf("\n\nSchwierigkeit: ");

        scanf("%d", &difficulty_input);
        fflush(stdin);

        if (difficulty_input > 0 && difficulty_input< 4)
        {
            input_accepted = 1;
            return difficulty_input;
        }
        else
        {
            difficulty_input = 0;
            input_accepted = 0;
            printf("\nBitte geben Sie eine Zahl von 1 - 3 ein");
        }
    }
    return 0;
}

/**
 * Erstellung des "Sudoku-Arrays"
 * \param level = ausgewähltes Level
 * Funktion als Zeiger und int als static, da zweidimensionale Arrays sonst nicht mehr zurück an main gegeben werden können
 * Quelle: https://www.tutorialspoint.com/cprogramming/c_return_arrays_from_function.htm
 * \return aufbau Sudoku als Array
 **/
struct Level sudoku_level_initialisition(int choosed_level)
{
    struct Level level;
    if (choosed_level == 1)
    {
    //Vorlage: https://www.raetseldino.de/sudoku-einfach/sudoku-01-einsteiger.pdf
        int auffueller_loesung_leicht[9][9] = {
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
        int auffuller_bearbeitung_leicht[9][9] = {
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

        for (int j=0; j<9; j++)
        {
            for (int i=0; i<9; i++)
            {
                level.loesung[j][i] = auffueller_loesung_leicht[j][i];
                level.array_zur_bearbeitung[j][i] = auffuller_bearbeitung_leicht[j][i];
                level.bearbeitung[j][i] = auffuller_bearbeitung_leicht[j][i];
            }
        }
    }
    else if (choosed_level == 2)
    {
        //static int loesung
    }
    else if (choosed_level == 3)
    {

    }

    return level;
}

/**
  * Ausgeben des Sudokus in der Konsole
  **/
int level_anzeige(struct Level level)
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
        Sleep(50);
        printf("| ");

        for (i=0; i<9; i++)
        {
            //Trenner nach drei Zahlen einfügen (zeilenweise)
            if (i==3 || i==6)
            {
                printf("| ");
            }
            //Nullen als Punkt ausgeben
            if (level.bearbeitung[k][i] == 0)
            {
                printf(". ");
            }
            //Sonst Zahlenwerte einfügen
            else
            {
                HANDLE hConsole;                                //Farbe der Ausgabe ändern
                hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

                SetConsoleTextAttribute(hConsole, 6); // 3, 5, 6, 9, 11, 12, 13 kommen zur Frage, je nachdem was optisch schöner ist
                printf("%d ", level.bearbeitung[k][i]);
                SetConsoleTextAttribute(hConsole, 15); // 15 = weiß mit schwarzem Hintergrund
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
  * main-Funktion aus CursorKeys (von Herrn Wichmann) übernommen und leicht angepasst.
  * getch() fängt Tastatureingaben ab und reagiert auf Pfeiltasten,
  * ruft bei entsprechendem Event set_cursor auf und speichert
  * aktuelle Cursorposition in current_cursor_position x oder y.
  **/
int *move_cursor(int set_cursor_position_x, int set_cursor_position_y)
{
    //Startposition definieren
    set_cursor(set_cursor_position_x, set_cursor_position_y);
    int current_cursor_position_x = set_cursor_position_x;
    int current_cursor_position_y = set_cursor_position_y;
    static int pressed_number_and_cursor_positions[3];

    while(1)
    {
        //Keycode-Quelle: "https://docs.microsoft.com/en-us/previous-versions/visualstudio/visual-studio-6.0/aa299374(v=vs.60)"
        //Abfangen der Tastatureingaben
        //Cursorbewegung wird auf das Spielfeld begrenzt
        int key_pressed = _getch();
        switch(key_pressed)
        {
            //Abfangen der Zahlen
            case 48 ... 57:
                // Array zur Rückgabe der Werte füllen
                pressed_number_and_cursor_positions[0] = key_pressed;
                pressed_number_and_cursor_positions[1] = current_cursor_position_x;
                pressed_number_and_cursor_positions[2] = current_cursor_position_y;
                return pressed_number_and_cursor_positions;
                set_cursor(current_cursor_position_x, current_cursor_position_y);
            //F3 zum Beenden bzw. Korrigieren
            case 61:
                // Array zur Rückgabe der Werte füllen
                pressed_number_and_cursor_positions[0] = key_pressed;
                pressed_number_and_cursor_positions[1] = current_cursor_position_x;
                pressed_number_and_cursor_positions[2] = current_cursor_position_y;
                return pressed_number_and_cursor_positions;
            //Abfangen der cursor
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
  *
  *Methode gibt 1 zurück, wenn die übergebene Koordinate beabeitet werden darf und 0 wenn nicht
  *
  **/
int *check_writable_field (int x, int y, int sudoku[9][9])
{
    // 2 Arrays für die Abbildung der erlaubten x und y Koordinaten
    int null_x[9] = {2,4,6,10,12,14,18,20,22};
    int null_y[9] = {1,2,3,5,6,7,9,10,11};

    int yField;
    yField = IsNumberInArray(null_x, x);
    int xField;
    xField = IsNumberInArray(null_y, y);

    static int writable_fields[2];
    if (yField != -1 && xField != -1)
    {
        if(sudoku[xField][yField]==0)
        {
            writable_fields[0] = xField;
            writable_fields[1] = yField;
            return writable_fields;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        return 0;
    }
}

/**
  * Überprüft, ob eine übergebene Zahl in einem übergebenen Array vorhanden ist
  */
int IsNumberInArray(int array[9], int number)
{
    for(int i = 0; i <= 8; i++)
    {
        if(array[i] == number)
        {
            return i;
        }
    }

    return -1;
}


/**
  * Hier wird das Array von dem Spieler ausgefüllt und am Ende wird das ausgefüllte Array zurückgegeben
  */
struct Level Array_ausfuellen_lassen(struct Level level)
{
    pthread_t thread;
    long start = GetTickCount()/1000.0;

    int cursor_position_x = 2;
    int cursor_position_y = 1;
    int boolean = 0;
    while (boolean == 0)
    {
        int *number_pressed_and_cursor_positions;
        number_pressed_and_cursor_positions = move_cursor(cursor_position_x, cursor_position_y);
        char number_pressed = *number_pressed_and_cursor_positions;
        int current_cursor_position_x = *(number_pressed_and_cursor_positions + 1);
        int current_cursor_position_y = *(number_pressed_and_cursor_positions + 2);

        if (number_pressed == 61)   // Um Spiel zu beenden
        {
            boolean = 1;
            break;
        }

        int *get_writable_field;
        get_writable_field = check_writable_field(current_cursor_position_x, current_cursor_position_y, level.bearbeitung);
        if (get_writable_field != 0)
        {
            int x_null = *get_writable_field;
            int y_null = *(get_writable_field + 1);

            if (*number_pressed_and_cursor_positions == 48) //0 leert Feld wieder
            {
                printf(".");
            }
            else
            {
                printf("%c", number_pressed);
                //printf("%i", int_number_pressed);
            }

            int int_number_pressed = number_pressed - 48; //Ascii zu Int
            level.array_zur_bearbeitung[x_null][y_null] = int_number_pressed;

            long end = GetTickCount()/1000.0;                 // Ende Zeitmessung
            long needed_time = end - start;  // Gesamter Zeitverbrauch
            pthread_create(&thread, NULL, show_time, &needed_time); //thread show_time erstellen
            pthread_join(thread, NULL); //thread starten
            Sleep(100);
        }
        cursor_position_x = current_cursor_position_x;
        cursor_position_y = current_cursor_position_y;
    }

   return level;
}



/**
  * Überprüfung ob das Ergebnis richtig ist mit Ausgabe der Fehler
  */
int Ueberpruefung_der_Loesung(struct Level level)
{
    HANDLE hConsole;
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
        Sleep(50);
        printf("| ");

        for (i=0; i<9; i++)
        {
            //Trenner nach drei Zahlen einfügen (zeilenweise)
            if (i==3 || i==6)
            {
                printf("| ");
            }

            //Falsche Werte rot und richtige Werte grün ausgeben
            if (level.array_zur_bearbeitung[k][i] == level.loesung[k][i])
            {
                hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(hConsole, 10); // richtig = grün

                printf("%i ", level.array_zur_bearbeitung[k][i]);

                SetConsoleTextAttribute(hConsole, 15); // 15 = weiß mit schwarzem Hintergrund
            }
            else
            {
                hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(hConsole, 4); // falsch = rot

                printf("%d ", level.array_zur_bearbeitung[k][i]);

                SetConsoleTextAttribute(hConsole, 15); // 15 = weiß mit schwarzem Hintergrund
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
