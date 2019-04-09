#pragma once
#include "Modelo.h"
#include "glm/gtx/transform.hpp"
#include "glm/glm.hpp"

class Nave : public Modelo {
public:
	Nave();
	enum Direccion {Izquierda, Derecha};
	vec3 coordenadas;
	float angulo;
	float velocidadAngular = 0.9f;
	float velocidad = 0.01f;

	float aceleracion = 0.009f;
	float desaceleracion = 0.02f;
	float velocidadActual = 0.0f;


	double tiempoAnterior = 0.0;
	double tiempoActual = 0.0;
	double tiempoDiferencial = 0.0;

	void rotar(Direccion direccion);
	void avanzar();
	void detener();
	void actualizarMatrizTransformacion();
};

