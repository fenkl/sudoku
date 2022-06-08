#include "bibliothek.h"

int main()
{
    int *result_level;
    int level_aufbau[9][9];
    int zaehler_aufbau_fuellen = 0;
    // Pointer result_level holt sich die Speicheradresse des Arrays in Sudoku_level
    result_level = sodoku_level(1);
    for (int i=0; i<9; i++)
    {
        for (int j=0; j<9; j++)
        {
            // *result_level ist ein eindimensionales Array mit der Länge 81
            // daher wird zweistelliges Array 9x9 damit befüllt
            level_aufbau[i][j] = *(result_level + zaehler_aufbau_fuellen);
            //printf("%d\n", level_aufbau[i][j]);
            zaehler_aufbau_fuellen += 1;
        }
    }
    level_anzeige(level_aufbau);
    move_cursor();
    return 0;
}
