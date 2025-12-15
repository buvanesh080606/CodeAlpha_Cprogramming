#include <stdio.h>
#include <stdlib.h>

#define MAX 10
int i,j,k;
// --- Function Prototypes ---
void readMatrix(int mat[MAX][MAX], int r, int c, char *name);
void printMatrix(int mat[MAX][MAX], int r, int c);
void addMatrix(int mat1[MAX][MAX], int r1, int c1, int mat2[MAX][MAX], int r2, int c2, int res[MAX][MAX]);
void multiplyMatrix(int mat1[MAX][MAX], int r1, int c1, int mat2[MAX][MAX], int r2, int c2, int res[MAX][MAX]);
void transposeMatrix(int mat[MAX][MAX], int r, int c, int res[MAX][MAX]);

int main() {
    int mat1[MAX][MAX], mat2[MAX][MAX], result[MAX][MAX];
    int r1, c1, r2, c2;
    int choice;

    while (1) {
        printf("\n--- Matrix Operations Menu ---\n");
        printf("1. Matrix Addition\n");
        printf("2. Matrix Multiplication\n");
        printf("3. Matrix Transpose\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: // Addition
                printf("Enter rows and cols for Matrix A: ");
                scanf("%d %d", &r1, &c1);
                printf("Enter rows and cols for Matrix B: ");
                scanf("%d %d", &r2, &c2);

                if (r1 != r2 || c1 != c2) {
                    printf("\nError: Addition requires matrices of the same dimensions.\n");
                } else {
                    readMatrix(mat1, r1, c1, "A");
                    readMatrix(mat2, r2, c2, "B");
                    addMatrix(mat1, r1, c1, mat2, r2, c2, result);
                    printf("\nResult of A + B:\n");
                    printMatrix(result, r1, c1);
                }
                break;

            case 2: // Multiplication
                printf("Enter rows and cols for Matrix A: ");
                scanf("%d %d", &r1, &c1);
                printf("Enter rows and cols for Matrix B: ");
                scanf("%d %d", &r2, &c2);

                if (c1 != r2) {
                    printf("\nError: Multiplication not possible. Cols of A must match Rows of B.\n");
                } else {
                    readMatrix(mat1, r1, c1, "A");
                    readMatrix(mat2, r2, c2, "B");
                    multiplyMatrix(mat1, r1, c1, mat2, r2, c2, result);
                    printf("\nResult of A * B (Dimension %dx%d):\n", r1, c2);
                    printMatrix(result, r1, c2);
                }
                break;

            case 3: // Transpose
                printf("Enter rows and cols for Matrix A: ");
                scanf("%d %d", &r1, &c1);
                readMatrix(mat1, r1, c1, "A");
                transposeMatrix(mat1, r1, c1, result);
                printf("\nTranspose of Matrix A:\n");
                // Note: rows and columns are swapped in printing
                printMatrix(result, c1, r1); 
                break;

            case 4:
                printf("Exiting program.\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}

// --- Function Definitions ---

// Helper function to read matrix elements
void readMatrix(int mat[MAX][MAX], int r, int c, char *name) {
    printf("\nEnter elements for Matrix %s (%dx%d):\n", name, r, c);
    for ( i = 0; i < r; i++) {
        for ( j = 0; j < c; j++) {
            printf("Element [%d][%d]: ", i, j);
            scanf("%d", &mat[i][j]);
        }
    }
}

// Helper function to print matrix elements
void printMatrix(int mat[MAX][MAX], int r, int c) {
    for (i = 0; i < r; i++) {
        for (j = 0; j < c; j++) {
            printf("%d\t", mat[i][j]);
        }
        printf("\n");
    }
}

void addMatrix(int mat1[MAX][MAX], int r1, int c1, int mat2[MAX][MAX], int r2, int c2, int res[MAX][MAX]) {
    for ( i = 0; i < r1; i++) {
        for (j = 0; j < c1; j++) {
            res[i][j] = mat1[i][j] + mat2[i][j];
        }
    }
}

void multiplyMatrix(int mat1[MAX][MAX], int r1, int c1, int mat2[MAX][MAX], int r2, int c2, int res[MAX][MAX]) {
    // Initialize result matrix to 0
    for (i = 0; i < r1; i++) {
        for (j = 0; j < c2; j++) {
            res[i][j] = 0;
        }
    }

    // Multiplication logic
    for (i = 0; i < r1; i++) { // Iterate through rows of Mat1
        for (j = 0; j < c2; j++) { // Iterate through columns of Mat2
            for ( k = 0; k < c1; k++) { // Iterate through common dimension
                res[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }
}

void transposeMatrix(int mat[MAX][MAX], int r, int c, int res[MAX][MAX]) {
    for (i = 0; i < r; i++) {
        for ( j = 0; j < c; j++) {
            // Swap indices: row becomes column, column becomes row
            res[j][i] = mat[i][j];
        }
    }
}
