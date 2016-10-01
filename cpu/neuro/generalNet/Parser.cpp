//
// Created by hokop on 7/30/16.
//

#include <fstream>
#include <iostream>
#include "Parser.hpp"

Network Parser::blockToNetwork(Block &block) {
	vector<Block> blocks = explodeBlock(block);
	
	vector<Data> data;
	Data axon, dendrite;
	vector<Layer> layers;
	// скопировать все данные из файла
	for(int i = 0; i < blocks.size(); ++i) {
		if (blocks[i].what == "data")
			data.push_back(blockToData(blocks[i]));
		if(blocks[i].what == "axon")
			axon = blockToData(blocks[i]);
		if(blocks[i].what == "dendrite")
			dendrite = blockToData(blocks[i]);
	}
	
	//count layers
	int layersN = 0;
	for(int i = 0; i < blocks.size(); ++i) {
		if(blocks[i].what == "convolution")
			++layersN;
		if(blocks[i].what == "max_pooling")
			++layersN;
	}
	
	Network network(data.size(), layersN);
	network.setData(dendrite, axon);
	for(int i = 0; i < data.size(); ++i) {
		network.data[i] = data[i];
		network.deriv[i] = data[i];
		network.deriv[i].initMem();
	}
	
	// скопировать все слои из файла
	for(int i = 0; i < blocks.size(); ++i) {
		if(blocks[i].what == "convolution") {
			layers.push_back(blockToConv(blocks[i], network));
			network.layer[layers.size() - 1] = blockToConv(blocks[i], network);
		}
		if(blocks[i].what == "max_pooling") {
			layers.push_back(blockToMaxPooling(blocks[i], network));
			network.layer[layers.size() - 1] = blockToMaxPooling(blocks[i], network);
		}
	}
	
	if(layersN != layers.size())
		throw "some error";
	
	for(int i = 0; i < layersN; ++i)
		network.layer[i] = layers[i];
	
	// построить последовательность выполнения слоев
	int seqId;
	for(int i = 0; i < blocks.size(); ++i)
		if(blocks[i].what == "sequence")
			seqId = i;
	
	if(layers.size() != blocks[seqId].size() )
		throw "error with sequence length";
	
	for(int i = 0; i < blocks[seqId].size(); ++i)
		network.seq[i] = network.nameToLayerId(blocks[seqId][i][0]);
	
	// выделить память для всех карт признаков
	for(int i = 0; i < network.dN; ++i)
		network.data[i].initMem();
	
	return network;
}

Convolution Parser::blockToConv(Block &block, Network &network) {
	int K = block.getInt("kernel");
	int S = block.getInt("stride");
	Convolution conv(K, S, block.name);
	Data axon = network.nameToData(block.getString("axon"));
	Data dendrite = network.nameToData(block.getString("dendrite"));
	conv.setData(axon, dendrite);
	return conv;
}

MaxPooling Parser::blockToMaxPooling(Block &block, Network &network) {
	int K = block.getInt("kernel");
	MaxPooling mp(K, block.name);
	Data axon = network.nameToData(block.getString("axon"));
	Data dendrite = network.nameToData(block.getString("dendrite"));
	mp.setData(axon, dendrite);
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
	int s = size();
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
	return "";
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
