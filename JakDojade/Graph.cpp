#include "Graph.h"

void Graph::addNewNode(const String& value) {
	Node node;
	node.value = value;
	MainHashMap.insertNode(value, Nodes.getSize());
	Nodes.push_back(node);
}

bool Graph::addAdjNode1Dir(const String& first, const String& second, int secondCost) {

	int index = MainHashMap.get(first);
	if (index != -1) {
		adjNode adj_node;
		adj_node.value = second;
		adj_node.cost = secondCost;
		Nodes.get(index).adjList.push_back(adj_node);
		return true;
	}
	else {
		return false;
	}
}

int Graph::numberOfNodes() {
	return Nodes.getSize();
}

void Graph::printGraph() {
	for (int i = 0; i < Nodes.getSize(); i++) {
		Node node = Nodes.get(i);
		cout << node.value << " --> ";
		for (int j = 0; j < node.adjList.getSize(); j++) {
			cout << node.adjList.get(j).value << " ";
		}
		cout << endl;
	}
}

int Graph::getNodeIndex(const String& name) {
	return MainHashMap.get(name);
}