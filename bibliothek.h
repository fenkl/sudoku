#include <stdio.h>
#include <stdlib.h>

#ifndef BIBLIOTHEK_H_INCLUDED
#define BIBLIOTHEK_H_INCLUDED

//int nullfelder(int array_y, int array_x);
int move_cursor();
int set_cursor(const int x, const int y);
int level_anzeige (int level_aufbau[9][9]);
int *sodoku_level(int level);

#endif // BIBLIOTHEK_H_INCLUDED
