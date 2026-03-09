//Práctica 2: índices, mesh, proyecciones, transformaciones geométricas
#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>
#include <glew.h>
#include <glfw3.h>
//glm
#include<glm.hpp>
#include<gtc\matrix_transform.hpp>
#include<gtc\type_ptr.hpp>
//clases para dar orden y limpieza al código
#include"Mesh.h"
#include"Shader.h"
#include"Window.h"
//Dimensiones de la ventana
const float toRadians = 3.14159265f / 180.0; //grados a radianes
Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<MeshColor*> meshColorList;
std::vector<Shader>shaderList;
//Vertex Shader
static const char* vShader = "shaders/shader.vert";
static const char* fShader = "shaders/shader.frag";
static const char* vShaderColor = "shaders/shadercolor.vert";
static const char* fShaderColor = "shaders/shadercolor.frag";
//shaders nuevos se crearían acá
static const char* vShaderAZUL = "shaders/shaderAZUL.vert";
static const char* fShaderAZUL = "shaders/shaderAZUL.frag";
static const char* vShaderCAFE = "shaders/shaderCAFE.vert";
static const char* fShaderCAFE = "shaders/shaderCAFE.frag";
static const char* vShaderROJO = "shaders/shaderROJO.vert";
static const char* fShaderROJO = "shaders/shaderROJO.frag";
static const char* vShaderVERDE_CLARO = "shaders/shaderVERDE_CLARO.vert";
static const char* fShaderVERDE_CLARO = "shaders/shaderVERDE_CLARO.frag";
static const char* vShaderVERDE_OSCURO = "shaders/shaderVERDE_OSCURO.vert";
static const char* fShaderVERDE_OSCURO = "shaders/shaderVERDE_OSCURO.frag";

float angulo = 0.0f;

//color café en RGB : 0.478, 0.255, 0.067

//Pirámide triangular regular
void CreaPiramide()
{
	unsigned int indices[] = {
		0,1,2,
		1,3,2,
		3,0,2,
		1,0,3

	};
	GLfloat vertices[] = {
		-0.5f, -0.5f,0.0f,	//0
		0.5f,-0.5f,0.0f,	//1
		0.0f,0.5f, -0.25f,	//2
		0.0f,-0.5f,-0.5f,	//3

	};
	Mesh* obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 12, 12);
	meshList.push_back(obj1);
}

//Vértices de un cubo
void CrearCubo()
{
	unsigned int cubo_indices[] = {
		// front
		0, 1, 2,
		2, 3, 0,
		// right
		1, 5, 6,
		6, 2, 1,
		// back
		7, 6, 5,
		5, 4, 7,
		// left
		4, 0, 3,
		3, 7, 4,
		// bottom
		4, 5, 1,
		1, 0, 4,
		// top
		3, 2, 6,
		6, 7, 3
	};

	GLfloat cubo_vertices[] = {
		// front
		-0.5f, -0.5f,  0.5f,
		0.5f, -0.5f,  0.5f,
		0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		// back
		-0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f,  0.5f, -0.5f,
		-0.5f,  0.5f, -0.5f
	};
	Mesh* cubo = new Mesh();
	cubo->CreateMesh(cubo_vertices, cubo_indices, 24, 36);
	meshList.push_back(cubo);
}

