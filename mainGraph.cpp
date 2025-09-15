#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <queue>
#include "Graph.h"

using namespace std;

class Process{
private:
    Graph G;

public:
    Process(const Graph &G) : G(G) {}

    // um grafo é completo se todo par de vertices distintos sao adjacentes
    bool isComplete(Graph G){
        int qtdeVertices = G.getV(); // V e o numero de vertices do grafo G
        for(int v = 0; v < qtdeVertices; v++){
            // se o grau do vertice v for diferente de V-1 
            if(degree(v) != qtdeVertices-1){
                return false;
            }
        }
        return true;
    }

    // função que retorna o grau de um vértice
    int degree(int v){
        return G.getAdj(v).size();
    }

    // um grafo é regular se todos os vertices tem o mesmo grau
    bool isRegular(Graph G){
        int qtdeVertices = G.getV(); // V e o numero de vertices do grafo G
        int grau = degree(0); // obtem o grau do primeiro vertice do grafo
        for(int v = 1; v < qtdeVertices; v++){
            // caso o grau do vertice v seja diferente do grau do primeiro vertice, retorna falso
            if(degree(v) != grau){
                return false;
            }
        }
        return true;
    }
    
    // um grafo é euleriano se possui um ciclo que visita todas as arestas exatamente uma unica vez
    // um grafo é euleriano se todos os vertices tem grau par
    bool isEulerian(){
        int qtdeVertices = G.getV();
        for(int v = 0; v < qtdeVertices; v++){
            if(degree(v)%2 != 0){
                return false;
            }
        }
        return true; // Implementar lógica para verificar se o grafo é Euleriano
    }

    bool isEulerianPath(){
        // função que verifica se o grafo possui um caminho euleriano
        
        return true; // Implementar lógica para verificar se o grafo tem um caminho Euleriano
    }

    // um grafo é conexo se existe um caminho entre qualquer par de vertices do grafo
    bool isConnected(Graph G){
        int qtdeVertices = G.getV();
        for(int v = 0; v < qtdeVertices; v++){
            // caso o grau do vertice v seja 0, o grafo nao e conexo
            if(degree(v) == 0){
                return false;
            }
            // percorrendo a lista de adjacencia do vertice v para descobrir se existe algum vertice isolado
            
        }
        return true; // Implementar lógica para verificar se o grafo é conexo
    }

    bool isBipartite(){
        // deve-se utilizar a busca em largura para colorir os vertices do grafo com duas cores diferentes (0 e 1)

        return true; // Implementar lógica para verificar se o grafo é bipartido
    }

    bool isPlanar(){
        return true; // Implesize()mentar lógica para verificar se o grafo é planar
    }

    // TODO: Implementar para a proxima aula
    // um grafo é ciclico se possui pelo menos um ciclo (vertice inicial é igual ao vertice final)
    // utilizar busca em profundidade ja que tem a recursividade para tentar voltar ao vertice inicial
    bool isCyclic(){

        return true; // Implementar lógica para verificar se o grafo contém ciclos
    }

    // função de busca em profundidade. utiliza recursão para explorar o grafo, marcando os vértices visitados
    class depthFirstPaths{
    private:
        vector<bool> marked; // marcado[v] = existe um caminho de s para v?
        vector<int> edgeTo;  // edgeTo[v] = último vértice no caminho de s para v
        const Graph &G;      // referência ao grafo
        int source;          // vértice de origem

        void dfs(int v){
            marked[v] = true;
            for (const Edge &e : G.getAdj(v)){ // Itera sobre as arestas adjacentes
                int w = e.other(v);
                if (!marked[w]){
                    edgeTo[w] = v;
                    dfs(w);
                }
            }
        }

    public:
        depthFirstPaths(const Graph &G, int s) : G(G), source(s)
        {
            marked.resize(G.getV(), false);
            edgeTo.resize(G.getV(), -1);
            dfs(s);
        }

        bool hasPathTo(int v) const
        {
            return marked[v];
        }

        stack<int> pathTo(int v) const
        {
            stack<int> path;
            if (!hasPathTo(v))
                return path; // Retorna pilha vazia

            for (int x = v; x != source; x = edgeTo[x])
            {
                path.push(x);
            }
            path.push(source); // Adiciona o vértice de origem
            return path;
        }
    };

    class breadthFirstPaths
    {
    private:
        vector<bool> marked; // marcado[v] = existe um caminho de s para v?
        vector<int> edgeTo;  // edgeTo[v] = último vértice no caminho de s para v
        vector<int> distTo;  // distTo[v] = distância de s para v
        const Graph &G;      // referência ao grafo
        int source;          // vértice de origem

