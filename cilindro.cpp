#include "cilindro.h"

//glm::vec3 lightPos(0.0f, 0.0f, 0.0f);
//GLuint VBO, VAO, lightVAO;
//Cilindro my_cylinder1(1.0);
//Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
//int SCR_WIDTH = 3800;
//int SCR_HEIGHT = 7600;

Cilindro::Cilindro(GLfloat radio) :

	radio(radio) {
	cilindro_VAO[4] = (-1, -1, -1, -1);
	cilindro_VBO[4] = (-1, -1, -1, -1);

}


Cilindro::~Cilindro()
{
	glDeleteVertexArrays(4, cilindro_VAO);
	glDeleteBuffers(4, cilindro_VBO);
}


void Cilindro::init()
{
	const int nn = PARALELOS * MERIDIANOS * 3;
	GLfloat cylinder_nor[nn]; // normal
	// generate the sphere data
	GLfloat x, y, z, a, b, da, db, r = 1.0;
	int ia, ib, ix, iy;
	da = (GLfloat)2.0*M_PI / GLfloat(MERIDIANOS);
	db = (GLfloat)M_PI / GLfloat(PARALELOS - 1);

	// [Generate sphere point data]

	// spherical angles a,b covering whole sphere surface
	for (ix = 0, b = (GLfloat)-0.5*M_PI, ib = 0; ib < PARALELOS; ib++, b += db)
		for (a = 0.0, ia = 0; ia < MERIDIANOS; ia++, a += da, ix += 3)
		{
			// unit cylinder

			x = b;
			y = sin(a);
			z = cos(a);
			cilindro_pos[ix + 0] = x * r;
			cilindro_pos[ix + 1] = y * r;
			cilindro_pos[ix + 2] = z * r;
			cylinder_nor[ix + 0] = x;
			cylinder_nor[ix + 1] = y;
			cylinder_nor[ix + 2] = z;
		}
	// [Generate GL_TRIANGLE indices]
	for (ix = 0, iy = 0, ib = 1; ib < PARALELOS; ib++)
	{
		for (ia = 1; ia < MERIDIANOS; ia++, iy++)
		{
			// first half of QUAD
			cilindro_index[ix] = iy;      ix++;
			cilindro_index[ix] = iy + 1;    ix++;
			cilindro_index[ix] = iy + MERIDIANOS;   ix++;
			// second half of QUAD
			cilindro_index[ix] = iy + MERIDIANOS;   ix++;
			cilindro_index[ix] = iy + 1;    ix++;
			cilindro_index[ix] = iy + MERIDIANOS + 1; ix++;
		}
		// first half of QUAD
		cilindro_index[ix] = iy;       ix++;
		cilindro_index[ix] = iy + 1 - MERIDIANOS;  ix++;
		cilindro_index[ix] = iy + MERIDIANOS;    ix++;
		// second half of QUAD
		cilindro_index[ix] = iy + MERIDIANOS;    ix++;
		cilindro_index[ix] = iy - MERIDIANOS + 1;  ix++;
		cilindro_index[ix] = iy + 1;     ix++;
		iy++;
	}
	// [VAO/VBO stuff]
	GLuint i;
	glGenVertexArrays(4, cilindro_VAO);
	glGenBuffers(4, cilindro_VBO);
	glBindVertexArray(cilindro_VAO[0]);
	i = 0; // vertex
	glBindBuffer(GL_ARRAY_BUFFER, cilindro_VBO[i]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cilindro_pos), cilindro_pos, GL_STATIC_DRAW);
	glEnableVertexAttribArray(i);
	glVertexAttribPointer(i, 3, GL_FLOAT, GL_FALSE, 0, 0);
	i = 1; // normal
	glBindBuffer(GL_ARRAY_BUFFER, cilindro_VBO[i]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cylinder_nor), cylinder_nor, GL_STATIC_DRAW);
	glEnableVertexAttribArray(i);
	glVertexAttribPointer(i, 3, GL_FLOAT, GL_FALSE, 0, 0);
	i = 2; // indices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cilindro_VBO[i]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cilindro_index), cilindro_index, GL_STATIC_DRAW);
	glEnableVertexAttribArray(i);
	glVertexAttribPointer(i, 4, GL_UNSIGNED_INT, GL_FALSE, 0, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}

