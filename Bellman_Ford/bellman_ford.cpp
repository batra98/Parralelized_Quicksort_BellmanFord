#include<bits/stdc++.h>
using namespace std;
#define INF 1000000009

typedef long long int ll;

vector < pair<int,pair<int,int> > > edges;

vector <int> bellman_ford(int n,int m,int src)
{
	int i,j,k;
	vector <int> distance(n);
	bool changed = false;

	for(i=1;i<=n;i++)
		distance[i] = INF;

	distance[src] = 0;

	for(i=0;i<(n-1);i++)
	{
		changed = false;
		for(j=0;j<m;j++)
		{
			if(distance[edges[j].second.first] + edges[j].first < distance[edges[j].second.second])
			{
				distance[edges[j].second.second] = distance[edges[j].second.first] + edges[j].first;
				changed = true;
			}

			if(distance[edges[j].second.second] + edges[j].first < distance[edges[j].second.first])
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

int main(int argc,char ** argv)
{
	int s,i,j,k,l,m,n,u,v,w;

	string input_filename = argv[1],output_filename = argv[2];

	ifstream input_file(input_filename);

	input_file >> n >> m;


	for(i=0;i<m;i++)
	{
		input_file >> u >> v >> w;

		edges.push_back(pair <int,pair <int,int> > (w,pair <int,int> (u,v)));

	}

	input_file >> s;

	for(i=0;i<edges.size();i++)
	{
		cout << edges[i].first << " " << edges[i].second.first << " " << edges[i].second.second << '\n';
	}
	// cout << '\n';
	vector <int> distance;
	distance = bellman_ford(n,m,s);


	for(i=1;i<=n;i++)
	{
		cout << i << " " << distance[i] << '\n';
	}




}
