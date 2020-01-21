#include<mpi.h>
#include<bits/stdc++.h>
using namespace std;
#define INF 1000000009

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
        // cout << loc_edge_u[i] << " " << loc_edge_v[i] << " " << loc_weight[i] << '\n';

    if(m >= (l*(rank+1)))
        local_end = l;
    else
        local_end = (m-l*rank);

    // cout << "LOCAL_END = " << local_end << '\n';




    ///Bellman-Ford

    vector <ll> distance(n+1);
    bool changed = false;

    for(i=1;i<=n;i++)
        distance[i] = INF;

    distance[s] = 0;

    // cout << "Rank = " << rank << '\n';

    // for(i=1;i<=n;i++)
    //     cout << i << " " << distance[i] << '\n';


    for(i=0;i<(n-1);i++)
    {
        // cout << "LOCAL_END = " << local_end << '\n';
        changed = false;
        for(j=0;j<l;j++)
        {
            if(distance[loc_edge_u[j]]+loc_weight[j] < distance[loc_edge_v[j]])
            {
                distance[loc_edge_v[j]] = distance[loc_edge_u[j]] + loc_weight[j];
                changed = true;
            }

            if(distance[loc_edge_v[j]]+loc_weight[j] < distance[loc_edge_u[j]])
            {
                distance[loc_edge_u[j]] = distance[loc_edge_v[j]] + loc_weight[j];
                changed = true;
            }
        }

        MPI_Allreduce(MPI_IN_PLACE,&changed,1,MPI_CXX_BOOL,MPI_LOR,MPI_COMM_WORLD);
        MPI_Allreduce(MPI_IN_PLACE,distance.data(),n+1,MPI_LONG_LONG_INT,MPI_MIN,MPI_COMM_WORLD);
        // MPI_Bcast(distance.data(),n,MPI_LONG_LONG_INT,0,MPI_COMM_WORLD);
        // if(rank == 0)
        // {
        //     cout << "Rank = " << rank << '\n';
        //     for(k=1;k<=n;k++)
        //     {
        //         cout << k << " " << distance[k] << '\n';
        //     }

        //     // cout << i << '\n';
        // }

            // cout << changed << '\n';

        if(changed == false)
            break;

    }





    if(rank == 0)
    {
        for(i=1;i<=n;i++)
        {
            cout << i << " " << distance[i] << '\n';
        }
    }











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