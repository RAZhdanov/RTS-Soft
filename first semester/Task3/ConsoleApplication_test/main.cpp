#include <Windows.h>
#include <opencv2/imgproc/imgproc.hpp>
#include "Image.h"
#include "LinkedList.h"
void recogniseStickersByThreshold(cv::Mat image, std::vector<cv::Mat> &stickers); //выделение контрастных стикеров
void transparentRect(cv::Mat& image, int x, int y, int w, int h, cv::Scalar clr);
int main(int argc, char **argv) {

	//1. читает изображение с доской и стикером
	std::vector<cv::Mat> stickers;
	cv::Mat bgr_image = cv::imread("image_one_sticker.jpg");
	cv::Mat orig_image = bgr_image.clone();
	recogniseStickersByThreshold(bgr_image, stickers);


	//читает изображение “динозавра” (или группу изображений динозавра dino1.jpg … dinoN.jpg помещает в односвязный список )
	Image *image;
	node mynode;
	LinkedList list;
	int number_of_files = 0;
	
	OPENFILENAMEA ofn;
	static char szFile[MAX_PATH];
	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = "JPG\0*.jpg\0PNG\0*.png\0PGM\0*.pgm";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = ".\\";
	ofn.Flags = OFN_ALLOWMULTISELECT | OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
	//Если все прошло успешно, то вызываем диалговое окно с установленными свойствами
	if (GetOpenFileNameA(&ofn) == TRUE)
	{
		//если следующий элемент после n-ой длины имени равен нулю, то это означает, что мы имеем дело с одним файлом
		if (*(szFile + strlen(szFile) + 1) == NULL)
		{
			image = new Image;
			image[0].load(szFile);
			mynode.image_node = image;
			mynode.next = NULL;
			list.insertNode(&mynode, 0);
		}
		else
		{
			char *NextFileName = szFile; // с указателем NextFileName мы будем работать
			NextFileName = NextFileName + strlen(NextFileName) + 1; //переход к первому имени файла

			//Для начала узнаем, сколько у нас всего файлов в итоге
			while (*NextFileName != NULL)
			{
				number_of_files++;
				NextFileName = NextFileName + strlen(NextFileName) + 1; //перейди к следующему имени
			}
			image = new Image[number_of_files];

			NextFileName = szFile;
			NextFileName = NextFileName + strlen(NextFileName) + 1; //переход к первому имени файла

			for (int i = 0; *NextFileName != NULL; ++i, NextFileName = NextFileName + strlen(NextFileName) + 1)
			{
				image[i].load(NextFileName);
				mynode.image_node = &image[i];
				mynode.next = NULL;
				list.insertAtBack(mynode);
			}
		}
	}

	node* head = list.GetHead();
	double alpha = 0.5;
	for (int i = 0; head != NULL; i++)
	{
		int * ptr = (head->image_node->get_pointer_of_image());
		cv::Mat *dino = new cv::Mat(cv::Mat(head->image_node->get_mx(), head->image_node->get_my(), CV_8UC3, ptr));
		for (auto number_of_sticker : stickers)
		{
			cv::resize(*dino, *dino, cv::Size(number_of_sticker.cols, number_of_sticker.rows)); //уменьшили размеры динозавра до размеров стикера
			cv::addWeighted(*dino, alpha, number_of_sticker, 1 - alpha, 0.0, number_of_sticker); //совместили динозавтра со стикером и записали результат в temp
			cv::addWeighted(number_of_sticker, alpha, number_of_sticker, 1 - alpha, 0.0, number_of_sticker);
			cv::addWeighted(bgr_image, alpha, orig_image, 1 - alpha, 0.0, bgr_image);
		}
		cv::imshow("tmp", bgr_image);
		cv::waitKey(1000);
		delete dino;
		head = head->next;
	}
	return 0;
}
//Transperent rectangle in the image
void transparentRect(cv::Mat& image, int x, int y, int w, int h, cv::Scalar clr)
{
	cv::Mat roi = image(cv::Rect(x, y, w, h));
	cv::Mat color(roi.size(), CV_8UC3, clr);
	double alpha = 0.3;
	cv::addWeighted(color, alpha, roi, 1.0 - alpha, 0.0, roi);
}
void recogniseStickersByThreshold(cv::Mat image, std::vector<cv::Mat> &stickers)
{	
	int key_hue = 173;
	int key_saturation = 167;
	int key_value = 129;

	cv::Mat image_hsv;
	std::vector<std::vector<cv::Point>> contours;
	cv::cvtColor(image, image_hsv, cv::COLOR_BGR2HSV); //Преобразуем image в hsv

	cv::Mat tmp_img;

	//Выделение подходящих по цвету областей. Цвет задается константой :)
	cv::inRange(image_hsv, cv::Scalar(key_hue - 20, key_saturation - 20, key_value - 20), cv::Scalar(key_hue + 20, key_saturation + 20, key_value + 20), tmp_img);
	
	//Замазать огрехи при выделении по цвету
	cv::dilate(tmp_img, tmp_img, cv::Mat(), cv::Point(-1, -1), 3);
	cv::erode(tmp_img, tmp_img, cv::Mat(), cv::Point(-1, -1), 1);
	//Выделение непрерывных областей
	cv::findContours(tmp_img, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
	for (unsigned int i = 0; i < contours.size(); i++)
	{
		stickers.push_back(image(cv::Rect(cv::boundingRect(contours[i])))); //Добавить к массиву распознанных стикеров
	}
}