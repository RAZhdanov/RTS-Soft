#include "Image.h"


MyImageNameSpace::Image::Image() : mx(0), my(0), img(NULL), min_value(0), max_value(0)
{
}
int* MyImageNameSpace::Image::NewCopy(const int* src, int srcsize, int destsize)
{
	assert(destsize >= srcsize);
	int* dest = new int[destsize]; //�������� ������
	try
	{
		std::copy(src, src + srcsize, stdext::checked_array_iterator<int*>(dest, 100));
	}
	catch (...)
	{
		delete[] dest; //����� ���������� �� ����� ����
		throw;	//�������� �������� ����������
	}
	return dest;
}
MyImageNameSpace::Image::~Image()
{
	delete[] img; //��� ���������� �������������� �� �����
}

void MyImageNameSpace::Image::load(const char *fname) //����� load - �������� �� pnm (������ p2)
{
	cv::Mat img = cv::imread(fname, cv::IMREAD_UNCHANGED);
	cv::minMaxLoc(img, &min_value, &max_value);
	img.convertTo(img, CV_8U, 255.0 / max_value);
	cv::imshow("Image", img);
	cv::waitKey();
}
//���������� ���� ������ ��������
void MyImageNameSpace::Image::show()
{
	for (int i = 0; i < my; i++)
	{
		for (int j = 0; j < mx; j++)
		{
			std::cout << get(i, j) << " ";
		}
		std::cout << std::endl;
	}
}

//�������� ���� ������ ��������
void MyImageNameSpace::Image::init()
{
	for (int i = 0; i < my; i++)
	{
		for (int j = 0; j < mx; j++)
		{
			set(i, j, 0);
		}
	}
}

//��� ��������� ������?
void MyImageNameSpace::Image::set(const int const y, const int const x, const int const c)
{
	img[mx*y + x] = c;
}
const int MyImageNameSpace::Image::get(const int const y, const int const x)
{
	return img[mx*y + x];
}
MyImageNameSpace::Image::Image(const Image &src) : img(NewCopy(src.img, src.mx*src.my, src.mx*src.my)), mx(src.mx), my(src.my)
{}

MyImageNameSpace::Image& MyImageNameSpace::Image::operator=(const MyImageNameSpace::Image &src)
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