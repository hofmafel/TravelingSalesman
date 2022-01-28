#include <iostream>
#include <vector>
#include <iterator>
#include <list>
#include <string>

constexpr auto NUMBEROFNODES = 7;
std::wstring szNodes[NUMBEROFNODES] = { L"Hamburg",L"Berlin", L"Köln", L"Mannheim", L"Düsseldorf", L"Bremen", L"Hannover" };
int choices[NUMBEROFNODES];
int paths;
int getWeight(std::wstring , std::wstring);

class Path {
private:
	std::vector<std::wstring> nodes;
	std::vector<std::wstring> available;
public:
	Path() {
		for (int i = 0; i < NUMBEROFNODES; i++)
			available.push_back(szNodes[i]);
	}
	void add(int index) {
		this->nodes.push_back(this->available.at(index));
		this->available.erase(this->available.begin() + index);
	}
	int weight() {
		int weight = 0;
		int j = 0;
		for (int i = 0; i < NUMBEROFNODES; i++) {
			if (i < NUMBEROFNODES - 1) {
				j = i + 1;
			}
			else {
				j = 0;
			}
			weight += getWeight(this->nodes[i], this->nodes[j]);
		}
		return weight;
	}
	void print() {
		for (const auto& n : nodes) {
			std::wcout << n << L"-";

		}
		std::wcout << nodes[0];
		std::cout << std::endl;
		std::wcout << L"Länge: " << this->weight() << std::endl;
	}
};
class Sequence {
private:
	int index = 0;
	int data[NUMBEROFNODES];
public:
	void add(int number) {
		this->data[this->index] = number;
		index++;
	}
	Path * getPath() {
		Path* path = new Path();
		for(int i = 0; i<NUMBEROFNODES; i++)
		path->add(data[i]);

		return path;
	}
	void print() {
		for(int i = 0; i< NUMBEROFNODES;i++)
		std::cout << data[i];
		std::cout << std::endl;
	}
};


std::list<Sequence *> sequences;
std::list<Path *> pathList;




int weights[NUMBEROFNODES][NUMBEROFNODES] = {
{0, 289, 422, 571, 427, 119, 154},
{289, 0, 569, 631, 572, 377, 282},
{422, 569, 0, 247, 47, 312, 287},
{571, 631, 247, 0, 290, 542, 428},
{427, 572, 47, 290, 0, 317, 292},
{119, 377, 312, 542, 317, 0, 125},
{154, 282, 287, 428, 292, 125, 0}
};

void init() {
	for (int i = 0; i < NUMBEROFNODES; i++)
		choices[i] = NUMBEROFNODES - i;
	
	paths = 1;	
	for (int i = 0; i < NUMBEROFNODES; i++)
		paths *= choices[i];
}
int getIndex(std::wstring szNode) {
	for (int i = 0; i < NUMBEROFNODES; i++)
		if (szNode == szNodes[i])
			return i;
	
	return -1;
}

int getWeight(std::wstring szNode1, std::wstring szNode2) {
	int idx1 = getIndex(szNode1);
	int idx2 = getIndex(szNode2);
	return weights[idx1][idx2];
}

void fillSequences() {
	int choice[NUMBEROFNODES];
	for (int i = 0; i < NUMBEROFNODES; i++)
		choice[i] = 0;
	int k = NUMBEROFNODES - 1;
	Sequence* current;
	int reset = 0;
	for (int i = 0; i <= paths; i++)
	{
		while ( choices[k] - 1 == choice[k] )
		{
			k--;
			if (k < 0) {
				k = NUMBEROFNODES - 1;
				reset++;
				if (reset > NUMBEROFNODES) 
				{
					current = new Sequence();
					for (int j = 0; j < NUMBEROFNODES; j++) {
						current->add(choices[j]-1);
					}
					sequences.push_back(current);
					return;
				}
					
			}			

		}
		current = new Sequence();
		for (int j = 0; j < NUMBEROFNODES; j++) {
			current->add(choice[j]);
		}
		sequences.push_back(current);
		choice[k]++;
		for (int i = k+1; i < NUMBEROFNODES; i++)
			choice[i] = 0;
		k = NUMBEROFNODES - 1;

	}
}
void fillPaths() {
	for (const auto & s : sequences) {
		pathList.push_back(s->getPath());
	}

}


int main() {
	init();
	fillSequences();
	fillPaths();

	std::wcout << L"Anzahl Hamiltonkreise: "<< sequences.size() << std::endl;

	Path* shortestPath = pathList.front();
	for (const auto& p : pathList) {
		if (p->weight() < shortestPath->weight()) {
			shortestPath = p;
		}
	}
	std::wcout << L"Kürzester Pfad:\n";
	shortestPath->print();


}