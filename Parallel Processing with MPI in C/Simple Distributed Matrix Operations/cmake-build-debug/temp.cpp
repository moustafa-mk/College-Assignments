#include <stdio.h>
#include <stdlib.h>
#include<mpi.h>

int **alloc_2d_int(int rows, int cols) {
    int i;
    int *data = (int *)malloc(rows*cols*sizeof(int));
    int **array= (int **)malloc(rows*sizeof(int*));
    for ( i=0; i<rows; i++)
        array[i] = &(data[cols*i]);

    return array;
}

int main(int argc, char* argv[])
{
    int i,j,k;
    int Mat1X, Mat1Y, Mat2X,Mat2Y;
    int **Mat1 ;
    int **Mat2 ;
    int **result;
    int my_rank;		/* rank of process ( task id)	*/
    int p;			/* number of process	number of tasks*/
    int source;		/* rank of sender	*/
    int dest;		/* rank of reciever	*/
    int rows;
    int workers;
    int offset;

    MPI_Status status;	/* return status for 	*/

    /* Start up MPI */
    MPI_Init( &argc , &argv );

    /* Find out process rank */
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    /* Find out number of process */
    MPI_Comm_size(MPI_COMM_WORLD, &p);

    workers = p-1;

    if(my_rank==0){

        printf("Enter the first matrix's dimensions\n");
        scanf("%d",&Mat1X);
        scanf("%d",&Mat1Y);
        printf("Enter the second matrix's dimensions\n");
        scanf("%d",&Mat2X);
        scanf("%d",&Mat2Y);
        printf("Enter the first matrix's Data\n");
        Mat1=alloc_2d_int(Mat1X,Mat1Y);
        Mat2= alloc_2d_int(Mat2X,Mat2Y);
        result= alloc_2d_int(Mat1X,Mat2Y);
        for ( i=0; i<Mat1X ; i++)
        {

            for( j=0; j < Mat1Y; j++)
            {
                scanf("%d",&Mat1[i][j]);
            }
        }
        printf("Enter the second matrix's Data\n");
        for ( i=0; i<Mat2X ; i++)
        {

            for( j=0; j < Mat2Y; j++)
            {
                scanf("%d",&Mat2[i][j]);
            }
        }
        for ( i=0; i<Mat1X; i++)
        {

            for( j=0; j<Mat2Y; j++)
            {
                result[i][j]=0;
            }
        }


        rows= Mat1X/workers;
        offset=0;
        for (dest=1; dest<=workers; dest++)
        {
            MPI_Send(&offset, 1, MPI_INT, dest, 1, MPI_COMM_WORLD);
            MPI_Send(&rows, 1, MPI_INT, dest, 1, MPI_COMM_WORLD);
            MPI_Send(&(Mat1[0][0]), rows*Mat1Y, MPI_INT,dest,1, MPI_COMM_WORLD);
            MPI_Send(&(Mat2[0][0]), Mat2X*Mat2Y, MPI_INT, dest, 1, MPI_COMM_WORLD);
            offset = offset + rows;
        }


    }

    if(my_rank !=0){
        Mat1=alloc_2d_int(Mat1X,Mat1Y);
        Mat2= alloc_2d_int(Mat2X,Mat2Y);
        result= alloc_2d_int(Mat1X,Mat2Y);
        source = 0;
        MPI_Recv(&offset, 1, MPI_INT, source, 1, MPI_COMM_WORLD, &status);
        MPI_Recv(&rows, 1, MPI_INT, source, 1, MPI_COMM_WORLD, &status);
        MPI_Recv(&(Mat1[0][0]), rows*Mat1Y, MPI_INT, source, 1, MPI_COMM_WORLD, &status);
        MPI_Recv(&(Mat2[0][0]), Mat2X*Mat2Y, MPI_INT, source, 1, MPI_COMM_WORLD, &status);

        for ( i=0; i<Mat1X; i++)
        {
            for( j=0; j<rows; j++)
            {
                for( k=0; k<Mat1Y; k++)
                {
                    result[i][j]+=Mat1[i][k]*Mat2[k][j];
                }
            }
        }
        
        MPI_Send(&offset, 1, MPI_INT, 0, 2, MPI_COMM_WORLD);
        MPI_Send(&rows, 1, MPI_INT, 0, 2, MPI_COMM_WORLD);
        MPI_Send(&(result[0][0]), rows*Mat2Y, MPI_INT, 0, 2, MPI_COMM_WORLD);

    }

    if(my_rank==0){
        for (i=1; i<=workers; i++)
        {
            source = i;
            MPI_Recv(&offset, 1, MPI_INT, source, 2, MPI_COMM_WORLD, &status);
            MPI_Recv(&rows, 1, MPI_INT, source, 2, MPI_COMM_WORLD, &status);
            MPI_Recv(&(result[0][0]), rows*Mat2Y, MPI_INT, source, 2, MPI_COMM_WORLD, &status);
        }
        for ( i=0; i<Mat1X; i++)
        {

            for( j=0; j<Mat2Y; j++)
            {
                printf("%d", result[i][j]);
                printf("%c",' ');
            }
            printf("%c",'\n');
        }


    }
    MPI_Finalize();

}