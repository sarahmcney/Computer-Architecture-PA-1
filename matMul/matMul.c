#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

int dotproduct(int row[], int col[], int size);
int main(int argc, char* argv[])
{
    FILE* matrix_a_fp = fopen(argv[1], "r");
    if (!matrix_a_fp) {
        perror("fopen failed");
        return EXIT_FAILURE;
    }
    char buff[256];

    //length_l = num rows
    fscanf(matrix_a_fp, "%s", buff);
    char length_l_a = atoi(buff);
    int** matrix_a = malloc( length_l_a * sizeof(int*) );

    //length_m = new cols
    fscanf(matrix_a_fp, "%s", buff);
    char length_m_a = atoi(buff);

    for ( unsigned char i=0; i<length_l_a; i++ ) {
        //for each row: allocate enough space for each integer in the row
        matrix_a[i] = malloc( length_m_a * sizeof(int) );
    }

    for(int i = 0; i < length_l_a; i++) {
        for(int j = 0; j < length_m_a; j++) {
            fscanf(matrix_a_fp, "%s", buff);
            int item = atoi(buff);
            matrix_a[i][j] = item;
        }
    }

    fclose(matrix_a_fp);

    //redo for matrix_b
    FILE* matrix_b_fp = fopen(argv[2], "r");
    if (!matrix_b_fp) {
        perror("fopen failed");
        return EXIT_FAILURE;
    }

    fscanf(matrix_b_fp, "%s", buff);
    char length_l_b = atoi(buff);
    int** matrix_b = malloc( length_l_b * sizeof(int*) );

    fscanf(matrix_b_fp, "%s", buff);
    char length_m_b = atoi(buff);

    for ( unsigned char i=0; i<length_l_b; i++ ) {
        matrix_b[i] = malloc( length_m_b * sizeof(int) );
    }

    for(int i = 0; i < length_l_b; i++) {
        for(int j = 0; j < length_m_b; j++) {
            fscanf(matrix_b_fp, "%s", buff);
            int item = atoi(buff);
            matrix_b[i][j] = item;
        }
    }

    fclose(matrix_b_fp);

    int** result = malloc(length_l_a * sizeof(int*));
    for ( unsigned char i=0; i<length_l_a; i++ ) {
        result[i] = malloc( length_m_b * sizeof(int) );
    }

    //set up dot product call
    int col[length_l_b];
    for(int i = 0; i < length_l_a; i++) {
        for(int j = 0; j < length_m_b; j++) {
            for(int k = 0; k < length_l_b; k++) {
                col[k] = matrix_b[k][j];
            }
            result[i][j] = dotproduct(matrix_a[i], col, length_l_b);
        }
    }

    for(int i = 0; i < length_l_a; i++) {
        for(int j = 0; j < length_m_b; j++) {
            printf("%d ", result[i][j]);
        }
    }

    for ( unsigned char i=0; i<length_l_a; i++ ) {
        free( matrix_a[i] );
    }
    free( matrix_a );

    for (unsigned char i=0; i<length_l_b; i++) {
        free(matrix_b[i]);
    }
    free(matrix_b);

    for (unsigned char i=0; i<length_l_a; i++) {
        free(result[i]);
    }
    free(result);

    return 0;

}

int dotproduct(int row[], int col[], int size) {
    int result = 0;
    for(int i = 0; i < size; i++) {
        result = result + row[i] * col[i];
    }
    return result;
}