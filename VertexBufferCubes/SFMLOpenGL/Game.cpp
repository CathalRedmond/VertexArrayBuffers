#include <Game.h>

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
					m_matrix = m_matrix.translate(0.0, -0.1); 
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
					m_matrix = m_matrix.rotationZ(3);
					transform = true;
					break;
				case sf::Keyboard::X:
					m_matrix = m_matrix.rotationZ(-3);
					transform = true;
					break;
				case sf::Keyboard::C:
					m_matrix = m_matrix.rotationY(3);
					transform = true;
					break;
				case sf::Keyboard::V:
					m_matrix = m_matrix.rotationY(-3);
					transform = true;
					break;
				case sf::Keyboard::B:
					m_matrix = m_matrix.rotationX(3);
					transform = true;
					break;
				case sf::Keyboard::N:
					m_matrix = m_matrix.rotationX(-3);
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

	setVertexsPosition();
	setVertexsColors();

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
	if (transform)
	{
		Vector3D toCentre;
		for (int index = 0; index < 8; index++)
		{
			toCentre = toCentre + cubeVertexPosition[index];
		}

		toCentre = toCentre * (1.0 / 8.0);

		for (int index = 0; index < 8; index++)
		{
			cubeVertexPosition[index] = ((cubeVertexPosition[index] - toCentre) * m_matrix) + toCentre;
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


// function to set the vertexs co-ordinates
void Game::setVertexsPosition()
{
	for (int index = 0; index < 36; index++)
	{	
		vertex[index].coordinate[0] = cubeVertexPosition[coordinate_index[index]].Xf();
		vertex[index].coordinate[1] = cubeVertexPosition[coordinate_index[index]].Yf();
		vertex[index].coordinate[2] = cubeVertexPosition[coordinate_index[index]].Zf();
	}
}

// function to set the vertexs colours
void Game::setVertexsColors()
{
	for (int index = 0; index < 36; index++)
	{
		vertex[index].color[0] = colours[colour_index[index]].Xf();
		vertex[index].color[1] = colours[colour_index[index]].Yf();
		vertex[index].color[2] = colours[colour_index[index]].Zf();
	}
}

