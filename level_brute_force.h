#ifndef LEVEL_BRUTE_FORCE_H_INCLUDED
#define LEVEL_BRUTE_FORCE_H_INCLUDED


// Funktionsprototypen
struct variablen init_variablen();
struct variablen setup_groups(struct variablen variable, int type_of_group);
struct variablen define_group(struct variablen variable, int group_number);
int get_random_number(int number_array[9]);
struct variablen reset_group(struct variablen variable, int group_number);
int IsNumberInRow(struct variablen variable, int blockid, int innerrow, int number);
int IsNumberInCol(struct variablen variable, int blockid, int innercol, int number);
struct variablen niner_fields_to_2d_array(struct variablen variable);
struct variablen create_level(struct variablen variable);

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
    int created_level[9][9];
};



#endif // LEVEL_BRUTE_FORCE_H_INCLUDED
