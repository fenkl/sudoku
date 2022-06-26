/**
* Programm zum Erstellen eines Sudokulevels
* Autoren: Klara von Lehmden, Francisco Fenkl und Henry Hamker
* Vollendet am: 26.06.2022
**/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "level_brute_force.h"



/**
* Initialisierung aller notwendigen Variablen
**/
struct variablen init_variablen()
{
    struct variablen variable;
    variable.initial_groups[0] = 0; variable.initial_groups[1] = 4; variable.initial_groups[2] = 8; //Neuner-Gruppen (Kästchen), die unabhängig voneinander gefüllt werden können
    variable.try_counter = 0;
    variable.reset_count = 0;
    variable.max_group_reset = 9;
    variable.group_reset_result = 0;

    // Arrays mit Nullen füllen
    for (int i=0; i<9; i++)
    {
        for (int j=0; j<9; j++)
        {
            variable.two_d_array_of_niner_fields[i][j] = 0;
            variable.created_level[i][j] = 0;
        }
    }

    for (int i=0; i<9; i++)
    {
        for (int j=0; j<3; j++)
        {
            for (int h=0; h<3; h++)
            {
                variable.nine_niner_fields[i][j][h] = 0;
            }
        }
    }

    for (int i=0; i<9; i++)
    {
        int x = i + 1;
        variable.numbers[i] = x; //verfügbare Zahlen
    }

    //proofrow entspricht: [[0, 1, 2], [0, 1, 2], [0, 1, 2], [3, 4, 5], [3, 4, 5], [3, 4, 5], [6, 7, 8], [6, 7, 8], [6, 7, 8]]
    for (int j=0; j<9; j++)
    {
        if (j>=0 && j<=2)
        {
            for (int h=0; h<3; h++)
            {
                variable.proofrow[j][h] = h;
            }
        }
        else if (j>=3 && j<=5)
        {
            for (int h=0; h<3; h++)
            {
                variable.proofrow[j][h] = h + 3;
            }
        }
        else if (j>=6 && j<=8)
        {
            for (int h=0; h<3; h++)
            {
                variable.proofrow[j][h] = h + 6;
            }
        }
    }

    //proofcol entspricht: [[0, 3, 6], [1, 4, 7], [2, 5, 8], [0, 3, 6], [1, 4, 7], [2, 5, 8], [0, 3, 6], [1, 4, 7], [2, 5, 8]]
    for (int j=0; j<9; j++)
    {
        if (j==0 || j==3 || j==6)
        {
            variable.proofcol[j][0] = 0;
            variable.proofcol[j][1] = 3;
            variable.proofcol[j][2] = 6;
        }
        else if (j==1 || j==4 || j==7)
        {
            variable.proofcol[j][0] = 1;
            variable.proofcol[j][1] = 4;
            variable.proofcol[j][2] = 7;
        }

        else if (j==2 || j==5 || j==8)
        {
            variable.proofcol[j][0] = 2;
            variable.proofcol[j][1] = 5;
            variable.proofcol[j][2] = 8;
        }
    }

    //restliche voneinander abhängige Gruppen: [1, 2, 3, 5, 6, 7]
    for (int j=0; j<6; j++)
    {
        if (j>=0 && j<=2)
        {
            variable.rest_of_groups[j] = j + 1;
        }
        else
        {
            variable.rest_of_groups[j] = j + 2;
        }
    }

    return variable;
}


/**
* Bekommmt die zu verarbeitende Gruppe mitgegeben
* Überwacht Brute-Force-Prozess (define_group)
*/
struct variablen setup_groups(struct variablen variable, int type_of_group)
{
    int groups[6];

    int length_groups;
    if (type_of_group == 1)
    {
        length_groups = 3;
        for (int i=0; i<3; i++)
        {
            groups[i] = variable.initial_groups[i];
        }
    }
    else
    {
        length_groups = 6;
        for (int i=0; i<6; i++)
        {
            groups[i] = variable.rest_of_groups[i];
        }
    }

