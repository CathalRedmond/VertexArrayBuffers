#include <Game.h>

static bool flip;

Game::Game() : window(sf::VideoMode(800, 600), "OpenGL Cube VBO")
{
	cubeVertexPosition[0] = Vector3D(0.25, 0.25, 0.0);
	cubeVertexPosition[1] = Vector3D(-0.25, 0.25, 0.0);
	cubeVertexPosition[2] = Vector3D(-0.25, -0.25, 0.0);
	cubeVertexPosition[3] = Vector3D(0.25, -0.25, 0.0);
	cubeVertexPosition[4] = Vector3D(0.25, 0.25, 0.5);
	cubeVertexPosition[5] = Vector3D(-0.25, 0.25, 0.5);
	cubeVertexPosition[6] = Vector3D(-0.25, -0.25, 0.5);
	cubeVertexPosition[7] = Vector3D(0.25, -0.25, 0.5);

	colours[RED] = Vector3D(1.0f,0.0f, 0.0f);
	colours[BLUE] = Vector3D(0.0f, 0.0f, 1.0f);
	colours[GREEN] = Vector3D(0.0f, 1.0f, 0.0f);
	colours[YELLOW] = Vector3D(1.0f, 1.0f, 0.0f);
	colours[CYAN] = Vector3D(0.0f, 1.0f, 1.0f);
	colours[MAGENTA] = Vector3D(1.0f, 0.0f, 1.0f);

}

Game::~Game() {}

void Game::run()
{

	initialize();

	sf::Event event;

	while (isRunning) {


		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				isRunning = false;
			}
			if (event.type == sf::Event::KeyPressed)
			{
				switch (event.key.code)
				{
				case sf::Keyboard::W:
					m_matrix = m_matrix.translate(0.1, 0.0);
					transform = true;
					break;
				case sf::Keyboard::S:
					m_matrix = m_matrix.translate(0.0, 0.1);
					transform = true;
					break;
				case sf::Keyboard::A:
					m_matrix = m_matrix.translate(0.1, 0.0);
					transform = true;
					break;
				case sf::Keyboard::D:
					m_matrix = m_matrix.translate(-0.1, 0.0);
					transform = true;
					break;
				case sf::Keyboard::Z:
					m_matrix = m_matrix.rotationZ(2);
					transform = true;
					break;
				case sf::Keyboard::X:
					m_matrix = m_matrix.rotationZ(-2);
					transform = true;
					break;
				case sf::Keyboard::C:
					m_matrix = m_matrix.rotationY(2);
					transform = true;
					break;
				case sf::Keyboard::V:
					m_matrix = m_matrix.rotationY(-2);
					transform = true;
					break;
				case sf::Keyboard::B:
					m_matrix = m_matrix.rotationX(2);
					transform = true;
					break;
				case sf::Keyboard::N:
					m_matrix = m_matrix.rotationX(-2);
					transform = true;
					break;
				case sf::Keyboard::F:
					m_matrix = m_matrix.scale(110, 110);
					transform = true;
					break;
				case sf::Keyboard::G:
					m_matrix = m_matrix.scale(90, 90);
					transform = true;
					break;
				default:
					break;
				}
			}
		}
		update();
		render();
	}

}

typedef struct
{
	float coordinate[3];
	float color[3];
} Vertex;

Vertex vertex[36];
GLubyte triangles[36];

/* Variable to hold the VBO identifier */
GLuint vbo[1];
GLuint index;

