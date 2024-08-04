#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Object.h"

using namespace std;

void framebufferSizeCallback(GLFWwindow* window, int width, int height);
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
unsigned int createShader(const string& filename, const string& type);
unsigned int createProgram(unsigned int vertexShader, unsigned int fragmentShader);
unsigned int modelVAO(Object& model);
unsigned int loadTexture(const char* tFileName);
void drawModel(const string& target, unsigned int& shaderProgram, const glm::mat4& M, const glm::mat4& V, const glm::mat4& P,
	unsigned int& vao, unsigned int& texture);

Object penguinModel("obj/penguin.obj");
Object boardModel("obj/surfboard.obj");

int windowWidth = 800, windowHeight = 600;

// You can use these parameters
float swingAngle = 0;
float swingPos = 0;
float swingAngleDir = -1;
float swingPosDir = 1;
float squeezeFactor = 0;
bool squeezing = false;
bool useGrayscale = false;
bool tremble=false;
double currentTime;

int main()
{
	// Initialization
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFE_OPENGL_FORWARD_COMPACT, GL_TRUE);
#endif
	/* TODO#0: Change window title to "HW2 - your student id"
   *        Ex. HW2 - 312550000
   */
	GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "HW2-110550142", NULL, NULL);

	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
	glfwSetKeyCallback(window, keyCallback);
	glfwSwapInterval(1);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// You are encouraged to complete TODO#1~3 by finishing the functions createShader, createProgram, loadTexture, and modelVAO, but it's not mandatory.
	// In other words, you can complete TODO#1~3 without using these four functions.

	/* TODO#1: Create vertex shader, fragment shader, shader program
	 * Hint:
	 *       createShader, createProgram, glUseProgram
	 * Note:
	 *       vertex shader filename: "vertexShader.vert"
	 *		 fragment shader filename: "fragmentShader.frag"
	 */

	 /* TODO#2: Load texture
	  * Hint:
	  *       loadTexture
	  * Note:
	  *       penguin texture filename: "obj/penguin_diffuse.jpg"
	  *       board texture filename : "obj/surfboard_diffuse.jpg"
	  */

	  /* TODO#3: Set up VAO, VBO
	   * Hint:
	   *       modelVAO
	   */

	unsigned int vertexShader, fragmentShader, shaderProgram;
	vertexShader = createShader("vertexShader.vert", "vert");
	fragmentShader = createShader("fragmentShader.frag", "frag");
	shaderProgram = createProgram(vertexShader, fragmentShader);
	unsigned int penguinTexture, boardTexture;
	penguinTexture = loadTexture("obj/penguin_diffuse.jpg");
	boardTexture = loadTexture("obj/surfboard_diffuse.jpg");
	unsigned int penguinVAO, boardVAO;
	penguinVAO = modelVAO(penguinModel);
	boardVAO = modelVAO(boardModel);


	// Display loop
	glfwGetFramebufferSize(window, &windowWidth, &windowHeight);
	glViewport(0, 0, windowWidth, windowHeight);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	double dt;
	double lastTime = glfwGetTime();
	//double currentTime;
	

	/* TODO#4: Data connection - Retrieve uniform variable locations
	 *    1. Retrieve locations for model, view, and projection matrices.
	 *    2. Obtain locations for squeezeFactor, grayscale, and other parameters.
	 * Hint:
	 *    glGetUniformLocation
	 */


	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 perspective = glm::perspective(glm::radians(45.0f), (float)windowWidth / (float)windowHeight, 1.0f, 100.0f);

		glm::mat4 view = glm::lookAt(glm::vec3(0, 5, 5), glm::vec3(0, 0.5, 0), glm::vec3(0, 1, 0));

		/* TODO#5-1: Render Board
		 *    1. Set up board model matrix.
		 *    2. Send model, view, and projection matrices to the program.
		 *    3. Send squeezeFactor, useGrayscale, or other parameters to the program.(for key 's')
		 *    4. Set the value of the uniform variable "useGrayscale" and render the board.(for key 'g')
		 * Hint:
		 *	  rotate, translate, scale
		 *    glUniformMatrix4fv, glUniform1i
		 *    glUniform1i, glActiveTexture, glBindTexture, glBindVertexArray, glDrawArrays
		 */

		 /* TODO#5-2: Render Penguin
		  *    1. Set up penguin model matrix.
		  *    2. Send model, view, and projection matrices to the program.
		  *    3. Send squeezeFactor, useGrayscale, or other parameters to the program.(for key 's')
		  *    4. Set the value of the uniform variable "useGrayscale" and render the penguin.(for key 'g')
		  * Hint:
		  *	 rotate, translate, scale
		  *   glUniformMatrix4fv, glUniform1i
		  *   glUniform1i, glActiveTexture, glBindTexture, glBindVertexArray, glDrawArrays
		  */

		glUseProgram(shaderProgram);
		
		glm::mat4 ModelMatrix = glm::mat4(1.0f);
		glm::mat4 boardModelMatrix = glm::mat4(1.0f);
		ModelMatrix = glm::translate(ModelMatrix, glm::vec3(0.0f, 0.0f, swingPos));
		ModelMatrix = glm::translate(ModelMatrix, glm::vec3(0.0f, -0.5f, 0.0f));
		ModelMatrix = glm::rotate(ModelMatrix, glm::radians(swingAngle), glm::vec3(0.0f, 1.0f, 0.0f));
		boardModelMatrix = glm::rotate(ModelMatrix, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		boardModelMatrix = glm::scale(boardModelMatrix, glm::vec3(0.03f, 0.03f, 0.03f));

		drawModel("board", shaderProgram, boardModelMatrix, view, perspective, boardVAO, boardTexture);
		


		glm::mat4 penguinModelMatrix = glm::mat4(1.0f);
		penguinModelMatrix = glm::translate(ModelMatrix, glm::vec3(0.0f, 0.5f, 0.0f));
		penguinModelMatrix = glm::rotate(penguinModelMatrix, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		penguinModelMatrix = glm::scale(penguinModelMatrix, glm::vec3(0.025f, 0.025f, 0.025f));

		drawModel("penguin",shaderProgram, penguinModelMatrix, view, perspective, penguinVAO, penguinTexture);
		

		// Status update
		currentTime = glfwGetTime();
		dt = currentTime - lastTime;
		lastTime = currentTime;

		/* TODO#6: Update "swingAngle", "swingPos", "squeezeFactor"
		 * Speed:
		 *	  swingAngle   : 20 degrees/sec
		 *    swingPos     : 1.0f / sec
		 *    squeezeFactor: 90 degrees/sec
		 */


		swingAngle = swingAngle +20.0f * swingAngleDir * dt;
		if (swingAngle >= 20.0f) {
			swingAngleDir = -1;
		}
		else if (swingAngle <= -20.0f) {
			swingAngleDir = 1;
		}

		swingPos = swingPos + swingPosDir * dt;
		if (swingPos >= 2) {
			swingPosDir = -1;
		}
		else if(swingPos<=0) {
			swingPosDir = 1;
		}
		
		if (squeezing) {
			squeezeFactor += 90.0f * dt;
		}
		

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

// Add key callback

/* TODO#7: Key callback
 *    1. Press 's' to squeeze the penguin.
 *    2. Press 'g' to change to grayscale.
 *    3. Print "KEY S PRESSED" when key 's' is pressed, and similarly for other keys.
 */
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (key == GLFW_KEY_S && action == GLFW_PRESS)
	{
		cout << "KEY S PRESSED\n";
		if (squeezing) {
			squeezing = false;
		}
		else {
			squeezing = true;
		}
		
	}

	if (key == GLFW_KEY_G && action == GLFW_PRESS) {
		cout << "KEY G PRESSED\n";
		if (useGrayscale) {
			useGrayscale = false;
		}
		else {
			useGrayscale = true;
		}

	}

	if (key == GLFW_KEY_T && action == GLFW_PRESS) {
		cout << "KEY T PRESSED\n";
		if (tremble) {
			tremble = false;
		}
		else {
			tremble = true;
		}

	}

	
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	windowWidth = width;
	windowHeight = height;
}

/* TODO#1-1: createShader
* Hint:
*       glCreateShader, glShaderSource, glCompileShader
*/
unsigned int createShader(const string& filename, const string& type)
{
	string shaderSource;
	ifstream shaderFile(filename);
	if (shaderFile.is_open()) {
		string line;
		while (getline(shaderFile, line)) {
			shaderSource += line + "\n";
		}
		shaderFile.close();
	}
	else {
		cerr << "Failed to open shader file: " << filename << endl;
		return 0;
	}

	unsigned int shaderID = glCreateShader(type == "vert" ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER);

	const char* source = shaderSource.c_str();
	glShaderSource(shaderID, 1, &source, nullptr);
	glCompileShader(shaderID);

	int success;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
	if (!success) {
		char infoLog[512];
		glGetShaderInfoLog(shaderID, 512, nullptr, infoLog);
		cerr << "Shader compilation error: " << infoLog << endl;
		return 0;
	}

	return shaderID;

}

/* TODO#1-2: createProgram
* Hint:
*       glCreateProgram, glAttachShader, glLinkProgram, glDetachShader
*/
unsigned int createProgram(unsigned int vertexShader, unsigned int fragmentShader)
{
	unsigned int shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	int success=0;
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		char infoLog[512];
		glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
		cerr << "Shader program linking error: " << infoLog << endl;
		return 0; 
	}

	glDetachShader(shaderProgram, vertexShader);
	glDetachShader(shaderProgram, fragmentShader);
	

	return shaderProgram;

}

