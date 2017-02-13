#include "Image.h"


Image::Image() : mx(0), my(0), img(NULL)
{
}

Image::~Image()
{
	delete[] img; //��� ���������� �������������� �� �����
}
const int Image::get_mx()const
{
	return mx;
}
const int Image::get_my()const
{
	return my;
}
void Image::load(const char *fname) //����� load - �������� �� pnm (������ p2)
{	
	cv::Mat image = cv::imread(fname);
	//for (int x = 0; x < image.size().width; ++x)
	//	for (int y = 0; y < image.size().height; ++y)
	//	{
	//		image.at<cv::Vec3b>(y, x)[0] = x; // Blue
	//		image.at<cv::Vec3b>(y, x)[1] = y; // Green
	//		image.at<cv::Vec3b>(y, x)[2] = (x+y)/2; // Red
	//	}
	mx = image.rows;
	my = image.cols;
	if (image.isContinuous())
	{
		array.assign((int*)image.datastart, (int*)image.dataend);
		
	}
	else
	{
		for (int i = 0; i < image.rows; ++i)
		{
			array.insert(array.end(), (int*)image.ptr<uchar>(i), (int*)image.ptr<uchar>(i)+image.cols);
		}
	}
	img = &array[0];
	
}
//���������� ���� ������ ��������
void Image::show()
{
	for (int i = 0; i < my; i++)  //column
	{
		for (int j = 0; j < mx; j++)  //rows
		{
			std::cout << get(i, j) << " ";
		}
		std::cout << std::endl;
	}
}

//�������� ���� ������ ��������
void Image::init(const cv::Mat &src)
{	
	for (int i = 0; i < my; i++) //column
	{
		for (int j = 0; j < mx; j++) //rows
		{
			set(i, j, src.data[mx*i + j]);
		}
	}
}

void Image::set(const int const y, const int const x, const int const c)
{
	img[mx*y + x] = c;
}
const int Image::get(const int const y, const int const x)
{
	return img[mx*y + x];
}
int *const Image::get_pointer_of_image()
{
	return img;
}
int* Image::NewCopy(const int* src, int srcsize, int destsize)
{
	assert(destsize >= srcsize);
	int* dest = new int[destsize]; //�������� ������
	try
	{
		std::copy(src, src + srcsize, stdext::checked_array_iterator<int*>(dest, srcsize));
	}
	catch (...)
	{
		delete[] dest; //����� ���������� �� ����� ����
		throw;	//�������� �������� ����������
	}
	return dest;
}
Image::Image(const Image &src) :
img(NewCopy(src.img, src.mx*src.my, src.mx*src.my)),
mx(src.mx),
my(src.my)
{}

Image& Image::operator=(const Image &src)
{
	if (this != &src)
	{
		int* img_new = NewCopy(src.img, src.mx*src.my, src.mx*src.my);
		delete[] img; //����� ���������� �� ����� ����
		img = img_new; //�������� �� ��������
		mx = src.mx;
		my = src.my;
	}
	return *this; //���������, ����������� �� ����������� 
}