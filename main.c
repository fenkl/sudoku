#include "bibliothek.h"
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>


int main()
{
    long start = GetTickCount()/1000.0;      // start Zeitmessung
    int level_difficulty = Difficulty();
    system("cls");


    int *bearbeitung_level;
    int level_aufbau[9][9];
    int zaehler_aufbau_fuellen = 0;
    // Pointer result_level holt sich die Speicheradresse des Arrays in Sudoku_level
    bearbeitung_level = sodoku_level(1);
    for (int i=0; i<9; i++)
    {
        for (int j=0; j<9; j++)
        {
            // *result_level ist ein eindimensionales Array mit der L�nge 81
            // daher wird zweistelliges Array 9x9 damit bef�llt
            level_aufbau[i][j] = *(bearbeitung_level + zaehler_aufbau_fuellen);
            //printf("%d\n", level_aufbau[i][j]);
            zaehler_aufbau_fuellen += 1;
        }
    }
    level_anzeige(bearbeitung_level);
    long end = GetTickCount()/1000.0; // Ende Zeitmessung
    long needed_time = end - start; // Gesamter Zeitverbrauch

    if (needed_time > 60) // Zeitumrechnung in Minuten, wenn notwendig
    {
        printf("\n\nBenoetigte Zeit: %ld Minuten", needed_time / 60);
    }
    else // ansonsten ausgabe in Sekunden
    {
        printf("\n\nBenoetigte Zeit: %ld Sekunden", needed_time);
    }
    int cursor_position_x = 2;
    int cursor_position_y = 1;
    while (1)
    {
        int *number_pressed_and_cursor_positions;
        number_pressed_and_cursor_positions = move_cursor(cursor_position_x, cursor_position_y);
        char number_pressed = *number_pressed_and_cursor_positions;
        int current_cursor_position_x = *(number_pressed_and_cursor_positions + 1);
        int current_cursor_position_y = *(number_pressed_and_cursor_positions + 2);

        int *get_writable_field;
        get_writable_field = check_writable_field(current_cursor_position_x, current_cursor_position_y, bearbeitung_level);
        if (get_writable_field != 0)
        {
            int x_null = *get_writable_field;
            int y_null = *(get_writable_field + 1);
            printf("%c", number_pressed);
        }
        cursor_position_x = current_cursor_position_x;
        cursor_position_y = current_cursor_position_y;
    }

    return 0;
}
