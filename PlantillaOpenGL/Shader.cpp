#include "stdafx.h"
#include "Shader.h"

GLuint Shader::getID() {
	return shaderID;
}

Shader::Shader(const char * rutaVertex, const char * rutaFragment) {

	string codigoVertexShader;
	ifstream vertexShaderStream(rutaVertex, ios::in);
	if (vertexShaderStream.is_open())
	{
		string linea;
		while (getline(vertexShaderStream, linea)) {
			codigoVertexShader += linea + "\n";
		} 
		vertexShaderStream.close();
	}
	else {
		cout << "No se pudo abrir el archivo " << rutaVertex;
	}

	string codigoFragmentShader;
	ifstream fragmentShaderStream(rutaFragment, ios::in);
	if (fragmentShaderStream.is_open()) {
		string linea;
		while (getline(fragmentShaderStream, linea)) {
			codigoFragmentShader += linea + "\n";
		}

		fragmentShaderStream.close();

	}
	else {

		cout << "No se pudo abrir el archivo" << rutaFragment << endl;

	}


	//Convertir de string a cadena de char
	const char* cadenaCodigoVertex = codigoVertexShader.c_str();
	const char* cadenaCodigoFragment = codigoFragmentShader.c_str();

	//1. Creamos el programa de Shaders
	shaderID = glCreateProgram();

	GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	//2. Cargar el codigo del shader
	glShaderSource(vertexShaderID, 1, &cadenaCodigoVertex, NULL);
	glShaderSource(fragmentShaderID, 1, &cadenaCodigoFragment, NULL);

	//3. Compila los Shaders
	glCompileShader(vertexShaderID);
	glCompileShader(fragmentShaderID);

	// 4.Verificar errores de complicación

	
}

void Shader::verificarCompilacion(GLuint id) {
	GLint resultado = GL_FALSE;
	int longitudLog = 0;
}
