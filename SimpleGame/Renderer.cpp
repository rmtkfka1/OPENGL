#include "stdafx.h"
#include "Renderer.h"

Renderer::Renderer(int windowSizeX, int windowSizeY)
{
	Initialize(windowSizeX, windowSizeY);
}


Renderer::~Renderer()
{
}

void Renderer::Initialize(int windowSizeX, int windowSizeY)
{
	//Set window size
	m_WindowSizeX = windowSizeX;
	m_WindowSizeY = windowSizeY;

	CompileAllShaders();
	CreateVertexBufferObjects();
	CreateGridMesh(50,50);
	GenerateParticles(1000);

	//glEnable(GL_CULL_FACE);       // 컬링 기능 켜기
	//glCullFace(GL_BACK);          // 어떤 면을 컬링할지 지정 (보통 BACK)
	//glFrontFace(GL_CCW);          // 앞면의 정점 순서 (반시계 방향이 기본)
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	m_Initialized = true;
	
}

bool Renderer::IsInitialized()
{
	return m_Initialized;
}

void Renderer::ReloadAllShaders()
{
	DeleteAllShaders();
	CompileAllShaders();
}

void Renderer::CompileAllShaders()
{
	m_SolidRectShader = CompileShaders("./Shaders/SolidRect.vs", "./Shaders/SolidRect.fs");
	m_TestShader = CompileShaders("./Shaders/SolidRectTest.vs", "./Shaders/SolidRectTest.fs");
	m_ParticleShader = CompileShaders("./Shaders/Particle.vs", "./Shaders/Particle.fs");
	m_GridMeshShader = CompileShaders("./Shaders/GridMesh.vs", "./Shaders/GridMesh.fs");
	m_FullScreenShader = CompileShaders("./Shaders/FullScreen.vs", "./Shaders/FullScreen.fs");

}

void Renderer::DeleteAllShaders()
{
	glDeleteShader(m_SolidRectShader);
	glDeleteShader(m_TestShader);
	glDeleteShader(m_ParticleShader);
	glDeleteShader(m_GridMeshShader);
	glDeleteShader(m_FullScreenShader);
}

void Renderer::CreateVertexBufferObjects()
{
	//float rect[]
	//	=
	//{
	//	-1.f / m_WindowSizeX, -1.f / m_WindowSizeY, 0.f, -1.f / m_WindowSizeX, 1.f / m_WindowSizeY, 0.f, 1.f / m_WindowSizeX, 1.f / m_WindowSizeY, 0.f, //Triangle1
	//	-1.f / m_WindowSizeX, -1.f / m_WindowSizeY, 0.f,  1.f / m_WindowSizeX, 1.f / m_WindowSizeY, 0.f, 1.f / m_WindowSizeX, -1.f / m_WindowSizeY, 0.f, //Triangle2
	//};

	//glGenBuffers(1, &m_VBORect);
	//glBindBuffer(GL_ARRAY_BUFFER, m_VBORect);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(rect), rect, GL_STATIC_DRAW);
							
							
	{						
		{
			float temp = 0.5f;
			float size = 0.1f;
			float rect[] =
			{
				(0 - temp) * size  , (0.f - temp) * size , (0.f - temp) * size, 0.5f,
				(1.f - temp) * size, (0.f - temp) * size, (0.f - temp) * size, 0.5f,
				(1.f - temp) * size, (1.f - temp) * size, (0.f - temp) * size, 0.5f,
				(0.f - temp) * size, (0.f - temp) * size, (0.f - temp) * size, 0.5f,
				(1.f - temp) * size, (1.f - temp) * size, (0.f - temp) * size, 0.5f,
				(0.f - temp) * size, (1.f - temp) * size, (0.f - temp) * size, 0.5f,

				(0 - temp)* size  , (0.f - temp)* size , (0.f - temp)* size, 1.0f,
				(1.f - temp)* size, (0.f - temp)* size, (0.f - temp)* size, 1.0f,
				(1.f - temp)* size, (1.f - temp)* size, (0.f - temp)* size, 1.0f,
				(0.f - temp)* size, (0.f - temp)* size, (0.f - temp)* size, 1.0f,
				(1.f - temp)* size, (1.f - temp)* size, (0.f - temp)* size, 1.0f,
				(0.f - temp)* size, (1.f - temp)* size, (0.f - temp)* size, 1.0f
			};

			glGenBuffers(1, &m_VBOTestPos);
			glBindBuffer(GL_ARRAY_BUFFER, m_VBOTestPos);
			glBufferData(GL_ARRAY_BUFFER, sizeof(rect), rect, GL_STATIC_DRAW);
		}

		{
			float color[] =
			{
				1.0f,0.0f,0.0f,1.0f,
				0.0f,1.0f,0.0f,1.0f,
				0.0f,0.0f,1.0f,1.0f, //Triangle1
				1.0f,0.0f,0.0f,1.0f,
				0.0f,1.0f,0.0f,1.0f,
				0.0f,0.0f,1.0f,1.0f,  //Triangle2


				1.0f,0.0f,0.0f,1.0f,
				0.0f,1.0f,0.0f,1.0f,
				0.0f,0.0f,1.0f,1.0f, //Triangle1
				1.0f,0.0f,0.0f,1.0f,
				0.0f,1.0f,0.0f,1.0f,
				0.0f,0.0f,1.0f,1.0f  //Triangle2
			};


			glGenBuffers(1, &m_VBOTestColor);
			glBindBuffer(GL_ARRAY_BUFFER, m_VBOTestColor);
			glBufferData(GL_ARRAY_BUFFER, sizeof(color), color, GL_STATIC_DRAW);
		}

	}



	float fullRect[]
		=
	{
		-1.f , -1.f , 0.f, -1.f , 1.f , 0.f, 1.f , 1.f , 0.f, //Triangle1
		-1.f , -1.f , 0.f,  1.f , 1.f , 0.f, 1.f , -1.f , 0.f, //Triangle2
	};

	glGenBuffers(1, &m_VBOFullScreen);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBOFullScreen);
	glBufferData(GL_ARRAY_BUFFER, sizeof(fullRect), fullRect, GL_STATIC_DRAW);



}

