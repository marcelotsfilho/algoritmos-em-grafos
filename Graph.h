#include <iostream>
#include <vector>
#include <list>
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <stack>
#include <queue>

using namespace std;

/**
 * @struct Edge
 * @brief Representa uma aresta em um grafo não direcionado.
 */
struct Edge{
    // A estrutura aresta armazena dois vértices e um peso (opcional), onde o peso padrão é 0.0 e indica uma aresta não ponderada.
    // Caso um grafo seja ponderado, o peso pode ser utilizado para representar o custo ou a distância entre os vétices.
    // Nesse caso, v e w são vértices diferentes conectados por essa aresta.
    int v, w;

    // Nesse caso, é realizado a inicialização dos vértices v e w com -1, indicando que a aresta não está conectada a nenhum vértice.
    Edge(int v = -1, int w = -1, double weight = 0.0) : v(v), w(w) {}

    // A condicional verifica se o vértice fornecido é igual a um dos vértices da aresta (v ou w). Caso seja igual, retorna o vertice oposto.
    int other(int vertex) const{
        if (vertex == v)
            return w;
        if (vertex == w)
            return v;
        // throw é uma instrução que indica que uma exceção foi lançada.
        throw invalid_argument("Vértice inválido na aresta");
    }
};


// CONSTRUÇÃO DO GRAFO

/**
 * @class Graph
 * @brief Representa um grafo não direcionado usando lista de adjacência.
 */
class Graph{
private:
    int V;                  // Número de vértices
    int E;                  // Número de arestas
    vector<list<Edge>> adj; // Lista de adjacência

public:
    // Construtor a partir do número de vértices
    Graph(int V) : V(V), E(0){
        if (V < 0)
            throw invalid_argument("O número de vértices não pode ser negativo");
        // Redimensiona o tamanho do vetor adj para armazenar V listas de adjacência (qtde de vertices que o grafo possui)
        adj.resize(V);
    }

    // Construtor a partir de um arquivo de entrada
    // O in é um objeto de fluxo de entrada (istream) que pode ser associado a diferentes fontes de dados, como arquivos ou entrada padrão.
    Graph(istream &in){
        if (!in)
            throw invalid_argument("Stream de entrada inválido.");
        in >> V;
        adj.resize(V);

        int totalEdges;
        in >> totalEdges;

        for (int i = 0; i < totalEdges; i++){
            int v, w;
            in >> v >> w;
            addEdge(Edge(v, w));
        }
    }

    void addEdge(Edge e){
        E++;
        int v = e.v;
        int w = e.w;
        adj[v].push_back(e);
        adj[w].push_back(Edge(w, v)); // Adiciona a aresta de volta para grafos não direcionados
    }

    int getV() const { return V; }
    int getE() const { return E; }

    // Retorna todas as arestas do grafo
    vector<Edge> getAllEdges() const{
        vector<Edge> edges;
        for (int v = 0; v < V; ++v){
            for (const auto &edge : adj[v]){
                if (edge.v < edge.w){ // Adiciona cada aresta apenas uma vez
                    edges.push_back(edge);
                }
            }
        }
        return edges;
    }

    // Retorna o grau do vertice v
    list<Edge> getAdj(int v) const{
        if (v < 0 || v >= V)
            throw invalid_argument("Vértice inválido");
        return adj[v];
    }           

    // Mostra o Grafo
    void show(){
        vector<Edge> edges;
        cout << "Grafo com " << V << " vértices e " << E << " arestas." << endl;
        cout << "---------------------------------------------" << endl;
        for (int v = 0; v < V; ++v){
            for (const auto &edge : adj[v]){
                if (edge.v < edge.w){ // Adiciona cada aresta apenas uma vez
                    cout << "  " << v << " -- " << edge.w << "\n";
                }
            }
        }
        cout << "---------------------------------------------" << endl;
    }

    // Mostra o grafo no formato dot
    void showDot(){
        vector<Edge> edges;
        cout << "graph {\n";
        cout << "  node [shape=circle];\n";
        for (int v = 0; v < V; ++v){
            for (const auto &edge : adj[v]){
                if (edge.v < edge.w){ // Adiciona cada aresta apenas uma vez
                    cout << "  " << v << " -- " << edge.w << ";\n";
                }
            }
        }
        cout << "}\n";
    }
};