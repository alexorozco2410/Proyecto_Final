#include "rueda.h"
#include"canasta.h"
#include"toroide.h"
#include "cilindro.h"

//glm::vec3 lightPos(0.0f, 0.0f, 0.0f);
//GLuint VBO, VAO, lightVAO;
Canasta my_canasta1(1.0f);
Rueda my_rueda1(1.0f);
Cilindro my_cylinder2(1.0f);
Toroide my_toroide2(1.0f);
//Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
//int SCR_WIDTH = 3800;
//int SCR_HEIGHT = 7600;

Rueda::Rueda(GLfloat radio) :

	radio(radio) {
	rueda_VAO[4] = (-1, -1, -1, -1);
	rueda_VBO[4] = (-1, -1, -1, -1);

}


Rueda::~Rueda()
{
	glDeleteVertexArrays(4, rueda_VAO);
	glDeleteBuffers(4, rueda_VBO);
}



void Rueda::init()
{
	
	const int nn = PARALELOS * MERIDIANOS * 3;
	GLfloat rueda_nor[nn]; // normal
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
			rueda_pos[ix + 0] = x * r;
			rueda_pos[ix + 1] = y * r;
			rueda_pos[ix + 2] = z * r;
			rueda_nor[ix + 0] = x;
			rueda_nor[ix + 1] = y;
			rueda_nor[ix + 2] = z;
		}
	// [Generate GL_TRIANGLE indices]
	for (ix = 0, iy = 0, ib = 1; ib < PARALELOS; ib++)
	{
		for (ia = 1; ia < MERIDIANOS; ia++, iy++)
		{
			// first half of QUAD
			rueda_index[ix] = iy;      ix++;
			rueda_index[ix] = iy + 1;    ix++;
			rueda_index[ix] = iy + MERIDIANOS;   ix++;
			// second half of QUAD
			rueda_index[ix] = iy + MERIDIANOS;   ix++;
			rueda_index[ix] = iy + 1;    ix++;
			rueda_index[ix] = iy + MERIDIANOS + 1; ix++;
		}
		// first half of QUAD
		rueda_index[ix] = iy;       ix++;
		rueda_index[ix] = iy + 1 - MERIDIANOS;  ix++;
		rueda_index[ix] = iy + MERIDIANOS;    ix++;
		// second half of QUAD
		rueda_index[ix] = iy + MERIDIANOS;    ix++;
		rueda_index[ix] = iy - MERIDIANOS + 1;  ix++;
		rueda_index[ix] = iy + 1;     ix++;
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
	glGenVertexArrays(4, rueda_VAO);
	glGenBuffers(4, rueda_VBO);
	glBindVertexArray(rueda_VAO[0]);
	i = 0; // vertex
	glBindBuffer(GL_ARRAY_BUFFER, rueda_VBO[i]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(rueda_pos), rueda_pos, GL_STATIC_DRAW);
	glEnableVertexAttribArray(i);
	glVertexAttribPointer(i, 3, GL_FLOAT, GL_FALSE, 0, 0);
	i = 1; // normal
	glBindBuffer(GL_ARRAY_BUFFER, rueda_VBO[i]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(rueda_nor), rueda_nor, GL_STATIC_DRAW);
	glEnableVertexAttribArray(i);
	glVertexAttribPointer(i, 3, GL_FLOAT, GL_FALSE, 0, 0);
	i = 2; // indices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rueda_VBO[i]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(rueda_index), rueda_index, GL_STATIC_DRAW);
	glEnableVertexAttribArray(i);
	glVertexAttribPointer(i, 4, GL_UNSIGNED_INT, GL_FALSE, 0, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}

void Rueda::render()
{
	//glEnable(GL_CULL_FACE);
	//glFrontFace(GL_CCW);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glBindVertexArray(rueda_VAO[0]);
	//  glDrawArrays(GL_POINTS,0,sizeof(esfera_pos)/sizeof(GLfloat));                   // POINTS ... no indices for debug
	glDrawElements(GL_TRIANGLES, sizeof(rueda_index) / sizeof(GLuint), GL_UNSIGNED_INT, 0);    // indices (choose just one line not both !!!)
	glBindVertexArray(0);
}


void Rueda::dibujaRueda(unsigned int tex1, Shader ligthShader, Shader textureShader, glm::mat4 model, GLuint rueda_VBO, GLuint rueda_VAO, GLuint rueda_EBO, float rotRueda, float angRotPuerta)
{
	my_cylinder2.init();
	my_toroide2.init();
	Shader projectionShader("shaders/shader_light.vs", "shaders/shader_light.fs");
	//glBindVertexArray(lightVAO);
	//glEnable(GL_CULL_FACE);
	//glFrontFace(GL_CCW);
	//glm::mat4 model = glm::mat4(1.0f); //Temp
	glm::mat4 temp01 = glm::mat4(1.0f); //Temp
	glm::mat4 temp02 = glm::mat4(1.0f); //Temp
	glm::mat4 temp03 = glm::mat4(1.0f); //Temp
	//glm::mat4 projection = glm::mat4(1.0f);	//This matrix is for Projection
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glBindVertexArray(rueda_VAO);
	//model = glm::mat4(1.0f);
	//model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1, 0, 0));
	//------------Rueda de la fortuna --------
	//-----------------Soporte------------------------------------
	temp01 = model;
	model = glm::scale(model, glm::vec3(0.1f, 1.2f, 0.1f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1, 0, 0));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 1, 0));
	//model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 1, 0));
	textureShader.setMat4("model", model);
	my_cylinder2.render();


	model = temp01;
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.0f));
	model = glm::scale(model, glm::vec3(0.1f, 1.2f, 0.1f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1, 0, 0));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 1, 0));
	textureShader.setMat4("model", model);
	//textureShader.setMat4("projection", projection);
	my_cylinder2.render();

	//Videndo de arriba x,z
	model = temp01;
	model = glm::translate(model, glm::vec3(0.6f, -0.3f, 0.0f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 1, 0));
	temp03 = model;
	model = temp03;
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 1, 0));
	model = glm::rotate(model, glm::radians(70.0f), glm::vec3(0, 0, 1));
	model = glm::scale(model, glm::vec3(1.1f, 0.1f, 0.1f));
	textureShader.setMat4("model", model);
	//textureShader.setMat4("projection", projection);
	my_cylinder2.render();
	//Videndo de arriba x,-z
	model = temp01;
	model = glm::translate(model, glm::vec3(-0.6f, -0.3f, 0.0f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 1, 0));
	temp03 = model;
	model = temp03;
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 1, 0));
	model = glm::rotate(model, glm::radians(-70.0f), glm::vec3(0, 0, 1));
	model = glm::scale(model, glm::vec3(1.1f, 0.1f, 0.1f));
	textureShader.setMat4("model", model);
	//textureShader.setMat4("projection", projection);
	my_cylinder2.render();
	//Videndo de arriba -x,z
	model = temp01;
	model = glm::translate(model, glm::vec3(0.6f, -0.3f, -2.0f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 1, 0));
	temp03 = model;
	model = temp03;
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 1, 0));
	model = glm::rotate(model, glm::radians(70.0f), glm::vec3(0, 0, 1));
	model = glm::scale(model, glm::vec3(1.1f, 0.1f, 0.1f));
	textureShader.setMat4("model", model);
	//textureShader.setMat4("projection", projection);
	my_cylinder2.render();
	//Videndo de arriba -x,-z
	model = temp01;
	model = glm::translate(model, glm::vec3(-0.6f, -0.3f, -2.0f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 1, 0));
	temp03 = model;
	model = temp03;
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 1, 0));
	model = glm::rotate(model, glm::radians(-70.0f), glm::vec3(0, 0, 1));
	model = glm::scale(model, glm::vec3(1.1f, 0.1f, 0.1f));
	textureShader.setMat4("model", model);
	//textureShader.setMat4("projection", projection);
	my_cylinder2.render();
	glBindVertexArray(rueda_VAO);

	//Base 
	ligthShader.use();
	model = temp01;
	model = glm::translate(model, glm::vec3(0.0f, -2.0f, -1.0f));
	model = glm::scale(model, glm::vec3(5.0f, 0.25f, 5.0f));
	//model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 1, 0));
	
	//textureShader.setMat4("model", model);
	ligthShader.setMat4("model", model);
	ligthShader.setInt("material_diffuse", tex1);
	//textureShader.setMat4("projection", projection);

	for (int i = 0; i < 4; i++)
	{
		glDrawArrays(GL_TRIANGLE_FAN, 24, i + 1);
	}
	for (int i = 0; i < 4; i++)
	{
		glDrawArrays(GL_TRIANGLE_FAN, 28, i + 1);
	}
	for (int i = 0; i < 4; i++)
	{
		glDrawArrays(GL_TRIANGLE_FAN, 40, i + 1);
	}
	for (int i = 0; i < 4; i++)
	{
		glDrawArrays(GL_TRIANGLE_FAN, 44, i + 1);
	}
	for (int i = 0; i < 4; i++)
	{
		glDrawArrays(GL_TRIANGLE_FAN, 32, i + 1);
	}
	for (int i = 0; i < 4; i++)
	{
		glDrawArrays(GL_TRIANGLE_FAN, 36, i + 1);
	}
	//-----------------Soporte------------------------------------
	//---------------------------------EJE-----------------------------------
	textureShader.use();
	model = temp01;
	model = glm::translate(model, glm::vec3(0.0f, 1.7f, -1.0f));
	temp01 = model;
	model = glm::rotate(model, glm::radians(rotRueda), glm::vec3(0, 0, 1));//PARA HACER RODAR LA RUEDA DE LA FORTUANA
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 1, 0));
	//model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
	temp01 = model;
	model = glm::scale(model, glm::vec3(0.75f, 0.1f, 0.1f));
	textureShader.setMat4("model", model);
	//textureShader.setMat4("projection", projection);
	my_cylinder2.render();
	//---------------------------------EJE-----------------------------------
	//-------------------------Rueda delantera------------------------------------
	model = temp01;
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 1, 0));
	model = glm::translate(model, glm::vec3(0, 0, 0.5));
	model = glm::scale(model, glm::vec3(0.215f, 0.215f, 0.1f));
	textureShader.setMat4("model", model);
	//textureShader.setMat4("projection", projection);
	my_toroide2.render();

	//----------------------------Rayos de la rueda-------------------
	model = temp01;
	model = glm::translate(model, glm::vec3(0.5, 0, 0));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 1, 0));
	model = glm::scale(model, glm::vec3(1.4f, 0.1f, 0.1f));
	textureShader.setMat4("model", model);
	//textureShader.setMat4("projection", projection);
	my_cylinder2.render();



	model = temp01;
	model = glm::translate(model, glm::vec3(0.5, 0, 0));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 1, 0));
	model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0, 0, 1));
	model = glm::scale(model, glm::vec3(1.4f, 0.1f, 0.1f));
	textureShader.setMat4("model", model);
	//textureShader.setMat4("projection", projection);
	my_cylinder2.render();

	model = temp01;
	model = glm::translate(model, glm::vec3(0.5, 0, 0));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 1, 0));
	model = glm::rotate(model, glm::radians(-45.0f), glm::vec3(0, 0, 1));
	model = glm::scale(model, glm::vec3(1.4f, 0.1f, 0.1f));
	textureShader.setMat4("model", model);
	//textureShader.setMat4("projection", projection);
	my_cylinder2.render();

	model = temp01;
	model = glm::translate(model, glm::vec3(0.5f, 0, 0));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 1, 0));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 0, 1));
	model = glm::scale(model, glm::vec3(1.4f, 0.1f, 0.1f));
	textureShader.setMat4("model", model);
	//textureShader.setMat4("projection", projection);
	my_cylinder2.render();
	//-------------------------Rayos de la rueda---------------------
	//-------------------------Rueda delantera------------------------------------

	//-------------------------Rueda trasera------------------------------------
	model = temp01;
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 1, 0));
	model = glm::translate(model, glm::vec3(0, 0, -0.5));
	model = glm::scale(model, glm::vec3(0.215f, 0.215f, 0.1f));
	textureShader.setMat4("model", model);
	//textureShader.setMat4("projection", projection);
	my_toroide2.render();
	//---------------------------Rayos de la rueda---------------------------
	model = temp01;
	model = glm::translate(model, glm::vec3(-0.5, 0, 0));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 1, 0));
	model = glm::scale(model, glm::vec3(1.4f, 0.1f, 0.1f));
	textureShader.setMat4("model", model);
	//textureShader.setMat4("projection", projection);
	my_cylinder2.render();

	model = temp01;
	model = glm::translate(model, glm::vec3(-0.5, 0, 0));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 1, 0));
	model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0, 0, 1));
	model = glm::scale(model, glm::vec3(1.4f, 0.1f, 0.1f));
	textureShader.setMat4("model", model);
	//textureShader.setMat4("projection", projection); projectionShader.setMat4("model", model);
	my_cylinder2.render();

	model = temp01;
	model = glm::translate(model, glm::vec3(-0.5, 0, 0));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 1, 0));
	model = glm::rotate(model, glm::radians(-45.0f), glm::vec3(0, 0, 1));
	model = glm::scale(model, glm::vec3(1.4f, 0.1f, 0.1f));
	textureShader.setMat4("model", model);
	//textureShader.setMat4("projection", projection);
	my_cylinder2.render();

	model = temp01;
	model = glm::translate(model, glm::vec3(-0.5, 0, 0));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 1, 0));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 0, 1));
	model = glm::scale(model, glm::vec3(1.4f, 0.1f, 0.1f));
	textureShader.setMat4("model", model);
	//textureShader.setMat4("projection", projection);
	my_cylinder2.render();
	//---------------------------Rayos de la rueda--------------------------
	//--------------------------Asientos de canastas ---------------------------------------
	//----------------------------1 arriba----------------------------------------

	model = temp01;
	model = glm::translate(model, glm::vec3(0.0f, 2.25f, 0.0f));
	model = glm::scale(model, glm::vec3(0.35f, 0.1f, 0.1f));
	model = glm::rotate(model, glm::radians(rotRueda), glm::vec3(1, 0, 0));
	textureShader.setMat4("model", model);
	//textureShader.setMat4("projection", projection);
	my_cylinder2.render();
	//glBindVertexArray(rueda_VAO);
	my_canasta1.dibujaCanasta(tex1,ligthShader,textureShader, model, temp01, rueda_VBO, rueda_VAO, rueda_EBO, angRotPuerta);

	//----------------------------2 derecha----------------------------------------
	model = temp01;
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 2.25f));
	model = glm::scale(model, glm::vec3(0.35f, 0.1f, 0.1f));
	model = glm::rotate(model, glm::radians(rotRueda), glm::vec3(1, 0, 0));
	textureShader.setMat4("model", model);
	//textureShader.setMat4("projection", projection);
	my_cylinder2.render();
	my_canasta1.dibujaCanasta(tex1, ligthShader, textureShader, model, temp01, rueda_VBO, rueda_VAO, rueda_EBO, angRotPuerta);

	//----------------------------3 izquierda----------------------------------------
	model = temp01;
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.25f));
	model = glm::scale(model, glm::vec3(0.35f, 0.1f, 0.1f));
	model = glm::rotate(model, glm::radians(rotRueda), glm::vec3(1, 0, 0));
	textureShader.setMat4("model", model);
	//textureShader.setMat4("projection", projection);
	my_cylinder2.render();
	my_canasta1.dibujaCanasta(tex1, ligthShader, textureShader, model, temp01, rueda_VBO, rueda_VAO, rueda_EBO, angRotPuerta);

	//----------------------------4 Abajo----------------------------------------
	model = temp01;
	model = glm::translate(model, glm::vec3(0.0f, -2.25f, 0.0f));
	model = glm::scale(model, glm::vec3(0.35f, 0.1f, 0.1f));
	model = glm::rotate(model, glm::radians(rotRueda), glm::vec3(1, 0, 0));
	textureShader.setMat4("model", model);
	//textureShader.setMat4("projection", projection);
	my_cylinder2.render();
	my_canasta1.dibujaCanasta(tex1, ligthShader, textureShader, model, temp01, rueda_VBO, rueda_VAO, rueda_EBO, angRotPuerta);
	
	//----------------------------5 izquierda arriba----------------------------------------
	model = temp01;
	model = glm::translate(model, glm::vec3(0.0f, 1.59f, -1.59f));
	model = glm::scale(model, glm::vec3(0.35f, 0.1f, 0.1f));
	model = glm::rotate(model, glm::radians(rotRueda), glm::vec3(1, 0, 0));
	textureShader.setMat4("model", model);
	//textureShader.setMat4("projection", projection);
	my_cylinder2.render();
	my_canasta1.dibujaCanasta(tex1, ligthShader, textureShader, model, temp01, rueda_VBO, rueda_VAO, rueda_EBO, angRotPuerta);
	//----------------------------6 izquierda abajo----------------------------------------
	model = temp01;
	model = glm::translate(model, glm::vec3(0.0f, -1.59f, -1.59f));
	model = glm::scale(model, glm::vec3(0.35f, 0.1f, 0.1f));
	model = glm::rotate(model, glm::radians(rotRueda), glm::vec3(1, 0, 0));
	textureShader.setMat4("model", model);
	//textureShader.setMat4("projection", projection);
	my_cylinder2.render();
	my_canasta1.dibujaCanasta(tex1, ligthShader, textureShader, model, temp01, rueda_VBO, rueda_VAO, rueda_EBO, angRotPuerta);
	
	//----------------------------7 derecha abajo----------------------------------------
	model = temp01;
	model = glm::translate(model, glm::vec3(0.0f, -1.59f, 1.59f));
	model = glm::scale(model, glm::vec3(0.35f, 0.1f, 0.1f));
	model = glm::rotate(model, glm::radians(rotRueda), glm::vec3(1, 0, 0));
	textureShader.setMat4("model", model);
	//textureShader.setMat4("projection", projection);
	my_cylinder2.render();
	my_canasta1.dibujaCanasta(tex1, ligthShader, textureShader, model, temp01, rueda_VBO, rueda_VAO, rueda_EBO,angRotPuerta);
	
	//----------------------------8 derecha arriba----------------------------------------
	model = temp01;
	model = glm::translate(model, glm::vec3(0.0f, 1.59f, 1.59f));
	model = glm::scale(model, glm::vec3(0.35f, 0.1f, 0.1f));
	model = glm::rotate(model, glm::radians(rotRueda), glm::vec3(1, 0, 0));
	textureShader.setMat4("model", model);
	//textureShader.setMat4("projection", projection);
	my_cylinder2.render();
	my_canasta1.dibujaCanasta(tex1, ligthShader, textureShader, model, temp01, rueda_VBO, rueda_VAO, rueda_EBO, angRotPuerta);
	
	
	//------------Rueda de la fortuna --------
	
	//my_canasta1.riel(textureShader,model,temp01,canast_VBO,canasta_VAO,canasta_EBO);

	glBindVertexArray(0);
}



