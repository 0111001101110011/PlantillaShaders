#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>

#define GLEW_STATIC

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include <iostream>

#include "Shader.h"
#include "Vertice.h"

using namespace std;

void dibujar();
void actualizar();
void inicializarTriangulo();
void inicializarCuadrado();
void inicializarChichenItza();

Shader *shader;
GLuint posicionID;
GLuint colorID;

vector<Vertice> triangulo;
GLuint vertexArrayTrianguloID;
GLuint bufferTrianguloID;

vector<Vertice> cuadrado;
GLuint vertexArrayCuadradoID;
GLuint bufferCuadradoID;

vector<Vertice> chichenItza;
GLuint vertexArrayChichenItzaID;
GLuint bufferChichenItzaID;

int main()
{
	// Creamos una ventana
	GLFWwindow *window;

	// Si no se puede inicializar glfw, finalizamos la ejecucion
	if (!glfwInit()) {
		exit(EXIT_FAILURE);
	}

	// Si se pudo iniciar GLFW, entonces inicializamos la ventana
	window = glfwCreateWindow(1024, 768, "Ventana", NULL, NULL);

	// Si no podemos iniciar la ventana, terminamos ejecucion
	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	//Establecemos el contexto
	glfwMakeContextCurrent(window);

	// Una vez establecido el contexto, activamos funciones modernas
	glewExperimental = true;
	GLenum errorGlew = glewInit();
	if (errorGlew != GLEW_OK) {
		cout << glewGetErrorString(errorGlew);
	}

	const GLubyte *versionGL = glGetString(GL_VERSION);
	cout << "Version OpenGL: " << versionGL << std::endl;

	//inicializarTriangulo();
	//inicializarCuadrado();
	inicializarChichenItza();

	const char *rutaVertex = "VertexShader.shader";
	const char *rutaFragment = "FragmentShader.shader";

	shader = new Shader(rutaVertex, rutaFragment);

	// Mapeo de atributos
	posicionID = glGetAttribLocation(shader->getID(), "posicion");
	colorID = glGetAttribLocation(shader->getID(), "color");

	// Desenlazar el shader
	shader->desenlazar();

	// Crear un vertex array (triángulo)
	glGenVertexArrays(1, &vertexArrayTrianguloID);
	glBindVertexArray(vertexArrayTrianguloID);
	// Crear un vertex buffer (triángulo)
	glGenBuffers(1, &bufferTrianguloID);
	glBindBuffer(GL_ARRAY_BUFFER, bufferTrianguloID);
	// Llenado del buffer (triángulo)
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertice) * triangulo.size(), triangulo.data(), GL_STATIC_DRAW);
	// Memoria consumida * Número de elementos (vértices) que tiene el vector

	// Habilitar atributos del Shader (cuadrado)
	glEnableVertexAttribArray(posicionID);
	glEnableVertexAttribArray(colorID);
	// Especificar a OpenGL cómo se va a comunicar (cuadrado)
	glVertexAttribPointer(posicionID, 3, GL_FLOAT, GL_FALSE, sizeof(Vertice), 0);
	glVertexAttribPointer(colorID, 4, GL_FLOAT, GL_FALSE, sizeof(Vertice), (void*)sizeof(vec3));
	// Vertex Array + Búffer (cuadrado)
	glGenVertexArrays(1, &vertexArrayCuadradoID);
	glBindVertexArray(vertexArrayCuadradoID);
	glGenBuffers(1, &bufferCuadradoID);
	glBindBuffer(GL_ARRAY_BUFFER, bufferCuadradoID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertice) * cuadrado.size(), cuadrado.data(), GL_STATIC_DRAW);

	// Habilitar atributos del Shader (chichen itzá)
	glEnableVertexAttribArray(posicionID);
	glEnableVertexAttribArray(colorID);
	// Especificar a OpenGL cómo se va a comunicar (chichen itzá)
	glVertexAttribPointer(posicionID, 3, GL_FLOAT, GL_FALSE, sizeof(Vertice), 0);
	glVertexAttribPointer(colorID, 4, GL_FLOAT, GL_FALSE, sizeof(Vertice), (void*)sizeof(vec3));
	// Vertex Array + Búffer (chichen itzá)
	glGenVertexArrays(1, &vertexArrayChichenItzaID);
	glBindVertexArray(vertexArrayChichenItzaID);
	glGenBuffers(1, &bufferChichenItzaID);
	glBindBuffer(GL_ARRAY_BUFFER, bufferChichenItzaID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertice) * chichenItza.size(), cuadrado.data(), GL_STATIC_DRAW);

	// Habilitar atributos del Shader (Triangulo)
	glEnableVertexAttribArray(posicionID);
	glEnableVertexAttribArray(colorID);
	// Especificar a OpenGL cómo se va a comunicar (Triangulo)
	glVertexAttribPointer(posicionID, 3, GL_FLOAT, GL_FALSE, sizeof(Vertice), 0);
	glVertexAttribPointer(colorID, 4, GL_FLOAT, GL_FALSE, sizeof(Vertice), (void*)sizeof(vec3));
	// Soltar vertex array y buffer
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Ciclo de dibujo (Draw loop)
	while (!glfwWindowShouldClose(window)) {

		// Establecer region de dibujo
		glViewport(0, 0, 1024, 768);

		// Establece el color de borrado
		glClearColor(.23, 0.3, 0.3, 1);

		// Borramos
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Rutina de dibujo
		dibujar();
		actualizar();

		// Cambiar los buffers
		glfwSwapBuffers(window);

		// Reconocer si hay entradas
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}

