/*---------------------------------------------------------*/
/* ----------------   Práctica 9 --------------------------*/
/*-----------------    2019-2   ---------------------------*/
/*--------- Alumno: Zagoya Mellado Roberto Uriel ---------*/
/*----------Version visual: 2017---------------------------*/
/*------------Ejercicio casa-----------------------------*/
/*------------------Grupo: 04-----------------------------*/
/*------------------Tecla E para: Spotlight
--------------------Tecla R para: direcional
--------------------Tecla T para: Position*/
#define STB_IMAGE_IMPLEMENTATION
#include <glew.h>
#include <glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <shader_m.h>

#include <iostream>
#include "esfera.h"
#include "camera.h"
#include "stb_image.h"
//#include "toroide.h"
//#include "cilindro.h"
//#include "canasta.h"
//Cilindro my_cylinder(1.0);
//Toroide my_toroide(1.0);
Esfera my_sphere(1.0f);
//Canasta my_canasta(1.0f);

void resize(GLFWwindow* window, int width, int height);
void my_input(GLFWwindow *window);
void mouse_callback(GLFWwindow *window, double xpos, double ypos);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

// settings
// Window size
int SCR_WIDTH = 3800;
int SCR_HEIGHT = 7600;

GLFWmonitor *monitors;
GLuint VBO, VAO, EBO;

//Camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
double	lastX = 0.0f,
		lastY = 0.0f;
bool firstMouse = true;

//Timing
double	deltaTime = 0.0f,
		lastFrame = 0.0f;

//Lighting
glm::vec3 lightPosition(0.0f, 3.0f, 0.0f); //Aqui declaramos la posicion de la luz, se utiliza cuando vayamos a utilizar iluminacion puntual o de reflector
glm::vec3 lightDirection(0.0f, 0.0f, -3.0f); //En esta parte se asigna la direccion de la luz para cuando utilizemos iluminacion direccional o de reflector

void myData(void);
void display(void);
void getResolution(void);
void animate(void);
void LoadTextures(void);
unsigned int generateTextures(char*, bool);

//For Keyboard
float	movX = 0.0f,
		movY = 0.0f,
		movZ = -5.0f,
		rotX = 0.0f;
//float bandera = 0.2;
//float angHom = 0.0f;
int luz = 0;

/*float	sol = 0.0f,
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
neptuno = 0.0f;*/


//Texture
unsigned int	t_smile,
				t_toalla,
				t_unam,
				t_white,
				t_panda,
				t_cubo,
				t_caja,
				t_caja_brillo,
				madera,
				t_cf1,
				frontal,
				trasera,
				superior,
				inferior,
				derecho,
				brillo,
				izquierdo,
				fSuperior,
				sky;


unsigned int generateTextures(const char* filename, bool alfa)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load image, create texture and generate mipmaps
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
	
	unsigned char *data = stbi_load(filename, &width, &height, &nrChannels, 0); //Funcion para cargar las texturas
	if (data)
	{
		if (alfa)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		else
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		return textureID;
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
		return 100;
	}

	stbi_image_free(data);
}

void getResolution()
{
	const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	SCR_WIDTH = mode->width;
	SCR_HEIGHT = (mode->height) - 80;

	lastX = SCR_WIDTH / 2.0f;
	lastY = SCR_HEIGHT / 2.0f;

}

void LoadTextures() //carga de todas las texturas
{

	t_smile = generateTextures("Texturas/awesomeface.png", 1);
	t_toalla = generateTextures("Texturas/toalla.tga", 0);
	t_unam = generateTextures("Texturas/escudo_unam.png", 1);
	t_white = generateTextures("Texturas/white.jpg", 0);
	t_panda = generateTextures("Texturas/Panda_01.png", 1);
	t_cubo = generateTextures("Texturas/Cube03.png", 1);
	t_caja = generateTextures("Texturas/caja.png", 1);
	t_caja_brillo = generateTextures("Texturas/caja_specular.png", 1);
	madera = generateTextures("Texturas/madera.jpg", 0);
	frontal = generateTextures("Texturas/frontal.jpg", 0);
	trasera = generateTextures("Texturas/trasera.jpg", 0);
	superior= generateTextures("Texturas/techo.jpg", 0);
	inferior = generateTextures("Texturas/suelo.jpg", 0);
	derecho = generateTextures("Texturas/derecha.jpg", 0);
	izquierdo = generateTextures("Texturas/izquierda.jpg", 0);
	brillo = generateTextures("Texturas/brillo.jpg", 0);
	fSuperior = generateTextures("Texturas/BibliotecaFrente.jpg", 0);
	sky = generateTextures("Texturas/sky.jpg", 0);


	
	
}

