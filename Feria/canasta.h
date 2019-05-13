
#pragma once
#ifndef CANASTA_H_
#define CANASTA_H_
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
class Canasta
{
public:
	Canasta(GLfloat radio);
	void init();
	//void load();
	void render();
	void dibujaCanasta(unsigned int tex1, Shader ligthShader, Shader textureShader, glm::mat4 model, glm::mat4 temp01, GLuint canast_VBO, GLuint canasta_VAO, GLuint canasta_EBO, float angRotPuerta);
	virtual ~Canasta();

private:

	float radio;

	GLuint canasta_VAO[4], canasta_VBO[4], canasta_index[MERIDIANOS*(PARALELOS - 1) * 6];
	GLfloat canasta_pos[PARALELOS * MERIDIANOS * 3];

};

#endif // !CILINDRO_H_