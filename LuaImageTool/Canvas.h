#pragma once
#ifndef Artist
#include "Artist.h"
#endif
class Canvas {
public:
	void resizeCanvas(int size);
	void resetCanvas();
	void resizePalette(int size);
	void resetPalette();
	Artist::RGB getCanvasPixel(int x, int y);
	void drawCanvas();
	void drawHud();
	void changePixel(int x, int y, int r, int g, int b);
	void control(int input);
	void draw();

	static std::vector<Artist::RGB> palette;
};