void Renderer::AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType)
{
	//쉐이더 오브젝트 생성
	GLuint ShaderObj = glCreateShader(ShaderType);

	if (ShaderObj == 0) {
		fprintf(stderr, "Error creating shader type %d\n", ShaderType);
	}

	const GLchar* p[1];
	p[0] = pShaderText;
	GLint Lengths[1];

	size_t slen = strlen(pShaderText);
	if (slen > INT_MAX) {
		// Handle error
	}
	GLint len = (GLint)slen;

	Lengths[0] = len;
	//쉐이더 코드를 쉐이더 오브젝트에 할당
	glShaderSource(ShaderObj, 1, p, Lengths);

	//할당된 쉐이더 코드를 컴파일
	glCompileShader(ShaderObj);

	GLint success;
	// ShaderObj 가 성공적으로 컴파일 되었는지 확인
	glGetShaderiv(ShaderObj, GL_COMPILE_STATUS, &success);
	if (!success) {
		GLchar InfoLog[1024];

		//OpenGL 의 shader log 데이터를 가져옴
		glGetShaderInfoLog(ShaderObj, 1024, NULL, InfoLog);
		fprintf(stderr, "Error compiling shader type %d: '%s'\n", ShaderType, InfoLog);
		printf("%s \n", pShaderText);
	}

	// ShaderProgram 에 attach!!
	glAttachShader(ShaderProgram, ShaderObj);
}

bool Renderer::ReadFile(char* filename, std::string *target)
{
	std::ifstream file(filename);
	if (file.fail())
	{
		std::cout << filename << " file loading failed.. \n";
		file.close();
		return false;
	}
	std::string line;
	while (getline(file, line)) {
		target->append(line.c_str());
		target->append("\n");
	}
	return true;
}

