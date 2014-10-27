//Header files
#include <iostream>
#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <gl\GLU.h>
#include "Vertex.h"

using namespace std;

GLuint triangleVBO;
GLuint triangleEBO;

//SDL GL Context
SDL_GLContext glcontext = NULL;

//Pointer to our SDL Windows
SDL_Window * window;

//Constants to control window creation
const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;
bool running = true;



Vertex triangleData[] = {

	//FRONT
		{ -0.5f, 0.5f, 0.5f,
		1.0f, 0.0f, 1.0f, 1.0f },// Top Left

		{ -0.5f, -0.5f, 0.5f,
		1.0f, 1.0f, 0.0f, 1.0f },// Bottom Left

		{ 0.5f, -0.5f, 0.5f,
		0.0f, 1.0f, 1.0f, 1.0f }, //Bottom Right

		{ 0.5f, 0.5f, 0.5f,
		1.0f, 0.0f, 1.0f, 1.0f },// Top Right

		{ -0.5f, 0.5f, 0.5f,
		1.0f, 0.0f, 1.0f, 1.0f },// Top Left

		{ 0.5f, -0.5f, 0.5f,
		0.0f, 1.0f, 1.0f, 1.0f }, //Bottom Right

		//BACK
		{ -0.5f, 0.5f, -0.5f,
		1.0f, 0.0f, 1.0f, 1.0f },// Top Left

		{ -0.5f, -0.5f, -0.5f,
		1.0f, 1.0f, 0.0f, 1.0f },// Bottom Left

		{ 0.5f, -0.5f, -0.5f,
		0.0f, 1.0f, 1.0f, 1.0f }, //Bottom Right

		{ 0.5f, 0.5f, -0.5f,
		1.0f, 0.0f, 1.0f, 1.0f },// Top Right

		{ -0.5f, 0.5f, -0.5f,
		1.0f, 0.0f, 1.0f, 1.0f },// Top Left

		{ 0.5f, -0.5f, -0.5f,
		0.0f, 1.0f, 1.0f, 1.0f }, //Bottom Right
};

		GLuint indices[] = {
			//front
			0, 1, 2,
			0, 3, 2,

			//left
			4, 5, 1,
			4, 1, 0,

			//right
			3, 7, 2,
			7, 6, 2,

			//bottom
			1, 5, 2,
			6, 2, 1,
			//top
			5, 0, 7,
			5, 7, 3,
			//back
			4, 5, 6,
			4, 7, 6

		};
/*
//TOP
{ -0.5f, 0.5f, -0.5f,
1.0f, 0.0f, 1.0f, 1.0f },// Top Left

{ -0.5f, 0.5f, 0.5f,
1.0f, 0.0f, 1.0f, 1.0f },// Bottom Left

{ 0.5f, 0.5f, 0.5f,
1.0f, 0.0f, 1.0f, 1.0f }, //Bottom Right

{ 0.5f, 0.5f, -0.5f,
1.0f, 0.0f, 1.0f, 1.0f },// Top Right

{ -0.5f, 0.5f, -0.5f,
1.0f, 0.0f, 1.0f, 1.0f },// Top Left

{ 0.5f, 0.5f, 0.5f,
1.0f, 0.0f, 1.0f, 1.0f } , //Bottom Right

//BOTTOM
{ -0.5f, -0.5f, -0.5f,
1.0f, 1.0f, 0.0f, 1.0f },// Top Left

{ -0.5f, -0.5f, 0.5f,
1.0f, 1.0f, 0.0f, 1.0f },// Bottom Left

{ 0.5f, -0.5f, 0.5f,
0.0f, 1.0f, 1.0f, 1.0f }, //Bottom Right

{ 0.5f, -0.5f, -0.5f,
0.0f, 1.0f, 1.0f, 1.0f },// Top Right

{ -0.5f, -0.5f, -0.5f,
1.0f, 1.0f, 0.0f, 1.0f },// Top Left

{ 0.5f, -0.5f, 0.5f,
0.0f, 1.0f, 1.0f, 1.0f }, //Bottom Right

// LEFT
{ -0.5f, 0.5f, -0.5f,
1.0f, 0.0f, 1.0f, 1.0f },// Top Left

{ -0.5f, -0.5f, -0.5f,
1.0f, 1.0f, 0.0f, 1.0f },// Bottom Left

{ -0.5f, -0.5f, 0.5f,
1.0f, 1.0f, 0.0f, 1.0f },// Bottom Right

{ -0.5f, 0.5f, 0.5f,
1.0f, 0.0f, 1.0f, 1.0f },// Top Right

{ -0.5f, 0.5f, -0.5f,
1.0f, 0.0f, 1.0f, 1.0f },// Top Left

{ -0.5f, -0.5f, 0.5f,
1.0f, 1.0f, 0.0f, 1.0f },// Bottom Right

// RIGHT
{ 0.5f, -0.5f, 0.5f,
1.0f, 0.0f, 1.0f, 1.0f },// Top Left

{ 0.5f, 0.5f, 0.5f,
1.0f, 1.0f, 0.0f, 1.0f },// Bottom Left

{ 0.5f, 0.5f, -0.5f,
1.0f, 1.0f, 0.0f, 1.0f },// Bottom Right

{ 0.5f, -0.5f, -0.5f,
1.0f, 0.0f, 1.0f, 1.0f },// Top Right

{ 0.5f, -0.5f, 0.5f,
1.0f, 0.0f, 1.0f, 1.0f },// Top Left

{ 0.5f, 0.5f, -0.5f,
1.0f, 1.0f, 0.0f, 1.0f },// Bottom Right 


};*/



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
	glDeleteBuffers(1, &triangleEBO);
	glDeleteBuffers(1, &triangleVBO);
	SDL_GL_DeleteContext(glcontext);
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

	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		/*Problem: glewInit failed, something is seriously wrong*/
		cout << "Error:" << glewGetErrorString(err) << endl;
	}
}