void dibujar()
{
	// Elegir el Shader
	shader->enlazar();

	// Elegir un vertex array
	glBindVertexArray(vertexArrayTrianguloID);

	// Dibujar
	glDrawArrays(GL_TRIANGLES, 0, triangulo.size());

	// Dibujar Cuadrado
	glBindVertexArray(vertexArrayCuadradoID);
	glDrawArrays(GL_POLYGON, 0, cuadrado.size());

	// Dibujar Chichen Itzá
	glBindVertexArray(vertexArrayChichenItzaID);
	glDrawArrays(GL_POLYGON, 0, chichenItza.size());

	// Soltar el vertex array
	glBindVertexArray(0);

	// Soltar el Shader
	shader->desenlazar();
}

void actualizar()
{

}

void inicializarTriangulo()
{
	Vertice v1 =
	{
		vec3(0.0f, 0.3f, 0.0f),
		vec4(1.0f, 0.8f, 0.0f, 1.0f)
	};
	Vertice v2 =
	{
		vec3(0.3f, -0.3f, 0.0f),
		vec4(1.0f, 0.8f, 0.0f, 1.0f)
	};
	Vertice v3 =
	{
		vec3(-0.3f, -0.3f, 0.0f),
		vec4(1.0f, 0.8f, 0.0f, 1.0f)
	};

	triangulo.push_back(v1);
	triangulo.push_back(v2);
	triangulo.push_back(v3);
}

void inicializarCuadrado()
{
	Vertice v1 =
	{
		vec3(1.0f, 0.0f, 0.0f),
		vec4(0.4f, 0.5f, 0.2f, 1.0f)
	};
	Vertice v2 =
	{
		vec3(0.5f, 0.0f, 0.0f),
		vec4(0.4f, 0.5f, 0.2f, 1.0f)
	};
	Vertice v3 =
	{
		vec3(0.5f, 0.5f, 0.0f),
		vec4(0.4f, 0.5f, 0.2f, 1.0f)
	};
	Vertice v4 =
	{
		vec3(1.0f, 0.5f, 0.0f),
		vec4(0.4f, 0.5f, 0.2f, 1.0f)
	};

	cuadrado.push_back(v1);
	cuadrado.push_back(v2);
	cuadrado.push_back(v3);
	cuadrado.push_back(v4);
}

