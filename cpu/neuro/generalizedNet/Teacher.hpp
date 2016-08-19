//
// Created by hokop on 8/14/16.
//

#ifndef GENERALIZEDNET_TEACHER_HPP
#define GENERALIZEDNET_TEACHER_HPP


#include "Network.hpp"
#include "Parser.hpp"

class Teacher
{
	Teacher() {}
	~Teacher() {}
	
	void readWeights(string filename, Network network);
	void teach(Network &network, vector<Data> in, vector<Data> out, int iterations, string fileForErrors = "");
	
	void writeWeights(Network network, string filename);
	// todo: функция которая обучает
	// берет массив дата и обучает
	// и делает градспуск
	// создает градспуск и делает итерации
	// и кросс-верификацию
	// пишет ошибки в файл
};


#endif //GENERALIZEDNET_TEACHER_HPP