//Function to set/reset viewport
void setViewport(int width, int height)
{
	//screen ration
	GLfloat ratio;

	//make sure height is always above 0
	if (height == 0)
	{
		height = 1;
	}

	//calculate screen ration
	ratio = (GLfloat)width / (GLfloat)height;

	//Setup viewport
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);

	//Change to project matrix mode
	glMatrixMode(GL_PROJECTION);

	//Calculate perpestive matrix, using glu library functions
	gluPerspective(45.0f, ratio, 0.1f, 100.0f);

	//Switch to ModelView
	glMatrixMode(GL_MODELVIEW);

	//Reset using the Identity
	glLoadIdentity();
}

void initGeometry()
{
	//Create buffer
	glGenBuffers(1, &triangleVBO);

	//Make the new VBO active
	glBindBuffer(GL_ARRAY_BUFFER, triangleVBO);

	//Copy Vertex Data to VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangleData),
		triangleData, GL_STATIC_DRAW);

	//create buffer
	glGenBuffers(1, &triangleEBO);

	//Make the EBO active
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, triangleEBO);

	//Copy Index data to the EBO
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
		GL_STATIC_DRAW);
}

//Function to Draw
void render()
{
	//Set the clear colour(background)
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	//clear the colour and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Make the new VBO active. Repeat here as a sanity check
	glBindBuffer(GL_ARRAY_BUFFER, triangleVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, triangleEBO);

	//Establish its 3 coordinates per vertex with zero stride
	glVertexPointer(3, GL_FLOAT, sizeof(Vertex), NULL);

	//Establish array contains vertices
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	//Switch to ModelView
	glMatrixMode(GL_MODELVIEW);

	//each element of the array
	glColorPointer(4, GL_FLOAT, sizeof(Vertex), (void**)(3 * sizeof(float)));

	//Reset using the Identity Matrix
	glLoadIdentity();

	gluLookAt(0.0, 0.0, 0.0, 
		0.0, 0.0, -1.0f, 
		0.0, 1.0, 0.0);

	//Translate
	glTranslatef(-1.5f, -1.5f, -6.0f);

	//Actually draw the triangle
	glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(GLuint),
		GL_UNSIGNED_INT, 0);

	//required to swap the back and front buffer
	SDL_GL_SwapWindow(window);

}

//Function to update game state
void update()
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

	//Call our InitOpenGL Function
	initOpenGL();
	initGeometry();

	//Set our viewport
	setViewport(WINDOW_WIDTH, WINDOW_HEIGHT);

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
		update();
		render();
	}


	CleanUp();

	return 0;
}

