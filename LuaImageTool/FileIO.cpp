#include "pch.h"
#include <fstream>
#include <sstream>
#include "FileIO.h"
#include "Canvas.h"

int findPaletteIndex(int x, int y)
{
	Canvas canvas;
	for (int i = 0; i < 16; i++)
	{
		if (Canvas::palette[i].r == canvas.getCanvasPixel(x, y).r)
		{
			if (Canvas::palette[i].g == canvas.getCanvasPixel(x, y).g)
			{
				if (Canvas::palette[i].b == canvas.getCanvasPixel(x, y).b)
				{
					return i;
				}
			}
		}
	}

	return -1;
}

void FileIO::SaveImage()
{
	std::ofstream myFile;
	myFile.open("Resource/save/save.meme");
	if (myFile.is_open())
	{
		Canvas canvas;

		for (int y = 0; y < 32; y++)
		{
			for (int x = 0; x < 32; x++)
			{
				myFile << canvas.getCanvasPixel(x, y).r << " ";
				myFile << canvas.getCanvasPixel(x, y).g << " ";
				myFile << canvas.getCanvasPixel(x, y).b << "\n";
			}
		}

		myFile.close();
	}
	else
	{

	}
}

void FileIO::LoadImage()
{
	std::ifstream myFile;
	myFile.open("Resource/load/load.meme");
	//myFile.open("Resource/maps/map.SGM");
	if (myFile.is_open())
	{
		Canvas canvas;

		std::string dataS;
		int dataI;

		
		std::string subS;

		for (int y = 0; y < 32; y++)
		{
			for (int x = 0; x < 32; x++)
			{
				getline(myFile, dataS);
				std::istringstream iss(dataS);

				iss >> subS;
				dataI = std::stoi(subS);
				//printf("R: %i ", dataI);
				canvas.changePixel(x, y, dataI, canvas.getCanvasPixel(x, y).g, canvas.getCanvasPixel(x, y).b);

				iss >> subS;
				dataI = std::stoi(subS);
				//printf("G: %i ", dataI);
				canvas.changePixel(x, y, canvas.getCanvasPixel(x, y).r, dataI, canvas.getCanvasPixel(x, y).b);

				iss >> subS;
				dataI = std::stoi(subS);
				//printf("B: %i \n", dataI);
				canvas.changePixel(x, y, canvas.getCanvasPixel(x, y).r, canvas.getCanvasPixel(x, y).g, dataI);
			}
		}
	}
	else
	{

	}
}

void FileIO::ExportImage()
{
	std::ofstream myFile;
	myFile.open("Resource/export/export.txt");
	if (myFile.is_open())
	{
		Canvas canvas;
		//MAYBE REWRITE SO IT ORDERS ALL THE COLORS SO WE ONLY HAVE TO CHANGE THE COLOR ONCE PER EACH COLOR THERE IS
		//generate the color pallet
		//gpu.setPaletteColor(index, color)
		for (int i = 0; i < 16; i++)
		{
			myFile << "gpu.setPaletteColor(";
			myFile << std::dec << i;
			myFile << ", 0x";
			if (Canvas::palette[i].r < 17)
			{
				myFile << 0;
			}
			myFile << std::hex << Canvas::palette[i].r;
			if (Canvas::palette[i].g < 17)
			{
				myFile << 0;
			}
			myFile << std::hex << Canvas::palette[i].g;
			if (Canvas::palette[i].b < 17)
			{
				myFile << 0;
			}
			myFile << std::hex << Canvas::palette[i].b;
			myFile << ")\n";
		}
		
		

		for (int y = 0; y < 32; y++)
		{
			for (int x = 0; x < 32; x++)
			{
				if (canvas.getCanvasPixel(x, y).r == 0 && canvas.getCanvasPixel(x, y).g == 0 && canvas.getCanvasPixel(x, y).b == 0)
				{
					//ignore
				}
				else
				{
					
					//drawPixel(x + X, y + Y, index)
					myFile << "drawPixel(";
					myFile << std::dec << x + 1;
					myFile << " + x, ";//NEEDS TEST
					myFile << y + 1;
					myFile << " + y, ";
					myFile << findPaletteIndex(x, y);
					myFile << ")\n";
					//myFile << ", 0x";
					//if (canvas.getCanvasPixel(x, y).r < 17)
					//{
					//	myFile << 0;
					//}
					//myFile << std::hex << canvas.getCanvasPixel(x, y).r;
					//if (canvas.getCanvasPixel(x, y).g < 17)
					//{
					//	myFile << 0;
					//}
					//myFile << canvas.getCanvasPixel(x, y).g;
					//if (canvas.getCanvasPixel(x, y).b < 17)
					//{
					//	myFile << 0;
					//}
					//myFile << canvas.getCanvasPixel(x, y).b << ")\n";
				}
			}
		}

		myFile.close();
	}
	else
	{

	}
}