GLuint Renderer::CompileShaders(char* filenameVS, char* filenameFS)
{
	GLuint ShaderProgram = glCreateProgram(); //빈 쉐이더 프로그램 생성

	if (ShaderProgram == 0) { //쉐이더 프로그램이 만들어졌는지 확인
		fprintf(stderr, "Error creating shader program\n");
	}

	std::string vs, fs;

	//shader.vs 가 vs 안으로 로딩됨
	if (!ReadFile(filenameVS, &vs)) {
		printf("Error compiling vertex shader\n");
		return -1;
	};

	//shader.fs 가 fs 안으로 로딩됨
	if (!ReadFile(filenameFS, &fs)) {
		printf("Error compiling fragment shader\n");
		return -1;
	};

	// ShaderProgram 에 vs.c_str() 버텍스 쉐이더를 컴파일한 결과를 attach함
	AddShader(ShaderProgram, vs.c_str(), GL_VERTEX_SHADER);

	// ShaderProgram 에 fs.c_str() 프레그먼트 쉐이더를 컴파일한 결과를 attach함
	AddShader(ShaderProgram, fs.c_str(), GL_FRAGMENT_SHADER);

	GLint Success = 0;
	GLchar ErrorLog[1024] = { 0 };

	//Attach 완료된 shaderProgram 을 링킹함
	glLinkProgram(ShaderProgram);

	//링크가 성공했는지 확인
	glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &Success);

	if (Success == 0) {
		// shader program 로그를 받아옴
		glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
		std::cout << filenameVS << ", " << filenameFS << " Error linking shader program\n" << ErrorLog;
		return -1;
	}

	glValidateProgram(ShaderProgram);
	glGetProgramiv(ShaderProgram, GL_VALIDATE_STATUS, &Success);
	if (!Success) {
		glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
		std::cout << filenameVS << ", " << filenameFS << " Error validating shader program\n" << ErrorLog;
		return -1;
	}

	glUseProgram(ShaderProgram);
	std::cout << filenameVS << ", " << filenameFS << " Shader compiling is done.";

	return ShaderProgram;
}

void Renderer::DrawSolidRect(float x, float y, float z, float size, float r, float g, float b, float a)
{
	//float newX, newY;

	//GetGLPosition(x, y, &newX, &newY);

	////Program select
	//glUseProgram(m_SolidRectShader);

	//glUniform4f(glGetUniformLocation(m_SolidRectShader, "u_Trans"), newX, newY, 0, size);
	//glUniform4f(glGetUniformLocation(m_SolidRectShader, "u_Color"), r, g, b, a);

	//int attribPosition = glGetAttribLocation(m_SolidRectShader, "a_Position");
	//glEnableVertexAttribArray(attribPosition);
	//glBindBuffer(GL_ARRAY_BUFFER, m_VBOTestPos);
	//glVertexAttribPointer(attribPosition, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);

	//glDrawArrays(GL_TRIANGLES, 0, 6);

	//glDisableVertexAttribArray(attribPosition);

	//glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Renderer::DrawTestRect()
{

#define ShaderName m_ParticleShader

	glUseProgram(ShaderName);


	
	glUniform1f(glGetUniformLocation(ShaderName, "u_radius"), 0.5f);
	glUniform1f(glGetUniformLocation(ShaderName, "u_Time"), m_time);
	

	// Bind position attribute
	int attribPosition = glGetAttribLocation(ShaderName, "a_Position");
	glEnableVertexAttribArray(attribPosition);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBOTestPos);
	glVertexAttribPointer(attribPosition, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 4, 0);

	int attribRadius = glGetAttribLocation(ShaderName, "a_Radius");
	glEnableVertexAttribArray(attribRadius);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBOTestPos);
	glVertexAttribPointer(attribRadius, 1, GL_FLOAT, GL_FALSE, sizeof(float)*4 , (GLvoid*)(sizeof(float)*3));
	
	// Bind color attribute
	int attribColor = glGetAttribLocation(ShaderName, "a_Color");
	glEnableVertexAttribArray(attribColor);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBOTestColor);
	glVertexAttribPointer(attribColor, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 4, 0);

	// Draw 
	glDrawArrays(GL_TRIANGLES, 0, 6*2);

	// Cleanup
	glDisableVertexAttribArray(attribPosition);
	glDisableVertexAttribArray(attribColor);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}


void Renderer::CreateGridMesh(int x, int y)