    int list_pointer = 0;
    while (list_pointer < length_groups)
    {
        int group = groups[list_pointer];
        variable = define_group(variable, group);


        //group done = 1
        if (variable.group_reset_result == 1)
        {
            list_pointer += 1;
        }
        //reset group = 0
        else if (variable.group_reset_result == 0)
        {
            variable.reset_count += 1;
            if (variable.reset_count >= variable.max_group_reset)
            {
                variable.reset_count = 0;
                reset_group(variable, group);
                list_pointer = 0;
            }
            else
            {
                //pass
            }
        }
        else
        {
            list_pointer = 0;
            variable.reset_count = 0;
        }

    }
    return variable;
}

/**
*
*/
struct variablen define_group(struct variablen variable, int group_number)
{
    variable.try_counter += 1;

    int copy_of_numbers[9];
    int length_copy_of_numbers = 9;


    //copy of numbers füllen
    for (int j=0; j<9; j++)
    {
        copy_of_numbers[j] = variable.numbers[j];
    }

    for (int row=0; row<3; row++)
    {
        for (int col=0; col<3; col++)
        {
            int inner_copy_of_numbers[9];
            int length_inner_copy_of_numbers = length_copy_of_numbers;
            for (int i=0; i<9; i++)
            {
                inner_copy_of_numbers[i] = copy_of_numbers[i];
            }
            int guessed_number;
            //wenn copy_of_numbers nicht guessed_number enthält, erneut zufällige Zahl suchen
            do
            {
                guessed_number = get_random_number(copy_of_numbers);
            }while (guessed_number == -1);

            //Prüfen, ob sich guessed_number in selber Reihe oder Spalte befindet
            while (IsNumberInRow(variable, group_number, row, guessed_number) == 1 || IsNumberInCol(variable, group_number, col, guessed_number) == 1)
            {
                // guessed_number vergeben, also aus möglichen Nummern streichen (0 einsetzen)
                for (int j=0; j<9; j++)
                {
                    if (inner_copy_of_numbers[j] == guessed_number)
                    {
                        inner_copy_of_numbers[j] = 0;
                        length_inner_copy_of_numbers = length_inner_copy_of_numbers - 1;
                    }
                }
                if (length_inner_copy_of_numbers == 0) //Keine möglichen Zahlen mehr vorhanden, also Reset
                {
                    if (row == 0 && col == 0)
                    {
                        variable = reset_group(variable, group_number);

                        variable.group_reset_result = -1;
                        return variable;
                    }
                    else
                    {
                        variable = reset_group(variable, group_number);

                        variable.group_reset_result = 0;
                        return variable;
                    }
                }
                do
                {
                    guessed_number = get_random_number(inner_copy_of_numbers);
                }while (guessed_number == -1);
            }
            // wenn guessed_number in copy_of_numbers enthalten, aus möglichen Nummern streichen (0 einsetzen)
            for (int j=0; j<9; j++)
            {
                if (copy_of_numbers[j] == guessed_number)
                {
                    copy_of_numbers[j] = 0;
                    length_copy_of_numbers = length_copy_of_numbers - 1;
                }
            }

            variable.nine_niner_fields[group_number][row][col] = guessed_number; //Einsetzen der passenden Nummer in Array

        }
    }
    variable.group_reset_result = 1;
    return variable;
}


/**
* Erzeugt zufällige Zahl
*/
int get_random_number(int number_array[9])
{
    bool number_in_available_numbers = false;
    int index_guessed_number = rand() % 9 ;
    int guessed_number = number_array[index_guessed_number];

    if (guessed_number != 0)
    {
        number_in_available_numbers = true;
    }

    if (number_in_available_numbers == false)
    {
        return -1;
    }
    else
    {
        return guessed_number;
    }
    return 0;
}


/**
* Setzt beim Stocken des Brute-Force-Prozesses die Gruppen zurück
*/
struct variablen reset_group(struct variablen variable, int group_number)
{
    for (int row=0; row<3; row++)
    {
        for (int col=0; col<3; col++)
        {
            variable.nine_niner_fields[group_number][row][col] = 0;
        }
    }
    return variable;
}


