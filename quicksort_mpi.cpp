#include<mpi.h>
#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;

vector <ll> input;
vector <ll> my_buffer;

void quicksort(ll low,ll high)
{
	ll pivot,i,j;

	if(low < high)
	{
		i = (low-1);
		pivot = my_buffer[high];

		for(j=low;j<high;j++)
		{
			if(my_buffer[j]<pivot)
			{
				i++;
				swap(my_buffer[i],my_buffer[j]);
			}
		}

		swap(my_buffer[i+1],my_buffer[high]);

		quicksort(low,i);
		quicksort(i+2,high);
	}
}

vector <ll> merge(vector <ll> v1,ll n1,vector <ll> v2,ll n2)
{
	ll t,i,j,k;

	vector <ll> aux(n1+n2);

	i = 0;
	j = 0;
	t = 0;
	while(i < n1 && j < n2)
	{
		if(v1[i] <= v2[j])
		{
			aux[t] = v1[i];
			i++;
			t++;
		}
		else
		{
			aux[t] = v2[j];
			j++;
			t++;
		}



	}

	while(i>= n1 && j < n2)
	{
		aux[t] = v2[j];
		j++;
		t++;
	}

	while(j >= n2 && i<n1)
	{
		aux[t] = v1[i];
		i++;
		t++;
	}

	return aux;
}

void write_to_file(string output_filename)
{
	ll i,j;
	ofstream out_file;
	out_file.open(output_filename);

	for(i=0;i<my_buffer.size();i++)
	{
		out_file << my_buffer[i] << " ";
	}
	out_file << '\n';

	out_file.close();

}



int main(int argc, char ** argv)
{
	int rank, numprocs;

    /* start up MPI */
    MPI_Init( &argc, &argv );

    MPI_Comm_rank( MPI_COMM_WORLD, &rank );
    MPI_Comm_size( MPI_COMM_WORLD, &numprocs );
    
    ll i,j,k,l,m,n;
    string input_filename = "",output_filename = "";


    if(rank == 0)
    {
       input_filename = argv[1];
       output_filename = argv[2];
       ifstream input_file(input_filename);

       while(input_file >> k)
       {
       		input.push_back(k);
       }

       input_file.close();

       n = input.size();

       // cout << n << '\n';

    }
    
    /*synchronize all processes*/
    MPI_Barrier( MPI_COMM_WORLD );
    double tbeg = MPI_Wtime();

    /* write your code here */

    MPI_Bcast(&n,1,MPI_LONG_LONG_INT,0,MPI_COMM_WORLD);

    if(n%numprocs == 0)
    	l = n/numprocs;
    else
    	l = n/numprocs+1;

	// vector <ll> my_buffer;
	my_buffer.resize(l);

    MPI_Scatter(input.data(),l,MPI_LONG_LONG_INT,my_buffer.data(),l,MPI_LONG_LONG_INT,0,MPI_COMM_WORLD);


    if(n >= l*(rank+1))
    	m = l;
    else
    	m = (n-l*rank);

    // cout << "Rank = "<< rank << " " << m << '\n';

    quicksort(0,m-1);

    // cout << "Rank = " << rank << '\n';
    // for(i=0;i<m;i++)
    // {
    // 	cout << my_buffer[i] << '\n';
    // }

    // my_buffer=merge(my_buffer,m,my_buffer,m);

    
    // cout << "Rank = " << rank << '\n';
    // for(i=0;i<my_buffer.size();i++)
    // {
    // 	cout << my_buffer[i] << '\n';
    // }


    /// Merge

    MPI_Status st;

    for(ll step = 1;step < numprocs; step *= 2)
    {
    	if(rank % (2*step) != 0)
    	{
    		if((rank-step) >= 0)
    		{
	    		MPI_Send(my_buffer.data(),m,MPI_LONG_LONG_INT,rank-step,0,MPI_COMM_WORLD);
	    		break;
	    	}
    	}

    	if((rank+step) < numprocs)
    	{
    		if(n >= l*(rank+2*step))
    			j = l*step;
    		else
    			j = n - l*(rank+step);

    		vector <ll> o(j);

    		MPI_Recv(o.data(),j,MPI_LONG_LONG_INT,(rank+step),0,MPI_COMM_WORLD,&st);

    		my_buffer = merge(my_buffer,m,o,j);
    		m += j;
    	}

    	// cout << "Rank = " << rank << '\n';
	    // for(i=0;i<my_buffer.size();i++)
	    // {
	    // 	cout << my_buffer[i] << '\n';
	    // }
    } 


    if(rank == 0)
    {
    	// for(i=0;i<my_buffer.size();i++)
    		// cout << my_buffer[i] << '\n';

    	write_to_file(output_filename);


    }










   	










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