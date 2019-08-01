//26.07.2019 code version 0.1 
/*
3D kernel image filtering for STM Assignment Work Part2 Section1

input form: 3D kernels single RGB color image
utput form: 3D kernels filtered single RGB color image

Keypoint: do not use any image processing/computer vision built-in filters
to manipulate image. Allowed to use them for only to read and write from/to.
**/

/*
To read and write an image in format .jpeg, cimg library is used.
Please be sure that you have cimg-dev on your system installed and CImg.h
file presents in your working directory.
Tip: you can install it on ubuntu by following fast initialization guide.
Compile & Run : You can may compile project over Makefile by command "make" or
with the command below:
 "c++ -o img_filter 3Dkernel_image_filtering.cc -L/usr/X11R6/lib -lm -lpthread -lX11"
Run, compiled project with "./img_filter"
**/
// implemented by Ayşegül Demirtaş

#include <iostream>
#include <vector>
#include <assert.h>
#include <cmath>

//to use cimg
#include "CImg.h"

using namespace cimg_library;
using namespace std;

typedef vector<double> Array;
typedef vector<Array> Matrix;
typedef vector<Matrix> Image;


Matrix getRkernelFilter(){

	Matrix Rkernel(3, Array(3));
	Rkernel= {
		{1,0,-1},
		{2,0,-2},
		{1,0,-1}
	};
	return Rkernel;
}

Matrix getGkernelFilter(){

	Matrix Gkernel(3, Array(3));
	Gkernel= {
		{1,1,1},
		{1,1,1},
		{1,1,1}
	};
	return Gkernel;
}

Matrix getBkernelFilter(){

	Matrix Bkernel(3, Array(3));
	Bkernel= {
		{1,2,1},
		{2,4,2},
		{1,2,1}
	};
	return Bkernel;
}


Image imageLoad(const char *filename){

	//loading img over CImg
	CImg<float> image(filename);
	Image imageMatrix(3, Matrix(image.height(), Array(image.width())));

	//input image info
	cout << "width of image : " ;
	cout << image.width();
	cout << "\nheight of image : " ;
	cout << image.height();
	cout << "\nimage spectrum/dimension :" ;
	cout << image.spectrum();
	cout << "\nimage depth : " ;
	cout << image.depth();
	cout << "\n" ;

	int h,w;
	for (h=0 ; h< image.height() ; h++) {
	
		for (w=0 ; w< image.width() ; w++) {
			imageMatrix[0][h][w] = image(w, h, 0, 0);
			imageMatrix[1][h][w] = image(w, h, 0, 1);
			imageMatrix[2][h][w] = image(w, h, 0, 2);

		}
	} 

	return imageMatrix;
}

void saveImage(Image &image, const char *filename)
{

	int height = image[0].size();
	int width = image[0][0].size();
	int x,y;

	CImg<float> imageFile("image.jpg");

	for (y=0 ; y<height ; y++) {
 		for (x=0 ; x<width ; x++) {

			imageFile(x, y, 0, 0) = image[0][y][x];

			imageFile(x, y, 0, 0) = image[1][y][x];

			imageFile(x, y, 0, 0) = image[2][y][x];
		}
	}
	imageFile.save(filename);
}

Image applyFilter(Image &image, Matrix &filter){

   	int height = image[0].size();
   	int width = image[0][0].size();
   	int filterHeight = filter.size();
   	int filterWidth = filter[0].size();
   	int newImageHeight = height-filterHeight+1;
   	int newImageWidth = width-filterWidth+1;
   	int d,i,j,h,w;

   	Image newImage(3, Matrix(newImageHeight, Array(newImageWidth)));

	for (d=0 ; d<3 ; d++) {
		for (i=0 ; i<newImageHeight ; i++) {
		    for (j=0 ; j<newImageWidth ; j++) {
			for (h=i ; h<i+filterHeight ; h++) {
			    for (w=j ; w<j+filterWidth ; w++) {
				newImage[d][i][j] += filter[h-i][w-j]*image[d][h][w];
			    }
			}
		    }
		}
	}

	return newImage;
}

Image uniteChannels(Image &image,const char *Rname,const char *Gname,const char *Bname){ 

	int height = image[0].size();
   	int width = image[0][0].size();

   	Image newImage(3, Matrix(height, Array(width)));
	CImg<float> r(Rname);
	CImg<float> g(Gname);
	CImg<float> b(Bname);

	for (int h=0 ; h< height ; h++) {
	
		for (int w=0 ; w< width ; w++) {

			newImage[0][h][w] = r(w, h, 0, 0);
			newImage[1][h][w] = g(w, h, 0, 1);
			newImage[2][h][w] = b(w, h, 0, 2);

		}
	} 

	return newImage;
}

//main function
int main(){
	Matrix RedFilter = getRkernelFilter();
	Matrix GreenFilter = getGkernelFilter();
	Matrix BlueFilter = getBkernelFilter();

   	cout << "Loading image..." << endl;
   	Image loadedImage = imageLoad("image.jpg");

	CImg<unsigned char> image("image.jpg");
	CImgDisplay source_disp(image,"source image");
	while (!source_disp.is_closed()) {
		source_disp.wait(); 
	}

   	cout << "Applying filter..." << endl;
   	Image newImageR = applyFilter(loadedImage, RedFilter);
   	Image newImageG = applyFilter(loadedImage, GreenFilter);
   	Image newImageB = applyFilter(loadedImage, BlueFilter);

   	cout << "Saving Filtered R Kernel..." << endl;
   	saveImage(newImageR, "filtered_Rkernel.jpg");

	CImg<unsigned char> Rimage("filtered_Rkernel.jpg");
	CImgDisplay r_disp(Rimage,"rkernel filtered of source image");
	while (!r_disp.is_closed()) {
		r_disp.wait(); 
	}

   	cout << "Saving Filtered G Kernel..." << endl;
   	saveImage(newImageG, "filtered_Gkernel.jpg");

	CImg<unsigned char> Gimage("filtered_Gkernel.jpg");
	CImgDisplay g_disp(Gimage,"gkernel filtered of source image");
	while (!g_disp.is_closed()) {
		g_disp.wait(); 
	}

   	cout << "Saving Filtered B Kernel..." << endl;
   	saveImage(newImageB, "filtered_Bkernel.jpg");

	CImg<unsigned char> Bimage("filtered_Bkernel.jpg");
	CImgDisplay b_disp(Bimage,"bkernel filtered of source image");
	while (!b_disp.is_closed()) {
		b_disp.wait(); 
	}

	const char *Rname = "filtered_Rkernel.jpg";
	const char *Gname = "filtered_Gkernel.jpg";
	const char *Bname = "filtered_Bkernel.jpg";
	
   	Image outputImage = uniteChannels(loadedImage, Rname, Gname, Bname);
	saveImage(outputImage, "output_image.jpg");

	cout << "Done!" << endl;

	CImg<unsigned char> output("output_image.jpg");
	CImgDisplay out_disp(output,"final 3D filtered source image");
	while (!out_disp.is_closed()) {
		out_disp.wait(); 
	}
	cout << "Filtering Process has been just ended!\nYou may reach filtered output and the intermediate manipulated kernels in your file directory." << endl;

	//output image info
	cout << "\nOutput file specifications : \n" ;
	
	cout << "width of image : " ;
	cout << output.width();
	cout << "\nheight of image : " ;
	cout << output.height();
	cout << "\nimage spectrum/dimension :" ;
	cout << output.spectrum();
	cout << "\nimage depth : " ;
	cout << output.depth();
	cout << "\n" ;

 	return 0;
}
// end of program.. 

