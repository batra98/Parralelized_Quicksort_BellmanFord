#include<bits/stdc++.h>
using namespace std;
#define INF LLONG_MAX

typedef long long int ll;

vector < pair<ll,pair<ll,ll> > > edges;

vector <ll> bellman_ford(ll n,ll m,ll src)
{
	ll i,j,k;
	vector <ll> distance(n+1);
	bool changed = false;

	for(i=1;i<=n;i++)
		distance[i] = INF;

	distance[src] = 0;

	for(i=0;i<(n-1);i++)
	{
		changed = false;
		for(j=0;j<m;j++)
		{
			if(distance[edges[j].second.first] < distance[edges[j].second.second]-edges[j].first)
			{
				distance[edges[j].second.second] = distance[edges[j].second.first] + edges[j].first;
				changed = true;
			}

			if(distance[edges[j].second.second] < distance[edges[j].second.first]-edges[j].first)
			{
				distance[edges[j].second.first] = distance[edges[j].second.second] + edges[j].first;
				changed = true;
			}
		}

		

		if(changed == false)
			break;
	}

	return distance;



}

void write_to_file(ll n,vector <ll> distance,string output_filename)
{
	ll i,j;
	ofstream out_file;
	out_file.open(output_filename);

	for(i=1;i<=n;i++)
	{
		out_file << i << " " << distance[i] << '\n';
		cout << i << " " << distance[i] << '\n';

	}
	// out_file << '\n';

	out_file.close();

}

int main(int argc,char ** argv)
{
	ll s,i,j,k,l,m,n,u,v,w;

	string input_filename = argv[1],output_filename = argv[2];

	ifstream input_file(input_filename);

	input_file >> n >> m;


	for(i=0;i<m;i++)
	{
		input_file >> u >> v >> w;

		edges.push_back(pair <ll,pair <ll,ll> > (w,pair <ll,ll> (u,v)));

	}

	input_file >> s;

	// for(i=0;i<edges.size();i++)
	// {
	// 	cout << edges[i].first << " " << edges[i].second.first << " " << edges[i].second.second << '\n';
	// }
	// cout << '\n';
	vector <ll> distance;
	distance = bellman_ford(n,m,s);


	// for(i=1;i<=n;i++)
	// {
	// 	cout << i << " " << distance[i] << '\n';
	// }

	write_to_file(n,distance,output_filename);




}