/**
* Prüft, ob gewählte Nummer in Zeile vorhanden ist
*/
int IsNumberInRow(struct variablen variable, int blockid, int innerrow, int number)
{
    int comparelist[9] = {0};
    int lists[3];
    for (int i=0; i<3; i++)
    {
        lists[i] = variable.proofrow[blockid][i];
    }

    //comparelist füllen
    comparelist[0] = variable.nine_niner_fields[lists[0]][innerrow][0];
    comparelist[1] = variable.nine_niner_fields[lists[0]][innerrow][1];
    comparelist[2] = variable.nine_niner_fields[lists[0]][innerrow][2];

    comparelist[3] = variable.nine_niner_fields[lists[1]][innerrow][0];
    comparelist[4] = variable.nine_niner_fields[lists[1]][innerrow][1];
    comparelist[5] = variable.nine_niner_fields[lists[1]][innerrow][2];

    comparelist[6] = variable.nine_niner_fields[lists[2]][innerrow][0];
    comparelist[7] = variable.nine_niner_fields[lists[2]][innerrow][1];
    comparelist[8] = variable.nine_niner_fields[lists[2]][innerrow][2];

    //number in comparelist?
    for (int j=0; j<9; j++)
    {
        if (number == comparelist[j])
        {
            return 1;
        }
    }
    return 0;
}


/**
* Prüft, ob gewählte Nummer in spalte vorhanden ist
*/
int IsNumberInCol(struct variablen variable, int blockid, int innercol, int number)
{
    int comparelist[9] = {0};
    int lists[3];

    for (int i=0; i<3; i++)
    {
        lists[i] = variable.proofcol[blockid][i];
    }

    //comparelist füllen
    comparelist[0] = variable.nine_niner_fields[lists[0]][0][innercol];
    comparelist[1] = variable.nine_niner_fields[lists[0]][1][innercol];
    comparelist[2] = variable.nine_niner_fields[lists[0]][2][innercol];

    comparelist[3] = variable.nine_niner_fields[lists[1]][0][innercol];
    comparelist[4] = variable.nine_niner_fields[lists[1]][1][innercol];
    comparelist[5] = variable.nine_niner_fields[lists[1]][2][innercol];

    comparelist[6] = variable.nine_niner_fields[lists[2]][0][innercol];
    comparelist[7] = variable.nine_niner_fields[lists[2]][1][innercol];
    comparelist[8] = variable.nine_niner_fields[lists[2]][2][innercol];



    //number in comparelist?
    for (int j=0; j<9; j++)
    {
        if (number == comparelist[j])
        {
            return 1;
        }
    }
    return 0;
}


/**
* Erstellt 2D-Array aus 3D-Array (notwendig für korrekte Ausgabe)
* variable.two_d_array_of_niner_fields entspricht am Ende der Lösung für das erstellte Level
*/
struct variablen niner_fields_to_2d_array(struct variablen variable)
{
    int *pointer_to_niner_fields;
    int helper_two_d_array[9][9];
    //Speicheradresse des 3D-Arrays beziehen
    pointer_to_niner_fields = *variable.nine_niner_fields;
    int counter = 0;

    //3d-array zu 2d-array
    for (int i=0; i<9; i++)
    {
        for (int j=0; j<9; j++)
        {
            helper_two_d_array[i][j] = *(pointer_to_niner_fields + counter);
            counter += 1;
        }
    }

    //Spalten und Zeilen umschreiben für Ausgabe
    for (int j=0; j<3; j++)
    {
        variable.two_d_array_of_niner_fields[0][j] = helper_two_d_array[0][j];
    }

    // Sorry
    variable.two_d_array_of_niner_fields[0][3] = helper_two_d_array[1][0];
    variable.two_d_array_of_niner_fields[0][4] = helper_two_d_array[1][1];
    variable.two_d_array_of_niner_fields[0][5] = helper_two_d_array[1][2];
    variable.two_d_array_of_niner_fields[0][6] = helper_two_d_array[2][0];
    variable.two_d_array_of_niner_fields[0][7] = helper_two_d_array[2][1];
    variable.two_d_array_of_niner_fields[0][8] = helper_two_d_array[2][2];

