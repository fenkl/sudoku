#include "bibliothek.h"

int ausgabe(int endergebnis[][])
{
    for (int i=0; i<9;i++)
    {
        for (int j=0;i<9; i++)
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
int* sodoku_level(int level)
{



    if (level == 1)
    {
    //Vorlage: https://www.raetseldino.de/sudoku-einfach/sudoku-01-einsteiger.pdf
    int* loesung_leicht[9][9]={
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
    int* bearbeitung_leicht[9][9]={
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
                 return loesung_leicht, bearbeitung_leicht;
    }
    else if (level == 2)
    {

    }
    else if (level == 3)
    {

    }
}

