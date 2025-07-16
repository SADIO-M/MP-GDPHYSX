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

	initialize();
}

  //Initializes the sphere and orthographic camera and time
void Game::initialize() {
	Vector defaultPos(0, 0 ,0);
	Vector myVecScale(50, 50, 50);
	Vector myVecRot(0, 0, 0);
	Vector color1(0.8f, 0.7f, 0.0f);
	Vector color2(0.5f, 0.1f, 0.4f);
	Vector noColor(0, 0, 0);
	
	//Load Sphere
	setVAO(&sphereVAO, GENERATE);
	setVAO(&sphereVAO, BIND);
		//1
	for(int i = 0; i < 5; i++){
		allModels.push_back(new Object(
			"3D/sphere.obj",
			(vec3)defaultPos,
			(vec3)myVecScale,
			(vec3)myVecRot,
			"Shaders/ObjectShader.vert",
			"Shaders/ObjectShader.frag",
			(vec3)color1
		));
	}
	setVAO(&sphereVAO, UNBIND);

	//Create Orthographic Camera
	orthoCam = new Orthographic(
        windowWidth,                 
		windowHeight,                 
        -50.0f,                 
         50.0f,                 
        vec3(0.0, 0.0, 5.0),  
        vec3(0.0),             
        -1200.0f,                 
         1200.0f,                  
        -1200.0f,                
         1200.0f                  
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

	//ROD
	//Particle particle =  Particle();
	//particle.position = Vector(-150, -100, 0);
	//particle.mass = 10;
	//particle.radius = 50;
	//physWorld.addStaticParticle(&particle);
	//
	//Particle particle1 =  Particle();
	//particle1.position = Vector(-250, -100, 0);
	//particle1.mass = 10;
	//particle1.radius = 50;
	//physWorld.addStaticParticle(&particle1);
	//
	//Rod* rod = new Rod();
	//rod->particles[0] = &particle;
	//rod->particles[1] = &particle1;
	//rod->rodLength = 500;
	//physWorld.links.push_back(rod);

	for (int i = 0; i < 5; i++) {
		Particle* particle = new Particle();
		particle->position = Vector(i * 105, 400, 0);
		particle->mass = 50;
		particle->radius = 50;
		physWorld.addParticle(particle);
	
		Cable* cable = new Cable(100, 0, particle->position);
		cable->particles[0] = particle;
		cable->particles[1] = nullptr;
		physWorld.links.push_back(cable);
	}

	//////////////////////RENDER PARTICLE LIST//////////////////////
	list<RenderParticle*> renderParticles;

	for (int i = 0; i < allModels.size(); i++) {
		Vector newCol;
		vec3 col = (dynamic_cast<Object*>(allModels[i])->getColor());
		newCol.x = col.x;
		newCol.y = col.y;
		newCol.z = col.z;

		RenderParticle* renPar = new RenderParticle(physWorld.getParticleAtIndex(i), allModels[i], newCol);
		renderParticles.push_back(renPar);
	}

	//////////////////////MAIN LOOP//////////////////////
	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);
		//GETS CURRENT TIME
		currTime = clock::now();
		auto duration = chrono::duration_cast<chrono::nanoseconds> (currTime - prevTime);
		prevTime = currTime;

		checkInput();

		if (punched) {
			physWorld.getParticleAtIndex(0)->addForce(Vector(-0.8, 0, 0) * 1200);
			punched = false;
		}

		curr_ns += duration;
		if (curr_ns >= timestep) {
			auto ms = chrono::duration_cast<chrono::milliseconds>(curr_ns);
			//RESET
			curr_ns -= curr_ns;

			physWorld.update((float)ms.count() / 1000);
		}
		
		//All objects use the same shader anyway
		glUseProgram(allModels[0]->getShader().getShaderProg());
		orthoCam->draw(allModels[0]->getShader().getShaderProg());
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
	// Camera Switching
	//if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) camOn = ORTHOGRAPHIC;
	//if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) camOn = PERSPECTIVE;
	//// Pause / Play
	//if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && inputCooldown >= 1000) {
	//	play = !play;
	//	inputCooldown = 0;
	//}
	//// Camera Rotation
	//if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) { persCam->rotateWithKeys('W'); orthoCam->rotateWithKeys('W'); }
	//if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) { persCam->rotateWithKeys('S'); orthoCam->rotateWithKeys('S'); }
	//if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) { persCam->rotateWithKeys('A'); orthoCam->rotateWithKeys('A'); }
	//if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) { persCam->rotateWithKeys('D'); orthoCam->rotateWithKeys('D'); }
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) { punched = true; }
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