void Cilindro::render()
{
	//glEnable(GL_CULL_FACE);
	//glFrontFace(GL_CCW);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glBindVertexArray(cilindro_VAO[0]);
	//  glDrawArrays(GL_POINTS,0,sizeof(esfera_pos)/sizeof(GLfloat));                   // POINTS ... no indices for debug
	glDrawElements(GL_TRIANGLES, sizeof(cilindro_index) / sizeof(GLuint), GL_UNSIGNED_INT, 0);    // indices (choose just one line not both !!!)
	glBindVertexArray(0);
}

void Cilindro::riel(glm::mat4 model)
{
	Shader projectionShader("shaders/shader_light.vs", "shaders/shader_light.fs");
	//glBindVertexArray(lightVAO);
	//glEnable(GL_CULL_FACE);
	//glFrontFace(GL_CCW);
	glm::mat4 temp01 = glm::mat4(1.0f); //Temp
	glm::mat4 temp02 = glm::mat4(1.0f); //Temp

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glBindVertexArray(cilindro_VAO[0]);
	//  glDrawArrays(GL_POINTS,0,sizeof(esfera_pos)/sizeof(GLfloat));     // POINTS ... no indices for debug
	temp01 = model;
	temp02 = model;

	model = temp02;
	model = glm::scale(model, glm::vec3(1.0f, 0.5f, 0.5f));
	projectionShader.setMat4("model", model);
	
	glDrawElements(GL_TRIANGLES, sizeof(cilindro_index) / sizeof(GLuint), GL_UNSIGNED_INT, 0);    // indices (choose just one line not both !!!)
	
	model = glm::translate(model, glm::vec3(0.0, 0, 6.5));
	projectionShader.setMat4("model", model);
	glDrawElements(GL_TRIANGLES, sizeof(cilindro_index) / sizeof(GLuint), GL_UNSIGNED_INT, 0);

	//model = glm::translate(model, glm::vec3(3.5, 0, 0));
	/*model = temp01;
	model = glm::translate(model, glm::vec3(2.5f, 0.0f, 2.25f));
	model = glm::scale(model, glm::vec3(1.0f, 0.2f, 0.2f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 1, 0));
	projectionShader.setMat4("model", model);
	glDrawElements(GL_TRIANGLES, sizeof(cilindro_index) / sizeof(GLuint), GL_UNSIGNED_INT, 0);*/

	model = temp01;
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.75f));
	model = glm::scale(model, glm::vec3(0.2f, 0.2f, 1.0f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 1, 0));
	projectionShader.setMat4("model", model);
	glDrawElements(GL_TRIANGLES, sizeof(cilindro_index) / sizeof(GLuint), GL_UNSIGNED_INT, 0);

	model = temp01;
	model = glm::translate(model, glm::vec3(-1.0f, 0.0f, 1.75f));
	model = glm::scale(model, glm::vec3(0.2f, 0.2f, 1.0f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 1, 0));
	projectionShader.setMat4("model", model);
	glDrawElements(GL_TRIANGLES, sizeof(cilindro_index) / sizeof(GLuint), GL_UNSIGNED_INT, 0);

	model = temp01;
	model = glm::translate(model, glm::vec3(1.0f, 0.0f, 1.75f));
	model = glm::scale(model, glm::vec3(0.2f, 0.2f, 1.0f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 1, 0));
	projectionShader.setMat4("model", model);
	glDrawElements(GL_TRIANGLES, sizeof(cilindro_index) / sizeof(GLuint), GL_UNSIGNED_INT, 0);



	glBindVertexArray(0);
}

