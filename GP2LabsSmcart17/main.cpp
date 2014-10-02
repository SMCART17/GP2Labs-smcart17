//Header files
#include <iostream>
#include <SDL.h>
#include <SDL_opengl.h>
#include <gl\GLU.h>

using namespace std;

//Pointer to our SDL Windows
SDL_Window *window;

//Constants to control window creation
const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;
bool running = true;

//SDL GL Context
SDL_GLContext glcontext = NULL;

//Global functions
void InitWindow(int width, int height, bool fullscreen)
{
	// Create Window
	window = SDL_CreateWindow(
		"Lab 1",
		SDL_WINDOWPOS_CENTERED,     //x position, centered
		SDL_WINDOWPOS_CENTERED,    //y position, centered
		width,  //width, in pixels
		height, //height, in pixels
		SDL_WINDOW_OPENGL //flags
		);
}

void CleanUp()
{
	// used to clean up once we exit
	SDL_DestroyWindow(window);
	SDL_Quit();
}

//Function to initialise OpenGL
void initOpenGL()
{
	//Create OPenGL Context
	glcontext = SDL_GL_CreateContext(window);
	//Something went wrong in creating the context, if it is still NULL
	if (!glcontext)
	{
		cout << "Error Creating OpenGL Context" << SDL_GetError() << endl;
	}

	//Smooth shading
	glShadeModel(GL_SMOOTH);

	//clear the background to black
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	//Clear the depth buffer to 1.0
	glClearDepth(1.0f);

	//Enable depth testing
	glEnable(GL_DEPTH_TEST);

	//The depth test to use
	glDepthFunc(GL_LEQUAL);

	//Turn on best perspective correction
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

//Function to set/reset viewport
void setViewport(int width, int height)
{

}





//Main Method - Entry Point
int main(int argc, char* arg[])
{
	//init everything - SDL, if it is nonzero we have a problem
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		cout << "ERROR SDL_Init" << SDL_GetError() << endl;

		return -1;
	}
	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, false);

	SDL_Event event;

	while (running)
	{
		while (SDL_PollEvent(&event))
		{
			// Get event type
			if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE)
			{
				running = false;
			}
		}
	}


	CleanUp();

	return 0;
}