void myData()
{	
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
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, 1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, 1.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, 1.0f,  1.0f,  1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, 1.0f,  0.0f,  1.0f,
		//Frontal
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  -1.0f,  1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  -1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  -1.0f,  0.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  -1.0f,  1.0f,  1.0f,

		//Izquierda
		-0.5f, -0.5f, -0.5f, 1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f, 1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, 1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		-0.5f,  0.5f, -0.5f, 1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		
		//Derecha
		0.5f,  -0.5f,   0.5f,  -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		0.5f,	0.5f,	0.5f,  -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		0.5f,   0.5f,  -0.5f,  -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		0.5f,  -0.5f,  -0.5f,  -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
		//Inferior
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
		//Superior
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,

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
	
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
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

}

void animate(void)
{
	/*sol += 0.1f;
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
	}*/

}

void display(void) //En esta funcion jugamos con todas las luces, a cada tipo de luz se le creo un tipo de shader, pero no por eso se deben manejar los shaders así, se pueden mezclar. Para fines didacticos se hizo así
{
	// bind textures on corresponding texture units
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, t_smile);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, t_toalla);
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, t_unam);
	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, t_white);
	glActiveTexture(GL_TEXTURE5);
	glBindTexture(GL_TEXTURE_2D, t_panda);
	glActiveTexture(GL_TEXTURE6);
	glBindTexture(GL_TEXTURE_2D, t_cubo);
	glActiveTexture(GL_TEXTURE7);
	glBindTexture(GL_TEXTURE_2D, t_caja);
	glActiveTexture(GL_TEXTURE8);
	glBindTexture(GL_TEXTURE_2D, t_caja_brillo);
	glActiveTexture(GL_TEXTURE9);
	glBindTexture(GL_TEXTURE_2D, madera);
	glActiveTexture(GL_TEXTURE10);
	glBindTexture(GL_TEXTURE_2D, frontal);
	glActiveTexture(GL_TEXTURE11);
	glBindTexture(GL_TEXTURE_2D, trasera);
	glActiveTexture(GL_TEXTURE12);
	glBindTexture(GL_TEXTURE_2D, superior);
	glActiveTexture(GL_TEXTURE13);
	glBindTexture(GL_TEXTURE_2D, inferior);
	glActiveTexture(GL_TEXTURE14);
	glBindTexture(GL_TEXTURE_2D, derecho);
	glActiveTexture(GL_TEXTURE15);
	glBindTexture(GL_TEXTURE_2D, izquierdo);
	glActiveTexture(GL_TEXTURE16);
	glBindTexture(GL_TEXTURE_2D, brillo);
	glActiveTexture(GL_TEXTURE17);
	glBindTexture(GL_TEXTURE_2D, fSuperior);
	glActiveTexture(GL_TEXTURE18);
	glBindTexture(GL_TEXTURE_2D, sky);
	//Shader projectionShader("shaders/shader_light.vs", "shaders/shader_light.fs");
	//Shader projectionShader("shaders/shader_texture_color.vs", "shaders/shader_texture_color.fs");
	//Shader projectionShader("shaders/shader_texture_color.vs", "shaders/shader_texture_color.fs");
	//Shader lightingShader("shaders/shader_texture_light_pos.vs", "shaders/shader_texture_light_pos.fs"); //Positional
	//Shader lightingShader("shaders/shader_texture_light_dir.vs", "shaders/shader_texture_light_dir.fs"); //Directional
	Shader textureShader("shaders/shader_texture.vs", "shaders/shader_texture.fs");
	Shader lightingShader("shaders/shader_texture_light_spot.vs", "shaders/shader_texture_light_spot.fs"); //Spotlight
	Shader lampShader("shaders/shader_lamp.vs", "shaders/shader_lamp.fs");
	//To Use Lighting
	
	//lightingShader.setVec3("light.direction", lightDirection);
	//lightingShader.use();
	Shader projectionShader("shaders/shader_light.vs", "shaders/shader_light.fs");
	
	
	if (luz == 0) {
		//Shader lightingShader("shaders/shader_texture_light_spot.vs", "shaders/shader_texture_light_spot.fs"); //Spotlight
		lightingShader.use();
		lightingShader.setVec3("light.position", camera.Position);
		lightingShader.setVec3("light.direction", camera.Front);
		lightingShader.setFloat("light.cutOff", glm::cos(glm::radians(12.5f)));
		
	}
	if (luz == 1) {//direcional adelante
		
		lightingShader.use();
		lightingShader.setVec3("light.direction", lightDirection);
		lightingShader.setVec3("light.position", lightPosition);
		
		
	}
	if (luz == 2) {
		lightingShader.use();
		//lightingShader.setVec3("light.position", lightPosition);
		lightingShader.setVec3("light.direction", lightDirection);
		
	}
	

	// light properties
	lightingShader.setVec3("light.ambient", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("light.diffuse", 0.8f, 0.8f, 0.8f);
	lightingShader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);
	//For Positional and Spotlight
	lightingShader.setVec3("viewPos", camera.Position);
	lightingShader.setFloat("light.constant", 1.0f);
	lightingShader.setFloat("light.linear", 0.09f);
	lightingShader.setFloat("light.quadratic", 0.032f);
	

	// material properties
	lightingShader.setFloat("material_shininess", 32.0f);

	

	// create transformations and Projection
	glm::mat4 temp = glm::mat4(1.0f);
	glm::mat4 temp01 = glm::mat4(1.0f); //Temp
	glm::mat4 temp02 = glm::mat4(1.0f);
	glm::mat4 temp03 = glm::mat4(1.0f);
	glm::mat4 model = glm::mat4(1.0f);		// initialize Matrix, Use this matrix for individual models
	glm::mat4 view = glm::mat4(1.0f);		//Use this matrix for ALL models
	glm::mat4 projection = glm::mat4(1.0f);	//This matrix is for Projection

	//Use "projection" to include Camera
	projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 300.0f);
	view = camera.GetViewMatrix();

	// pass them to the shaders
	//lightingShader.setVec3("viewPos", camera.Position);
	lightingShader.setMat4("model", model);
	lightingShader.setMat4("view", view);
	// note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
	lightingShader.setMat4("projection", projection);


	glBindVertexArray(VAO);
	//Colocar código aquí
	/*Para crear una nueva caja lo que hacemos es transladarnos y escalarla las matrices*/
	model = glm::translate(model, glm::vec3(2.0f, 10.0f, 2.0f));//trasladamos
	model = glm::scale(model, glm::vec3(250.0f, 80.0f, 250.0f));//escalamos
	//model = glm::scale(model, glm::vec3(80.0f, 50.0f, 80.0f));//escalamos
	/*Para esta caja usaremos la caja dos declarada en los verticesque se encuentran anteriormente*/

	lightingShader.setMat4("model", model);//iniciamos el shader al lugar donde nos trasladamos
	/*Debido a que todo el tiempo estaremos trabajando aquí no es necesario iniciar el sheder cada 
	vez que se dibuja una nueva cara, pues siempre estaremos aqui para esta caja
	solo usaremos el shader para dibujar las diferentes texturas, pero si se quiere reiniciar 
	el shader en la matriz que estamos daria lo mismo o incluso un poco pero tan solo por las lineas 
	de codigo.*/

	//--------------------Sky Box--------------------
	lightingShader.setInt("material_diffuse", trasera);//parte trasera
	//glDrawArrays(GL_QUADS, 24, 4);

	for (int i = 0; i < 4; i++)
	{
		glDrawArrays(GL_TRIANGLE_FAN, 24, i + 1);
	}
	

	//lightingShader.setMat4("model", model);
	lightingShader.setInt("material_diffuse", frontal);//Parte frontal
	//glDrawArrays(GL_QUADS, 28, 4);
	for (int i = 0; i < 4; i++)
	{
		glDrawArrays(GL_TRIANGLE_FAN, 28, i + 1);
	}
	//lightingShader.setMat4("model", model);
	lightingShader.setInt("material_diffuse", inferior);//parte inferior
	//glDrawArrays(GL_QUADS, 40, 4);
	for (int i = 0; i < 4; i++)
	{
		glDrawArrays(GL_TRIANGLE_FAN, 40, i + 1);
	}
	//lightingShader.setMat4("model", model);
	lightingShader.setInt("material_diffuse", superior);//parte superior
	//glDrawArrays(GL_QUADS, 44, 4);
	for (int i = 0; i < 4; i++)
	{
		glDrawArrays(GL_TRIANGLE_FAN, 44, i + 1);
	}
	//lightingShader.setMat4("model", model);
	lightingShader.setInt("material_diffuse", izquierdo);//parte izquierda
	/*Como aqui queremos agregar el material especular se lo pasamos al shader y como parametros nuestra textura 
	que sera el especular, en esta parte en especifico lo tendral los dos costados, por lo que solo pasamos como parametro y 
	dibujamos*/
	lightingShader.setInt("material_specular", izquierdo);
	//glDrawArrays(GL_QUADS, 32, 4);
	for (int i = 0; i < 4; i++)
	{
		glDrawArrays(GL_TRIANGLE_FAN, 32, i + 1);
	}

	lightingShader.setInt("material_diffuse", derecho);
	lightingShader.setInt("material_specular", brillo);
	//glDrawArrays(GL_QUADS, 36, 4);
	for (int i = 0; i < 4; i++)
	{
		glDrawArrays(GL_TRIANGLE_FAN, 36, i + 1);
	}

	//-----------------Sky box---------------------
	
	
	

	/*if (luz == 0) {
		//Shader lightingShader("shaders/shader_texture_light_spot.vs", "shaders/shader_texture_light_spot.fs"); //Spotlight
		lightingShader.use();
		lightingShader.setVec3("light.position", camera.Position);
		lightingShader.setVec3("light.direction", camera.Front);
		lightingShader.setFloat("light.cutOff", glm::cos(glm::radians(12.5f)));

	}
	if (luz == 1) {//direcional adelante

		lightingShader.use();
		lightingShader.setVec3("light.direction", lightDirection);
		lightingShader.setVec3("light.position", lightPosition);


	}
	if (luz == 2) {
		lightingShader.use();
		//lightingShader.setVec3("light.position", lightPosition);
		lightingShader.setVec3("light.direction", lightDirection);

	}*/
	/*model = glm::mat4(1.0f);//para que los cubos de caja, unam y toalla no sean modificados, reiniciamos la matriz
	lightingShader.setMat4("model", model);//reiniciamos el shader en el inicio.
	//y dibujamos toddo nuevamente. 
	lightingShader.setVec3("ambientColor", 0.0f, 0.0f, 0.0f);
	lightingShader.setVec3("diffuseColor", 1.0f, 1.0f, 1.0f);
	lightingShader.setVec3("specularColor", 1.0f, 0.0f, 0.0f);
	lightingShader.setInt("material_diffuse", t_unam);
	lightingShader.setInt("material_specular", t_caja_brillo);
	glDrawArrays(GL_QUADS, 0,24);
	
	model = glm::translate(model, glm::vec3(4.0f, 0.0f, -1.0f));
	model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
	lightingShader.setMat4("model", model);
	lightingShader.setInt("material_diffuse", t_caja);
	glDrawArrays(GL_QUADS, 0, 24);


	model = glm::translate(glm::mat4(1.0f), glm::vec3(-2.0f, 0.0f, -3.0f));
	model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
	lightingShader.setMat4("model", model);
	lightingShader.setInt("material_diffuse", t_toalla);
	glDrawArrays(GL_QUADS, 0, 24);*/
	textureShader.use();
	textureShader.setInt("texture1", 3);
	glBindVertexArray(VAO);

