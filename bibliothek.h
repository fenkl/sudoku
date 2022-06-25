#include <stdio.h>
#include <stdlib.h>

#ifndef BIBLIOTHEK_H_INCLUDED
#define BIBLIOTHEK_H_INCLUDED

struct Level {
    int array_zur_bearbeitung[9][9];
    int loesung[9][9];
    int bearbeitung[9][9];
};

void *show_time(void *needed_time);

int Difficulty();

struct Level sudoku_level_initialisition(int choosed_level);

int level_anzeige (struct Level);

int *move_cursor();

int set_cursor(const int x, const int y);

int *check_writable_field (int x, int y, int sudoku[9][9]);

int IsNumberInArray(int array[9], int number);

struct Level Array_ausfuellen_lassen(struct Level);

int Ueberpruefung_der_Loesung(struct Level);

#endif // BIBLIOTHEK_H_INCLUDED
