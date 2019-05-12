#include "canasta.h"

//glm::vec3 lightPos(0.0f, 0.0f, 0.0f);
//GLuint VBO, VAO, lightVAO;

Canasta my_rueda1(1.0);
//Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
//int SCR_WIDTH = 3800;
//int SCR_HEIGHT = 7600;

Canasta::Canasta(GLfloat radio) :

	radio(radio) {
	canasta_VAO[4] = (-1, -1, -1, -1);
	canasta_VBO[4] = (-1, -1, -1, -1);

}


Canasta::~Canasta()
{
	glDeleteVertexArrays(4, canasta_VAO);
	glDeleteBuffers(4, canasta_VBO);
}



void Canasta::init()
{
	
	const int nn = PARALELOS * MERIDIANOS * 3;
	GLfloat canasta_nor[nn]; // normal
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
			/*x = cos(a)*(2+cos(b));
			y = sin(a)*(2+cos(b));
			z = sin(b);*/
			canasta_pos[ix + 0] = x * r;
			canasta_pos[ix + 1] = y * r;
			canasta_pos[ix + 2] = z * r;
			canasta_nor[ix + 0] = x;
			canasta_nor[ix + 1] = y;
			canasta_nor[ix + 2] = z;
		}
	// [Generate GL_TRIANGLE indices]
	for (ix = 0, iy = 0, ib = 1; ib < PARALELOS; ib++)
	{
		for (ia = 1; ia < MERIDIANOS; ia++, iy++)
		{
			// first half of QUAD
			canasta_index[ix] = iy;      ix++;
			canasta_index[ix] = iy + 1;    ix++;
			canasta_index[ix] = iy + MERIDIANOS;   ix++;
			// second half of QUAD
			canasta_index[ix] = iy + MERIDIANOS;   ix++;
			canasta_index[ix] = iy + 1;    ix++;
			canasta_index[ix] = iy + MERIDIANOS + 1; ix++;
		}
		// first half of QUAD
		canasta_index[ix] = iy;       ix++;
		canasta_index[ix] = iy + 1 - MERIDIANOS;  ix++;
		canasta_index[ix] = iy + MERIDIANOS;    ix++;
		// second half of QUAD
		canasta_index[ix] = iy + MERIDIANOS;    ix++;
		canasta_index[ix] = iy - MERIDIANOS + 1;  ix++;
		canasta_index[ix] = iy + 1;     ix++;
		iy++;
	}
	float vertices[] = {
		// positions          // normals           // texture coords
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,


		//////Segunda caja
		//Position			  //Normals			   //Texture Coords
		//Trasera
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, 1.0f,  0.25f,  0.333f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, 1.0f,  0.5f,  0.333f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, 1.0f,  0.5f,  0.666f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, 1.0f,  0.25f,  0.666f,
		//Frontal
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  -1.0f,  1.0f,  0.333f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  -1.0f,  0.75f,  0.333f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  -1.0f,  0.75f,  0.666f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  -1.0f,  1.0f,  0.666f,

		//Izquierda
		-0.5f, -0.5f, -0.5f, 1.0f,  0.0f,  0.0f,  0.25f,  0.333f,
		-0.5f, -0.5f,  0.5f, 1.0f,  0.0f,  0.0f,  0.0f,  0.333f,
		-0.5f,  0.5f,  0.5f, 1.0f,  0.0f,  0.0f,  0.0f,  0.666f,
		-0.5f,  0.5f, -0.5f, 1.0f,  0.0f,  0.0f,  0.25f,  0.666f,

		//Derecha
		0.5f,  -0.5f,   0.5f,  -1.0f,  0.0f,  0.0f,  0.75f,  0.333f,
		0.5f,	0.5f,	0.5f,  -1.0f,  0.0f,  0.0f,  0.75f,  0.666f,
		0.5f,   0.5f,  -0.5f,  -1.0f,  0.0f,  0.0f,  0.5f,  0.666f,
		0.5f,  -0.5f,  -0.5f,  -1.0f,  0.0f,  0.0f,  0.5f,  0.333f,
		//Inferior
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.25f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.5f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.5f,  0.333f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.25f,  0.333f,
		//Superior
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.25f, 0.666f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.5f,  0.666f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.5f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.25f,  1.0f,

		/*//Cara de atrás
		Auxiliar:
		-0.5f,  0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f,  0.5f, -0.5f,

		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,		0.0f,  0.0f, -1.0f,//Bottom Left
		0.5f, -0.5f, -0.5f,  1.0f, 0.0f,		0.0f,  0.0f, -1.0f,//Bottom Right
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,		0.0f,  0.0f, -1.0f,//Top Right
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,		0.0f,  0.0f, -1.0f,//Top Left

		//Cara de enfrente
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,		0.0f,  0.0f, 1.0f,//Bottom Left
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,		0.0f,  0.0f, 1.0f,//Bottom Right
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,		0.0f,  0.0f, 1.0f,//Top Right
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,		0.0f,  0.0f, 1.0f,//Top Left

		//Cara de la izquierda
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,		-1.0f,  0.0f, 0.0f,//Bottom Left
		-0.5f, -0.5f,  0.5f,  1.0f, 0.0f,		-1.0f,  0.0f, 0.0f,//Bottom Right
		-0.5f,  0.5f,  0.5f,  1.0f, 1.0f,		-1.0f,  0.0f, 0.0f,//Top Right
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,		-1.0f,  0.0f, 0.0f,//Top Left

		//Cara de la derecha
		0.5f, -0.5f,  0.5f,  0.0f, 0.0f,		1.0f,  0.0f, 0.0f,//Bottom Left
		0.5f, -0.5f, -0.5f,  1.0f, 0.0f,		1.0f,  0.0f, 0.0f,//Bottom Right
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,		1.0f,  0.0f, 0.0f,//Top Right
		0.5f,  0.5f,  0.5f,  0.0f, 1.0f,		1.0f,  0.0f, 0.0f,//Top Left

		//Cara de abajo
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,		0.0f,  -1.0f, 0.0f,//Bottom Left
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,		0.0f,  -1.0f, 0.0f,//Bottom Right
		0.5f, -0.5f,  0.5f,  1.0f,  1.0f,		0.0f,  -1.0f, 0.0f,//Top Right
		-0.5f, -0.5f,  0.5f,  0.0f, 1.0f,		0.0f,  -1.0f, 0.0f,//Top Left

		//Cara de arriba
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,		0.0f,  1.0f, 0.0f,//Bottom Left
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,		0.0f,  1.0f, 0.0f,//Bottom Right
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,		0.0f,  1.0f, 0.0f,//Top Right
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,		0.0f,  1.0f, 0.0f,//Top Left*/
	};

	unsigned int indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};

	/*glGenVertexArrays(1, &canasta_VAO);
	glGenBuffers(1, &canasta_VBO);
	glGenBuffers(1, &canasta_EBO);

	glBindVertexArray(canasta_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, canasta_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, canasta_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
	// [VAO/VBO stuff]*/
	GLuint i;
	glGenVertexArrays(4, canasta_VAO);
	glGenBuffers(4, canasta_VBO);
	glBindVertexArray(canasta_VAO[0]);
	i = 0; // vertex
	glBindBuffer(GL_ARRAY_BUFFER, canasta_VBO[i]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(canasta_pos), canasta_pos, GL_STATIC_DRAW);
	glEnableVertexAttribArray(i);
	glVertexAttribPointer(i, 3, GL_FLOAT, GL_FALSE, 0, 0);
	i = 1; // normal
	glBindBuffer(GL_ARRAY_BUFFER, canasta_VBO[i]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(canasta_nor), canasta_nor, GL_STATIC_DRAW);
	glEnableVertexAttribArray(i);
	glVertexAttribPointer(i, 3, GL_FLOAT, GL_FALSE, 0, 0);
	i = 2; // indices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, canasta_VBO[i]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(canasta_index), canasta_index, GL_STATIC_DRAW);
	glEnableVertexAttribArray(i);
	glVertexAttribPointer(i, 4, GL_UNSIGNED_INT, GL_FALSE, 0, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}

