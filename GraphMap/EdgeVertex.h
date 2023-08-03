#ifndef EdgeVertex_h
#define Edgevertex_h
#include <iostream>
#include <climits>
#include <string>
using namespace std;

// Edge class
class Edges {
public:
	string city1;
	string city2;
	int edgeWeight;
	Edges* next;
	Edges* prev;
	Edges();
};

// Edge constructor
Edges::Edges() {
	city1 = "";
	city2 = "";
	edgeWeight = 0;
	next = nullptr;
	prev = nullptr;
}

// Class for list of edges
class EdgeList {
private:
	Edges* head;
	Edges* tail;
	int edgeCount;
public:
	EdgeList();
	Edges* lowestEdge();
	void addEdge(string, string, int);
	void removeEdge(Edges*);
	void printEdges();
	void printEdgesMin();
};

// Edgelist constructor
EdgeList::EdgeList() {
	head = nullptr;
	tail = nullptr;
	edgeCount = 0;
}

// Adding city1 & city2 to each edge with its weight
void EdgeList::addEdge(string city1, string city2, int edge) {
	Edges* newEdge = new Edges();
	// Create and initialize edgePtr to head
	Edges* edgePtr = new Edges();
	edgePtr = head;
	// Create and initialize lastEdge to nullptr
	Edges* lastEdge = new Edges();
	lastEdge = nullptr;

	//////////////////////////////////////////////////////
	// Comparing city string to initialize city1 and city2
	if (city1 < city2) {
		newEdge->city1 = city1;
		newEdge->city2 = city2;
	}
	else {
		newEdge->city1 = city2;
		newEdge->city2 = city1;
	}
	//////////////////////////////////////////////////////

	// Set edge parameter to newEdge weight
	newEdge->edgeWeight = edge;

	// Check if head is null to initialize head/tail
	if (head == nullptr)
	{
		head = newEdge;
		tail = newEdge;
	}
	else
	{
		// Loop until edgePtr reaches the end/nullptr
		while (edgePtr != nullptr)
		{
			// When edgePtr city1 is less than newEdge
			// Set edgePtr equals to edgePtr->next
			// in order to traverse through the edges
			if (edgePtr->city1 < newEdge->city1)
			{
				edgePtr = edgePtr->next;
			}
			else
			{
				break;
			}
		}
		
		// Loop edgePtr until it reaches nullptr
		while (edgePtr != nullptr)
		{
			// If edgePtr->city2 is less than newEdge->city2 while their city1 are equal
			// Set edgePtr equals to edgePtr->next
			if ((edgePtr->city2 < newEdge->city2) && (edgePtr->city1 == newEdge->city1))
			{
				edgePtr = edgePtr->next;
			}
			else
			{
				break;
			}
		}

		// When edgePtr is null, set tail to newEdge accordingly
		if (edgePtr == nullptr)
		{
			tail->next = newEdge;
			newEdge->prev = tail;
			tail = newEdge;
		}
		else
		{
			// When edgePtr equals head set head to newEdge
			if (edgePtr == head)
			{
				newEdge->next = head;
				head->prev = newEdge;
				head = newEdge;
			}
			// Else lastEdge to edgePtr prev in order to link the edges together
			else
			{
				lastEdge = edgePtr->prev;
				edgePtr->prev = newEdge;
				newEdge->prev = lastEdge;
				lastEdge->next = newEdge;
				newEdge->next = edgePtr;
			}
		}
	}
	// Increment edge counts
	edgeCount++;
	return;
}

// Printing graph edges
void EdgeList::printEdges()
{
	// Create and initialize edgePtr to head
	Edges* edgePtr = new Edges();
	edgePtr = head;
	// Create and initialize totalWeight to 0 for summation
	int totalWeight{ 0 };

	cout << "--------------------------"
		<< "\n---Printing graph edges---\n"
		<< "--------------------------\n";

	// Traverse edges with edgePtr until it reaches nullptr
	while (edgePtr != nullptr)
	{
		cout << "Distance between " << edgePtr->city1 << " and " << edgePtr->city2 
			<< " is: " << edgePtr->edgeWeight << " miles" << endl;
		// Totaling the edge weights
		totalWeight += edgePtr->edgeWeight;
		// Move to next edge
		edgePtr = edgePtr->next;
	}
	cout << "\n--------------------------------"
		<< "\n--Total edge weight sum: " << totalWeight << "--\n"
		<< "--------------------------------\n";
	return;
}

// Printing graph edges for minimum spanning tree
void EdgeList::printEdgesMin()
{
	// Create and initialize edgePtr to head
	Edges* edgePtr = new Edges();
	edgePtr = head;
	// Create and initialize totalWeight to 0 for summation
	int totalWeight{ 0 };

	cout << "\n----------------------------------";
	cout << "\n--Printing minimum spanning tree--\n";
	cout << "----------------------------------\n";

	// Traverse edges with edgePtr until it reaches nullptr
	while (edgePtr != nullptr)
	{
		cout << edgePtr->city1 << " to " << edgePtr->city2
			<< " is: " << edgePtr->edgeWeight << " miles" << endl;
		// Totaling each weights
		totalWeight += edgePtr->edgeWeight;
		// Move onto next edge with edgePtr
		edgePtr = edgePtr->next;
	}
	cout << "\n-----------------------------------------------------";
	cout << "\n--Total minimum spanning tree edges is: " << totalWeight << " miles" << "--\n";
	cout << "-----------------------------------------------------\n";
	return;
}

