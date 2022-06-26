#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

// Funktionsprototypen
struct variablen init_variablen();
struct variablen setup_groups(struct variablen variable, int type_of_group);
struct variablen define_group(struct variablen variable, int group_number);
int get_random_number(int number_array[9]);
struct variablen reset_group(struct variablen variable, int group_number);
int IsNumberInRow(struct variablen variable, int blockid, int innerrow, int number);
int IsNumberInCol(struct variablen variable, int blockid, int innercol, int number);
int ausgabe_felder(struct variablen variable);
struct variablen niner_fields_to_2d_array(struct variablen variable);

struct variablen {
    int nine_niner_fields[9][3][3];
    int numbers[9];
    int proofrow[9][3];
    int proofcol[9][3];
    int reset_count;
    int max_group_reset;
    int initial_groups[3];
    int rest_of_groups[6];
    int try_counter;
    int group_reset_result;
    int two_d_array_of_niner_fields[9][9];
};


struct variablen init_variablen()
{

    struct variablen variable;
    variable.initial_groups[0] = 0; variable.initial_groups[1] = 4; variable.initial_groups[2] = 8;
    variable.try_counter = 0;
    variable.reset_count = 0;
    variable.max_group_reset = 9;
    variable.group_reset_result = 0;

    for (int i=0; i<9; i++)
    {
        for (int j=0; j<9; j++)
        {
            variable.two_d_array_of_niner_fields[i][j] = 0;
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
        variable.numbers[i] = x;
        //printf("numbers: %i\n", variable.numbers[i]);
    }

    for (int j=0; j<9; j++)
    {
        if (j>=0 && j<=2)
        {
            for (int h=0; h<3; h++)
            {
                variable.proofrow[j][h] = h;
                //printf("\n%i", proofrow[j][h]);
            }
        }
        else if (j>=3 && j<=5)
        {
            for (int h=0; h<3; h++)
            {
                variable.proofrow[j][h] = h + 3;
                //printf("\n%i", proofrow[j][h]);
            }
        }
        else if (j>=6 && j<=8)
        {
            for (int h=0; h<3; h++)
            {
                variable.proofrow[j][h] = h + 6;
                //printf("\n%i", proofrow[j][h]);
            }
        }
    }

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
        //printf("%i", rest_of_groups[j]);
    }

    return variable;
}


struct variablen setup_groups(struct variablen variable, int type_of_group)
{
    //printf("%i", variable.initial_groups[0]);

    int groups[6];

    int length_groups;
    //printf("%i\n", type_of_group);
    if (type_of_group == 1)
    {
        length_groups = 3;
        for (int i=0; i<3; i++)
        {
            groups[i] = variable.initial_groups[i];
            //printf("%i", groups[i]);
        }
        //printf("%i", groups[0]);
    }
    else
    {
        length_groups = 6;
        for (int i=0; i<6; i++)
        {
            groups[i] = variable.rest_of_groups[i];
            //printf("rest:%i", groups[i]);
        }
    }