/* TODO#2: Load texture
 * Hint:
 *       glEnable, glGenTextures, glBindTexture, glTexParameteri, glTexImage2D
 */
unsigned int loadTexture(const char* tFileName) {
	unsigned int texture;
	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	stbi_set_flip_vertically_on_load(true);

	int width, height, nrChannels;
	unsigned char* data = stbi_load(tFileName, &width, &height, &nrChannels, 0);
	if (data) {

		glActiveTexture(GL_TEXTURE0);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);
		stbi_image_free(data);
	}
	else {
		cerr << "Failed to load texture: " << tFileName << endl;
		return 0; 
	}

	return texture;
}

/* TODO#3: Set up VAO, VBO
 * Hint:
 *       glGenVertexArrays, glBindVertexArray, glGenBuffers, glBindBuffer, glBufferData,
 *       glVertexAttribPointer, glEnableVertexAttribArray, 
 */
unsigned int modelVAO(Object& model)
{
	unsigned int VAO, VBO[3];
	glGenVertexArrays(1,&VAO);
	glBindVertexArray(VAO);

	glGenBuffers(3, VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GL_FLOAT)*model.positions.size(), model.positions.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	

	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, model.normals.size() * sizeof(float), model.normals.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	

	glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
	glBufferData(GL_ARRAY_BUFFER, model.texcoords.size() * sizeof(float), model.texcoords.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(2);


	glBindVertexArray(0);

	return VAO;
	
}
void drawModel(const string& target, unsigned int& shaderProgram, const glm::mat4& M, const glm::mat4& V, const glm::mat4& P,
	unsigned int& vao, unsigned int& texture)
{
	unsigned int mLoc, vLoc, pLoc;
	mLoc = glGetUniformLocation(shaderProgram, "M");
	vLoc = glGetUniformLocation(shaderProgram, "V");
	pLoc = glGetUniformLocation(shaderProgram, "P");
	glUniformMatrix4fv(mLoc, 1, GL_FALSE, glm::value_ptr(M));
	glUniformMatrix4fv(vLoc, 1, GL_FALSE, glm::value_ptr(V));
	glUniformMatrix4fv(pLoc, 1, GL_FALSE, glm::value_ptr(P));

	int useGrayscaleLoc = glGetUniformLocation(shaderProgram, "useGrayscale");
	int squeezeFactorLoc = glGetUniformLocation(shaderProgram, "squeezeFactor");

	if (useGrayscaleLoc != -1) {
		glUniform1i(useGrayscaleLoc, useGrayscale ? 1 : 0);
	}
	
	if (target == "board") {

		if (squeezeFactorLoc != -1) {
			glUniform1f(squeezeFactorLoc, glm::radians(0.0f));
		}

		glUniform1i(glGetUniformLocation(shaderProgram, "ourTexture"), 0);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, boardModel.positions.size());

	}
	else if (target == "penguin") {
		
		if (squeezeFactorLoc != -1) {
			glUniform1f(squeezeFactorLoc, glm::radians(squeezeFactor));
		}

	
		glUniform1i(glGetUniformLocation(shaderProgram, "ourTexture"), 0);
		glUniform1i(glGetUniformLocation(shaderProgram, "tremble"), tremble?1:0);
		glUniform1f(glGetUniformLocation(shaderProgram, "time"), currentTime);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, penguinModel.positions.size());


	}

	glBindVertexArray(0);
}

