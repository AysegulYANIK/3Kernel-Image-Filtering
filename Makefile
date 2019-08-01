output: 3Dkernel_image_filtering.o
	c++ -o img_filter 3Dkernel_image_filtering.cc -L/usr/X11R6/lib -lm -lpthread -lX11


3Dkernel_image_filtering.o : 3Dkernel_image_filtering.cc 
	g++ -c 3Dkernel_image_filtering.cc 

clean: 
	rm *.o 