// Removing edges when needed
void EdgeList::removeEdge(Edges* edge)
{
	// Create and initialize next/prev Edge to their respective next/prev
	Edges* nextEdge = new Edges();
	nextEdge = edge->next;
	Edges* prevEdge = new Edges();
	prevEdge = edge->prev;

	// When the edge to be removed is not head nor tail
	if ((edge != head) && (edge != tail))
	{
		nextEdge->prev = prevEdge;
		prevEdge->next = nextEdge;
	}

	// When edge to be removed is head
	if (edge == head)
	{
		nextEdge->prev = nullptr;
		head = nextEdge;
	}

	// When edge to be removed is tail
	if (edge == tail)
	{
		prevEdge->next = nullptr;
		tail = prevEdge;
	}
	edgeCount--;
}

// Finding lowest edge 
Edges* EdgeList::lowestEdge() {
	// Create edgePtr and lowestEdge and initialize to head
	Edges* edgePtr = new Edges();
	edgePtr = head;
	Edges* lowestEdge = new Edges();
	lowestEdge = head;
	
// Create and initialize lowest weight to maximum int
	int lowestWeight = INT_MAX;

	// Traverse until edgePtr reaches nullptr
	while (edgePtr != nullptr)
	{
		// When edgePtr weight is less than lowest weight
		if ((edgePtr->edgeWeight) < lowestWeight)
		{
			// Set lowest weight equals to edgePtr weight 
			// while setting lowest edge equals to edgePtr 
			lowestWeight = edgePtr->edgeWeight;
			lowestEdge = edgePtr;
		}

		// Set edgePtr to edgePtr next to traverse
		edgePtr = edgePtr->next;
	}
	// Return back the lowest edge found
	return lowestEdge;
}

// Vertex class
class Vertex
{
public:
	string place;
	Vertex* next;
	Vertex* prev;
	Vertex();
};

// Vertex constructor
Vertex::Vertex() {
	next = nullptr;
	prev = nullptr;
}

// VertexList class
class VertexList
{
public:
	Vertex* head;
	Vertex* tail;
	VertexList* up;
	VertexList* down;
	int vertexCount;

	VertexList();
	void addVertex(string);
	void printVertexList();
	bool searchList(string);
};

// VertexList constructor
VertexList::VertexList() {
	head = nullptr;
	tail = nullptr;
	up = nullptr;
	down = nullptr;
	vertexCount = 0;
}

// Adding string (city) to each vertices
void VertexList::addVertex(string city) {
	// Create newVertex and initialize its place to city (parameter)
	Vertex* newVertex = new Vertex();
	newVertex->place = city;

	// When head is null set head and tail to newVertex
	if (head == nullptr) {
		head = newVertex;
		tail = newVertex;
	}
	// Else set tail to newVertex
	else {
		tail->next = newVertex;
		newVertex->prev = tail;
		tail = newVertex;
	}
}

// Printing list of vertex 
void VertexList::printVertexList()
{
	// Create and initialize vertexPtr to head
	Vertex* vertexPtr = new Vertex(); 
	vertexPtr = head;

	// Traverse vertexPtr until it reaches nullptr
	while (vertexPtr != nullptr)
	{
		cout << vertexPtr->place << endl;
		// Set vertexPtr to vertexPtr->next
		vertexPtr = vertexPtr->next;
		
	}
}

// Search for vertex in the list and return true if found, false for not found
bool VertexList::searchList(string city)
{
	// Create and initialize vertexPtr to head
	Vertex* vertexPtr = new Vertex();
	vertexPtr =	head;
	while (vertexPtr != nullptr)
	{
		// When vertex is found return true
		if (vertexPtr->place == city)
		{
			return true;
		}
		// Set vertexPtr to vertexPtr->next to traverse
		vertexPtr = vertexPtr->next;
	}
	return false;
}

// VertexDList class / doubly linked list of doubly linked list vertex
class VertexDList
{
private:
	VertexList* listHead;
	VertexList* listTail;
	int vertexListCount;

public:
	void addVertexList(string);
	VertexDList();
	int getCount();
};

// VertexDList constructor
VertexDList::VertexDList() {
	listHead = nullptr;
	listTail = nullptr;
	vertexListCount = 0;
}

// Return total vertex count
int VertexDList::getCount() {
	return this->vertexListCount;
}

// Adding vertices with string city parameter
void VertexDList::addVertexList(string city) {
	// Create and initialize newVertex object of VertexList
	VertexList* newVertex = new VertexList();

	// Add the city into VertexList
	newVertex->addVertex(city);

	// When listHead is nullptr set listHead and listTail to 
	// newVertex
	if (listHead == nullptr) {
		listHead = newVertex;
		listTail = newVertex;
	}
	// Else set listTail to newVertex accordingly
	else {
		listTail->down = newVertex;
		newVertex->up = listTail;
		listTail = newVertex;
	}

	// Increment the vertices count
	vertexListCount++;
}
#endif