#include<iostream>

#include"mlp.hpp"
#include"descriptor.hpp"

using namespace std;

int main() {
	int lsz[] = {1024, 48, 26, 1};
	int lN = sizeof(lsz) / sizeof(int);
	MLP mlp(lN, lsz); // создать персептрон с заданными размерами
	
	Descriptor desc(mlp);
	desc.load("cross_conf");
	
	vector<vector<flt> > theory; // шаблоны, с которыми будет сравниваться выход нейросети
	vector<flt> th; // шаблон, который означает, что обнаружен крест
	th.push_back(1);
	theory.push_back(th); // множество шаблонов в этом состоит из одного шаблона - креста
	
	vector<string> names; // множество имен объектов, чтобы подписывать их на картинке
	names.push_back("cross");
	
	desc.processVideo("example3.avi", "examlpe3_out.avi", theory, names);
}
