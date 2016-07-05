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
	
	Mat image = imread("test.png", CV_LOAD_IMAGE_GRAYSCALE);
	
	//пройтись по картинке окнами разных размеров. Масштабирование
	//способом "пирамид" (увеличить в степень двойки раз)
	Mat result = image.clone();
	int mult = 1;
	for(int i = 1; i < 5; ++i) {
		desc.processImage(image, result, 32, theory, names, mult, 5, .01);
		mult *= 2;
	}
	
	imwrite("out.png", result);
}
