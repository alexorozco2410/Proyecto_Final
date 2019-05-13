
#pragma once
#ifndef RUEDA_H_
#define RUEDA_H_
#include <glew.h>
#include <glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <shader_m.h>
#include <iostream>
#define M_PI 3.14159265358979323846264338327950288
#define MERIDIANOS 50
#define PARALELOS 10
class Rueda
{
public:
	Rueda(GLfloat radio);
	void init();
	//void load();
	void render();
	void dibujaRueda(unsigned int tex1, Shader ligthShader, Shader textureShader, glm::mat4 model, GLuint rueda_VBO, GLuint rueda_VAO, GLuint rueda_EBO, float rotRueda, float angRotPuerta);
	virtual ~Rueda();

private:

	float radio;

	GLuint rueda_VAO[4], rueda_VBO[4], rueda_index[MERIDIANOS*(PARALELOS - 1) * 6];
	GLfloat rueda_pos[PARALELOS * MERIDIANOS * 3];

};

#endif // !CILINDRO_H_