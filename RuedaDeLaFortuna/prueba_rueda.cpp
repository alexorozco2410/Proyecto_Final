/*---------------------------------------------------------*/
/* ----------------   Práctica 7 --------------------------*/
/*-----------------    2019-2   ---------------------------*/
/*---------------------Grupo : 04--------------------------*/
/*------------- Alumno:  Zagoya Mellado Roberto Uriel ---------------*/
/*--------------------Version de visual : 2017-----------------------*/
/* LOS MOVIMIENTOS DE LA LUZ SON:

   O --> MOVIMIENTO NEGATIVO EN Z
   U --> MOVIMIETNO POSITIVO EN Z
   I --> MOVIMIENTO POSITIVO EN Y
   K --> MOVIMIENTO NEGATIVO EN Y
   L --> MOVIMIENTO POSITIVO EN X
   J --> MOVIMIENTO NEGATIVO EN X

*/
#include <glew.h>
#include <glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <shader_m.h>

#include <iostream>
#include "esfera.h"
#include "cilindro.h"
#include "camera.h"
#include "toroide.h"

	Cilindro my_cylinder(1.0);
	Toroide my_toroide(1.0);
	Esfera my_esfera(1.0);
	//Canasta my_canasta(1.0);

	void resize(GLFWwindow* window, int width, int height);
	void my_input(GLFWwindow *window);
	void mouse_callback(GLFWwindow *window, double xpos, double ypos);
	void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
	// settings
	// Window size
	int SCR_WIDTH = 3800;
	int SCR_HEIGHT = 7600;
	GLFWmonitor *monitors;
	GLuint VBO, VAO, lightVAO;



	//Camera

	Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
	double	lastX = 0.0f,
	lastY = 0.0f;
	bool firstMouse = true;

	//Timing
	double	deltaTime = 0.0f,
	lastFrame = 0.0f;


	//Lighting

	glm::vec3 lightPos(0.0f, 0.0f, 0.0f);
	void myData(void);
	void display(void);
	void getResolution(void);
	void animate(void);
	//For Keyboard
	float	movX = 0.0f,
	movY = 0.0f,
	movZ = -5.0f,
	rotX = 0.0f;
	float bandera = 0.2;
	float angHom = 0.0f;


	float	sol = 0.0f,
	year = 0.0f,
	day = 0.0f,
	moon = 0.0f,
	mars_year = 0.0f,
	jupiter_year = 0.0f,
	mercurio = 0.0f,
	venus = 0.0f,
	tierra = 0.00,
	marte = 0.0f,
	jupiter = 0.0f,
	saturno = 0.0f,
	urano = 0.0f,
	neptuno = 0.0f;

void getResolution()
{
	const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	SCR_WIDTH = mode->width;
	SCR_HEIGHT = (mode->height) - 80;
	lastX = SCR_WIDTH / 2.0f;
	lastY = SCR_HEIGHT / 2.0f;
}



void myData()

{
	GLfloat vertices[] = {
		//Position				//Normals
		-0.5f, -0.5f, 0.5f,		 0.0f,  0.0f,  1.0f,
		0.5f, -0.5f, 0.5f,		 0.0f,  0.0f,  1.0f,
		0.5f, 0.5f, 0.5f,		 0.0f,  0.0f,  1.0f,
		-0.5f, 0.5f, 0.5f,		 0.0f,  0.0f,  1.0f,
		

		0.5f, -0.5f, -0.5f,		  0.0f,  0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,	  0.0f,  0.0f,  -1.0f,
		-0.5f, 0.5f, -0.5f,		  0.0f,  0.0f,  -1.0f,
		0.5f, 0.5f, -0.5f,		  0.0f,  0.0f,  -1.0f,

		-0.5f, 0.5f, 0.5f,		   -1.0f,  0.0f,  0.0f,
		-0.5f, 0.5f, -0.5f,		   -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,	   -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, 0.5f,		   -1.0f,  0.0f,  0.0f,

		0.5f, 0.5f, 0.5f,			  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, 0.5f,			  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,			  1.0f,  0.0f,  0.0f,
		0.5f, 0.5f, -0.5f,			  1.0f,  0.0f,  0.0f,

		-0.5f, 0.5f, 0.5f,		   0.0f,  1.0f,  0.0f,
		0.5f, 0.5f, 0.5f,		   0.0f,  1.0f,  0.0f,
		0.5f, 0.5f, -0.5f,		   0.0f,  1.0f,  0.0f,
		-0.5f, 0.5f, -0.5f,		   0.0f,  1.0f,  0.0f,

		-0.5f, -0.5f, 0.5f,		   0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,	   0.0f, -1.0f,  0.0f,
		0.5f, -0.5f, -0.5f,		   0.0f, -1.0f,  0.0f,
		0.5f, -0.5f, 0.5f,		   0.0f, -1.0f,  0.0f


	};

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// Normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//To configure Second Objecto to represet Light
	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}



void animate(void)
{
	sol += 0.1f;
	mercurio += 0.4f;
	venus += 0.35f;
	tierra += 0.3f;
	marte += 0.25f;
	jupiter += 0.2f;
	saturno += 0.15f;
	urano += 0.1f;
	neptuno += 0.05f;

	angHom = angHom + bandera;
	if (angHom >= 0)
	{
		bandera = -0.2;
	}
	if (angHom <= -45)
	{
		bandera = 0.2;
	}
}



