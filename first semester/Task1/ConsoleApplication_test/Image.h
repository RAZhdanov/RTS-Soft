#pragma once
#include <opencv\highgui.h>
#include <iostream>
namespace MyImageNameSpace
{
	class Image
	{
	private:
		int mx;
		int my;
		int* img;
		double min_value;
		double max_value;
	private:
		int* NewCopy(const int* src, int srcsize, int destsize);
	public:
		Image();
		Image(int tmx, int tmy);
		Image(const Image& src); // конструктор копирования
		virtual ~Image() throw();
		Image& operator=(const Image& src); //оператор присваивания		

		void load(const char *fname);
		void show();
		void init();
		void set(const int const y, const int const x, const int const c);
		const int get(const int const y, const int const x);
	};
}