    int list_pointer = 0;
    while (list_pointer < length_groups)
    {
        int group = groups[list_pointer];
        variable = define_group(variable, group);


        //done = 1
        if (variable.group_reset_result == 1)
        {
            list_pointer += 1;
        }
        //reset = 0
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


struct variablen define_group(struct variablen variable, int group_number)
{

    variable.try_counter += 1;

    int copy_of_numbers[9];
    int length_copy_of_numbers = 9;


    //copy of numbers füllen
    for (int j=0; j<9; j++)
    {
        copy_of_numbers[j] = variable.numbers[j];
        //printf("copy: %i\n", copy_of_numbers[j]);
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
                //printf("guessed 1: %i\n", guessed_number);
            }while (guessed_number == -1);


            //printf("numbergroup: %i, row: %i, col: %i, guessed_number: %i\n", group_number, row, col, guessed_number);
            while (IsNumberInRow(variable, group_number, row, guessed_number) == 1 || IsNumberInCol(variable, group_number, col, guessed_number) == 1)
            {

                // guessed_number vergeben, also aus möglichen Nummern streichen (0 einsetzen)
                //printf("available: ");
                for (int j=0; j<9; j++)
                {

                    if (inner_copy_of_numbers[j] == guessed_number)
                    {
                        inner_copy_of_numbers[j] = 0;
                        length_inner_copy_of_numbers = length_inner_copy_of_numbers - 1;
                        //printf("length_numbers: %i\n", length_inner_copy_of_numbers);
                    }


                }
                //printf("\n");
                if (length_inner_copy_of_numbers == 0)
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
                //printf("new guessed number: %i\n", guessed_number);
            }
            //printf("2");
            // guessed_number wurde eingesetzt, also aus möglichen Nummern streichen (0 einsetzen)
            for (int j=0; j<9; j++)
            {
                if (copy_of_numbers[j] == guessed_number)
                {
                    copy_of_numbers[j] = 0;
                    length_copy_of_numbers = length_copy_of_numbers - 1;
                }
            }

            variable.nine_niner_fields[group_number][row][col] = guessed_number;
            //printf("group_number: %i; row: %i; col: %i; value: %i\n\n", group_number, row, col, variable.nine_niner_fields[group_number][row][col]);

        }
    }
    variable.group_reset_result = 1;
    return variable;
}

