#pragma once

#ifndef GRAPH_H
#define GRAPH_H

#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <vector>
#include <algorithm>

#define ll long long int
#define edge tuple<ll, ll, int> 

using namespace std;

//comparator sruct so stl priority queues can properly deal with edges
struct edgeTupleComparator
{
	int operator()(const tuple<int, int, int>& tuple1, const tuple<int, int, int>& tuple2)
	{
			return get<2>(tuple1) > get<2>(tuple2);
	}
};

//class of graph
//adjacency matrix representation
class graph
{
private:
	vector<vector<ll>> _adjMatrix; //adjacency matrix
	vector<vector<ll>> _mst; //minumum spanning tree
	priority_queue<edge, vector<edge>, edgeTupleComparator> _nonZeroEdges; //vector of non zero weight edges (sorted with initialization)
	ll *_parent; 
	ll _N; //number of vertices in graph

public:

	//default constructor
	graph();

	//parameterized constructor of vector of edges as a parameter
	graph(vector<edge> edges, ll N);

	//parameterized constructor of adjmatrix as a parameter
	graph(vector<vector<ll>> adjMatrix);

	ll get_nonZeroEdges_size();

	ll get_Mst_Cost();

		//////methods//////

	void union_Set(ll u, ll v);

	ll find_Set(ll u);

	//kruskals algorithim for finding minimum spanning tree (mst)
	//uses minimum heap (priority queue)
	void kruskal();

	//prims algorithim for finding mst
	void prim();

	//updates the mst
	//is called when a minimum spanning tree algorithim is called
	void update_Mst(vector<edge> edges);

	template<class T>
	void swap(T* a, T* b);

		///print methods///

	void print_Graph();

	void print_Mst();

	void print_NonZeroEdges() const;

	void print_mstEdges() const;

};

#endif
