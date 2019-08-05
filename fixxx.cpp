#include<stdio.h>
#include<stdlib.h>
#include<GL/glut.h>
#include<math.h>
#include<Box2D/Box2D.h>

/*
#include "imageloader.h"
GLuint texture[35];
int is_depth;
GLuint _textureId;

GLuint loadTexture(Image* image){
GLuint textureId;
glGenTextures(1, &textureId);
glBindTexture(GL_TEXTURE_2D, textureId);
glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,image -> width, image -> height, 0, GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
return textureId;
}

void Inisialisasi()
{
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	GLfloat ambientLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	GLfloat diffuseLight[] = { 0.8f, 0.8f, 0.8, 1.0f };

	GLfloat specularLight[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	GLfloat position[] = { 1.5f, 1.0f, 4.0f, 1.0f };

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
	glLightfv(GL_LIGHT0, GL_POSITION, position);

	glClearColor (1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION); 
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHT1);
	glEnable(GL_DEPTH_TEST);
	is_depth=1;
	Image* image = loadBMP("1.bmp");//ambil gambar bmp
	_textureId = loadTexture(image);
}

void tekstur(b2Vec2 lol[10])
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId);
	glTexParameteri(GL_TEXTURE_2D,
	GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,
	GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glColor3f(1.0f, 1.0f, 1.0f);

	glBegin(GL_QUADS);
	glTexCoord2f(1.0, 1.0f);

	for(int j = 0; j < 4; j++){									
		glTexCoord2f(lol[j].x, lol[j].y);
	}
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}
*/

const double PI = 3.14; // const = nilai tidak dapat diubah
const int size = 15; // const = nilai tidak dapat diubah
bool gravity = true; // isi ne 0 & 1 
b2World* world;

b2Body* addCircle(int x, int y, int radius, bool dyn)
{
	b2BodyDef bodydef;
	bodydef.position.Set(x, y);
	if(dyn)
	{
		bodydef.type = b2_dynamicBody;
	}

	b2Body* body = world->CreateBody(&bodydef);

	b2CircleShape shape;
	shape.m_radius=radius;
	shape.m_p.Set(0,0);

	b2FixtureDef fixturedef;
	fixturedef.shape=&shape;
	fixturedef.density=1.0;
	body->CreateFixture(&fixturedef);
	return body;
}

void drawCircle(b2Vec2 center, float radius, float angle)
{
	glColor3f(0.5, 0, 1);
	glPushMatrix();
	glTranslatef(center.x, center.y, 0);
	glRotatef(angle*180/PI, 0, 0, 1);

	glBegin(GL_LINE_LOOP);
		for(int i = 0; i <= 360; i++)
		{
			glVertex2f(cos(i*PI/180.0)*radius, (sin(i*PI/180.0)*radius));
		}
	glEnd();

	glPopMatrix();
}

b2Body* addRect(int x, int y, int z, int v, bool dyn)
{
	b2BodyDef bodydef;
	bodydef.position.Set(x, y);
	if(dyn)
	{
		bodydef.type = b2_dynamicBody;
	}
	b2Body* body = world->CreateBody(&bodydef);
	
	b2PolygonShape shape;
	shape.SetAsBox(z, v);

	b2FixtureDef fixturedef;
	fixturedef.shape=&shape;
	fixturedef.density=1.0;
	body->CreateFixture(&fixturedef);
	return body;
}

void drawRect(b2Vec2 points[10], b2Vec2 center, float angle)
{
	glColor3f(1, 0.2345, 0);
	glPushMatrix();
	glTranslatef(center.x, center.y, 0);
	glRotatef(angle*180.0/PI, 0, 0, 1);
	glBegin(GL_LINE_LOOP);
	for(int j = 0; j < 4; j++)
	{
		glVertex2f(points[j].x, points[j].y);
	}
	glEnd();
	glPopMatrix();
}

