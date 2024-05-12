#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// Структура рёбер графа
struct Edge {
    int to;    // Конечная вершина ребра
    int capas; // Пропускная способность ребра
    int flow;  // Поток через ребро

    Edge(int to, int capas) {
        this->to = to;
        this->capas = capas;
        flow = 0;
    }
};

class Graph {
private:
    vector<vector<Edge>> G;   // Граф (список смежности)
    vector<int> d;  // Уровни вершин в слоистой сети
    vector<int> p;  // Указатели вершин

public:
    // Конструктор класса Graph с использованием вспомогательной структуры Edge
    Graph(vector<vector<Edge>> g) {
        G = g;
        d.resize(g.size());
        p.resize(g.size());
    }

    // Обход в ширину для построения уровневой сети
    bool bfs(int s, int t) {
        fill(d.begin(), d.end(), -1);  // Устанавливаем уровни всех вершин в -1
        d[s] = 0; // Уровень истока устанавливаем в 0
        queue<int> q;
        q.push(s);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (const Edge& e : G[u]) {
                if (d[e.to] == -1 && e.flow < e.capas) {  // Проверяем, не посещали ли вершину и доступно ли ребро
                    d[e.to] = d[u] + 1;
                    q.push(e.to);
                }
            }
        }
        return (d[t] != -1);  // Возвращаем true, если сток достижим
    }

    // Поиск блокирующего потока
    int dfs(int u, int minC, int t) {
        if (u == t || minC == 0) {
            return minC;
        }
        for (int& i = p[u]; i < G[u].size(); ++i) {
            Edge& e = G[u][i];
            if (d[e.to] == d[u] + 1 && e.flow < e.capas) {
                int delta = dfs(e.to, min(minC, e.capas - e.flow), t);
                if (delta > 0) {
                    e.flow += delta;
                    // Обратное ребро для сохранения консервации потока
                    for (Edge& backEdge : G[e.to]) {
                        if (backEdge.to == u) {
                            backEdge.flow -= delta;
                            break;
                        }
                    }
                    return delta;
                }
            }
        }
        return 0;
    }

    // Алгоритм Диница для нахождения максимального потока
    int findMaxFlow(int s, int t) {
        int maxFlow = 0;
        while (bfs(s, t)) {
            fill(p.begin(), p.end(), 0);
            int flow;
            while (flow = dfs(s, INT_MAX, t)) {
                maxFlow += flow;
            }
        }
        return maxFlow;
    }
};

int main() {
	vector<vector<Edge>> g = {
		{Edge(1,7),Edge(2,4)}, //0
		{Edge(2,4),Edge(4,2)}, //1
		{Edge(3,4),Edge(4,8)}, //2
		{Edge(5,12)}, //3
		{Edge(3,4),Edge(5,5)}, //4
		{} //5
	};
	Graph G(g);

    cout << G.findMaxFlow(0, 5);
}



