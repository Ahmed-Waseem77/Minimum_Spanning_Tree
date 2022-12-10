
#include "utils.h"

void clear_console()
{
	cout << "\x1B[2J\x1B[H";
}

void option1()
{
	string filePath;
	cout << "Please enter the file path of your graph is located: \n";
	cin.ignore();
	cin >> filePath;

	auto e = utils::parse_Files(filePath);
	graph g(e.second, e.first);

	cout << "\n\n\nYour Graph: \n\n";
	g.print_Graph();
	cout << "\n\n\nNon Zero Edges within your Graph: \n\n";
	g.print_NonZeroEdges();
	cout << "\n\nNumber of non zero Edges: " << g.get_nonZeroEdges_size();

	cout << "\n\n\nMinimum spanning tree of your Graph (By Kruskal's): \n\n";
	g.kruskal();
	g.print_Mst();
	cout << "\n\nMinimum spanning Edges: \n\n";
	g.print_mstEdges();
	cout << "\n\nYour Minimum spanning cost is: " << g.get_Mst_Cost() << "\n\n\n\n\n\n";
	
}

void option2()
{
	string filePath;
	cout << "Please enter the file path of your graph is located: \n";
	cin.ignore();
	cin >> filePath;

	auto e = utils::parse_Files(filePath);
	graph g(e.second, e.first);

	cout << "\n\n\nYour Graph: \n\n";
	g.print_Graph();
	cout << "\n\n\nNon Zero Edges within your Graph: \n\n";
	g.print_NonZeroEdges();
	cout << "\n\nNumber of non zero Edges: " << g.get_nonZeroEdges_size();

	cout << "\n\n\nMinimum spanning tree of your Graph (By Prim's): \n\n";
	g.prim();
	g.print_Mst();
	cout << "\n\nMinimum spanning Edges: \n\n";
	g.print_mstEdges();
	cout << "\n\nYour Minimum spanning cost is: " << g.get_Mst_Cost() << "\n\n\n\n\n\n";
}

void option3()
{
	string filePath;
	fstream fileOut;
	ll N, Wmin, Wmax;

	cout << "Enter number of vertices of your graph: ";
	cin >> N;

	cout << "\nEnter the minimum weight of an edge: ";
	cin >> Wmin;

	cout << "\nEnter the maximum weight of an edge: ";
	cin >> Wmax;

	cout << "\nEnter file destination: ";
	cin >> filePath;

	clear_console();

	fileOut.open(filePath, ios::out);

	auto e = utils::generate_Random_Edges(N, Wmin, Wmax);
	graph g(e.first);
	cout << "\n\nYour Graph: \n\n";
	g.print_Graph();

	fileOut << e.first.size() << ' ';

	for (auto i : e.first)
	{
		for (auto j : i)
		{
			fileOut << j << ' ';
		}
	}

	cout << "\nsaved to " << filePath;
	cout << "\n\n\n\n\n\n";
	fileOut.close();

}

void option4()
{
	string filePath;
	ll Nstart, Nend, Wmin, Wmax;

	cout << "Enter number of vertices to start profiling from: ";
	cin >> Nstart;

	cout << "\nEnter number of vertices to end profiling at: ";
	cin >> Nend;

	cout << "\nEnter the minimum weight of an edge of randomly generated matricies: ";
	cin >> Wmin;

	cout << "\nEnter the maximum weight of an edge of randomly generated matricies: ";
	cin >> Wmax;

	cout << "\nEnter file destination: ";
	cin >> filePath;

	utils::profile_algorithims(Nstart, Nend, Wmin, Wmax, filePath);

	cout << "\nProfiling done! data saved as a csv to " << filePath;
	cout << "\n\n\n\n\n\n";
}

int main()
{
	int userin = 0;
	cout << "Welcome what do you want to do?: ";

	while (userin != -1)
	{
		cout << "\n1. Apply Kruskal on a Graph file\n2. Apply Prim's on a Graph file\n3. Generate a random graph and store it in a file\n4. Generate custom profiling of both Algorithims\n5. Exit\n\n Type in your choice: ";

		cin >> userin;
		cout << "\n";
		while (!utils::valid_Choice({ 1, 2, 3, 4, 5 }, userin) && cin.fail())
		{
			cout << "Invalid input, Please try again\n";
			cin.ignore();
			cin >> userin;
		}
		switch (userin)
		{
		case(1):
			clear_console();
			option1();
			break;
		case(2):
			clear_console();
			option2();
			break;
		case(3):
			clear_console();
			option3();
			break;
		case(4):
			clear_console();
			option4();
			break;
		case(5):
			exit(1);
		}
	}
}