    variable.two_d_array_of_niner_fields[1][0] = helper_two_d_array[0][3];
    variable.two_d_array_of_niner_fields[1][1] = helper_two_d_array[0][4];
    variable.two_d_array_of_niner_fields[1][2] = helper_two_d_array[0][5];
    variable.two_d_array_of_niner_fields[1][3] = helper_two_d_array[1][3];
    variable.two_d_array_of_niner_fields[1][4] = helper_two_d_array[1][4];
    variable.two_d_array_of_niner_fields[1][5] = helper_two_d_array[1][5];
    variable.two_d_array_of_niner_fields[1][6] = helper_two_d_array[2][3];
    variable.two_d_array_of_niner_fields[1][7] = helper_two_d_array[2][4];
    variable.two_d_array_of_niner_fields[1][8] = helper_two_d_array[2][5];

    variable.two_d_array_of_niner_fields[2][0] = helper_two_d_array[0][6];
    variable.two_d_array_of_niner_fields[2][1] = helper_two_d_array[0][7];
    variable.two_d_array_of_niner_fields[2][2] = helper_two_d_array[0][8];
    variable.two_d_array_of_niner_fields[2][3] = helper_two_d_array[1][6];
    variable.two_d_array_of_niner_fields[2][4] = helper_two_d_array[1][7];
    variable.two_d_array_of_niner_fields[2][5] = helper_two_d_array[1][8];
    variable.two_d_array_of_niner_fields[2][6] = helper_two_d_array[2][6];
    variable.two_d_array_of_niner_fields[2][7] = helper_two_d_array[2][7];
    variable.two_d_array_of_niner_fields[2][8] = helper_two_d_array[2][8];

    variable.two_d_array_of_niner_fields[3][0] = helper_two_d_array[3][0];
    variable.two_d_array_of_niner_fields[3][1] = helper_two_d_array[3][1];
    variable.two_d_array_of_niner_fields[3][2] = helper_two_d_array[3][2];
    variable.two_d_array_of_niner_fields[3][3] = helper_two_d_array[4][0];
    variable.two_d_array_of_niner_fields[3][4] = helper_two_d_array[4][1];
    variable.two_d_array_of_niner_fields[3][5] = helper_two_d_array[4][2];
    variable.two_d_array_of_niner_fields[3][6] = helper_two_d_array[5][0];
    variable.two_d_array_of_niner_fields[3][7] = helper_two_d_array[5][1];
    variable.two_d_array_of_niner_fields[3][8] = helper_two_d_array[5][2];

    variable.two_d_array_of_niner_fields[4][0] = helper_two_d_array[3][3];
    variable.two_d_array_of_niner_fields[4][1] = helper_two_d_array[3][4];
    variable.two_d_array_of_niner_fields[4][2] = helper_two_d_array[3][5];
    variable.two_d_array_of_niner_fields[4][3] = helper_two_d_array[4][3];
    variable.two_d_array_of_niner_fields[4][4] = helper_two_d_array[4][4];
    variable.two_d_array_of_niner_fields[4][5] = helper_two_d_array[4][5];
    variable.two_d_array_of_niner_fields[4][6] = helper_two_d_array[5][3];
    variable.two_d_array_of_niner_fields[4][7] = helper_two_d_array[5][4];
    variable.two_d_array_of_niner_fields[4][8] = helper_two_d_array[5][5];

    variable.two_d_array_of_niner_fields[5][0] = helper_two_d_array[3][6];
    variable.two_d_array_of_niner_fields[5][1] = helper_two_d_array[3][7];
    variable.two_d_array_of_niner_fields[5][2] = helper_two_d_array[3][8];
    variable.two_d_array_of_niner_fields[5][3] = helper_two_d_array[4][6];
    variable.two_d_array_of_niner_fields[5][4] = helper_two_d_array[4][7];
    variable.two_d_array_of_niner_fields[5][5] = helper_two_d_array[4][8];
    variable.two_d_array_of_niner_fields[5][6] = helper_two_d_array[5][6];
    variable.two_d_array_of_niner_fields[5][7] = helper_two_d_array[5][7];
    variable.two_d_array_of_niner_fields[5][8] = helper_two_d_array[5][8];

