#include "EdgeVertex.h"
#include <iostream>

using namespace std;

int main()
{
	VertexDList vertex;
	// Adding string vertices/Cities
	vertex.addVertexList("Seattle");
	vertex.addVertexList("SanFrancisco");
	vertex.addVertexList("LosAngeles");
	vertex.addVertexList("LasVegas");
	vertex.addVertexList("Denver");
	vertex.addVertexList("Minneapolis");
	vertex.addVertexList("Dallas");
	vertex.addVertexList("Chicago");
	vertex.addVertexList("WashingtonDC");
	vertex.addVertexList("Miami");
	vertex.addVertexList("NewYork");
	vertex.addVertexList("Boston");

	EdgeList graph;
	// Adding edges with their distances between each cities
	graph.addEdge("Minneapolis", "Chicago", 661);
	graph.addEdge("Dallas", "WashingtonDC", 2113);
	graph.addEdge("Dallas", "Miami", 2161);
	graph.addEdge("Chicago", "WashingtonDC", 1145);
	graph.addEdge("Chicago", "Boston", 1613);
	graph.addEdge("Miami", "WashingtonDC", 1709);
	graph.addEdge("Miami", "NewYork", 2145);
	graph.addEdge("WashingtonDC", "NewYork", 383);
	graph.addEdge("WashingtonDC", "Boston", 725);
	graph.addEdge("NewYork", "Boston", 338);
	graph.addEdge("Seattle", "SanFrancisco", 1306);
	graph.addEdge("SanFrancisco", "LosAngeles", 629);
	graph.addEdge("LosAngeles", "LasVegas", 435);
	graph.addEdge("LasVegas", "SanFrancisco", 919);
	graph.addEdge("Seattle", "Denver", 2161);
	graph.addEdge("Seattle", "Minneapolis", 2661);
	graph.addEdge("LasVegas", "Denver", 1225);
	graph.addEdge("LasVegas", "Dallas", 1983);
	graph.addEdge("Denver", "Minneapolis", 1483);
	graph.addEdge("Denver", "Dallas", 1258);
	graph.addEdge("Minneapolis", "Dallas", 1532);
	
	// Print graph edges
	graph.printEdges();

	int count = vertex.getCount();
	cout << "\nVertex count is " << count << endl;
	
	// Inititalize total for MST
	int total{ 0 };
	Edges* lowEdge = nullptr;
	EdgeList minGraph;
	for (int index{ 0 }; index < count; index++) {
		// Set lowEdge equals to lowest edge in graph
		lowEdge = graph.lowestEdge();

		// Add lowest edge to minGraph
		minGraph.addEdge(lowEdge->city1, lowEdge->city2, lowEdge->edgeWeight);
		
		// Total up each edgeWeight
		total += lowEdge->edgeWeight;
		// Remove the lowest edge in order to add new edges to MST
		graph.removeEdge(lowEdge);
	}
	minGraph.printEdgesMin();
	return 0;
}