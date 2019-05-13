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

void Cilindro::riel(glm::mat4 model, Shader projectionShader)
{
	//Shader projectionShader("shaders/shader_light.vs", "shaders/shader_light.fs");
	projectionShader.use();
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

void Cilindro::roller_coaster(Shader projectionShader)
{
	//Shader projectionShader("shaders/shader_light.vs", "shaders/shader_light.fs");//ponerlo como parametro para evitar que se cargue multiples veces
	projectionShader.use();
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
	model = glm::translate(model, glm::vec3(-30.0, -4.15, -70.0));//era -4.0
	//model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 1, 0));
	model = glm::scale(model, glm::vec3(0.3f, 0.2f, 0.2f));
	temp04 = model;
	projectionShader.setMat4("model", model);
	//projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	//projectionShader.setVec3("diffuseColor", 0.6f, 0.0f, 0.3f);
	//projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);

	Cilindro::riel(model, projectionShader);
	
	for (int i = 0; i < 11; i++) {
		model = glm::translate(model, glm::vec3(3.14, 0, 0));
		projectionShader.setMat4("model", model);
		Cilindro::riel(model, projectionShader);
	}
	
	//inicia curva de subida
	
	model = glm::translate(model, glm::vec3(2.0, 0.3, 0.0));
	model = glm::rotate(model, glm::radians(-30.0f), glm::vec3(0, 0, -1));
	model = glm::scale(model, glm::vec3(0.5f, 1.0f, 1.0f));
	projectionShader.setMat4("model", model);

	Cilindro::riel(model, projectionShader);

	model = glm::translate(model, glm::vec3(3.0, 0.4, 0.0));
	model = glm::rotate(model, glm::radians(-15.0f), glm::vec3(0, 0, -1));
	projectionShader.setMat4("model", model);
	Cilindro::riel(model, projectionShader);

	//model = glm::translate(model, glm::vec3(0, 0.55, 4.6));
	model = glm::translate(model, glm::vec3(6.15, 0.81, 0));
	model = glm::rotate(model, glm::radians(-10.0f), glm::vec3(0, 0, -1));
	model = glm::scale(model, glm::vec3(3.0f, 1.0f, 1.0f));
	projectionShader.setMat4("model", model);

	Cilindro::riel(model, projectionShader);
	
	//subida
	model = glm::translate(model, glm::vec3(4.71, 0.0, 0));
	model = glm::scale(model, glm::vec3(2.0f, 1.0f, 1.0));
	projectionShader.setMat4("model", model);

	Cilindro::riel(model, projectionShader);

	for (int i = 0; i < 5; i++) {
		model = glm::translate(model, glm::vec3(3.14, 0, 0));
		projectionShader.setMat4("model", model);
		Cilindro::riel(model, projectionShader);
	}
	//termina subida

	//curva antes de la caida
	model = glm::translate(model, glm::vec3(1.9, -0.7, 0));
	model = glm::scale(model, glm::vec3(0.3f, 1.0f, 1.0f));
	model = glm::rotate(model, glm::radians(-30.0f), glm::vec3(0, 0, 1));
	projectionShader.setMat4("model", model);

	Cilindro::riel(model, projectionShader);

	model = glm::translate(model, glm::vec3(2.9, -0.4, 0));
	//model = glm::scale(model, glm::vec3(1.0f, 1.0f, 0.5f));
	model = glm::rotate(model, glm::radians(-15.0f), glm::vec3(0, 0, 1));
	projectionShader.setMat4("model", model);

	Cilindro::riel(model, projectionShader);

	model = glm::translate(model, glm::vec3(3.0, -0.4, 0));
	//model = glm::scale(model, glm::vec3(1.0f, 1.0f, 0.5f));
	model = glm::rotate(model, glm::radians(-14.0f), glm::vec3(0, 0, 1));
	projectionShader.setMat4("model", model);

	Cilindro::riel(model, projectionShader);

	//antes de caida
	model = glm::scale(model, glm::vec3(2.0f, 1.0f, 1.0f));
	model = glm::translate(model, glm::vec3(2.35, 0.0, 0));
	//model = glm::rotate(model, glm::radians(30.0f), glm::vec3(1, 0, 0));
	projectionShader.setMat4("model", model);

	Cilindro::riel(model, projectionShader);

	//inicio de caida
	model = glm::translate(model, glm::vec3(1.8, -1.0, 0));
	model = glm::scale(model, glm::vec3(0.5f, 1.0f, 1.0f));
	model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(0, 0, 1));
	projectionShader.setMat4("model", model);

	Cilindro::riel(model, projectionShader);

	model = glm::translate(model, glm::vec3(3.0, -0.4, 0));
	//model = glm::scale(model, glm::vec3(1.0f, 1.0f, 0.5f));
	model = glm::rotate(model, glm::radians(-15.0f), glm::vec3(0, 0, 1));
	projectionShader.setMat4("model", model);

	Cilindro::riel(model, projectionShader);
	model = glm::translate(model, glm::vec3(5.3, -0.4, 0));
	model = glm::scale(model, glm::vec3(2.6f, 1.0f, 1.0f));
	model = glm::rotate(model, glm::radians(-15.0f), glm::vec3(0, 0, 1));
	projectionShader.setMat4("model", model);

	Cilindro::riel(model, projectionShader);
	


	//caida
	for (int i = 0; i < 4; i++) {
		model = glm::translate(model, glm::vec3(3.14, 0, 0));
		projectionShader.setMat4("model", model);
		Cilindro::riel(model, projectionShader);
	}
	


	//curva nivel del piso es practicamente = a la primer curva para la subida
	model = glm::translate(model, glm::vec3(1.9, 0.4, 0));
	model = glm::rotate(model, glm::radians(40.0f), glm::vec3(0, 0, 1));
	model = glm::scale(model, glm::vec3(0.5f, 1.0f, 1.0f));
	projectionShader.setMat4("model", model);

	Cilindro::riel(model, projectionShader);

	model = glm::translate(model, glm::vec3(2.9, 0.55, 0));
	model = glm::rotate(model, glm::radians(23.0f), glm::vec3(0, 0, 1));
	model = glm::scale(model, glm::vec3(1.0f, 0.8f, 1.0f));
	projectionShader.setMat4("model", model);
	Cilindro::riel(model, projectionShader);

	//model = glm::translate(model, glm::vec3(0, 0.55, 4.6));
	model = glm::translate(model, glm::vec3(3.7, 0.3, 0));
	model = glm::rotate(model, glm::radians(8.0f), glm::vec3(0, 0, 1));
	model = glm::scale(model, glm::vec3(1.5f, 1.0f, 1.0f));
	projectionShader.setMat4("model", model);

	Cilindro::riel(model, projectionShader);

	model = glm::translate(model, glm::vec3(3.0, 0.3, 0));
	model = glm::rotate(model, glm::radians(10.0f), glm::vec3(0, 0, 1));
	//model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.5f));
	projectionShader.setMat4("model", model);

	Cilindro::riel(model, projectionShader);
	//termina curva nivel de piso

	model = glm::translate(model, glm::vec3(3.8, 0.2, 0));
	model = glm::rotate(model, glm::radians(5.0f), glm::vec3(0, 0, 1));
	model = glm::scale(model, glm::vec3(1.5f, 0.8f, 1.0f));
	projectionShader.setMat4("model", model);

	Cilindro::riel(model, projectionShader);

//antes de giro de rueda
	for (int i = 0; i < 5; i++) {
		model = glm::translate(model, glm::vec3(3.14, 0, 0.0));
		projectionShader.setMat4("model", model);
		Cilindro::riel(model, projectionShader);
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
		Cilindro::riel(model, projectionShader);
	}
	
	
	//despues de la rueda, antes del ultimo giro
	
	
	model = glm::scale(model, glm::vec3(1.0f, 0.8f, 0.8f));
	for (int i = 0; i < 4; i++) {
		model = glm::translate(model, glm::vec3(3.14, 0, 0));
		projectionShader.setMat4("model", model);
		Cilindro::riel(model, projectionShader);
	}

	//model = glm::scale(model, glm::vec3(0.9f, 1.0f, 1.1f));
	
	for (int i = 0; i < 35; i++) {//e wey eran 20 xD
		model = glm::translate(model, glm::vec3(2.8, 0.0, 0));
		model = glm::rotate(model, glm::radians(-5.5f), glm::vec3(0, 1, 0));
		model = glm::rotate(model, glm::radians(1.5f), glm::vec3(0, 0, 1));
		model = glm::rotate(model, glm::radians(-0.5f), glm::vec3(1, 0, 0));
		projectionShader.setMat4("model", model);
		Cilindro::riel(model, projectionShader);
	}

	//model = glm::scale(model, glm::vec3(0.9f, 1.0f, 1.1f));
	for (int i = 0; i < 15; i++) {//e wey eran 15 xD
		model = glm::translate(model, glm::vec3(2.7, 0.2, 0.3));
		model = glm::rotate(model, glm::radians(-5.0f), glm::vec3(0, 1, 0));
		model = glm::rotate(model, glm::radians(0.4f), glm::vec3(0, 0, 1));
		//model = glm::rotate(model, glm::radians(-1.9f), glm::vec3(1, 0, 0));
		projectionShader.setMat4("model", model);
		Cilindro::riel(model, projectionShader);
	}

	model = glm::scale(model, glm::vec3(0.9f, 0.9f, 1.1f));
	for (int i = 0; i < 3; i++) {//ese we eran 6 xD
		model = glm::translate(model, glm::vec3(2.3, 0.0, 0.2));
		model = glm::rotate(model, glm::radians(-.0f), glm::vec3(0, 1, 0));
		model = glm::rotate(model, glm::radians(4.5f), glm::vec3(0, 0, 1));
		model = glm::rotate(model, glm::radians(-3.0f), glm::vec3(1, 0, 0));
		projectionShader.setMat4("model", model);
		Cilindro::riel(model, projectionShader);
	}
	
	model = glm::scale(model, glm::vec3(1.5f, 0.9f, 0.9f));
	model = glm::translate(model, glm::vec3(2.5, 0.0, 0));
	model = glm::rotate(model, glm::radians(5.0f), glm::vec3(0, 0, 1));
	projectionShader.setMat4("model", model);
	Cilindro::riel(model, projectionShader);
	for (int i = 0; i < 25; i++) {
		model = glm::translate(model, glm::vec3(3.0, 0.0, 0));
		model = glm::rotate(model, glm::radians(-2.5f), glm::vec3(0, 1, 0));
		model = glm::rotate(model, glm::radians(0.5f), glm::vec3(0, 0, 1));
		model = glm::rotate(model, glm::radians(2.0f), glm::vec3(1, 0, 0));
		projectionShader.setMat4("model", model);
		Cilindro::riel(model, projectionShader);
	}
	
	//curva final de caida entre la rueda
	model = glm::translate(model, glm::vec3(2.4, 0.2, 0));
	model = glm::rotate(model, glm::radians(10.0f), glm::vec3(0, 0, 1));
	model = glm::rotate(model, glm::radians(-4.0f), glm::vec3(1, 0, 0));
	model = glm::scale(model, glm::vec3(0.5f, 1.0f, 1.0f));
	projectionShader.setMat4("model", model);

	Cilindro::riel(model, projectionShader);

	model = glm::translate(model, glm::vec3(3.0, 0.3, 0));
	//model = glm::scale(model, glm::vec3(1.0f, 1.0f, 50.5f));
	model = glm::rotate(model, glm::radians(15.0f), glm::vec3(0, 0, 1));
	model = glm::rotate(model, glm::radians(-4.0f), glm::vec3(1, 0, 0));
	projectionShader.setMat4("model", model);
	Cilindro::riel(model, projectionShader);

	model = glm::translate(model, glm::vec3(4.3, 0.1, 0));
	model = glm::scale(model, glm::vec3(2.0f, 1.0f, 1.0f));
	model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0, 0, 1));
	model = glm::rotate(model, glm::radians(-4.0f), glm::vec3(1, 0, 0));
	projectionShader.setMat4("model", model);
	Cilindro::riel(model, projectionShader);
	
	for (int i = 0; i < 6; i++) {
		model = glm::translate(model, glm::vec3(3.14, 0, 0));
		model = glm::rotate(model, glm::radians(-4.5f), glm::vec3(1, 0, 0));
		projectionShader.setMat4("model", model);
		Cilindro::riel(model, projectionShader);
	}
	
	temp03 = model; //para seguir despues de la rueda
	//hasta aqui ya estan correguidos los angulos
	//ultima subida

	model = glm::translate(model, glm::vec3(2.0, 0.3, 0));
	model = glm::rotate(model, glm::radians(25.0f), glm::vec3(0, 0, 1));
	model = glm::scale(model, glm::vec3(0.5f, 1.0f, 1.0f));
	projectionShader.setMat4("model", model);

	Cilindro::riel(model, projectionShader);

	model = glm::translate(model, glm::vec3(3.0, 0.4, 0));
	model = glm::rotate(model, glm::radians(15.0f), glm::vec3(0, 0, 1));
	projectionShader.setMat4("model", model);
	Cilindro::riel(model, projectionShader);

	//model = glm::translate(model, glm::vec3(0, 0.55, 4.6));
	model = glm::translate(model, glm::vec3(3.0, 0.4, 0));
	model = glm::rotate(model, glm::radians(10.0f), glm::vec3(0, 0, 1));
	projectionShader.setMat4("model", model);

	Cilindro::riel(model, projectionShader);

	model = glm::translate(model, glm::vec3(4.1, 0.81, 0));
	model = glm::rotate(model, glm::radians(10.0f), glm::vec3(0, 0, 1));
	model = glm::scale(model, glm::vec3(3.0f, 1.0f, 1.0f));
	projectionShader.setMat4("model", model);

	Cilindro::riel(model, projectionShader);
	for (int i = 0; i < 7; i++) {
		model = glm::translate(model, glm::vec3(3.14, 0, 0));
		projectionShader.setMat4("model", model);
		Cilindro::riel(model, projectionShader);
	}

	//nivelar ultima caida
	model = glm::translate(model, glm::vec3(1.9, -0.7, 0));
	model = glm::scale(model, glm::vec3(0.3f, 1.0f, 1.0f));
	model = glm::rotate(model, glm::radians(-20.0f), glm::vec3(0, 0, 1));
	projectionShader.setMat4("model", model);

	Cilindro::riel(model, projectionShader);

	model = glm::translate(model, glm::vec3(2.9, -0.4, 0));
	//model = glm::scale(model, glm::vec3(1.0f, 1.0f, 0.5f));
	model = glm::rotate(model, glm::radians(-15.0f), glm::vec3(0, 0, 1));
	projectionShader.setMat4("model", model);

	Cilindro::riel(model, projectionShader);

	model = glm::translate(model, glm::vec3(2.8, -0.4, 0));
	//model = glm::scale(model, glm::vec3(1.0f, 1.0f, 0.5f));
	model = glm::rotate(model, glm::radians(-10.0f), glm::vec3(0, 0, 1));
	projectionShader.setMat4("model", model);

	Cilindro::riel(model, projectionShader);
	//antes de empezar ultima caida
	
	model = glm::scale(model, glm::vec3(2.0f, 1.0f, 1.0f));
	model = glm::translate(model, glm::vec3(2.8, 0, 0));
	projectionShader.setMat4("model", model);
	Cilindro::riel(model, projectionShader);
	
	//giro antes de la caida

	model = glm::translate(model, glm::vec3(2.2, 0.0, 0.5));
	model = glm::rotate(model, glm::radians(-20.0f), glm::vec3(0, 1, 0));
	model = glm::rotate(model, glm::radians(-2.0f), glm::vec3(1, 0, 0));
	model = glm::scale(model, glm::vec3(0.5f, 1.0f, 1.0f));
	projectionShader.setMat4("model", model);

	Cilindro::riel(model, projectionShader);

	model = glm::translate(model, glm::vec3(2.8, 0.0, 0.5));
	model = glm::rotate(model, glm::radians(-25.0f), glm::vec3(0, 1, 0));
	model = glm::rotate(model, glm::radians(-2.0f), glm::vec3(1, 0, 0));
	projectionShader.setMat4("model", model);
	Cilindro::riel(model, projectionShader);

	//model = glm::translate(model, glm::vec3(0, 0.55, 4.6));
	model = glm::translate(model, glm::vec3(2.8, 0.0, 0.5));
	model = glm::rotate(model, glm::radians(-25.0f), glm::vec3(0, 1, 0));
	model = glm::rotate(model, glm::radians(-2.0f), glm::vec3(1, 0, 0));
	projectionShader.setMat4("model", model);

	Cilindro::riel(model, projectionShader);

	model = glm::translate(model, glm::vec3(2.8, 0.0, 0.5));
	model = glm::rotate(model, glm::radians(-20.0f), glm::vec3(0, 1, 0));
	model = glm::rotate(model, glm::radians(-2.0f), glm::vec3(1, 0, 0));
	projectionShader.setMat4("model", model);

	Cilindro::riel(model, projectionShader);

	//primera
	model = glm::translate(model, glm::vec3(4.5, -0.8, 0));
	model = glm::scale(model, glm::vec3(3.0f, 1.0f, 1.0f));
	model = glm::rotate(model, glm::radians(-50.0f), glm::vec3(0, 0, 1));
	projectionShader.setMat4("model", model);

	Cilindro::riel(model, projectionShader);

	for (int i = 0; i < 15; i++) {
		model = glm::translate(model, glm::vec3(3.14, 0, 0));
		projectionShader.setMat4("model", model);
		Cilindro::riel(model, projectionShader);
	}

	//nivelar antes de la segunda caida
	model = glm::translate(model, glm::vec3(2.6, 0.9, 0));
	model = glm::scale(model, glm::vec3(0.7f, 1.0f, 0.9f));
	model = glm::rotate(model, glm::radians(40.0f), glm::vec3(0, 0, 1));
	model = glm::rotate(model, glm::radians(-5.0f), glm::vec3(1, 0, 0));
	projectionShader.setMat4("model", model);
	Cilindro::riel(model, projectionShader);

	//giro para segunda caida
	for (int i = 0; i < 10; i++) {
		model = glm::translate(model, glm::vec3(3.0, -0.2, 0.4));
		//model = glm::rotate(model, glm::radians(2.0f), glm::vec3(0, 0, 1));
		model = glm::rotate(model, glm::radians(-15.0f), glm::vec3(0, 1, 0));
		//if (i > 6) {
		//	model = glm::rotate(model, glm::radians(-15.0f), glm::vec3(0, 0, 1));
		//	model = glm::translate(model, glm::vec3(0.0, -0.3, 0.0));
		//}
		//model = glm::rotate(model, glm::radians(20.0f), glm::vec3(1, 0, 0));
		projectionShader.setMat4("model", model);
		Cilindro::riel(model, projectionShader);
	}

	//segunda
	model = glm::translate(model, glm::vec3(2.2, -0.2, 0));
	//model = glm::scale(model, glm::vec3(1.0f, 1.0f, 2.0f));
	model = glm::rotate(model, glm::radians(-15.0f), glm::vec3(0, 0, 1));
	projectionShader.setMat4("model", model);
	Cilindro::riel(model, projectionShader);

	for (int i = 0; i < 12; i++) {
		model = glm::translate(model, glm::vec3(3.14, 0, 0));
		model = glm::rotate(model, glm::radians(-0.3f), glm::vec3(1, 0, 0));
		projectionShader.setMat4("model", model);
		Cilindro::riel(model, projectionShader);
	}


	//nivelar antes de la tercera caida
	model = glm::translate(model, glm::vec3(2.6, 0.3, 0));
	model = glm::scale(model, glm::vec3(0.8f, 1.0f, 1.2f));
	model = glm::rotate(model, glm::radians(10.0f), glm::vec3(0, 0, 1));
	model = glm::rotate(model, glm::radians(-5.0f), glm::vec3(1, 0, 0));
	projectionShader.setMat4("model", model);
	Cilindro::riel(model, projectionShader);

	//model = glm::scale(model, glm::vec3(1.0f, 1.0f, 2.0f));
	projectionShader.setMat4("model", model);
	//giro para tercera y ultima caida
	for (int i = 0; i < 10; i++) {
		model = glm::translate(model, glm::vec3(2.2, -0.1, -0.5));
		model = glm::rotate(model, glm::radians(2.0f), glm::vec3(0, 0, 1));
		model = glm::rotate(model, glm::radians(14.0f), glm::vec3(0, 1, 0));
		if (i > 5) {
			model = glm::rotate(model, glm::radians(-12.0f), glm::vec3(0, 0, 1));
			model = glm::translate(model, glm::vec3(0.0, -0.2, 0));
		}
		//model = glm::rotate(model, glm::radians(20.0f), glm::vec3(1, 0, 0));
		projectionShader.setMat4("model", model);
		Cilindro::riel(model, projectionShader);
	}
	
	//tercera
	model = glm::translate(model, glm::vec3(3.1, -0.4, 0));
	model = glm::scale(model, glm::vec3(1.5f, 1.0f, 1.0f));
	model = glm::rotate(model, glm::radians(-10.0f), glm::vec3(0, 0, 1));
	projectionShader.setMat4("model", model);
	Cilindro::riel(model, projectionShader);



	//model = glm::translate(model, glm::vec3(0, -0.4, 2.2));
	//model = glm::scale(model, glm::vec3(1.0f, 1.0f, 2.0f));
	//model = glm::rotate(model, glm::radians(15.0f), glm::vec3(1, 0, 0));
	//projectionShader.setMat4("model", model);
	//Cilindro::riel(model);

	for (int i = 0; i < 13; i++) {
		model = glm::translate(model, glm::vec3(3.14, 0, 0));
		model = glm::rotate(model, glm::radians(-0.3f), glm::vec3(1, 0, 0));
		projectionShader.setMat4("model", model);
		Cilindro::riel(model, projectionShader);
	}


	model = glm::translate(model, glm::vec3(2.5, 1.1, 0.0));
	model = glm::rotate(model, glm::radians(60.0f), glm::vec3(0, 0, 1));
	projectionShader.setMat4("model", model);
	Cilindro::riel(model, projectionShader);

	
	
	//camino de regreso al inicio
	model = temp04;

	for (int i = 0; i < 3; i++) {
		model = glm::translate(model, glm::vec3(-3.14, 0, 0));
		projectionShader.setMat4("model", model);
		Cilindro::riel(model, projectionShader);
	}

	//giro
	for (int i = 0; i < 5; i++) {
		model = glm::translate(model, glm::vec3(-2.2, 0.0, 0.3));
		model = glm::rotate(model, glm::radians(18.0f), glm::vec3(0, 1, 0));
		projectionShader.setMat4("model", model);
		Cilindro::riel(model, projectionShader);
	}

	model = glm::translate(model, glm::vec3(-4.6, 0, 0));
	model = glm::scale(model, glm::vec3(2.0f, 1.0f, 1.0f));
	projectionShader.setMat4("model", model);
	Cilindro::riel(model, projectionShader);

	for (int i = 0; i < 7; i++) {
		model = glm::translate(model, glm::vec3(-3.14, 0, 0));
		projectionShader.setMat4("model", model);
		Cilindro::riel(model, projectionShader);
	}

	for (int i = 0; i < 5; i++) {
		model = glm::translate(model, glm::vec3(-2.2, 0.0, 0.3));
		model = glm::rotate(model, glm::radians(18.0f), glm::vec3(0, 1, 0));
		projectionShader.setMat4("model", model);
		Cilindro::riel(model, projectionShader);
	}

	model = glm::translate(model, glm::vec3(-4.6, 0, 0));
	model = glm::scale(model, glm::vec3(2.0f, 1.0f, 1.0f));
	projectionShader.setMat4("model", model);
	Cilindro::riel(model, projectionShader);
	for (int i = 0; i < 28; i++) {
		model = glm::translate(model, glm::vec3(-3.14, 0, 0));
		projectionShader.setMat4("model", model);
		Cilindro::riel(model, projectionShader);
	}

	model = glm::translate(model, glm::vec3(-3.9, 0, 0));
	model = glm::scale(model, glm::vec3(1.6f, 1.0f, 1.0f));
	projectionShader.setMat4("model", model);
	Cilindro::riel(model, projectionShader);

	//pilares
	model = temp04;

	model = glm::translate(model, glm::vec3(60.5, 37.0, -0.1));
	model = glm::scale(model, glm::vec3(0.5f, 24.0f, 0.5f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 0, 1));
	projectionShader.setMat4("model", model);
	Cilindro::render();

	model = glm::translate(model, glm::vec3(0.0, 0.0, 6.0));
	projectionShader.setMat4("model", model);
	Cilindro::render();


	model = temp04;
	model = glm::translate(model, glm::vec3(70.5, 37.0, -0.1));
	model = glm::scale(model, glm::vec3(0.5f, 25.0f, 0.5f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 0, 1));
	projectionShader.setMat4("model", model);
	Cilindro::render();

	model = glm::translate(model, glm::vec3(0.0, 0.0, 6.0));
	projectionShader.setMat4("model", model);
	Cilindro::render();


	model = temp04;
	model = glm::translate(model, glm::vec3(82.5, 8.0, -0.0));
	model = glm::scale(model, glm::vec3(0.5f, 6.5f, 0.5f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 0, 1));
	projectionShader.setMat4("model", model);
	Cilindro::render();

	model = glm::translate(model, glm::vec3(0.0, 0.0, 6.0));
	projectionShader.setMat4("model", model);
	Cilindro::render();

	model = temp04;
	model = glm::translate(model, glm::vec3(95.0, 5.5, -0.0));
	model = glm::scale(model, glm::vec3(0.5f, 5.5f, 0.5f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 0, 1));
	projectionShader.setMat4("model", model);
	Cilindro::render();

	model = glm::translate(model, glm::vec3(0.0, 0.0, 6.5));
	projectionShader.setMat4("model", model);
	Cilindro::render();


	model = temp04;
	model = glm::translate(model, glm::vec3(115.0, 5.5, -0.0));
	model = glm::scale(model, glm::vec3(0.5f, 5.5f, 0.5f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 0, 1));
	projectionShader.setMat4("model", model);
	Cilindro::render();

	model = glm::translate(model, glm::vec3(0.0, 0.0, 6.5));
	projectionShader.setMat4("model", model);
	Cilindro::render();


	//------------------inicia vuelta de rueda-----------------------------------
	model = temp04;
	model = glm::translate(model, glm::vec3(125.0, 10.0, -0.9));
	model = glm::scale(model, glm::vec3(0.5f, 8.5f, 0.5f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 0, 1));
	projectionShader.setMat4("model", model);
	Cilindro::render();


	model = glm::translate(model, glm::vec3(0.0, -1.0, 6.0));
	projectionShader.setMat4("model", model);
	Cilindro::render();

	model = temp04;
	model = glm::translate(model, glm::vec3(127.3, 14.0, -1.8));
	model = glm::scale(model, glm::vec3(0.5f, 12.0f, 0.5f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 0, 1));
	projectionShader.setMat4("model", model);
	Cilindro::render();

	model = glm::translate(model, glm::vec3(0.0, -1.5, 7.0));
	projectionShader.setMat4("model", model);
	Cilindro::render();

	//--------------------antes de terminar giro de rueda-----------------------------
	model = temp04;
	model = glm::translate(model, glm::vec3(86.5, 18.0, -6.8));
	model = glm::scale(model, glm::vec3(0.5f, 14.0f, 0.5f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 0, 1));
	projectionShader.setMat4("model", model);
	Cilindro::render();

	model = glm::translate(model, glm::vec3(0.0, 2.0, 6.0));
	projectionShader.setMat4("model", model);
	Cilindro::render();

	//termina rueda
	model = temp04;
	model = glm::translate(model, glm::vec3(95.0, 8.5, -8.3));
	model = glm::scale(model, glm::vec3(0.5f, 8.5f, 0.5f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 0, 1));
	projectionShader.setMat4("model", model);
	Cilindro::render();

	model = glm::translate(model, glm::vec3(0.0, 2.5, 6.5));
	projectionShader.setMat4("model", model);
	Cilindro::render();


	model = temp04;
	model = glm::translate(model, glm::vec3(110.0, 5.5, -9.0));
	model = glm::scale(model, glm::vec3(0.5f, 5.5f, 0.5f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 0, 1));
	projectionShader.setMat4("model", model);
	Cilindro::render();

	model = glm::translate(model, glm::vec3(0.0, 0.0, 6.5));
	projectionShader.setMat4("model", model);
	Cilindro::render();

	model = temp04;
	model = glm::translate(model, glm::vec3(135.0, 5.5, -8.3));
	model = glm::scale(model, glm::vec3(0.5f, 5.5f, 0.5f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 0, 1));
	projectionShader.setMat4("model", model);
	Cilindro::render();

	model = glm::translate(model, glm::vec3(0.0, 0.0, 5.4));
	projectionShader.setMat4("model", model);
	Cilindro::render();


	model = temp04;
	model = glm::translate(model, glm::vec3(154.0, 6.7, 5.3));
	model = glm::scale(model, glm::vec3(0.5f, 8.1f, 0.5f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 0, 1));
	projectionShader.setMat4("model", model);
	Cilindro::render();

	model = glm::translate(model, glm::vec3(0.0, -6.5, 0.0));
	projectionShader.setMat4("model", model);
	Cilindro::render();

	model = temp04;
	model = glm::translate(model, glm::vec3(149.0, 12.0, 24.0));
	model = glm::scale(model, glm::vec3(0.5f, 11.0f, 0.5f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 0, 1));
	projectionShader.setMat4("model", model);
	Cilindro::render();

	model = glm::translate(model, glm::vec3(0.0, -0.0, 7.0));
	model = glm::scale(model, glm::vec3(1.15f, 1.0f, 1.0f));
	projectionShader.setMat4("model", model);
	Cilindro::render();

	model = temp04;
	model = glm::translate(model, glm::vec3(130.0, 14.5, 30.5));
	model = glm::scale(model, glm::vec3(0.5f, 13.5f, 0.5f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 0, 1));
	projectionShader.setMat4("model", model);
	Cilindro::render();

	model = glm::translate(model, glm::vec3(0.05, 0.0, 5.0));
	model = glm::scale(model, glm::vec3(1.08f, 1.0f, 1.0f));
	projectionShader.setMat4("model", model);
	Cilindro::render();

	model = temp04;
	model = glm::translate(model, glm::vec3(99.8, 16.0, 16.5));
	model = glm::scale(model, glm::vec3(0.5f, 14.0f, 0.5f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 0, 1));
	projectionShader.setMat4("model", model);
	Cilindro::render();

	model = glm::translate(model, glm::vec3(0.02, 8.0, -2.0));
	projectionShader.setMat4("model", model);
	Cilindro::render();

	model = temp04;
	model = glm::translate(model, glm::vec3(110.0, 10.5, -30.5));
	model = glm::scale(model, glm::vec3(0.5f, 10.0f, 0.5f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 0, 1));
	projectionShader.setMat4("model", model);
	Cilindro::render();

	model = glm::translate(model, glm::vec3(0.00, -2.0, 8.5));
	projectionShader.setMat4("model", model);
	Cilindro::render();

	model = temp04;
	model = glm::translate(model, glm::vec3(130.0, 8.5, -50.5));
	model = glm::scale(model, glm::vec3(0.5f, 7.5f, 0.5f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 0, 1));
	projectionShader.setMat4("model", model);
	Cilindro::render();

	model = glm::translate(model, glm::vec3(-0.07, 0.0, 7.0));
	projectionShader.setMat4("model", model);
	Cilindro::render();


	model = temp04;
	model = glm::translate(model, glm::vec3(160.0, 4.5, -64.5));
	model = glm::scale(model, glm::vec3(0.5f, 4.0f, 0.5f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 0, 1));
	projectionShader.setMat4("model", model);
	Cilindro::render();

	model = glm::translate(model, glm::vec3(-0.0, 0.0, 6.0));
	model = glm::scale(model, glm::vec3(0.8f, 1.0f, 1.0f));
	projectionShader.setMat4("model", model);
	Cilindro::render();

	model = temp04;
	model = glm::translate(model, glm::vec3(188.0, 5.5, -62.5));
	model = glm::scale(model, glm::vec3(0.5f, 5.0f, 0.5f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 0, 1));
	projectionShader.setMat4("model", model);
	Cilindro::render();

	model = glm::translate(model, glm::vec3(-0.07, 0.0, 6.4));
	projectionShader.setMat4("model", model);
	Cilindro::render();

	model = temp04;
	model = glm::translate(model, glm::vec3(203.0, 30.0, -55.8));
	model = glm::scale(model, glm::vec3(0.5f, 22.0f, 0.5f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 0, 1));
	projectionShader.setMat4("model", model);
	Cilindro::render();

	model = glm::translate(model, glm::vec3(0.00, 0.0, 7.0));
	projectionShader.setMat4("model", model);
	Cilindro::render();

	model = temp04;
	model = glm::translate(model, glm::vec3(212.0, 30.0, -50.0));
	model = glm::scale(model, glm::vec3(0.5f, 22.0f, 0.5f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 0, 1));
	projectionShader.setMat4("model", model);
	Cilindro::render();

	model = glm::translate(model, glm::vec3(0.00, 5.0, 0.0));
	projectionShader.setMat4("model", model);
	Cilindro::render();

	model = temp04;
	model = glm::translate(model, glm::vec3(212.5, 25.0, -5.0));
	model = glm::scale(model, glm::vec3(0.5f, 18.0f, 0.5f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 0, 1));
	projectionShader.setMat4("model", model);
	Cilindro::render();

	model = glm::translate(model, glm::vec3(0.00, 4.5, 0.0));
	projectionShader.setMat4("model", model);
	Cilindro::render();

	model = temp04;
	model = glm::translate(model, glm::vec3(213.5, 18.0, 46.5));
	model = glm::scale(model, glm::vec3(0.5f, 13.0f, 0.5f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 0, 1));
	projectionShader.setMat4("model", model);
	Cilindro::render();

	model = glm::translate(model, glm::vec3(0.00, 4.5, 0.0));
	projectionShader.setMat4("model", model);
	Cilindro::render();

	model = temp04;
	model = glm::translate(model, glm::vec3(203.0, 18.0, 71.5));
	model = glm::scale(model, glm::vec3(0.5f, 13.5f, 0.5f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 0, 1));
	projectionShader.setMat4("model", model);
	Cilindro::render();

	model = glm::translate(model, glm::vec3(0.00, 0.0, 14.0));
	projectionShader.setMat4("model", model);
	Cilindro::render();

	model = temp04;
	model = glm::translate(model, glm::vec3(199.5, 18.0, 55.5));
	model = glm::scale(model, glm::vec3(0.5f, 13.0f, 0.5f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 0, 1));
	projectionShader.setMat4("model", model);
	Cilindro::render();

	model = glm::translate(model, glm::vec3(0.00, 5.0, 0.0));
	projectionShader.setMat4("model", model);
	Cilindro::render();

	model = temp04;
	model = glm::translate(model, glm::vec3(199.5, 17.0, 25.5));
	model = glm::scale(model, glm::vec3(0.5f, 12.0f, 0.5f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 0, 1));
	projectionShader.setMat4("model", model);
	Cilindro::render();

	model = glm::translate(model, glm::vec3(0.00, 4.0, 0.0));
	projectionShader.setMat4("model", model);
	Cilindro::render();

	model = temp04;
	model = glm::translate(model, glm::vec3(200.5, 14.5, -20.5));
	model = glm::scale(model, glm::vec3(0.5f, 11.0f, 0.5f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 0, 1));
	projectionShader.setMat4("model", model);
	Cilindro::render();

	model = glm::translate(model, glm::vec3(0.00, 4.0, 0.0));
	projectionShader.setMat4("model", model);
	Cilindro::render();

	model = temp04;
	model = glm::translate(model, glm::vec3(192.0, 14.5, -33.0));
	model = glm::scale(model, glm::vec3(0.5f, 11.0f, 0.5f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 0, 1));
	projectionShader.setMat4("model", model);
	Cilindro::render();

	model = glm::translate(model, glm::vec3(0.00, 0.0, 10.0));
	projectionShader.setMat4("model", model);
	Cilindro::render();

	model = temp04;
	model = glm::translate(model, glm::vec3(185.5, 14.0, -10.0));
	model = glm::scale(model, glm::vec3(0.5f, 10.5f, 0.5f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 0, 1));
	projectionShader.setMat4("model", model);
	Cilindro::render();

	model = glm::translate(model, glm::vec3(0.00, 4.0, 0.0));
	projectionShader.setMat4("model", model);
	Cilindro::render();

	model = temp04;
	model = glm::translate(model, glm::vec3(185.5, 7.0, 20.0));
	model = glm::scale(model, glm::vec3(0.5f, 6.0f, 0.5f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 0, 1));
	projectionShader.setMat4("model", model);
	Cilindro::render();

	model = glm::translate(model, glm::vec3(0.00, 4.5, 0.0));
	projectionShader.setMat4("model", model);
	Cilindro::render();
	
	glBindVertexArray(0);
}



