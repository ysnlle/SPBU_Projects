#include <iostream>
#include <vector>

using namespace std;
const int INF = 999999999;

//Ребро в графе
struct Edge {
	int to; //куда ведет
	int capas; //пропускная способность
	int flow;//поток по ребру

	Edge(int t, int c) {
		to = t;
		capas = c;
		flow = 0;
	}
};

class Graph { //класс Граф
private:
	vector<vector<Edge>> G;
	vector<bool> visited; //массив посещенных вершин

	int dfs(int at, int t, int min_cap) {
		if (at == t) {
			return min_cap;
		}
		visited[at] = true; //текущая вершина -- посещена
		for (auto& edge : G[at]) { //ребра из текущей вершины
			
			//посещена ли вершина, если нет то смотрим есть ли свободный поток
			if (!visited[edge.to] && edge.capas - edge.flow > 0) {
				int new_flow = min(min_cap, edge.capas - edge.flow);//вычисляем новый поток
				int final_flow = dfs(edge.to, t, new_flow);//ищем путь дальше
				
				if (final_flow > 0) {
					edge.flow += final_flow;
					
					//ищем обратное ребро, чтобы обновить его поток
					for (auto& back_edge : G[edge.to]) {
						if (back_edge.to == at) {
							back_edge.flow -= final_flow;
							break;

						}
					}
					return final_flow;
				}
			}
		}
		return 0;
	}

public:
	Graph(vector<vector<Edge>> g) {
		G = g;
		visited.resize(g.size());

	}
	
	int Ford_Fulkerson(int s, int t) { // алгоритм Форда-Фалкерсона
		int max_flow = 0;
		int new_flow = 0;

		while (true) {
			fill(visited.begin(), visited.end(), false); //обнуляем массив посещенных вершин
			new_flow = dfs(s, t, INF); //ищем увеличивающие пути
			if (new_flow == 0) {
				break; //если не нашли --  выходим
			}
			max_flow += new_flow; // увеличиваем общий поток
		}
		return max_flow;
	}


};



int main() {
	vector<vector<Edge>> g = {
		{Edge(1,7),Edge(2,4)},//0
		{Edge(2,4),Edge(4,2)},//1
		{Edge(3,4),Edge(4,8)},//2
		{Edge(5,12)},//3
		{Edge(3,4),Edge(5,5)},//4
		{},//5
	};
	Graph G(g);

	cout << G.Ford_Fulkerson(0, 5) << endl;

}