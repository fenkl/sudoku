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
    printf("\n\n (4) Datei einlesen");

    while (input_accepted== 0)
    {
        printf("\n\n zufaelliges Level: ");

        scanf("%d", &difficulty_input);
        fflush(stdin);

        if (difficulty_input > 0 && difficulty_input< 5)
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
        //Vorlage: https://www.raetseldino.de/sudoku-mittel/sudoku-mittel-schwer-loesung-m14.pdf
        int auffueller_loesung_mittel[9][9] = {
                    {5,3,4,1,9,6,8,7,2},
                    {2,8,9,5,7,4,6,3,1},
                    {1,7,6,2,8,3,4,9,5},
                    {6,9,7,4,5,1,3,2,8},
                    {3,5,8,7,6,2,1,4,9},
                    {4,1,2,9,3,8,7,5,6},
                    {9,2,1,6,4,7,5,8,3},
                    {8,4,5,3,1,9,2,6,7},
                    {7,6,3,8,2,5,9,1,4},
                 };
        int auffuller_bearbeitung_mittel[9][9] = {
                    {0,0,0,1,0,0,0,0,0},
                    {2,0,0,0,7,0,0,3,0},
                    {0,0,6,0,8,3,0,9,0},
                    {0,0,7,4,0,1,3,0,0},
                    {3,5,8,0,6,0,1,0,0},
                    {0,1,0,9,0,0,0,0,0},
                    {9,0,0,6,0,0,5,0,0},
                    {0,4,0,0,0,0,0,0,7},
                    {0,0,3,0,0,5,0,0,0},
                 };

        for (int j=0; j<9; j++)
        {
            for (int i=0; i<9; i++)
            {
                level.loesung[j][i] = auffueller_loesung_mittel[j][i];
                level.array_zur_bearbeitung[j][i] = auffuller_bearbeitung_mittel[j][i];
                level.bearbeitung[j][i] = auffuller_bearbeitung_mittel[j][i];
            }
        }
    }
    else if (choosed_level == 3)
    {
        //Vorlage: https://www.raetseldino.de/sudoku-schwer/sudoku-17-extra-schwer.pdf
        int auffueller_loesung_schwer[9][9] = {
                    {9,1,7,5,2,4,6,8,3},
                    {8,3,6,1,9,7,4,2,5},
                    {5,4,2,8,3,6,1,7,9},
                    {3,5,1,6,4,8,7,9,2},
                    {4,2,9,3,7,1,8,5,6},
                    {6,7,8,9,5,2,3,4,1},
                    {7,8,5,2,1,3,9,6,4},
                    {1,9,4,7,6,5,2,3,8},
                    {2,6,3,4,8,9,5,1,7},
                 };
        int auffuller_bearbeitung_schwer[9][9] = {
                    {9,0,0,0,2,4,0,8,0},
                    {8,3,0,0,0,0,0,2,0},
                    {0,0,0,0,3,0,0,7,0},
                    {0,5,1,6,4,8,0,0,0},
                    {0,2,0,0,0,1,0,0,0},
                    {6,0,8,0,0,0,0,0,0},
                    {0,8,5,0,1,0,9,0,0},
                    {0,0,4,7,0,5,0,0,0},
                    {2,0,0,0,0,0,0,1,0},
                 };

        for (int j=0; j<9; j++)
        {
            for (int i=0; i<9; i++)
            {
                level.loesung[j][i] = auffueller_loesung_schwer[j][i];
                level.array_zur_bearbeitung[j][i] = auffuller_bearbeitung_schwer[j][i];
                level.bearbeitung[j][i] = auffuller_bearbeitung_schwer[j][i];
            }
        }
    }
    else if (choosed_level == 4)
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
            Sleep(0.8);
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
            //Enter zum Beenden bzw. Korrigieren
            case 13:
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

        if (number_pressed == 13)   // Um Spiel zu beenden
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
int Ueberpruefung_der_Loesung(struct Level level, int gesamt)
{
    HANDLE hConsole;
    int i, j, k;
    int finished = 1;
    int prozent =0;
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

                finished = 0;
                prozent +=1;
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
    double temp = prozent_richtig(gesamt, prozent);

    if(temp!=100)
    {
        printf("\n richtige Eingaben = %.2f %% \n", temp );
    }

    return finished;
}


int anzahl_nullen(struct Level level)
{
   int i,j,counter =0;
   for(i=0; i<9;  i++)
   {
        for(j=0; j<9; j++)
        {
            if (level.bearbeitung[j][i]==0)
            {
                counter +=1;
            }
        }
   }
   return counter;
}

double prozent_richtig (int gesamt, int falsch)
    {
        double wrong=falsch;
        double total=gesamt;

        double prozent = 100-(wrong/total*100);
        return prozent;
    }

struct Level weiterspielen(struct Level level)
{
    int k,i;
    for (k=0; k<9; k++)
    {
        for ( i=0; i<9; i++)
        {
            //Falsche Werte rot und richtige Werte grün ausgeben
            if (level.array_zur_bearbeitung[k][i] == level.loesung[k][i])
            {
            level.bearbeitung[k][i]=level.array_zur_bearbeitung[k][i];
            }
           level.array_zur_bearbeitung[k][i] = level.bearbeitung[k][i];
        }
    }
    return level;
}
long zeit_berechnen(long start, long end)
{
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
    return 0;
}


/*
struct Level datei_einlesen(struct Level level)
{
        char filename[120];
        printf("/n Dateipfad angeben:");
        fgets(filename, 120, stdin);
    const char* filename2 = filename;
    FILE *fp;
    int temp;
    printf ("%s", filename2);
        fp = fopen(filename2, "r");

    if(fp == NULL) {
        printf("Datei konnte nicht geoeffnet werden.\n");
    }else {
	// komplette Datei zeichenweise ausgeben
	while((temp = fgetc(fp))!=EOF) {
    printf("%c ", temp);

	}
	fclose(fp);
}


    FILE* input_file = fopen(filename, "r");
    if (!input_file)
        exit(EXIT_FAILURE);

    struct stat sb;
    if (stat(filename, &sb) == -1) {
        perror("stat");
        exit(EXIT_FAILURE);
    }

    char* file_contents = malloc(sb.st_size);
    fread(file_contents, sb.st_size, 1, input_file);

    printf("%s\n", file_contents);

    fclose(input_file);
    free(file_contents);

    printf("/n %s",file_contents);
    exit(EXIT_SUCCESS);

    printf("/n %s",file_contents);

    return level;
*/
