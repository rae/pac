#define _USE_MATH_DEFINES

#include <iostream>
#include <cmath>
#include <bitset>

#include "PacMan.h"
#include "Ghost.h"
#include "Wall.h"
#include "Map.h"
#include "Node.h"

PacMan* player;
static float rotation_angle = -M_PI;
static float rotation_delta = 0.0001;
static float x, y=0;
int oldTimeSinceStart = 0;

const char * mapData[] = {
	"#######",
	"#     #",
	"#  ####",
	"#     #",
	"#######"
};
const int mapRowCount = sizeof(mapData) / sizeof(mapData[0]);



void handleKeyPresses(unsigned char key, int x, int y)
{
	switch (key) {
		case 'w': player->holdingUp = true;		break;
		case 's': player->holdingDown = true;	break;
		case 'a': player->holdingLeft = true;	break;
		case 'd': player->holdingRight = true;	break;
		default: /* do nothing */				break;
	}
}

void handleKeyReleased(unsigned char key, int x, int y)
{
	switch (key) {
		case 'w': player->holdingUp = false;	break;
		case 's': player->holdingDown = false;	break;
		case 'a': player->holdingLeft = false;	break;
		case 'd': player->holdingRight = false;	break;
		// esc quits
		case '\e': exit(0);						break;
		default: /* do nothing */				break;
	}
}

void myDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//Ready to Draw
	glColor3f(1.0, 1.0, 0.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 0, 0.5, 0, 0, -1, 0, 1, 0);

	// draw ground
	glColor3f(1, 1, 1);
	glBegin(GL_QUADS);
	const float groundSize = .3;
	glVertex3f(groundSize, groundSize, 0);
	glVertex3f(-groundSize, groundSize, 0);
	glVertex3f(-groundSize, -groundSize, 0);
	glVertex3f(groundSize, -groundSize, 0);
	glEnd();

	player->setColor(1.0, 1.0, 0.0);
	player->render();
	unsigned long width = strlen(mapData[0]);

	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < mapRowCount; y++)
		{
			if (mapData[y][x] == '#')
			{
				// render new Wall
			}
			//else if (mapData[x][y] == ' ')
		}
	}

	Ghost g1 = Ghost(glm::mat4(1.0f), 0.1, 32);
	g1.setColor(1.0, 0.0, 0.0);
	g1.render();

	Wall leftWall = Wall(glm::translate(glm::mat4(1.0f), glm::vec3(-1.0, 0, 0)), 0.1, 2);
	Wall rightWall = Wall(glm::translate(glm::mat4(1.0f), glm::vec3(1.0, 0, 0)), 0.1, 2);
	Wall topWall = Wall(glm::translate(glm::mat4(1.0f), glm::vec3(0, 1.0, 0)), 2, 0.1);
	Wall botWall = Wall(glm::translate(glm::mat4(1.0f), glm::vec3(0, -1.0, 0)), 2, 0.1);
	leftWall.setColor(1.0, 1.0, 1.0);
	rightWall.setColor(1.0, 1.0, 1.0);
	topWall.setColor(1.0, 1.0, 1.0);
	botWall.setColor(1.0, 1.0, 1.0);
	leftWall.render();
	rightWall.render();
	topWall.render();
	botWall.render();

	glutSwapBuffers();
//	glFlush();
}


void myIdleFunc()
{
	if (fabs(rotation_angle + rotation_delta) > M_PI) {
		rotation_delta = -rotation_delta;
	}
	rotation_angle += rotation_delta;

	x += 0.0005;
	y -= 0.00025;

	int timeSinceStart = glutGet(GLUT_ELAPSED_TIME);
	int deltaTime = timeSinceStart - oldTimeSinceStart;
	oldTimeSinceStart = timeSinceStart;

	player->move(deltaTime / 1000.0f);

	glutPostRedisplay();
}

void genMap()
{
	Map * map = new Map;
	map->parseMap(mapData, mapRowCount);
	for (int y = 0; y<map->height; y++) {
		for (int x = 0; x<map->width; x++) {
			if (map->nodeAt(x, y)->canBePath) {
				std::cout << " ";
			}
			else {
				std::cout << "#";
			}
		}
		std::cout << std::endl;
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(900, 900);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("My First Application");

	glutDisplayFunc(myDisplay);
	glutIdleFunc(myIdleFunc);
	glClearColor(0.3, 0.2, 0.0, 0.0);

	glutKeyboardFunc(handleKeyPresses);
	glutKeyboardUpFunc(handleKeyReleased);

	player = new PacMan(glm::mat4(1.0f), 0.2);
	glutMainLoop();
	return 0;
}
