
#include "Image.h"
using namespace MyImageNameSpace;

int main(int argc, char **argv) {
	
	Image img;
	img.load("abe_natsumi.pgm");

	Image img1(img);
	return 0;
}