void CrearLetrasyFiguras()
{
	GLfloat vertices_letras[] = {
		//X	   Y	  Z				 R		 G		 B
	   //    ------ LETRA H ------
-0.6f,  0.2f, 0.0f,   1.0f, 0.0f, 0.0f,
-0.6f, -0.2f, 0.0f,   1.0f, 0.0f, 0.0f,
-0.5f,  0.2f, 0.0f,   1.0f, 0.0f, 0.0f,
-0.6f, -0.2f, 0.0f,   1.0f, 0.0f, 0.0f,
-0.5f, -0.2f, 0.0f,   1.0f, 0.0f, 0.0f,
-0.5f,  0.2f, 0.0f,   1.0f, 0.0f, 0.0f,

-0.3f,  0.2f, 0.0f,   1.0f, 0.0f, 0.0f,
-0.3f, -0.2f, 0.0f,   1.0f, 0.0f, 0.0f,
-0.2f,  0.2f, 0.0f,   1.0f, 0.0f, 0.0f,
-0.3f, -0.2f, 0.0f,   1.0f, 0.0f, 0.0f,
-0.2f, -0.2f, 0.0f,   1.0f, 0.0f, 0.0f,
-0.2f,  0.2f, 0.0f,   1.0f, 0.0f, 0.0f,

-0.5f,  0.05f, 0.0f,  1.0f, 0.0f, 0.0f,
-0.5f, -0.05f, 0.0f,  1.0f, 0.0f, 0.0f,
-0.3f,  0.05f, 0.0f,  1.0f, 0.0f, 0.0f,
-0.5f, -0.05f, 0.0f,  1.0f, 0.0f, 0.0f,
-0.3f, -0.05f, 0.0f,  1.0f, 0.0f, 0.0f,
-0.3f,  0.05f, 0.0f,  1.0f, 0.0f, 0.0f,

//    ------ LETRA C ------
-0.1f,  0.2f, 0.0f,   0.0f, 1.0f, 0.0f,
 0.1f,  0.2f, 0.0f,   0.0f, 1.0f, 0.0f,
-0.1f,  0.1f, 0.0f,   0.0f, 1.0f, 0.0f,
 0.1f,  0.2f, 0.0f,   0.0f, 1.0f, 0.0f,
 0.1f,  0.1f, 0.0f,   0.0f, 1.0f, 0.0f,
-0.1f,  0.1f, 0.0f,   0.0f, 1.0f, 0.0f,

-0.1f,  0.2f, 0.0f,   0.0f, 1.0f, 0.0f,
-0.1f, -0.2f, 0.0f,   0.0f, 1.0f, 0.0f,
 0.0f,   0.2f, 0.0f,  0.0f, 1.0f, 0.0f,
-0.1f, -0.2f, 0.0f,   0.0f, 1.0f, 0.0f,
 0.0f,  -0.2f, 0.0f,  0.0f, 1.0f, 0.0f,
 0.0f,   0.2f, 0.0f,  0.0f, 1.0f, 0.0f,

-0.1f, -0.2f, 0.0f,   0.0f, 1.0f, 0.0f,
 0.1f, -0.2f, 0.0f,   0.0f, 1.0f, 0.0f,
-0.1f, -0.1f, 0.0f,   0.0f, 1.0f, 0.0f,
 0.1f, -0.2f, 0.0f,   0.0f, 1.0f, 0.0f,
 0.1f, -0.1f, 0.0f,   0.0f, 1.0f, 0.0f,
-0.1f, -0.1f, 0.0f,   0.0f, 1.0f, 0.0f,

//    ------ LETRA R ------
0.2f,  0.2f, 0.0f,   0.0f, 0.0f, 1.0f,
0.2f, -0.2f, 0.0f,   0.0f, 0.0f, 1.0f,
0.3f,  0.2f, 0.0f,   0.0f, 0.0f, 1.0f,
0.2f, -0.2f, 0.0f,   0.0f, 0.0f, 1.0f,
0.3f, -0.2f, 0.0f,   0.0f, 0.0f, 1.0f,
0.3f,  0.2f, 0.0f,   0.0f, 0.0f, 1.0f,

0.3f,  0.2f, 0.0f,   0.0f, 0.0f, 1.0f,
0.5f,  0.2f, 0.0f,   0.0f, 0.0f, 1.0f,
0.3f,  0.1f, 0.0f,   0.0f, 0.0f, 1.0f,
0.5f,  0.2f, 0.0f,   0.0f, 0.0f, 1.0f,
0.5f,  0.1f, 0.0f,   0.0f, 0.0f, 1.0f,
0.3f,  0.1f, 0.0f,   0.0f, 0.0f, 1.0f,

0.3f,  0.05f, 0.0f,  0.0f, 0.0f, 1.0f,
0.5f,  0.05f, 0.0f,  0.0f, 0.0f, 1.0f,
0.3f, -0.05f, 0.0f,  0.0f, 0.0f, 1.0f,
0.5f,  0.05f, 0.0f,  0.0f, 0.0f, 1.0f,
0.5f, -0.05f, 0.0f,  0.0f, 0.0f, 1.0f,
0.3f, -0.05f, 0.0f,  0.0f, 0.0f, 1.0f,

0.3f,  0.05f, 0.0f,  0.0f, 0.0f, 1.0f,
0.5f, -0.2f, 0.0f,   0.0f, 0.0f, 1.0f,
0.4f, -0.2f, 0.0f,   0.0f, 0.0f, 1.0f,

	};
	MeshColor* letras = new MeshColor();
	letras->CreateMeshColor(vertices_letras, 432);
	meshColorList.push_back(letras);

	GLfloat vertices_triangulorojo[] = {
		//X			Y			Z			R		G		B
		-1.0f,	-1.0f,		0.5f,			1.0f,	0.0f,	0.0f,
		1.0f,	-1.0f,		0.5f,			1.0f,	0.0f,	0.0f,
		0.0f,	1.0f,		0.5f,			1.0f,	0.0f,	0.0f,

	};

	MeshColor* triangulorojo = new MeshColor();
	triangulorojo->CreateMeshColor(vertices_triangulorojo, 18);
	meshColorList.push_back(triangulorojo);

	GLfloat vertices_trianguloverde[] = {
		//X			Y			Z			R		G		B
		-1.0f,	-1.0f,		0.5f,			0.0f,	0.5f,	0.0f,
		1.0f,	-1.0f,		0.5f,			0.0f,	0.5f,	0.0f,
		0.0f,	1.0f,		0.5f,			0.0f,	0.5f,	0.0f,

	};

	MeshColor* trianguloverde = new MeshColor();
	trianguloverde->CreateMeshColor(vertices_trianguloverde, 18);
	meshColorList.push_back(trianguloverde);

	GLfloat vertices_trianguloazul[] = {
		//X			Y			Z			R		G		B
		-1.0f,	-1.0f,		0.5f,			0.0f,	0.0f,	1.0f,
		1.0f,	-1.0f,		0.5f,			0.0f,	0.0f,	1.0f,
		0.0f,	1.0f,		0.5f,			0.0f,	0.0f,	1.0f,

	};

	MeshColor* trianguloazul = new MeshColor();
	trianguloazul->CreateMeshColor(vertices_trianguloazul, 18);
	meshColorList.push_back(trianguloazul);

	GLfloat vertices_cuadradoverde[] = {
		//X			Y			Z			R		G		B
		-0.5f,	-0.5f,		0.5f,			0.0f,	1.0f,	0.0f,
		0.5f,	-0.5f,		0.5f,			0.0f,	1.0f,	0.0f,
		0.5f,	0.5f,		0.5f,			0.0f,	1.0f,	0.0f,
		-0.5f,	-0.5f,		0.5f,			0.0f,	1.0f,	0.0f,
		0.5f,	0.5f,		0.5f,			0.0f,	1.0f,	0.0f,
		-0.5f,	0.5f,		0.5f,			0.0f,	1.0f,	0.0f,

	};

	MeshColor* cuadradoverde = new MeshColor();
	cuadradoverde->CreateMeshColor(vertices_cuadradoverde, 36);
	meshColorList.push_back(cuadradoverde);

	GLfloat vertices_cuadradorojo[] = {
		//X			Y			Z			R		G		B
		-0.5f,	-0.5f,		0.5f,			1.0f,	0.0f,	0.0f,
		0.5f,	-0.5f,		0.5f,			1.0f,	0.0f,	0.0f,
		0.5f,	0.5f,		0.5f,			1.0f,	0.0f,	0.0f,
		-0.5f,	-0.5f,		0.5f,			1.0f,	0.0f,	0.0f,
		0.5f,	0.5f,		0.5f,			1.0f,	0.0f,	0.0f,
		-0.5f,	0.5f,		0.5f,			1.0f,	0.0f,	0.0f,

	};

	MeshColor* cuadradorojo = new MeshColor();
	cuadradorojo->CreateMeshColor(vertices_cuadradorojo, 36);
	meshColorList.push_back(cuadradorojo);

	GLfloat vertices_cuadradocafe[] = {
		//X			Y			Z			R		G		B
		-0.5f,	-0.5f,		0.5f,			0.478f, 0.255f, 0.067f,
		0.5f,	-0.5f,		0.5f,			0.478f, 0.255f, 0.067f,
		0.5f,	0.5f,		0.5f,			0.478f, 0.255f, 0.067f,
		-0.5f,	-0.5f,		0.5f,			0.478f, 0.255f, 0.067f,
		0.5f,	0.5f,		0.5f,			0.478f, 0.255f, 0.067f,
		-0.5f,	0.5f,		0.5f,			0.478f, 0.255f, 0.067f,

	};

	MeshColor* cuadradocafe = new MeshColor();
	cuadradocafe->CreateMeshColor(vertices_cuadradocafe, 36);
	meshColorList.push_back(cuadradocafe);
}


