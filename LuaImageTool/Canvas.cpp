#include "pch.h"
#include <vector>
#include "Artist.h"
#include "Canvas.h"
#include "Controller.h"
#include "FileIO.h"

std::vector<std::vector<Artist::RGB>> canvas;

std::vector<Artist::RGB> Canvas::palette;

int selectedColorIndex = 0;
int bottemMenuIndex = 0;
bool changingColor = false;
bool drawGrid = false;

void Canvas::resizeCanvas(int size)
{
	canvas.resize(size);
	for (int i = 0; i < size; i++)
		canvas[i].resize(size);
}

void Canvas::resetCanvas()
{
	for (int y = 0; y < 32; y++)
	{
		for (int x = 0; x < 32; x++)
		{
			canvas[x][y].r = 0;
			canvas[x][y].g = 0;
			canvas[x][y].b = 0;
		}
	}
	/*for (int y = 0; y < 16; y++)
	{
		for (int x = 0; x < 16; x++)
		{
			canvas[x][y].r = 255;
			canvas[x][y].g = 0;
			canvas[x][y].b = 255;
		}
	}
	for (int y = 0; y < 16; y++)
	{
		for (int x = 0; x < 16; x++)
		{
			canvas[x + 16][y + 16].r = 255;
			canvas[x + 16][y + 16].g = 0;
			canvas[x + 16][y + 16].b = 255;
		}
	}*/
}

void Canvas::resizePalette(int size)
{
	palette.resize(size);
}

void Canvas::resetPalette()
{
	for (int i = 0; i < 16; i++)
	{
		palette[i].r = 0;
		palette[i].g = 0;
		palette[i].b = 0;
	}
}

Artist::RGB Canvas::getCanvasPixel(int x, int y)
{
	return canvas[x][y];
}

void Canvas::drawCanvas()
{
	Artist artist;

	

	for (int y = 0; y < canvas.size(); y++)
	{
		
		for (int x = 0; x < canvas.size(); x++)
		{
			artist.changeRendererColor(canvas[x][y].r, canvas[x][y].g, canvas[x][y].b);
			artist.drawRectangle(x * 8, y * 8, 8, 8);
		}
	}
	if (drawGrid)
	{
		artist.changeRendererColor(112, 112, 112);
		for (int y = 0; y <= canvas.size(); y++)
		{
			artist.drawLineFromPoints(0, y * 8, 256, y * 8);
		}
		for (int x = 0; x <= canvas.size(); x++)
		{
			artist.drawLineFromPoints(x * 8, 0, x * 8, 256);
		}
	}
}

void Canvas::drawHud()
{
	Artist artist;

	if (changingColor)
	{
		artist.changeRendererColor(44, 44, 44);
		artist.drawRectangle(256, 0, 87, 257);
	}
	else
	{
		artist.changeRendererColor(107, 82, 0);
		artist.drawRectangle(256, 0, 87, 257);
	}
	

	artist.changeRendererColor(213, 165, 0);
	artist.drawRectangle(261 + 27 * (selectedColorIndex % 3), 4 + 27 * (selectedColorIndex / 3), 24, 24);

	artist.changeRendererColor(112, 112, 112);
	for (int y = 0; y < 8; y++)
	{
		for (int x = 0; x < 3; x++)
		{
			artist.drawRectangle(262 + x * 27, 5 + y * 27, 22, 22);
			
		}
	}
	for (int y = 0; y < 6; y++)
	{
		for (int x = 0; x < 3; x++)
		{
			if (y < 5 || x < 1)
			{
				artist.changeRendererColor(palette[y * 3 + x].r, palette[y * 3 + x].g, palette[y * 3 + x].b);
				artist.drawRectangle(263 + x * 27, 6 + y * 27, 20, 20);
			}
		}
	}
	//bottem
	if (!changingColor)
	{
		artist.changeRendererColor(44, 44, 44);
		artist.drawRectangle(0, 256, 343, 44);
	}
	else
	{
		artist.changeRendererColor(107, 82, 0);
		artist.drawRectangle(0, 256, 343, 44);
	}

	
	
	artist.changeRendererColor(213, 165, 0);
	if (bottemMenuIndex < 3)
	{
		artist.drawRectangle(4 + 65 * bottemMenuIndex, 260, 62, 24);
	}
	if (bottemMenuIndex >= 3)
	{
		artist.drawRectangle(205 + 29 * (bottemMenuIndex - 3), 260, 24, 24);
	}

	artist.changeRendererColor(255, 0, 0);
	artist.drawRectangle(5, 261, 60, 22);

	artist.changeRendererColor(0, 255, 0);
	artist.drawRectangle(70, 261, 60, 22);

	artist.changeRendererColor(0, 0, 255);
	artist.drawRectangle(135, 261, 60, 22);

	artist.changeRendererColor(112, 112, 112);
	artist.drawRectangle(206, 261, 22, 22);
	artist.drawLetters("S", 207, 262, Artist::smallFont);

	artist.drawRectangle(235, 261, 22, 22);
	artist.drawLetters("E", 236, 262, Artist::smallFont);

	artist.drawRectangle(264, 261, 22, 22);
	artist.drawLetters("L", 265, 262, Artist::smallFont);

	artist.drawLetters(std::to_string(palette[selectedColorIndex].r), 5, 262, Artist::smallFont);
	artist.drawLetters(std::to_string(palette[selectedColorIndex].g), 70, 262, Artist::smallFont);
	artist.drawLetters(std::to_string(palette[selectedColorIndex].b), 135, 262, Artist::smallFont);
}