    variable.two_d_array_of_niner_fields[6][0] = helper_two_d_array[6][0];
    variable.two_d_array_of_niner_fields[6][1] = helper_two_d_array[6][1];
    variable.two_d_array_of_niner_fields[6][2] = helper_two_d_array[6][2];
    variable.two_d_array_of_niner_fields[6][3] = helper_two_d_array[7][0];
    variable.two_d_array_of_niner_fields[6][4] = helper_two_d_array[7][1];
    variable.two_d_array_of_niner_fields[6][5] = helper_two_d_array[7][2];
    variable.two_d_array_of_niner_fields[6][6] = helper_two_d_array[8][0];
    variable.two_d_array_of_niner_fields[6][7] = helper_two_d_array[8][1];
    variable.two_d_array_of_niner_fields[6][8] = helper_two_d_array[8][2];

    variable.two_d_array_of_niner_fields[7][0] = helper_two_d_array[6][3];
    variable.two_d_array_of_niner_fields[7][1] = helper_two_d_array[6][4];
    variable.two_d_array_of_niner_fields[7][2] = helper_two_d_array[6][5];
    variable.two_d_array_of_niner_fields[7][3] = helper_two_d_array[7][3];
    variable.two_d_array_of_niner_fields[7][4] = helper_two_d_array[7][4];
    variable.two_d_array_of_niner_fields[7][5] = helper_two_d_array[7][5];
    variable.two_d_array_of_niner_fields[7][6] = helper_two_d_array[8][3];
    variable.two_d_array_of_niner_fields[7][7] = helper_two_d_array[8][4];
    variable.two_d_array_of_niner_fields[7][8] = helper_two_d_array[8][5];

    variable.two_d_array_of_niner_fields[8][0] = helper_two_d_array[6][6];
    variable.two_d_array_of_niner_fields[8][1] = helper_two_d_array[6][7];
    variable.two_d_array_of_niner_fields[8][2] = helper_two_d_array[6][8];
    variable.two_d_array_of_niner_fields[8][3] = helper_two_d_array[7][6];
    variable.two_d_array_of_niner_fields[8][4] = helper_two_d_array[7][7];
    variable.two_d_array_of_niner_fields[8][5] = helper_two_d_array[7][8];
    variable.two_d_array_of_niner_fields[8][6] = helper_two_d_array[8][6];
    variable.two_d_array_of_niner_fields[8][7] = helper_two_d_array[8][7];
    variable.two_d_array_of_niner_fields[8][8] = helper_two_d_array[8][8];


    return variable;
}

/**
* Ersetzt zufällige Zahlen durch Nullen, um Level zu erstellen
*/
struct variablen create_level(struct variablen variable)
{
    int numbers[9] = {1,2,3,4,5,6,7,8,9};
    int array_index_to_del[9][9];
    int number_index_x_to_del = 0;
    int number_index_y_to_del = 0;

    //copy level
    for (int i=0; i<9; i++)
    {
        for (int j=0; j<9; j++)
        {
            variable.created_level[i][j] = variable.two_d_array_of_niner_fields[i][j];
        }
    }

    //Zufällige Zahl als Index holen
    for (int i=0; i<9; i++)
    {
        for (int j=0; j<9; j++)
        {
            array_index_to_del[i][j] = get_random_number(numbers);
        }
    }

    //Nullen einfügen
    for (int i=0; i<6; i++)
    {
        for (int j=0; j<9; j++)
        {
            number_index_x_to_del = array_index_to_del[i][j];
            number_index_y_to_del = array_index_to_del[j][i];
            variable.created_level[number_index_x_to_del][number_index_y_to_del] = 0;
        }
    }

    return variable;
}