void display(void)
{
	//Shader myShader("shaders/shader.vs", "shaders/shader.fs");
	//Shader projectionShader("shaders/shader_projection.vs", "shaders/shader_projection.fs");
	Shader projectionShader("shaders/shader_light.vs", "shaders/shader_light.fs");
	//Shader projectionShader("shaders/shader_light_Gouraud.vs", "shaders/shader_light_Gouraud.fs");
	Shader lampShader("shaders/shader_lamp.vs", "shaders/shader_lamp.fs");
	//To Use Lighting
	projectionShader.use();
	projectionShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
	projectionShader.setVec3("lightPos", lightPos);
	// create transformations and Projection
	glm::mat4 temp01 = glm::mat4(1.0f); //Temp
	glm::mat4 temp02 = glm::mat4(1.0f); //Temp
	glm::mat4 temp03 = glm::mat4(1.0f);
	glm::mat4 model = glm::mat4(1.0f);		// initialize Matrix, Use this matrix for individual models
	glm::mat4 view = glm::mat4(1.0f);		//Use this matrix for ALL models
	glm::mat4 projection = glm::mat4(1.0f);	//This matrix is for Projection
	//Use "projection" to inlcude Camera
	projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	view = camera.GetViewMatrix();
	// pass them to the shaders}
	projectionShader.setVec3("viewPos", camera.Position);
	projectionShader.setMat4("model", model);
	projectionShader.setMat4("view", view);
	// note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.

	projectionShader.setMat4("projection", projection);
	glBindVertexArray(VAO);
	//Colocar código aquí

	
	//----------------RUEDA------------------------------------
	//-----------------Soporte------------------------------------

	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(4.5f, 1.0f, 1.0f));
	model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
	//model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1, 0, 0));
	temp01 = model;
	model = glm::scale(model, glm::vec3(0.1f, 1.2f, 0.1f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1, 0, 0));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 1, 0));
	//model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 1, 0));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.6f, 0.0f, 0.3f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	my_cylinder.render();

	model=temp01;
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.0f));
	model = glm::scale(model, glm::vec3(0.1f, 1.2f, 0.1f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1, 0, 0));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 1, 0));
	projectionShader.setMat4("model", model);
	my_cylinder.render();

	//Videndo de arriba x,z
	model = temp01;
	model = glm::translate(model, glm::vec3(0.6f, -0.3f, 0.0f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 1, 0));
	temp03 = model;
	model = temp03;
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 1, 0));
	model = glm::rotate(model, glm::radians(70.0f), glm::vec3(0, 0, 1));
	model = glm::scale(model, glm::vec3(1.1f, 0.1f, 0.1f));
	projectionShader.setMat4("model", model);
	my_cylinder.render();
	//Videndo de arriba x,-z
	model = temp01;
	model = glm::translate(model, glm::vec3(-0.6f, -0.3f, 0.0f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 1, 0));
	temp03 = model;
	model = temp03;
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 1, 0));
	model = glm::rotate(model, glm::radians(-70.0f), glm::vec3(0, 0, 1));
	model = glm::scale(model, glm::vec3(1.1f, 0.1f, 0.1f));
	projectionShader.setMat4("model", model);
	my_cylinder.render();
	//Videndo de arriba -x,z
	model = temp01;
	model = glm::translate(model, glm::vec3(0.6f, -0.3f, -2.0f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 1, 0));
	temp03 = model;
	model = temp03;
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 1, 0));
	model = glm::rotate(model, glm::radians(70.0f), glm::vec3(0, 0, 1));
	model = glm::scale(model, glm::vec3(1.1f, 0.1f, 0.1f));
	projectionShader.setMat4("model", model);
	my_cylinder.render();
	//Videndo de arriba -x,-z
	model = temp01;
	model = glm::translate(model, glm::vec3(-0.6f, -0.3f, -2.0f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 1, 0));
	temp03 = model;
	model = temp03;
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 1, 0));
	model = glm::rotate(model, glm::radians(-70.0f), glm::vec3(0, 0, 1));
	model = glm::scale(model, glm::vec3(1.1f, 0.1f, 0.1f));
	projectionShader.setMat4("model", model);
	my_cylinder.render();

	projectionShader.setMat4("projection", projection);
	glBindVertexArray(VAO);

	//Base 
	model = temp01;
	model = glm::translate(model, glm::vec3(0.0f, -2.0f, -1.0f));
	model = glm::scale(model, glm::vec3(5.0f, 0.25f, 5.0f));
	//model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 1, 0));
	projectionShader.setMat4("model", model);
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.6f, 0.0f, 0.3f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);

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

	//---------------------------------Soporte--------------------------
	//---------------------------------EJE-----------------------------------
	model = temp01;
	model = glm::translate(model, glm::vec3(0.0f, 1.7f, -1.0f));
	temp01 = model;
	model = glm::rotate(model, glm::radians(mercurio), glm::vec3(0, 0, 1));//PARA HACER RODAR LA RUEDA DE LA FORTUANA
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 1, 0));
	//model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
	temp01 = model;
	model = glm::scale(model, glm::vec3(0.75f, 0.1f, 0.1f));
	projectionShader.setMat4("model", model);
	my_cylinder.render();
	//---------------------------------EJE-----------------------------------

	//-------------------------Rueda delantera------------------------------------
	model = temp01;
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 1, 0));
	model = glm::translate(model, glm::vec3(0, 0, 0.5));
	model = glm::scale(model, glm::vec3(0.215f, 0.215f, 0.1f));

	projectionShader.setMat4("model", model);
	my_toroide.render();
	//----------------------------Rayos de la rueda-------------------
	model = temp01;
	model = glm::translate(model, glm::vec3(0.5, 0, 0));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 1, 0));
	model = glm::scale(model, glm::vec3(1.4f, 0.1f, 0.1f));
	projectionShader.setMat4("model", model);
	my_cylinder.render();

	

	model = temp01;
	model = glm::translate(model, glm::vec3(0.5, 0, 0));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 1, 0));
	model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0, 0, 1));
	model = glm::scale(model, glm::vec3(1.4f, 0.1f, 0.1f));
	projectionShader.setMat4("model", model);
	my_cylinder.render();

	model = temp01;
	model = glm::translate(model, glm::vec3(0.5, 0, 0));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 1, 0));
	model = glm::rotate(model, glm::radians(-45.0f), glm::vec3(0, 0, 1));
	model = glm::scale(model, glm::vec3(1.4f, 0.1f, 0.1f));
	projectionShader.setMat4("model", model);
	my_cylinder.render();

	model = temp01;
	model = glm::translate(model, glm::vec3(0.5f, 0, 0));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 1, 0));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 0, 1));
	model = glm::scale(model, glm::vec3(1.4f, 0.1f, 0.1f));
	projectionShader.setMat4("model", model);
	my_cylinder.render();
	//-------------------------Rayos de la rueda---------------------
	//-------------------------Rueda delantera------------------------------------

	//-------------------------Rueda trasera------------------------------------
	model = temp01;
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 1, 0));
	model = glm::translate(model, glm::vec3(0, 0, -0.5));
	model = glm::scale(model, glm::vec3(0.215f, 0.215f, 0.1f));
	projectionShader.setMat4("model", model);
	my_toroide.render();
	//---------------------------Rayos de la rueda---------------------------
	model = temp01;
	model = glm::translate(model, glm::vec3(-0.5, 0, 0));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 1, 0));
	model = glm::scale(model, glm::vec3(1.4f, 0.1f, 0.1f));
	projectionShader.setMat4("model", model);
	my_cylinder.render();

	model = temp01;
	model = glm::translate(model, glm::vec3(-0.5, 0, 0));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 1, 0));
	model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0, 0, 1));
	model = glm::scale(model, glm::vec3(1.4f, 0.1f, 0.1f));
	projectionShader.setMat4("model", model);
	my_cylinder.render();

	model = temp01;
	model = glm::translate(model, glm::vec3(-0.5, 0, 0));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 1, 0));
	model = glm::rotate(model, glm::radians(-45.0f), glm::vec3(0, 0, 1));
	model = glm::scale(model, glm::vec3(1.4f, 0.1f, 0.1f));
	projectionShader.setMat4("model", model);
	my_cylinder.render();

	model = temp01;
	model = glm::translate(model, glm::vec3(-0.5, 0, 0));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 1, 0));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 0, 1));
	model = glm::scale(model, glm::vec3(1.4f, 0.1f, 0.1f));
	projectionShader.setMat4("model", model);
	my_cylinder.render();
	//---------------------------Rayos de la rueda--------------------------
	//--------------------------Asientos de canastas ---------------------------------------
	//----------------------------1 arriba----------------------------------------
	
	model = temp01;
	model = glm::translate(model, glm::vec3(0.0f, 2.25f, 0.0f));
	model = glm::scale(model, glm::vec3(0.35f, 0.1f, 0.1f));
	model = glm::rotate(model, glm::radians(mercurio), glm::vec3(1, 0, 0));
	projectionShader.setMat4("model", model);
	my_cylinder.render();

	projectionShader.setMat4("projection", projection);
	glBindVertexArray(VAO);

	model = glm::translate(model, glm::vec3(0.0f, -1.7, 1.0f));
	model = glm::scale(model, glm::vec3(1.0f, 1.5f, 1.5f));
	//model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 1, 0));
	projectionShader.setMat4("model", model);
	temp02 = model;
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.6f, 0.0f, 0.3f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);


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
	//Parte superior de la canata 
	model = temp02;
	model = glm::scale(model, glm::vec3(2, 0.25, 6)); //HACEMOS UN "MODELO" ESCALADO CON MEDIDAS 5 * 1 * 3 UNIDADES
	projectionShader.setMat4("model", model); //LE PASAMOS LOS DATOS DEL MODELO AL SHADER
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.6f, 0.0f, 0.3f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);

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
	projectionShader.setMat4("model", model); //LE PASAMOS LOS DATOS DEL MODELO AL SHADER
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.6f, 0.0f, 0.3f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);

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
	projectionShader.setMat4("model", model); //LE PASAMOS LOS DATOS DEL MODELO AL SHADER
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.6f, 0.0f, 0.3f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);

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
	projectionShader.setMat4("model", model); //LE PASAMOS LOS DATOS DEL MODELO AL SHADER
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.6f, 0.0f, 0.3f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);

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
	projectionShader.setMat4("model", model); //LE PASAMOS LOS DATOS DEL MODELO AL SHADER
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.6f, 0.0f, 0.3f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);

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
	projectionShader.setMat4("model", model); //LE PASAMOS LOS DATOS DEL MODELO AL SHADER
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.6f, 0.0f, 0.3f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);

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
	projectionShader.setMat4("model", model); //LE PASAMOS LOS DATOS DEL MODELO AL SHADER
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.6f, 0.0f, 0.3f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);

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
	model = glm::rotate(model, glm::radians(angHom), glm::vec3(0, 1, 0));//rotamos
	model = glm::translate(model, glm::vec3(-1.0f, 0.0f, 0.0f));
	projectionShader.setMat4("model", model);
	model = glm::scale(model, glm::vec3(2.0f, 3.0f, 0.025f)); //HACEMOS UN "MODELO" ESCALADO CON MEDIDAS 5 * 1 * 3 UNIDADES
	projectionShader.setMat4("model", model);//LE PASAMOS LOS DATOS DEL MODELO AL SHADER
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.6f, 0.0f, 0.3f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);

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
	projectionShader.setMat4("model", model); //LE PASAMOS LOS DATOS DEL MODELO AL SHADER
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.6f, 0.0f, 0.3f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);

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
	projectionShader.setMat4("model", model); //LE PASAMOS LOS DATOS DEL MODELO AL SHADER
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.6f, 0.0f, 0.3f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);

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
	projectionShader.setMat4("model", model); //LE PASAMOS LOS DATOS DEL MODELO AL SHADER
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.6f, 0.0f, 0.3f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);

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
	model = glm::rotate(model, glm::radians(angHom), glm::vec3(0, 1, 0));//rotamos
	model = glm::translate(model, glm::vec3(-1.0f, 0.0f, 0.0f));
	projectionShader.setMat4("model", model);
	model = glm::scale(model, glm::vec3(2.0f, 0.1f, 0.025f)); //HACEMOS UN "MODELO" ESCALADO CON MEDIDAS 5 * 1 * 3 UNIDADES
	projectionShader.setMat4("model", model);//LE PASAMOS LOS DATOS DEL MODELO AL SHADER
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.6f, 0.0f, 0.3f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);

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
	projectionShader.setMat4("model", model); //LE PASAMOS LOS DATOS DEL MODELO AL SHADER
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.6f, 0.0f, 0.3f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);

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
	projectionShader.setMat4("model", model); //LE PASAMOS LOS DATOS DEL MODELO AL SHADER
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.6f, 0.0f, 0.3f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);

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


	/*
	model = temp01;
	model = glm::translate(model, glm::vec3(0.0f, 2.25f, 0.0f));
	model = glm::scale(model, glm::vec3(0.35f, 0.1f, 0.1f));
	projectionShader.setMat4("model", model);
	my_cylinder.render();
	model = temp01;
	model = glm::translate(model, glm::vec3(0.0f, 2.25f, 0.0f));
	model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));
	projectionShader.setMat4("model", model);
	my_esfera.render();*/
	//----------------------------2 derecha----------------------------------------
	model = temp01;
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 2.25f));
	model = glm::scale(model, glm::vec3(0.35f, 0.1f, 0.1f));
	model = glm::rotate(model, glm::radians(mercurio), glm::vec3(1, 0, 0));
	projectionShader.setMat4("model", model);
	my_cylinder.render();
	projectionShader.setMat4("projection", projection);
	glBindVertexArray(VAO);

	model = glm::translate(model, glm::vec3(0.0f, -1.7, 1.0f));
	model = glm::scale(model, glm::vec3(1.0f, 1.5f, 1.5f));
	//model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 1, 0));
	projectionShader.setMat4("model", model);
	temp02 = model;
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.6f, 0.0f, 0.3f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);


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
	//Parte superior de la canata 
	model = temp02;
	model = glm::scale(model, glm::vec3(2, 0.25, 6)); //HACEMOS UN "MODELO" ESCALADO CON MEDIDAS 5 * 1 * 3 UNIDADES
	projectionShader.setMat4("model", model); //LE PASAMOS LOS DATOS DEL MODELO AL SHADER
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.6f, 0.0f, 0.3f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);

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
	projectionShader.setMat4("model", model); //LE PASAMOS LOS DATOS DEL MODELO AL SHADER
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.6f, 0.0f, 0.3f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);

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
	projectionShader.setMat4("model", model); //LE PASAMOS LOS DATOS DEL MODELO AL SHADER
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.6f, 0.0f, 0.3f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);

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
	projectionShader.setMat4("model", model); //LE PASAMOS LOS DATOS DEL MODELO AL SHADER
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.6f, 0.0f, 0.3f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);

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
	projectionShader.setMat4("model", model); //LE PASAMOS LOS DATOS DEL MODELO AL SHADER
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.6f, 0.0f, 0.3f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);

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
	projectionShader.setMat4("model", model); //LE PASAMOS LOS DATOS DEL MODELO AL SHADER
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.6f, 0.0f, 0.3f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);

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
	projectionShader.setMat4("model", model); //LE PASAMOS LOS DATOS DEL MODELO AL SHADER
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.6f, 0.0f, 0.3f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);

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
	model = glm::rotate(model, glm::radians(angHom), glm::vec3(0, 1, 0));//rotamos
	model = glm::translate(model, glm::vec3(-1.0f, 0.0f, 0.0f));
	projectionShader.setMat4("model", model);
	model = glm::scale(model, glm::vec3(2.0f, 3.0f, 0.025f)); //HACEMOS UN "MODELO" ESCALADO CON MEDIDAS 5 * 1 * 3 UNIDADES
	projectionShader.setMat4("model", model);//LE PASAMOS LOS DATOS DEL MODELO AL SHADER
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.6f, 0.0f, 0.3f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);

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
	projectionShader.setMat4("model", model); //LE PASAMOS LOS DATOS DEL MODELO AL SHADER
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.6f, 0.0f, 0.3f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);

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
	projectionShader.setMat4("model", model); //LE PASAMOS LOS DATOS DEL MODELO AL SHADER
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.6f, 0.0f, 0.3f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);

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
	projectionShader.setMat4("model", model); //LE PASAMOS LOS DATOS DEL MODELO AL SHADER
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.6f, 0.0f, 0.3f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);

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
	model = glm::rotate(model, glm::radians(angHom), glm::vec3(0, 1, 0));//rotamos
	model = glm::translate(model, glm::vec3(-1.0f, 0.0f, 0.0f));
	projectionShader.setMat4("model", model);
	model = glm::scale(model, glm::vec3(2.0f, 0.1f, 0.025f)); //HACEMOS UN "MODELO" ESCALADO CON MEDIDAS 5 * 1 * 3 UNIDADES
	projectionShader.setMat4("model", model);//LE PASAMOS LOS DATOS DEL MODELO AL SHADER
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.6f, 0.0f, 0.3f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);

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
	projectionShader.setMat4("model", model); //LE PASAMOS LOS DATOS DEL MODELO AL SHADER
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.6f, 0.0f, 0.3f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);

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
	projectionShader.setMat4("model", model); //LE PASAMOS LOS DATOS DEL MODELO AL SHADER
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.6f, 0.0f, 0.3f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);

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
	//----------------------------3 izquierda----------------------------------------
	model = temp01;
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.25f));
	model = glm::scale(model, glm::vec3(0.35f, 0.1f, 0.1f));
	model = glm::rotate(model, glm::radians(mercurio), glm::vec3(1, 0, 0));
	projectionShader.setMat4("model", model);
	my_cylinder.render();
	projectionShader.setMat4("projection", projection);
	glBindVertexArray(VAO);

	model = glm::translate(model, glm::vec3(0.0f, -1.7, 1.0f));
	model = glm::scale(model, glm::vec3(1.0f, 1.5f, 1.5f));
	//model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 1, 0));
	projectionShader.setMat4("model", model);
	temp02 = model;
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.6f, 0.0f, 0.3f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);


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
	//Parte superior de la canata 
	model = temp02;
	model = glm::scale(model, glm::vec3(2, 0.25, 6)); //HACEMOS UN "MODELO" ESCALADO CON MEDIDAS 5 * 1 * 3 UNIDADES
	projectionShader.setMat4("model", model); //LE PASAMOS LOS DATOS DEL MODELO AL SHADER
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.6f, 0.0f, 0.3f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);

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
	projectionShader.setMat4("model", model); //LE PASAMOS LOS DATOS DEL MODELO AL SHADER
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.6f, 0.0f, 0.3f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);

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
	projectionShader.setMat4("model", model); //LE PASAMOS LOS DATOS DEL MODELO AL SHADER
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.6f, 0.0f, 0.3f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);

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
	projectionShader.setMat4("model", model); //LE PASAMOS LOS DATOS DEL MODELO AL SHADER
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.6f, 0.0f, 0.3f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);

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
	projectionShader.setMat4("model", model); //LE PASAMOS LOS DATOS DEL MODELO AL SHADER
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.6f, 0.0f, 0.3f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);

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
	projectionShader.setMat4("model", model); //LE PASAMOS LOS DATOS DEL MODELO AL SHADER
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.6f, 0.0f, 0.3f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);

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
	projectionShader.setMat4("model", model); //LE PASAMOS LOS DATOS DEL MODELO AL SHADER
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.6f, 0.0f, 0.3f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);

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
	model = glm::rotate(model, glm::radians(angHom), glm::vec3(0, 1, 0));//rotamos
	model = glm::translate(model, glm::vec3(-1.0f, 0.0f, 0.0f));
	projectionShader.setMat4("model", model);
	model = glm::scale(model, glm::vec3(2.0f, 3.0f, 0.025f)); //HACEMOS UN "MODELO" ESCALADO CON MEDIDAS 5 * 1 * 3 UNIDADES
	projectionShader.setMat4("model", model);//LE PASAMOS LOS DATOS DEL MODELO AL SHADER
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.6f, 0.0f, 0.3f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);

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
	projectionShader.setMat4("model", model); //LE PASAMOS LOS DATOS DEL MODELO AL SHADER
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.6f, 0.0f, 0.3f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);

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
	projectionShader.setMat4("model", model); //LE PASAMOS LOS DATOS DEL MODELO AL SHADER
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.6f, 0.0f, 0.3f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);

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
	projectionShader.setMat4("model", model); //LE PASAMOS LOS DATOS DEL MODELO AL SHADER
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.6f, 0.0f, 0.3f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);

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
	model = glm::rotate(model, glm::radians(angHom), glm::vec3(0, 1, 0));//rotamos
	model = glm::translate(model, glm::vec3(-1.0f, 0.0f, 0.0f));
	projectionShader.setMat4("model", model);
	model = glm::scale(model, glm::vec3(2.0f, 0.1f, 0.025f)); //HACEMOS UN "MODELO" ESCALADO CON MEDIDAS 5 * 1 * 3 UNIDADES
	projectionShader.setMat4("model", model);//LE PASAMOS LOS DATOS DEL MODELO AL SHADER
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.6f, 0.0f, 0.3f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);

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
	projectionShader.setMat4("model", model); //LE PASAMOS LOS DATOS DEL MODELO AL SHADER
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.6f, 0.0f, 0.3f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);

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
	projectionShader.setMat4("model", model); //LE PASAMOS LOS DATOS DEL MODELO AL SHADER
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.6f, 0.0f, 0.3f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);

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
	//----------------------------4 Abajo----------------------------------------
	model = temp01;
	model = glm::translate(model, glm::vec3(0.0f, -2.25f, 0.0f));
	model = glm::scale(model, glm::vec3(0.35f, 0.1f, 0.1f));
	model = glm::rotate(model, glm::radians(mercurio), glm::vec3(1, 0, 0));
	projectionShader.setMat4("model", model);
	my_cylinder.render();
	projectionShader.setMat4("projection", projection);
	glBindVertexArray(VAO);

	model = glm::translate(model, glm::vec3(0.0f, -1.7, 1.0f));
	model = glm::scale(model, glm::vec3(1.0f, 1.5f, 1.5f));
	//model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 1, 0));
	projectionShader.setMat4("model", model);
	temp02 = model;
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.6f, 0.0f, 0.3f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);


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
	//Parte superior de la canata 
	model = temp02;
	model = glm::scale(model, glm::vec3(2, 0.25, 6)); //HACEMOS UN "MODELO" ESCALADO CON MEDIDAS 5 * 1 * 3 UNIDADES
	projectionShader.setMat4("model", model); //LE PASAMOS LOS DATOS DEL MODELO AL SHADER
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.6f, 0.0f, 0.3f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);

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
	projectionShader.setMat4("model", model); //LE PASAMOS LOS DATOS DEL MODELO AL SHADER
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.6f, 0.0f, 0.3f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);

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
	projectionShader.setMat4("model", model); //LE PASAMOS LOS DATOS DEL MODELO AL SHADER
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.6f, 0.0f, 0.3f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);

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
	projectionShader.setMat4("model", model); //LE PASAMOS LOS DATOS DEL MODELO AL SHADER
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.6f, 0.0f, 0.3f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);

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
	projectionShader.setMat4("model", model); //LE PASAMOS LOS DATOS DEL MODELO AL SHADER
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.6f, 0.0f, 0.3f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);

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
	projectionShader.setMat4("model", model); //LE PASAMOS LOS DATOS DEL MODELO AL SHADER
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.6f, 0.0f, 0.3f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);

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
	projectionShader.setMat4("model", model); //LE PASAMOS LOS DATOS DEL MODELO AL SHADER
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.6f, 0.0f, 0.3f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);

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
	model = glm::rotate(model, glm::radians(angHom), glm::vec3(0, 1, 0));//rotamos
	model = glm::translate(model, glm::vec3(-1.0f, 0.0f, 0.0f));
	projectionShader.setMat4("model", model);
	model = glm::scale(model, glm::vec3(2.0f, 3.0f, 0.025f)); //HACEMOS UN "MODELO" ESCALADO CON MEDIDAS 5 * 1 * 3 UNIDADES
	projectionShader.setMat4("model", model);//LE PASAMOS LOS DATOS DEL MODELO AL SHADER
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.6f, 0.0f, 0.3f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);

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
	projectionShader.setMat4("model", model); //LE PASAMOS LOS DATOS DEL MODELO AL SHADER
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.6f, 0.0f, 0.3f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);

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
	projectionShader.setMat4("model", model); //LE PASAMOS LOS DATOS DEL MODELO AL SHADER
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.6f, 0.0f, 0.3f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);

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
	projectionShader.setMat4("model", model); //LE PASAMOS LOS DATOS DEL MODELO AL SHADER
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.6f, 0.0f, 0.3f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);

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
	model = glm::rotate(model, glm::radians(angHom), glm::vec3(0, 1, 0));//rotamos
	model = glm::translate(model, glm::vec3(-1.0f, 0.0f, 0.0f));
	projectionShader.setMat4("model", model);
	model = glm::scale(model, glm::vec3(2.0f, 0.1f, 0.025f)); //HACEMOS UN "MODELO" ESCALADO CON MEDIDAS 5 * 1 * 3 UNIDADES
	projectionShader.setMat4("model", model);//LE PASAMOS LOS DATOS DEL MODELO AL SHADER
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.6f, 0.0f, 0.3f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);

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
	projectionShader.setMat4("model", model); //LE PASAMOS LOS DATOS DEL MODELO AL SHADER
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.6f, 0.0f, 0.3f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);

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
	projectionShader.setMat4("model", model); //LE PASAMOS LOS DATOS DEL MODELO AL SHADER
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.6f, 0.0f, 0.3f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);

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
	//----------------------------5 izquierda arriba----------------------------------------
	model = temp01;
	model = glm::translate(model, glm::vec3(0.0f, 1.59f, -1.59f));
	model = glm::scale(model, glm::vec3(0.35f, 0.1f, 0.1f));
	model = glm::rotate(model, glm::radians(mercurio), glm::vec3(1, 0, 0));
	projectionShader.setMat4("model", model);
	my_cylinder.render();
	projectionShader.setMat4("projection", projection);
	glBindVertexArray(VAO);

	model = glm::translate(model, glm::vec3(0.0f, -1.7, 1.0f));
	model = glm::scale(model, glm::vec3(1.0f, 1.5f, 1.5f));
	//model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 1, 0));
	projectionShader.setMat4("model", model);
	temp02 = model;
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.6f, 0.0f, 0.3f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);


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
	//Parte superior de la canata 
	model = temp02;
	model = glm::scale(model, glm::vec3(2, 0.25, 6)); //HACEMOS UN "MODELO" ESCALADO CON MEDIDAS 5 * 1 * 3 UNIDADES
	projectionShader.setMat4("model", model); //LE PASAMOS LOS DATOS DEL MODELO AL SHADER
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.6f, 0.0f, 0.3f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);

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
	projectionShader.setMat4("model", model); //LE PASAMOS LOS DATOS DEL MODELO AL SHADER
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.6f, 0.0f, 0.3f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);

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
	projectionShader.setMat4("model", model); //LE PASAMOS LOS DATOS DEL MODELO AL SHADER
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.6f, 0.0f, 0.3f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);

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
	projectionShader.setMat4("model", model); //LE PASAMOS LOS DATOS DEL MODELO AL SHADER
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.6f, 0.0f, 0.3f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);

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
	projectionShader.setMat4("model", model); //LE PASAMOS LOS DATOS DEL MODELO AL SHADER
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.6f, 0.0f, 0.3f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);

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
	projectionShader.setMat4("model", model); //LE PASAMOS LOS DATOS DEL MODELO AL SHADER
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.6f, 0.0f, 0.3f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);

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
	projectionShader.setMat4("model", model); //LE PASAMOS LOS DATOS DEL MODELO AL SHADER
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.6f, 0.0f, 0.3f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);

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
	model = glm::rotate(model, glm::radians(angHom), glm::vec3(0, 1, 0));//rotamos
	model = glm::translate(model, glm::vec3(-1.0f, 0.0f, 0.0f));
	projectionShader.setMat4("model", model);
	model = glm::scale(model, glm::vec3(2.0f, 3.0f, 0.025f)); //HACEMOS UN "MODELO" ESCALADO CON MEDIDAS 5 * 1 * 3 UNIDADES
	projectionShader.setMat4("model", model);//LE PASAMOS LOS DATOS DEL MODELO AL SHADER
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.6f, 0.0f, 0.3f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);

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
	projectionShader.setMat4("model", model); //LE PASAMOS LOS DATOS DEL MODELO AL SHADER
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.6f, 0.0f, 0.3f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);

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
	projectionShader.setMat4("model", model); //LE PASAMOS LOS DATOS DEL MODELO AL SHADER
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.6f, 0.0f, 0.3f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);

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
	projectionShader.setMat4("model", model); //LE PASAMOS LOS DATOS DEL MODELO AL SHADER
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.6f, 0.0f, 0.3f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);

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
	model = glm::rotate(model, glm::radians(angHom), glm::vec3(0, 1, 0));//rotamos
	model = glm::translate(model, glm::vec3(-1.0f, 0.0f, 0.0f));
	projectionShader.setMat4("model", model);
	model = glm::scale(model, glm::vec3(2.0f, 0.1f, 0.025f)); //HACEMOS UN "MODELO" ESCALADO CON MEDIDAS 5 * 1 * 3 UNIDADES
	projectionShader.setMat4("model", model);//LE PASAMOS LOS DATOS DEL MODELO AL SHADER
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.6f, 0.0f, 0.3f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);

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
	projectionShader.setMat4("model", model); //LE PASAMOS LOS DATOS DEL MODELO AL SHADER
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.6f, 0.0f, 0.3f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);

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
	projectionShader.setMat4("model", model); //LE PASAMOS LOS DATOS DEL MODELO AL SHADER
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.6f, 0.0f, 0.3f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);

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
	//----------------------------6 izquierda abajo----------------------------------------
	model = temp01;
	model = glm::translate(model, glm::vec3(0.0f, -1.59f, -1.59f));
	model = glm::scale(model, glm::vec3(0.35f, 0.1f, 0.1f));
	model = glm::rotate(model, glm::radians(mercurio), glm::vec3(1, 0, 0));
	projectionShader.setMat4("model", model);
	my_cylinder.render();
	projectionShader.setMat4("projection", projection);
	glBindVertexArray(VAO);

	model = glm::translate(model, glm::vec3(0.0f, -1.7, 1.0f));
	model = glm::scale(model, glm::vec3(1.0f, 1.5f, 1.5f));
	//model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 1, 0));
	projectionShader.setMat4("model", model);
	temp02 = model;
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.6f, 0.0f, 0.3f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);


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
	//Parte superior de la canata 
	model = temp02;
	model = glm::scale(model, glm::vec3(2, 0.25, 6)); //HACEMOS UN "MODELO" ESCALADO CON MEDIDAS 5 * 1 * 3 UNIDADES
	projectionShader.setMat4("model", model); //LE PASAMOS LOS DATOS DEL MODELO AL SHADER
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.6f, 0.0f, 0.3f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);

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
	projectionShader.setMat4("model", model); //LE PASAMOS LOS DATOS DEL MODELO AL SHADER
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.6f, 0.0f, 0.3f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);

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
	projectionShader.setMat4("model", model); //LE PASAMOS LOS DATOS DEL MODELO AL SHADER
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.6f, 0.0f, 0.3f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);

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
	projectionShader.setMat4("model", model); //LE PASAMOS LOS DATOS DEL MODELO AL SHADER
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.6f, 0.0f, 0.3f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);

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
	projectionShader.setMat4("model", model); //LE PASAMOS LOS DATOS DEL MODELO AL SHADER
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.6f, 0.0f, 0.3f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);

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
	projectionShader.setMat4("model", model); //LE PASAMOS LOS DATOS DEL MODELO AL SHADER
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.6f, 0.0f, 0.3f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);

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
	projectionShader.setMat4("model", model); //LE PASAMOS LOS DATOS DEL MODELO AL SHADER
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.6f, 0.0f, 0.3f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);

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
	model = glm::rotate(model, glm::radians(angHom), glm::vec3(0, 1, 0));//rotamos
	model = glm::translate(model, glm::vec3(-1.0f, 0.0f, 0.0f));
	projectionShader.setMat4("model", model);
	model = glm::scale(model, glm::vec3(2.0f, 3.0f, 0.025f)); //HACEMOS UN "MODELO" ESCALADO CON MEDIDAS 5 * 1 * 3 UNIDADES
	projectionShader.setMat4("model", model);//LE PASAMOS LOS DATOS DEL MODELO AL SHADER
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.6f, 0.0f, 0.3f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);

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
	projectionShader.setMat4("model", model); //LE PASAMOS LOS DATOS DEL MODELO AL SHADER
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.6f, 0.0f, 0.3f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);

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
	projectionShader.setMat4("model", model); //LE PASAMOS LOS DATOS DEL MODELO AL SHADER
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.6f, 0.0f, 0.3f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);

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
	projectionShader.setMat4("model", model); //LE PASAMOS LOS DATOS DEL MODELO AL SHADER
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.6f, 0.0f, 0.3f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);

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
	model = glm::rotate(model, glm::radians(angHom), glm::vec3(0, 1, 0));//rotamos
	model = glm::translate(model, glm::vec3(-1.0f, 0.0f, 0.0f));
	projectionShader.setMat4("model", model);
	model = glm::scale(model, glm::vec3(2.0f, 0.1f, 0.025f)); //HACEMOS UN "MODELO" ESCALADO CON MEDIDAS 5 * 1 * 3 UNIDADES
	projectionShader.setMat4("model", model);//LE PASAMOS LOS DATOS DEL MODELO AL SHADER
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.6f, 0.0f, 0.3f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);

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
	projectionShader.setMat4("model", model); //LE PASAMOS LOS DATOS DEL MODELO AL SHADER
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.6f, 0.0f, 0.3f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);

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
	projectionShader.setMat4("model", model); //LE PASAMOS LOS DATOS DEL MODELO AL SHADER
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.6f, 0.0f, 0.3f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);

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
	//----------------------------7 derecha abajo----------------------------------------
	model = temp01;
	model = glm::translate(model, glm::vec3(0.0f, -1.59f, 1.59f));
	model = glm::scale(model, glm::vec3(0.35f, 0.1f, 0.1f));
	model = glm::rotate(model, glm::radians(mercurio), glm::vec3(1, 0, 0));
	projectionShader.setMat4("model", model);
	my_cylinder.render();
	projectionShader.setMat4("projection", projection);
	glBindVertexArray(VAO);

	model = glm::translate(model, glm::vec3(0.0f, -1.7, 1.0f));
	model = glm::scale(model, glm::vec3(1.0f, 1.5f, 1.5f));
	//model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 1, 0));
	projectionShader.setMat4("model", model);
	temp02 = model;
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.6f, 0.0f, 0.3f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);


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
	//Parte superior de la canata 
	model = temp02;
	model = glm::scale(model, glm::vec3(2, 0.25, 6)); //HACEMOS UN "MODELO" ESCALADO CON MEDIDAS 5 * 1 * 3 UNIDADES
	projectionShader.setMat4("model", model); //LE PASAMOS LOS DATOS DEL MODELO AL SHADER
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.6f, 0.0f, 0.3f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);

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
	projectionShader.setMat4("model", model); //LE PASAMOS LOS DATOS DEL MODELO AL SHADER
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.6f, 0.0f, 0.3f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);

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
	projectionShader.setMat4("model", model); //LE PASAMOS LOS DATOS DEL MODELO AL SHADER
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.6f, 0.0f, 0.3f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);

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
	projectionShader.setMat4("model", model); //LE PASAMOS LOS DATOS DEL MODELO AL SHADER
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.6f, 0.0f, 0.3f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);

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
	projectionShader.setMat4("model", model); //LE PASAMOS LOS DATOS DEL MODELO AL SHADER
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.6f, 0.0f, 0.3f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);

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
	projectionShader.setMat4("model", model); //LE PASAMOS LOS DATOS DEL MODELO AL SHADER
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.6f, 0.0f, 0.3f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);

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
	projectionShader.setMat4("model", model); //LE PASAMOS LOS DATOS DEL MODELO AL SHADER
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.6f, 0.0f, 0.3f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);

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
	model = glm::rotate(model, glm::radians(angHom), glm::vec3(0, 1, 0));//rotamos
	model = glm::translate(model, glm::vec3(-1.0f, 0.0f, 0.0f));
	projectionShader.setMat4("model", model);
	model = glm::scale(model, glm::vec3(2.0f, 3.0f, 0.025f)); //HACEMOS UN "MODELO" ESCALADO CON MEDIDAS 5 * 1 * 3 UNIDADES
	projectionShader.setMat4("model", model);//LE PASAMOS LOS DATOS DEL MODELO AL SHADER
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.6f, 0.0f, 0.3f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);

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
	projectionShader.setMat4("model", model); //LE PASAMOS LOS DATOS DEL MODELO AL SHADER
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.6f, 0.0f, 0.3f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);

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
	projectionShader.setMat4("model", model); //LE PASAMOS LOS DATOS DEL MODELO AL SHADER
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.6f, 0.0f, 0.3f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);

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
	projectionShader.setMat4("model", model); //LE PASAMOS LOS DATOS DEL MODELO AL SHADER
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.6f, 0.0f, 0.3f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);

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
	model = glm::rotate(model, glm::radians(angHom), glm::vec3(0, 1, 0));//rotamos
	model = glm::translate(model, glm::vec3(-1.0f, 0.0f, 0.0f));
	projectionShader.setMat4("model", model);
	model = glm::scale(model, glm::vec3(2.0f, 0.1f, 0.025f)); //HACEMOS UN "MODELO" ESCALADO CON MEDIDAS 5 * 1 * 3 UNIDADES
	projectionShader.setMat4("model", model);//LE PASAMOS LOS DATOS DEL MODELO AL SHADER
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.6f, 0.0f, 0.3f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);

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
	projectionShader.setMat4("model", model); //LE PASAMOS LOS DATOS DEL MODELO AL SHADER
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.6f, 0.0f, 0.3f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);

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
	projectionShader.setMat4("model", model); //LE PASAMOS LOS DATOS DEL MODELO AL SHADER
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.6f, 0.0f, 0.3f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);

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
	//----------------------------8 derecha arriba----------------------------------------
	model = temp01;
	model = glm::translate(model, glm::vec3(0.0f, 1.59f, 1.59f));
	model = glm::scale(model, glm::vec3(0.35f, 0.1f, 0.1f));
	model = glm::rotate(model, glm::radians(mercurio), glm::vec3(1, 0, 0));
	projectionShader.setMat4("model", model);
	my_cylinder.render();
	projectionShader.setMat4("projection", projection);
	glBindVertexArray(VAO);

	model = glm::translate(model, glm::vec3(0.0f, -1.7, 1.0f));
	model = glm::scale(model, glm::vec3(1.0f, 1.5f, 1.5f));
	//model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 1, 0));
	projectionShader.setMat4("model", model);
	temp02 = model;
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.6f, 0.0f, 0.3f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);


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
	//Parte superior de la canata 
	model = temp02;
	model = glm::scale(model, glm::vec3(2, 0.25, 6)); //HACEMOS UN "MODELO" ESCALADO CON MEDIDAS 5 * 1 * 3 UNIDADES
	projectionShader.setMat4("model", model); //LE PASAMOS LOS DATOS DEL MODELO AL SHADER
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.6f, 0.0f, 0.3f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);

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
	projectionShader.setMat4("model", model); //LE PASAMOS LOS DATOS DEL MODELO AL SHADER
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.6f, 0.0f, 0.3f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);

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
	projectionShader.setMat4("model", model); //LE PASAMOS LOS DATOS DEL MODELO AL SHADER
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.6f, 0.0f, 0.3f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);

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
	projectionShader.setMat4("model", model); //LE PASAMOS LOS DATOS DEL MODELO AL SHADER
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.6f, 0.0f, 0.3f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);

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
	projectionShader.setMat4("model", model); //LE PASAMOS LOS DATOS DEL MODELO AL SHADER
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.6f, 0.0f, 0.3f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);

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
	projectionShader.setMat4("model", model); //LE PASAMOS LOS DATOS DEL MODELO AL SHADER
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.6f, 0.0f, 0.3f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);

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
	projectionShader.setMat4("model", model); //LE PASAMOS LOS DATOS DEL MODELO AL SHADER
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.6f, 0.0f, 0.3f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);

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
	model = glm::rotate(model, glm::radians(angHom), glm::vec3(0, 1, 0));//rotamos
	model = glm::translate(model, glm::vec3(-1.0f, 0.0f, 0.0f));
	projectionShader.setMat4("model", model);
	model = glm::scale(model, glm::vec3(2.0f, 3.0f, 0.025f)); //HACEMOS UN "MODELO" ESCALADO CON MEDIDAS 5 * 1 * 3 UNIDADES
	projectionShader.setMat4("model", model);//LE PASAMOS LOS DATOS DEL MODELO AL SHADER
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.6f, 0.0f, 0.3f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);

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
	projectionShader.setMat4("model", model); //LE PASAMOS LOS DATOS DEL MODELO AL SHADER
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.6f, 0.0f, 0.3f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);

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
	projectionShader.setMat4("model", model); //LE PASAMOS LOS DATOS DEL MODELO AL SHADER
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.6f, 0.0f, 0.3f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);

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
	projectionShader.setMat4("model", model); //LE PASAMOS LOS DATOS DEL MODELO AL SHADER
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.6f, 0.0f, 0.3f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);

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
	model = glm::rotate(model, glm::radians(angHom), glm::vec3(0, 1, 0));//rotamos
	model = glm::translate(model, glm::vec3(-1.0f, 0.0f, 0.0f));
	projectionShader.setMat4("model", model);
	model = glm::scale(model, glm::vec3(2.0f, 0.1f, 0.025f)); //HACEMOS UN "MODELO" ESCALADO CON MEDIDAS 5 * 1 * 3 UNIDADES
	projectionShader.setMat4("model", model);//LE PASAMOS LOS DATOS DEL MODELO AL SHADER
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.6f, 0.0f, 0.3f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);

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
	projectionShader.setMat4("model", model); //LE PASAMOS LOS DATOS DEL MODELO AL SHADER
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.6f, 0.0f, 0.3f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);

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
	projectionShader.setMat4("model", model); //LE PASAMOS LOS DATOS DEL MODELO AL SHADER
	projectionShader.setVec3("ambientColor", 0.0f, 0.0f, 1.0f);
	projectionShader.setVec3("diffuseColor", 0.6f, 0.0f, 0.3f);
	projectionShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);

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
	//--------------------------Asientos---------------------------------------
	//-------------------------Rueda trasera---------------
	//-----------------RUEDA-----------------------------------
	
	//-----------Riel---------------------------------------
	/*model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(4.2, 0, 0));
	//model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 1, 0));
	model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
	projectionShader.setMat4("model", model);
	my_cylinder.riel(model);*/
	//-----------Riel---------------------------------------



	//----------------Cilindro blanco -------------------------
	lampShader.use();//esto es para indicar que shader se va a usar y poder cambiar entre shaders
	lampShader.setMat4("projection", projection);
	lampShader.setMat4("view", view);
	model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 1, 0));
	model = glm::translate(model, lightPos);
	model = glm::scale(model, glm::vec3(0.8f));
	lampShader.setMat4("model", model);
	my_cylinder.render();	//Sphere
	//-------------------Cilindor blanco----------------------
	
	
	
	glBindVertexArray(lightVAO);
	//glDrawArrays(GL_TRIANGLES, 0, 36);	//Light
	//glBindVertexArray(0);

}
int main()

