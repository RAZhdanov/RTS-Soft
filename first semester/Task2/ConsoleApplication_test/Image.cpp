#include "Image.h"


Image::Image() : mx(0), my(0), img(NULL)
{
}

Image::~Image()
{
	delete[] img; //Тут исключения генерироваться не могут
}
const int Image::get_mx()const
{
	return mx;
}
const int Image::get_my()const
{
	return my;
}
void Image::load(const char *fname) //метод load - загрузка из pnm (формат p2)
{	
	cv::Mat image = cv::imread(fname);
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
//показываем весь массив значений
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

//обнуляем весь массив значений
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
	int* dest = new int[destsize]; //выделяем память
	try
	{
		std::copy(src, src + srcsize, stdext::checked_array_iterator<int*>(dest, srcsize));
	}
	catch (...)
	{
		delete[] dest; //Здесь исключений не может быть
		throw;	//Передаем исходное исключение
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
		delete[] img; //здесь исключений не может быть
		img = img_new; //Вступаем во владение
		mx = src.mx;
		my = src.my;
	}
	return *this; //Безопасно, копирование не выполняется 
}