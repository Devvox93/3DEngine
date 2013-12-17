#define _CRT_SECURE_NO_DEPRECATE
#include "BitmapLoader.h"
#include <Windows.h>
#include <iostream>
#include "Logger.h"


void BitmapLoader::loadBMP()
{
	FILE* fp;	
	int raw_data_size;
	char* pixel;
	BITMAP_FILEHEADER bmpheader;
	BITMAP_HEADER bmpinfheader;
	std::ofstream outfile;
	outfile.open("bitmap_Test.txt", std::ios_base::app);


	fp = fopen("test.bmp", "rb");
	Logger::getInstance().log(INFO, "BMP found yeyeye");

	if (fp == NULL)
	{
		perror("Can't find BMP");
		Logger::getInstance().log(CRITICAL, "Can't find BMP Test");
	}

	fread(&bmpheader, sizeof(bmpheader), 1, fp);
	fread(&bmpinfheader, sizeof(bmpinfheader), 1, fp);

	raw_data_size = bmpinfheader.SizeImage;
	pixel = new char[raw_data_size];
	fread(pixel, sizeof(char), raw_data_size, fp);
	
	outfile << bmpinfheader.Height << std::endl;
	outfile << bmpinfheader.Width << std::endl;




	fclose(fp);
}


BitmapLoader::BitmapLoader()
{

}

BitmapLoader::~BitmapLoader()
{

}