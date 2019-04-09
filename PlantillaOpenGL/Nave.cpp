#include "stdafx.h"
#include "Nave.h"

Nave::Nave() {
	angulo = 0.0f;
	coordenadas = vec3(0.0f, 0.0f, 0.0f);
	//Establece el valor como una matriz identidad
	transformaciones = mat4(1.0f);

	Vertice v1 = {
		vec4(0.0f,0.1f,0.0f,1.0f),
		vec4(1.0f,0.0f,0.0f,1.0f)
	};
	Vertice v2 = {
		vec4(-0.1f,-0.1f,0.0f,1.0f),
		vec4(1.0f,0.8f,0.0f,1.0f)
	};
	Vertice v3 = {
		vec4(0.1f,-0.1f,0.0f,1.0f),
		vec4(1.0f,0.8f,0.0f,1.0f)
	};
	vertices.push_back(v1);
	vertices.push_back(v2);
	vertices.push_back(v3);
}

void Nave::rotar(Direccion direccion) {

	float rotacion = velocidadAngular;
	if (direccion == Direccion::Derecha) {
		rotacion = -rotacion;
	}
	angulo += rotacion;
	actualizarMatrizTransformacion();
}

void Nave::avanzar() {
	float anguloDesfasado = angulo + 90.0f;

	if (velocidadActual <= velocidad) {
		velocidadActual +=
			aceleracion * tiempoDiferencial;
	}

	vec3 traslacion = vec3(
	cos(anguloDesfasado * 3.14159 / 180.0f) * velocidadActual, //X
	sin(anguloDesfasado * 3.14159 / 180.0f) * velocidadActual, //Y
		0.0f
	);
	coordenadas += traslacion;
	actualizarMatrizTransformacion();
}

void Nave::detener() {
	float anguloDesfasado = angulo + 90.0f;

	if (velocidadActual >= 0) {
		velocidadActual -=
			desaceleracion * tiempoDiferencial;
		if (velocidadActual < 0) {
			velocidadActual = 0.0f;
		}
	}

	vec3 traslacion = vec3(
		cos(anguloDesfasado * 3.14159 / 180.0f) * velocidadActual, //X
		sin(anguloDesfasado * 3.14159 / 180.0f) * velocidadActual, //Y
		0.0f
	);
	coordenadas += traslacion;
	actualizarMatrizTransformacion();
}

void Nave::actualizarMatrizTransformacion() {
	//Partir siempre de una matriz identidad
	transformaciones = mat4(1.0f);
	//Aplicar las transformaciones
	transformaciones =
		translate(transformaciones, coordenadas);
	transformaciones =
		rotate(transformaciones, angulo * 3.14159f / 180.0f,
			vec3(0.0f, 0.0f, 1.0f));

}