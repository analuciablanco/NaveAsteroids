// PlantillaOpenGL.cpp: define el punto de entrada de la aplicación de consola.
//

#include "stdafx.h"

#include <stdio.h>
#include <stdlib.h>

#define GLEW_STATIC

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <iostream>

#include "Shader.h"
#include "Vertice.h"

#include "Modelo.h"
#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"
#include "Nave.h"

using namespace std;

Shader *shader;
GLuint posicionID;
GLuint colorID;
GLuint transformacionesID;

//Declaramos apuntador de ventana
GLFWwindow *window;

Nave *nave;

void dibujar() {
	nave->dibujar(GL_TRIANGLES);
}

void actualizar() {

	nave->tiempoActual = glfwGetTime();
	nave->tiempoDiferencial = nave->tiempoActual - nave->tiempoAnterior;
	
	int estadoArriba =
		glfwGetKey(window, GLFW_KEY_UP);
	if (estadoArriba == GLFW_PRESS) {
		nave->avanzar();
	}
	else
	{
		nave->detener();
	}

	int estadoIzquierda =
		glfwGetKey(window, GLFW_KEY_LEFT);
	if (estadoIzquierda == GLFW_PRESS) {
		nave->rotar(Nave::Direccion::Izquierda);
	}

	int estadoDerecha =
		glfwGetKey(window, GLFW_KEY_RIGHT);
	if (estadoDerecha == GLFW_PRESS) {
		nave->rotar(Nave::Direccion::Derecha);
	}

	if (nave->coordenadas.x < -1.2f)
	{
		nave->coordenadas.x += 2.1f;
	} else if (nave->coordenadas.x > 1.2f)
	{
		nave->coordenadas.x -= 2.1f;
	}

	if (nave->coordenadas.y < -1.2f)
	{
		nave->coordenadas.y += 2.1f;
	}
	else if (nave->coordenadas.y > 1.2f)
	{
		nave->coordenadas.y -= 2.1f;
	}


	nave->tiempoAnterior = nave->tiempoActual;
}

int main()
{
	
	
	//Si no se pudo iniciar glfw
	//terminamos ejcución
	if (!glfwInit()) {
		exit(EXIT_FAILURE);
	}
	//Si se pudo iniciar GLFW
	//entonces inicializamos la ventana
	window =
		glfwCreateWindow(1024, 768, "Ventana", 
			NULL, NULL);
	//Si no podemos iniciar la ventana
	//Entonces terminamos ejecucion
	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	//Establecemos el contexto
	glfwMakeContextCurrent(window);

	//Una vez establecido  el contexto
	//Activamos funciones modernas
	glewExperimental = true;
	GLenum errorGlew = glewInit();
	if (errorGlew != GLEW_OK) {
		cout << 
			glewGetErrorString(errorGlew);
	}

	const GLubyte *versionGL =
		glGetString(GL_VERSION);
	cout << "Version OpenGL: "
		<< versionGL;


	const char *rutaVertex = 
		"VertexShader.shader";
	const char *rutaFragment = 
		"FragmentShader.shader";

	shader = new Shader(rutaVertex, rutaFragment);

	

	//Mapeo de atributos
	posicionID =
		glGetAttribLocation(shader->getID(), "posicion");
	colorID =
		glGetAttribLocation(shader->getID(), "color");
	transformacionesID =
		glGetUniformLocation(shader->getID(), "transformaciones");


	nave = new Nave();
	nave->shader = shader;
	nave->inicializarVertexArray(posicionID,
		colorID, transformacionesID);

	//Desenlazar el shader
	shader->desenlazar();


	//Ciclo de dibujo (Draw loop)
	while (!glfwWindowShouldClose(window)) {
		//Esablecer region de dibujo
		glViewport(0, 0, 1024, 768);
		//Establece el color de borrado
		glClearColor(1, 0.2, 0.5, 1);
		//Borramos
		glClear(
			GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Rutina de dibujo
		dibujar();
		actualizar();

		//Cambiar los buffers
		glfwSwapBuffers(window);
		//Reconocer si hay entradas
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();

    return 0;
}