{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);*/
#ifdef __APPLE__

	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X

#endif

	// glfw window creation
	// --------------------
	monitors = glfwGetPrimaryMonitor();
	getResolution();
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Practica 7", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwSetWindowPos(window, 0, 30);
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, resize);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	//To Enable capture of our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	glewInit();
	//Mis funciones
	//Datos a utilizar
	myData();
	my_cylinder.init();
	my_toroide.init();
	my_esfera.init();

	glEnable(GL_DEPTH_TEST);
	// render loop
	// While the windows is not closed
	while (!glfwWindowShouldClose(window))

	{
		// per-frame time logic
		// --------------------
		double currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		// input
		// -----
		my_input(window);
		animate();
		// render
		// Backgound color
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Mi función de dibujo
		display();
		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();

	}

	// glfw: terminate, clearing all previously allocated GLFW resources.

	// ------------------------------------------------------------------

	glDeleteVertexArrays(1, &VAO);
	glDeleteVertexArrays(1, &lightVAO);
	glDeleteBuffers(1, &VBO);
	glfwTerminate();

	return 0;

}



// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly

// ---------------------------------------------------------------------------------------------------------

void my_input(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, (float)deltaTime);
}



// glfw: whenever the window size changed (by OS or user resize) this callback function executes

// ---------------------------------------------------------------------------------------------

void resize(GLFWwindow* window, int width, int height)

{

	// Set the Viewport to the size of the created window

	glViewport(0, 0, width, height);

}
// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}
	double xoffset = xpos - lastX;

	double yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top



	lastX = xpos;

	lastY = ypos;



	camera.ProcessMouseMovement(xoffset, yoffset);

}



// glfw: whenever the mouse scroll wheel scrolls, this callback is called

// ----------------------------------------------------------------------

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)

{

	camera.ProcessMouseScroll(yoffset);

}



/*

shader light vertices



version 330 core

layout (location = 0) in vec3 aPos;

layout (location = 1) in vec3 aNormal;



uniform mat4 model;

uniform mat4 view;

uniform mat4 projection;



out vec3 FragPos;

out vec3 Normal;



void main()

{

gl_Position = projection * view * model * vec4(aPos, 1.0f);



FragPos = vec3(model * vec4(aPos, 1.0f));

Normal = mat3(transpose(inverse(model))) * aNormal;

}

*/

