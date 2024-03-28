#include "pch.h"
#include <iostream>
#include "Artist.h"
#include "Controller.h"
#include "Canvas.h"


int main(int argc, char* args[])
{
	//Declare Artist and controller
	Artist Artist;
	Controller Controller;
	Canvas canvas;

	//Start up SDL and create window
	if (!Artist.init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		//Load media
		if (!Artist.loadMedia())
		{
			printf("Failed to load media!\n");
		}
		else
		{
			canvas.resizeCanvas(32);
			canvas.resetCanvas();
			canvas.resizePalette(16);
			canvas.resetPalette();

			//While application is running
			while (!Controller::quit)
			{
				//Clear screen
				Artist.clearScreen();




				
				
				//Draw everything
				Artist.draw();

				//Checks for user input
				Controller.controller();




				//Update screen
				Artist.updateScreen();
			}
		}
	}

	//Free resources and close SDL
	Artist.close();


	
	return 0;
}