{

	float basePosX = -0.5f;

	float basePosY = -0.5f;

	float targetPosX = 0.5f;

	float targetPosY = 0.5f;

	int pointCountX = x;

	int pointCountY = y;

	float width = targetPosX - basePosX;

	float height = targetPosY - basePosY;

	float* point = new float[pointCountX * pointCountY * 2];

	float* vertices = new float[(pointCountX - 1) * (pointCountY - 1) * 2 * 3 * 3];

	m_GridMeshVertexCount = (pointCountX - 1) * (pointCountY - 1) * 2 * 3;

	//Prepare points
	for (int x = 0; x < pointCountX; x++)

	{

		for (int y = 0; y < pointCountY; y++)

		{

			point[(y * pointCountX + x) * 2 + 0] = basePosX + width * (x / (float)(pointCountX - 1));

			point[(y * pointCountX + x) * 2 + 1] = basePosY + height * (y / (float)(pointCountY - 1));

		}

	}



	//Make triangles

	int vertIndex = 0;

	for (int x = 0; x < pointCountX - 1; x++)

	{

		for (int y = 0; y < pointCountY - 1; y++)

		{

			//Triangle part 1

			vertices[vertIndex] = point[(y * pointCountX + x) * 2 + 0];

			vertIndex++;

			vertices[vertIndex] = point[(y * pointCountX + x) * 2 + 1];

			vertIndex++;

			vertices[vertIndex] = 0.f;

			vertIndex++;

			vertices[vertIndex] = point[((y + 1) * pointCountX + (x + 1)) * 2 + 0];

			vertIndex++;

			vertices[vertIndex] = point[((y + 1) * pointCountX + (x + 1)) * 2 + 1];

			vertIndex++;

			vertices[vertIndex] = 0.f;

			vertIndex++;

			vertices[vertIndex] = point[((y + 1) * pointCountX + x) * 2 + 0];

			vertIndex++;

			vertices[vertIndex] = point[((y + 1) * pointCountX + x) * 2 + 1];

			vertIndex++;

			vertices[vertIndex] = 0.f;

			vertIndex++;



			//Triangle part 2

			vertices[vertIndex] = point[(y * pointCountX + x) * 2 + 0];

			vertIndex++;

			vertices[vertIndex] = point[(y * pointCountX + x) * 2 + 1];

			vertIndex++;

			vertices[vertIndex] = 0.f;

			vertIndex++;

			vertices[vertIndex] = point[(y * pointCountX + (x + 1)) * 2 + 0];

			vertIndex++;

			vertices[vertIndex] = point[(y * pointCountX + (x + 1)) * 2 + 1];

			vertIndex++;

			vertices[vertIndex] = 0.f;

			vertIndex++;

			vertices[vertIndex] = point[((y + 1) * pointCountX + (x + 1)) * 2 + 0];

			vertIndex++;

			vertices[vertIndex] = point[((y + 1) * pointCountX + (x + 1)) * 2 + 1];

			vertIndex++;

			vertices[vertIndex] = 0.f;

			vertIndex++;

		}

	}

	glGenBuffers(1, &m_GridMeshVBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_GridMeshVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * (pointCountX - 1) * (pointCountY - 1) * 2 * 3 * 3, vertices, GL_STATIC_DRAW);

	delete[] point;
	delete[] vertices;
}


void Renderer::DrawParticle()
{

#define ShaderName m_ParticleShader


	glUseProgram(ShaderName);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);



	glUniform1f(glGetUniformLocation(ShaderName, "u_radius"), 0.5f);
	glUniform1f(glGetUniformLocation(ShaderName, "u_Time"), m_time);
	glUniform3f(glGetUniformLocation(ShaderName, "u_Force"), 5, 0, 0);

	int stride = sizeof(float) * 15;
	glBindBuffer(GL_ARRAY_BUFFER, m_VBOParticle);

	// Bind position attribute
	int attribPosition = glGetAttribLocation(ShaderName, "a_Position");
	glEnableVertexAttribArray(attribPosition);
	glVertexAttribPointer(attribPosition, 3, GL_FLOAT, GL_FALSE, stride, 0);

	int attribColor = glGetAttribLocation(ShaderName, "a_Color");
	glEnableVertexAttribArray(attribColor);
	glVertexAttribPointer(attribColor, 4, GL_FLOAT, GL_FALSE, stride, (GLvoid*)(sizeof(float) * 4));

	int attribRadius = glGetAttribLocation(ShaderName, "a_Value");
	glEnableVertexAttribArray(attribRadius);
	glVertexAttribPointer(attribRadius, 1, GL_FLOAT, GL_FALSE, stride, (GLvoid*)(sizeof(float) * 3));

	int attributeTime = glGetAttribLocation(ShaderName, "a_STime");
	glEnableVertexAttribArray(attributeTime);
	glVertexAttribPointer(attributeTime, 1, GL_FLOAT, GL_FALSE, stride, (GLvoid*)(sizeof(float) * 8));

	int atrrubuteVelocity = glGetAttribLocation(ShaderName, "a_Vel");
	glEnableVertexAttribArray(atrrubuteVelocity);
	glVertexAttribPointer(atrrubuteVelocity, 3, GL_FLOAT, GL_FALSE, stride, (GLvoid*)(sizeof(float) * 9));

	int atrrubuteLifeTime = glGetAttribLocation(ShaderName, "a_LifeTime");
	glEnableVertexAttribArray(atrrubuteLifeTime);;
	glVertexAttribPointer(atrrubuteLifeTime, 1, GL_FLOAT, GL_FALSE, stride, (GLvoid*)(sizeof(float) * 12));

	int atrributeMass = glGetAttribLocation(ShaderName, "a_Mass");
	glEnableVertexAttribArray(atrributeMass);
	glVertexAttribPointer(atrributeMass, 1, GL_FLOAT, GL_FALSE, stride, (GLvoid*)(sizeof(float) * 13));

	int atrributePeriod = glGetAttribLocation(ShaderName, "a_Period");
	glEnableVertexAttribArray(atrributePeriod);
	glVertexAttribPointer(atrributePeriod, 1, GL_FLOAT, GL_FALSE, stride, (GLvoid*)(sizeof(float) * 14));
	//// Draw 
	glDrawArrays(GL_TRIANGLES, 0, m_VBOParticleVertexCount);

	// Cleanup
	glDisableVertexAttribArray(attribPosition);
	glDisableVertexAttribArray(attribColor);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);


	glDisable(GL_BLEND);

}

