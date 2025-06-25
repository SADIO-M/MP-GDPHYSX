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

  //Initializes the sphere and orthographic camera and time
void Game::initialize() {
	// Load the sphere VAO
	Vector zero(0, 0 ,0);
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
		windowWidth,
		windowHeight,
		-500.0f,
		500.0f,
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
		vec3(0.0, 0.0, 500.0),
		vec3(0.0),
		vec3(0.0),
		100.0
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