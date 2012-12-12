#include "png.h"

int main()
{
	PNG inImage("in.png");
	int height= inImage.height();
	int width= inImage.width();
	PNG outImage(width, height);

	for (int i = 0; i < width; i++) 
	{
		for (int j = 0; j < height; j++)
		{
			RGBAPixel a = *inImage(width-i-1,height-j-1);
			outImage(i,j)->red=a.red;
			outImage(i,j)->green=a.green;
			outImage(i,j)->blue=a.blue;
			outImage(i,j)->alpha=a.alpha;	
		}
	}
	
	outImage.writeToFile("out.png");

	return 0;	

}
