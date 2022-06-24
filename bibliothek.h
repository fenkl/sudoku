#include <stdio.h>
#include <stdlib.h>

#ifndef BIBLIOTHEK_H_INCLUDED
#define BIBLIOTHEK_H_INCLUDED

int Difficulty();

int *sudoku_level(int level);

int level_anzeige (int level_aufbau[9][9]);

int *move_cursor();

int set_cursor(const int x, const int y);

int *check_writable_field (int x, int y, int sudoku[9][9]);

int IsNumberInArray(int array[9], int number);

int *Array_ausfuellen_lassen(int bekannte_Zahlen[9][9], int array_zur_Bearbeitung[9][9]);

int Ueberpruefung_der_Loesung(int ausgefuelltes_Sudoku[9][9], int loesung_Sudoku[9][9]);

#endif // BIBLIOTHEK_H_INCLUDED
