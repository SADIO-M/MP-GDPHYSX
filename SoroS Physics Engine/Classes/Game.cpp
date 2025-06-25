#include "Game.h"

//CONSTRUCTORS
Game::Game() {}

Game::Game(GLFWwindow* window, float windowWidth, float windowHeight) {
	this->window = window;
	this->windowWidth = windowWidth;
	this->windowHeight = windowHeight;
}

//FUNCTIONS
  //Starts initialization
void Game::start() {
	glfwMakeContextCurrent(window);
	gladLoadGL();
	glViewport(0, 0, windowWidth, windowHeight);
	glEnable(GL_DEPTH_TEST);

	initialize();
}

  //Initializes the sphere VAO and the cameras
void Game::initialize() {
	// Load the sphere VAO
	// Setting everything to zero because all we need is to load the shaders
	Vector zero(0, 0 ,0);
	Vector orthoPos(0.0, 0.0, 5.0);
	Vector persPos(0.0, 0.0, 700.0);

	setVAO(&sphereVAO, GENERATE);
	setVAO(&sphereVAO, BIND);
	sphereObj = new Object(
		"3D/sphere.obj",
		(vec3)zero,
		(vec3)zero,
		(vec3)zero,
		"Shaders/ObjectShader.vert",
		"Shaders/ObjectShader.frag",
		(vec3)zero
	);
	setVAO(&sphereVAO, UNBIND);

	//Create Orthographic Camera
	orthoCam = new Orthographic(
		windowWidth,            // Window width
		windowHeight,           // Window height
		-1200.0f,               // zNear
		 1200.0f,				// zFar
		(vec3)orthoPos,	        // Camera Position
		(vec3)zero,				// Camera Center
		(vec3)zero,				// Camera Rotation
		-800.0f,				// Left Point
		 800.0f,				// Right Point
		-800.0f,				// Bottom Point
		 800.0f					// Top Point
	);

	//Create Perspective Camera
	persCam = new Perspective(
		windowWidth,            // Window width
		windowHeight,			// Window height
		0.1f,					// zNear
		1200.0f,				// zFar
		(vec3)persPos,	        // Camera Position
		(vec3)zero,				// Camera Center
		(vec3)zero,				// Camera Rotation
		100.0					// Field of View (FOV)
	);

	//Runs the game
	run();
	glfwTerminate();
}

  //Runs the game, renders cameras and particles
void Game::run() {
	using clock = chrono::high_resolution_clock;
	auto currTime = clock::now();
	auto prevTime = currTime;
	chrono::nanoseconds curr_ns(0);
	
	// Initialize a physics world
	PhysicsWorld physWorld = PhysicsWorld();
	
	int sparkNum = 0;
		cout << "Enter spark number: ";
		cin >> sparkNum;
		cout << endl;

	RenderParticleFactory renParFactory(&physWorld);
	list<RenderParticle*> renderParticles;

	//////////////////////MAIN LOOP//////////////////////
	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//GETS CURRENT TIME
		currTime = clock::now();
		auto duration = chrono::duration_cast<chrono::nanoseconds> (currTime - prevTime);
		prevTime = currTime;

		checkInput();
		inputCooldown++;

		curr_ns += duration;
		///// FIXED UPDATE /////
		if (curr_ns >= timestep) {
			auto ms = chrono::duration_cast<chrono::milliseconds>(curr_ns);
			//RESET
			curr_ns -= curr_ns;

			orthoCam->update();
			persCam->update();

			if (play) {
				physWorld.update((float)ms.count() / 1000);

				if (renderParticles.size() < sparkNum) {
					renderParticles.push_back(renParFactory.create());
				}
			}
		}
		
		//All objects use the same shader anyway
		glUseProgram(sphereObj->getShader().getShaderProg());
		//Change view depending on which camera is active
		if(camOn == ORTHOGRAPHIC) orthoCam->draw(sphereObj->getShader().getShaderProg());
		else persCam->draw(sphereObj->getShader().getShaderProg());

		setVAO(&sphereVAO, BIND);
		for (list<RenderParticle*>::iterator r = renderParticles.begin(); r != renderParticles.end(); r++) {
			(*r)->draw();
		}
		cleanRenderParticles(&renderParticles);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

void Game::cleanRenderParticles(list<RenderParticle*>* renderParticles)
{
	renderParticles->remove_if(
		[](RenderParticle* p) {
			return p->isDestroyed;
		}
	);
}

void Game::checkInput()
{
	// Camera Switching
	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) camOn = ORTHOGRAPHIC;
	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) camOn = PERSPECTIVE;
	// Pause / Play
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && inputCooldown >= 1000) {
		play = !play;
		inputCooldown = 0;
	}
	// Camera Rotation
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
	glDeleteVertexArrays(1, &sphereVAO);
}