void CreateShaders()
{

	Shader* shader1 = new Shader(); //shader para usar índices: objetos: cubo y  pirámide
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);

	Shader* shader2 = new Shader();//shader para usar color como parte del VAO: letras 
	shader2->CreateFromFiles(vShaderColor, fShaderColor);
	shaderList.push_back(*shader2);

	Shader* shader3 = new Shader(); //shader AZUL
	shader3->CreateFromFiles(vShaderAZUL, fShaderAZUL);
	shaderList.push_back(*shader3);

	Shader* shader4 = new Shader(); //shader CAFE
	shader4->CreateFromFiles(vShaderCAFE, fShaderCAFE);
	shaderList.push_back(*shader4);

	Shader* shader5 = new Shader(); //shader ROJO
	shader5->CreateFromFiles(vShaderROJO, fShaderROJO);
	shaderList.push_back(*shader5);

	Shader* shader6 = new Shader(); //shader VERDE_CLARO
	shader6->CreateFromFiles(vShaderVERDE_CLARO, fShaderVERDE_CLARO);
	shaderList.push_back(*shader6);

	Shader* shader7 = new Shader(); //shader VERDE_OSCURO
	shader7->CreateFromFiles(vShaderVERDE_OSCURO, fShaderVERDE_OSCURO);
	shaderList.push_back(*shader7);
}


