#include "LoadBitmap.h"
#include <windows.h>
#include <gdiplus.h>

#include <iostream>
#include <fstream>
#include <sstream>

#pragma comment(lib, "gdiplus.lib")
using namespace std;
using namespace Gdiplus;

Texture2D MathUtil::LoadBitmapToColorArray(wstring filePath)
{
	GdiplusStartupInput gdiplusstartupinput;
	ULONG_PTR gdiplustoken;
	GdiplusStartup(&gdiplustoken, &gdiplusstartupinput, nullptr);

	Bitmap* bmp = new Bitmap(filePath.c_str());
	if (!bmp)
	{
		MessageBox(nullptr, "error", "picture path is null!", MB_OK);
		delete bmp;
		GdiplusShutdown(gdiplustoken);
		return Texture2D(0,0);
	}
	else
	{
		UINT height = bmp->GetHeight();
		UINT width = bmp->GetWidth();
		//≥ı ºªØTexture2D
		Texture2D texture(width, height);

		Color color;

		for (int y = 0; y < height; y++)
			for (int x = 0; x < width; x++)
			{
				bmp->GetPixel(x, y, &color);

				texture.m_pixelBuffer[x][y] = ZCFLOAT3(
					color.GetRed() / 255.f,
					color.GetGreen() / 255.f,
					color.GetBlue() / 255.f
				);
			}
// 		vector<vector<ZCFLOAT3>> res(width,vector<ZCFLOAT3>(height));
// 		for (int i = 0; i < width; ++i)
// 		{
// 			for (int j = 0; j < height; ++j)
// 			{
// 				res[i][j] = texture.m_pixelBuffer[i][j];
// 			}
// 		}
		delete bmp;
		GdiplusShutdown(gdiplustoken);
		return texture;
	}
	
}

/*

ZCFLOAT3** MathUtil::LoadBitmapToColorArray(wstring filePath)
{
	GdiplusStartupInput gdiplusstartupinput;
	ULONG_PTR gdiplustoken;
	GdiplusStartup(&gdiplustoken, &gdiplusstartupinput, nullptr);

	Bitmap* bmp = new Bitmap(filePath.c_str());
	if (!bmp)
	{
		MessageBox(nullptr, "error", "pic path is null!", MB_OK);
	}
	else
	{
		string outfilename("color.txt");
		UINT height = bmp->GetHeight();
		UINT width = bmp->GetWidth();
		Color color;
		ofstream fout(outfilename.c_str());

		for (int y = 0; y < height; y++)
			for (int x = 0; x < width; x++)
			{
				bmp->GetPixel(x, y, &color);
				fout << x << ";" << y << ";"
					<< (int)color.GetRed() << ";"
					<< (int)color.GetGreen() << ";"
					<< (int)color.GetBlue() << endl;
			}

	}
	delete bmp;
	GdiplusShutdown(gdiplustoken);
}

*/