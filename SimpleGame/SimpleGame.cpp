/*
Copyright 2022 Lee Taek Hee (Tech University of Korea)

This program is free software: you can redistribute it and/or modify
it under the terms of the What The Hell License. Do it plz.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY.
*/

#include "stdafx.h"
#include <iostream>
#include "Dependencies\glew.h"
#include "Dependencies\freeglut.h"
#include "Renderer.h"

Renderer *g_Renderer = NULL;
bool g_globalBool = false;

void RenderScene(void)
{
	g_Renderer->m_time += 0.016f;

	if (g_globalBool)
	{
		g_Renderer->ReloadAllShaders();
		g_globalBool = false;
	}


	glClear(GL_COLOR_BUFFER_BIT);
	/*g_Renderer->DrawFullScreenColor(0, 0, 0, 0.3f);*/


	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//g_Renderer->DrawFullScreenColor(0, 0, 0, 0.3f);
	// Renderer Test
	//g_Renderer->DrawSolidRect(0, 0, 0, 300, 1, 1, 1, 1);
	//g_Renderer->DrawTestRect();
	//g_Renderer->DrawParticle();
	g_Renderer->DrawWave();
	//g_Renderer->DrawFs();


	glutSwapBuffers();
}

void Idle(void)
{
	RenderScene();
}

void MouseInput(int button, int state, int x, int y)
{

}

void KeyInput(unsigned char key, int x, int y)
{
	switch (key)
	{
	case '1':
		g_globalBool = true;
		break;
	default:
		break;
	}

}

void SpecialKeyInput(int key, int x, int y)
{

}

int main(int argc, char **argv)
{
	// Initialize GL things
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(800, 800);
	glutCreateWindow("Game Software Engineering KPU");

	glewInit();
	if (glewIsSupported("GL_VERSION_3_0"))
	{
		std::cout << " GLEW Version is 3.0\n ";
	}
	else
	{
		std::cout << "GLEW 3.0 not supported\n ";
	}

	// Initialize Renderer
	g_Renderer = new Renderer(800, 800);
	if (!g_Renderer->IsInitialized())
	{
		std::cout << "Renderer could not be initialized.. \n";
	}

	glutDisplayFunc(RenderScene);
	glutIdleFunc(Idle);
	glutKeyboardFunc(KeyInput);
	glutMouseFunc(MouseInput);
	glutSpecialFunc(SpecialKeyInput);
	glutMainLoop();

	delete g_Renderer;

    return 0;
}

