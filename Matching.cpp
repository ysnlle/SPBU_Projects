/*
	1.Паросочетание (англ. matсhing) M в двудольном графе — произвольное множество рёбер двудольного графа такое, что никакие два ребра не имеют общей вершины.

	2.Чередующаяся цепь (англ. alternating path) — путь в двудольном графе, для любых двух соседних рёбер которого верно, что одно из них принадлежит паросочетанию M,а другое нет.

	3.Вершины двудольного графа, инцидентные рёбрам паросочетания M,называются покрытыми (англ. matched), а неинцидентные — свободными (англ. unmatched)

	4.Дополняющая цепь (или увеличивающая цепь) (англ. augmenting path) — чередующаяся цепь, у которой оба конца свободны.

	Теор(Бержа): Паросочетание максимально, ТиТТК не существует дополнителняющих путей

*/

#include <iostream>
#include <vector>
#include <queue>
using namespace std;


class Graph { //класс граф
private:
	vector<vector<int>> G;

	bool BFS(int start, vector<int>& matching, vector<int> used) {//алгоритм поиска в ширину возвращает true когда для какой либо из соседних вершин "cur"та								
		queue<int> q;                                         //еще не найдено наибольшее паросочетание.
		q.push(start);
		used[start] = true;

		while (!q.empty()) {
			int cur = q.front();
			q.pop();
			for (int to : G[cur]) {
				if (!used[to]) {
					if (matching[to] == -1) {
						matching[to] = cur;
						return true;
					}
					used[to] = true;
					if (!used[matching[to]]) {
						q.push(matching[to]);
					}
				}
			}
		}
		return false;
	}
	

public:
	Graph(vector<vector<int>> g) {
		G = g;
	}



	void MaxMatching() { //алгоритм Куна
		vector<int> matching(G.size(), -1);//массив паросочетаний, индекс - вершина паросочетания, значение - максимальное паросочетание
		for (int i = 0; i < G.size(); ++i) {
			vector<int> used(G.size(), false);
			BFS(i, matching, used); // запускаем DFS предварительно "обнуляя" вектор used
		}

		for (int i = 0; i < G.size(); ++i) {
			if (matching[i] != -1) cout << i << " " << matching[i] << endl;;
		}
		cout << endl;
	}

};

int main() {
	vector<vector<int>> g = {
		{5},//0
		{5,6},//1
		{7,8},//2
		{6},//3
		{5,8},//4
		{0,1,4},//5
		{1,3},//6
		{2},//7
		{2,4}//8
	};
	Graph G(g);
	G.MaxMatching();

}
/*
H/W: 0.send results by gift
	 1. Finish Matching
	 2. Определение двудольности
	 3. (2) +(1)
	 4. Ans: which part should work faster?ЫЫ
*/
