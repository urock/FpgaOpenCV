//
// Created by hokop on 7/30/16.
//

#include <fstream>
#include <iostream>
#include "Parser.hpp"

Network *Parser::blockToNetwork(Block &block, Network *sourceNet) {
	string sourceFileName = block.getString("file");
	if (sourceFileName != NO_STRING) {
		if (sourceNet == nullptr)
			throw "no network given";
		Block conf = Block(sourceFileName);
		Network *network = blockToNetwork(conf, sourceNet);
		network->name = block.name;
		Data dendrite = sourceNet->nameToData(block.getString("dendrite"));
		Data axon = sourceNet->nameToData(block.getString("axon"));
		Data eDendrite = sourceNet->nameToErrorData(block.getString("dendrite"));
		Data eAxon = sourceNet->nameToErrorData(block.getString("axon"));
		network->setData(dendrite, axon, eDendrite, eAxon);
		return network;
	}
	
	vector<Block> blocks = explodeBlock(block);
	
	vector<Data> data;
	Data axon, dendrite, eAxon, eDendrite;
	// скопировать все данные из файла
	for (int i = 0; i < blocks.size(); ++i) {
		if (blocks[i].what == "data")
			data.push_back(blockToData(blocks[i]));
		if (blocks[i].what == "axon") {
			axon = blockToData(blocks[i]);
			eAxon = blockToData(blocks[i]);
		}
		if (blocks[i].what == "dendrite") {
			dendrite = blockToData(blocks[i]);
			eDendrite = blockToData(blocks[i]);
		}
	}
	
	//count layers
	int layersN = block.getInt("layers_number");
	
	Network *network = new Network((int) data.size(), layersN, block.name);
	network->setData(dendrite, axon, eDendrite, eAxon);
	for (int i = 0; i < data.size(); ++i) {
		network->data[i] = data[i];
		network->deriv[i] = data[i];
	}
	
	// выделить память для всех карт признаков
	for (int i = 0; i < network->dN; ++i) {
		network->data[i].initMem();
		network->deriv[i].initMem();
	}
	if(sourceNet == nullptr){
		network->axon.initMem();
		network->errAxon.initMem();
		network->dendrite.initMem();
		network->errDend.initMem();
	}
	
	// скопировать все слои из файла
	int lastIndex = 0;
	for(int i = 0; i < blocks.size(); ++i) {
		if(blocks[i].what == "convolution") {
			network->layer[lastIndex] = blockToConv(blocks[i], network);
			++lastIndex;
		}
		if(blocks[i].what == "max_pooling") {
			network->layer[lastIndex] = blockToMaxPooling(blocks[i], network);
			++lastIndex;
		}
		if(blocks[i].what == "network") {
			network->layer[lastIndex] = blockToNetwork(blocks[i], network);
			++lastIndex;
		}
		if(lastIndex > layersN)
			throw "more layers than expected";
	}
	
	// построить последовательность выполнения слоев
	int seqId = -1;
	for(int i = 0; i < blocks.size(); ++i)
		if(blocks[i].what == "sequence")
			seqId = i;
	
	if(seqId == -1)
		throw "sequence not found";
	if(layersN != blocks[seqId].size() )
		throw "error with sequence length";
	
	for(int i = 0; i < blocks[seqId].size(); ++i)
		network->seq[i] = network->nameToLayerId(blocks[seqId][i][0]);
	
	return network;
}

Convolution *Parser::blockToConv(Block &block, Network *sourceNet) {
	int K = block.getInt("kernel");
	int S = block.getInt("stride");
	Convolution *conv = new Convolution(K, S, block.name);
	Data dendrite = sourceNet->nameToData(block.getString("dendrite"));
	Data axon = sourceNet->nameToData(block.getString("axon"));
	Data eDendrite = sourceNet->nameToErrorData(block.getString("dendrite"));
	Data eAxon = sourceNet->nameToErrorData(block.getString("axon"));
	conv->setData(dendrite, axon, eDendrite, eAxon);
	return conv;
}

