#include <stdio.h>
#include <stdlib.h>

#ifndef BIBLIOTHEK_H_INCLUDED
#define BIBLIOTHEK_H_INCLUDED

int move_cursor();
int set_cursor(const int x, const int y);
int level_anzeige (int level_aufbau[9][9]);
int sodoku_level(int level);
int* null_festellen(int level_neu[9][9]);
int sudoku_voll (int level_bearbeitet[9][9]);
int sudoku_geloest (int level_bearbeitet[9][9], int level_loesung[9][9]);
int* koordinaten_umrechnen(int x, int y, int ausgabe_zu_array);

#endif // BIBLIOTHEK_H_INCLUDED
