#pragma once
#include <opencv\highgui.h>
#include <iostream>

class Image
{
private:
	int mx;
	int my;
	int* img;
private:
	void set(const int const y, const int const x, const int const c);
	const int get(const int const y, const int const x);
	int* NewCopy(const int* src, int srcsize, int destsize);
	void init(const cv::Mat &src);
	std::vector<int> array;
public:
	Image();
	Image(const Image& src); // конструктор копирования
	virtual ~Image(); /*throw()*/
	Image& operator=(const Image& src); //оператор присваивания		

	void load(const char *fname);
	void show();	
	int *const get_pointer_of_image();
	const int get_mx()const;
	const int get_my()const;
};