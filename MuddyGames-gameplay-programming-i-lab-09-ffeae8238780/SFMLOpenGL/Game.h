#include <iostream>
#include <GL/glew.h>
#include <GL/wglew.h>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>

#include <Vector3.h>
#include <MyMatrix3.h>

#include <stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

const int VERTICES = 24;	// Total Number of Vertices
class Game
{
public:
	Game();
	~Game();
	void run();
private:
	sf::Window window;
	bool isRunning = false;
	void initialize();
	void update();
	void render();
	void unload();

	sf::Clock clock;
	sf::Time elapsed;

	float rotationAngle = 0.0f;
};


//
//#ifndef GAME_H
//#define GAME_H
//
//#include <Debug.h>
//
//#include <iostream>
//#include <GL/glew.h>
//#include <GL/wglew.h>
//#include <SFML/Window.hpp>
//#include <SFML/OpenGL.hpp>
//
//#include <Vector3.h>
//#include <MyMatrix3.h>
//
//#define STB_IMAGE_IMPLEMENTATION
//#include <stb_image.h>
//
//using namespace std;
//using namespace sf;
//using namespace gpp;
//
//class Game
//{
//public:
//	Game();
//	~Game();
//	void run();
//private:
//	Window window;
//	bool isRunning = false;
//	void initialize();
//	void update();
//	void render();
//	void unload();
//
//	Clock clock;
//	Time elapsed;
//
//	float rotationAngle = 0.0f;
//};
//
//#endif