#include<bits/stdc++.h>
using namespace std;

typedef long long int ll;

vector <int> input;

void insertion_sort(int low,int high)
{
	int i,j,k;

	for(i=low;i<=high;i++)
	{
		for(j=i;j>low && (input[j] < input[j-1]);j--)
		{
			swap(input[j],input[j-1]);
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

	if(input[a]<input[b])
	{
		if(input[b]<input[c])
			return b;
		else if(input[a]<input[c])
			return c;
		else
			return a;
	}
	else
	{
		if(input[a]>input[c])
			return a;
		else if(input[b]<input[c])
			return c;
		else
			return b;
	}
}

void quicksort(int low,int high)
{
	// cout << low << " " << high << '\n';
	int pivot,i,j,random,p;
	if(low < high)
	{
		if((high-low) <= 20)
		{
			insertion_sort(low,high);
			return;
		}

		i = (low-1);
		// srand(time(NULL));
		random = median(low,high);

		swap(input[high],input[random]);

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




		// p = i+1;

		// if((p-low) < (high-p))
		// {
		// 	quicksort(low,p-1);
		// 	low = p+1;
		// }
		// else
		// {
		// 	quicksort(p+1,high);
		// 	high = p-1;
		// }

		quicksort(low,i);
		quicksort(i+2,high);



	}

}

string isSorted(int n)
{
	int i,j,k,l,m;

	k = input[0];
	for(i=1;i<n;i++)
	{
		if(k>input[i])
			return "NO\n";
		k = input[i];
	}


	return "YES\n";
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
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

	cout << isSorted(n) << '\n';
	// for(i=0;i<n;i++)
	// {
	// 	cout << input[i] << '\n';

		

	// }
	// cout << j << '\n';

	
}