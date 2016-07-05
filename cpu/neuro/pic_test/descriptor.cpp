#include"descriptor.hpp"

void Descriptor::load( string filename ) {
	ifstream f( filename.c_str() );
	
	if( ! f.is_open() ) {
		cout << "could not open input file\n";
		return;
	}
	
	string line;
	vector<string> parsed;
	
	getline( f, line );
	
	parsed = parseLine(line);
	int layersN = parsed.size();
	int *layersz = (int*) malloc( layersN * sizeof(int) );
	
	for(int l = 0; l < layersN; ++l ) {
		layersz[l] = atoi( parsed[l].c_str() );
	}
	
	if( mlp.weight != nullptr )
		mlp.clear();
	mlp.init( layersN, layersz );
	
	for( int l = 0; l < layersN - 1; ++l ){
		for( int i = 0; i <= layersz[l]; ++i ) {
			getline( f, line );
			parsed = parseLine( line );
			for( int o = 0; o < layersz[l + 1]; ++o )
				mlp.weight[l][i][o] = atof( parsed[o].c_str() );
		}
	}
	
	free(layersz);
	
	f.close();
	return;
}

void Descriptor::save( string filename ) {
	ofstream f( filename.c_str() );
	if( ! f.is_open() ) {
		cout << "could not open output file\n";
		return;
	}
	for( int l = 0; l < mlp.layersN; ++l )
		f << mlp.layersz[l] << '\t';
	f << endl;
	
	for( int l = 0; l < mlp.layersN - 1; ++l ) {
		for( int i = 0; i <= mlp.layersz[l]; ++i ) {
			for( int o = 0; o < mlp.layersz[l + 1]; ++o ) {
				f << mlp.weight[l][i][o] << '\t';
			}
			f << '\n';
		}
	}
	f.close();
	return;
}

std::vector<string> parseLine(string line) {
	std::vector<string> parsed;
	bool split = true;
	string temp = "";
	
	for( int i = 0; i < line.length(); ++i ) {
		char c = line[i];
		if( c == ' ' || c == '\t' ) {
			if( !split ) {
				parsed.push_back(temp);
				temp = "";
			}
			split = true;
		} else {
			split = false;
			temp += c;
		}
	}
	if( !split )
		parsed.push_back(temp);
	
	return parsed;
}

float sigmoid(float x, float slope) {
	return x / ( fabs(x) + 1.0 / slope );
}

Scalar colorTran( float x, float slope ) {
	slope /= 2.0;
	int b = 0, r = 0;
	if( x > .0 )
		r = 255 * sigmoid( x, slope );
	else
		b = 255 * sigmoid( -x, slope );
	return Scalar(255 - r, 255 - r - b, 255 - b);
}

Mat Descriptor::getImage( ) {
	int width = 1920;
	int height = 1080;
	int lN = mlp.layersN;
	int x[ lN ];
	int dx = width / (lN + 1);
	
	for( int i = 0; i < lN; ++i )
		x[i] = dx * (i + 1);
	
	Mat mat( height, width, CV_8UC3, Scalar(255, 255, 255) );
	
	vector< vector<int> > y;
	
	for( int i = 0; i < lN; ++i ) {
		int nN = mlp.layersz[i];
		int dy = height / (nN + 1);
		vector<int> yi;
		for( int k = 0; k < nN; ++k )
			yi.push_back( dy * (k + 1) );
		y.push_back( yi );
	}
	
	for( int i = 0; i < lN - 1; ++i ) {
		int ni = mlp.layersz[i];
		int no = mlp.layersz[i + 1];
		for( int j = 0; j < ni; ++j )
			for( int k = 0; k < no; ++k ) {
				line(mat, Point( x[i], y[i][j] ), Point( x[i + 1], y[i + 1][k] ),
						colorTran(mlp.weight[i][j][k], ni), 2 );
			}
	}
	
	for( int l = 0; l < lN - 1; ++l ) {
		int ni = mlp.layersz[l];
		int no = mlp.layersz[l + 1];
		int rad = 8;
		for( int o = 0; o < no; ++o )
			circle(mat, Point( x[l + 1], y[l + 1][o] ), rad, colorTran(mlp.weight[l][ni][o], ni), -1 );
	}
	
	return mat;
}

Mat Descriptor::preprocessImage(Mat image, float alpha) {
	Mat new_image = Mat::zeros( image.size(), image.type() );
	
	int beta = 128 * (1.0 - alpha) ; //brightness control
	
	/// Do the operation new_image(i,j) = alpha*image(i,j) + beta
	for( int y = 0; y < image.rows; y++ ) {
		for( int x = 0; x < image.cols; x++ ) {
			new_image.at<uchar>(y,x) = saturate_cast<uchar>( alpha*( image.at<uchar>(y,x) ) + beta );
		}
	}
	
	return new_image;
}

Mat Descriptor::processImage(Mat img, int width, vector<vec> theory, vector<string> names,
			int mult, int step, flt tolerance)
{
	Mat result = img.clone();
	int x1, y1;
	
	width *= mult;
	step *= mult;
	
	for(x1 = 0; x1 + width < img.cols; x1 += step) {
		for(y1 = 0; y1 + width < img.rows; y1 += step) {
			vec real = theory[0];
			Rect rect(x1, y1, width, width);
			Mat part = img(rect).clone();
			vec imgV = imgToVec(part, mult);
			mlp.predict( &imgV[0], &real[0] );
			
			for(int i = 0; i < theory.size(); ++i) {
				flt error = tolerance;
				for(int j = 0; j < real.size(); ++j) {
					if(theory[i][j] > 0)
						error = fabs(real[j] - theory[i][j]);
				}
		
				if(error < tolerance) {
					rectangle( result, rect, Scalar::all(127), 2 );
					putText( result, names[i], Point(x1, y1), FONT_HERSHEY_SIMPLEX, .5, Scalar::all(127) );
				}
			}
		}
	}
	return result;
}