b2Body* addTriangle(int x, int y, bool dynamic)
{
	b2BodyDef bodydef; 
	bodydef.position.Set(x, y);
	if(dynamic)
	{
		bodydef.type = b2_dynamicBody;
	}
	b2Body* body = world->CreateBody(&bodydef);

	b2PolygonShape shape;

	b2Vec2 vert[3];

	b2Vec2 vertices[3];
	vertices[0].Set(-13.0f, 0.0f);
	vertices[1].Set(13.0f, 0.0f);
	vertices[2].Set(0.0f, 13.0f);
	
	int32 count = 3;
	shape.Set(vertices, count);

	b2FixtureDef fixturedef;
	fixturedef.shape=&shape;
	fixturedef.density=1.0;


	body->CreateFixture(&fixturedef);
	return body;
}


void drawTriangle(b2Vec2 points[3], b2Vec2 center, float angle)
{
	glColor3f(0, 0, 0);

	glPushMatrix();
	glTranslatef(center.x, center.y, 0);
	glRotatef(angle*180.0/PI, 0, 0, 1);

	glBegin(GL_LINE_LOOP);
	for(int a = 0; a < 3; a++)
	{
		glVertex2f(points[a].x, points[a].y);
	}


	glEnd();
	glPopMatrix();

	glBegin(GL_POINTS);
	glVertex2f(center.x, center.y);
	glEnd();
}


void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();


	b2Body* node = world->GetBodyList();
	b2Vec2 points[4];
	b2Vec2 trianglePoints[3];

	b2Color color(1, 1, 1);

	while(node)
	{
		if(node->GetFixtureList()->GetShape()->GetType() == b2Shape::e_circle)
		{
			b2CircleShape* circle = (b2CircleShape* ) node->GetFixtureList()->GetShape();
			drawCircle(node->GetWorldCenter(), circle->m_radius, node->GetAngle());
		} else 
		{
			int checkShape = ((b2PolygonShape*)node->GetFixtureList()->GetShape())->GetVertexCount();		

			if (checkShape == 3) 
			{
				for (int a = 0; a < 3; a++) 
				{
					trianglePoints[a] = ((b2PolygonShape*)node->GetFixtureList()->GetShape())->GetVertex(a);
				}
				drawTriangle(trianglePoints, node->GetWorldCenter(), node->GetAngle());		
			
			}
			if (checkShape == 4) 
			{
				for (int a = 0; a < 4; a++) 
				{
					points[a] = ((b2PolygonShape*)node->GetFixtureList()->GetShape())->GetVertex(a);
				}
				drawRect(points, node->GetWorldCenter(), node->GetAngle());				
			}
		}
		node = node->GetNext();
	}

	glutSwapBuffers();
}

void loop (int c)
{
	world->Step(0.05, 8, 3);
	glutPostRedisplay();
	glutTimerFunc(1, loop, 0);
}

void init(void)
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, 800.0, 0.0, 600.0);
	glMatrixMode(GL_MODELVIEW);
	glClearColor(1,1,1,1);
	world = new b2World(b2Vec2(0, -9.81));
	glColor3f(1.0, 1.0, 1.0);
	addRect(400, -5, 800, 10, false);
}

void keyboardFunc(unsigned char key, int x, int y)
{
	x = x;
	y = 600 - y;
	switch(key){
	case 'A':
	case 'a':
		addRect(x, y, size, size, true);
		break;
	case 'S':
	case 's':
		addCircle(x, y, size, true);
		break;
	case 'D':
	case 'd':
		addTriangle(x, y, true);
		break;
	case 'G':
	case 'g':
		if(gravity){
			glutTimerFunc(1, loop, 0);
			gravity = false;
		}
		break;
	}
	glutPostRedisplay();
}
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH);
	glMatrixMode(GL_PROJECTION);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(300 ,100);
	glutCreateWindow("TR_GRAFKOM_PENENTU");
	//Inisialisasi();
	init();
	glutDisplayFunc(display);
    glutKeyboardFunc(keyboardFunc);

	glutMainLoop();
	return 0;
}
