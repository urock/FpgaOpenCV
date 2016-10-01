#include <iostream>
#include "layers/Network.hpp"
#include "Parser.hpp"
#include "Teacher.hpp"
#include "Converter.hpp"

int main() {
//	Parser parser;
//	Block crossConf = Block("data/cross.conf");
//	Network network = parser.blockToNetwork(crossConf);
//
//	Converter converter;
//	vector<string> names;
//	names.push_back("cross");
//	vector<Data> in, out;
//	converter.loadTask("data/", names, in, out);
//
//	Teacher teacher;
//	teacher.writeWeights(network, "data/crossInit.dat");
//	teacher.teach(network, in, out, 1e3, "data/errors.txt");
//
//	teacher.writeWeights(network, "data/crossTeached.dat");
	
	Layer l = *(new Convolution());
	Data dendrite, axon;
	l.setData(dendrite, axon);
	
	return 0;
}