void Descriptor::processVideo(string inputName, string outputName, vector<vec> theory, vector<string> names) {
	VideoCapture cap(inputName);
	if( !cap.isOpened() ) {
		cout << "Couldn't open the input video\n";
		return;
	}
	
	Size S = Size((int) cap.get(CV_CAP_PROP_FRAME_WIDTH),    // Acquire input size
                  (int) cap.get(CV_CAP_PROP_FRAME_HEIGHT));
	VideoWriter wr;
	wr.open(outputName, cap.get(CV_CAP_PROP_FOURCC), cap.get(CV_CAP_PROP_FPS), S, true);
	if (!wr.isOpened()) {
		cout  << "Could not open the output video for write" << endl;
		return;
	}
	
	Mat img;
	int i = 0;
	while ( cap.read(img) ) {
		if (img.empty())
			continue;
		
		if( i % 100 == 0 )
			cout << i << endl;
		++i;
		
		int width = 330;
		resize(img, img, Size( width, (int)((float)img.rows / (float)img.cols * (float) width) ) );
		cvtColor(img, img, CV_BGR2GRAY);
		
		img = preprocessImage(img, 5);
		img = processImage(img, 32, theory, names, 1, 6, 0.05);
		
		resize(img, img, S);
	 	cvtColor(img, img, CV_GRAY2BGR);
		
		wr.write(img);
 	}
}

vec imgToVec( Mat &img, int mult ) {
	vec v;
	uchar *data = img.data;
	for(int i = 0; i < img.cols; i += mult)
		for(int j = 0; j < img.rows; j += mult)
			v.push_back( (flt) data[i * img.rows + j] / 255. );
	return v;
}

int getdir (string dir, vector<string> &files)
{
    DIR *dp;
    struct dirent *dirp;
    if((dp  = opendir(dir.c_str())) == NULL) {
        cout << "Error(" << errno << ") opening " << dir << endl;
        return errno;
    }

    while ((dirp = readdir(dp)) != NULL) {
        files.push_back(string(dirp->d_name));
    }
    closedir(dp);
    return 0;
}

vector< vector<vec> > loadClassificationTask( string dir, vector<string> names ) {
	int species = names.size();
	vector< vector<vec> > task;
	for(int j = 0; j < species; ++j) {
		string folder = dir + names[j] + string("/");
		vector<string> files;
		getdir(folder, files);
		
		vector<vec> tmp;
		for(int k = 0; k < files.size(); ++k) {
			if(files[k] == "." or files[k] == "..")
				continue;
			string name = folder + files[k];
			Mat img = imread( name, CV_LOAD_IMAGE_GRAYSCALE );
			tmp.push_back( imgToVec(img) );
		}
		
		task.push_back(tmp);
	}
	return task;
}

vector<vec> generateTheory( int size ) {
	vector<vec> theory;
	int num = size;
	for(int i = 0; i < num; ++i) {
		vec tmp;
		for(int j = 0; j < size; ++j)
			tmp.push_back( (j == i % size)? 1.0 : -1.0 );
		theory.push_back( tmp );
	}
	return theory;
}

void Descriptor::pseudoTeachLayer( const vec &inputVal, int outputSz, const vec &deriv,
		flt **weight, vec &nextDeriv )
{
	// prepare some values
	vec s(outputSz, .0);
	for( int o = 0; o < outputSz; ++o ) {
		for( int i = 0; i < inputVal.size(); ++i )
			s[o] += weight[i][o] * inputVal[i];
		s[o] = mlp.activationDeriv( s[o] );
	}
	// calc derivatives for next layer
	for( int i = 0; i < inputVal.size(); ++i ) {
		flt edai = 0;
		for( int k = 0; k < outputSz; ++k )
			edai += deriv[k] * weight[i][k] * s[k];
		nextDeriv.push_back( edai ); // edai * 1.0 is default
	}
	return;
}
vec errorDeriv( const vec &real, const vec &theory ) {
	vec ed;
	for( int i = 0; i < real.size(); ++i ) {
		flt a = real[i] - theory[i];
		ed.push_back( a );
	}
	return ed;
}
Mat Descriptor::getLayerImage(int L, vec what, vec white) {
	if( white.size() == 0 )
		for(int i = 0; i < mlp.layersz[0]; ++i)
			white.push_back( .5 );
	
	vec output( mlp.layersz[ mlp.layersN - 1 ], 0 );
	mlp.predict( &white[0], &output[0] );
	
	vec ed = errorDeriv(output, what);
	
	for( int l = mlp.layersN - 1; l > L; --l ) {
		int ls = mlp.layersz[ l - 1 ];
		
		vec nextD;
		vec inputVal( ls, .0 );
		for( int i = 0; i < ls; ++i )
			inputVal[i] = mlp.lreg[l - 1][i];
		inputVal.push_back(1.0);
		
		pseudoTeachLayer( inputVal, mlp.layersz[l], ed, mlp.weight[l - 1], nextD );
		
		ed = nextD;
	}
	
	return vecToImg(ed);
}


Mat vecToImg( vec &v ) {
	int sz = (int)sqrt(v.size());
	Mat m(sz, sz, CV_8UC3, Scalar(0));
	
	flt sum = 0.0;
	for(int i = 0; i < v.size(); ++i)
		sum += fabs(v[i]);
	flt slope = 1. / sum * (flt) v.size();
	
	for(int i = 0; i < sz; ++i)
		for(int j = 0; j < sz; ++j) {
			int k = i * sz + j;
			Scalar col = colorTran( v[k], slope );
			circle(m, Point(j, i), 1, col);
		}
	
	return m;
}




















