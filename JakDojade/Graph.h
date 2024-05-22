#pragma once
#include "MyVector.h"
#include "String.h"
#include "HashMap.h"

struct adjNode {
	String value;
	int cost;
};
struct Node {
	String value;
	MyVector <adjNode> adjList;
};

class Graph {
public:
	
	
	MyVector<Node> Nodes;
	HashMap MainHashMap;

	void addNewNode(const String& value);
	bool addAdjNode1Dir(const String& first, const String& second, int secondCost);
	int numberOfNodes();
	void printGraph();
	int getNodeIndex(const String& name);
};