/*
	//lightingShader.setInt("material_diffuse", t_unam);
	model = glm::mat4(1.0f);
	// note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
	model = glm::translate(model, glm::vec3(4.5f, 1.0f, 1.0f));
	model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
	//model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1, 0, 0));
	temp01 = model;
	model = glm::scale(model, glm::vec3(0.1f, 1.2f, 0.1f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1, 0, 0));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 1, 0));
	//model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 1, 0));
	projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	view = camera.GetViewMatrix();
	textureShader.setVec3("viewPos", camera.Position);
	textureShader.setMat4("model", model);
	textureShader.setMat4("view", view);
	textureShader.setMat4("projection", projection);

	my_canasta.riel(model, VBO, VAO, EBO);

	if (luz == 0) {
		//Shader lightingShader("shaders/shader_texture_light_spot.vs", "shaders/shader_texture_light_spot.fs"); //Spotlight
		lightingShader.use();
		lightingShader.setVec3("light.position", camera.Position);
		lightingShader.setVec3("light.direction", camera.Front);
		lightingShader.setFloat("light.cutOff", glm::cos(glm::radians(12.5f)));

	}
	if (luz == 1) {//direcional adelante

		lightingShader.use();
		lightingShader.setVec3("light.direction", lightDirection);
		lightingShader.setVec3("light.position", lightPosition);


	}
	if (luz == 2) {
		lightingShader.use();
		//lightingShader.setVec3("light.position", lightPosition);
		lightingShader.setVec3("light.direction", lightDirection);

	}*/

	glBindVertexArray(VAO);
	//Light
	lampShader.use();
	lampShader.setMat4("projection", projection);
	lampShader.setMat4("view", view);
	model = glm::mat4(1.0f);
	model = glm::translate(model, lightPosition);
	model = glm::scale(model, glm::vec3(0.25f));
	lampShader.setMat4("model", model);

	//glBindVertexArray(lightVAO);
	glDrawArrays(GL_QUADS, 0, 24);	//Light

	
	glBindVertexArray(0);

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

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Practica 9", NULL, NULL);
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
	LoadTextures();
	myData();
	my_sphere.init();
	//my_canasta.init();
	//my_cylinder.init();
	//my_toroide.init();
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
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		luz = 0;
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
		luz = 1;
	if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
		luz = 2;
	

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