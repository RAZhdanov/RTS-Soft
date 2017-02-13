#include <Windows.h>
#include <opencv\highgui.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <memory> //shared_ptr, weak_ptr
#include <iostream>
#include "tree.h" //definition of Tree class

int main(int argc, char **argv) {
	setlocale(LC_ALL, "");
	cv::Mat image, gray;
	Tree<cv::Mat> tree, tree1;
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
	if (GetOpenFileNameA(&ofn) == TRUE)
	{
		//if the next element after strlen(szFile)+1 equals NULL than we have only one file
		if (*(szFile + strlen(szFile) + 1) == NULL)
		{
			image = cv::imread(szFile);
			cvtColor(image, gray, CV_BGR2GRAY);
			tree.insertNode(gray);
		}
		else
		{
			char *NextFileName = szFile; // initialization of char-pointer variable which points to szFile char-array
			NextFileName = NextFileName + strlen(NextFileName) + 1; //this operation cuts path and gives us only filename
			//Lets implement while-loop to get number of files
			while (*NextFileName != NULL)
			{
				number_of_files++; //incrementation of number of files
				NextFileName = NextFileName + strlen(NextFileName) + 1; //than we have the next file name
			}


			NextFileName = szFile; // initialization of char-pointer variable which points to szFile char-array
			NextFileName = NextFileName + strlen(NextFileName) + 1;  //than we have the next file name

			//Great! Finally we can work with our files, because now we know what number of files must be processed.
			for (int i = 0; *NextFileName != NULL; ++i, NextFileName = NextFileName + strlen(NextFileName) + 1)
			{
				image = cv::imread(NextFileName);
				cvtColor(image, gray, CV_BGR2GRAY);
				cv::resize(gray, gray, cv::Size(8, 8));
				tree.insertNode(gray);
			}
		}
	}
	tree1 = tree;
	tree1(tree);

	
	return 0;
}