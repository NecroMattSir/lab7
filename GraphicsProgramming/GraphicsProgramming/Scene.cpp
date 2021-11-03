#include "Scene.h"

// Scene constructor, initilises OpenGL
// You should add further variables to need initilised.
Scene::Scene(Input* in) :
	camera(in)
{
	// Store pointer for input class
	input = in;
	initialiseOpenGL();

	// Other OpenGL / render setting should be applied here.
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	// Initialise scene variables
	isMouse = true;

	camera.SetPos(0, 5, 8);
	camera.SetRot(0, -30, 0);
	camera.SetIsMouse(&isMouse);

	rot = 0;

	p1rot = 0;
	p2rot = 0;
	p3rot = 0;
	p2m1rot = 0;
	p2m1m1rot = 0;
	p3m1rot = 0;
	p3m2rot = 0;


	tex1 = SOIL_load_OGL_texture(
		"gfx/crate.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB|
		SOIL_FLAG_COMPRESS_TO_DXT);

	tex2 = SOIL_load_OGL_texture(
		"gfx/checked.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB |
		SOIL_FLAG_COMPRESS_TO_DXT);

	skybox = SOIL_load_OGL_texture(
		"gfx/skybox.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB |
		SOIL_FLAG_COMPRESS_TO_DXT);

	//glBindTexture(GL_TEXTURE_2D, tex1);

	//glBindTexture(GL_TEXTURE_2D, tex2);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

void Scene::handleInput(float dt)
{
	camera.HandleInput(dt);

	// Handle user input
	if (input->isKeyDown('o'))
	{
		rot -= 15;
		input->setKeyUp('o');
	}

	if (input->isKeyDown('p'))
	{
		rot += 15;
		input->setKeyUp('p');
	}

	if (input->isKeyDown('i'))
	{
		isMouse = !isMouse;
		input->setKeyUp('i');
	}
}

void Scene::update(float dt)
{
	// update scene related variables.
	camera.Update(dt);

	//a
	rot += 10 * dt;
	p1rot += 10 * dt;
	p2rot += 15 * dt;
	p3rot += 5 * dt;

	//quad
	roty += 10 * dt;
	rotx += 30 * dt;
	rotz += 5 * dt;

	//solarsystem
	p2m1rot -= 40 * dt;
	p2m1m1rot += 70 * dt;
	p3m1rot += 50 * dt;
	p3m2rot += 80 * dt;

	// Calculate FPS for output
	calculateFPS();
}

void Scene::render() {




	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	// Reset transformations
	glLoadIdentity();
	glDisable(GL_TEXTURE_2D);
	// Set the camera
	gluLookAt(camera.GetPosX(), camera.GetPosY(), camera.GetPosZ(), camera.GetLAX(), camera.GetLAY(), camera.GetLAZ(), camera.GetUpX(), camera.GetUpY(), camera.GetUpZ());
	
	// Render geometry/scene here -------------------------------------
	
	//skybox
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_DEPTH_TEST);
	glBindTexture(GL_TEXTURE_2D, skybox);
	glPushMatrix();
	glTranslatef(camera.GetPosX(), camera.GetPosY(), camera.GetPosZ());
	glBegin(GL_QUADS);
	{
		glColor3f(1.0f, 1.0f, 1.0f);


		glNormal3f(0.0f, 0.0f, -1.0f);
		glTexCoord2f(1.0f, 0.5f);
		glVertex3f(-0.5f, -0.5f, 0.5f);
		glTexCoord2f(0.75f, 0.5f);
		glVertex3f(0.5f, -0.5f, 0.5f);
		glTexCoord2f(0.75f, 0.25f);
		glVertex3f(0.5f, 0.5f, 0.5f);
		glTexCoord2f(1.0f, 0.25f);
		glVertex3f(-0.5f, 0.5f, 0.5f);


		glNormal3f(-1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.75f, 0.5f);
		glVertex3f(0.5f, -0.5f, 0.5f);
		glTexCoord2f(0.5f, 0.5f);
		glVertex3f(0.5f, -0.5f, -0.5f);
		glTexCoord2f(0.5f, 0.25f);
		glVertex3f(0.5f, 0.5f, -0.5f);
		glTexCoord2f(0.75f, 0.25f);
		glVertex3f(0.5f, 0.5f, 0.5f);


		glNormal3f(0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.25f, 0.75f);
		glVertex3f(-0.5f, -0.5f, 0.5f);
		glTexCoord2f(0.25f, 0.5f);
		glVertex3f(-0.5f, -0.5f, -0.5f);
		glTexCoord2f(0.5f, 0.5f);
		glVertex3f(0.5f, -0.5f, -0.5f);
		glTexCoord2f(0.5f, 0.75f);
		glVertex3f(0.5f, -0.5f, 0.5f);

		glNormal3f(0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.5f, 0.25f);
		glVertex3f(0.5f, 0.5f, -0.5f);
		glTexCoord2f(0.25f, 0.25f);
		glVertex3f(-0.5f, 0.5f, -0.5f);
		glTexCoord2f(0.25f, 0.5f);
		glVertex3f(-0.5f, -0.5f, -0.5f);
		glTexCoord2f(0.5f, 0.5f);
		glVertex3f(0.5f, -0.5f, -0.5f);

		glNormal3f(1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.25f, 0.25f);
		glVertex3f(-0.5f, 0.5f, -0.5f);
		glTexCoord2f(0.0f, 0.25f);
		glVertex3f(-0.5f, 0.5f, 0.5f);
		glTexCoord2f(0.0f, 0.5f);
		glVertex3f(-0.5f, -0.5f, 0.5f);
		glTexCoord2f(0.25f, 0.5f);
		glVertex3f(-0.5f, -0.5f, -0.5f);

		glNormal3f(0.0f, -1.0f, 0.0f);
		glTexCoord2f(0.5f, 0.25f);
		glVertex3f(0.5f, 0.5f, -0.5f);
		glTexCoord2f(0.5f, 0.0f);
		glVertex3f(0.5f, 0.5f, 0.5f);
		glTexCoord2f(0.25f, 0.0f);
		glVertex3f(-0.5f, 0.5f, 0.5f);
		glTexCoord2f(0.25f, 0.25f);
		glVertex3f(-0.5f, 0.5f, -0.5f);
	}
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);



	//light
	GLfloat AmbientLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	GLfloat DiffuseLight[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, AmbientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, DiffuseLight);
	glEnable(GL_LIGHT0);


	GLfloat AmbientLight2[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	GLfloat PointCoords2[] = { 0.0f, 10.0f, 0.0f, 1.0f };
	GLfloat DiffuseLight2[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat Direction[] = { 0, -1, 0 };
	glLightfv(GL_LIGHT1, GL_DIFFUSE, DiffuseLight2);
	glLightfv(GL_LIGHT1, GL_POSITION, PointCoords2);
	glLightfv(GL_LIGHT1, GL_AMBIENT, AmbientLight2);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, Direction);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 25.0f);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 50.0f);
	glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 1.0f);
	glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.05f);
	glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.005f);
	glEnable(GL_LIGHT1);

	
	//sideplanes
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex2);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);
	for (float z = -90.0f; z < 10.f; z += 1.0f)
	{
		for (float y = -50.f; y < 50.f; y += 1.0f)
		{
			/*int temp = y + z;
			if (temp%2 == 0)
			{
				glColor3f(1.0f, 1.0f, 1.0f);
			}
			else
			{

				glColor3f(0.0f, 0.0f, 0.0f);
			}*/
			glNormal3f(1.0f, 0.0f, 0.0f);
			glTexCoord2f(y, z);
			glVertex3f(-10, y, z);
			glTexCoord2f(y, z+1);
			glVertex3f(-10, y, z+1);
			glTexCoord2f(y+1, z+1);
			glVertex3f(-10, y+1, z + 1.f);
			glTexCoord2f(y+1, z);
			glVertex3f(-10, y+1, z);
		}
	}
	glEnd();


	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBegin(GL_QUADS);
	for (float z = -90.0f; z < 10.f; z += 1.0f)
	{
		for (float y = -50.f; y < 50.f; y += 1.0f)
		{
			/*int temp = y + z;
			if (temp % 2 == 0)
			{
				glColor3f(1.0f, 1.0f, 1.0f);
			}
			else
			{

				glColor3f(0.0f, 0.0f, 0.0f);
			}*/
			glNormal3f(-1.0f, 0.0f, 0.0f);
			glTexCoord2f(y, z+1);
			glVertex3f(10, y, z+1);
			glTexCoord2f(y, z);
			glVertex3f(10, y, z);
			glTexCoord2f(y+1, z);
			glVertex3f(10, y + 1, z);
			glTexCoord2f(y+1, z+1);
			glVertex3f(10, y + 1, z+1);
		}
	}
	glEnd();

	glDisable(GL_TEXTURE_2D);


	//glPushMatrix();
	//glTranslatef(2, 1, -5);

	//glScalef(2, 0.5, 0);


	//glRotatef(rot, 0, 1, 0);


	////a (has a part in update)
	//glTranslatef(-2, 0, 0);
	//glRotatef(rot, 0, 0, -1);

	////b
	//glRotatef(rot, 0, 0, -1);
	//glTranslatef(1.5, 0, 0);
	//glRotatef(rot, 0, 0, 1);
	//glScalef(0.5, 0.5, 0);


	////triangle
	//glBegin(GL_TRIANGLES);
	//glColor3f(1.0f, 0.0f, 0.0f);
	//glVertex3f(0.0f, 1.0f, 0.0f);
	//glColor3f(0.0f, 1.0f, 0.0f);
	//glVertex3f(-1.0f, -1.0f, 0.0f);
	//glColor3f(0.0f, 0.0f, 1.0f);
	//glVertex3f(1.0f, -1.0f, 0.0f);
	//glEnd();

	////trianglemidpoint
	//glBegin(GL_TRIANGLES);
	//glColor3f(0.0f, 0.0f, 0.0f);
	//glVertex3f(0.0f, 0.02f, 0.0f);
	//glVertex3f(-0.02f, -0.02f, 0.0f);
	//glVertex3f(0.02f, -0.02f, 0.0f);
	//glEnd();

	//quad
	glPushMatrix();
	glTranslatef(-3, 1, 0);
	glRotatef(roty, 50, 20, 5);
	DrawCube();
	glPopMatrix();


	//solarsystem

	{
		glPushMatrix();
		glRotatef(90, 1, 0, 0);
		//sun
		glDisable(GL_LIGHTING);
		glColor3f(1.0f, 1.0f, 0.0f);
		gluSphere(gluNewQuadric(), 0.25, 100, 100);
		glEnable(GL_LIGHTING);

		//p1
		glPushMatrix();
		glRotatef(p1rot, 0, 0, 1);
		glTranslatef(0.7, 0, 0);
		glColor3f(0.8f, 0.0f, 0.0f);
		gluSphere(gluNewQuadric(), 0.05, 100, 100);
		glPopMatrix();

		//p2
		glPushMatrix();
		{
			glRotatef(p2rot, 0, 0, 1);
			glTranslatef(1.4, 0, 0);
			glColor3f(0.0f, 0.5f, 0.0f);
			gluSphere(gluNewQuadric(), 0.05, 100, 100);
			//m1
			glPushMatrix();
			{
				glRotatef(p2m1rot, 0, 0, 1);
				glTranslatef(0.2, 0, 0);
				glColor3f(0.2f, 0.1f, 0.3f);
				gluSphere(gluNewQuadric(), 0.025, 100, 100);
				//m1m1
				glPushMatrix();
				{
					glRotatef(p2m1m1rot, 0, 0, 1);
					glTranslatef(0.1, 0, 0);
					glColor3f(0.2f, 0.6f, 0.3f);
					gluSphere(gluNewQuadric(), 0.015, 100, 100);
				}
				glPopMatrix();
			}
			glPopMatrix();
		}
		glPopMatrix();

		//p3
		glPushMatrix();
		{
			glRotatef(p3rot, 0, 0, 1);
			glTranslatef(2.1, 0, 0);
			glColor3f(0.0f, 0.5f, 0.8f);
			gluSphere(gluNewQuadric(), 0.05, 100, 100);
			//m1
			glPushMatrix();
			{
				glRotatef(p3m1rot, 0, 0, 1);
				glTranslatef(0.2, 0, 0);
				glColor3f(0.8f, 0.1f, 0.6f);
				gluSphere(gluNewQuadric(), 0.025, 100, 100);
			}
			glPopMatrix();
			//m2
			glPushMatrix();
			{
				glRotatef(p3m2rot, 1, 0, 0);
				glTranslatef(0, 0, 0.2);
				glColor3f(0.3f, 0.8f, 0.6f);
				gluSphere(gluNewQuadric(), 0.025, 100, 100);
			}
			glPopMatrix();
		}
		glPopMatrix();
		glPopMatrix();

	}

	//spheres
	GLfloat no_mat[] = { 0, 0, 0, 0 };
	GLfloat mat_ambient_color[] = { 0.2, 0, 0, 1 };
	GLfloat mat_red[] = { 1, 0, 0, 1 };
	GLfloat mat_metal[] = { 0.5, 0.5, 0.6, 1 };
	GLfloat mat_specular[] = { 0.75, 0.75, 0.75, 1 };
	GLfloat low_specular[] = { 0.05, 0.05, 0.05, 1 };
	GLfloat noshine = 0;
	GLfloat midshine = 50;
	GLfloat highshine = 100;
	GLfloat mat_emissiom[] = { 0.3, 0.2, 0.2, 0.0 };


	glDisable(GL_COLOR_MATERIAL);
	glPushMatrix();
	glTranslatef(0.0f, -3.0f, 0.0f);
	{
		glPushMatrix();
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_red);
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
		glMateriali(GL_FRONT, GL_SHININESS, 100);
		glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);

		gluSphere(gluNewQuadric(), 1.0f, 100, 100);

		glPopMatrix();
	}
	glPushMatrix();
	glTranslatef(2.0f, 0.0f, 0.0f); 
	{
		glPushMatrix();
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_red);
		glMaterialfv(GL_FRONT, GL_SPECULAR, low_specular);
		glMateriali(GL_FRONT, GL_SHININESS, 50);
		glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);

		gluSphere(gluNewQuadric(), 1.0f, 100, 100);

		glPopMatrix();
	}
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-2.0f, 0.0f, 0.0f);
	{
		glPushMatrix();
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_metal);
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
		glMateriali(GL_FRONT, GL_SHININESS, 5);
		glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);

		gluSphere(gluNewQuadric(), 1.0f, 100, 100);

		glPopMatrix();
	}
	glPopMatrix();
	glPopMatrix();

	glEnable(GL_COLOR_MATERIAL);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_red);
	glMaterialfv(GL_FRONT, GL_SPECULAR, low_specular);
	glMateriali(GL_FRONT, GL_SHININESS, 0);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	


	

	////midpoint
	//glPopMatrix();
	//glBegin(GL_TRIANGLES);
	//glColor3f(0.0f, 0.0f, 0.0f);
	//glVertex3f(0.0f, 0.02f, 0.0f);
	//glVertex3f(-0.02f, -0.02f, 0.0f);
	//glVertex3f(0.02f, -0.02f, 0.0f);
	//glEnd();



	//midplane
	glEnable(GL_BLEND);
	glColor4f(0.2f, 0.4f, 0.6f, 0.5);
	glBegin(GL_QUADS);
	for (float z = -10.0f; z < 10.f; z += 1.0f)
	{
		for (float x = -10.f; x < 10.f; x += 1.0f)
		{
			glNormal3f(0.0f, 1.0f, 0.0f);
			glVertex3f(x, -3, z);
			glNormal3f(0.0f, 1.0f, 0.0f);
			glVertex3f(x + 1.f, -3, z);
			glNormal3f(0.0f, 1.0f, 0.0f);
			glVertex3f(x + 1.f, -3, z + 1.f);
			glNormal3f(0.0f, 1.0f, 0.0f);
			glVertex3f(x, -3, z + 1.f);
		}
	}
	glEnd();
	glDisable(GL_BLEND);



	// End render geometry --------------------------------------

	// Render text, should be last object rendered.
	renderTextOutput();
	
	// Swap buffers, after all objects are rendered.
	glutSwapBuffers();
}

