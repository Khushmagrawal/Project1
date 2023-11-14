/*Dijkstra’s algorithm is implemented in the repository for 200 randomly selected source-destination pairs on the Florida graph and total
time elapsed for this whole process was calculated.The Graph of Florida is provided in DIMACS Format, The Dijsktra Alogrithm is an 
algorithm is used to calculate the shortest distance between souce and destination. */
#include <iostream>
#include <vector>
#include <string>
#include <set>
#include "dijkstra.cpp"
#include<chrono>



  #include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct Edge {
    int u, v, w;
};

std::vector<Edge> loadGraphFromDIMACS(const std::string& filename) {
    std::ifstream file(filename);

    std::string line;
    std::vector<Edge> edges;

    while (std::getline(file, line)) {
        if (line[0] == 'a') {
            int u, v, w;
            sscanf(line.c_str(), "a %d %d %d", &u, &v, &w);
            edges.push_back({u, v, w});
        }
    }

    return edges;
}

int main() {
    vector<Edge> edges = loadGraphFromDIMACS("Data.txt");
   random_device rd;
    mt19937 gen(rd());
    int total,int duration;
    int numNodes = 1070376;
     double total = 0.0;
   
    for (int i = 0; i < 200; i++) {
        // Generate a random source and destination
        int source = std::uniform_int_distribution<int>(0, numNodes - 1)(gen);
        int destination = std::uniform_int_distribution<int>(0, numNodes - 1)(gen);

        
        auto start = std::chrono::high_resolution_clock::now();  // Clock staarts now
        
        dijkstraAlgorithm(graph, source, destination);        // Function is called now
        auto end = std::chrono::high_resolution_clock::now()    //Clock stops now
        std::chrono::auto duration = end - start;
        total = total + duration.count();

        
    }

    return 0;
}
  

   

    

