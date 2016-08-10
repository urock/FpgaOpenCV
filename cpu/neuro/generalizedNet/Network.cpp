//
// Created by hokop on 7/30/16.
//

#include "Network.hpp"

Network::Network(int sDN, int sLN) {
	
}

int Network::nameToId(string name);
void Network::connect(string name1, string name2);

bool Network::check();
void Network::compute();
void Network::proceedError();