        void bfs(int s)
        {
            queue<int> q;
            marked[s] = true;
            distTo[s] = 0;
            q.push(s);

            while (!q.empty())
            {
                int v = q.front();
                q.pop();

                for (const Edge &e : G.getAdj(v))
                {
                    int w = e.other(v);
                    if (!marked[w])
                    {
                        edgeTo[w] = v;
                        distTo[w] = distTo[v] + 1;
                        marked[w] = true;
                        q.push(w);
                    }
                }
            }
        }

    public:
        breadthFirstPaths(const Graph &G, int s) : G(G), source(s)
        {
            marked.resize(G.getV(), false);
            edgeTo.resize(G.getV(), -1);
            distTo.resize(G.getV(), 99999);
            bfs(s);
        }

        bool hasPathTo(int v) const
        {
            return marked[v];
        }

        int distanceTo(int v) const
        {
            return distTo[v];
        }

        stack<int> pathTo(int v) const
        {
            stack<int> path;
            if (!hasPathTo(v))
                return path; // Retorna pilha vazia

            for (int x = v; x != source; x = edgeTo[x])
            {
                path.push(x);
            }
            path.push(source); // Adiciona o vértice de origem
            return path;
        }
    };

    class ConnectedComponents
    {
    private:
        vector<bool> marked; // marcado[v] = componente conectada de v?
        vector<int> id;      // id[v] = id da componente conectada de v
        int count;           // número de componentes conectadas
        const Graph &G;

        void dfs(int v, int componentId)
        {
            marked[v] = true;
            id[v] = componentId;
            for (const Edge &e : G.getAdj(v))
            {
                int w = e.other(v);
                if (!marked[w])
                {
                    dfs(w, componentId);
                }
            }
        }

    public:
        ConnectedComponents(const Graph &G) : G(G), count(0)
        {
            marked.resize(G.getV(), false);
            id.resize(G.getV(), -1);

            for (int v = 0; v < G.getV(); v++)
            {
                if (!marked[v])
                {
                    dfs(v, count);
                    count++;
                }
            }
        }

        int getCount() const { return count; }
        int getId(int v) const { return id[v]; }
        bool connected(int v, int w){
            return getId(v) == getId(w);
        }
    };
};

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        cerr << "Uso: " << argv[0] << " <arquivo_do_grafo>" << endl;
        return 1;
    }

    ifstream in(argv[1]);
    if (!in)
    {
        cerr << "Erro ao abrir o arquivo: " << argv[1] << endl;
        return 1;
    }

    // Cria o grafo a partir do arquivo
    Graph G(in);

    G.show();
    G.showDot();
    // Cria o objeto Process que executa as operações no grafo
    Process graph(G);

    cout << "Euleriano: " << graph.isEulerian() << endl;
    cout << "Caminho Euleriano: " << graph.isEulerianPath() << endl;
    cout << "Conexo: " << graph.isConnected(G) << endl;
    cout << "Bipartido: " << graph.isBipartite() << endl;
    cout << "Planar: " << graph.isPlanar() << endl;
    cout << "Cíclico: " << graph.isCyclic() << endl;
    cout << "Completo: " << graph.isComplete(G) << endl;
    cout << "Regular: " << graph.isRegular(G) << endl;

    Process::ConnectedComponents cc(G);
    cout << "Número de componentes conectados: " << cc.getCount() << endl;
    for(int v = 0; v < G.getV(); v++){
        cout << "Vertice: " << v << ", Componente: " << cc.getId(v) << endl;
    }
    cout << "Vertices 0 e 6 são conectados? " << cc.connected(0, 6) << endl;

    Process::depthFirstPaths dfs(G, 0); // Inicia a busca em profundidade a partir do vértice 0
    cout << " ------- DFS -------" << endl;
    for (int v = 0; v < G.getV(); v++)
    {
        if (dfs.hasPathTo(v))
        {
            stack<int> path = dfs.pathTo(v);
            cout << "Caminho de 0 para " << v << ": ";
            while (!path.empty())
            {
                cout << path.top() << " ";
                path.pop();
            }
            cout << endl;
        }
        else
        {
            cout << "Não há caminho de 0 para " << v << endl;
        }
    }

    Process::breadthFirstPaths bfs(G, 0); // Inicia a busca em largura a partir do vértice 0
    cout << " ------- BFS -------" << endl;

    for (int v = 0; v < G.getV(); v++)
    {
        if (bfs.hasPathTo(v))
        {
            stack<int> path = bfs.pathTo(v);
            cout << "Caminho de 0 para " << v << ": " << "Distância: " << bfs.distanceTo(v) << " - ";
            while (!path.empty())
            {
                cout << path.top() << " ";
                path.pop();
            }
            cout << endl;
        }
        else
        {
            cout << "Não há caminho de 0 para " << v << endl;
        }
    }

    return 0;
}