void Game::initialize()
{
	isRunning = true;
	
	glewInit();

	/*glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, window.getSize().x / window.getSize().y, 1.0, 500.0);
	glMatrixMode(GL_MODELVIEW);
	glTranslatef(0.0f,0.0f,-10.f);*/

	/* Vertices counter-clockwise winding */

	setVertexsPosition();

	


	// colors


	vertex[0].color[0] = colours[RED].Xf();
	vertex[0].color[1] = colours[RED].Yf();
	vertex[0].color[2] = colours[RED].Zf();

	vertex[1].color[0] = colours[RED].Xf();
	vertex[1].color[1] = colours[RED].Yf();
	vertex[1].color[2] = colours[RED].Zf();

	vertex[2].color[0] = colours[RED].Xf();
	vertex[2].color[1] = colours[RED].Yf();
	vertex[2].color[2] = colours[RED].Zf();

	vertex[3].color[0] = colours[RED].Xf();
	vertex[3].color[1] = colours[RED].Yf();
	vertex[3].color[2] = colours[RED].Zf();

	vertex[4].color[0] = colours[RED].Xf();
	vertex[4].color[1] = colours[RED].Yf();
	vertex[4].color[2] = colours[RED].Zf();

	vertex[5].color[0] = colours[RED].Xf();
	vertex[5].color[1] = colours[RED].Yf();
	vertex[5].color[2] = colours[RED].Zf();

	vertex[6].color[0] = colours[BLUE].Xf();
	vertex[6].color[1] = colours[BLUE].Yf();
	vertex[6].color[2] = colours[BLUE].Zf();

	vertex[7].color[0] = colours[BLUE].Xf();
	vertex[7].color[1] = colours[BLUE].Yf();
	vertex[7].color[2] = colours[BLUE].Zf();

	vertex[8].color[0] = colours[BLUE].Xf();
	vertex[8].color[1] = colours[BLUE].Yf();
	vertex[8].color[2] = colours[BLUE].Zf();

	vertex[9].color[0] = colours[BLUE].Xf();
	vertex[9].color[1] = colours[BLUE].Yf();
	vertex[9].color[2] = colours[BLUE].Zf();

	vertex[10].color[0] = colours[BLUE].Xf();
	vertex[10].color[1] = colours[BLUE].Yf();
	vertex[10].color[2] = colours[BLUE].Zf();

	vertex[11].color[0] = colours[BLUE].Xf();
	vertex[11].color[1] = colours[BLUE].Yf();
	vertex[11].color[2] = colours[BLUE].Zf();

	vertex[12].color[0] = colours[GREEN].Xf();
	vertex[12].color[1] = colours[GREEN].Yf();
	vertex[12].color[2] = colours[GREEN].Zf();

	vertex[13].color[0] = colours[GREEN].Xf();
	vertex[13].color[1] = colours[GREEN].Yf();
	vertex[13].color[2] = colours[GREEN].Zf();

	vertex[14].color[0] = colours[GREEN].Xf();
	vertex[14].color[1] = colours[GREEN].Yf();
	vertex[14].color[2] = colours[GREEN].Zf();

	vertex[15].color[0] = colours[GREEN].Xf();
	vertex[15].color[1] = colours[GREEN].Yf();
	vertex[15].color[2] = colours[GREEN].Zf();

	vertex[16].color[0] = colours[GREEN].Xf();
	vertex[16].color[1] = colours[GREEN].Yf();
	vertex[16].color[2] = colours[GREEN].Zf();

	vertex[17].color[0] = colours[GREEN].Xf();
	vertex[17].color[1] = colours[GREEN].Yf();
	vertex[17].color[2] = colours[GREEN].Zf();

	vertex[18].color[0] = colours[YELLOW].Xf();
	vertex[18].color[1] = colours[YELLOW].Yf();
	vertex[18].color[2] = colours[YELLOW].Zf();

	vertex[19].color[0] = colours[YELLOW].Xf();
	vertex[19].color[1] = colours[YELLOW].Yf();
	vertex[19].color[2] = colours[YELLOW].Zf();

	vertex[20].color[0] = colours[YELLOW].Xf();
	vertex[20].color[1] = colours[YELLOW].Yf();
	vertex[20].color[2] = colours[YELLOW].Zf();

	vertex[21].color[0] = colours[YELLOW].Xf();
	vertex[21].color[1] = colours[YELLOW].Yf();
	vertex[21].color[2] = colours[YELLOW].Zf();

	vertex[22].color[0] = colours[YELLOW].Xf();
	vertex[22].color[1] = colours[YELLOW].Yf();
	vertex[22].color[2] = colours[YELLOW].Zf();

	vertex[23].color[0] = colours[YELLOW].Xf();
	vertex[23].color[1] = colours[YELLOW].Yf();
	vertex[23].color[2] = colours[YELLOW].Zf();

	vertex[24].color[0] = colours[CYAN].Xf();
	vertex[24].color[1] = colours[CYAN].Yf();
	vertex[24].color[2] = colours[CYAN].Zf();

	vertex[25].color[0] = colours[CYAN].Xf();
	vertex[25].color[1] = colours[CYAN].Yf();
	vertex[25].color[2] = colours[CYAN].Zf();

	vertex[26].color[0] = colours[CYAN].Xf();
	vertex[26].color[1] = colours[CYAN].Yf();
	vertex[26].color[2] = colours[CYAN].Zf();

	vertex[27].color[0] = colours[CYAN].Xf();
	vertex[27].color[1] = colours[CYAN].Yf();
	vertex[27].color[2] = colours[CYAN].Zf();

	vertex[28].color[0] = colours[CYAN].Xf();
	vertex[28].color[1] = colours[CYAN].Yf();
	vertex[28].color[2] = colours[CYAN].Zf();

	vertex[29].color[0] = colours[CYAN].Xf();
	vertex[29].color[1] = colours[CYAN].Yf();
	vertex[29].color[2] = colours[CYAN].Zf();

	vertex[30].color[0] = colours[MAGENTA].Xf();
	vertex[30].color[1] = colours[MAGENTA].Yf();
	vertex[30].color[2] = colours[MAGENTA].Zf();

	vertex[31].color[0] = colours[MAGENTA].Xf();
	vertex[31].color[1] = colours[MAGENTA].Yf();
	vertex[31].color[2] = colours[MAGENTA].Zf();

	vertex[32].color[0] = colours[MAGENTA].Xf();
	vertex[32].color[1] = colours[MAGENTA].Yf();
	vertex[32].color[2] = colours[MAGENTA].Zf();

	vertex[33].color[0] = colours[MAGENTA].Xf();
	vertex[33].color[1] = colours[MAGENTA].Yf();
	vertex[33].color[2] = colours[MAGENTA].Zf();

	vertex[34].color[0] = colours[MAGENTA].Xf();
	vertex[34].color[1] = colours[MAGENTA].Yf();
	vertex[34].color[2] = colours[MAGENTA].Zf();

	vertex[35].color[0] = colours[MAGENTA].Xf();
	vertex[35].color[1] = colours[MAGENTA].Yf();
	vertex[35].color[2] = colours[MAGENTA].Zf();


	for(int index = 0; index < 36; index++)
	{
		triangles[index] = index;
	}
	

	/* Create a new VBO using VBO id */
	glGenBuffers(1, vbo);
	
	/* Bind the VBO */
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);

	/* Upload vertex data to GPU */
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 36, vertex, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &index);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLubyte) * 36, triangles, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Game::update()
{
	elapsed = clock.getElapsedTime();

	if (elapsed.asSeconds() >= 1.0f)
	{
		clock.restart();

		if (!flip)
		{
			flip = true;
		}
		else
			flip = false;
	}

	if (flip)
	{
		rotationAngle += 0.005f;

		if (rotationAngle > 360.0)
		{
			rotationAngle -= 360.0;
		}
	}


	Vector3D centre;
	for (int index = 0; index < 8; index++)
	{
		centre = centre + cubeVertexPosition[index];
	}
	centre = centre * (1 / 8.0);

	if (transform)
	{
		for (int index = 0; index < 8; index++)
		{
			cubeVertexPosition[index] = ((cubeVertexPosition[index] - centre) * m_matrix) + centre;
			setVertexsPosition();
		}
		transform = false;
	}

}

