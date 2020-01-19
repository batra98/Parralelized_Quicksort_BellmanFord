// #include<mpi.h>
#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;

vector <ll> input;


void quicksort(ll low,ll high)
{
	// cout << low << " " << high << '\n';
	ll pivot,i,j;
	if(low < high)
	{
		i = (low-1);
		pivot = input[high];

		// cout << "pivot = " << pivot << '\n';

		for(j=low;j<high;j++)
		{
			if(input[j]<pivot)
			{
				i++;
				swap(input[i],input[j]);
			}
		}


		swap(input[i+1],input[high]);

		// for(j=low;j<=high;j++)
		// {
		// 	cout << input[j] << '\n';
		// }




		quicksort(low,i);
		quicksort(i+2,high);



	}

}

void write_to_file(string output_filename)
{
	ll i,j;
	ofstream out_file;
	out_file.open(output_filename);

	for(i=0;i<input.size();i++)
	{
		out_file << input[i] << '\n';
	}

	out_file.close();

}


int main(int argc, char ** argv)
{
	ll i,j,k,l,m,n;

	string input_filename = argv[1],output_filename = argv[2];


	ifstream input_file(input_filename);

	while(input_file >> k)
	{
		input.push_back(k);
	}

	input_file.close();

	n = input.size();

	quicksort(0,n-1);

	write_to_file(output_filename);







}