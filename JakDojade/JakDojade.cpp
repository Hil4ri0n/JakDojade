#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include "String.h"
#include "MyVector.h"
#include "HashMap.h"
#include "HashMapPointString.h"
#include "Graph.h"
#include "Queue.h"
#include "PriorityQueue.h"

#define MAXINT 2147483647

struct Location {
    int x, y, distance;
};

struct CityIndex {
    String name;
    int x, y;
};

Point AdjacentLetter(int x, int y, char** plansza, int h, int w);
bool isCityLetter(char znak);
String GetCityName(Point punkt, char** plansza, int width);
void readFlights(String& source, String& destination, int& time);
int shortestPath(String& source, String& destination, MyVector<String>& trasa, Graph& graph);
void BFS(int x, int y, Graph& graph, bool* visited, char** plansza, int width, int height, HashMapPointString& MapXY, String& start);

int main()
{
    int w, h;
    scanf_s("%d", &w);
    scanf_s("%d", &h);
    getchar();
    char** plansza = new char*[h];
    for (int i = 0; i < h; i++) {
        plansza[i] = new char[w];
    }

    MyVector <CityIndex> listaMiast;

    char znak;
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            znak = getchar();
            plansza[i][j] = znak;
            if (znak == '*') {
                CityIndex miasto;
                miasto.x = j;
                miasto.y = i;
                miasto.name = "";
                listaMiast.push_back(miasto);
            }
        }
        getchar();
    }


    Graph graph;
    HashMapPointString MapXY;

    for (int i = 0; i < listaMiast.getSize(); i++) {
        CityIndex miasto = listaMiast.get(i);
        Point punkt = AdjacentLetter(miasto.x, miasto.y, plansza, h, w);
        String nazwaMiasta = GetCityName(punkt, plansza, w);
        miasto.name = nazwaMiasta;
        listaMiast.get(i) = miasto;
        graph.addNewNode(nazwaMiasta);
        MapXY.insertNode({ miasto.x,miasto.y }, miasto.name);
    }


    int k;
    scanf_s("%d", &k);
    getchar();
    String source="";
    String destination="";
    int time;
    for (int i = 0; i < k; i++) {
        readFlights(source, destination, time);
        graph.addAdjNode1Dir(source, destination, time);
        source = "";
        destination = "";
    }
    

    for (int i = 0; i < listaMiast.getSize(); i++) {
        CityIndex miasto = listaMiast.get(i);
        bool* visited = new bool[w * h] {};
        BFS(miasto.x, miasto.y, graph, visited, plansza, w, h,MapXY, miasto.name);
        delete[] visited;
    }

    //graph.printGraph();

    int q;
    scanf_s("%d", &q);
    getchar();
    source = "";
    destination = "";
    int type;
    int distance;
    for (int i = 0; i < q; i++) {
        readFlights(source, destination, type);
        MyVector<String> trasa;
        distance = shortestPath(source, destination, trasa, graph);
        if (type == 1) {
            cout << distance << " ";
            for (int i = trasa.getSize() - 2; i > 0; i--) {
                cout << trasa.get(i) << " ";
            }
            cout << endl;
        }
        else {
            cout << distance << endl;
        }
        source = "";
        destination = "";
    }

    for (int i = 0; i < h; i++) {
        delete[] plansza[i];
    }
    delete[] plansza;
}

int shortestPath(String& source, String& destination, MyVector<String>& trasa, Graph& graph) {
    int n = graph.numberOfNodes();
    int src = graph.getNodeIndex(source);
    int* costTable = new int[n];
    int* poprzednicy = new int[n];
    for (int i = 0; i < n; i++) {
        costTable[i] = MAXINT;
        poprzednicy[i] = -1;
    }
    PriorityQueue pq;
    costTable[src] = 0;
    pq.push({ 0, src });

    while (!pq.empty()) {
        int u = pq.top().second;
        int d = pq.top().first;
        pq.pop();

        if (d > costTable[u]) continue;

        for (int i = 0; i < graph.Nodes.get(u).adjList.getSize(); i++) {
            adjNode currentNode = graph.Nodes.get(u).adjList.get(i);
            
            int v = graph.getNodeIndex(currentNode.value);
            int w = currentNode.cost;

            if (costTable[u] + w < costTable[v]) {
                costTable[v] = costTable[u] + w;
                pq.push({ costTable[v], v });
                poprzednicy[v] = u;
            }
        }
    }

    int destinationIndex = graph.getNodeIndex(destination);

    int current = destinationIndex;
    while (current != -1) {
        trasa.push_back(graph.Nodes.get(current).value);
        current = poprzednicy[current];
    }

    int returnValue = costTable[destinationIndex];

    delete[] costTable;

    return returnValue;
}

