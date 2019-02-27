#version 330 core
//Primera linea SIEMPRE es la version

//Atributos de entrada (Vienen desd el Vertex Shader)
in vec4 fragmentColor;

//Atributos de salida
out vec4 salidaColor;

//Funcion main
void main() {
	salidaColor = fragmentColor;
}