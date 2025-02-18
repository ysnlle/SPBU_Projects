#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Block {//структура блока
	int data;//значение
	Block* next;//сылка на следующий

	Block() { next = nullptr; }
	Block(int v) { data = v; next = nullptr; }

};

class ChainList {
	friend class Heap;//обьявим Heap дружественным
private:
	Block* first;//первый блок
	int size;//размер

	void AddToChain(int newdata) {//функция добавляения в односвязный список
		Block* new_block;
		new_block = new Block(newdata);//создаем блок значение которого равна newdata

		if (first == nullptr) {
			first = new_block; // если первый элемент пустой, то новый блок становится первым элементом

		}
		else { // в противном случае будем бегать по списку пока не упремся в пустоту, затем добавим в список
			Block* temp = first;
			while (temp->next != nullptr)
				temp = temp->next;
			temp->next = new_block;
		}


	}
	void Merge(int* arr, int* buffer, int l, int r) {//сортировка слиянием
		if (l < r) {
			int m = (l + r) / 2;
			Merge(arr, buffer, l, m);
			Merge(arr, buffer, m + 1, r);

			int k = l;
			for (int i = l, j = m + 1; i <= m || j <= r; ) {
				if (j > r || (i <= m && arr[i] < arr[j])) {
					buffer[k] = arr[i];
					++i;
				}
				else {
					buffer[k] = arr[j];
					++j;
				}
				++k;
			}
			for (int i = l; i <= r; ++i) {
				arr[i] = buffer[i];
			}
		}
	}




public:
	ChainList() {
		size = 0;
		first = nullptr;

	}

	ChainList(int p, int* arr) {
		size = p;
		int* buff = new int[p];

		Merge(arr, buff, 0, p - 1);//сначала сортируем данный список

		for (int i = 0; i < p; ++i) {
			AddToChain(arr[i]);//потом добавляем в список, получаем отсортированный список
		}
	}



	void Add(int newvalue) {//функция добавляет новый элемент в список, причем сразу сортируя его
		Block* newblock = new Block(newvalue);

		if (first == nullptr || newvalue < first->data) {//если нет первого или новый элемент меньше первого
			newblock->next = first;//то первым элементов ставим наш новый элемент
			first = newblock;

		}
		else {//иначе бегаем по списку пока не найдем момент когда новый элемент не будет меньше следующего
			Block* temp = first;
			while (temp->next != nullptr && temp->next->data < newvalue)
				temp = temp->next;

			newblock->next = temp->next;
			temp->next = newblock;

		}
		++size;
	}

	void Add(int* values, int p) {//функция добавляет массив в список, и сразу сортирует его
		int* buff = new int[p];
		Merge(values, buff, 0, p - 1);//сразу сортируем его

		for (int i = 0; i < p; ++i) {//дальше берем каждый жлемент и вставляем его
			Block* newblock = new Block(values[i]);

			if (first == nullptr || values[i] < first->data) {
				newblock->next = first;
				first = newblock;

			}
			else {
				Block* temp = first;
				while (temp->next != nullptr && temp->next->data < values[i])
					temp = temp->next;

				newblock->next = temp->next;
				temp->next = newblock;

			}

		}

		size += p;
	}

	Block* TakeEl(int p) {//выбираем p-тый элемент
		
		Block* temp = first;
		for (int i = 0; i < p; ++i) {
			temp = temp->next;
		}
		return temp;
	}

	void Print() {//функция вывода
		Block* out = first;
		cout << out->data << " ";

		while (out->next != nullptr) {
			out = out->next;
			cout << out->data << " ";
		}
		cout << endl;

	}
};


struct Node {
	int val;
	Node* left, * right;

	Node(int v) { val = v; left = nullptr; right = nullptr; }
};

class Heap {
	friend class ChainList;
private:
	Node* root;

public:
	Heap() : root(nullptr) {}

	Node* BuildTreeHelp(int i, vector<int> tree) {
		if (i > tree.size() - 1) return nullptr;

		Node* newNode = new Node(tree[i]);

		int l = 2 * i + 1, r = 2 * i + 2;
		newNode->left = BuildTreeHelp(l, tree);
		newNode->right = BuildTreeHelp(r, tree);

		return newNode;

	}

	void BuildTree(ChainList list) {
		vector<int> tree;
		Block* temp = list.first;
		while(temp != nullptr) {
			tree.push_back(temp->data);
			temp = temp->next;
		}

		root = BuildTreeHelp(0, tree);
	}

	void BFS() {
		if (root == nullptr) {
			return;
		}
		queue<Node*> q;
		q.push(root);

		while (!q.empty()) {
			Node* curr = q.front();
			cout << curr->val << " ";

			if (curr->left != nullptr) {
				q.push(curr->left);
			}
			if (curr->right != nullptr) {
				q.push(curr->right);
			}
			q.pop();
		}
	}
};

/*
class Heap {//класс дерева
	friend class ChainList;//односв список --  друг
	friend void swap(int&, int&);//свап --  друг
private:
	vector<int> tree;

	void HeapifyRec(int i) {//вспомогательная функция упорядочивания кучи
		int root = i;//корнем ставим i-тый элемент
		int l = 2 * i + 1, r = 2 * i + 2;//выбиарем правый и левый элемент нашего корня

		if (l < tree.size() && tree[l] < tree[root]) root = l;//если левый элемент меньше корня то корнем становится левый элемент
		if (r < tree.size() && tree[r] < tree[root]) root = r;//анологично для правого

		if (i != root) {
			swap(tree[i], tree[root]);//если i-тый элемент не остался корнем то меняем их местами
			HeapifyRec(root);//и продолжаем рекурсию

		}
	}
public:
	Heap(ChainList list) {//конструктор
		for (int i = 0; i < list.size; ++i)//пушим в конец i-тый элемент списка
			tree.push_back(list.TakeEl(i)->data);
	}//в итоге мы получим бинарную кучу

	               //далее реализовал несколько функций

	void Add(int num) {//функция добавления
		tree.push_back(num);//сначала пушим в конец
		int i = tree.size() - 1;//далее определяем какой это элемент
		int parent = (i - 1) / 2;//определяем его родителя

		while (i > 0 && tree[parent] > tree[i]) {//дальше будем свапать элементы дерева пока она не станет бинарной кучей
			if (tree[parent] >= tree[i]) {
				swap(tree[parent], tree[i]);
				i = parent;
				parent = (parent - 1) / 2;
			}

		}
	}

	void Heapify() {//функций упорядочивания кучи
		for (int j = tree.size() / 2 - 1; j >= 0; --j) {
			HeapifyRec(j);
		}
	}

	void Print() {//функция вывода
		for (int i = 0; i < tree.size(); ++i) {
			cout << tree[i]<<" ";
		}
	};

};
*/
void swap(int& a, int& b) { //свап
	int temp = b;
	b = a;
	a = temp;
}

int main() {
	//пример
	int p[5] = { 0,2,4,6,8 };
	ChainList A(5, p);

	int a[4] = { 1,3,5,7 };
	cout << "Chain List: ";
	A.Add(a, 4);
	A.Print();
	cout << endl;
	
	cout << "Binary tree: ";
	Heap tree;
	tree.BuildTree(A);
	tree.BFS();


}