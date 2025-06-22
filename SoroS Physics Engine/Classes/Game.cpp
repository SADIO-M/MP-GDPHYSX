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
	Vector myVecScale(10, 10, 10);
	Vector myVecRot(0, 0, 0);
	Vector color1(0.8f, 0.7f, 0.0f);
	Vector color2(0.0f, 0.5f, 0.8f);
	Vector color3(0.5f, 0.1f, 0.4f);
	Vector color4(1.0f, 0.0f, 0.0f);
	
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

		//2
	allModels.push_back(new Object(
		"3D/sphere.obj",
		(vec3)defaultPos,
		(vec3)myVecScale,
		(vec3)myVecRot,
		"Shaders/ObjectShader.vert",
		"Shaders/ObjectShader.frag",
		(vec3)color2
	));

		//3
	allModels.push_back(new Object(
		"3D/sphere.obj",
		(vec3)defaultPos,
		(vec3)myVecScale,
		(vec3)myVecRot,
		"Shaders/ObjectShader.vert",
		"Shaders/ObjectShader.frag",
		(vec3)color3
	));

		//4
	allModels.push_back(new Object(
		"3D/sphere.obj",
		(vec3)defaultPos,
		(vec3)myVecScale,
		(vec3)myVecRot,
		"Shaders/ObjectShader.vert",
		"Shaders/ObjectShader.frag",
		(vec3)color4
	));

	//Create Orthographic Camera
	orthoCam = new Orthographic(
        windowWidth,                 
		windowHeight,                 
        -50.0f,                 
         50.0f,                 
        vec3(0.0, 0.0, 5.0),  
        vec3(0.0),             
        -800.0f,                 
         800.0f,                  
        -800.0f,                
         800.0f                  
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

	//////DRAG FORCE//////
	//DragForceGenerator drag = DragForceGenerator(0.14f, 0.1f);
	//DragForceGenerator drag = DragForceGenerator();
	
	//////////////////////FOUR PARTICLES//////////////////////
	Particle particle1 = Particle();
	particle1.position = Vector(-110, 0, 0);

	Particle particle2 = Particle();
	particle2.position = Vector(-75, -75, 0);
	
	Particle particle3 = Particle();
	particle3.position = Vector(75, -75, 0);
	
	Particle particle4 = Particle();
	particle4.position = Vector(-75, 75, 0);
	
	PhysicsWorld physWorld = PhysicsWorld();
	physWorld.addParticle(&particle1);
	physWorld.addParticle(&particle2);
	physWorld.addParticle(&particle3);
	physWorld.addParticle(&particle4);
	//only particle 1 has drag applied
	//physWorld.forceRegistry.add(&particle1, &drag);

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

		//STOP RENDERING OBJECT IF AT CENTER
		//for (list<Particle*>::iterator p = physWorld.getParticleList()->begin(); p != physWorld.getParticleList()->end(); p++) {
		//	if ((*p)->atCenter()) (*p)->Destroy();
		//}

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