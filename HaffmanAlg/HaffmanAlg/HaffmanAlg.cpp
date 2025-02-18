/*
0. Table of freqmuents:
	A - 57
	B - 45
	C - 34
	D - 24
1. Складываем минимальный узлы: 1. C + D = 58(CD)
								2. A + B = 102(AB)
								3. AB + CD = 160(ABCD)
2. Строим дерево; в сторону где число получилось больше ставим -- 0, где меньше -- 1.
*/	

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>

using namespace std;


//структура Block содержит в себе символ, количество символов и указатели на правый и левый блок
//подумал, что будет полезен для бинарного дерева.
struct Block {
	char symb;
	int count;
	Block* left; Block* right;

	Block(char s, int c) {//конструктор без указателей
		symb = s; count = c; 
		left = nullptr; right = nullptr;
	}

	Block(int c, Block* l, Block* r) {//конструктор с указателями
		count = c;
		left = l; right = r;
	}

};

class Tree {
public:
	vector<Block*> tree;
	string text;

	void swap(Block*& a, Block*& b) {//обычный свап
		Block* temp = a;
		a = b;
		b = temp;
	}

	void sort() {//пузырек
		for (int i = 0; i < tree.size() - 1; ++i) {
			for (int j = 0; j < tree.size() - i - 1; j++) {
				if (tree[j]->count > tree[j + 1]->count) swap(tree[j], tree[j + 1]);

			}
		}
	}

	void bin_codes(Block* root, string code, map<char, string>& b_codes) {//кодировщик
		if (!root) return;//если дошли до низа выходим

		if (!root->left && !root->right) b_codes[root->symb] = code;//если нет вершин ниже то сохраняем код

		//рекурсивно скускаемся до низа, формируя коды
		bin_codes(root->left, code + "0", b_codes);
		bin_codes(root->right, code + "1", b_codes);
	}

	string decoder(Block* root, string ciphert) {//декодер
		string decode = "";
		Block* curr = root;

		//смотрим элемент шифрованного текста, если 0, то спускаемся налево, иначе направо
		//так пока не дойдем до низу, полученный элемент пушим в текст
		for (char symb : ciphert) {
			if (symb == '0') { curr = curr->left; }
			else curr = curr->right;

			if (!curr->left && !curr->right) {
				decode += curr->symb;
				curr = root;
			}
		}

		return decode;
	}

public:
	Tree(map<char, int> c_symb, string t) {//конструктор дерева; состоит из блоков
		for (auto& pair : c_symb) tree.push_back(new Block(pair.first, pair.second)); text = t;

	}

	//алгоритм Хоффмана(или Хаффмана) *_* *_* *_*
	void Haffman() {
		while (tree.size() > 1) {//пробегаемся пока размер дерева не станет 1
			sort();//при этом постоянно сортируем
			
			Block* l = tree[0], * r = tree[1];//выбираем наименьшие элементы
			tree.erase(tree.begin()); tree.erase(tree.begin());//удаляем их из дерева

			Block* co_block = new Block(l->count + r->count, l, r);//создаем новый блок, который включает в себя два удаленных
			tree.push_back(co_block);//добавляем его в конец

		}
	
		Block* root = tree[0]; //дальше берем корень дерева
		map<char, string> b_codes;//создаем пары элементов типа символ - строка, в которой строка будет нашим бинарный кодом
		bin_codes(root, "", b_codes); //дальше используя алгоритм шифровки создаем коды.


		                           //Разные выводы
		                      //пытадся сделать выводы разными функциями но получается очень муторно

		//Бинарные коды
		cout << "Haffman Codes: " << endl;
		for (auto& pair : b_codes) cout << pair.first << ": " << pair.second << endl;
		cout << endl << endl;

		//Кодированный текст
		string ciphertext = "";
		for (char symb : text) ciphertext += b_codes[symb];
		cout << "Ciphertext: \n" << ciphertext << endl<<endl;

		//Раскодированный кодированный текст
		string decoded = decoder(root, ciphertext);
		cout << "Decoded ciphertext: \n" << decoded << endl << endl;
	} 
};

map<char, int> freq(string text) {//количество разных символов
	map<char, int> f;
	for (char symb : text) ++f[symb];

	return f;

}

string input() {//считывает текст с файла
	string text;

	ifstream in("text.txt.txt");
	string line;
	while (getline(in, line)) {
		text += line + "\n";
	}
	in.close();
	return text;
}

int main() {
	string str = input();
	cout << "Text:" << endl;
	cout << str << endl << endl;//выводим текст

	map<char, int> c_symb = freq(str);
	for (auto& item : c_symb) cout << item.first << ": " << item.second << endl;//выводим символы и их количество

	Tree tree(c_symb, str);
	tree.Haffman();

}