void readFlights(String& source, String& destination, int& time) {
    char buffer[100];
    fgets(buffer, 100, stdin);
    char* token = strtok(buffer, " ");
    source = token;
    token = strtok(NULL, " ");
    destination = token;
    token = strtok(NULL, " ");
    String timeStr = token;
    time = timeStr.to_int();
}

bool isCityLetter(char znak) {
    return ((znak >= 65 && znak <= 90) || (znak >= 48 && znak <= 57));
}

String GetCityName(Point punkt, char** plansza, int width) {
    int x = punkt.x;
    while (x >= 0 && isCityLetter(plansza[punkt.y][x]) ) {
        x--;
    }
    x++;
    String nazwaMiasta = "";
    while (x < width && isCityLetter(plansza[punkt.y][x])) {
        nazwaMiasta = nazwaMiasta + plansza[punkt.y][x];
        x++;
    }
    return nazwaMiasta;
}

Point AdjacentLetter(int x, int y, char** plansza, int h, int w) {
    if (x - 1 >= 0) {
        if (isCityLetter(plansza[y][x - 1])) {
            return { x - 1, y };
        }
        else if (y + 1 < h && isCityLetter(plansza[y + 1][x - 1])) {
            return { x - 1, y + 1 };
        }
        else if (y - 1 >= 0 && isCityLetter(plansza[y - 1][x - 1])) {
            return { x - 1, y - 1 };
        }
    }
    if (x + 1 < w) {
        if (isCityLetter(plansza[y][x + 1])) {
            return { x + 1, y };
        }
        else if (y + 1 < h && isCityLetter(plansza[y + 1][x + 1])) {
            return { x + 1, y + 1 };
        }
        else if (y - 1 >= 0 && isCityLetter(plansza[y - 1][x + 1])) {
            return { x + 1, y - 1 };
        }
    }
    if (y - 1 >= 0) {
        if (isCityLetter(plansza[y - 1][x])) {
            return { x, y - 1};
        }
    }
    if (y + 1 < h) {
        if (isCityLetter(plansza[y + 1][x])) {
            return { x, y + 1};
        }
    }
    return { -1,-1 };
}

void BFS(int x, int y, Graph& graph, bool* visited, char** plansza, int width, int height, HashMapPointString& MapXY, String& start) {
    Location pkt;
    pkt.x = x;
    pkt.y = y;
    pkt.distance = 0;
    Queue<Location> queue;
    queue.enqueue(pkt);
    visited[y * width + x] = true;
    while (!queue.isEmpty()) {
        pkt = queue.dequeue();
            if (plansza[pkt.y][pkt.x] == '*' && (pkt.x != x || pkt.y != y)){
                String nazwaMiasta = MapXY.get({ pkt.x,pkt.y });
                graph.addAdjNode1Dir(start, nazwaMiasta, pkt.distance);
            }
            else {
                if (pkt.x + 1 < width && (plansza[pkt.y][pkt.x + 1] == '#' || plansza[pkt.y][pkt.x + 1] == '*') 
                    && visited[pkt.y * width + pkt.x + 1] != true) {
                    queue.enqueue({ pkt.x + 1, pkt.y, pkt.distance + 1 });
                    visited[pkt.y * width + pkt.x + 1] = true;
                }
                if (pkt.x - 1 >= 0 && (plansza[pkt.y][pkt.x - 1] == '#' || plansza[pkt.y][pkt.x - 1] == '*') && visited[pkt.y * width + pkt.x - 1] != true) {
                    queue.enqueue({ pkt.x - 1, pkt.y, pkt.distance + 1 });
                    visited[pkt.y * width + pkt.x - 1] = true;
                }
                if (pkt.y + 1 < height && (plansza[pkt.y + 1][pkt.x] == '#' || plansza[pkt.y + 1][pkt.x] == '*') && visited[(pkt.y + 1) * width + pkt.x] != true) {
                    queue.enqueue({ pkt.x, pkt.y + 1, pkt.distance + 1 });
                    visited[(pkt.y + 1) * width + pkt.x] = true;
                }
                if (pkt.y - 1 >= 0 && (plansza[pkt.y - 1][pkt.x] == '#' || plansza[pkt.y - 1][pkt.x] == '*') && visited[(pkt.y - 1) * width + pkt.x] != true) {
                    queue.enqueue({ pkt.x, pkt.y - 1, pkt.distance + 1 });
                    visited[(pkt.y - 1) * width + pkt.x] = true;
                }
            }
    }
}