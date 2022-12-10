#pragma once

#ifndef UTILS_H
#define UTILS_H


#include "graph.h"
#include <string>
#include <iostream>
#include <fstream>
#include <set>
#include <random>


//utilities class
//serves as a container for functions unrelated to other classes
class utils
{
public:

	//function to parse any text file handling for program initialization
	//files parsed: testgraph.txt (for edges and graph initialization)
	//returns:	1. number of vertices
	//	2. vector of edges
	static pair<int, vector<edge>> parse_Files(string filePath);

	//generates random weighted edges for a graph
	//cut off for random generation is Wmin
	//returns: 1. adjacency matrix
	//	2. vector of edges
	static pair<vector<vector<ll>>, vector<edge>> generate_Random_Edges(ll N, ll Wmin, ll Wmax);

	//profiles mst algorithims using ctime
	//takes starting number of verticies and ending number of vertecies to profile on that range
	//writes the results onto a file, file path given as parameter
	static void profile_algorithims(ll Nstart, ll Nend, ll Wmin, ll Wmax, string filepath);

	//gets execution times of kruskal and prims algorithim on a given graph
	static pair<float, float> get_Execution_Times(graph g);


							///navigation///
	
	//boolean function to validate user choice given a set of choices
	static bool valid_Choice(set<int>, int);
	
};

#endif