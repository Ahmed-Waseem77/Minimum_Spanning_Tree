
#include "graph.h"

bool cmp(edge u, edge v)
{
	return get<2>(v) < get<2>(u);
}

graph::graph()
{
	_adjMatrix = {};
	_mst = {};
	_nonZeroEdges = {};
	_parent = {};
	_N = 0;
}

graph::graph(vector<edge> edges, ll N)
{
	vector<ll> temp;
	_N = N;
	_mst = {};
	_nonZeroEdges = {};
	ll index = 0;

	//intializing parent
	_parent = new ll[N];
	for (ll i = 0; i < _N; i++)
	{
		_parent[i] = i;
	}

	//initialization of graph and nonZeroEdges
	for (ll i = 0; i < _N; i++)
	{
		for (ll j = 0; j < _N; j++)
		{
			//initializes rows of the weights of edges
			temp.push_back(get<2>(edges[index]));

			//initialization of nonzero edges
			if (get<2>(edges[index]) != 0 && j > i)
			{
				_nonZeroEdges.push(edges[index]);
			}

			index++;
		}

		//pushes rows onto the adjacency list
		_adjMatrix.push_back(temp);
		temp = {};
	}
	

	//intializing the mst
	//mst = kruskal(this)
}

graph::graph(vector<vector<ll>> adjMatrix)
{
	_N = adjMatrix.size();
	_adjMatrix = adjMatrix;
	_mst = {};
	_nonZeroEdges = {};

	//intializing parent
	_parent = new ll[_N];
	for (ll i = 0; i < _N; i++)
	{
		_parent[i] = i;
	}

	for (ll i = 0; i < _N; i++)
	{
		for (ll j = i; j < _N; j++)
		{
			if (adjMatrix[i][j] != 0)
			{
				edge e
				{
					i,
					j,
					adjMatrix[i][j]
				};

				_nonZeroEdges.push(e);
			}
		}
	}
}

void graph::union_Set(ll u, ll v)
{
	_parent[u] = _parent[v];
}

ll graph::find_Set(ll u)
{
	if (u == _parent[u])
		return u;
	else
		return find_Set(_parent[u]);
}

void graph::kruskal()
{
	ll i = 0;
	vector<edge> temp;
	edge tempEdge;
	ll numOfNonZeroEdges = _nonZeroEdges.size();
	auto tempQueue = _nonZeroEdges;

	//heap_sort(_nonZeroEdges, _nonZeroEdges.size());

	while ((i < _N - 1) && !tempQueue.empty())
	{
		//getting min edge
		edge e = tempQueue.top();
		tempQueue.pop();

		//finds sets j and k. j of vertices having u, k of vertices having v
		ll j = find_Set(get<0>(e));
		ll k = find_Set(get<1>(e));

		//if sets not equal (aka graph doesnt contain cycle)
		//push minimum edge, and unionize their sets
		if (i < numOfNonZeroEdges && j != k)
		{

			get<0>(tempEdge) = get<0>(e);
			get<1>(tempEdge) = get<1>(e);
			get<2>(tempEdge) = get<2>(e);
			union_Set(j, k);

			temp.push_back(tempEdge);
			i++;
		}
	}

	update_Mst(temp);
}

void graph::prim() 
{
	ll noEdge = 0;  // number of edges
	vector<edge> tempMse;
	edge temp;
	ll x, y;
	vector<ll> selected(_N, false);
	selected[0] = true;

	while (noEdge < _N - 1)
	{
		ll min = INT_MAX;
		x = 0; y = 0;

		for (ll i = 0; i < _N; i++) {
			if (selected[i]) {
				for (ll j = 0; j < _N; j++) {
					if (!selected[j] && _adjMatrix[i][j])
					{  // not in selected and there is an edge
						if (min > _adjMatrix[i][j])
						{
							min = _adjMatrix[i][j];
							x = i;
							y = j;
						}
					}
				}
			}
		}
		selected[y] = true;
		noEdge++;
		get<0>(temp) = x;
		get<1>(temp) = y;
		get<2>(temp) = _adjMatrix[x][y];
		tempMse.push_back(temp);
	}

	update_Mst(tempMse);
}

void graph::update_Mst(vector<edge> edges)
{
	_mst.resize(_adjMatrix.size(), vector<ll>(_adjMatrix.size(), 0)); //re-empties mst if an mst was computes previously
	vector<ll> temp;
	ll index = 0;

	for (auto i : edges)
	{
		_mst[get<0>(i)][get<1>(i)] = get<2>(i);
	}
}

void graph::print_Graph()
{
	char letter = 'A';

	cout << right << setw(_N / 2) << " ";

	for (ll i = 0; i < _N; i++)
	{
		cout << right << setw(_N / 2) << letter;
		letter++;
	}

	cout << "\n";
	letter = 'A';

	for (ll i = 0; i < _N; i++)
	{
		cout << right << setw(_N / 2) << letter;
		for (ll j = 0; j < _N; j++)
		{
			cout << right << setw(_N / 2) << _adjMatrix[i][j];
		}
		cout << "\n";
		letter++;
	}
}

void graph::print_Mst()
{
	char letter = 'A';

	cout << right << setw(_N / 2) << " ";

	for (ll i = 0; i < _N; i++)
	{
		cout << right << setw(_N / 2) << letter;
		letter++;
	}

	cout << "\n";
	letter = 'A';

	for (ll i = 0; i < _N; i++)
	{
		cout << right << setw(_N / 2) << letter;
		for (ll j = 0; j < _N; j++)
		{
			cout << right << setw(_N / 2) << _mst[i][j];
		}
		cout << "\n";
		letter++;
	}
}

void graph::print_NonZeroEdges() const
{
	auto temp = _nonZeroEdges;
	cout << right << "s: "<< setw(5) <<"d: " << setw(5) << "w: "<< endl;
	for (ll i = 0; i < _nonZeroEdges.size(); i++)
	{
		cout << right << get<0>(temp.top()) << setw(5) << get<1>(temp.top()) << setw(5) << get<2>(temp.top()) << "\n";
		temp.pop();
	}
}

void graph::print_mstEdges() const
{
	cout << "src" << setw(8) << "dst" << setw(8) << "wght\n";
	for (ll i = 0; i < _N; i++)
	{
		for (ll j = 0; j < _N; j++)
		{
			if (_mst[i][j] != 0)
			{
				cout << i << setw(8) << j << setw(8) << _mst[i][j] << "\n";
			}

		}

	}
}

template<class T>
void graph::swap(T* a, T* b)
{
	T temp = *a;
	*a = *b;
	*b = temp;
}

ll graph::get_nonZeroEdges_size()
{
	return _nonZeroEdges.size();
}

ll graph::get_Mst_Cost()
{
	ll sum = 0;
	for (auto i : _mst)
	{
		for (auto j : i)
		{
			if (j != 0)
			{
				sum += j;
			}
		}
	}

	return sum;
}
