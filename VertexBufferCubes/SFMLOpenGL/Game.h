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


};