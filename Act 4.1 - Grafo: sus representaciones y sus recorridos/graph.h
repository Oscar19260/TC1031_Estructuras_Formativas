// graph.h
#ifndef GRAPH_H // include guard
#define GRAPH_H

#include <iostream>
#include <cstring>
#include <fstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

using namespace std;

string show(vector<int>);

// Clase Grafo ///////////////////////////////////////////////////////////////////////////////////////////////////
class Graph{
    private:
        int vertex;
        int edges;
        vector<vector<int>> adjList;
        vector<vector<int>> adjMat;

    public:
        // Constructor de Grafo //////////////////////////////////////////////////////////////////////////////////
        Graph(){}
        void loadGraphMat(string file, int nodos, int arcos);
        string printAdjMat();

        void loadGraphList(string file, int nodos, int arcos);
        string printAdjList();

        string DFS(int x, int z);
        string BFS(int x, int z);
};

// Load Graph List ///////////////////////////////////////////////////////////////////////////////////////////////
void Graph::loadGraphList(string file, int nodos, int arcos){
    vertex = nodos;
    edges = arcos;
    for(int i = 0; i < nodos; i++){   //Creamos la matriz de adjacencia
        vector<int> list;          
        adjList.push_back(list);
    }
    ifstream arch;                  //Leemos el archivo
    arch.open(file);                //Abrimos el archivo
    while(arch.good()){
        string x;
        string y;
        getline(arch, x, ',');      
        getline(arch, y, '\n');
        x = x.substr(1, x.length()-1);  //Obtenemos los datos de la coordenada x
        y = y.substr(1, y.length()-2);  //Obtenemos los datos de la coordenada y
        int u = stoi(x);                //Los convertimos de string a int
        int v = stoi(y);
        // Metemos los datos en el grafo
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }
}

// Load Graph Matrix /////////////////////////////////////////////////////////////////////////////////////////////
void Graph::loadGraphMat(string file, int nodos, int arcos){
    vertex = nodos;
    edges = arcos;
    for(int i = 0; i<nodos; i++){
        vector<int> matrix(nodos, 0);
        adjMat.push_back(matrix);
    }
    ifstream arch;                      //Leemos el archivo
    arch.open(file);                    //Abrimos el archivo
    while(arch.good()){
        string x;
        string y;
        getline(arch, x, ',');
        getline(arch, y, '\n');
        x = x.substr(1, x.length()-1);  //Obtenemos los datos de la coordenada x
        y = y.substr(1, y.length()-2);  //Obtenemos los datos de la coordenada y
        int u = stoi(x);                //Los convertimos de string a int
        int v = stoi(y);
        // Metemos los datos en el grafo
        adjMat[u][v] = 1;
        adjMat[v][u] = 1;
    }
}

// Print Adjacent List ///////////////////////////////////////////////////////////////////////////////////////////
string Graph::printAdjList(){
    string data = "";
	for(int i = 0; i < adjList.size(); i++){
		data += "vertex " + to_string(i) + " : ";
		sort(adjList[i].begin(), adjList[i].end());
		for(int j = 0; j < adjList[i].size(); j++){
			data += to_string(adjList[i][j]) + " ";
		}
	}
	return data;
}

// Print Adjacent Matrix /////////////////////////////////////////////////////////////////////////////////////////
string Graph::printAdjMat(){
    string data = "";
	for(int i = 0; i < adjMat.size(); i++){
		for(int j = 0; j < adjMat[i].size(); j++){
			data = data + to_string(adjMat[i][j]) + " ";
		}
	}
	return data;
}

// Depth-First Search ////////////////////////////////////////////////////////////////////////////////////////////
string Graph::DFS(int x, int z){
	vector<vector<int>> adjList2;
	for (int i=0; i<adjList.size(); i++){
		adjList2.push_back(adjList[i]);
	}
	vector<int> stack;
	vector<int> visited;
	bool band = false;
	int pos = x;

	while (!band && !(visited.size() >= vertex)){
		bool avisited = false;
		for (int i=0; i<visited.size(); i++){
			if(pos == visited[i]) {
				avisited = true;
				break;
			}
		}
		if (!avisited) visited.push_back(pos);
		if (pos == z){
			band = true;
			break;
		}
		for (int i = 0; i < adjList2[pos].size(); i++){
			for (int j = 0; j < visited.size(); j++){
				if(adjList2[pos][i] == visited[j])
					adjList2[pos].erase(adjList2[pos].begin()+i);
			}
		}
		if (adjList2[pos].size() > 0){
			stack.push_back(pos);
			int temp_index = pos;
			pos = adjList2[pos].back();
			adjList2[temp_index].pop_back();
		} 
		else {
			pos = stack[stack.size()-1];
			stack.pop_back();
		}
	}
	stack.push_back(pos);
	string svisited = show(visited);
	string spath = show(stack);
	string data = "visited: " + svisited + "path: " + spath;
	data = data.substr(0, data.size()-1);
	return data;
}

// Breadth-First Search //////////////////////////////////////////////////////////////////////////////////////////
string Graph::BFS(int x, int z){
    vector<vector<int>> queue;
	vector<vector<int>> visited;
	int pos = x;
	int parent = -1;
	bool band = false;

	while (true){
		visited.push_back(vector<int>({parent, pos}));
		if (pos == z){
			band = true;
			break;
		}
		for (int i=0; i < adjList[pos].size(); i++){
			int val = adjList[pos][i];
			bool avisited = false;
			for (int j = 0; j<visited.size(); j++){
				if (visited[j][1] == val){
					avisited = true;
					break;
				}
			}
			if (!avisited) queue.push_back(vector<int>({pos, val}));
		}
		parent = queue[0][0];
		pos = queue[0][1];
		queue.erase(queue.begin());
	}
	vector<int> path;
	int find = z;
	do {
		for (int i=0; i < visited.size(); i++){
			if (visited[i][1] == find){
				path.insert(path.begin(), find);
				find = visited[i][0];
			}
		}
	} while (find != -1);
	vector<int> converted_visited;
	for (int i=0; i<visited.size(); i++){
		converted_visited.push_back(visited[i][1]);
	}
	string svisited = show(converted_visited);
	string spath = show(path);
	string data = "visited: " + svisited + "path: " + spath;
	data = data.substr(0, data.size()-1);
	return data;
}

// Show Vector ///////////////////////////////////////////////////////////////////////////////////////////////////
string show(vector<int> v){
	string data = "";
	for (int i = 0; i < v.size(); i++){
		data = data + to_string(v[i]) + " ";
	}
	return data;
}

// Fin de la transmición /////////////////////////////////////////////////////////////////////////////////////////
#endif /* GRAPH_H */