void Renderer::DrawWave()
{
	
	//Program select
	const int shaderInt = m_GridMeshShader;
	glUseProgram(shaderInt);


	glUniform1f(glGetUniformLocation(shaderInt, "u_Time"), m_time);

	int attribPosition = glGetAttribLocation(shaderInt, "a_Position");
	glEnableVertexAttribArray(attribPosition);
	glBindBuffer(GL_ARRAY_BUFFER, m_GridMeshVBO);
	glVertexAttribPointer(attribPosition, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);

	glDrawArrays(GL_TRIANGLES, 0, m_GridMeshVertexCount);
	glDisableVertexAttribArray(attribPosition);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

}

void Renderer::DrawFullScreenColor(float r, float g, float b, float a)
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	int shader = m_FullScreenShader;
	glUseProgram(shader);

	glUniform4f(glGetUniformLocation(shader, "u_Color"), r, g, b, a);

	int attribPosition = glGetAttribLocation(shader, "a_Position");
	glEnableVertexAttribArray(attribPosition);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBOFullScreen);
	glVertexAttribPointer(attribPosition, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);

	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDisableVertexAttribArray(attribPosition);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glDisable(GL_BLEND);
}

void Renderer::GetGLPosition(float x, float y, float *newX, float *newY)
{
	*newX = x * 2.f / m_WindowSizeX;
	*newY = y * 2.f / m_WindowSizeY;
}

