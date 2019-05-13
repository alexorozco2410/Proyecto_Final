/*---------------------------------------------------------*/
/* ----------------  Proyecto Final --------------------------*/
/*-----------------    2019-2   ---------------------------*/
/*-- Computación gráfica e interacción humano computadora --*/
/*------------------Integrantes:--------------------------*/
/*------------- Orozco Hernandez Alexis  -----------------*/
/*------------- Zagoya Mellado Roberto Uriel-----------------*/
/*---------------  Version VS 2017  ----------------------*/
/*---------------------Grupo de teoria: 04----------------*/
/*------------------  Grupo 04  --------------------------*/

/*--------------------Controles:
						W: mover hacia delante
						S: Mover hacia atras
						D: Mover hacia la derecha
						A: Mover hacia la izquierda
						P: Poner de noche
						O : poner de dia
						R: Activar la aniacion de la rueda de la fortuna
						T: Activar las tazas
						D: Desactivar las tazas
						K: Activar el carro de comida
						J: Activar los carros chocones
						L: Detiene los carros chocones
						H: Activa los caballos
						V: Activa animacion por keyframes de la montaña */

//#define STB_IMAGE_IMPLEMENTATION
#include <glew.h>
#include <glfw3.h>
#include <stb_image.h>

#include "camera.h"
#include "Model.h"
#include "cilindro.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "canasta.h"
#include "rueda.h"


//para activar la animacion se usa la tecla P y para detenerla se usa la tecla O

// Other Libs
#include "SOIL2/SOIL2.h" //ayuda a cargar los modelos

Cilindro my_cilynder(1.0);
Canasta my_canasta(1.0f);
Rueda my_rueda(1.0f);

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

float ambient1 = 1.0f;
float ambient2 = 1.0f;
float ambient3 = 1.0f;

//Camera

float x_camera = 0.0f,
y_camera = 0.0f,
z_camera = 0.10f;
Camera camera(glm::vec3(x_camera, y_camera, z_camera));
double	lastX = 0.0f,
lastY = 0.0f;
bool firstMouse = true;

//Timing
double	deltaTime = 0.0f,
lastFrame = 0.0f;

//Lighting
glm::vec3 lightPosition(0.0f, 20.0f, 0.0f);
glm::vec3 lightDirection(0.0f, -0.0f, -10.0f);

void myData(void);
void display(Shader, Model, Model);
void getResolution(void);
//void animate(void);
void LoadTextures(void);
unsigned int generateTextures(char*, bool);

//For Keyboard
float	movX = 0.0f,
movY = 0.0f,
movZ = -5.0f,
rotX = 0.0f;

//Texture
unsigned int	t_smile,
t_toalla,
t_unam,
t_caja,
t_coaster,
sky,
frontal,
trasera,
superior,
inferior,
derecho,
brillo,
izquierdo,
t_caja_brillo;

//For model

//---------personaje con movimiento------------
float x_personaje = -30.0f,
y_personaje = 5.6f,
z_personaje = 0.0f,
rot_personaje = 0.0f,
rot_piernaDer = 0.0f,
rot_piernaIzq = 0.0f;

//--------------------------------------------

//----------para tasas giratorias------------
float rot_tasas = 0.0f;
float rot_base_tasas = 0.0f;
bool activate_tasas = false;
int vueltas_tasas = 0;

//------------------------------------------

//-----------para carros chocones------------
int espera = 0;

float x_cart = 0.0f;
float y_cart = 0.0f;
float z_cart = 1.0f;
float rot_cart = 0.0f;
float rot_cart_z = 0.0f;
bool play_carts = false;
int estado_cart1 = 3;
int avanzar = 0;
int mov1[20] = { 0,2,1,3,2,0,2,3,1,2,3,1,0,2,0,3,2,1,2,0 };
bool stop_cart1 = true;
bool ac_cart1 = false;
int tiempo_bumper1 = 0;

//carro 2
float x_cart2 = -30.0f;
float z_cart2 = -30.0f;
float y_cart2 = 1.0f;
float rot_cart2 = 90.0f;
float rot_cart2_z = 0.0f;
int estado_cart2 = 0;
int mov2[20] = { 1,0,3,1,2,0,0,3,1,1,3,2,1,1,3,2,1,0,0,3 };
bool stop_cart2 = true;
bool ac_cart2 = false;
int tiempo_bumper2 = 0;

//carro 3
float x_cart3 = 30.0f;
float z_cart3 = 30.0f;
float y_cart3 = 1.0f;
float rot_cart3 = 180.0f;
float rot_cart3_z = 0.0f;
int estado_cart3 = 2;
int mov3[20] = { 2,0,1,3,3,1,0,0,2,3,0,0,2,1,1,0,3,3,1,2 };
bool stop_cart3 = true;
bool ac_cart3 = false;
int tiempo_bumper3 = 0;

int aux = 0;
int aux_ac;

//-------------------------------------------

//------------------coaster cart-------------------------
float x_coaster_cart = 45.0f;
float y_coaster_cart = 5.5f;
float z_coaster_cart = -34.5f;
bool activate_coaster = false;
float rotx_coaster_cart = 0.0f; 
float roty_coaster_cart = 90.0f; 
float rotz_coaster_cart = 0.0f;


//------------------coaster cart--------------------------

//--------------------carro comida---------------------
float x_comida = -25.0f;
float z_comida = 20.0f;
float rot_comida = 90.0f;
float rot_llanta_cc = 0.0f;
bool activate_cc = false;
int estado_cc = 0;
//-----------------------------------------------------

//------------------- carrusel-------------------------
float rot_caballos = 0.0f;
bool activate_caballos = false;
int vueltas_caballos = 0;
float y_caballos = 5.5f;
bool up_caballos = false;
//-----------------------------------------------------


//-----para la rueda-----
float angRotPuerta = 0.0f;
float rotaRueda = 0.0f;
float	sol = 0.0f,
year = 0.0f,
day = 0.0f,
moon = 0.0f,
mars_year = 0.0f,
jupiter_year = 0.0f,
venus = 0.0f,
tierra = 0.00,
marte = 0.0f,
jupiter = 0.0f,
saturno = 0.0f,
urano = 0.0f,
neptuno = 0.0f;
float bandera = 0.2;
bool activate_rueda = false;
//------------------------

bool play = false;
bool direction_right = true;
bool direction_front = false;
bool stop = false;
bool regreso = false;

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

	unsigned char *data = stbi_load(filename, &width, &height, &nrChannels, 0);
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

int aleatorio(void) {
	int num;
	srand(time(0));
	num = rand() % 4;
	return num;
}

void getResolution()
{
	const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	SCR_WIDTH = mode->width;
	SCR_HEIGHT = (mode->height) - 80;

	lastX = SCR_WIDTH / 2.0f;
	lastY = SCR_HEIGHT / 2.0f;

}