void inicializarChichenItza()
{
	// Primer Rectángulo
	Vertice v1 =
	{
		vec3(-0.95f, -0.95f, 0.0f),
		vec4(0.4f, 0.5f, 0.2f, 1.0f)
	};
	Vertice v2 =
	{
		vec3(-0.95f, -0.8f, 0.0f),
		vec4(0.4f, 0.5f, 0.2f, 1.0f)
	};
	Vertice v3 =
	{
		vec3(-0.87f, -0.8f, 0.0f),
		vec4(0.4f, 0.5f, 0.2f, 1.0f)
	};
	// Segundo Rectángulo
	Vertice v4 =
	{
		vec3(-0.87f, -0.65f, 0.0f),
		vec4(0.4f, 0.5f, 0.2f, 1.0f)
	};
	Vertice v5 =
	{
		vec3(-0.79f, -0.65f, 0.0f),
		vec4(0.4f, 0.5f, 0.2f, 1.0f)
	};
	// Tercer Rectángulo
	Vertice v6 =
	{
		vec3(-0.79f, -0.5f, 0.0f),
		vec4(0.4f, 0.5f, 0.2f, 1.0f)
	};
	Vertice v7 =
	{
		vec3(-0.71f, -0.5f, 0.0f),
		vec4(0.4f, 0.5f, 0.2f, 1.0f)
	};
	// Cuarto Rectángulo
	Vertice v8 =
	{
		vec3(-0.71f, -0.35f, 0.0f),
		vec4(0.4f, 0.5f, 0.2f, 1.0f)
	};
	Vertice v9 =
	{
		vec3(-0.63f, -0.35f, 0.0f),
		vec4(0.4f, 0.5f, 0.2f, 1.0f)
	};
	// Quinto Rectángulo
	Vertice v10 =
	{
		vec3(-0.63f, -0.2f, 0.0f),
		vec4(0.4f, 0.5f, 0.2f, 1.0f)
	};
	Vertice v11 =
	{
		vec3(-0.55f, -0.2f, 0.0f),
		vec4(0.4f, 0.5f, 0.2f, 1.0f)
	};
	// Sexto Rectángulo
	Vertice v12 =
	{
		vec3(-0.55f, -0.05f, 0.0f),
		vec4(0.4f, 0.5f, 0.2f, 1.0f)
	};
	Vertice v13 =
	{
		vec3(-0.47f, -0.05f, 0.0f),
		vec4(0.4f, 0.5f, 0.2f, 1.0f)
	};
	// Sétpimo Rectángulo
	Vertice v14 =
	{
		vec3(-0.47f, 0.1f, 0.0f),
		vec4(0.4f, 0.5f, 0.2f, 1.0f)
	};
	Vertice v15 =
	{
		vec3(-0.39f, 0.1f, 0.0f),
		vec4(0.4f, 0.5f, 0.2f, 1.0f)
	};
	// Octavo Rectángulo
	Vertice v16 =
	{
		vec3(-0.39f, 0.25f, 0.0f),
		vec4(0.4f, 0.5f, 0.2f, 1.0f)
	};
	Vertice v17 =
	{
		vec3(-0.31f, 0.25f, 0.0f),
		vec4(0.4f, 0.5f, 0.2f, 1.0f)
	};
	// Noveno Rectángulo
	Vertice v18 =
	{
		vec3(-0.31f, 0.25f, 0.0f),
		vec4(0.4f, 0.5f, 0.2f, 1.0f)
	};
	Vertice v19 =
	{
		vec3(-0.23f, 0.25f, 0.0f),
		vec4(0.4f, 0.5f, 0.2f, 1.0f)
	};
	Vertice v20 =
	{
		vec3(-0.23f, 0.25f, 0.0f),
		vec4(0.4f, 0.5f, 0.2f, 1.0f)
	};
	Vertice v21 =
	{
		vec3(-0.23f, 0.25f, 0.0f),
		vec4(0.4f, 0.5f, 0.2f, 1.0f)
	};
	Vertice v22 =
	{
		vec3(-0.23f, 0.1f, 0.0f),
		vec4(0.4f, 0.5f, 0.2f, 1.0f)
	};
	Vertice v23 =
	{
		vec3(0.23f, 0.1f, 0.0f),
		vec4(0.4f, 0.5f, 0.2f, 1.0f)
	};
	Vertice v24 =
	{
		vec3(0.05f, -0.05f, 0.0f),
		vec4(0.4f, 0.5f, 0.2f, 1.0f)
	};
	Vertice v25 =
	{
		vec3(0.2f, -0.05f, 0.0f),
		vec4(0.4f, 0.5f, 0.2f, 1.0f)
	};
	Vertice v26 =
	{
		vec3(0.2f, -0.2f, 0.0f),
		vec4(0.4f, 0.5f, 0.2f, 1.0f)
	};
	Vertice v27 =
	{
		vec3(0.35f, -0.2f, 0.0f),
		vec4(0.4f, 0.5f, 0.2f, 1.0f)
	};
	Vertice v28 =
	{
		vec3(0.35f, -0.35f, 0.0f),
		vec4(0.4f, 0.5f, 0.2f, 1.0f)
	};
	Vertice v29 =
	{
		vec3(0.5f, -0.35f, 0.0f),
		vec4(0.4f, 0.5f, 0.2f, 1.0f)
	};
	Vertice v30 =
	{
		vec3(0.5f, -0.5f, 0.0f),
		vec4(0.4f, 0.5f, 0.2f, 1.0f)
	};
	Vertice v31 =
	{
		vec3(0.65f, -0.5f, 0.0f),
		vec4(0.4f, 0.5f, 0.2f, 1.0f)
	};
	Vertice v32 =
	{
		vec3(0.65f, -0.65f, 0.0f),
		vec4(0.4f, 0.5f, 0.2f, 1.0f)
	};
	Vertice v33 =
	{
		vec3(0.8f, -0.65f, 0.0f),
		vec4(0.4f, 0.5f, 0.2f, 1.0f)
	};
	Vertice v34 =
	{
		vec3(0.8f, -0.8f, 0.0f),
		vec4(0.4f, 0.5f, 0.2f, 1.0f)
	};
	Vertice v35 =
	{
		vec3(0.95f, -0.8f, 0.0f),
		vec4(0.4f, 0.5f, 0.2f, 1.0f)
	};
	Vertice v36 =
	{
		vec3(0.95f, -0.95f, 0.0f),
		vec4(0.4f, 0.5f, 0.2f, 1.0f)
	};

	cuadrado.push_back(v1);
	cuadrado.push_back(v2);
	cuadrado.push_back(v3);
	cuadrado.push_back(v4);
	cuadrado.push_back(v5);
	cuadrado.push_back(v6);
	cuadrado.push_back(v7);
	cuadrado.push_back(v8);
	cuadrado.push_back(v9);
	cuadrado.push_back(v10);
	cuadrado.push_back(v11);
	cuadrado.push_back(v12);
	cuadrado.push_back(v13);
	cuadrado.push_back(v14);
	cuadrado.push_back(v15);
	cuadrado.push_back(v16);
	cuadrado.push_back(v17);
	cuadrado.push_back(v18);
	cuadrado.push_back(v19);
	cuadrado.push_back(v20);
	cuadrado.push_back(v21);
	cuadrado.push_back(v22);
	cuadrado.push_back(v23);
	cuadrado.push_back(v24);
	cuadrado.push_back(v25);
	cuadrado.push_back(v26);
	cuadrado.push_back(v27);
	cuadrado.push_back(v28);
	cuadrado.push_back(v29);
	cuadrado.push_back(v30);
	cuadrado.push_back(v31);
	cuadrado.push_back(v32);
	cuadrado.push_back(v33);
	cuadrado.push_back(v34);
	cuadrado.push_back(v35);
	cuadrado.push_back(v36);
}