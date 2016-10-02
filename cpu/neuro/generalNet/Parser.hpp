//
// Created by hokop on 7/30/16.
//

#ifndef GENERALIZEDNET_PARSER_H
#define GENERALIZEDNET_PARSER_H

#include<string>
#include<vector>
#include "Data.hpp"
#include "Layer.hpp"
#include "layers/Network.hpp"
#include "layers/Convolution.hpp"
#include "layers/Subsampling.hpp"
#include "layers/MaxPooling.hpp"

using namespace std;

#define COMMENT '#'

struct Line
{
	Line() {}
	Line(const string str);
	void init(string str);
	vector<string> words;
	Line operator=(string);
	Line operator=(Line);
	string to_str();
	string operator[](int index);
	unsigned long size();
};

struct Block
{
	Block() {}
	Block(Block const &block);
	Block(string filename);
	void init(string filename);
	string what;
	string name;
	vector<Line> lines;
	Line operator[](int index);
	Block operator=(Block);
	void add(Line line);
	unsigned long size();
	string getString(string what);
	int getInt(string what);
};

class Parser
{
public:
	Parser() {}
	
	Network *blockToNetwork(Block &block);
	
	Convolution *blockToConv(Block &block, Network &network);
	MaxPooling *blockToMaxPooling(Block &block, Network &network);
	
	Data blockToData(Block &block);
	
	vector<Block> explodeBlock(Block &);
};

#endif //GENERALIZEDNET_PARSER_H