void LoadTextures()
{
	t_unam = generateTextures("Texturas/escudo_unam.png", 1);
	t_caja_brillo = generateTextures("Texturas/caja_specular.png", 1);
	t_coaster = generateTextures("Texturas/bluemetal.jpg", 0);
	frontal = generateTextures("Texturas/frontal.jpg", 0);
	trasera = generateTextures("Texturas/trasera.jpg", 0);
	superior = generateTextures("Texturas/techo.jpg", 0);
	inferior = generateTextures("Texturas/suelo.jpg", 0);
	derecho = generateTextures("Texturas/derecha.jpg", 0);
	izquierdo = generateTextures("Texturas/izquierda.jpg", 0);
	brillo = generateTextures("Texturas/brillo.jpg", 0);
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




		//////Segunda caja

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

void accidente(bool *ac_c, float *x, float *y, float *z, float *rot_c, float *rot_c2) {
	if (*ac_c == true) {
		*x -= 4.0f;
		*rot_c += 20.0f;
		*rot_c2 -= 25.0f;
		*y -= 3.0f;
		*z += 1.5;
		aux_ac += 1;
	}
	if (aux_ac == 7) {
		*ac_c = false;
		aux_ac = 0;
	}
}

void choque(float *x1, float *y1, bool *stop1, bool *ac_c1, float *x2, float *y2, bool *stop2, bool *ac_c2, float *x3, float *y3, bool *stop3, bool *ac_c3) {
	if (((*x1 <= *x2 + 11 && *x1 >= *x2 - 11) && (*y1 <= *y2 + 13 && *y1 >= *y2 - 13))) {
		*stop1 = true;
		*stop2 = true;
		*ac_c1 = true;
		//*ac_c2 = true;
	}
	if (((*x1 <= *x3 + 11 && *x1 >= *x3 - 11) && (*y1 <= *y3 + 13 && *y1 >= *y3 - 13))) {
		*stop1 = true;
		*stop3 = true;
		*ac_c1 = true;
		//*ac_c3 = true;
	}
}


void animate_bumper(float *x, float *y, float *rot, int *estado_cart, int mov[], bool *stop, int *tiempo) {
	//int aux = 1;
	if (*stop == false) {
		*tiempo += 1;
		//estado_cart = aleatorio();
		if (*estado_cart == 0) {//movimiento hacia adelante
			*rot = 90.0f;
			if ((*x < 30.0f) && avanzar < 5) {
				*x += 4.0f;
				avanzar += 1;
			}
			if ((*x >= 30.0f) || avanzar == 5) {
				*estado_cart = mov[aux];
				avanzar = 0;
				aux += 1;
			}
		}
		if (*estado_cart == 1) {//movimiento hacia atras
			*rot = -90.0f;
			if ((*x > -30.0f) && avanzar < 5) {
				*x -= 4.0f;
				avanzar += 1;
			}
			if ((*x <= -30.0f) || avanzar == 5) {
				*estado_cart = mov[aux];
				avanzar = 0;
				aux += 1;
			}
		}
		if (*estado_cart == 2) {//movimiento izquierda
			*rot = 180.0f;
			if ((*y > -30.0f) && avanzar < 5) {
				*y -= 4.0f;
				avanzar += 1;
			}
			if ((*y <= -30.0f) || avanzar == 5) {
				*estado_cart = mov[aux];
				avanzar = 0;
				aux += 1;
			}
		}
		if (*estado_cart == 3) {//movimiento izquierda
			*rot = 0.0f;
			if ((*y < 30.0f) && avanzar < 5) {
				*y += 4.0f;
				avanzar += 1;
			}
			if ((*y >= 30.0f) || avanzar == 5) {
				*estado_cart = mov[aux];
				avanzar = 0;
				aux += 1;
			}
		}
		if (aux >= 19) {
			aux = 0;
		}
		if (*tiempo == 65) {
			*stop = true;
			*tiempo = 0;
		}
	}
}


void animate_cc(void) {
	if (activate_cc) {
		if (estado_cc == 0) {
			rot_comida = -90.0f;
			if (x_comida >= -30.0f) {
				x_comida -= 0.3f;
			}
			else {
				estado_cc = 1;
			}
		}
		if (estado_cc == 1) {
			rot_comida = 180.0f;
			if (z_comida >= -25) {
				z_comida -= 0.3f;
			}
			else {
				estado_cc = 2;
			}
		}
		if (estado_cc == 2) {
			rot_comida = -270;
			if (x_comida <= 25) {
				x_comida += 0.3;
			}
			else {
				estado_cc = 3;
			}
		}
		if (estado_cc == 3) {
			rot_comida = 0.0f;
			if (z_comida <= 23) {
				z_comida += 0.3;
			}
			else {
				estado_cc = 0;
			}
		}
	}
}


void animate_horse(void) {
	if (activate_caballos) {
		if (vueltas_caballos == 0 || vueltas_caballos == 4) {
			rot_caballos += 7.0f;
		}
		if (vueltas_caballos > 0 && vueltas_caballos < 4) {
			rot_caballos += 10.0f;
		}
		if (vueltas_caballos == 5) {
			activate_caballos = false;
			vueltas_caballos = 0;
		}
		if (rot_caballos > 360.0) {
			rot_caballos -= 360.0f;
			vueltas_caballos += 1;
		}
		if (y_caballos < 6.0f && up_caballos) {
			y_caballos += 0.3f;
			if (y_caballos >= 6.0f) {
				up_caballos = false;
			}
		}
		if (y_caballos > 4.0f && !up_caballos) {
			y_caballos -= 0.3f;
			if (y_caballos <= 4.4f) {
				up_caballos = true;
			}
		}
	}
}

void animated_tasas(void) {
	if (activate_tasas) {
		if (vueltas_tasas == 0 || vueltas_tasas == 6) {
			rot_base_tasas += 4.0f;
			rot_tasas += 6.0f;
		}
		if ((vueltas_tasas >= 1 && vueltas_tasas < 2) || (vueltas_tasas >= 5 && vueltas_tasas < 6)) {
			rot_base_tasas += 6.0f;
			rot_tasas += 8.0f;
		}
		if (vueltas_tasas >= 2 && vueltas_tasas <= 4) {
			rot_base_tasas += 10.0f;
			rot_tasas += 12.0f;
		}

		if (rot_base_tasas > 360.0) {
			rot_base_tasas -= 360.0f;
			vueltas_tasas += 1;
		}
		if (rot_tasas > 360.0) {
			rot_tasas -= 360.0f;
		}

		if (vueltas_tasas == 7) {
			activate_tasas = false;
			vueltas_tasas = 0;
		}
	}
}



//-------------------------animacion por keyframes----------------------------------------------

#define MAX_FRAMES 60 //numero maximo de keyframes se puede modificar
int i_max_steps = 7; //intervalo entre cvada uno de los keyframes (interpolacion)
int i_curr_steps = 0; //indice para saber en que keyframe estamos
typedef struct _frame //definicion de la estructura
{
	float x_coaster_cart;
	float xInc_coaster_cart;
	float y_coaster_cart;
	float yInc_coaster_cart;
	float z_coaster_cart;
	float zInc_coaster_cart;
	float rotx_coaster_cart;
	float rotxInc_coaster_cart;
	float roty_coaster_cart;
	float rotyInc_coaster_cart;
	float rotz_coaster_cart;
	float rotzInc_coaster_cart;

}FRAME;

FRAME KeyFrame[MAX_FRAMES];
int FrameIndex = 0;			//introducir datos
//bool play = false;
int playIndex = 0;


void saveFrame(void) //pasa los datos a la estructura
{

	printf("frameindex %d\n", FrameIndex);
	printf("x %f ", x_coaster_cart);
	printf("y %f ", y_coaster_cart);
	printf("z %f ", z_coaster_cart);
	printf("angx %f ", rotx_coaster_cart);
	printf("angy %f ", roty_coaster_cart);
	printf("angz %f\n ", rotz_coaster_cart);

	KeyFrame[FrameIndex].x_coaster_cart = x_coaster_cart; //pasa las posiciones por cada estado (guarda el estado del monito)
	KeyFrame[FrameIndex].y_coaster_cart = y_coaster_cart;
	KeyFrame[FrameIndex].z_coaster_cart = z_coaster_cart;

	KeyFrame[FrameIndex].rotx_coaster_cart = rotx_coaster_cart;
	KeyFrame[FrameIndex].roty_coaster_cart = roty_coaster_cart;
	KeyFrame[FrameIndex].rotz_coaster_cart = rotz_coaster_cart;

	FrameIndex++;
}



void setFrame(void) {
	FILE * frames;
	errno_t err;
	if((err = fopen_s(&frames, "list_frames.txt", "rb")) != 0){
		perror("Error al intentar abrir el archivor");
	}
	else {
		while (feof(frames) == 0) {
			fscanf_s(frames, "%f%f%f%f%f%f", &KeyFrame[FrameIndex].x_coaster_cart, &KeyFrame[FrameIndex].y_coaster_cart, &KeyFrame[FrameIndex].z_coaster_cart, &KeyFrame[FrameIndex].rotx_coaster_cart,
				&KeyFrame[FrameIndex].roty_coaster_cart, &KeyFrame[FrameIndex].rotz_coaster_cart);
			//printf("frameindex %d\n", FrameIndex);//primera parte
			FrameIndex++;
		}
	}
	
	fclose(frames);
	//printf("archivo leido correctamente...\n");
}




void resetElements(void)//coloca la animacion al inicio
{
	x_coaster_cart = KeyFrame[0].x_coaster_cart;
	y_coaster_cart = KeyFrame[0].y_coaster_cart;
	z_coaster_cart = KeyFrame[0].z_coaster_cart;

	rotx_coaster_cart = KeyFrame[0].rotx_coaster_cart;
	roty_coaster_cart = KeyFrame[0].roty_coaster_cart;
	rotz_coaster_cart = KeyFrame[0].rotz_coaster_cart;
}

void interpolation(void)//interpolacion entre keyframes
{

	KeyFrame[playIndex].xInc_coaster_cart = (KeyFrame[playIndex + 1].x_coaster_cart - KeyFrame[playIndex].x_coaster_cart) / i_max_steps;//se divide entre el numero de frames intermedios
	KeyFrame[playIndex].yInc_coaster_cart = (KeyFrame[playIndex + 1].y_coaster_cart - KeyFrame[playIndex].y_coaster_cart) / i_max_steps;
	KeyFrame[playIndex].zInc_coaster_cart = (KeyFrame[playIndex + 1].z_coaster_cart - KeyFrame[playIndex].z_coaster_cart) / i_max_steps;

	KeyFrame[playIndex].rotxInc_coaster_cart = (KeyFrame[playIndex + 1].rotx_coaster_cart - KeyFrame[playIndex].rotx_coaster_cart) / i_max_steps;
	KeyFrame[playIndex].rotyInc_coaster_cart = (KeyFrame[playIndex + 1].roty_coaster_cart - KeyFrame[playIndex].roty_coaster_cart) / i_max_steps;
	KeyFrame[playIndex].rotzInc_coaster_cart = (KeyFrame[playIndex + 1].rotz_coaster_cart - KeyFrame[playIndex].rotz_coaster_cart) / i_max_steps;

}

void animate_coaster(void) {
	if (activate_coaster) {
		if (i_curr_steps >= i_max_steps) //end of animation between frames?
		{
			playIndex++;
			if (playIndex > FrameIndex - 2)	//end of total animation?
			{
				printf("termina anim\n");
				playIndex = 0;
				activate_coaster = false;
			}
			else //Next frame interpolations
			{
				i_curr_steps = 0; //Reset counter
								  //Interpolation
				interpolation();
			}
		}
		else
		{
			//Draw animation
			x_coaster_cart += KeyFrame[playIndex].xInc_coaster_cart;//paso actual mas el paso siguiente
			y_coaster_cart += KeyFrame[playIndex].yInc_coaster_cart;
			z_coaster_cart += KeyFrame[playIndex].zInc_coaster_cart;

			rotx_coaster_cart += KeyFrame[playIndex].rotxInc_coaster_cart;
			roty_coaster_cart += KeyFrame[playIndex].rotyInc_coaster_cart;
			rotz_coaster_cart += KeyFrame[playIndex].rotzInc_coaster_cart;

			i_curr_steps++;
		}
	}
}


//rueda de la fortuna
void animate(void)
{
	if (activate_rueda) {
		sol += 0.1f;
		rotaRueda += 0.4f;
		venus += 0.35f;
		tierra += 0.3f;
		marte += 0.25f;
		jupiter += 0.2f;
		saturno += 0.15f;
		urano += 0.1f;
		neptuno += 0.05f;

		angRotPuerta = angRotPuerta + bandera;
		if (angRotPuerta >= 0)
		{
			bandera = -0.5;
		}
		if (angRotPuerta <= -45)
		{
			bandera = 0.5;
		}
	}
}

//------------------------------------------animacion por keyframes-------------------------------------------------------------

void display(Shader shader, Shader lampshader, Shader lightingshader, Shader textureshader, Shader lightposshader,
	Model carril, Model personaje, Model personaje2, Model futbolito, Model carpa_tasas, Model base_tasas, Model tasa, Model basketball, Model tiro_blanco,
	Model jugos, Model ambulante1, Model barrera, Model carpa_fut, Model bumper_car, Model pista, Model silla, Model trash, Model trash2, Model poste_luz1, Model arbol1, Model premios,
	Model toilet, Model base_caballos, Model giro_caballos, Model caballo, Model coaster_cart)//ahora si resiven parametros: shader, carril y personaje
{
	//lightingshader.use();
	//Shader lightingshader("shaders/shader_texture_light_spot.vs", "shaders/shader_texture_light_spot.fs"); //Spotlight(luz de reflector)
	lightingshader.use();

	// create transformations and Projection
	glm::mat4 tmp = glm::mat4(1.0f);
	glm::mat4 tmp_carros = glm::mat4(1.0f);
	glm::mat4 temp2 = glm::mat4(1.0f);
	glm::mat4 model = glm::mat4(1.0f);		// initialize Matrix, Use this matrix for individual models
	glm::mat4 modeltemp = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);		//Use this matrix for ALL models
	glm::mat4 projection = glm::mat4(1.0f);	//This matrix is for Projection




	//modelos
	shader.use();


	projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 500.0f);
	view = camera.GetViewMatrix();


	model = glm::mat4(1.0f);
	shader.setMat4("projection", projection);
	shader.setMat4("view", view);

	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	tmp = model = glm::translate(model, glm::vec3(15.0f, -10.0f, 0.0f));
	model = glm::scale(model, glm::vec3(0.06f, 0.060f, 0.06f));
	shader.setMat4("model", model);
	carril.Draw(shader);//dibuja el parque


	//--------------------barrera para montaña rusa-----------------------------
	model = glm::translate(tmp, glm::vec3(35.0f, 5.65f, -30.0));
	model = glm::scale(model, glm::vec3(0.4f, 0.2f, 0.5f));
	model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	//model = glm::rotate(model, glm::radians(rot_llanta), glm::vec3(1.0f, 0.0f, 0.0f));
	shader.setMat4("model", model);
	barrera.Draw(shader);

	model = glm::translate(model, glm::vec3(-11.4f, 0.0f, 0.0));
	shader.setMat4("model", model);
	barrera.Draw(shader);

	model = glm::translate(model, glm::vec3(22.8f, 0.0f, 0.0));
	shader.setMat4("model", model);
	barrera.Draw(shader);

	model = glm::translate(model, glm::vec3(11.4f, 0.0f, 0.0));
	shader.setMat4("model", model);
	barrera.Draw(shader);

	model = glm::translate(model, glm::vec3(11.4f, 0.0f, 0.0));
	shader.setMat4("model", model);
	barrera.Draw(shader);

	model = glm::translate(model, glm::vec3(11.4f, 0.0f, 0.0));
	shader.setMat4("model", model);
	barrera.Draw(shader);

	model = glm::translate(model, glm::vec3(11.4f, 0.0f, 0.0));
	shader.setMat4("model", model);
	barrera.Draw(shader);

	model = glm::translate(model, glm::vec3(11.4f, 0.0f, 0.0));
	shader.setMat4("model", model);
	barrera.Draw(shader);

	model = glm::translate(model, glm::vec3(11.4f, 0.0f, 0.0));
	shader.setMat4("model", model);
	barrera.Draw(shader);

	model = glm::translate(model, glm::vec3(11.4f, 0.0f, 0.0));
	shader.setMat4("model", model);
	barrera.Draw(shader);

	model = glm::translate(model, glm::vec3(11.4f, 0.0f, 0.0));
	shader.setMat4("model", model);
	barrera.Draw(shader);

	model = glm::translate(model, glm::vec3(11.4f, 0.0f, 0.0));
	shader.setMat4("model", model);
	barrera.Draw(shader);

	model = glm::translate(model, glm::vec3(11.4f, 0.0f, 0.0));
	shader.setMat4("model", model);
	barrera.Draw(shader);

	model = glm::translate(model, glm::vec3(11.4f, 0.0f, 0.0));
	shader.setMat4("model", model);
	barrera.Draw(shader);

	model = glm::translate(model, glm::vec3(6.5f, 0.0f, -5.1));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	shader.setMat4("model", model);
	barrera.Draw(shader);

	model = glm::translate(model, glm::vec3(11.4f, 0.0f, 0.0));
	shader.setMat4("model", model);
	barrera.Draw(shader);

	model = glm::translate(model, glm::vec3(11.4f, 0.0f, 0.0));
	shader.setMat4("model", model);
	barrera.Draw(shader);

	model = glm::translate(model, glm::vec3(11.4f, 0.0f, 0.0));
	shader.setMat4("model", model);
	barrera.Draw(shader);

	model = glm::translate(model, glm::vec3(11.4f, 0.0f, 0.0));
	shader.setMat4("model", model);
	barrera.Draw(shader);

	model = glm::translate(model, glm::vec3(11.4f, 0.0f, 0.0));
	shader.setMat4("model", model);
	barrera.Draw(shader);

	model = glm::translate(model, glm::vec3(11.4f, 0.0f, 0.0));
	shader.setMat4("model", model);
	barrera.Draw(shader);

	model = glm::translate(model, glm::vec3(11.4f, 0.0f, 0.0));
	shader.setMat4("model", model);
	barrera.Draw(shader);

	model = glm::translate(model, glm::vec3(6.5f, 0.0f, -5.1));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	shader.setMat4("model", model);
	barrera.Draw(shader);

	model = glm::translate(model, glm::vec3(11.4f, 0.0f, 0.0));
	shader.setMat4("model", model);
	barrera.Draw(shader);

	model = glm::translate(model, glm::vec3(11.4f, 0.0f, 0.0));
	shader.setMat4("model", model);
	barrera.Draw(shader);

	model = glm::translate(model, glm::vec3(11.4f, 0.0f, 0.0));
	shader.setMat4("model", model);
	barrera.Draw(shader);

	model = glm::translate(model, glm::vec3(11.4f, 0.0f, 0.0));
	shader.setMat4("model", model);
	barrera.Draw(shader);

	model = glm::translate(model, glm::vec3(11.4f, 0.0f, 0.0));
	shader.setMat4("model", model);
	barrera.Draw(shader);

	model = glm::translate(model, glm::vec3(11.4f, 0.0f, 0.0));
	shader.setMat4("model", model);
	barrera.Draw(shader);

	model = glm::translate(model, glm::vec3(11.4f, 0.0f, 0.0));
	shader.setMat4("model", model);
	barrera.Draw(shader);

	model = glm::translate(model, glm::vec3(11.4f, 0.0f, 0.0));
	shader.setMat4("model", model);
	barrera.Draw(shader);

	model = glm::translate(model, glm::vec3(11.4f, 0.0f, 0.0));
	shader.setMat4("model", model);
	barrera.Draw(shader);

	model = glm::translate(model, glm::vec3(11.4f, 0.0f, 0.0));
	shader.setMat4("model", model);
	barrera.Draw(shader);

	model = glm::translate(model, glm::vec3(11.4f, 0.0f, 0.0));
	shader.setMat4("model", model);
	barrera.Draw(shader);

	model = glm::translate(model, glm::vec3(11.4f, 0.0f, 0.0));
	shader.setMat4("model", model);
	barrera.Draw(shader);

	model = glm::translate(model, glm::vec3(11.4f, 0.0f, 0.0));
	shader.setMat4("model", model);
	barrera.Draw(shader);

	model = glm::translate(model, glm::vec3(6.5f, 0.0f, -5.1));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	shader.setMat4("model", model);
	barrera.Draw(shader);

	model = glm::translate(model, glm::vec3(11.4f, 0.0f, 0.0));
	shader.setMat4("model", model);
	barrera.Draw(shader);

	model = glm::translate(model, glm::vec3(11.4f, 0.0f, 0.0));
	shader.setMat4("model", model);
	barrera.Draw(shader);

	model = glm::translate(model, glm::vec3(11.4f, 0.0f, 0.0));
	shader.setMat4("model", model);
	barrera.Draw(shader);

	model = glm::translate(model, glm::vec3(11.4f, 0.0f, 0.0));
	shader.setMat4("model", model);
	barrera.Draw(shader);

	model = glm::translate(model, glm::vec3(34.2f, 0.0f, 0.0));
	shader.setMat4("model", model);
	barrera.Draw(shader);

	//----------------------------------------------------------------------------

	//personaje1
	model = glm::translate(tmp, glm::vec3(-30.0f, 5.68f, 0.0));
	model = glm::scale(model, glm::vec3(0.015f, 0.015f, 0.015f));
	//model = glm::rotate(model, glm::radians(rot_personaje), glm::vec3(0.0f, 1.0f, 0.0f));

	//model = glm::rotate(model, glm::radians(rot_llanta), glm::vec3(1.0f, 0.0f, 0.0f));
	shader.setMat4("model", model);
	personaje.Draw(shader);	//Izq delantera

	//personaje 2
	model = glm::translate(tmp, glm::vec3(-10.0f, 5.68f, 40.0));
	model = glm::scale(model, glm::vec3(0.015f, 0.015f, 0.015f));
	//model = glm::rotate(model, glm::radians(rot_personaje), glm::vec3(0.0f, 1.0f, 0.0f));

	//model = glm::rotate(model, glm::radians(rot_llanta), glm::vec3(1.0f, 0.0f, 0.0f));
	shader.setMat4("model", model);
	personaje2.Draw(shader);



	model = glm::translate(tmp, glm::vec3(30.0f, 5.68f, -20.0));
	model = glm::scale(model, glm::vec3(0.015f, 0.015f, 0.015f));
	//model = glm::rotate(model, glm::radians(rot_personaje), glm::vec3(0.0f, 1.0f, 0.0f));

	//model = glm::rotate(model, glm::radians(rot_llanta), glm::vec3(1.0f, 0.0f, 0.0f));
	shader.setMat4("model", model);
	personaje2.Draw(shader);

	/*
	//personaje con movimiento
	model = glm::translate(tmp, glm::vec3(x_personaje, y_personaje, z_personaje));
	model = glm::scale(model, glm::vec3(0.015f, 0.015f, 0.015f));
	model = glm::rotate(model, glm::radians(rot_personaje), glm::vec3(0.0f, 1.0f, 0.0f));

	//model = glm::rotate(model, glm::radians(rot_llanta), glm::vec3(1.0f, 0.0f, 0.0f));
	shader.setMat4("model", model);
	cuerpo.Draw(shader);
	temp2 = model;

	//Pierna Der
	model = glm::translate(model, glm::vec3(-0.0f, 63.0f, -0.0f));
	model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0));
	model = glm::rotate(model, glm::radians(rot_piernaDer), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::translate(model, glm::vec3(0.0f, -60.1f, 0.0f));
	//model = glm::scale(model, glm::vec3(50000.007f, 50000.007f, 50000.007f));
	shader.setMat4("model", model);
	musloDer.Draw(shader);


	model = temp2;
	//Pierna Izq
	model = glm::translate(model, glm::vec3(0.0f, 63.0f, -0.0f));
	model = glm::rotate(model, glm::radians(rot_piernaIzq), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::translate(model, glm::vec3(0.0f, -60.05f, 0.0f));
	shader.setMat4("model", model);
	musloIzq.Draw(shader);
	*/

	//futbolitos
	//-----------------------------------futbolitos-------------------------------------
	//carpa
	model = glm::translate(tmp, glm::vec3(-50.0f, 5.45f, -25.0));
	model = glm::scale(model, glm::vec3(0.09f, 0.09f, 0.09f));
	model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	shader.setMat4("model", model);
	carpa_fut.Draw(shader);
	//-

	model = glm::translate(model, glm::vec3(70.0f, 2.0f, 30.0));
	model = glm::scale(model, glm::vec3(17.0f, 17.0f, 17.0f));
	model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	//model = glm::rotate(model, glm::radians(rot_llanta), glm::vec3(1.0f, 0.0f, 0.0f));
	shader.setMat4("model", model);
	futbolito.Draw(shader);	//

	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 3.5));
	shader.setMat4("model", model);
	futbolito.Draw(shader);	//

	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 3.5));
	shader.setMat4("model", model);
	futbolito.Draw(shader);

	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 3.5));
	shader.setMat4("model", model);
	futbolito.Draw(shader);

	model = glm::translate(model, glm::vec3(-3.0f, 0.0f, 0.0));
	shader.setMat4("model", model);
	futbolito.Draw(shader);

	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -3.5));
	shader.setMat4("model", model);
	futbolito.Draw(shader);

	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -3.5));
	shader.setMat4("model", model);
	futbolito.Draw(shader);

	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -3.5));
	shader.setMat4("model", model);
	futbolito.Draw(shader);

	//----------------------futbolitos-----------------------------------

	//---------------------tasas giratorias------------------------------
	model = glm::translate(tmp, glm::vec3(10.0f, 5.7f, -40.0));
	model = glm::scale(model, glm::vec3(0.9f, 0.8f, 0.9f));
	//model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	shader.setMat4("model", model);
	carpa_tasas.Draw(shader);

	model = glm::translate(model, glm::vec3(0.0f, 0.05f, 0.0f));
	model = glm::rotate(model, glm::radians(rot_base_tasas), glm::vec3(0.0f, 1.0f, 0.0f)); //para el movimiento de todas las tasas
	shader.setMat4("model", model);
	temp2 = model;
	base_tasas.Draw(shader);

	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -5.5));
	model = glm::rotate(model, glm::radians(rot_tasas), glm::vec3(0.0f, 1.0f, 0.0f));//para rotar la tasa
	shader.setMat4("model", model);
	tasa.Draw(shader);

	model = temp2;
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 5.5));
	model = glm::rotate(model, glm::radians(rot_tasas), glm::vec3(0.0f, 1.0f, 0.0f));//para rotar la tasa
	shader.setMat4("model", model);
	tasa.Draw(shader);

	model = temp2;
	model = glm::translate(model, glm::vec3(5.5f, 0.0f, 0.0));
	model = glm::rotate(model, glm::radians(rot_tasas), glm::vec3(0.0f, 1.0f, 0.0f));//para rotar la tasa
	shader.setMat4("model", model);
	tasa.Draw(shader);

	model = temp2;
	model = glm::translate(model, glm::vec3(-5.5f, 0.0f, 0.0));
	model = glm::rotate(model, glm::radians(rot_tasas), glm::vec3(0.0f, 1.0f, 0.0f));//para rotar la tasa
	shader.setMat4("model", model);
	tasa.Draw(shader);

	//----------------------------tasas giratorias---------------------------------------------

	//----------------------------basketball---------------------------------------------
	model = glm::translate(tmp, glm::vec3(-48.0f, 5.5f, 27.0));
	model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
	model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	shader.setMat4("model", model);
	basketball.Draw(shader);

	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 15.0));
	shader.setMat4("model", model);
	basketball.Draw(shader);

	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 15.0));
	shader.setMat4("model", model);
	basketball.Draw(shader);

	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 15.0));
	shader.setMat4("model", model);
	basketball.Draw(shader);

	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 15.0));
	shader.setMat4("model", model);
	basketball.Draw(shader);

	model = glm::translate(model, glm::vec3(-10.0f, 0.0f, 0.0));
	model = glm::rotate(model, glm::radians(-180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	shader.setMat4("model", model);
	basketball.Draw(shader);

	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 15.0));
	shader.setMat4("model", model);
	basketball.Draw(shader);

	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 15.0));
	shader.setMat4("model", model);
	basketball.Draw(shader);

	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 15.0));
	shader.setMat4("model", model);
	basketball.Draw(shader);

	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 15.0));
	shader.setMat4("model", model);
	basketball.Draw(shader);

	//--------------------basketball ------------------------------------

	//-----------------------tiro al blanco------------------------------
	//carpa
	model = glm::translate(tmp, glm::vec3(-45.0f, 5.45f, 43.0));
	model = glm::scale(model, glm::vec3(0.08f, 0.09f, 0.07f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	shader.setMat4("model", model);
	temp2 = model;
	carpa_fut.Draw(shader);

	//-

	model = glm::translate(model, glm::vec3(80.0f, 2.5f, -50.0));
	model = glm::scale(model, glm::vec3(1.20f, 0.9f, 0.90f));
	//model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	shader.setMat4("model", model);
	tiro_blanco.Draw(shader);

	model = glm::translate(model, glm::vec3(-30.0f, 0.0f, 0.0));
	shader.setMat4("model", model);
	tiro_blanco.Draw(shader);

	model = glm::translate(model, glm::vec3(-30.0f, 0.0f, 0.0));
	shader.setMat4("model", model);
	tiro_blanco.Draw(shader);

	model = glm::translate(model, glm::vec3(-30.0f, 0.0f, 0.0));
	shader.setMat4("model", model);
	tiro_blanco.Draw(shader);

	model = glm::translate(model, glm::vec3(-30.0f, 0.0f, 0.0));
	shader.setMat4("model", model);
	tiro_blanco.Draw(shader);

	model = glm::translate(model, glm::vec3(-30.0f, 0.0f, 0.0));
	shader.setMat4("model", model);
	tiro_blanco.Draw(shader);

	//premios 
	model = temp2;
	model = glm::translate(model, glm::vec3(-140.0f, 2.5f, -30.0));
	model = glm::scale(model, glm::vec3(3.00f, 4.0f, 4.00f));
	//model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	shader.setMat4("model", model);
	premios.Draw(shader);

	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 8.0));
	shader.setMat4("model", model);
	premios.Draw(shader);

	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 8.0));
	shader.setMat4("model", model);
	premios.Draw(shader);

	model = temp2;
	model = glm::translate(model, glm::vec3(100.0f, 2.5f, -30.0));
	model = glm::scale(model, glm::vec3(3.00f, 4.0f, 4.00f));
	model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	shader.setMat4("model", model);
	premios.Draw(shader);

	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -8.0));
	shader.setMat4("model", model);
	premios.Draw(shader);

	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -8.0));
	shader.setMat4("model", model);
	premios.Draw(shader);
	//--------------------------------------------------------------------


	//-------------------carros chocones----------------------------------
	model = glm::translate(tmp, glm::vec3(10.0f, 5.7f, 45.0));
	model = glm::scale(model, glm::vec3(0.3f, 0.1f, 0.3f));
	//model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	shader.setMat4("model", model);
	pista.Draw(shader);
	tmp_carros = model;
	//bumper_car.Draw(shader);

	model = glm::translate(model, glm::vec3(x_cart, z_cart, y_cart));//carro1
	model = glm::scale(model, glm::vec3(0.4f, 0.8f, 0.4f));
	model = glm::rotate(model, glm::radians(rot_cart), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(rot_cart_z), glm::vec3(0.0f, 0.0f, 1.0f));
	shader.setMat4("model", model);
	bumper_car.Draw(shader);

	model = tmp_carros;
	model = glm::translate(model, glm::vec3(x_cart3, y_cart3, z_cart3));//carro 3
	model = glm::scale(model, glm::vec3(0.4f, 0.8f, 0.4f));
	model = glm::rotate(model, glm::radians(rot_cart3), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(rot_cart3_z), glm::vec3(0.0f, 0.0f, 1.0f));
	shader.setMat4("model", model);
	bumper_car.Draw(shader);

	model = tmp_carros;
	model = glm::translate(model, glm::vec3(x_cart2, y_cart2, z_cart2));//carro2
	model = glm::scale(model, glm::vec3(0.4f, 0.8f, 0.4f));
	model = glm::rotate(model, glm::radians(rot_cart2), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(rot_cart2_z), glm::vec3(0.0f, 0.0f, 1.0f));
	shader.setMat4("model", model);
	bumper_car.Draw(shader);
	//--------------------------------------------------------------------

	//------------------ comida -------------------------------

	//jugos
	model = glm::translate(tmp, glm::vec3(x_comida, 5.6f, z_comida));
	model = glm::scale(model, glm::vec3(0.80f, 0.80f, 0.80f));
	model = glm::rotate(model, glm::radians(rot_comida), glm::vec3(0.0f, 1.0f, 0.0f));
	//model = glm::rotate(model, glm::radians(rot_llanta), glm::vec3(1.0f, 0.0f, 0.0f));
	shader.setMat4("model", model);
	jugos.Draw(shader);


	//------------------ comida --------------------------------

	//-----------------------carro montaña rusa---------------------------------------------------------------
	model = glm::translate(tmp, glm::vec3(x_coaster_cart, y_coaster_cart, z_coaster_cart));
	model = glm::scale(model, glm::vec3(0.50f, 0.50f, 0.50f));
	model = glm::rotate(model, glm::radians(rotx_coaster_cart), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(roty_coaster_cart), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(rotz_coaster_cart), glm::vec3(0.0f, 0.0f, 1.0f));
	//model = glm::rotate(model, glm::radians(rot_llanta), glm::vec3(1.0f, 0.0f, 0.0f));
	shader.setMat4("model", model);
	coaster_cart.Draw(shader);
	//--------------------------------------------------------------------------------------------------------
	
	//------------------------------------caballos------------------------------------------------------------------
	model = glm::translate(tmp, glm::vec3(-20.0f, 5.6f, 45.0f));
	model = glm::scale(model, glm::vec3(0.30f, 0.30f, 0.30f));
	//model = glm::rotate(model, glm::radians(rot_llanta), glm::vec3(1.0f, 0.0f, 0.0f));
	shader.setMat4("model", model);
	base_caballos.Draw(shader);

	model = glm::translate(model, glm::vec3(0, -3.5f, 0.0));
	model = glm::scale(model, glm::vec3(1.0f, 1.15f, 1.0f));
	model = glm::rotate(model, glm::radians(rot_caballos), glm::vec3(0.0f, 1.0f, 0.0f));
	shader.setMat4("model", model);
	temp2 = model;
	giro_caballos.Draw(shader);

	model = glm::translate(model, glm::vec3(18.0f, y_caballos, 0.0));
	model = glm::scale(model, glm::vec3(1.1f, 1.1f, 1.0f));
	model = glm::rotate(model, glm::radians(40.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	shader.setMat4("model", model);
	caballo.Draw(shader);

	model = temp2;
	model = glm::translate(model, glm::vec3(-18.0f, y_caballos, 0.0));
	model = glm::scale(model, glm::vec3(1.1f, 1.1f, 1.0f));
	model = glm::rotate(model, glm::radians(220.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	shader.setMat4("model", model);
	caballo.Draw(shader);

	model = temp2;
	model = glm::translate(model, glm::vec3(0.0f, y_caballos, 18.0));
	model = glm::scale(model, glm::vec3(1.1f, 1.1f, 1.0f));
	model = glm::rotate(model, glm::radians(-40.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	shader.setMat4("model", model);
	caballo.Draw(shader);

	model = temp2;
	model = glm::translate(model, glm::vec3(0.0f, y_caballos, -18.0));
	model = glm::scale(model, glm::vec3(1.1f, 1.1f, 1.0f));
	model = glm::rotate(model, glm::radians(-220.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	shader.setMat4("model", model);
	caballo.Draw(shader);
	
	//------------------elementos clasicos---------------------------
	//sillas
	model = glm::translate(tmp, glm::vec3(-24.0f, 5.67f, 10.0));
	model = glm::scale(model, glm::vec3(0.017f, 0.0140f, 0.017f));
	model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	//model = glm::rotate(model, glm::radians(rot_llanta), glm::vec3(1.0f, 0.0f, 0.0f));
	shader.setMat4("model", model);
	silla.Draw(shader);

	model = glm::translate(tmp, glm::vec3(-23.0f, 5.67f, 13.0));
	model = glm::scale(model, glm::vec3(0.017f, 0.0140f, 0.017f));
	shader.setMat4("model", model);
	trash.Draw(shader); //bote de basura

	model = glm::translate(tmp, glm::vec3(-24.0f, 5.67f, 5.0));
	model = glm::scale(model, glm::vec3(0.017f, 0.0140f, 0.017f));
	model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	shader.setMat4("model", model);
	silla.Draw(shader);

	model = glm::translate(tmp, glm::vec3(-23.0f, 5.67f, 2.0f));
	model = glm::scale(model, glm::vec3(0.017f, 0.0140f, 0.017f));
	shader.setMat4("model", model);
	trash.Draw(shader);//bote de basura

	model = glm::translate(tmp, glm::vec3(-24.0f, 5.67f, -7.0));
	model = glm::scale(model, glm::vec3(0.017f, 0.0140f, 0.017f));
	model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	shader.setMat4("model", model);
	silla.Draw(shader);

	//atras de la fuente
	model = glm::translate(tmp, glm::vec3(19.0f, 5.67f, -12.0));
	model = glm::scale(model, glm::vec3(0.017f, 0.0140f, 0.017f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	shader.setMat4("model", model);
	silla.Draw(shader);

	model = glm::translate(tmp, glm::vec3(18.0f, 5.67f, -15.0));
	model = glm::scale(model, glm::vec3(0.017f, 0.0140f, 0.017f));
	shader.setMat4("model", model);
	trash.Draw(shader);//bote de basura

	model = glm::translate(tmp, glm::vec3(19.0f, 5.67f, -7.0));
	model = glm::scale(model, glm::vec3(0.017f, 0.0140f, 0.017f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	shader.setMat4("model", model);
	silla.Draw(shader);

	model = glm::translate(tmp, glm::vec3(18.0f, 5.67f, -4.0));
	model = glm::scale(model, glm::vec3(0.017f, 0.0140f, 0.017f));
	shader.setMat4("model", model);
	trash.Draw(shader);//bote de basura

	//izquierda de la fuente
	model = glm::translate(tmp, glm::vec3(11.0f, 5.67f, -19.0));
	model = glm::scale(model, glm::vec3(0.017f, 0.0140f, 0.017f));
	model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	shader.setMat4("model", model);
	silla.Draw(shader);

	model = glm::translate(tmp, glm::vec3(14.0f, 5.67f, -18.0));
	model = glm::scale(model, glm::vec3(0.017f, 0.0140f, 0.017f));
	shader.setMat4("model", model);
	trash.Draw(shader);//bote de basura

	model = glm::translate(tmp, glm::vec3(6.0f, 5.67f, -19.0));
	model = glm::scale(model, glm::vec3(0.017f, 0.0140f, 0.017f));
	model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	shader.setMat4("model", model);
	silla.Draw(shader);

	model = glm::translate(tmp, glm::vec3(3.0f, 5.67f, -18.0));
	model = glm::scale(model, glm::vec3(0.017f, 0.0140f, 0.017f));
	shader.setMat4("model", model);
	trash.Draw(shader);//bote de basura

	model = glm::translate(tmp, glm::vec3(-9.0f, 5.67f, -19.0));
	model = glm::scale(model, glm::vec3(0.017f, 0.0140f, 0.017f));
	model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	shader.setMat4("model", model);
	silla.Draw(shader);

	model = glm::translate(tmp, glm::vec3(-6.0f, 5.67f, -18.0));
	model = glm::scale(model, glm::vec3(0.017f, 0.0140f, 0.017f));
	shader.setMat4("model", model);
	trash.Draw(shader);//bote de basura

	model = glm::translate(tmp, glm::vec3(-14.0f, 5.67f, -19.0));
	model = glm::scale(model, glm::vec3(0.017f, 0.0140f, 0.017f));
	model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	shader.setMat4("model", model);
	silla.Draw(shader);

	model = glm::translate(tmp, glm::vec3(-17.0f, 5.67f, -18.0));
	model = glm::scale(model, glm::vec3(0.017f, 0.0140f, 0.017f));
	shader.setMat4("model", model);
	trash.Draw(shader);//bote de basura

	//derecha
	model = glm::translate(tmp, glm::vec3(-7.0f, 5.67f, 17.0));
	model = glm::scale(model, glm::vec3(0.017f, 0.0140f, 0.017f));
	shader.setMat4("model", model);
	silla.Draw(shader);

	model = glm::translate(tmp, glm::vec3(-4.0f, 5.67f, 16.0));
	model = glm::scale(model, glm::vec3(0.017f, 0.0140f, 0.017f));
	shader.setMat4("model", model);
	trash.Draw(shader);//bote de basura

	model = glm::translate(tmp, glm::vec3(-12.0f, 5.67f, 17.0));
	model = glm::scale(model, glm::vec3(0.017f, 0.0140f, 0.017f));
	shader.setMat4("model", model);
	silla.Draw(shader);

	model = glm::translate(tmp, glm::vec3(-15.0f, 5.67f, 16.0));
	model = glm::scale(model, glm::vec3(0.017f, 0.0140f, 0.017f));
	shader.setMat4("model", model);
	trash.Draw(shader);//bote de basura

	//botes de basura
	model = glm::translate(tmp, glm::vec3(-23.0f, 5.67f, -13.0));
	model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	shader.setMat4("model", model);
	trash2.Draw(shader);//bote de basura

	model = glm::translate(tmp, glm::vec3(-23.0f, 5.67f, -14.5));
	model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	shader.setMat4("model", model);
	trash2.Draw(shader);//bote de basura

	model = glm::translate(tmp, glm::vec3(-23.0f, 5.67f, -16.0));
	model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	shader.setMat4("model", model);
	trash2.Draw(shader);//bote de basura


	model = glm::translate(tmp, glm::vec3(15.0f, 5.67f, 7.0));
	model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
	model = glm::rotate(model, glm::radians(40.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	shader.setMat4("model", model);
	trash2.Draw(shader);//bote de basura

	model = glm::translate(tmp, glm::vec3(12.0f, 5.67f, 10.0));
	model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
	model = glm::rotate(model, glm::radians(40.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	shader.setMat4("model", model);
	trash2.Draw(shader);//bote de basura

	//--------------

	//------------------------arboles------------------------------------
	model = glm::translate(tmp, glm::vec3(-3.0f, 5.7f, -20.0)); // a la derecha de las canastas
	model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
	model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	shader.setMat4("model", model);
	arbol1.Draw(shader);//arbol grande

	model = glm::translate(tmp, glm::vec3(10.0f, 5.7f, 12.0)); // a la derecha de las canastas
	model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
	model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	shader.setMat4("model", model);
	arbol1.Draw(shader);//arbol grande

	model = glm::translate(tmp, glm::vec3(-45.0f, 5.7f, 60.0)); // a lado de los dardos
	model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
	model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	shader.setMat4("model", model);
	arbol1.Draw(shader);//arbol grande

	model = glm::translate(tmp, glm::vec3(-5.0f, 5.7f, 60.0)); // a la derecha de las canastas
	model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
	model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	shader.setMat4("model", model);
	arbol1.Draw(shader);//arbol grande

	model = glm::translate(tmp, glm::vec3(-72.0f, 5.7f, -37.0)); // a la izquierda de los baños
	model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
	model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	shader.setMat4("model", model);
	arbol1.Draw(shader);//arbol grande

	model = glm::translate(tmp, glm::vec3(-55.0f, 5.7f, 5.0)); // izquierda de las canastas
	model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
	model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	shader.setMat4("model", model);
	arbol1.Draw(shader);//arbol grande

	model = glm::translate(tmp, glm::vec3(20.0f, 5.7f, -50.0)); // a lado de las tasas
	model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
	model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	shader.setMat4("model", model);
	arbol1.Draw(shader);//arbol grande
	//------------------------arboles-------------------------------------
	//----------------------------------

	//-------------------------------poste de luz--------------------------------------------
	model = glm::translate(tmp, glm::vec3(-40.0f, 5.68f, 32.0)); // a la derecha de las canastas
	model = glm::scale(model, glm::vec3(0.02f, 0.02f, 0.02f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	shader.setMat4("model", model);
	poste_luz1.Draw(shader);

	model = glm::translate(tmp, glm::vec3(-60.0f, 5.68f, -10.0)); // al inicio del todo xD
	model = glm::scale(model, glm::vec3(0.02f, 0.02f, 0.02f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	shader.setMat4("model", model);
	poste_luz1.Draw(shader);

	model = glm::translate(tmp, glm::vec3(-40.0f, 5.68f, 5.0)); // al inicio del todo xD
	model = glm::scale(model, glm::vec3(0.02f, 0.02f, 0.02f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	shader.setMat4("model", model);
	poste_luz1.Draw(shader);

	model = glm::translate(tmp, glm::vec3(15.0f, 5.68f, -30.0));//a la do de las tasas
	model = glm::scale(model, glm::vec3(0.02f, 0.02f, 0.02f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	shader.setMat4("model", model);
	poste_luz1.Draw(shader);
	//---------------------------Elementos clasicos-------------------------------------------

	//---------------------------------baños-----------------------------------------------
	model = glm::translate(tmp, glm::vec3(-75.0f, 5.68f, -20.0));//a la do de las tasas
	model = glm::scale(model, glm::vec3(0.6f, 0.6f, 0.6f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	shader.setMat4("model", model);
	toilet.Draw(shader);

	model = glm::translate(model, glm::vec3(10.0f, 0.0f, 0.0));//a la do de las tasas
	shader.setMat4("model", model);
	toilet.Draw(shader);

	model = glm::translate(model, glm::vec3(10.0f, 0.0f, 0.0));//a la do de las tasas
	shader.setMat4("model", model);
	toilet.Draw(shader);

	model = glm::translate(tmp, glm::vec3(-75.0f, 5.68f, 20.0));//a la do de las tasas
	model = glm::scale(model, glm::vec3(0.6f, 0.6f, 0.6f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	shader.setMat4("model", model);
	toilet.Draw(shader);

	model = glm::translate(model, glm::vec3(-10.0f, 0.0f, 0.0));//a la do de las tasas
	shader.setMat4("model", model);
	toilet.Draw(shader);

	model = glm::translate(model, glm::vec3(-10.0f, 0.0f, 0.0));//a la do de las tasas
	shader.setMat4("model", model);
	toilet.Draw(shader);


	//---------------------------------baños------------------------------------------



	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, t_unam);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, t_caja_brillo);
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, t_coaster);
	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, frontal);
	glActiveTexture(GL_TEXTURE5);
	glBindTexture(GL_TEXTURE_2D, trasera);
	glActiveTexture(GL_TEXTURE6);
	glBindTexture(GL_TEXTURE_2D, superior);
	glActiveTexture(GL_TEXTURE7);
	glBindTexture(GL_TEXTURE_2D, inferior);
	glActiveTexture(GL_TEXTURE8);
	glBindTexture(GL_TEXTURE_2D, derecho);
	glActiveTexture(GL_TEXTURE9);
	glBindTexture(GL_TEXTURE_2D, izquierdo);
	glActiveTexture(GL_TEXTURE10);
	glBindTexture(GL_TEXTURE_2D, brillo);


	textureshader.use();
	textureshader.setInt("texture1", 3);
	glBindVertexArray(VAO);
	projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 500.0f);
	view = camera.GetViewMatrix();

	model = glm::mat4(1.0f);


	textureshader.setVec3("viewPos", camera.Position);
	textureshader.setMat4("model", model);
	textureshader.setMat4("view", view);
	// note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
	textureshader.setMat4("projection", projection);

	//my_cilynder.render();
	//my_cilynder.riel(model, textureshader);
	my_cilynder.roller_coaster(textureshader);

	
	

	


	
	
	
	
	
	
	
	
	lightingshader.use();

	lightingshader.setVec3("light.position", camera.Position);
	lightingshader.setVec3("light.direction", camera.Front);
	lightingshader.setFloat("light.cutOff", glm::cos(glm::radians(10.0f)));

	lightingshader.setVec3("viewPos", camera.Position);

	lightingshader.setVec3("light.ambient", ambient1, ambient2, ambient3);
	lightingshader.setVec3("light.diffuse", 0.4f, 0.8f, 0.8f);
	lightingshader.setVec3("light.specular", 0.0f, 0.0f, 2.0f);
	//For Positional and Spotlight
	lightingshader.setFloat("light.constant", 1.0f);
	lightingshader.setFloat("light.linear", 0.009f);
	lightingshader.setFloat("light.quadratic", 0.0032f);

	// material properties
	lightingshader.setFloat("material_shininess", 35.0f);

	projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 500.0f);
	view = camera.GetViewMatrix();

	model = glm::mat4(1.0f);

	lightingshader.setMat4("view", view);
	// note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
	lightingshader.setMat4("projection", projection);
	lightingshader.setMat4("model", model);

	glBindVertexArray(VAO);

	model = glm::translate(model, glm::vec3(2.0f, 0.0f, 2.0f));//trasladamos
	model = glm::scale(model, glm::vec3(300.0f, 200.0f, 300.0f));//escalamos
	lightingshader.setMat4("model", model);//iniciamos el shader al lugar donde nos trasladamos
	
	//--------------------Sky Box--------------------
	lightingshader.setVec3("ambientColor", 1.0f, 1.0f, 1.0f);
	lightingshader.setVec3("diffuseColor", 0.8f, 0.8f, 0.8f);
	lightingshader.setVec3("specularColor", 1.0f, 1.0f, 1.0f);
	lightingshader.setInt("material_diffuse", 5);//parte trasera
	lightingshader.setMat4("model", model);
	//glDrawArrays(GL_QUADS, 24, 4);

	for (int i = 0; i < 4; i++)
	{
		glDrawArrays(GL_TRIANGLE_FAN, 24, i + 1);
	}
	

	//lightingShader.setMat4("model", model);
	lightingshader.setInt("material_diffuse", 4);//Parte frontal
	//glDrawArrays(GL_QUADS, 28, 4);
	for (int i = 0; i < 4; i++)
	{
		glDrawArrays(GL_TRIANGLE_FAN, 28, i + 1);
	}
	//lightingShader.setMat4("model", model);
	lightingshader.setInt("material_diffuse", 7);//parte inferior
	//glDrawArrays(GL_QUADS, 40, 4);
	for (int i = 0; i < 4; i++)
	{
		glDrawArrays(GL_TRIANGLE_FAN, 40, i + 1);
	}
	//lightingShader.setMat4("model", model);
	lightingshader.setInt("material_diffuse", 6);//parte superior
	//glDrawArrays(GL_QUADS, 44, 4);
	for (int i = 0; i < 4; i++)
	{
		glDrawArrays(GL_TRIANGLE_FAN, 44, i + 1);
	}
	//lightingShader.setMat4("model", model);
	lightingshader.setInt("material_diffuse", 9);//parte izquierda
	/*Como aqui queremos agregar el material especular se lo pasamos al shader y como parametros nuestra textura 
	que sera el especular, en esta parte en especifico lo tendral los dos costados, por lo que solo pasamos como parametro y 
	dibujamos*/
	lightingshader.setInt("material_specular", 9);
	//glDrawArrays(GL_QUADS, 32, 4);
	for (int i = 0; i < 4; i++)
	{
		glDrawArrays(GL_TRIANGLE_FAN, 32, i + 1);
	}

	lightingshader.setInt("material_diffuse", 8);
	lightingshader.setInt("material_specular", 10);
	//glDrawArrays(GL_QUADS, 36, 4);
	for (int i = 0; i < 4; i++)
	{
		glDrawArrays(GL_TRIANGLE_FAN, 36, i + 1);
	}

	//-----------------Sky box---------------------
	
	

	textureshader.use();
	textureshader.setInt("texture1", 3);
	glBindVertexArray(VAO);
	model = glm::mat4(1.0f);


	projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 500.0f);
	view = camera.GetViewMatrix();
	textureshader.setVec3("viewPos", camera.Position);
	textureshader.setMat4("model", model);
	textureshader.setMat4("view", view);
	textureshader.setMat4("projection", projection);



	model = glm::translate(model, glm::vec3(-48.0f, 3.5f, 5.0f));
	model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
	model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	my_rueda.dibujaRueda(3, lightingshader, textureshader, model, VBO, VAO, EBO, rotaRueda, angRotPuerta);

	lampshader.use();

	lampshader.setMat4("projection", projection);
	lampshader.setMat4("view", view);
	model = glm::mat4(1.0f);
	model = glm::translate(model, lightPosition);
	model = glm::scale(model, glm::vec3(0.25f));
	lampshader.setMat4("model", model);

/*
	lightposshader.use();
	glBindVertexArray(VAO);
	lightposshader.setVec3("light.position", glm::vec3(0.0f, 10.0f, 0.0f));
	lightposshader.setVec3("viewPos", camera.Position);
	lightposshader.setVec3("light.ambient", 0.9f, 0.9f, 0.9f);
	lightposshader.setVec3("light.diffuse", 0.8f, 0.8f, 0.8f);
	lightposshader.setVec3("light.specular", 10.0f, 10.0f, 10.0f);
	//For Positional and Spotlight
	lightposshader.setFloat("light.constant", 1.0f);
	lightposshader.setFloat("light.linear", 0.09f);
	lightposshader.setFloat("light.quadratic", 0.032f);

	// material properties
	lightposshader.setFloat("material_shininess", 32.0f);
	model = glm::mat4(1.0f);
	lightposshader.setMat4("model", model);
	lightposshader.setMat4("view", view);
	// note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
	lightposshader.setMat4("projection", projection);

	model = glm::translate(model, glm::vec3(-30.0f, 5.0f, 0.0f));
	model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
	lightposshader.setMat4("model", model);
	lightposshader.setInt("material_diffuse", 1);
	glDrawArrays(GL_QUADS, 0, 24);
	*/
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
	//LoadTextures();
	myData();
	my_cilynder.init();
	my_canasta.init();
	my_rueda.init();
	glEnable(GL_DEPTH_TEST);

	//esta parte es la carga del shader que antes se hacia en display
	Shader modelShader("Shaders/modelLoading.vs", "Shaders/modelLoading.fs");
	Shader lampShader("shaders/shader_lamp.vs", "shaders/shader_lamp.fs");//para la luz
	Shader lightingShader("shaders/shader_texture_light_spot.vs", "shaders/shader_texture_light_spot.fs"); //Spotlight(luz de reflector)
	Shader projectionShader("shaders/shader_texture.vs", "shaders/shader_texture.fs");
	Shader lightposShader("shaders/shader_texture_light_pos.vs", "shaders/shader_texture_light_pos.fs");
	//esto se cambia porque asi el shader se carga un avez y antes se cargaba multiples veces, a cada rato se dibujaba el frame
	//ahora como son modelos muy robustos con demasiados vertices  eso lo haria demasiado lento

	// Load models
	Model carril = ((char *)"Models/parque/parqueWL.obj");//para cargar el modelo del carril
	Model personaje = ((char *)"Models/personaje/muro.obj");//para cargar el modelo del personaje
	Model personaje2 = ((char *)"Models/man/man.obj");//para cargar el modelo del personaje
	Model carpa_tasas = ((char *)"Models/tasas_giratorias/carpa_tasas.obj");
	Model base_tasas = ((char *)"Models/tasas_giratorias/base_giro.obj");
	Model tasa = ((char *)"Models/tasas_giratorias/tasa.obj");
	Model futbolito = ((char *)"Models/futbolito/futbolito.obj");
	Model carpa_fut = ((char *)"Models/futbolito/carpa/carpa_futbolito.obj");
	Model basketball = ((char *)"Models/basketball/basketball.obj");
	Model jugos = ((char *)"Models/food_carts/jugos/jugos.obj");
	//Model jugos = ((char *)"Models/coaster_cart/coaster_cart.obj");

	Model ambulante1 = ((char *)"Models/food_carts/jugos/jugos.obj");//carro de comida ambulante
	Model barrera = ((char *)"Models/barrera/Barrera.obj");
	Model bumper_car = ((char *)"Models/bumper/carrito_chocon.obj");
	Model pista = ((char *)"Models/bumper/pista_2.obj");
	Model silla = ((char *)"Models/elementos/silla1.obj");
	Model poste_luz1 = ((char *)"Models/elementos/poste_luz1.obj");
	Model trash = ((char *)"Models/elementos/trash.obj");
	Model trash2 = ((char *)"Models/elementos/trash/bote.obj");
	Model arbol1 = ((char *)"Models/elementos/arboles/bigtree.obj");
	Model tiro_blanco = ((char *)"Models/tiro_blanco/dart_board.obj");
	Model premios = ((char *)"Models/juguetes/premios/premios.obj");
	Model toilet = ((char *)"Models/toilet/toilet.obj");

	Model base_caballos = ((char *)"Models/caballos/base.obj");
	Model giro_caballos = ((char *)"Models/caballos/c_giratorio.obj");
	Model caballo = ((char *)"Models/caballos/caballo.obj");
	
	//Model cuerpo = ((char *)"Models/hombre/superior.obj");
	//Model musloDer = ((char *)"Models/hombre/piernader.obj");
	//Model musloIzq = ((char *)"Models/hombre/piernaizq.obj");

	Model coaster_cart = ((char *)"Models/coaster_cart/coaster_cart.obj");

	//personaje por partes
	

	LoadTextures();//carga las texturas a utilizar


	//-------------------inicializacion de keyframes-------------------------------------
	for (int i = 0; i < MAX_FRAMES; i++)
	{
		KeyFrame[i].x_coaster_cart = 0;
		KeyFrame[i].xInc_coaster_cart = 0;
		KeyFrame[i].y_coaster_cart = 0;
		KeyFrame[i].yInc_coaster_cart = 0;
		KeyFrame[i].z_coaster_cart = 0;
		KeyFrame[i].zInc_coaster_cart = 0;
		KeyFrame[i].rotx_coaster_cart = 0;
		KeyFrame[i].rotxInc_coaster_cart = 0;
		KeyFrame[i].roty_coaster_cart = 0;
		KeyFrame[i].rotyInc_coaster_cart = 0;
		KeyFrame[i].rotz_coaster_cart = 0;
		KeyFrame[i].rotzInc_coaster_cart = 0;
	}

	setFrame();//lee el archivo con los frames de la montaña rusa


	//----------------------------------------------------------------------

	//aprender modelado_ 3d maps o otras cosas parecidas en este caso la llanta se mueve mal por un problema de modelado
	//ya que el pivote esta mal ubicado en el modelo de la llanta

	glm::mat4 projection = glm::mat4(1.0f);	//This matrix is for Projection
	projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
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
		//animate();
		animated_tasas();
		animate_cc();
		animate_bumper(&x_cart, &y_cart, &rot_cart, &estado_cart1, mov1, &stop_cart1, &tiempo_bumper1);
		choque(&x_cart, &y_cart, &stop_cart1, &ac_cart1, &x_cart2, &z_cart2, &stop_cart2, &ac_cart2, &x_cart3, &z_cart3, &stop_cart3, &ac_cart3);
		accidente(&ac_cart1, &x_cart, &y_cart, &z_cart, &rot_cart, &rot_cart_z);
		animate_bumper(&x_cart2, &z_cart2, &rot_cart2, &estado_cart2, mov2, &stop_cart2, &tiempo_bumper2);
		animate_bumper(&x_cart3, &z_cart3, &rot_cart3, &estado_cart3, mov3, &stop_cart3, &tiempo_bumper3);

		animate_horse();
		animate_coaster();


		animate();//rueda de la fortuna


		// render
		// Backgound color
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		display(modelShader, lampShader, lightingShader, projectionShader, lightposShader, carril, personaje, personaje2, futbolito, carpa_tasas, base_tasas, tasa, basketball, tiro_blanco, jugos, ambulante1, barrera, carpa_fut, bumper_car,
			pista, silla, trash, trash2, poste_luz1, arbol1, premios, toilet, base_caballos, giro_caballos, caballo, coaster_cart);

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

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		camera.ProcessKeyboard(FORWARD, (float)deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, (float)deltaTime);
	//if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
	//	play = true;
	//if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
	//	play = false;
	/*if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		direction_right = true;
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		direction_right = false;*/
	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) {//poner de noche
		ambient1 = 0.04f;
		ambient2 = 0.04f;
		ambient3 = 0.04f;
	}
	if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) {//poner de dia
		ambient1 = 1.0f;
		ambient2 = 1.0f;
		ambient3 = 1.0f;
	}
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)//PARA ACTIVAR LA NIMACION DE LA RUEDA
		activate_rueda = true;
		//----------para tasas giratorias
	if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)//activar taas
		activate_tasas = true;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)//descativar tasas
		activate_tasas = false;
	if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)//para activar el carro de comida
		activate_cc = true;
	if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) {//para activar los carros chocones
		stop_cart1 = false;
		stop_cart2 = false;
		stop_cart3 = false;

		x_cart = 0.0f;
		y_cart = 0.0f;
		z_cart = 1.0f;
		rot_cart = 0.0f;
		rot_cart_z = 0.0f;
		estado_cart1 = 3;
		avanzar = 0;

		ac_cart1 = false;

		//carro 2
		x_cart2 = -30.0f;
		z_cart2 = -30.0f;
		y_cart2 = 1.0f;
		rot_cart2 = 90.0f;
		rot_cart2_z = 0.0f;
		estado_cart2 = 0;
		ac_cart2 = false;

		//carro 3
		x_cart3 = 30.0f;
		z_cart3 = 30.0f;
		y_cart3 = 1.0f;
		rot_cart3 = 180.0f;
		rot_cart3_z = 0.0f;
		estado_cart3 = 2;
		ac_cart3 = false;

		aux = 0;
		aux_ac;

	}
	if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {//detiene los carros chocones
		stop_cart1 = true;
		stop_cart2 = true;
		stop_cart3 = true;
	}

	if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS) {//activa los caballos
		activate_caballos = true;
	}

	//-------------para activar la animacion por keyframes-------------------------
	if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS) {//activa animacion por keyframes de la montaña
		if (activate_coaster == false && (FrameIndex > 1))
		{
			resetElements();
			//First Interpolation				
			interpolation();

			activate_coaster = true;
			playIndex = 0;
			i_curr_steps = 0;
		}
		else
		{
			activate_coaster = false;
		}
	}
	/*
	//To Save a KeyFrame
	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
	{
		if (FrameIndex < MAX_FRAMES)
		{
			saveFrame();
		}
	}*/
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