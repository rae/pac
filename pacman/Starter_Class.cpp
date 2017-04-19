#define _USE_MATH_DEFINES

#include <iostream>
#include <cmath>
#include <bitset>
#include <glm/glm.hpp>
#include <glm/gtx/matrix_decompose.hpp>

using namespace glm;

#include "PacMan.h"
#include "Ghost.h"
#include "Wall.h"
#include "Map.h"
#include "Node.h"

static float rotation_angle = -M_PI;
static float rotation_delta = 0.0001;
static float x, y=0;
static Map * g_map = nullptr;
static Node ***map_nodes = nullptr;
int gLastTime = 0;

const char * mapData[] = {
	"#######",
	"#     #",
	"#  ####",
	"#     #",
	"#######"
};
const int mapRowCount = sizeof(mapData) / sizeof(mapData[0]);

const char *pacData[] = {
	//    123456789 123456789 1234567
	"############################", // 0
	"#            ##            #", // 1
	"# #### ##### ## ##### #### #", // 2
	"# #### ##### ## ##### #### #", // 3
	"# #### ##### ## ##### #### #", // 4
	"#     @  @                 #", // 5
	"# #### ## ######## ## #### #", // 6
	"# #### ## ######## ## #### #", // 7
	"#      ##    ##    ##      #", // 8
	"###### ##### ## ##### ######", // 9
	"###### ##### ## ##### ######", // 10
	"###### ##          ## ######", // 11
	"###### ## ######## ## ######", // 12
	"###### ## ######## ## ######", // 13
	"          ########          ", // 14
	"###### ## ######## ## ######", // 15
	"###### ## ######## ## ######", // 16
	"###### ##@         ## ######", // 17
	"###### ## ######## ## ######", // 18
	"###### ## ######## ## ######", // 19
	"#            ##            #", // 20
	"# #### ##### ## ##### #### #", // 21
	"# #### ##### ## ##### #### #", // 22
	"#   ##                ##   #", // 23
	"### ## ## ######## ## ## ###", // 24
	"### ## ## ######## ## ## ###", // 25
	"#      ##    ##    ##      #", // 26
	"# ########## ## ########## #", // 27
	"# ########## ## ########## #", // 28
	"#                          #", // 29
	"############################"  // 30
									//    123456789 123456789 1234567
};
const int pacRowCount = sizeof(pacData) / sizeof(pacData[0]);



void handleKeyPresses(unsigned char key, int x, int y)
{
	PacMan* player = Map::sharedMap()->pacMan;
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
	PacMan* player = Map::sharedMap()->pacMan;
	switch (key) {
		case 'w': player->holdingUp = false;	break;
		case 's': player->holdingDown = false;	break;
		case 'a': player->holdingLeft = false;	break;
		case 'd': player->holdingRight = false;	break;
		// esc quits
		case '\033': exit(0);						break;
		default: /* do nothing */				break;
	}
}

void myDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//Ready to Draw
	glColor3f(0, 0, 0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

#define WANT_GROUND 0

#if WANT_GROUND
	gluLookAt(0, 0, .1,		// eye
			  0, 0, 0,		// centre
			  0, 1, 0);		// up

	// draw ground
	float coords[] = { -0.5, -0.4, -0.3, -0.2, -0.1, 0, 0.1, 0.2, 0.3, 0.4, 0.5 };
	for(float z: coords) {
		glColor4f(.5+z*0.9, 0, 0, 0.25);
		glBegin(GL_QUADS);
		const float groundSize = .3;
		const float offset = z;
		glVertex3f(groundSize+offset, groundSize+offset, z);
		glVertex3f(-groundSize+offset, groundSize+offset, z);
		glVertex3f(-groundSize+offset, -groundSize+offset, z);
		glVertex3f(groundSize+offset, -groundSize+offset, z);
		glEnd();
	}
#endif

	//
	// draw map
	//
	if (g_map != nullptr) {
		g_map->render();
	}

	Ghost g2 = Ghost(1, 1);
	g2.setColor(1.0, 0.0, 0.0);
	g2.render();

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
	int deltaTime = timeSinceStart - gLastTime;
	gLastTime = timeSinceStart;

	g_map->update(deltaTime / 1000.0f);

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
	glClearColor(0, 0, 0, 0);

	glutKeyboardFunc(handleKeyPresses);
	glutKeyboardUpFunc(handleKeyReleased);
	g_map = new Map();
	g_map->parseMap(pacData, pacRowCount);
	
	glutMainLoop();
	return 0;
}
