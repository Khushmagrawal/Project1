#include <iostream>
#include <vector>
#include <string>
#include <set>
#include "dijkstra.cpp"



  #include <iostream>
#include <fstream>
#include <vector>

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
    std::vector<Edge> edges = loadGraphFromDIMACS("Data.txt");
    std::random_device rd;
    std::mt19937 gen(rd());
    int total,int duration;
    int numNodes = 1070376
    // Loop for 200 random source-destination pairs
    for (int i = 0; i < 200; i++) {
        // Generate a random source and destination
        int source = std::uniform_int_distribution<int>(0, numNodes - 1)(gen);
        int destination = std::uniform_int_distribution<int>(0, numNodes - 1)(gen);

        // Call Dijkstra's algorithm from the repository with the generated source and destination
        auto start = std::chrono::high_resolution_clock::now();
        // Assuming dijkstra algorithm function is called dijkstraAlgorithm
        dijkstraAlgorithm(graph, source, destination);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;
        total = total+duration;

        
    }

    return 0;
}
  

   

    return 0;
}