void Scene::initialiseOpenGL()
{
	//OpenGL settings
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.39f, 0.58f, 93.0f, 1.0f);			// Cornflour Blue Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glClearStencil(0);									// Clear stencil buffer
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
	glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, 1);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

// Handles the resize of the window. If the window changes size the perspective matrix requires re-calculation to match new window size.
void Scene::resize(int w, int h) 
{
	width = w;
	height = h;
	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;

	float ratio = (float)w / (float)h;
	fov = 45.0f;
	nearPlane = 0.1f;
	farPlane = 100.0f;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(fov, ratio, nearPlane, farPlane);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);

	camera.SetWindow(&width, &height);
}

// Calculates FPS
void Scene::calculateFPS()
{
	frame++;
	time = glutGet(GLUT_ELAPSED_TIME);

	if (time - timebase > 1000) {
		sprintf_s(fps, "FPS: %4.2f", frame*1000.0 / (time - timebase));
		timebase = time;
		frame = 0;
	}
}

// Compiles standard output text including FPS and current mouse position.
void Scene::renderTextOutput()
{
	// Render current mouse position and frames per second.
	sprintf_s(mouseText, "Mouse: %i, %i", input->getMouseX(), input->getMouseY());
	displayText(-1.f, 0.96f, 1.f, 0.f, 0.f, mouseText);
	displayText(-1.f, 0.90f, 1.f, 0.f, 0.f, fps);
}

