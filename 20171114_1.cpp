#include<mpi.h>
#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;

vector <ll> input;
vector <ll> my_buffer;

void insertion_sort(int low,int high)
{
	int i,j,k;

	for(i=low;i<=high;i++)
	{
		for(j=i;j>low && (my_buffer[j] < my_buffer[j-1]);j--)
		{
			swap(my_buffer[j],my_buffer[j-1]);
		}
	}
}

int median(int low,int high)
{
	int a,b,c,d,e,f;

	srand(time(NULL));
	a = low + rand()%(high-low);
	b = low + rand()%(high-low);
	c = low + rand()%(high-low);

	// cout << a << " " << b << " " << c << '\n'; 

	if(my_buffer[a]<my_buffer[b])
	{
		if(my_buffer[b]<my_buffer[c])
			return b;
		else if(my_buffer[a]<my_buffer[c])
			return c;
		else
			return a;
	}
	else
	{
		if(my_buffer[a]>my_buffer[c])
			return a;
		else if(my_buffer[b]<my_buffer[c])
			return c;
		else
			return b;
	}
}

void quicksort(ll low,ll high)
{
	ll pivot,i,j,random,p;

	if(low < high)
	{
		if((high-low) <= 20)
		{
			insertion_sort(low,high);
			return;
		}

		i = (low-1);

		random = median(low,high);

		swap(my_buffer[high],my_buffer[random]);
		
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

string isSorted(ll n)
{

	ll i,j,k,l,m;

	l = my_buffer.size();

	if(l!=n)
	{
		return "NO\n";

	}

	k = my_buffer[0];
	for(i=1;i<n;i++)
	{
		if(k>my_buffer[i])
		{
			cout << k << " " << my_buffer[i] << '\n';
			return "NO\n";
		}

		k = my_buffer[i];
	}


	return "YES\n";
}



int main(int argc, char ** argv)
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int rank, numprocs;

    /* start up MPI */
    MPI_Init( &argc, &argv );

    MPI_Comm_rank( MPI_COMM_WORLD, &rank );
    MPI_Comm_size( MPI_COMM_WORLD, &numprocs );
    
    ll i,j,k,l,m,n;
    string input_filename = "",output_filename = "";

    if(argc < 2)
    {
        cout << "Usage: mpirun -np numprocs a.out input.txt output.txt\n";
        return 0;
    }


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
    m = max(m,(ll)0);

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
    	// cout << "Rank = " << rank << " " << step << '\n';

    	if(rank % (2*step) != 0)
    	{
    		// if((rank-step) >= 0)
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

    		if(j <= 0)
    			continue;

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

	    // break;

    } 


    if(rank == 0)
    {
    	// for(i=0;i<my_buffer.size();i++)
    		// cout << my_buffer[i] << '\n';

    	write_to_file(output_filename);

    	// cout << isSorted(n);



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