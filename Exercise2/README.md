Using C++11 new features such as : Smart Pointers, emplace_back function instead push_back , move semantics , STL and lambda functions.

This project consists of a number of different transportation ways such as bus, rail, sprinter and tram.

The project is to implement a public transport network using a graph and compute queries on the graph such as shortest path using Dijkstra's algorithm, DFS to find all the connected possible nodes from a source node, creating the graph transpose etc.

The query uniexpress is the most complicated and a lot of our design was around this query. We are supposed to find the shortest route using all the transportation methods. We created one single graph with all the edges from all the transportation methods, we calculate all the possible paths and find the minimal.

Even though it's and NP problem, the inputs were small enough so the computer can handle it.

Raviv Trichter 204312086
Alon Zemer 305767303