#include "gen_1ax1b.h"

#include <stdio.h>
#include <stdlib.h>
#include <vector>

#include "uniform.h"

static void gen_1ax1b_one_page(const char* file_name, int page_index);

void gen_1ax1b(int page_number, const char* file_name)
{
    if (file_name == NULL) {
        printf("ERROR: file_name is null\n");
        return;
    }

    for (int page_index = 0; page_index < page_number; page_index++) {
        gen_1ax1b_one_page(file_name, page_index);
    }
}

/*
Count: 4 x 20
  11 x 12 =        11 x 12 =        11 x 12 =        11 x 12 =        
*/
static void gen_1ax1b_one_page(const char* file_name, int page_index)
{
    const int COLUMNS = 4;
    const int ROWS = 20;
    std::vector< std::pair<int, int> > values(COLUMNS * ROWS);

    int index = 0;
    Uniform uniform(11, 20);
    for (int row = 0; row < ROWS; row++) {
        printf("  ");
        for (int column = 0; column < COLUMNS; column++) {
            values[index].first = (int)uniform.next();
            values[index].second = (int)uniform.next();
            printf("%02d x %02d =        ", values[index].first, values[index].second);

            index++;
        }

        printf("\n\n");
    }

    printf("Answer:\n");
    index = 0;
    for (int row = 0; row < ROWS; row++) {
        printf("  ");
        for (int column = 0; column < COLUMNS; column++) {
            printf("%02d x %02d = %3d    ", values[index].first, values[index].second,
                values[index].first * values[index].second);
            index++;
        }

        printf("\n\n");
    }
}