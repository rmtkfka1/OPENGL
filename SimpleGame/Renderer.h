#pragma once

#include <string>
#include <cstdlib>
#include <fstream>
#include <iostream>

#include "Dependencies\glew.h"

class Renderer
{
public:
	Renderer(int windowSizeX, int windowSizeY);
	~Renderer();

	bool IsInitialized();
	void ReloadAllShaders();
	void CompileAllShaders();
	void DeleteAllShaders();
	void DrawSolidRect(float x, float y, float z, float size, float r, float g, float b, float a);
	void DrawTestRect();
	void DrawParticle();
	void DrawWave();
	void DrawFs();
	void DrawFullScreenColor(float r, float g, float b, float a);
private:
	void Initialize(int windowSizeX, int windowSizeY);
	bool ReadFile(char* filename, std::string *target);
	void AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType);
	GLuint CompileShaders(char* filenameVS, char* filenameFS);
	void CreateVertexBufferObjects();
	void GetGLPosition(float x, float y, float *newX, float *newY);
	void GenerateParticles(int numParticle);
	void CreateGridMesh(int x, int y);

	bool m_Initialized = false;
	
	unsigned int m_WindowSizeX = 0;
	unsigned int m_WindowSizeY = 0;

	//GLuint m_VBORect = 0;
	
public:
	float m_time = 0;
private:

	GLuint m_SolidRectShader = 0;
	GLuint m_TestShader = 0;

	//Lecture2
	GLuint m_VBOTestPos=0;
	GLuint m_VBOTestColor = 0;


	//Particle System
	GLuint m_ParticleShader = 0;
	GLuint m_VBOParticle = 0;
	GLuint m_VBOParticleVertexCount = 0;

	//Wave
	GLuint m_GridMeshShader = 0;
	GLuint m_GridMeshVertexCount=0;
	GLuint m_GridMeshVBO = 0;

	//Full Screen 
	GLuint m_VBOFullScreen = 0;
	GLuint m_FullScreenShader = 0;

	//For Fragmentshader
	GLuint m_VBOFS = 0;
	GLuint m_FSShader = 0;

	float m_points[100*4];

	
};