// Renders text to screen. Must be called last in render function (before swap buffers)
void Scene::displayText(float x, float y, float r, float g, float b, char* string) {
	// Get Lenth of string
	int j = strlen(string);

	// Swap to 2D rendering
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, 5, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// Orthographic lookAt (along the z-axis).
	gluLookAt(0.0f, 0.0f, 10.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	// Set text colour and position.
	glColor3f(r, g, b);
	glRasterPos2f(x, y);
	// Render text.
	for (int i = 0; i < j; i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, string[i]);
	}
	// Reset colour to white.
	glColor3f(1.f, 1.f, 1.f);

	// Swap back to 3D rendering.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fov, ((float)width/(float)height), nearPlane, farPlane);
	glMatrixMode(GL_MODELVIEW);
}


void Scene::DrawCube()
{
	glEnable(GL_TEXTURE_2D); 
	glBindTexture(GL_TEXTURE_2D, tex1);
	glBegin(GL_QUADS);
	{
		glColor3f(1.0f, 1.0f, 1.0f);


		glNormal3f(0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-0.5f, 0.5f, 0.5f);
		glNormal3f(0.0f, 0.0f, 1.0f);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(0.5f, 0.5f, 0.5f);
		glNormal3f(0.0f, 0.0f, 1.0f);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(0.5f, -0.5f, 0.5f);
		glNormal3f(0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-0.5f, -0.5f, 0.5f);


		glNormal3f(1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(0.5f, 0.5f, 0.5f);
		glNormal3f(1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(0.5f, 0.5f, -0.5f);
		glNormal3f(1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(0.5f, -0.5f, -0.5f);
		glNormal3f(1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(0.5f, -0.5f, 0.5f);


		glNormal3f(0.0f, -1.0f, 0.0f);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(0.5f, -0.5f, 0.5f);
		glNormal3f(0.0f, -1.0f, 0.0f);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(0.5f, -0.5f, -0.5f);
		glNormal3f(0.0f, -1.0f, 0.0f);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(-0.5f, -0.5f, -0.5f);
		glNormal3f(0.0f, -1.0f, 0.0f);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-0.5f, -0.5f, 0.5f);

		glNormal3f(0.0f, 0.0f, -1.0f);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(0.5f, -0.5f, -0.5f);
		glNormal3f(0.0f, 0.0f, -1.0f);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(-0.5f, -0.5f,- 0.5f);
		glNormal3f(0.0f, 0.0f, -1.0f);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(-0.5f, 0.5f, -0.5f);
		glNormal3f(0.0f, 0.0f, -1.0f);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(0.5f, 0.5f, -0.5f);

		glNormal3f(-1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-0.5f, -0.5f, -0.5f);
		glNormal3f(-1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(-0.5f, -0.5f, 0.5f);
		glNormal3f(-1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(-0.5f, 0.5f, 0.5f);
		glNormal3f(-1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-0.5f, 0.5f, -0.5f);

		glNormal3f(0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-0.5f, 0.5f, -0.5f);
		glNormal3f(0.0f, 1.0f, 0.0f);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(-0.5f, 0.5f, 0.5f);
		glNormal3f(0.0f, 1.0f, 0.0f);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(0.5f, 0.5f, 0.5f);
		glNormal3f(0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(0.5f, 0.5f, -0.5f);
	}
	glEnd();
	glDisable(GL_TEXTURE_2D);
}
