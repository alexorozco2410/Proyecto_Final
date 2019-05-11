/*---------------------------------------------------------*/
/* ----------------  Práctica 10 --------------------------*/
/*-----------------    2019-2   ---------------------------*/
/*-- Computación gráfica e interacción humano computadora --*/
/*------------- Orozco Hernandez Alexis  -----------------*/
/*---------------  Version VS 2017  ----------------------*/
/*------------------  Grupo 04  --------------------------*/
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

//para activar la animacion se usa la tecla P y para detenerla se usa la tecla O

// Other Libs
#include "SOIL2/SOIL2.h" //ayuda a cargar los modelos

Cilindro my_cilynder(1.0);

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
glm::vec3 lightPosition(0.0f, 3.0f, 0.0f);
glm::vec3 lightDirection(0.0f, 0.0f, -70.0f);

void myData(void);
void display(Shader, Model, Model);
void getResolution(void);
void animate(void);
void LoadTextures(void);
unsigned int generateTextures(char*, bool);

//For Keyboard
float	movX = 0.0f,
movY = 0.0f,
movZ = -5.0f,
rot_personaje = 0.0f,
rotX = 0.0f;

//Texture
unsigned int	t_smile,
t_toalla,
t_unam,
t_white,
t_panda,
t_cubo,
t_caja,
t_caja_brillo;

//For model
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

float movKit_z = -15.0f;
float movKit_x = -4.0f;

float rot_llanta = 0.0f;

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