void Game::render()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index);

	/*	As the data positions will be updated by the this program on the
		CPU bind the updated data to the GPU for drawing	*/
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 36, vertex, GL_STATIC_DRAW);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);


	glColorPointer(3, GL_FLOAT, sizeof(Vertex), (char*)NULL + 12);

	/*	Draw Triangle from VBO	(set where to start from as VBO can contain 
		model compoents that are and are not to be drawn )	*/
	glVertexPointer(3, GL_FLOAT, sizeof(Vertex), (char*)NULL + 0);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, (char*)NULL + 0);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);

	window.display();

}

void Game::unload()
{

	glDeleteBuffers(1, vbo);
}

void Game::setVertexsPosition()
{
	vertex[0].coordinate[0] = cubeVertexPosition[0].Xf();
	vertex[0].coordinate[1] = cubeVertexPosition[0].Yf();
	vertex[0].coordinate[2] = cubeVertexPosition[0].Zf();

	vertex[1].coordinate[0] = cubeVertexPosition[1].Xf();
	vertex[1].coordinate[1] = cubeVertexPosition[1].Yf();
	vertex[1].coordinate[2] = cubeVertexPosition[1].Zf();

	vertex[2].coordinate[0] = cubeVertexPosition[2].Xf();
	vertex[2].coordinate[1] = cubeVertexPosition[2].Yf();
	vertex[2].coordinate[2] = cubeVertexPosition[2].Zf();

	vertex[3].coordinate[0] = cubeVertexPosition[0].Xf();
	vertex[3].coordinate[1] = cubeVertexPosition[0].Yf();
	vertex[3].coordinate[2] = cubeVertexPosition[0].Zf();

	vertex[4].coordinate[0] = cubeVertexPosition[2].Xf();
	vertex[4].coordinate[1] = cubeVertexPosition[2].Yf();
	vertex[4].coordinate[2] = cubeVertexPosition[2].Zf();

	vertex[5].coordinate[0] = cubeVertexPosition[3].Xf();
	vertex[5].coordinate[1] = cubeVertexPosition[3].Yf();
	vertex[5].coordinate[2] = cubeVertexPosition[3].Zf();

	vertex[6].coordinate[0] = cubeVertexPosition[4].Xf();
	vertex[6].coordinate[1] = cubeVertexPosition[4].Yf();
	vertex[6].coordinate[2] = cubeVertexPosition[4].Zf();

	vertex[7].coordinate[0] = cubeVertexPosition[5].Xf();
	vertex[7].coordinate[1] = cubeVertexPosition[5].Yf();
	vertex[7].coordinate[2] = cubeVertexPosition[5].Zf();

	vertex[8].coordinate[0] = cubeVertexPosition[6].Xf();
	vertex[8].coordinate[1] = cubeVertexPosition[6].Yf();
	vertex[8].coordinate[2] = cubeVertexPosition[6].Zf();

	vertex[9].coordinate[0] = cubeVertexPosition[4].Xf();
	vertex[9].coordinate[1] = cubeVertexPosition[4].Yf();
	vertex[9].coordinate[2] = cubeVertexPosition[4].Zf();

	vertex[10].coordinate[0] = cubeVertexPosition[6].Xf();
	vertex[10].coordinate[1] = cubeVertexPosition[6].Yf();
	vertex[10].coordinate[2] = cubeVertexPosition[6].Zf();

	vertex[11].coordinate[0] = cubeVertexPosition[7].Xf();
	vertex[11].coordinate[1] = cubeVertexPosition[7].Yf();
	vertex[11].coordinate[2] = cubeVertexPosition[7].Zf();

	vertex[12].coordinate[0] = cubeVertexPosition[1].Xf();
	vertex[12].coordinate[1] = cubeVertexPosition[1].Yf();
	vertex[12].coordinate[2] = cubeVertexPosition[1].Zf();

	vertex[13].coordinate[0] = cubeVertexPosition[2].Xf();
	vertex[13].coordinate[1] = cubeVertexPosition[2].Yf();
	vertex[13].coordinate[2] = cubeVertexPosition[2].Zf();

	vertex[14].coordinate[0] = cubeVertexPosition[5].Xf();
	vertex[14].coordinate[1] = cubeVertexPosition[5].Yf();
	vertex[14].coordinate[2] = cubeVertexPosition[5].Zf();

	vertex[15].coordinate[0] = cubeVertexPosition[2].Xf();
	vertex[15].coordinate[1] = cubeVertexPosition[2].Yf();
	vertex[15].coordinate[2] = cubeVertexPosition[2].Zf();

	vertex[16].coordinate[0] = cubeVertexPosition[5].Xf();
	vertex[16].coordinate[1] = cubeVertexPosition[5].Yf();
	vertex[16].coordinate[2] = cubeVertexPosition[5].Zf();

	vertex[17].coordinate[0] = cubeVertexPosition[6].Xf();
	vertex[17].coordinate[1] = cubeVertexPosition[6].Yf();
	vertex[17].coordinate[2] = cubeVertexPosition[6].Zf();

	vertex[18].coordinate[0] = cubeVertexPosition[0].Xf();
	vertex[18].coordinate[1] = cubeVertexPosition[0].Yf();
	vertex[18].coordinate[2] = cubeVertexPosition[0].Zf();

	vertex[19].coordinate[0] = cubeVertexPosition[3].Xf();
	vertex[19].coordinate[1] = cubeVertexPosition[3].Yf();
	vertex[19].coordinate[2] = cubeVertexPosition[3].Zf();

	vertex[20].coordinate[0] = cubeVertexPosition[4].Xf();
	vertex[20].coordinate[1] = cubeVertexPosition[4].Yf();
	vertex[20].coordinate[2] = cubeVertexPosition[4].Zf();

	vertex[21].coordinate[0] = cubeVertexPosition[3].Xf();
	vertex[21].coordinate[1] = cubeVertexPosition[3].Yf();
	vertex[21].coordinate[2] = cubeVertexPosition[3].Zf();

	vertex[22].coordinate[0] = cubeVertexPosition[4].Xf();
	vertex[22].coordinate[1] = cubeVertexPosition[4].Yf();
	vertex[22].coordinate[2] = cubeVertexPosition[4].Zf();

	vertex[23].coordinate[0] = cubeVertexPosition[7].Xf();
	vertex[23].coordinate[1] = cubeVertexPosition[7].Yf();
	vertex[23].coordinate[2] = cubeVertexPosition[7].Zf();

	vertex[24].coordinate[0] = cubeVertexPosition[0].Xf();
	vertex[24].coordinate[1] = cubeVertexPosition[0].Yf();
	vertex[24].coordinate[2] = cubeVertexPosition[0].Zf();

	vertex[25].coordinate[0] = cubeVertexPosition[1].Xf();
	vertex[25].coordinate[1] = cubeVertexPosition[1].Yf();
	vertex[25].coordinate[2] = cubeVertexPosition[1].Zf();

	vertex[26].coordinate[0] = cubeVertexPosition[4].Xf();
	vertex[26].coordinate[1] = cubeVertexPosition[4].Yf();
	vertex[26].coordinate[2] = cubeVertexPosition[4].Zf();

	vertex[27].coordinate[0] = cubeVertexPosition[1].Xf();
	vertex[27].coordinate[1] = cubeVertexPosition[1].Yf();
	vertex[27].coordinate[2] = cubeVertexPosition[1].Zf();

	vertex[28].coordinate[0] = cubeVertexPosition[4].Xf();
	vertex[28].coordinate[1] = cubeVertexPosition[4].Yf();
	vertex[28].coordinate[2] = cubeVertexPosition[4].Zf();

	vertex[29].coordinate[0] = cubeVertexPosition[5].Xf();
	vertex[29].coordinate[1] = cubeVertexPosition[5].Yf();
	vertex[29].coordinate[2] = cubeVertexPosition[5].Zf();

	vertex[30].coordinate[0] = cubeVertexPosition[2].Xf();
	vertex[30].coordinate[1] = cubeVertexPosition[2].Yf();
	vertex[30].coordinate[2] = cubeVertexPosition[2].Zf();

	vertex[31].coordinate[0] = cubeVertexPosition[3].Xf();
	vertex[31].coordinate[1] = cubeVertexPosition[3].Yf();
	vertex[31].coordinate[2] = cubeVertexPosition[3].Zf();

	vertex[32].coordinate[0] = cubeVertexPosition[6].Xf();
	vertex[32].coordinate[1] = cubeVertexPosition[6].Yf();
	vertex[32].coordinate[2] = cubeVertexPosition[6].Zf();

	vertex[33].coordinate[0] = cubeVertexPosition[3].Xf();
	vertex[33].coordinate[1] = cubeVertexPosition[3].Yf();
	vertex[33].coordinate[2] = cubeVertexPosition[3].Zf();

	vertex[34].coordinate[0] = cubeVertexPosition[6].Xf();
	vertex[34].coordinate[1] = cubeVertexPosition[6].Yf();
	vertex[34].coordinate[2] = cubeVertexPosition[6].Zf();

	vertex[35].coordinate[0] = cubeVertexPosition[7].Xf();
	vertex[35].coordinate[1] = cubeVertexPosition[7].Yf();
	vertex[35].coordinate[2] = cubeVertexPosition[7].Zf();
}