int get_random_number(int number_array[9])
{
    bool number_in_available_numbers = false;
    int index_guessed_number = rand() % 9 ;
    int guessed_number = number_array[index_guessed_number];
    /*
    printf("number_array[%i]:", index_guessed_number);
    for (int i=0; i<9; i++)
    {
        printf(" %i", number_array[i]);
    }
    printf("\n");
    */
    //prüfen, ob zufällige Zahl noch in verfügbaren Zahlen (number_array) enthalten ist,
    //nicht verfügbare Zahlen wurden vorher auf 0 gesetzt

    //printf("number array: %i; guessed: %i\n", number_array[i], guessed_number);
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

int IsNumberInRow(struct variablen variable, int blockid, int innerrow, int number)
{
    //printf("in number is in row");
    int comparelist[9] = {0};
    int lists[3];
    for (int i=0; i<3; i++)
    {
        lists[i] = variable.proofrow[blockid][i];
        //printf("lists: %i, innerrwo: %i, i: %i\n", lists[i], innerrow, i);
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

    /*for (int h=0; h<9; h++)
    {
        printf("%i, %i\n", comparelist[h], number);
    }*/

    //number in comparelist?
    for (int j=0; j<9; j++)
    {
        if (number == comparelist[j])
        {
            //printf("number in row\n");
            return 1;
        }
    }
    return 0;
}

int IsNumberInCol(struct variablen variable, int blockid, int innercol, int number)
{
    int comparelist[9] = {0};
    int lists[3];

    for (int i=0; i<3; i++)
    {
        lists[i] = variable.proofcol[blockid][i];
        //printf("lists: %i, innecol: %i, i: %i\n", lists[i], innercol, i);
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


    /*for (int h=0; h<9; h++)
    {
        printf("%i, %i\n", comparelist[h], number);
    }*/

    //number in comparelist?
    for (int j=0; j<9; j++)
    {
        if (number == comparelist[j])
        {
            //printf("number in col\n");
            return 1;
        }
    }
    return 0;
}

int ausgabe_felder(struct variablen variable)
{
    int j;
    int k;
    int i;

    printf("--------------------\n");

    for (j=0; j<3;j++)
    {
        for (i=0; i<3; i++)
        {
            printf("%i ", variable.nine_niner_fields[j][0][i]);
        }
    }
    printf("\n");
    for (j=0; j<3;j++)
    {
        for (i=0; i<3; i++)
        {
            printf("%i ", variable.nine_niner_fields[j][1][i]);
        }
    }
    printf("\n");
    for (j=0; j<3;j++)
    {
        for (i=0; i<3; i++)
        {
            printf("%i ", variable.nine_niner_fields[j][2][i]);
        }
    }
    printf("\n");
    printf("--------------------\n");

    for (j=3; j<6;j++)
    {
        for (i=0; i<3; i++)
        {
            printf("%i ", variable.nine_niner_fields[j][0][i]);
        }
    }
    printf("\n");
    for (j=3; j<6;j++)
    {
        for (i=0; i<3; i++)
        {
            printf("%i ", variable.nine_niner_fields[j][1][i]);
        }
    }
    printf("\n");
    for (j=3; j<6;j++)
    {
        for (i=0; i<3; i++)
        {
            printf("%i ", variable.nine_niner_fields[j][2][i]);
        }
    }
    printf("\n");
    printf("--------------------\n");

    for (j=6; j<9;j++)
    {
        for (i=0; i<3; i++)
        {
            printf("%i ", variable.nine_niner_fields[j][0][i]);
        }
    }
    printf("\n");
    for (j=6; j<9;j++)
    {
        for (i=0; i<3; i++)
        {
            printf("%i ", variable.nine_niner_fields[j][1][i]);
        }
    }
    printf("\n");
    for (j=6; j<9;j++)
    {
        for (i=0; i<3; i++)
        {
            printf("%i ", variable.nine_niner_fields[j][2][i]);
        }
    }
    printf("\n");




    return 0;

}


struct variablen niner_fields_to_2d_array(struct variablen variable)
{
    int i, j, k;

    int *pointer_to_niner_fields;
    int helper_two_d_array[9][9];
    pointer_to_niner_fields = *variable.nine_niner_fields;
    int zaehler_aufbau_fuellen = 0;
    int counter = 0;
    for (int i=0; i<9; i++)
    {
        for (int j=0; j<9; j++)
        {
            // *result_level ist ein eindimensionales Array mit der Länge 81
            // daher wird zweistelliges Array 9x9 damit befüllt
            helper_two_d_array[i][j] = *(pointer_to_niner_fields + zaehler_aufbau_fuellen);
            //printf("%d\n", level_aufbau[i][j]);
            zaehler_aufbau_fuellen += 1;
        }
    }




    for (int j=0; j<3; j++)
    {
        variable.two_d_array_of_niner_fields[0][j] = helper_two_d_array[0][j];
    }
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

    variable.two_d_array_of_niner_fields[3][0] = helper_two_d_array[3][0];
    variable.two_d_array_of_niner_fields[3][1] = helper_two_d_array[3][1];
    variable.two_d_array_of_niner_fields[3][2] = helper_two_d_array[3][2];
    variable.two_d_array_of_niner_fields[3][3] = helper_two_d_array[4][0];
    variable.two_d_array_of_niner_fields[3][4] = helper_two_d_array[4][1];
    variable.two_d_array_of_niner_fields[3][5] = helper_two_d_array[4][2];
    variable.two_d_array_of_niner_fields[3][6] = helper_two_d_array[5][0];
    variable.two_d_array_of_niner_fields[3][7] = helper_two_d_array[5][1];
    variable.two_d_array_of_niner_fields[3][8] = helper_two_d_array[5][2];



    /*for (int i=3; i<6; i++)
    {
        for (int j=3; j<6; j++)
        {
            variable.two_d_array_of_niner_fields[i][j] = helper_two_d_array[i][j];
        }
    }*/
    for (int i=0; i<9; i++)
    {
        for (int j=0; j<9; j++)
        {
            printf("%i ", variable.two_d_array_of_niner_fields[i][j]);
        }
    }



}

int main()
{
    struct variablen variable;
    srand(time(NULL));

    variable = init_variablen();

    //type group - initial group = 1
    variable = setup_groups(variable, 1);
    variable = setup_groups(variable, 0);
    ausgabe_felder(variable);
    printf("\n\n");
    for (int j=0; j<9;j++)
    {
        for (int i=0; i<3; i++)
        {
            for (int h=0; h<3; h++)
            {
                printf("%i ", variable.nine_niner_fields[j][i][h]);
            }
        }
    }
    printf("\n-----------------------\n finished in %i tries", variable.try_counter);

    variable = niner_fields_to_2d_array(variable);


    return 0;
}
