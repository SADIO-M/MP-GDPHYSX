#include "Game.h"

//CONSTRUCTORS
Game::Game() {}

Game::Game(GLFWwindow* window, float windowWidth, float windowHeight) {
	this->window = window;
	this->windowWidth = windowWidth;
	this->windowHeight = windowHeight;

	camOn = ORTHOGRAPHIC;
}

//FUNCTIONS
  //Starts initialization
void Game::start() {
	glfwMakeContextCurrent(window);
	gladLoadGL();
	glViewport(0, 0, windowWidth, windowHeight);

	initialize();
}

  //Initializes the sphere and orthographic camera and time
void Game::initialize() {
	Vector defaultPos(0, 0 ,0);
	Vector myVecScale(10, 10, 10);
	Vector myVecRot(0, 0, 0);
	Vector color1(0.8f, 0.7f, 0.0f);
	
	//Load Sphere
	setVAO(&sphereVAO, GENERATE);
	setVAO(&sphereVAO, BIND);
		//1
	allModels.push_back(new Object(
		"3D/sphere.obj",
		(vec3)defaultPos,
		(vec3)myVecScale,
		(vec3)myVecRot,
		"Shaders/ObjectShader.vert",
		"Shaders/ObjectShader.frag",
		(vec3)color1
	));
	setVAO(&sphereVAO, UNBIND);

	//Create Orthographic Camera
	orthoCam = new Orthographic(
        windowWidth,                 
		windowHeight,                 
        -200.0f,                 
         200.0f,                 
        vec3(0.0, 0.0, 5.0),  
        vec3(0.0),
		vec3(0.0),
        -800.0f,                 
         800.0f,                  
        -800.0f,                
         800.0f                  
	);

	persCam = new Perspective(
		windowWidth,
		windowHeight,
		0.1f,                   
		1000.0f,                 
		vec3(0.0, 0.0, 900.0),
		vec3(0.0),
		vec3(0.0),
		80.0
	);

	//Runs the game
	run();
	glfwTerminate();
}

  //Runs the game, renders camera and sphere
void Game::run() {
	using clock = chrono::high_resolution_clock;
	auto currTime = clock::now();
	auto prevTime = currTime;
	chrono::nanoseconds curr_ns(0);
	
	PhysicsWorld physWorld = PhysicsWorld();

	//////////////////////RENDER PARTICLE LIST//////////////////////
	list<RenderParticle*> renderParticles;

	int sparkNum = 0;
	cout << "Enter spark number: ";
	cin >> sparkNum;
	cout << endl;

	// TESTING FACTORY //
	RenderParticleFactory renParFactory(&allModels, &physWorld);

	for (int i = 0; i < sparkNum; i++) {
		renderParticles.push_back(renParFactory.create());
	}

	// END OF TESTING FACTORY //

	//////////////////////MAIN LOOP//////////////////////
	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		checkInput();

		//GETS CURRENT TIME
		currTime = clock::now();
		auto duration = chrono::duration_cast<chrono::nanoseconds> (currTime - prevTime);
		prevTime = currTime;

		//STOP RENDERING OBJECT IF AT CENTER
		//for (list<Particle*>::iterator p = physWorld.getParticleList()->begin(); p != physWorld.getParticleList()->end(); p++) {
		//	if ((*p)->atCenter()) (*p)->Destroy();
		//}

		curr_ns += duration;
		if (curr_ns >= timestep) {
			auto ms = chrono::duration_cast<chrono::milliseconds>(curr_ns);
			//RESET
			curr_ns -= curr_ns;

			//UPDATE Camera only in fixed update
			// EITHER UPDATE ONLY 1 CAM OR BOTH AND JUST SWITCH
			//if (camOn == ORTHOGRAPHIC) orthoCam->update();
			//else persCam->update();
			orthoCam->update();
			persCam->update();

			physWorld.update((float)ms.count() / 1000);
		}
		
		//All objects use the same shader anyway
		glUseProgram(allModels[0]->getShader().getShaderProg());

		if(camOn == ORTHOGRAPHIC)
			orthoCam->draw(allModels[0]->getShader().getShaderProg());
		else
			persCam->draw(allModels[0]->getShader().getShaderProg());

		setVAO(&sphereVAO, BIND);

		for (list<RenderParticle*>::iterator r = renderParticles.begin(); r != renderParticles.end(); r++) {
			(*r)->draw();
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

void Game::checkInput()
{
	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) camOn = ORTHOGRAPHIC;
	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) camOn = PERSPECTIVE;

	//if (camOn == PERSPECTIVE) {
	//	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) persCam->rotateWithKeys('W');
	//	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) persCam->rotateWithKeys('S');
	//	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) persCam->rotateWithKeys('A');
	//	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) persCam->rotateWithKeys('D');
	//}
	//else {
	//	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) orthoCam->rotateWithKeys('W');
	//	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) orthoCam->rotateWithKeys('S');
	//	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) orthoCam->rotateWithKeys('A');
	//	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) orthoCam->rotateWithKeys('D');
	//}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) { persCam->rotateWithKeys('W'); orthoCam->rotateWithKeys('W'); }
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) { persCam->rotateWithKeys('S'); orthoCam->rotateWithKeys('S'); }
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) { persCam->rotateWithKeys('A'); orthoCam->rotateWithKeys('A'); }
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) { persCam->rotateWithKeys('D'); orthoCam->rotateWithKeys('D'); }


}

  //For proper VAO handling
void Game::setVAO(GLuint* VAO, int type) {
	switch (type) {
		case UNBIND:	// Unbind VAO
			glBindVertexArray(0);
			break;
		case BIND:		// Bind VAO
			glBindVertexArray(*VAO);
			break;
		case GENERATE:  // Generate VAO
			glGenVertexArrays(1, VAO);
			break;
	}
}

//DECONSTRUCTOR
Game::~Game() {
	for (Model3D* model : allModels)
		model->~Model3D();

	glDeleteVertexArrays(1, &sphereVAO);
}