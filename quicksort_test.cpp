#include<bits/stdc++.h>
using namespace std;

typedef long long int ll;

vector <int> input;

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

int main()
{
	int i,j,k,l,m,n,t;

	
	input.clear();
	cin >> n;

	for(i=0;i<n;i++)
	{
		cin >> k;
		input.push_back(k);
	}

	quicksort(0,n-1);
	j = 0;
	for(i=1;i<n;i+=2)
	{
		// cout << input[i] << " ";

		if(input[i] != input[i-1])
			j+=(input[i]-input[i-1]);

	}
	cout << j << '\n';

	
}