void animate_bumper(float *x, float *y, float *rot, int *estado_cart, int mov[], bool *stop) {
	//int aux = 1;
	if (*stop == false) {
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


void animate(void)//para personaje
{
	if (play) {
		if (movKit_z >= 20.0f && rot_personaje >= 180) {
			direction_right = false;
			stop = false;
		}

		if (movKit_z <= -17.0f && rot_personaje >= 360) {
			direction_right = true;
			stop = false;
			rot_personaje = 0.0f;
		}

		if (direction_right && !stop) {
			movKit_z += 0.04f; //para mover o detener el carro_ iniciar i detener la animacion
		}
		if (!direction_right && !stop) {
			movKit_z -= 0.04f; //para mover o detener el carro_ iniciar i detener la animacion
		}
		if (movKit_z <= -17.0f) {
			stop = true;
			//direction_right = true;
		}
		if (movKit_z >= 20.0f) {
			stop = true;
			//direction_right = false;
		}

		//esta parte hace que gire y cambie de carril el personaje
		if (stop && direction_right && (rot_personaje <= 90.0f)) {
			rot_personaje += 0.8f;
			direction_front = true;
		}

		if (direction_front && rot_personaje >= 90.0f && movKit_x < 4.0f) {
			movKit_x += 0.04f;
		}

		if (direction_front && rot_personaje <= 180.0f && movKit_x >= 4.0f) {
			rot_personaje += 0.8f;

		}
		//hasta aqui media vuelta, ya regresa

		//esta parte hace que gire y cambie otra vez de carril, a donde comenzo
		if (stop && !direction_right && (rot_personaje <= 270.0f)) {
			rot_personaje += 0.8f;
			direction_front = false;
		}

		if (!direction_front && rot_personaje >= 270.0f && movKit_x > -4.0f) {
			movKit_x -= 0.04f;
		}

		if (!direction_front && (rot_personaje <= 360.0f && rot_personaje != 0.0f) && movKit_x <= -4.0f) {
			rot_personaje += 0.8f;

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
int i_max_steps = 15; //intervalo entre cvada uno de los keyframes (interpolacion)
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



/*
void setFrame(void) //pasa los datos a la estructura
{

	printf("frameindex %d\n", FrameIndex);//primera parte

	KeyFrame[FrameIndex].x_coaster_cart = 45.0; //pasa las posiciones por cada estado (guarda el estado del monito)
	KeyFrame[FrameIndex].y_coaster_cart = 5.5;
	KeyFrame[FrameIndex].z_coaster_cart = -34.5;

	KeyFrame[FrameIndex].rotx_coaster_cart = 0.0;
	KeyFrame[FrameIndex].roty_coaster_cart = 90.0;
	KeyFrame[FrameIndex].rotz_coaster_cart = 0.0;

	FrameIndex++;

	printf("frameindex %d\n", FrameIndex);//segunda parte

	KeyFrame[FrameIndex].x_coaster_cart = 53.0; //pasa las posiciones por cada estado (guarda el estado del monito)
	KeyFrame[FrameIndex].y_coaster_cart = 5.5;
	KeyFrame[FrameIndex].z_coaster_cart = -34.5;

	KeyFrame[FrameIndex].rotx_coaster_cart = 0.0;
	KeyFrame[FrameIndex].roty_coaster_cart = 90.0;
	KeyFrame[FrameIndex].rotz_coaster_cart = 0.0;

	FrameIndex++;

	printf("frameindex %d\n", FrameIndex);//tercera parte

	KeyFrame[FrameIndex].x_coaster_cart = 54.5; //pasa las posiciones por cada estado (guarda el estado del monito)
	KeyFrame[FrameIndex].y_coaster_cart = 5.5;
	KeyFrame[FrameIndex].z_coaster_cart = -32.0;

	KeyFrame[FrameIndex].rotx_coaster_cart = 0.0;
	KeyFrame[FrameIndex].roty_coaster_cart = 0.0;
	KeyFrame[FrameIndex].rotz_coaster_cart = 0.0;

	FrameIndex++;
}
*/


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

//------------------------------------------animacion por keyframes-------------------------------------------------------------

void display(Shader shader, Shader lampshader, Shader lightingshader, Shader textureshader,
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


	projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 300.0f);
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
	model = glm::translate(tmp, glm::vec3(35.0f, 5.8f, -30.0));
	model = glm::scale(model, glm::vec3(0.5f, 0.3f, 0.6f));
	model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	//model = glm::rotate(model, glm::radians(rot_llanta), glm::vec3(1.0f, 0.0f, 0.0f));
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
	//----------------------------------------------------------------------------

	//personaje1
	model = glm::translate(tmp, glm::vec3(-30.0f, 5.7f, 0.0));
	model = glm::scale(model, glm::vec3(0.017f, 0.017f, 0.017f));
	//model = glm::rotate(model, glm::radians(rot_personaje), glm::vec3(0.0f, 1.0f, 0.0f));

	//model = glm::rotate(model, glm::radians(rot_llanta), glm::vec3(1.0f, 0.0f, 0.0f));
	shader.setMat4("model", model);
	personaje.Draw(shader);	//Izq delantera

	//personaje 2
	model = glm::translate(tmp, glm::vec3(-10.0f, 5.7f, 40.0));
	model = glm::scale(model, glm::vec3(0.017f, 0.017f, 0.017f));
	//model = glm::rotate(model, glm::radians(rot_personaje), glm::vec3(0.0f, 1.0f, 0.0f));

	//model = glm::rotate(model, glm::radians(rot_llanta), glm::vec3(1.0f, 0.0f, 0.0f));
	shader.setMat4("model", model);
	personaje2.Draw(shader);



	model = glm::translate(tmp, glm::vec3(41.5f, 5.7f, -20.0));
	model = glm::scale(model, glm::vec3(0.015f, 0.015f, 0.015f));
	//model = glm::rotate(model, glm::radians(rot_personaje), glm::vec3(0.0f, 1.0f, 0.0f));

	//model = glm::rotate(model, glm::radians(rot_llanta), glm::vec3(1.0f, 0.0f, 0.0f));
	shader.setMat4("model", model);
	personaje2.Draw(shader);

	//futbolitos
	//-----------------------------------futbolitos-------------------------------------
	//carpa
	model = glm::translate(tmp, glm::vec3(-50.0f, 5.5f, -25.0));
	model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
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
	model = glm::scale(model, glm::vec3(1.30f, 1.0f, 1.00f));
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
	model = glm::scale(model, glm::vec3(0.30f, 0.11f, 0.30f));
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


	textureshader.use();
	textureshader.setInt("texture1", 1);
	glBindVertexArray(VAO);
	projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 300.0f);
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
	glEnable(GL_DEPTH_TEST);

	//esta parte es la carga del shader que antes se hacia en display
	Shader modelShader("Shaders/modelLoading.vs", "Shaders/modelLoading.fs");
	Shader lampShader("shaders/shader_lamp.vs", "shaders/shader_lamp.fs");//para la luz
	Shader lightingShader("shaders/shader_texture_light_spot.vs", "shaders/shader_texture_light_spot.fs"); //Spotlight(luz de reflector)
	Shader projectionShader("shaders/shader_texture.vs", "shaders/shader_texture.fs");

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
	
	Model coaster_cart = ((char *)"Models/coaster_cart/coaster_cart.obj");

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

	setFrame();


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
		animate();
		animated_tasas();
		animate_cc();
		animate_bumper(&x_cart, &y_cart, &rot_cart, &estado_cart1, mov1, &stop_cart1);
		choque(&x_cart, &y_cart, &stop_cart1, &ac_cart1, &x_cart2, &z_cart2, &stop_cart2, &ac_cart2, &x_cart3, &z_cart3, &stop_cart3, &ac_cart3);
		accidente(&ac_cart1, &x_cart, &y_cart, &z_cart, &rot_cart, &rot_cart_z);
		animate_bumper(&x_cart2, &z_cart2, &rot_cart2, &estado_cart2, mov2, &stop_cart2);
		animate_bumper(&x_cart3, &z_cart3, &rot_cart3, &estado_cart3, mov3, &stop_cart3);

		animate_horse();
		animate_coaster();
		// render
		// Backgound color
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		display(modelShader, lampShader, lightingShader, projectionShader, carril, personaje, personaje2, futbolito, carpa_tasas, base_tasas, tasa, basketball, tiro_blanco, jugos, ambulante1, barrera, carpa_fut, bumper_car,
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

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, (float)deltaTime);
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

		//----------para tasas giratorias
	if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
		activate_tasas = true;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
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
	if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
		stop_cart1 = true;
		stop_cart2 = true;
		stop_cart3 = true;
	}

	if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS) {
		activate_caballos = true;
	}

	//-------------para activar la animacion por keyframes-------------------------
	if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS) {
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

	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
		z_coaster_cart -= 0.5f;
	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		z_coaster_cart += 0.5f;
	}
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		x_coaster_cart += 0.5f;
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		x_coaster_cart -= 0.5f;
	}
	if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS) {
		y_coaster_cart -= 0.5f;
	}
	if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS) {
		y_coaster_cart += 0.5f;
	}
	if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) {
		rotx_coaster_cart -= 5.0f;
	}
	if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) {
		rotx_coaster_cart += 5.0f;
	}
	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) {
		roty_coaster_cart += 5.0f;
	}
	if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) {
		roty_coaster_cart -= 5.0f;
	}
	if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS) {
		rotz_coaster_cart -= 5.0f;
	}
	if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) {
		rotz_coaster_cart += 5.0f;
	}

	//To Save a KeyFrame
	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
	{
		if (FrameIndex < MAX_FRAMES)
		{
			saveFrame();
		}
	}
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