#include"neuro.hpp"

#include<fstream>
#include<vector>
#include<string>

using namespace std;

void load( string filename, Neuro &neuro );
std::vector<string> parseLine(string line);