MaxPooling *Parser::blockToMaxPooling(Block &block, Network *sourceNet) {
	int K = block.getInt("kernel");
	MaxPooling *mp = new MaxPooling(K, block.name);
	Data dendrite = sourceNet->nameToData(block.getString("dendrite"));
	Data axon = sourceNet->nameToData(block.getString("axon"));
	Data eDendrite = sourceNet->nameToErrorData(block.getString("dendrite"));
	Data eAxon = sourceNet->nameToErrorData(block.getString("axon"));
	mp->setData(dendrite, axon, eDendrite, eAxon);
	return mp;
}

Data Parser::blockToData(Block &block) {
	int N = block.getInt("N");
	int M = block.getInt("M");
	return Data(M, N, block.name);
}

vector<Block> Parser::explodeBlock(Block &block) {
	int cPos = 0;
	vector<Block> v;
	Block tmp;
	while(cPos < block.size()) {
		tmp = Block();
		tmp.what = block[cPos][0];
		tmp.name = block[cPos][1];
		++cPos;
		if(block[cPos][0] == "begin") {
			int braces = 1;
			for(++cPos; cPos < block.size(); ++cPos) {
				if(block[cPos][0] == "begin")
					++braces;
				if(block[cPos][0] == "end")
					--braces;
				if(braces == 0)
					break;
				tmp.add(block[cPos]);
			}
			++cPos;
		}
		v.push_back(tmp);
	}
	return v;
}

void Line::init(string str) {
	bool split = true;
	string temp = "";
	words.clear();
	for (unsigned int i = 0; i < str.length(); ++i) {
		char c = str[i];
		#ifdef COMMENT
		if (c == COMMENT)
			break;
		#endif
		if (c == ' ' || c == '\t') {
			if (!split) {
				words.push_back(temp);
				temp = "";
			}
			split = true;
		} else {
			split = false;
			temp += c;
		}
	}
	if (!split)
		words.push_back(temp);
}

Line::Line(const string str) {
	init(str);
}

Line Line::operator=(string str) {
	init(str);
	return *this;
}

Line Line::operator=(Line line) {
	init(line.to_str());
	return *this;
}

string Line::to_str() {
	string str = "";
	int s = (int)size();
	for(int i = 0; i < s; ++i) {
		str += operator[](i);
		if(i < s - 1)
			str += " ";
	}
	return str;
}

unsigned long Line::size() {
	return words.size();
}

string Line::operator[](int index) {
	if(index >= size())
		return "";
	return words[index];
}

Block::Block(Block const &block) {
	what = block.what;
	name = block.name;
	for(int i = 0; i < block.lines.size(); ++i)
		lines.push_back(block.lines[i]);
}

void Block::init(string filename) {
	ifstream f(filename.c_str());
	string str;
	Line line;
	lines.clear();
	
	getline(f, str);
	line = str;
	what = line[0];
	name = line[1];
	
	while(getline(f, str)) {
		line = str;
		if (line.size() != 0)
			add(line);
	}
	
	if(lines[0][0] == "begin") {
		lines.erase(lines.begin());
		lines.erase(lines.end());
	}
	
	f.close();
}

Block::Block(string filename) {
	init(filename);
}

int Block::getInt(string what) {
	return atoi(getString(what).c_str());
}

string Block::getString(string what) {
	int braces = 0;
	for(int i = 0; i < size(); ++i) {
		if (lines[i][0] == "begin")
			++braces;
		if (lines[i][0] == "end")
			--braces;
		if (lines[i][0] == what && braces == 0)
			return lines[i][1];
	}
	return NO_STRING;
}

Block Block::operator=(Block block) {
	what = block.what;
	name = block.name;
	lines.clear();
	for (int i = 0; i < block.size(); ++i)
		add(block[i]);
	return *this;
}

unsigned long Block::size() {
	return lines.size();
}

Line Block::operator[](int index) {
	return lines[index];
}

void Block::add(Line line) {
	lines.push_back(line);
}
