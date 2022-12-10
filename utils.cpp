
#include "utils.h"

pair<int, vector<edge>> utils::parse_Files(string filePath)
{
	fstream testGraphIn;
	
	testGraphIn.open(filePath, ios::in);

	string line;

	//gets each string between spaces (space is the delimiter)
	getline(testGraphIn, line, ' ');

	int numberOfVertices = stoi(line);

	int rowIndex = -1;
	int index = 0;

	vector<edge> edges;

	while (getline(testGraphIn, line, ' '))
	{
		
		//since edges table is on a line a mod n condition will partition it into its rows
		if (index % numberOfVertices == 0)
		{
			rowIndex++;
			index = 0;
		}

		//edge intialization
		edge e = {
			rowIndex, //source
			index, //destination
			stoi(line) //weight
		};

		index++;

		edges.push_back(e);
	}

	testGraphIn.close();

	return {numberOfVertices, edges};
}

pair<vector<vector<ll>>, vector<edge>> utils::generate_Random_Edges(ll N, ll Wmin, ll Wmax)
{
	srand(time(NULL)); //seeding random time
	vector<vector<ll>> mat(N, vector<ll>(N, 0));
	vector<edge> edges;
	ll randomWeight;

	for (int i = 0; i < N; i++)
	{
		for (int j = i + 1; j < N; j++)
		{
			randomWeight = rand() % (Wmax + 1);
			if (randomWeight < Wmin)
			{
				randomWeight = 0;
			}

			mat[i][j] = randomWeight;
			edge e
			{
				i,
				j,
				randomWeight
			};

			edges.push_back(e);
		}

		for (int j = 0; j < i; j++)
		{
			mat[i][j] = mat[j][i];
		}
	}

	return {mat, edges};
}

bool utils::valid_Choice(set<int> choices, int choice)
{
	return choices.find(choice) != choices.end();
}

pair<float,float> utils::get_Execution_Times(graph g)
{
	float startTime = clock();
	g.kruskal();
	float endTime = clock();

	float executionTimeK = (double)(endTime - startTime) / CLOCKS_PER_SEC;

	///
	startTime = clock();
	g.prim();
	endTime = clock();

	float executionTimeP = (double)(endTime - startTime) / CLOCKS_PER_SEC;

	return {executionTimeK, executionTimeP};
}

void utils::profile_algorithims(ll Nstart, ll Nend, ll Wmin, ll Wmax, string filePath)
{
	float kruskalTime;
	float primsTime;
	fstream resultsOut;
	string row;

	resultsOut.open(filePath, ios::out);

	for (int i = Nstart; i <= Nend; i++)
	{
		auto p = utils::generate_Random_Edges(i, Wmin, Wmax); //returns pair p of matrix first and vector of edges second
		
		graph g(p.first); //parameterized constructor for matrix

		auto f = utils::get_Execution_Times(g);
		kruskalTime = f.first;
		primsTime = f.second;
		
		row = to_string(i) + "," + to_string(kruskalTime) + "," + to_string(primsTime);

		resultsOut << row << '\n';
	}

	resultsOut.close();
}
