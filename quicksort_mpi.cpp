#include<mpi.h>
#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;

vector <int> input;
vector <int> my_buffer;



int main(int argc, char ** argv)
{
	int rank, numprocs;

    /* start up MPI */
    MPI_Init( &argc, &argv );

    MPI_Comm_rank( MPI_COMM_WORLD, &rank );
    MPI_Comm_size( MPI_COMM_WORLD, &numprocs );
    
    int i,j,k,l,m,n;


    if(rank == 0)
    {
       string input_filename = argv[1],output_filename = argv[2];
       ifstream input_file(input_filename);

       while(input_file >> k)
       {
       		input.push_back(k);
       }

       input_file.close();

       n = input.size();

       cout << n << '\n';

    }
    
    /*synchronize all processes*/
    MPI_Barrier( MPI_COMM_WORLD );
    double tbeg = MPI_Wtime();

    /* write your code here */

    MPI_Bcast(&n,1,MPI_INT,0,MPI_COMM_WORLD);

    if(n%numprocs == 0)
    	l = n/numprocs;
    else
    	l = n/numprocs+1;

	// vector <int> my_buffer;
	my_buffer.resize(l);

    MPI_Scatter(input.data(),l,MPI_INT,my_buffer.data(),l,MPI_INT,0,MPI_COMM_WORLD);

    // cout << "Rank = " << rank << '\n';
    // for(i=0;i<l;i++)
    // {
    // 	cout << my_buffer[i] << '\n';
    // }

    if(n >= l*(rank+1))
    	m = l;
    else
    	m = (n-l*rank);

    cout << "Rank = "<< rank << " " << m << '\n';






   	










    MPI_Barrier( MPI_COMM_WORLD );
    double elapsedTime = MPI_Wtime() - tbeg;
    double maxTime;
    MPI_Reduce( &elapsedTime, &maxTime, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD );
    if ( rank == 0 ) {
        cout << "Total time (s): " << maxTime << '\n';
    }

    /* shut down MPI */
    MPI_Finalize();
    return 0;
}