void Canasta::render()
{
	//glEnable(GL_CULL_FACE);
	//glFrontFace(GL_CCW);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glBindVertexArray(canasta_VAO[0]);
	//  glDrawArrays(GL_POINTS,0,sizeof(esfera_pos)/sizeof(GLfloat));                   // POINTS ... no indices for debug
	glDrawElements(GL_TRIANGLES, sizeof(canasta_index) / sizeof(GLuint), GL_UNSIGNED_INT, 0);    // indices (choose just one line not both !!!)
	glBindVertexArray(0);
}


void Canasta::dibujaCanasta(unsigned int tex1, Shader ligthShader,Shader textureShader, glm::mat4 model, glm::mat4 temp01, GLuint canast_VBO, GLuint canasta_VAO, GLuint canasta_EBO, float angRotPuerta)
{
	//Shader projectionShader("shaders/shader_light.vs", "shaders/shader_light.fs");
	//glBindVertexArray(lightVAO);
	//glEnable(GL_CULL_FACE);
	//glFrontFace(GL_CCW);
	//glm::mat4 temp01 = glm::mat4(1.0f); //Temp
	glm::mat4 temp02 = glm::mat4(1.0f); //Temp
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glBindVertexArray(canasta_VAO);

	
	ligthShader.use();
	model = glm::translate(model, glm::vec3(0.0f, -1.7, 1.0f));
	model = glm::scale(model, glm::vec3(1.0f, 1.5f, 1.5f));
	//model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 1, 0));
	//textureShader.setMat4("model", model);
	ligthShader.setMat4("model", model);
	ligthShader.setInt("material_diffuse", tex1);
	//textureShader.setMat4("projection", projection);
	temp02 = model;
	/*projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.6f, 0.0f, 0.3f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);*/


	for (int i = 0; i < 4; i++)
	{
		glDrawArrays(GL_TRIANGLE_FAN, 0, i + 1);
	}
	for (int i = 0; i < 4; i++)
	{
		glDrawArrays(GL_TRIANGLE_FAN, 4, i + 1);
	}
	for (int i = 0; i < 4; i++)
	{
		glDrawArrays(GL_TRIANGLE_FAN, 8, i + 1);
	}
	for (int i = 0; i < 4; i++)
	{
		glDrawArrays(GL_TRIANGLE_FAN, 12, i + 1);
	}
	for (int i = 0; i < 4; i++)
	{
		glDrawArrays(GL_TRIANGLE_FAN, 16, i + 1);
	}
	for (int i = 0; i < 4; i++)
	{
		glDrawArrays(GL_TRIANGLE_FAN, 20, i + 1);
	}
	for (int i = 0; i < 4; i++)
	{
		glDrawArrays(GL_TRIANGLE_FAN, 24, i + 1);
	}
	//textureShader.use();
	//Parte superior de la canata 
	model = temp02;
	model = glm::scale(model, glm::vec3(2, 0.25, 6)); //HACEMOS UN "MODELO" ESCALADO CON MEDIDAS 5 * 1 * 3 UNIDADES
	ligthShader.setMat4("model", model);
	ligthShader.setInt("material_diffuse", tex1);
	//textureShader.setMat4("projection", projection);

	for (int i = 0; i < 4; i++)
	{
		glDrawArrays(GL_TRIANGLE_FAN, 0, i + 1);
	}
	for (int i = 0; i < 4; i++)
	{
		glDrawArrays(GL_TRIANGLE_FAN, 4, i + 1);
	}
	for (int i = 0; i < 4; i++)
	{
		glDrawArrays(GL_TRIANGLE_FAN, 8, i + 1);
	}
	for (int i = 0; i < 4; i++)
	{
		glDrawArrays(GL_TRIANGLE_FAN, 12, i + 1);
	}
	for (int i = 0; i < 4; i++)
	{
		glDrawArrays(GL_TRIANGLE_FAN, 16, i + 1);
	}
	for (int i = 0; i < 4; i++)
	{
		glDrawArrays(GL_TRIANGLE_FAN, 20, i + 1);
	}
	for (int i = 0; i < 4; i++)
	{
		glDrawArrays(GL_TRIANGLE_FAN, 24, i + 1);
	}
	//Parte superior de la canasta

	//Postes que sostienen
	//POSTE 1
	model = temp02;
	model = glm::translate(model, glm::vec3(0.9f, -3.0f, 2.0f));
	model = glm::scale(model, glm::vec3(0.1, 6, 0.1)); //HACEMOS UN "MODELO" ESCALADO CON MEDIDAS 5 * 1 * 3 UNIDADES
	ligthShader.setMat4("model", model);
	ligthShader.setInt("material_diffuse", tex1);
	//textureShader.setMat4("projection", projection);
	for (int i = 0; i < 4; i++)
	{
		glDrawArrays(GL_TRIANGLE_FAN, 0, i + 1);
	}
	for (int i = 0; i < 4; i++)
	{
		glDrawArrays(GL_TRIANGLE_FAN, 4, i + 1);
	}
	for (int i = 0; i < 4; i++)
	{
		glDrawArrays(GL_TRIANGLE_FAN, 8, i + 1);
	}
	for (int i = 0; i < 4; i++)
	{
		glDrawArrays(GL_TRIANGLE_FAN, 12, i + 1);
	}
	for (int i = 0; i < 4; i++)
	{
		glDrawArrays(GL_TRIANGLE_FAN, 16, i + 1);
	}
	for (int i = 0; i < 4; i++)
	{
		glDrawArrays(GL_TRIANGLE_FAN, 20, i + 1);
	}
	for (int i = 0; i < 4; i++)
	{
		glDrawArrays(GL_TRIANGLE_FAN, 24, i + 1);
	}
	//POSTE 2
	model = temp02;
	model = glm::translate(model, glm::vec3(-0.9f, -3.0f, 2.0f));
	model = glm::scale(model, glm::vec3(0.1, 6, 0.1)); //HACEMOS UN "MODELO" ESCALADO CON MEDIDAS 5 * 1 * 3 UNIDADES
	ligthShader.setMat4("model", model);
	ligthShader.setInt("material_diffuse", tex1);
	//textureShader.setMat4("projection", projection);

	for (int i = 0; i < 4; i++)
	{
		glDrawArrays(GL_TRIANGLE_FAN, 0, i + 1);
	}
	for (int i = 0; i < 4; i++)
	{
		glDrawArrays(GL_TRIANGLE_FAN, 4, i + 1);
	}
	for (int i = 0; i < 4; i++)
	{
		glDrawArrays(GL_TRIANGLE_FAN, 8, i + 1);
	}
	for (int i = 0; i < 4; i++)
	{
		glDrawArrays(GL_TRIANGLE_FAN, 12, i + 1);
	}
	for (int i = 0; i < 4; i++)
	{
		glDrawArrays(GL_TRIANGLE_FAN, 16, i + 1);
	}
	for (int i = 0; i < 4; i++)
	{
		glDrawArrays(GL_TRIANGLE_FAN, 20, i + 1);
	}
	for (int i = 0; i < 4; i++)
	{
		glDrawArrays(GL_TRIANGLE_FAN, 24, i + 1);
	}
	//POSTE 3
	model = temp02;
	model = glm::translate(model, glm::vec3(0.9f, -3.0f, -2.0f));
	model = glm::scale(model, glm::vec3(0.1, 6, 0.1)); //HACEMOS UN "MODELO" ESCALADO CON MEDIDAS 5 * 1 * 3 UNIDADES
	ligthShader.setMat4("model", model);
	ligthShader.setInt("material_diffuse", tex1);
	//textureShader.setMat4("projection", projection);

	for (int i = 0; i < 4; i++)
	{
		glDrawArrays(GL_TRIANGLE_FAN, 0, i + 1);
	}
	for (int i = 0; i < 4; i++)
	{
		glDrawArrays(GL_TRIANGLE_FAN, 4, i + 1);
	}
	for (int i = 0; i < 4; i++)
	{
		glDrawArrays(GL_TRIANGLE_FAN, 8, i + 1);
	}
	for (int i = 0; i < 4; i++)
	{
		glDrawArrays(GL_TRIANGLE_FAN, 12, i + 1);
	}
	for (int i = 0; i < 4; i++)
	{
		glDrawArrays(GL_TRIANGLE_FAN, 16, i + 1);
	}
	for (int i = 0; i < 4; i++)
	{
		glDrawArrays(GL_TRIANGLE_FAN, 20, i + 1);
	}
	for (int i = 0; i < 4; i++)
	{
		glDrawArrays(GL_TRIANGLE_FAN, 24, i + 1);
	}

	//POSTE 4
	model = temp02;
	model = glm::translate(model, glm::vec3(-0.9f, -3.0f, -2.0f));
	model = glm::scale(model, glm::vec3(0.1, 6, 0.1)); //HACEMOS UN "MODELO" ESCALADO CON MEDIDAS 5 * 1 * 3 UNIDADES
	ligthShader.setMat4("model", model);
	ligthShader.setInt("material_diffuse", tex1);
	//textureShader.setMat4("projection", projection);

	for (int i = 0; i < 4; i++)
	{
		glDrawArrays(GL_TRIANGLE_FAN, 0, i + 1);
	}
	for (int i = 0; i < 4; i++)
	{
		glDrawArrays(GL_TRIANGLE_FAN, 4, i + 1);
	}
	for (int i = 0; i < 4; i++)
	{
		glDrawArrays(GL_TRIANGLE_FAN, 8, i + 1);
	}
	for (int i = 0; i < 4; i++)
	{
		glDrawArrays(GL_TRIANGLE_FAN, 12, i + 1);
	}
	for (int i = 0; i < 4; i++)
	{
		glDrawArrays(GL_TRIANGLE_FAN, 16, i + 1);
	}
	for (int i = 0; i < 4; i++)
	{
		glDrawArrays(GL_TRIANGLE_FAN, 20, i + 1);
	}
	for (int i = 0; i < 4; i++)
	{
		glDrawArrays(GL_TRIANGLE_FAN, 24, i + 1);
	}
	//POSTES QUE SOSTIENEN LA CANASTA.
	//Laterales de la canasta. 
	//Costado izquierdo
	model = temp02;
	model = glm::translate(model, glm::vec3(-1.0f, -4.5, 0.0f));
	model = glm::scale(model, glm::vec3(0.025f, 3.0f, 6.0f)); //HACEMOS UN "MODELO" ESCALADO CON MEDIDAS 5 * 1 * 3 UNIDADES
	ligthShader.setMat4("model", model);
	ligthShader.setInt("material_diffuse", tex1);
	//textureShader.setMat4("projection", projection);

	for (int i = 0; i < 4; i++)
	{
		glDrawArrays(GL_TRIANGLE_FAN, 0, i + 1);
	}
	for (int i = 0; i < 4; i++)
	{
		glDrawArrays(GL_TRIANGLE_FAN, 4, i + 1);
	}
	for (int i = 0; i < 4; i++)
	{
		glDrawArrays(GL_TRIANGLE_FAN, 8, i + 1);
	}
	for (int i = 0; i < 4; i++)
	{
		glDrawArrays(GL_TRIANGLE_FAN, 12, i + 1);
	}
	for (int i = 0; i < 4; i++)
	{
		glDrawArrays(GL_TRIANGLE_FAN, 16, i + 1);
	}
	for (int i = 0; i < 4; i++)
	{
		glDrawArrays(GL_TRIANGLE_FAN, 20, i + 1);
	}
	for (int i = 0; i < 4; i++)
	{
		glDrawArrays(GL_TRIANGLE_FAN, 24, i + 1);
	}
	//Costado Izquierdo 
	model = temp02;
	model = glm::translate(model, glm::vec3(1.0f, -4.5, 0.0f));
	model = glm::scale(model, glm::vec3(0.025f, 3.0f, 6.0f)); //HACEMOS UN "MODELO" ESCALADO CON MEDIDAS 5 * 1 * 3 UNIDADES
	ligthShader.setMat4("model", model);
	ligthShader.setInt("material_diffuse", tex1);
	//textureShader.setMat4("projection", projection);

	for (int i = 0; i < 4; i++)
	{
		glDrawArrays(GL_TRIANGLE_FAN, 0, i + 1);
	}
	for (int i = 0; i < 4; i++)
	{
		glDrawArrays(GL_TRIANGLE_FAN, 4, i + 1);
	}
	for (int i = 0; i < 4; i++)
	{
		glDrawArrays(GL_TRIANGLE_FAN, 8, i + 1);
	}
	for (int i = 0; i < 4; i++)
	{
		glDrawArrays(GL_TRIANGLE_FAN, 12, i + 1);
	}
	for (int i = 0; i < 4; i++)
	{
		glDrawArrays(GL_TRIANGLE_FAN, 16, i + 1);
	}
	for (int i = 0; i < 4; i++)
	{
		glDrawArrays(GL_TRIANGLE_FAN, 20, i + 1);
	}
	for (int i = 0; i < 4; i++)
	{
		glDrawArrays(GL_TRIANGLE_FAN, 24, i + 1);
	}
	//Parte delantera. 
	model = temp02;
	model = glm::translate(model, glm::vec3(1.0f, -4.5f, -3.0f));
	model = glm::rotate(model, glm::radians(angRotPuerta), glm::vec3(0, 1, 0));//rotamos
	model = glm::translate(model, glm::vec3(-1.0f, 0.0f, 0.0f));
	ligthShader.setMat4("model", model);
	//ligthShader.setInt("material_diffuse", tex1);
	model = glm::scale(model, glm::vec3(2.0f, 3.0f, 0.025f)); //HACEMOS UN "MODELO" ESCALADO CON MEDIDAS 5 * 1 * 3 UNIDADES
	ligthShader.setMat4("model", model);
	ligthShader.setInt("material_diffuse", tex1);
	//textureShader.setMat4("projection", projection);

	for (int i = 0; i < 4; i++)
	{
		glDrawArrays(GL_TRIANGLE_FAN, 0, i + 1);
	}
	for (int i = 0; i < 4; i++)
	{
		glDrawArrays(GL_TRIANGLE_FAN, 4, i + 1);
	}
	for (int i = 0; i < 4; i++)
	{
		glDrawArrays(GL_TRIANGLE_FAN, 8, i + 1);
	}
	for (int i = 0; i < 4; i++)
	{
		glDrawArrays(GL_TRIANGLE_FAN, 12, i + 1);
	}
	for (int i = 0; i < 4; i++)
	{
		glDrawArrays(GL_TRIANGLE_FAN, 16, i + 1);
	}
	for (int i = 0; i < 4; i++)
	{
		glDrawArrays(GL_TRIANGLE_FAN, 20, i + 1);
	}
	for (int i = 0; i < 4; i++)
	{
		glDrawArrays(GL_TRIANGLE_FAN, 24, i + 1);
	}
	//Asientos en canastas
	//Asiento
	model = temp02;
	model = glm::translate(model, glm::vec3(0.0f, -4.5, 0.0f));
	model = glm::scale(model, glm::vec3(2.0f, 0.25f, 1.0f)); //HACEMOS UN "MODELO" ESCALADO CON MEDIDAS 5 * 1 * 3 UNIDADES
	ligthShader.setMat4("model", model);
	ligthShader.setInt("material_diffuse", tex1);
	//textureShader.setMat4("projection", projection);

	for (int i = 0; i < 4; i++)
	{
		glDrawArrays(GL_TRIANGLE_FAN, 0, i + 1);
	}
	for (int i = 0; i < 4; i++)
	{
		glDrawArrays(GL_TRIANGLE_FAN, 4, i + 1);
	}
	for (int i = 0; i < 4; i++)
	{
		glDrawArrays(GL_TRIANGLE_FAN, 8, i + 1);
	}
	for (int i = 0; i < 4; i++)
	{
		glDrawArrays(GL_TRIANGLE_FAN, 12, i + 1);
	}
	for (int i = 0; i < 4; i++)
	{
		glDrawArrays(GL_TRIANGLE_FAN, 16, i + 1);
	}
	for (int i = 0; i < 4; i++)
	{
		glDrawArrays(GL_TRIANGLE_FAN, 20, i + 1);
	}
	for (int i = 0; i < 4; i++)
	{
		glDrawArrays(GL_TRIANGLE_FAN, 24, i + 1);
	}
	//Asiento 
	model = temp02;
	model = glm::translate(model, glm::vec3(0.0f, -5.3, -0.5f));
	model = glm::scale(model, glm::vec3(2.0f, 1.5f, 0.025f)); //HACEMOS UN "MODELO" ESCALADO CON MEDIDAS 5 * 1 * 3 UNIDADES
	ligthShader.setMat4("model", model);
	ligthShader.setInt("material_diffuse", tex1);
	//textureShader.setMat4("projection", projection);

	for (int i = 0; i < 4; i++)
	{
		glDrawArrays(GL_TRIANGLE_FAN, 0, i + 1);
	}
	for (int i = 0; i < 4; i++)
	{
		glDrawArrays(GL_TRIANGLE_FAN, 4, i + 1);
	}
	for (int i = 0; i < 4; i++)
	{
		glDrawArrays(GL_TRIANGLE_FAN, 8, i + 1);
	}
	for (int i = 0; i < 4; i++)
	{
		glDrawArrays(GL_TRIANGLE_FAN, 12, i + 1);
	}
	for (int i = 0; i < 4; i++)
	{
		glDrawArrays(GL_TRIANGLE_FAN, 16, i + 1);
	}
	for (int i = 0; i < 4; i++)
	{
		glDrawArrays(GL_TRIANGLE_FAN, 20, i + 1);
	}
	for (int i = 0; i < 4; i++)
	{
		glDrawArrays(GL_TRIANGLE_FAN, 24, i + 1);
	}
	//Respaldo 
	model = temp02;
	model = glm::translate(model, glm::vec3(0.0f, -4.3, 0.5f));
	model = glm::scale(model, glm::vec3(2.0f, 3.5f, 0.025f)); //HACEMOS UN "MODELO" ESCALADO CON MEDIDAS 5 * 1 * 3 UNIDADES
	ligthShader.setMat4("model", model);
	ligthShader.setInt("material_diffuse", tex1);
	//textureShader.setMat4("projection", projection);

	for (int i = 0; i < 4; i++)
	{
		glDrawArrays(GL_TRIANGLE_FAN, 0, i + 1);
	}
	for (int i = 0; i < 4; i++)
	{
		glDrawArrays(GL_TRIANGLE_FAN, 4, i + 1);
	}
	for (int i = 0; i < 4; i++)
	{
		glDrawArrays(GL_TRIANGLE_FAN, 8, i + 1);
	}
	for (int i = 0; i < 4; i++)
	{
		glDrawArrays(GL_TRIANGLE_FAN, 12, i + 1);
	}
	for (int i = 0; i < 4; i++)
	{
		glDrawArrays(GL_TRIANGLE_FAN, 16, i + 1);
	}
	for (int i = 0; i < 4; i++)
	{
		glDrawArrays(GL_TRIANGLE_FAN, 20, i + 1);
	}
	for (int i = 0; i < 4; i++)
	{
		glDrawArrays(GL_TRIANGLE_FAN, 24, i + 1);
	}
	//Asientos en canastas
	//Barra de seguridad 
	model = temp02;
	model = glm::translate(model, glm::vec3(1.0f, -3.5f, -1.0f));
	model = glm::rotate(model, glm::radians(angRotPuerta), glm::vec3(0, 1, 0));//rotamos
	model = glm::translate(model, glm::vec3(-1.0f, 0.0f, 0.0f));
	ligthShader.setMat4("model", model);
	//ligthShader.setInt("material_diffuse", tex1);
	model = glm::scale(model, glm::vec3(2.0f, 0.1f, 0.025f)); //HACEMOS UN "MODELO" ESCALADO CON MEDIDAS 5 * 1 * 3 UNIDADES
	ligthShader.setMat4("model", model);
	ligthShader.setInt("material_diffuse", tex1);
	//textureShader.setMat4("projection", projection);

	for (int i = 0; i < 4; i++)
	{
		glDrawArrays(GL_TRIANGLE_FAN, 0, i + 1);
	}
	for (int i = 0; i < 4; i++)
	{
		glDrawArrays(GL_TRIANGLE_FAN, 4, i + 1);
	}
	for (int i = 0; i < 4; i++)
	{
		glDrawArrays(GL_TRIANGLE_FAN, 8, i + 1);
	}
	for (int i = 0; i < 4; i++)
	{
		glDrawArrays(GL_TRIANGLE_FAN, 12, i + 1);
	}
	for (int i = 0; i < 4; i++)
	{
		glDrawArrays(GL_TRIANGLE_FAN, 16, i + 1);
	}
	for (int i = 0; i < 4; i++)
	{
		glDrawArrays(GL_TRIANGLE_FAN, 20, i + 1);
	}
	for (int i = 0; i < 4; i++)
	{
		glDrawArrays(GL_TRIANGLE_FAN, 24, i + 1);
	}
	//Parte trasera. 
	model = temp02;
	model = glm::translate(model, glm::vec3(0.0f, -4.5, 3.0f));
	model = glm::scale(model, glm::vec3(2.0f, 3.0f, 0.025f)); //HACEMOS UN "MODELO" ESCALADO CON MEDIDAS 5 * 1 * 3 UNIDADES
	ligthShader.setMat4("model", model);
	ligthShader.setInt("material_diffuse", tex1);
	//textureShader.setMat4("projection", projection);

	for (int i = 0; i < 4; i++)
	{
		glDrawArrays(GL_TRIANGLE_FAN, 0, i + 1);
	}
	for (int i = 0; i < 4; i++)
	{
		glDrawArrays(GL_TRIANGLE_FAN, 4, i + 1);
	}
	for (int i = 0; i < 4; i++)
	{
		glDrawArrays(GL_TRIANGLE_FAN, 8, i + 1);
	}
	for (int i = 0; i < 4; i++)
	{
		glDrawArrays(GL_TRIANGLE_FAN, 12, i + 1);
	}
	for (int i = 0; i < 4; i++)
	{
		glDrawArrays(GL_TRIANGLE_FAN, 16, i + 1);
	}
	for (int i = 0; i < 4; i++)
	{
		glDrawArrays(GL_TRIANGLE_FAN, 20, i + 1);
	}
	for (int i = 0; i < 4; i++)
	{
		glDrawArrays(GL_TRIANGLE_FAN, 24, i + 1);
	}
	//Suelo de la canasta
	model = temp02;
	model = glm::translate(model, glm::vec3(0.0f, -6, 0.0f));
	model = glm::scale(model, glm::vec3(2, 0.25, 6)); //HACEMOS UN "MODELO" ESCALADO CON MEDIDAS 5 * 1 * 3 UNIDADES
	ligthShader.setMat4("model", model);
	ligthShader.setInt("material_diffuse", tex1);
	//textureShader.setMat4("projection", projection);

	for (int i = 0; i < 4; i++)
	{
		glDrawArrays(GL_TRIANGLE_FAN, 0, i + 1);
	}
	for (int i = 0; i < 4; i++)
	{
		glDrawArrays(GL_TRIANGLE_FAN, 4, i + 1);
	}
	for (int i = 0; i < 4; i++)
	{
		glDrawArrays(GL_TRIANGLE_FAN, 8, i + 1);
	}
	for (int i = 0; i < 4; i++)
	{
		glDrawArrays(GL_TRIANGLE_FAN, 12, i + 1);
	}
	for (int i = 0; i < 4; i++)
	{
		glDrawArrays(GL_TRIANGLE_FAN, 16, i + 1);
	}
	for (int i = 0; i < 4; i++)
	{
		glDrawArrays(GL_TRIANGLE_FAN, 20, i + 1);
	}
	for (int i = 0; i < 4; i++)
	{
		glDrawArrays(GL_TRIANGLE_FAN, 24, i + 1);
	}
	//Suelo de la canasta

	textureShader.use();

	glBindVertexArray(0);
}