int main()
{
	mainWindow = Window(720, 720);
	mainWindow.Initialise();
	CreaPiramide(); //índice 0 en MeshList
	CrearCubo();//índice 1 en MeshList
	CrearLetrasyFiguras(); //usa MeshColor, índices en MeshColorList
	CreateShaders();
	GLuint uniformProjection = 0;
	GLuint uniformModel = 0;
	//Projection: Matriz de Dimensión 4x4 para indicar si vemos en 2D( orthogonal) o en 3D) perspectiva
	//glm::mat4 projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.0f);
	glm::mat4 projection = glm::perspective(glm::radians(60.0f), mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 100.0f);

	//Model: Matriz de Dimensión 4x4 en la cual se almacena la multiplicación de las transformaciones geométricas.
	glm::mat4 model(1.0); //fuera del while se usa para inicializar la matriz con una identidad

	//Loop mientras no se cierra la ventana
	while (!mainWindow.getShouldClose())
	{
		//Recibir eventos del usuario
		glfwPollEvents();
		//Limpiar la ventana
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Se agrega limpiar el buffer de profundidad


		///*				- - - EJERCICIOS DE LA PRÁCTICA 2 - - -
		//Para las letras hay que usar el segundo set de shaders con índice 1 en ShaderList 
		shaderList[1].useShader();
		uniformModel = shaderList[1].getModelLocation();
		uniformProjection = shaderList[1].getProjectLocation();

		//Inicializar matriz de dimensión 4x4 que servirá como matriz de modelo para almacenar las transformaciones geométricas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.4f, 0.5f, -1.7f));
		model = glm::scale(model, glm::vec3(0.7f, 0.7f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshColorList[0]->RenderMeshColor();

		//3D
		shaderList[4].useShader();
		uniformModel = shaderList[4].getModelLocation();
		uniformProjection = shaderList[4].getProjectLocation();

		//Pared Casa (Cubo Rojo) 
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -0.58f, -2.0f));
		model = glm::scale(model, glm::vec3(1.0f, -1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();

		shaderList[5].useShader();
		uniformModel = shaderList[5].getModelLocation();
		uniformProjection = shaderList[5].getProjectLocation();
		//Ventana Izquierda (Cubo Verde)
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.25f, -0.3f, -2.0f));
		model = glm::scale(model, glm::vec3(0.3f, -0.3f, 0.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();

		shaderList[5].useShader();
		uniformModel = shaderList[5].getModelLocation();
		uniformProjection = shaderList[5].getProjectLocation();
		//Ventana Derecha (Cubo Verde)
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.25f, -0.3f, -2.0f));
		model = glm::scale(model, glm::vec3(0.3f, -0.3f, 0.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();

		shaderList[5].useShader();
		uniformModel = shaderList[5].getModelLocation();
		uniformProjection = shaderList[5].getProjectLocation();
		//Puerta Casa (Cubo Verde)
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -0.85f, -2.0f));
		model = glm::scale(model, glm::vec3(0.3f, -0.3f, 0.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();

		shaderList[2].useShader();
		uniformModel = shaderList[2].getModelLocation();
		uniformProjection = shaderList[2].getProjectLocation();
		//Techo (Piramide Azul)
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.15f, -1.9f));
		model = glm::scale(model, glm::vec3(1.0f, 0.5f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[0]->RenderMesh();

		shaderList[3].useShader();
		uniformModel = shaderList[3].getModelLocation();
		uniformProjection = shaderList[3].getProjectLocation();
		//Tronco Izquierdo (Cubo Café)
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.75f, -0.9f, -2.0f));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();

		shaderList[3].useShader();
		uniformModel = shaderList[3].getModelLocation();
		uniformProjection = shaderList[3].getProjectLocation();
		//Tronco Derecho (Cubo Café)
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.75f, -0.9f, -2.0f));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.3f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();

		shaderList[6].useShader();
		uniformModel = shaderList[6].getModelLocation();
		uniformProjection = shaderList[6].getProjectLocation();
		//Hojas Pino Izquierdo (Pramide Verde Oscuro)
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.75f, -0.6f, -1.9f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[0]->RenderMesh();

		shaderList[6].useShader();
		uniformModel = shaderList[6].getModelLocation();
		uniformProjection = shaderList[6].getProjectLocation();
		//Hojas Pino Derecho (Piramide Verde Oscuro)
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.75f, -0.6f, -1.9f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[0]->RenderMesh();
		//*/

		glUseProgram(0);
		mainWindow.swapBuffers();

	}
	return 0;
}