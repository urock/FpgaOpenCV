#include <iostream>
#include<fstream>
#include<string>

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/core/core.hpp>

using namespace cv;
using namespace std;

// g++ color_test.cpp -lopencv_highgui -lopencv_imgproc -lopencv_core

int main()
{
	// создать объект видео-потока и открыть файл
	VideoCapture cap;
	cap.open("example.AVI");
	if ( !cap.isOpened() )  // if not success, exit program
    {
         cout << "Cannot open file" << endl;
         return -1;
    }
    
    // диапазон значений Hue (тон в модели HSV), в котором обнаруживается объект
	int iLowH = 2;
	int iHighH = 27;
	
	// Saturation насыщенность
	int iLowS = 200; 
	int iHighS = 255;
	
	// Value яркость
	int iLowV = 70;
	int iHighV = 255;
	
	// прочитать настройки тех ^ параметров из файла настроек
	// если файла нет, останутся по-умолчанию
	ifstream settings("settings");
	if( settings.is_open() ){
		string line;
		stringstream ss(line);
		
		getline(settings, line);
		ss >> iLowH;
		getline(settings, line);
		ss >> iHighH;
		getline(settings, line);
		ss >> iLowS;
		getline(settings, line);
		ss >> iHighS;
		getline(settings, line);
		ss >> iLowV;
		getline(settings, line);
		ss >> iHighV;
	}
	
	// создать контейнер для текущего изображения
	Mat imgIn;
	Mat imgOut;
	
	int iLastX = -1;
	int iLastY = -1;
	
	
	Size S = Size((int) cap.get(CV_CAP_PROP_FRAME_WIDTH),    // Acquire input size
                  (int) cap.get(CV_CAP_PROP_FRAME_HEIGHT));
    
    // создать поток вывода видео
	VideoWriter wr;
	wr.open("output.AVI", cap.get(CV_CAP_PROP_FOURCC), cap.get(CV_CAP_PROP_FPS), S, true);
	
	if (!wr.isOpened()) {
		cout  << "Could not open the output video for write" << endl;
		return -1;
	}
	
	// файл для записи координат
	ofstream cordsFile;
	cordsFile.open("cords_output.txt");
	
	while(cap.read(imgIn)){ // read читает один кадр из потока и возвращает false если поток закончился
		imgOut = imgIn;
		
		Mat imgHSV;
		// пребразовать изображение из BGR в HSV
		cvtColor(imgIn, imgHSV, COLOR_BGR2HSV);
		
		// здесь будет бинарное изображение, которое означает,
		// попал ли нужный пиксель в определенный выше диапазон
		Mat imgThresholded;
		inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), imgThresholded);
		
		//morphological opening (removes small objects from the foreground)
		// стянуть границы "белых" областей
		erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
		// снова расширить границы
		dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) ); 
		
		//morphological closing (removes small holes from the foreground)
		dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) ); 
		erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
		
		Moments oMoments = moments(imgThresholded);
		// Момент изображения - сумма вида summ(x^p * y^q * f(x, y)) по пикселям
		// где f(x, y) дает 1 либо 0 в зависимости от цвета
		// p + q = n - порядок момента
		
		// моменты первого порядка - это координаты геометрического центра белой области
		// момент нулегого порядка - площадь белой области
		double dM01 = oMoments.m01;
		double dM10 = oMoments.m10;
		double dArea = oMoments.m00;
		
		if (dArea > 1000) {
			//calculate the position of the ball
			int posX = dM10 / dArea;
			int posY = dM01 / dArea;        
			if (iLastX >= 0 && iLastY >= 0 && posX >= 0 && posY >= 0)
			{
				// отметить красной стрелкой объект
				line(imgOut, Point(posX, posY), Point(0, 0), Scalar(0,0,255), 2);
			}
			iLastX = posX;
			iLastY = posY;
			//Write coordinates to file
			cordsFile << posX << ' ' << posY << '\n';
		}
		
		// записать кадр с отмеченным объектом в output файл
		wr.write(imgOut);
	}
	
	cordsFile.close();
	return 0;
}
