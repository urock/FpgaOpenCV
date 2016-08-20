//
// Created by hokop on 7/30/16.
//

#include <fstream>
#include "Parser.hpp"

Network Parser::blockToNetwork(Block block) {
	vector<Block> blocks = explodeBlock(block);
	
	vector<Data> data;
	vector<Layer> layers;
	// скопировать все слои и данные из файла
	for(int i = 0; i < blocks.size(); ++i) {
		if(blocks[i].what == "data")
			data.push_back(blockToData(blocks[i]));
		if(blocks[i].what == "convolution")
			layers.push_back(blockToConv(blocks[i]));
		if(blocks[i].what == "max_pooling")
			layers.push_back(blockToMaxPooling(blocks[i]));
	}
	
	Network network(data.size(), layers.size());
	
	// соединить все данные  со слоями
	for(int i = 0; i < data.size(); ++i)
		network.data[i] = data[i];
	for(int i = 0; i < layers.size(); ++i) {
		network.layer[i] = layers[i];
		network.connectAxon(layers[i].name, layers[i].axon.name);
		network.connectDendrite(layers[i].name, layers[i].dendrite.name);
	}
	
	// построить последовательность выполнения слоев
	int seqId;
	for(int i = 0; i < blocks.size(); ++i)
		if(blocks[i].what == "sequence")
			seqId = i;
	
	for(int i = 0; i < blocks[seqId].size(); ++i)
		network.seq[i] = network.nameToLayerId(blocks[seqId][i][0]);
	
	// выделить память для всех карт признаков
	network.initData();
	
	return network;
}

Convolution Parser::blockToConv(Block block) {
	int K = block.getInt("kernel");
	int S = block.getInt("stride");
	Convolution conv(K, S, block.name);
	Data axon(0, 0, block.getString("axon"));
	Data dendrite(0, 0, block.getString("dendrite"));
	conv.setData(axon, dendrite);
	return conv;
}

MaxPooling Parser::blockToMaxPooling(Block block) {
	int K = block.getInt("kernel");
	MaxPooling mp(K, block.name);
	mp.axon = Data(0, 0, block.getString("axon"));
	mp.dendrite = Data(0, 0, block.getString("dendrite"));
	return mp;
}

Data Parser::blockToData(Block block) {
	int N = block.getInt("N");
	int M = block.getInt("M");
	return Data(M, N, block.name);
}

vector<Block> Parser::explodeBlock(Block block) {
	int cPos = 0;
	vector<Block> v;
	while(cPos < block.size()) {
		Block tmp;
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

void Block::init(string filename) {
	what = "block_from_file";
	name = filename;
	ifstream f(filename.c_str());
	string str;
	Line line;
	while(getline(f, str))
		if( (line = str).size() != 0 )
			add(line);
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
