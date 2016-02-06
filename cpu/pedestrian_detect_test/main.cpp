
// g++ main.cpp -lopencv_core -lopencv_objdetect -lopencv_highgui

#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;
 
int main (int argc, const char * argv[])
{
    VideoCapture cap("example.AVI");
    /*cap.set(CV_CAP_PROP_FRAME_WIDTH, 320);
    cap.set(CV_CAP_PROP_FRAME_HEIGHT, 240);*/
 
    if (!cap.isOpened())
        return -1;
 
    Mat img;
    //namedWindow("opencv", CV_WINDOW_AUTOSIZE);
    // создать объект hog
    HOGDescriptor hog;
    hog.setSVMDetector(HOGDescriptor::getDefaultPeopleDetector());
 	
 	Size S = Size((int) cap.get(CV_CAP_PROP_FRAME_WIDTH),    // Acquire input size
                  (int) cap.get(CV_CAP_PROP_FRAME_HEIGHT));
 	// создать поток вывода видео
	VideoWriter wr;
	wr.open("output.AVI", cap.get(CV_CAP_PROP_FOURCC), cap.get(CV_CAP_PROP_FPS), S, true);
	
	if (!wr.isOpened()) {
		cout  << "Could not open the output video for write" << endl;
		return -1;
	}
 	
    while ( cap.read(img) )
    {
        if (img.empty())
            continue;
 		
        vector<Rect> found, found_filtered;
        // выделить много коробок
        hog.detectMultiScale(img, found, 0, Size(8,8), Size(32,32), 1.05, 2);
        size_t i, j;
        for (i=0; i<found.size(); i++) 
        {
            Rect r = found[i];
            // найти прямоугольник, не содержащийся полностью ни в одном из других
            for (j=0; j<found.size(); j++) 
                if (j!=i && (r & found[j]) == r)
                    break;
            if (j== found.size())
                found_filtered.push_back(r);
        }
 		
        for (i=0; i<found_filtered.size(); i++) 
        {
        	// сделать прямоугольники поменьше
            Rect r = found_filtered[i];
            /*r.x += cvRound(r.width*0.1);
		    r.width = cvRound(r.width*0.8);
		    r.y += cvRound(r.height*0.07);
		    r.height = cvRound(r.height*0.8);*/
		    // нарисовать их зеленым цветом
		    rectangle(img, r.tl(), r.br(), Scalar(0,255,0), 3);
        }
        for(int i = 0; i < found.size(); ++i)
        {
        	// нарисовать красными первоначальные прямоугольники
        	Rect r = found[i];
        	rectangle(img, r.tl(), r.br(), Scalar(0,0,255), 1);
 		}
//        imshow("opencv", img);
//        if (waitKey(10)>=0)
//            break;
		wr.write(img);
    }
    return 0;
}
