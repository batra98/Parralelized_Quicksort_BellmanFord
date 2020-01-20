#include<mpi.h>
#include<bits/stdc++.h>
using namespace std;

typedef long long int ll;

vector <ll> edge_u;
vector <ll> edge_v;
vector <ll> weight;

vector <ll> loc_edge_u;
vector <ll> loc_edge_v;
vector <ll> loc_weight;


int main(int argc,char **argv)
{
    int rank, numprocs;

    /* start up MPI */
    MPI_Init( &argc, &argv );

    MPI_Comm_rank( MPI_COMM_WORLD, &rank );
    MPI_Comm_size( MPI_COMM_WORLD, &numprocs );


    ll s,i,j,k,l,m,n,u,v,w;
    ll local_start,local_end;
    string input_filename = "",output_filename = "";

    if(rank == 0)
    {
        input_filename = argv[1];
        output_filename = argv[2];

        ifstream input_file(input_filename);

        input_file >> n >> m;


        for(i=0;i<m;i++)
        {
            input_file >> u >> v >> w;
            edge_u.push_back(u);
            edge_v.push_back(v);
            weight.push_back(w);
        }

        input_file >> s;
    }


    
    /*synchronize all processes*/
    MPI_Barrier( MPI_COMM_WORLD );
    double tbeg = MPI_Wtime();

    /* write your code here */

    MPI_Bcast(&n,1,MPI_LONG_LONG_INT,0,MPI_COMM_WORLD);
    MPI_Bcast(&m,1,MPI_LONG_LONG_INT,0,MPI_COMM_WORLD);
    MPI_Bcast(&s,1,MPI_LONG_LONG_INT,0,MPI_COMM_WORLD);

    if(m%numprocs == 0)
        l = m/numprocs;
    else
        l = m/numprocs+1;

    loc_edge_u.resize(l);
    loc_edge_v.resize(l);
    loc_weight.resize(l);

    MPI_Scatter(edge_u.data(),l,MPI_LONG_LONG_INT,loc_edge_u.data(),l,MPI_LONG_LONG_INT,0,MPI_COMM_WORLD);
    MPI_Scatter(edge_v.data(),l,MPI_LONG_LONG_INT,loc_edge_v.data(),l,MPI_LONG_LONG_INT,0,MPI_COMM_WORLD);
    MPI_Scatter(weight.data(),l,MPI_LONG_LONG_INT,loc_weight.data(),l,MPI_LONG_LONG_INT,0,MPI_COMM_WORLD);


    // cout << "Rank = " << rank << '\n';

    // for(i=0;i<(l);i++)
    //     cout << loc_edge_u[i] << " " << loc_edge_v[i] << " " << loc_weight[i] << '\n';

    if(n >= (l*(rank+1)))
        local_end = l;
    else
        local_end = (n-l*rank);



    ///Bellman-Ford











    // bellman_ford(rank,n,m,s)

    















    MPI_Barrier( MPI_COMM_WORLD );
    double elapsedTime = MPI_Wtime() - tbeg;
    double maxTime;
    MPI_Reduce( &elapsedTime, &maxTime, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD );
    if ( rank == 0 ) {
        printf( "Total time (s): %f\n", maxTime );
    }

    /* shut down MPI */
    MPI_Finalize();
    return 0;
}