void Renderer::GenerateParticles(int numParticle)
{
	 int floatCountPerVertex = 3 + 1 + 4 + 1 + 3 + 1 + 1 + 1 ; //x,y,z,value,r,g,b,a , startTime , vx,vy,vz , lifetime
	 int verticesCountPerParticle = 6; //2 triangles
	 int floatCountPerParticle = floatCountPerVertex * verticesCountPerParticle;
	 int totalVertexCount = verticesCountPerParticle * numParticle;
	 int totalFloatCount = floatCountPerVertex * totalVertexCount;

	float* vertices = new float[totalFloatCount];

	for (int i = 0; i < numParticle; ++i)
	{
		float x, y,z, value, r, g, b, a , sTime , lifeTime , mass;
	/*	x = ((float)rand() / (float)RAND_MAX)*2.0f-1.0f;
		y = ((float)rand() / (float)RAND_MAX) * 2.0f - 1.0f;
		z = 0;*/
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
		value = ((float)rand() / (float)RAND_MAX);

		r = ((float)rand() / (float)RAND_MAX);
		g = ((float)rand() / (float)RAND_MAX);
		b = ((float)rand() / (float)RAND_MAX);
		a = ((float)rand() / (float)RAND_MAX);
		sTime = ((float)rand() / (float)RAND_MAX) * 2.0f;

		float size = ((float)rand() / (float)RAND_MAX) * 0.01f;

		int index = i * floatCountPerParticle;

		float vx = ((float)rand() / (float)RAND_MAX) * 2.0f - 1.0f;
		float vy = (((float)rand() / (float)RAND_MAX) * 2.0f - 1.0f) +1.5f;
		float vz = 0;

		lifeTime = ((float)rand() / (float)RAND_MAX);
		mass = ((float)rand() / (float)RAND_MAX) + 1;
		float period = ((float)rand() / (float)RAND_MAX) + 1;

		//v1
		vertices[index] = x - size;		index++;
		vertices[index] = y - size;		index++;
		vertices[index] = z;			index++;
		vertices[index] = value;		index++;
		vertices[index] = r;			index++;
		vertices[index] = g;			index++;
		vertices[index] = b;			index++;
		vertices[index] = a;			index++;
		vertices[index] = sTime;		index++;
		vertices[index] = vx;			index++;
		vertices[index] = vy;			index++;
		vertices[index] = vz;			index++;
		vertices[index] = lifeTime;		index++;
		vertices[index] = mass;			index++;
		vertices[index] = period;		index++;
		//v2
		vertices[index] = x + size;		index++;
		vertices[index] = y + size;		index++;
		vertices[index] = z;			index++;
		vertices[index] = value;		index++;
		vertices[index] = r;			index++;
		vertices[index] = g;			index++;
		vertices[index] = b;			index++;
		vertices[index] = a;			index++;
		vertices[index] = sTime;		index++;
		vertices[index] = vx;			index++;
		vertices[index] = vy;			index++;
		vertices[index] = vz;			index++;
		vertices[index] = lifeTime;		index++;
		vertices[index] = mass;			index++;
		vertices[index] = period;		index++;


		//v3
		vertices[index] = x - size;		index++;
		vertices[index] = y + size;		index++;
		vertices[index] = z;			index++;
		vertices[index] = value;		index++;
		vertices[index] = r;			index++;
		vertices[index] = g;			index++;
		vertices[index] = b;			index++;
		vertices[index] = a;			index++;
		vertices[index] = sTime;		index++;
		vertices[index] = vx;			index++;
		vertices[index] = vy;			index++;
		vertices[index] = vz;			index++;
		vertices[index] = lifeTime;		index++;
		vertices[index] = mass;			index++;
		vertices[index] = period;		index++;
		//v4
		vertices[index] = x - size;		index++;
		vertices[index] = y - size;		index++;
		vertices[index] = z;			index++;
		vertices[index] = value;		index++;
		vertices[index] = r;			index++;
		vertices[index] = g;			index++;
		vertices[index] = b;			index++;
		vertices[index] = a;			index++;
		vertices[index] = sTime;		index++;
		vertices[index] = vx;			index++;
		vertices[index] = vy;			index++;
		vertices[index] = vz;			index++;
		vertices[index] = lifeTime;		index++;
		vertices[index] = mass;			index++;
		vertices[index] = period;		index++;
		//v5
		vertices[index] = x + size;		index++;
		vertices[index] = y - size;		index++;
		vertices[index] = z;			index++;
		vertices[index] = value;		index++;
		vertices[index] = r;			index++;
		vertices[index] = g;			index++;
		vertices[index] = b;			index++;
		vertices[index] = a;			index++;
		vertices[index] = sTime;		index++;
		vertices[index] = vx;			index++;
		vertices[index] = vy;			index++;
		vertices[index] = vz;			index++;
		vertices[index] = lifeTime;		index++;
		vertices[index] = mass;			index++;
		vertices[index] = period;		index++;
		//v6
		vertices[index] = x + size;		index++;
		vertices[index] = y + size;		index++;
		vertices[index] = z;			index++;
		vertices[index] = value;		index++;
		vertices[index] = r;			index++;
		vertices[index] = g;			index++;
		vertices[index] = b;			index++;
		vertices[index] = a;			index++;
		vertices[index] = sTime;		index++;
		vertices[index] = vx;			index++;
		vertices[index] = vy;			index++;
		vertices[index] = vz;			index++;
		vertices[index] = lifeTime;		index++;
		vertices[index] = mass;			index++;
		vertices[index] = period;		index++;
	}

	glGenBuffers(1, &m_VBOParticle);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBOParticle);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * totalFloatCount, vertices, GL_STATIC_DRAW);


	delete[] vertices;
	m_VBOParticleVertexCount = totalVertexCount;

}
