#include <iostream>
#include <GL/glew.h>
#include <GL/wglew.h>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <Vector3D.h>
#include <Matrix3D.h>


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

	void setVertexsPosition();
	void setVertexsColors();

	Vector3D cubeVertexPosition[8];
	Vector3D colours[6];

	const int RED = 0;
	const int BLUE = 1;
	const int GREEN = 2;
	const int YELLOW = 3;
	const int CYAN = 4;
	const int MAGENTA = 5;

	Matrix3D m_matrix;
	bool transform{ false };

	int coordinate_index[36] = { 0,1,2,  0,2,3,
							     4,5,6,  4,6,7,
								 1,2,5,  2,5,6,
								 0,3,4,  3,4,7,
								 0,1,4,  1,4,5,
								 2,3,6,  3,6,7 };
		
	int colour_index[36] = { RED,     RED,     RED,      RED,     RED,     RED,
							 BLUE,    BLUE,    BLUE,     BLUE,    BLUE,    BLUE,
							 GREEN,   GREEN,   GREEN,    GREEN,   GREEN,   GREEN,
							 YELLOW,  YELLOW,  YELLOW,   YELLOW,  YELLOW,  YELLOW,
							 CYAN,    CYAN,    CYAN,     CYAN,    CYAN,    CYAN,
							 MAGENTA, MAGENTA, MAGENTA,  MAGENTA, MAGENTA, MAGENTA };
};