void Canvas::changePixel(int x, int y, int r, int g, int b)
{
	canvas[x][y].r = r;
	canvas[x][y].g = g;
	canvas[x][y].b = b;
}

void Canvas::control(int input)
{
	//Left Mouse Click
	if (input == 1)
	{
		if (Controller::mouseX / 8 < canvas.size() && Controller::mouseY / 8 < canvas.size())
		{
			changePixel(Controller::mouseX / 8, Controller::mouseY / 8, palette[selectedColorIndex].r, palette[selectedColorIndex].g, palette[selectedColorIndex].b);
		}
	}
	//keyboard
	if (input == 3)
	{
		const Uint8 *state = SDL_GetKeyboardState(NULL);
		if (state[SDL_SCANCODE_RETURN])
		{
			if (bottemMenuIndex == 3)
			{
				FileIO fileIO;
				fileIO.SaveImage();
			}
			if (bottemMenuIndex == 4)
			{
				FileIO fileIO;
				fileIO.ExportImage();
			}
			if (bottemMenuIndex == 5)
			{
				FileIO fileIO;
				fileIO.LoadImage();
			}
		}
		if (state[SDL_SCANCODE_LSHIFT])
		{
			if (changingColor)
			{
				changingColor = false;
			}
			else
			{
				changingColor = true;
			}
		}
		if (!changingColor)
		{
			if (state[SDL_SCANCODE_RIGHT])
			{
				selectedColorIndex += 1;
			}
			if (state[SDL_SCANCODE_LEFT])
			{
				selectedColorIndex -= 1;
			}
			if (state[SDL_SCANCODE_UP])
			{
				selectedColorIndex -= 3;
			}
			if (state[SDL_SCANCODE_DOWN])
			{
				selectedColorIndex += 3;
			}
			if (selectedColorIndex < 0)
			{
				selectedColorIndex += 16;
			}
			if (selectedColorIndex >= 16)
			{
				selectedColorIndex -= 16;
			}
		}
		if (changingColor)
		{
			if (state[SDL_SCANCODE_RIGHT])
			{
				bottemMenuIndex += 1;
			}
			if (state[SDL_SCANCODE_LEFT])
			{
				bottemMenuIndex -= 1;
			}
			if (bottemMenuIndex < 0)
			{
				bottemMenuIndex = 5;
			}
			if (bottemMenuIndex > 5)
			{
				bottemMenuIndex = 0;
			}

			if (state[SDL_SCANCODE_UP])
			{
				switch (bottemMenuIndex)
				{
				case 0:
					palette[selectedColorIndex].r += 1;
					break;
				case 1:
					palette[selectedColorIndex].g += 1;
					break;
				case 2:
					palette[selectedColorIndex].b += 1;
					break;
				}
			}
			if (state[SDL_SCANCODE_DOWN])
			{
				switch (bottemMenuIndex)
				{
				case 0:
					palette[selectedColorIndex].r -= 1;
					break;
				case 1:
					palette[selectedColorIndex].g -= 1;
					break;
				case 2:
					palette[selectedColorIndex].b -= 1;
					break;
				}
			}
			
			if (palette[selectedColorIndex].r < 0)
			{
				palette[selectedColorIndex].r += 256;
			}
			if (palette[selectedColorIndex].r > 255)
			{
				palette[selectedColorIndex].r -= 256;
			}
			if (palette[selectedColorIndex].g < 0)
			{
				palette[selectedColorIndex].g += 256;
			}
			if (palette[selectedColorIndex].g > 255)
			{
				palette[selectedColorIndex].g -= 256;
			}
			if (palette[selectedColorIndex].b < 0)
			{
				palette[selectedColorIndex].b += 256;
			}
			if (palette[selectedColorIndex].b > 255)
			{
				palette[selectedColorIndex].b -= 256;
			}
		}
		if (state[SDL_SCANCODE_G])
		{
			if (drawGrid)
			{
				drawGrid = false;
			}
			else
			{
				drawGrid = true;
			}
		}
	}
	//left drag
	if (input == 11)
	{
		if (Controller::mouseX / 8 < canvas.size() && Controller::mouseY / 8 < canvas.size())
		{
			changePixel(Controller::mouseX / 8, Controller::mouseY / 8, palette[selectedColorIndex].r, palette[selectedColorIndex].g, palette[selectedColorIndex].b);
		}
	}
}

void Canvas::draw()
{
	drawHud();
	drawCanvas();
	
}