void Cilindro::roller_coaster()
{
	Shader projectionShader("shaders/shader_light.vs", "shaders/shader_light.fs");
	//glBindVertexArray(lightVAO);
	//glEnable(GL_CULL_FACE);
	//glFrontFace(GL_CCW);
	glm::mat4 model = glm::mat4(1.0f);		// initialize Matrix, Use this matrix for individual models
	glm::mat4 temp04 = glm::mat4(1.0f);//Temp
	glm::mat4 temp03 = glm::mat4(1.0f);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glBindVertexArray(cilindro_VAO[0]);
	//  glDrawArrays(GL_POINTS,0,sizeof(esfera_pos)/sizeof(GLfloat));     // POINTS ... no indices for debug
	
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0, -1.5, -3.2));
	//model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 1, 0));
	model = glm::scale(model, glm::vec3(0.1f, 0.05f, 0.05f));
	temp04 = model;
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.6f, 0.0f, 0.3f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);

	Cilindro::riel(model);
	
	for (int i = 0; i < 3; i++) {
		model = glm::translate(model, glm::vec3(3.14, 0, 0));
		projectionShader.setMat4("model", model);
		Cilindro::riel(model);
	}
	
	//inicia curva de subida
	
	model = glm::translate(model, glm::vec3(2.0, 0.3, 0.0));
	model = glm::rotate(model, glm::radians(-30.0f), glm::vec3(0, 0, -1));
	model = glm::scale(model, glm::vec3(0.5f, 1.0f, 1.0f));
	projectionShader.setMat4("model", model);

	Cilindro::riel(model);

	model = glm::translate(model, glm::vec3(3.0, 0.4, 0.0));
	model = glm::rotate(model, glm::radians(-15.0f), glm::vec3(0, 0, -1));
	projectionShader.setMat4("model", model);
	Cilindro::riel(model);

	//model = glm::translate(model, glm::vec3(0, 0.55, 4.6));
	model = glm::translate(model, glm::vec3(6.15, 0.81, 0));
	model = glm::rotate(model, glm::radians(-10.0f), glm::vec3(0, 0, -1));
	model = glm::scale(model, glm::vec3(3.0f, 1.0f, 1.0f));
	projectionShader.setMat4("model", model);

	Cilindro::riel(model);
	
	//subida
	model = glm::translate(model, glm::vec3(4.71, 0.0, 0));
	model = glm::scale(model, glm::vec3(2.0f, 1.0f, 1.0));
	projectionShader.setMat4("model", model);

	Cilindro::riel(model);

	for (int i = 0; i < 5; i++) {
		model = glm::translate(model, glm::vec3(3.14, 0, 0));
		projectionShader.setMat4("model", model);
		Cilindro::riel(model);
	}
	//termina subida

	//curva antes de la caida
	model = glm::translate(model, glm::vec3(1.9, -0.7, 0));
	model = glm::scale(model, glm::vec3(0.3f, 1.0f, 1.0f));
	model = glm::rotate(model, glm::radians(-30.0f), glm::vec3(0, 0, 1));
	projectionShader.setMat4("model", model);

	Cilindro::riel(model);

	model = glm::translate(model, glm::vec3(2.9, -0.4, 0));
	//model = glm::scale(model, glm::vec3(1.0f, 1.0f, 0.5f));
	model = glm::rotate(model, glm::radians(-15.0f), glm::vec3(0, 0, 1));
	projectionShader.setMat4("model", model);

	Cilindro::riel(model);

	model = glm::translate(model, glm::vec3(3.0, -0.4, 0));
	//model = glm::scale(model, glm::vec3(1.0f, 1.0f, 0.5f));
	model = glm::rotate(model, glm::radians(-14.0f), glm::vec3(0, 0, 1));
	projectionShader.setMat4("model", model);

	Cilindro::riel(model);

	//antes de caida
	model = glm::scale(model, glm::vec3(2.0f, 1.0f, 1.0f));
	model = glm::translate(model, glm::vec3(2.35, 0.0, 0));
	//model = glm::rotate(model, glm::radians(30.0f), glm::vec3(1, 0, 0));
	projectionShader.setMat4("model", model);

	Cilindro::riel(model);

	//inicio de caida
	model = glm::translate(model, glm::vec3(1.8, -1.0, 0));
	model = glm::scale(model, glm::vec3(0.5f, 1.0f, 1.0f));
	model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(0, 0, 1));
	projectionShader.setMat4("model", model);

	Cilindro::riel(model);

	model = glm::translate(model, glm::vec3(3.0, -0.4, 0));
	//model = glm::scale(model, glm::vec3(1.0f, 1.0f, 0.5f));
	model = glm::rotate(model, glm::radians(-15.0f), glm::vec3(0, 0, 1));
	projectionShader.setMat4("model", model);

	Cilindro::riel(model);
	model = glm::translate(model, glm::vec3(5.3, -0.4, 0));
	model = glm::scale(model, glm::vec3(2.6f, 1.0f, 1.0f));
	model = glm::rotate(model, glm::radians(-15.0f), glm::vec3(0, 0, 1));
	projectionShader.setMat4("model", model);

	Cilindro::riel(model);
	


	//caida
	for (int i = 0; i < 4; i++) {
		model = glm::translate(model, glm::vec3(3.14, 0, 0));
		projectionShader.setMat4("model", model);
		Cilindro::riel(model);
	}
	


	//curva nivel del piso es practicamente = a la primer curva para la subida
	model = glm::translate(model, glm::vec3(1.9, 0.4, 0));
	model = glm::rotate(model, glm::radians(40.0f), glm::vec3(0, 0, 1));
	model = glm::scale(model, glm::vec3(0.5f, 1.0f, 1.0f));
	projectionShader.setMat4("model", model);

	Cilindro::riel(model);

	model = glm::translate(model, glm::vec3(2.9, 0.55, 0));
	model = glm::rotate(model, glm::radians(23.0f), glm::vec3(0, 0, 1));
	model = glm::scale(model, glm::vec3(1.0f, 0.8f, 1.0f));
	projectionShader.setMat4("model", model);
	Cilindro::riel(model);

	//model = glm::translate(model, glm::vec3(0, 0.55, 4.6));
	model = glm::translate(model, glm::vec3(3.7, 0.3, 0));
	model = glm::rotate(model, glm::radians(8.0f), glm::vec3(0, 0, 1));
	model = glm::scale(model, glm::vec3(1.5f, 1.0f, 1.0f));
	projectionShader.setMat4("model", model);

	Cilindro::riel(model);

	model = glm::translate(model, glm::vec3(3.0, 0.3, 0));
	model = glm::rotate(model, glm::radians(10.0f), glm::vec3(0, 0, 1));
	//model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.5f));
	projectionShader.setMat4("model", model);

	Cilindro::riel(model);
	//termina curva nivel de piso

	model = glm::translate(model, glm::vec3(3.8, 0.2, 0));
	model = glm::rotate(model, glm::radians(5.0f), glm::vec3(0, 0, 1));
	model = glm::scale(model, glm::vec3(1.5f, 0.8f, 1.0f));
	projectionShader.setMat4("model", model);

	Cilindro::riel(model);
	
	//antes de giro de rueda
	for (int i = 0; i < 5; i++) {
		model = glm::translate(model, glm::vec3(3.14, 0, 0.0));
		projectionShader.setMat4("model", model);
		Cilindro::riel(model);
	}

	
	//giro de rueda
	for (int i = 0; i < 35; i++) {
		model = glm::translate(model, glm::vec3(3.1, 0.3, 0));
		model = glm::rotate(model, glm::radians(10.0f), glm::vec3(0, 0, 1));
		if (i < 9) {
			model = glm::rotate(model, glm::radians(2.0f), glm::vec3(0, 1, 0));
			model = glm::rotate(model, glm::radians(1.0f), glm::vec3(1, 0, 0));
		}
		if ( i > 8 && i < 31) {
			model = glm::rotate(model, glm::radians(3.0f), glm::vec3(0, 1, 0));
			model = glm::rotate(model, glm::radians(1.0f), glm::vec3(-1, 0, 0));
		}
		if (i > 30) {
			model = glm::rotate(model, glm::radians(4.0f), glm::vec3(-1, 0, 0));
		}
		projectionShader.setMat4("model", model);
		Cilindro::riel(model);
	}
	
	
	//despues de la rueda, antes del ultimo giro
	
	
	model = glm::scale(model, glm::vec3(1.0f, 0.8f, 0.8f));
	for (int i = 0; i < 4; i++) {
		model = glm::translate(model, glm::vec3(3.14, 0, 0));
		projectionShader.setMat4("model", model);
		Cilindro::riel(model);
	}

	//model = glm::scale(model, glm::vec3(0.9f, 1.0f, 1.1f));
	
	for (int i = 0; i < 20; i++) {//e wey eran 20 xD
		model = glm::translate(model, glm::vec3(2.7, 0.0, 0));
		model = glm::rotate(model, glm::radians(-4.0f), glm::vec3(0, 1, 0));
		model = glm::rotate(model, glm::radians(4.0f), glm::vec3(0, 0, 1));
		projectionShader.setMat4("model", model);
		Cilindro::riel(model);
	}

	//model = glm::scale(model, glm::vec3(0.9f, 1.0f, 1.1f));
	for (int i = 0; i < 15; i++) {//e wey eran 15 xD
		model = glm::translate(model, glm::vec3(2.7, 0.2, 0));
		model = glm::rotate(model, glm::radians(-5.0f), glm::vec3(0, 1, 0));
		model = glm::rotate(model, glm::radians(5.0f), glm::vec3(0, 0, 1));
		model = glm::rotate(model, glm::radians(-1.9f), glm::vec3(1, 0, 0));
		projectionShader.setMat4("model", model);
		Cilindro::riel(model);
	}

	model = glm::scale(model, glm::vec3(0.9f, 0.9f, 1.1f));
	for (int i = 0; i < 6; i++) {//ese we eran 6 xD
		model = glm::translate(model, glm::vec3(2.3, 0.0, 0.2));
		model = glm::rotate(model, glm::radians(-8.6f), glm::vec3(0, 1, 0));
		model = glm::rotate(model, glm::radians(5.0f), glm::vec3(0, 0, 1));
		model = glm::rotate(model, glm::radians(-1.9f), glm::vec3(1, 0, 0));
		projectionShader.setMat4("model", model);
		Cilindro::riel(model);
	}
	
	model = glm::scale(model, glm::vec3(1.5f, 0.9f, 0.9f));
	model = glm::translate(model, glm::vec3(2.5, 0.0, 0));
	model = glm::rotate(model, glm::radians(5.0f), glm::vec3(0, 0, 1));
	projectionShader.setMat4("model", model);
	Cilindro::riel(model);
	for (int i = 0; i < 20; i++) {
		model = glm::translate(model, glm::vec3(3.0, 0.0, 0));
		model = glm::rotate(model, glm::radians(-2.0f), glm::vec3(0, 1, 0));
		model = glm::rotate(model, glm::radians(0.5f), glm::vec3(0, 0, 1));
		model = glm::rotate(model, glm::radians(2.0f), glm::vec3(1, 0, 0));
		projectionShader.setMat4("model", model);
		Cilindro::riel(model);
	}
	
	//curva final de caida entre la rueda
	model = glm::translate(model, glm::vec3(2.4, 0.2, 0));
	model = glm::rotate(model, glm::radians(18.0f), glm::vec3(0, 0, 1));
	model = glm::rotate(model, glm::radians(-2.0f), glm::vec3(1, 0, 0));
	model = glm::scale(model, glm::vec3(0.5f, 1.0f, 1.0f));
	projectionShader.setMat4("model", model);

	Cilindro::riel(model);

	model = glm::translate(model, glm::vec3(3.0, 0.3, 0));
	//model = glm::scale(model, glm::vec3(1.0f, 1.0f, 50.5f));
	model = glm::rotate(model, glm::radians(15.0f), glm::vec3(0, 0, 1));
	model = glm::rotate(model, glm::radians(-2.0f), glm::vec3(1, 0, 0));
	projectionShader.setMat4("model", model);
	Cilindro::riel(model);

	model = glm::translate(model, glm::vec3(4.3, 0.1, 0));
	model = glm::scale(model, glm::vec3(2.0f, 1.0f, 1.0f));
	model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0, 0, 1));
	model = glm::rotate(model, glm::radians(-2.0f), glm::vec3(1, 0, 0));
	projectionShader.setMat4("model", model);
	Cilindro::riel(model);
	
	for (int i = 0; i < 6; i++) {
		model = glm::translate(model, glm::vec3(3.14, 0, 0));
		projectionShader.setMat4("model", model);
		Cilindro::riel(model);
	}
	
	temp03 = model; //para seguir despues de la rueda
	//hasta aqui ya estan correguidos los angulos
	//ultima subida

	model = glm::translate(model, glm::vec3(2.0, 0.3, 0));
	model = glm::rotate(model, glm::radians(30.0f), glm::vec3(0, 0, 1));
	model = glm::scale(model, glm::vec3(0.5f, 1.0f, 1.0f));
	projectionShader.setMat4("model", model);

	Cilindro::riel(model);

	model = glm::translate(model, glm::vec3(3.0, 0.4, 0));
	model = glm::rotate(model, glm::radians(20.0f), glm::vec3(0, 0, 1));
	projectionShader.setMat4("model", model);
	Cilindro::riel(model);

	//model = glm::translate(model, glm::vec3(0, 0.55, 4.6));
	model = glm::translate(model, glm::vec3(3.0, 0.4, 0));
	model = glm::rotate(model, glm::radians(15.0f), glm::vec3(0, 0, 1));
	projectionShader.setMat4("model", model);

	Cilindro::riel(model);

	model = glm::translate(model, glm::vec3(4.1, 0.81, 0));
	model = glm::rotate(model, glm::radians(15.0f), glm::vec3(0, 0, 1));
	model = glm::scale(model, glm::vec3(3.0f, 1.0f, 1.0f));
	projectionShader.setMat4("model", model);

	Cilindro::riel(model);
	for (int i = 0; i < 7; i++) {
		model = glm::translate(model, glm::vec3(3.14, 0, 0));
		projectionShader.setMat4("model", model);
		Cilindro::riel(model);
	}

	//nivelar ultima caida
	model = glm::translate(model, glm::vec3(1.9, -0.7, 0));
	model = glm::scale(model, glm::vec3(0.3f, 1.0f, 1.0f));
	model = glm::rotate(model, glm::radians(-25.0f), glm::vec3(0, 0, 1));
	projectionShader.setMat4("model", model);

	Cilindro::riel(model);

	model = glm::translate(model, glm::vec3(2.9, -0.4, 0));
	//model = glm::scale(model, glm::vec3(1.0f, 1.0f, 0.5f));
	model = glm::rotate(model, glm::radians(-20.0f), glm::vec3(0, 0, 1));
	projectionShader.setMat4("model", model);

	Cilindro::riel(model);

	model = glm::translate(model, glm::vec3(2.8, -0.4, 0));
	//model = glm::scale(model, glm::vec3(1.0f, 1.0f, 0.5f));
	model = glm::rotate(model, glm::radians(-15.0f), glm::vec3(0, 0, 1));
	projectionShader.setMat4("model", model);

	Cilindro::riel(model);
	//antes de empezar ultima caida
	
	model = glm::scale(model, glm::vec3(2.0f, 1.0f, 1.0f));
	model = glm::translate(model, glm::vec3(2.8, 0, 0));
	projectionShader.setMat4("model", model);
	Cilindro::riel(model);
	
	//giro antes de la caida

	model = glm::translate(model, glm::vec3(2.2, 0.0, 0));
	model = glm::rotate(model, glm::radians(-20.0f), glm::vec3(0, 1, 0));
	model = glm::rotate(model, glm::radians(-2.0f), glm::vec3(1, 0, 0));
	model = glm::scale(model, glm::vec3(0.5f, 1.0f, 1.0f));
	projectionShader.setMat4("model", model);

	Cilindro::riel(model);

	model = glm::translate(model, glm::vec3(2.2, 0.0, 0));
	model = glm::rotate(model, glm::radians(-25.0f), glm::vec3(0, 1, 0));
	model = glm::rotate(model, glm::radians(-2.0f), glm::vec3(1, 0, 0));
	projectionShader.setMat4("model", model);
	Cilindro::riel(model);

	//model = glm::translate(model, glm::vec3(0, 0.55, 4.6));
	model = glm::translate(model, glm::vec3(2.2, 0.0, 0));
	model = glm::rotate(model, glm::radians(-25.0f), glm::vec3(0, 1, 0));
	model = glm::rotate(model, glm::radians(-2.0f), glm::vec3(1, 0, 0));
	projectionShader.setMat4("model", model);

	Cilindro::riel(model);

	model = glm::translate(model, glm::vec3(2.2, 0.0, 0));
	model = glm::rotate(model, glm::radians(-20.0f), glm::vec3(0, 1, 0));
	model = glm::rotate(model, glm::radians(-2.0f), glm::vec3(1, 0, 0));
	projectionShader.setMat4("model", model);

	Cilindro::riel(model);

	//primera
	model = glm::translate(model, glm::vec3(4.5, -0.2, 0));
	model = glm::scale(model, glm::vec3(3.0f, 1.0f, 1.0f));
	model = glm::rotate(model, glm::radians(-10.0f), glm::vec3(0, 0, 1));
	projectionShader.setMat4("model", model);

	Cilindro::riel(model);

	for (int i = 0; i < 8; i++) {
		model = glm::translate(model, glm::vec3(3.14, 0, 0));
		projectionShader.setMat4("model", model);
		Cilindro::riel(model);
	}

	//giro para segunda caida
	for (int i = 0; i < 10; i++) {
		model = glm::translate(model, glm::vec3(2.0, -0.2, 0.4));
		model = glm::rotate(model, glm::radians(2.0f), glm::vec3(0, 0, 1));
		model = glm::rotate(model, glm::radians(-18.0f), glm::vec3(0, 1, 0));
		if (i > 6) {
			model = glm::rotate(model, glm::radians(-15.0f), glm::vec3(0, 0, 1));
			model = glm::translate(model, glm::vec3(0.0, -0.3, 0.0));
		}
		//model = glm::rotate(model, glm::radians(20.0f), glm::vec3(1, 0, 0));
		projectionShader.setMat4("model", model);
		Cilindro::riel(model);
	}

	//segunda
	model = glm::translate(model, glm::vec3(2.2, -0.2, 0));
	//model = glm::scale(model, glm::vec3(1.0f, 1.0f, 2.0f));
	model = glm::rotate(model, glm::radians(-15.0f), glm::vec3(0, 0, 1));
	projectionShader.setMat4("model", model);
	Cilindro::riel(model);

	for (int i = 0; i < 8; i++) {
		model = glm::translate(model, glm::vec3(3.14, 0, 0));
		projectionShader.setMat4("model", model);
		Cilindro::riel(model);
	}

	//model = glm::scale(model, glm::vec3(1.0f, 1.0f, 2.0f));
	projectionShader.setMat4("model", model);
	//giro para tercera y ultima caida
	for (int i = 0; i < 10; i++) {
		model = glm::translate(model, glm::vec3(2.2, -0.1, -0.5));
		model = glm::rotate(model, glm::radians(2.0f), glm::vec3(0, 0, 1));
		model = glm::rotate(model, glm::radians(18.0f), glm::vec3(0, 1, 0));
		if (i > 5) {
			model = glm::rotate(model, glm::radians(-15.0f), glm::vec3(0, 0, 1));
			model = glm::translate(model, glm::vec3(0.0, -0.2, 0));
		}
		//model = glm::rotate(model, glm::radians(20.0f), glm::vec3(1, 0, 0));
		projectionShader.setMat4("model", model);
		Cilindro::riel(model);
	}
	
	//tercera
	model = glm::translate(model, glm::vec3(3.1, -0.4, 0));
	model = glm::scale(model, glm::vec3(1.5f, 1.0f, 1.0f));
	model = glm::rotate(model, glm::radians(-15.0f), glm::vec3(0, 0, 1));
	projectionShader.setMat4("model", model);
	Cilindro::riel(model);



	//model = glm::translate(model, glm::vec3(0, -0.4, 2.2));
	//model = glm::scale(model, glm::vec3(1.0f, 1.0f, 2.0f));
	//model = glm::rotate(model, glm::radians(15.0f), glm::vec3(1, 0, 0));
	//projectionShader.setMat4("model", model);
	//Cilindro::riel(model);

	for (int i = 0; i < 4; i++) {
		model = glm::translate(model, glm::vec3(3.14, 0, 0));
		projectionShader.setMat4("model", model);
		Cilindro::riel(model);
	}

	model = glm::translate(model, glm::vec3(1.9, 0.2, 0));
	model = glm::scale(model, glm::vec3(0.1f, 1.0f, 1.0f));
	model = glm::rotate(model, glm::radians(15.0f), glm::vec3(0, 0, 1));
	projectionShader.setMat4("model", model);
	Cilindro::riel(model);

	model = glm::translate(model, glm::vec3(2.3, 0.2, 0));
	model = glm::rotate(model, glm::radians(15.0f), glm::vec3(0, 0, 1));
	projectionShader.setMat4("model", model);
	Cilindro::riel(model);

	//giro para cierre del camino
	for (int i = 0; i <7; i++) {
		model = glm::translate(model, glm::vec3(1.9, 0, 0.2));
		model = glm::rotate(model, glm::radians(-15.5f), glm::vec3(0, 1, 0));
		model = glm::rotate(model, glm::radians(-0.8f), glm::vec3(1, 0, 0));
		projectionShader.setMat4("model", model);
		Cilindro::riel(model);
	}



	model = glm::translate(model, glm::vec3(1.9, 0.0, 0.2));
	model = glm::scale(model, glm::vec3(2.5f, 1.0f, 1.2f));
	model = glm::rotate(model, glm::radians(-0.2f), glm::vec3(0, 1, 0));
	model = glm::rotate(model, glm::radians(-5.0f), glm::vec3(1, 0, 0));
	projectionShader.setMat4("model", model);
	Cilindro::riel(model);

	for (int i = 0; i < 2; i++) {
		model = glm::translate(model, glm::vec3(3.14, 0.0, 0));
		//model = glm::rotate(model, glm::radians(-15.0f), glm::vec3(0, 1, 0));
		//model = glm::rotate(model, glm::radians(5.5f), glm::vec3(0, 0, 1));
		projectionShader.setMat4("model", model);
		Cilindro::riel(model);
	}

	
	//camino de regreso al inicio
	model = temp04;

	for (int i = 0; i < 3; i++) {
		model = glm::translate(model, glm::vec3(-3.14, 0, 0));
		projectionShader.setMat4("model", model);
		Cilindro::riel(model);
	}

	//giro
	for (int i = 0; i < 5; i++) {
		model = glm::translate(model, glm::vec3(-2.2, 0.0, 0.3));
		model = glm::rotate(model, glm::radians(18.0f), glm::vec3(0, 1, 0));
		projectionShader.setMat4("model", model);
		Cilindro::riel(model);
	}

	model = glm::translate(model, glm::vec3(-4.6, 0, 0));
	model = glm::scale(model, glm::vec3(2.0f, 1.0f, 1.0f));
	projectionShader.setMat4("model", model);
	Cilindro::riel(model);

	for (int i = 0; i < 7; i++) {
		model = glm::translate(model, glm::vec3(-3.14, 0, 0));
		projectionShader.setMat4("model", model);
		Cilindro::riel(model);
	}

	for (int i = 0; i < 5; i++) {
		model = glm::translate(model, glm::vec3(-2.2, 0.0, 0.3));
		model = glm::rotate(model, glm::radians(18.0f), glm::vec3(0, 1, 0));
		projectionShader.setMat4("model", model);
		Cilindro::riel(model);
	}

	model = glm::translate(model, glm::vec3(-4.6, 0, 0));
	model = glm::scale(model, glm::vec3(2.0f, 1.0f, 1.0f));
	projectionShader.setMat4("model", model);
	Cilindro::riel(model);
	for (int i = 0; i < 21; i++) {
		model = glm::translate(model, glm::vec3(-3.14, 0, 0));
		projectionShader.setMat4("model", model);
		Cilindro::riel(model);
	}

	
	
	glBindVertexArray(0);
}



