#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

int **alloc_array(int n, int m) {
    int i;
    int *data = (int *) malloc(n * m * sizeof(int));
    int **array = (int **) malloc(n * sizeof(int *));
    for (i = 0; i < n; i++)
        array[i] = &(data[m * i]);

    return array;
}

void read_data(int **arr, int n, int m) {
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) scanf("%d", &arr[i][j]);
    }
}

int main(int argc, char *argv[]) {

    int num_processes, rank, num_slaves, tag = 0,
        rows_to_send, div, mod, offset,
        i, j, k,
        **a, **b, **c,
        rows_1, cols_1,
        rows_2, cols_2;

    const int master_id = 0;

    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &num_processes);
    if (num_processes < 2) {
        printf("Number of processes must be greater than 1");
        return 0;
    }

    num_slaves = num_processes - 1;

    if (rank == master_id) {            //MASTER

        printf("\nEnter dimensions of first matrix: ");
        scanf("%d %d", &rows_1, &cols_1);
        a = alloc_array(rows_1, cols_1);
        printf("\nPlease enter its elements:\n");
        read_data(a, rows_1, cols_1);

        printf("\nEnter dimensions of second matrix: ");
        scanf("%d %d", &rows_2, &cols_2);
        b = alloc_array(rows_2, cols_2);
        printf("\nPlease enter its elements:\n");
        read_data(b, rows_2, cols_2);

        if (cols_1 != rows_2) {
            printf("The dimensions of matrices are not suitable for multiplying, exiting .....\n");
            return 0;
        }

        c = alloc_array(rows_1, cols_2);

        div = rows_1 / num_slaves;
        mod = rows_1 % num_slaves;

        offset = 0;
        int slave_id;
        for (slave_id = 1; slave_id <= num_slaves; slave_id++) {
            tag = 0;
            rows_to_send = (slave_id <= mod) ? div + 1 : div;

            MPI_Send(&cols_1, 1, MPI_INT, slave_id, tag++, MPI_COMM_WORLD);
            MPI_Send(&cols_2, 1, MPI_INT, slave_id, tag++, MPI_COMM_WORLD);
            MPI_Send(&offset, 1, MPI_INT, slave_id, tag++, MPI_COMM_WORLD);
            MPI_Send(&rows_to_send, 1, MPI_INT, slave_id, tag++, MPI_COMM_WORLD);

            MPI_Send(&(a[offset][0]), rows_to_send * cols_1, MPI_INT, slave_id, tag++,
                     MPI_COMM_WORLD);
            MPI_Send(&(b[0][0]), cols_1 * cols_2, MPI_INT, slave_id, tag++, MPI_COMM_WORLD);

            offset = offset + rows_to_send;
        }

        /*** Receive results from slaves */

        for (slave_id = 1; slave_id <= num_slaves; slave_id++) {
            tag = 0;
            MPI_Recv(&offset, 1, MPI_INT, slave_id, tag++, MPI_COMM_WORLD, &status);
            MPI_Recv(&rows_to_send, 1, MPI_INT, slave_id, tag++, MPI_COMM_WORLD, &status);
            MPI_Recv(&(c[offset][0]), rows_to_send * cols_2, MPI_DOUBLE, slave_id, tag++,
                     MPI_COMM_WORLD, &status);
        }

        /* Print results */
        printf("\n\n");
        printf("Result Matrix (%d x %d):", rows_1, cols_2);
        for (i = 0; i < rows_1; i++) {
            printf("\n");
            for (j = 0; j < cols_2; j++)
                printf("%d  ", c[i][j]);
        }
        printf("\n");
    }

    if (rank > 0) {         //SLAVES
        tag = 0;
        MPI_Recv(&cols_1, 1, MPI_INT, master_id, tag++, MPI_COMM_WORLD, &status);
        MPI_Recv(&cols_2, 1, MPI_INT, master_id, tag++, MPI_COMM_WORLD, &status);
        MPI_Recv(&offset, 1, MPI_INT, master_id, tag++, MPI_COMM_WORLD, &status);

        MPI_Recv(&rows_to_send, 1, MPI_INT, master_id, tag++, MPI_COMM_WORLD, &status);

        a = alloc_array(rows_to_send, cols_1);
        b = alloc_array(cols_1, cols_2);
        c = alloc_array(rows_to_send, cols_2);

        MPI_Recv(&(a[0][0]), rows_to_send * cols_1, MPI_DOUBLE, master_id, tag++, MPI_COMM_WORLD, &status);
        MPI_Recv(&(b[0][0]), cols_1 * cols_2, MPI_DOUBLE, master_id, tag++, MPI_COMM_WORLD, &status);

        printf("%d", b[0][0]);

        for (k = 0; k < cols_2; k++)
            for (i = 0; i < rows_to_send; i++) {
                c[i][k] = 0;
                for (j = 0; j < cols_1; j++)
                    c[i][k] = c[i][k] + a[i][j] * b[j][k];
            }

        tag = 0;
        MPI_Send(&offset, 1, MPI_INT, master_id, tag++, MPI_COMM_WORLD);
        MPI_Send(&rows_to_send, 1, MPI_INT, master_id, tag++, MPI_COMM_WORLD);
        MPI_Send(&(c[0][0]), rows_to_send * cols_2, MPI_DOUBLE, master_id, tag++, MPI_COMM_WORLD);
    }
    MPI_Finalize();
}
