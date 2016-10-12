#include <iostream>
#include "layers/Network.hpp"
#include "Parser.hpp"
#include "Teacher.hpp"
#include "Converter.hpp"
#include "Player.hpp"

int main() {
	clock_t begin = clock();
	
	Parser parser;
	cout << "Loading architecture...\n";
	Block crossConf = Block("data/lenet_adv.conf");
	Network *network = parser.blockToNetwork(crossConf);
	cout << "\tDone.\n";
	
	cout << "Loading task...\n";
	Converter converter;
	vector<string> names;
	names.push_back("cross");
	names.push_back("nothing");
	vector<Data> in, out;
	converter.loadTask_Type1("data/", names, in, out);
	cout << "\tDone.\n";
	
//	cout << "Loading weights...\n";
//	readWeights("data/crossTaught.dat", *network);
//	cout << "\tDone.\n";
	
//	Player player;
//	vector<Data> theory;
//	theory.push_back(indexToData(0,2));
//	theory.push_back(indexToData(1,2));
////	player.processCamera(network, theory, names);
//	player.processVideeo(network, theory, names, "data/cross_test.avi", "data/cross_test_result.avi");
	
	Teacher teacher;
	writeWeights(*network, "data/crossInit.dat");
	cout << "Teaching network...\n";
	teacher.teach(*network, in, out, 1e6, "data/errors.txt");
	cout << "\tDone.\n";

	cout << "Writing results...\n";
	writeWeights(*network, "data/crossTaught.dat");
	cout << "\tDone.\n";

	clock_t end = clock();
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	cout << "Finished in " << elapsed_secs << " seconds";
	
	return 0;
}