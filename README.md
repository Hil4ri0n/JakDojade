# Jak Dojade

## Description
Jak Dojade is a C++ console application designed to simulate navigating between cities on a grid map. The program reads a map, identifies cities and paths, and calculates the shortest path between cities using a graph representation. The application supports multiple queries and operations such as reading flight connections, computing shortest paths, and printing routes.

## Features
- **Map Parsing**: Reads a grid map from input and identifies city locations.
- **Graph Representation**: Uses a graph to represent cities and their connections.
- **Shortest Path Calculation**: Calculates the shortest path between cities using Dijkstra's algorithm.
- **BFS Path Finding**: Uses Breadth-First Search (BFS) to find paths between cities on the map.
- **Custom Data Structures**: Utilizes custom vector, hash map, and graph implementations.
- **Flight Connections**: Reads and stores direct flight connections between cities.
- **Query Handling**: Supports various queries to find routes and distances.

## How to Use
1. **Start the Program**: Run the program and provide the map dimensions and the map itself.
2. **Input Map**: The map consists of a grid where `*` represents a city and letters represent city names.
3. **Input Flights**: Provide the number of flights and the direct connections between cities.
4. **Query Paths**: Enter queries to find the shortest path between cities and print the results.

### Input Format
1. **Map Dimensions**: Enter the width and height of the map.
2. **Map**: Enter the grid representation of the map.
3. **Flights**: Enter the number of direct flight connections followed by the flight details.
4. **Queries**: Enter the number of queries followed by the queries to find paths.

### Example
```plaintext
5 5
.....
.*A..
.....
.B*..
.....
3
A B 5
B C 10
A C 15
2
A C 1
B A 0
