#include "Engine.h"

#include <GL\glew.h>

#include <SDL.h>
#include <SDL_opengl.h>
#include <stdio.h>
#include <gl\GLU.h>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtx\string_cast.hpp>

#include <iostream>
#include "ShaderLibrary.h"
#include "GLErrorLogger.h"
#include "Terrain.h"
#include "ZombieNode.h"
#include <vector>

//#define FPS_COUNT

Engine::Engine(Player* pl)
	: player(pl)
{ }

void Engine::Start()
{
	bool status = Init();
	// check whether the engine is initialized successfully if not, print an error message and quit

	if (!status)
	{
		printf("Fatal error when initializing engine! Quitting...\n");
		return;
	}

	// scene creation

	CreateScene();
	Update();
}

bool Engine::Init()
{
	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf(" could not be initialized!  Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

		

		/*SDL_DisplayMode dMode;
		SDL_GetCurrentDisplayMode(0, &dMode);
		printf("%d x %d\n", dMode.w, dMode.h);*/

		gWindow = SDL_CreateWindow("FPS Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 0, 0,
			SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_MAXIMIZED ); // SDL_WINDOW_MAXIMIZED

		/*int w, h;

		SDL_GetWindowSize(gWindow, &w, &h);
		printf("%d x %d\n", w, h);*/

		int w, h;
		SDL_GL_GetDrawableSize(gWindow, &w, &h);

		player->camera->SetProjectionMatrix(glm::radians(45.0f), w, h, 0.1f, 100.0f);
		
		SDL_SetRelativeMouseMode(SDL_TRUE);
		SDL_WarpMouseInWindow(gWindow, w / 2, h / 2);

		if (gWindow == NULL)
		{
			printf("Window creation error! SDL error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{

			SDL_GLContext gContext = SDL_GL_CreateContext(gWindow);
			if (gContext == NULL)
			{
				printf("OpenGL context cannot be created! SDL error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				if (SDL_GL_SetSwapInterval(1) < 0)
				{
					printf("Warning! Unable to set VSync. SDL error: %s\n", SDL_GetError());
				}

				if (!InitGL())
				{
					printf("Unable to inialize OpenGL!\n");
					success = false;
				}
			}
		}

		ShaderLibrary* shLib = ShaderLibrary::GetInstance();
		shLib->SetShaderPath("./shaders/");

		if (!shLib->LoadShaders())
		{
			printf("Error loading shaders!");
			success = false;
		}

		bulletEngine = new BulletEngine(250, 250);
	}

	return success;
}

bool Engine::InitGL()
{
	bool success = true;
	GLenum error = GL_NO_ERROR;

	glewInit();

	error = glGetError();
	if (error != GL_NO_ERROR)
	{
		success = false;
		printf("Error initializing OpenGL! %s\n", gluErrorString(error));
	}

	glClearColor(0.72f, 0.27f, 0.27f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//cubeShader.Load("cube_vertex.vert", "cube_fragment.frag");

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	return success;
}

void Engine::CreateScene()
{
	

	GroupNode* rootNode = new GroupNode("root");

	// add player node
	PlayerNode* pl = new PlayerNode(player);
	player->SetPlayerNode(pl);

	rootNode->AddNode(pl);

	//ModelNode* zombie = new ModelNode("zombie", "./models/zombie/zombie.obj");
	TransformNode* trZombie = new TransformNode("zombie_transf");
	trZombie->translateVector = glm::vec3(1.0f, -1.0f, 3.0f);
	trZombie->rotateVector2 = glm::vec3(1.0f, 0.0f, 0.0f);
	trZombie->rotateAngleRad2 = glm::radians(-90.0f);
	trZombie->rotateVector = glm::vec3(0.0f, 0.0f, 1.0f);
	trZombie->rotateAngleRad = glm::radians(-160.0f);
	trZombie->scaleVector = glm::vec3(0.12f, 0.12f, 0.12f);

	// create zombie node

	Zombie* zombie = new Zombie(trZombie, player, bulletEngine);
	ZombieNode* zombieNode = new ZombieNode(zombie);

	zombie->SetSceneNode(zombieNode);

	 zombies.push_back(zombie);

	

	ModelNode* crate = new ModelNode("crate", "./models/crate/Crate.obj");	
	crate->SetTexture("./models/crate/Textures/1024/A.png");


	ModelNode* crateNode = new ModelNode("crate", "./models/crate/Crate.obj");
	ModelNode* crateNode2 = new ModelNode("crate", "./models/tracks_obj/rail_straight.obj");

	TransformNode* trCrate = new TransformNode("crate_transf");
	TransformNode* trCrate2 = new TransformNode("crate_transf2");
	TransformNode* trCrate3 = new TransformNode("crate_transf3");
	TransformNode* trCrate4 = new TransformNode("crate_transf4");
	TransformNode* trCrate5 = new TransformNode("crate_transf5");
	TransformNode* trCrate6 = new TransformNode("crate_transf6");
	TransformNode* trCrate7 = new TransformNode("crate_transf7");
	TransformNode* trCrate8 = new TransformNode("crate_transf8");
	TransformNode* trCrate9 = new TransformNode("crate_transf9");
	TransformNode* trCrate10 = new TransformNode("crate_transf10");
	TransformNode* trCrate11 = new TransformNode("crate_transf11");
	TransformNode* trCrate12 = new TransformNode("crate_transf12");
	TransformNode* trCrate13 = new TransformNode("crate_transf13");
	TransformNode* trCrate14 = new TransformNode("crate_transf14");
	TransformNode* trCrate15 = new TransformNode("crate_transf15");
	TransformNode* trCrate16 = new TransformNode("crate_transf16");
	TransformNode* trCrate17 = new TransformNode("crate_transf17");
	TransformNode* trCrate18 = new TransformNode("crate_transf18");
	TransformNode* trCrate19 = new TransformNode("crate_transf19");
	TransformNode* trCrate20 = new TransformNode("crate_transf20");
	TransformNode* trCrate21 = new TransformNode("crate_transf21");
	TransformNode* trCrate22 = new TransformNode("crate_transf22");
	TransformNode* trCrate23 = new TransformNode("crate_transf23");
	TransformNode* trCrate24 = new TransformNode("crate_transf24");
	TransformNode* trCrate25 = new TransformNode("crate_transf25");
	TransformNode* trCrate26 = new TransformNode("crate_transf26");
	TransformNode* trCrate27 = new TransformNode("crate_transf27");
	TransformNode* trCrate28 = new TransformNode("crate_transf28");
	TransformNode* trCrate29 = new TransformNode("crate_transf29");
	TransformNode* trCrate30 = new TransformNode("crate_transf30");

	

	

	GroupNode* crates = new GroupNode("crates");

	ModelNode* building = new ModelNode("building");

	
	// create and position the crates

	

	//GroupNode* crates = new GroupNode("crates");
	//for(auto node : crateNodes){
	//	crates->AddNode(node);
	//}

	//rootNode->AddNode(crates);

	

	

	// add building to the scene

	

	

	

	trZombie->AddNode(zombieNode);

	// add crates



	// loading and adding the models to the scene graph
	float crateScaleFactor = 0.005f;
	float crateScaleFactor2 = 0.005f / 4;

	trCrate->translateVector = glm::vec3(3.0f, -1.0f, 10.0f);
	trCrate->scaleVector = glm::vec3(crateScaleFactor2, crateScaleFactor2, crateScaleFactor2);
	trCrate->AddNode(crate);

	trCrate2->translateVector = glm::vec3(3.0f, -1.0f, -5.0f);
	trCrate2->scaleVector = glm::vec3(crateScaleFactor/3, crateScaleFactor/3, crateScaleFactor/3);
	trCrate2->AddNode(crate);

	trCrate3->translateVector = glm::vec3(-4.0f, -1.0f, -6.0f);
	trCrate3->scaleVector = glm::vec3(crateScaleFactor2, crateScaleFactor2, crateScaleFactor2);
	trCrate3->AddNode(crate);

	trCrate4->translateVector = glm::vec3(0.0f, -1.0f, 12.0f);
	trCrate4->scaleVector = glm::vec3(crateScaleFactor2, crateScaleFactor2, crateScaleFactor2);
	trCrate4->AddNode(crate);

	float objectWidth = crateScaleFactor;


	trCrate5->translateVector = glm::vec3(19.0f, -1.0f, 0.0f);
	trCrate5->scaleVector = glm::vec3(crateScaleFactor*2, crateScaleFactor*2, crateScaleFactor*2);
	trCrate5->AddNode(crate);

	trCrate6->translateVector = glm::vec3(19.0f, -1.0f, 1.8f);
	trCrate6->scaleVector = glm::vec3(crateScaleFactor * 2, crateScaleFactor * 2, crateScaleFactor * 2);
	trCrate6->AddNode(crate);

	trCrate7->translateVector = glm::vec3(19.0f, -1.0f, 3.6f);
	trCrate7->scaleVector = glm::vec3(crateScaleFactor * 2, crateScaleFactor * 2, crateScaleFactor * 2);
	trCrate7->AddNode(crate);

	trCrate8->translateVector = glm::vec3(19.0f, -1.0f, 5.4f);
	trCrate8->scaleVector = glm::vec3(crateScaleFactor * 2, crateScaleFactor * 2, crateScaleFactor * 2);
	trCrate8->AddNode(crate);

	trCrate9->translateVector = glm::vec3(19.0f, -1.0f, 7.2f);
	trCrate9->scaleVector = glm::vec3(crateScaleFactor * 2, crateScaleFactor * 2, crateScaleFactor * 2);
	trCrate9->AddNode(crate);

	trCrate10->translateVector = glm::vec3(19.0f, -1.0f, 9.0f);
	trCrate10->scaleVector = glm::vec3(crateScaleFactor * 2, crateScaleFactor * 2, crateScaleFactor * 2);
	trCrate10->AddNode(crate);

	trCrate11->translateVector = glm::vec3(19.0f, 0.7f, 0.9f);
	trCrate11->scaleVector = glm::vec3(crateScaleFactor * 2, crateScaleFactor * 2, crateScaleFactor * 2);
	trCrate11->AddNode(crate);

	trCrate12->translateVector = glm::vec3(19.0f, 0.7f, 2.7f);
	trCrate12->scaleVector = glm::vec3(crateScaleFactor * 2, crateScaleFactor * 2, crateScaleFactor * 2);
	trCrate12->AddNode(crate);

	trCrate13->translateVector = glm::vec3(19.0f, 0.7f, 4.5f);
	trCrate13->scaleVector = glm::vec3(crateScaleFactor * 2, crateScaleFactor * 2, crateScaleFactor * 2);
	trCrate13->AddNode(crate);

	trCrate14->translateVector = glm::vec3(19.0f, 0.7f, 6.3f);
	trCrate14->scaleVector = glm::vec3(crateScaleFactor * 2, crateScaleFactor * 2, crateScaleFactor * 2);
	trCrate14->AddNode(crate);

	trCrate15->translateVector = glm::vec3(19.0f, 0.7f, 8.1f);
	trCrate15->scaleVector = glm::vec3(crateScaleFactor * 2, crateScaleFactor * 2, crateScaleFactor * 2);
	trCrate15->AddNode(crate);

	trCrate16->translateVector = glm::vec3(19.0f, 2.4f, 2.3f);
	trCrate16->scaleVector = glm::vec3(crateScaleFactor * 2, crateScaleFactor * 2, crateScaleFactor * 2);
	trCrate16->AddNode(crate);

	trCrate17->translateVector = glm::vec3(19.0f, 2.4f, 4.1f);
	trCrate17->scaleVector = glm::vec3(crateScaleFactor * 2, crateScaleFactor * 2, crateScaleFactor * 2);
	trCrate17->AddNode(crate);

	trCrate18->translateVector = glm::vec3(19.0f, 2.4f, 5.9f);
	trCrate18->scaleVector = glm::vec3(crateScaleFactor * 2, crateScaleFactor * 2, crateScaleFactor * 2);
	trCrate18->AddNode(crate);

	trCrate19->translateVector = glm::vec3(19.0f, 4.0f, 3.2f);
	trCrate19->scaleVector = glm::vec3(crateScaleFactor * 2, crateScaleFactor * 2, crateScaleFactor * 2);
	trCrate19->AddNode(crate);

	trCrate20->translateVector = glm::vec3(19.0f, 4.0f, 5.0f);
	trCrate20->scaleVector = glm::vec3(crateScaleFactor * 2, crateScaleFactor * 2, crateScaleFactor * 2);
	trCrate20->AddNode(crate);

	trCrate21->translateVector = glm::vec3(19.0f, 5.6f, 3.8f);
	trCrate21->scaleVector = glm::vec3(crateScaleFactor * 2, crateScaleFactor * 2, crateScaleFactor * 2);
	trCrate21->AddNode(crate);

	// place the crates in the scene between the terrain
	trCrate22->translateVector = glm::vec3(-2.0f, -1.0f, 4.0f);
	trCrate22->scaleVector = glm::vec3(crateScaleFactor2, crateScaleFactor2, crateScaleFactor2);
	trCrate22->AddNode(crate);

	trCrate23->translateVector = glm::vec3(9.0f, -1.0f, 5.0f);
	trCrate23->scaleVector = glm::vec3(crateScaleFactor2, crateScaleFactor2, crateScaleFactor2);
	trCrate23->AddNode(crate);

	trCrate24->translateVector = glm::vec3(3.0f, -1.0f, 6.0f);
	trCrate24->scaleVector = glm::vec3(crateScaleFactor2, crateScaleFactor2, crateScaleFactor2);
	trCrate24->AddNode(crate);

	trCrate25->translateVector = glm::vec3(-5.0f, -1.0f, 7.0f);
	trCrate25->scaleVector = glm::vec3(crateScaleFactor2, crateScaleFactor2, crateScaleFactor2);
	trCrate25->AddNode(crate);

	trCrate26->translateVector = glm::vec3(-7.0f, -1.0f, 8.0f);
	trCrate26->scaleVector = glm::vec3(crateScaleFactor2, crateScaleFactor2, crateScaleFactor2);	
	trCrate26->AddNode(crate);

	trCrate27->translateVector = glm::vec3(-2.0f, -1.0f, -4.0f);
	trCrate27->scaleVector = glm::vec3(crateScaleFactor2, crateScaleFactor2, crateScaleFactor2);
	trCrate27->AddNode(crate);

	trCrate28->translateVector = glm::vec3(9.0f, -1.0f, -8.0f);
	trCrate28->scaleVector = glm::vec3(crateScaleFactor2, crateScaleFactor2, crateScaleFactor2);
	trCrate28->AddNode(crate);

	trCrate29->translateVector = glm::vec3(3.0f, -1.0f, -9.0f);
	trCrate29->scaleVector = glm::vec3(crateScaleFactor2, crateScaleFactor2, crateScaleFactor2);
	trCrate29->AddNode(crate);

	trCrate30->translateVector = glm::vec3(-5.0f, -1.0f, -2.0f);
	trCrate30->scaleVector = glm::vec3(crateScaleFactor2, crateScaleFactor2, crateScaleFactor2);

	trCrate30->AddNode(crate);









	

	

	crates->AddNode(trCrate);
	crates->AddNode(trCrate2);
	crates->AddNode(trCrate3);
	crates->AddNode(trCrate4);
	crates->AddNode(trCrate5);
	crates->AddNode(trCrate6);
	crates->AddNode(trCrate7);
	crates->AddNode(trCrate8);
	crates->AddNode(trCrate9);
	crates->AddNode(trCrate10);
	crates->AddNode(trCrate11);
	crates->AddNode(trCrate12);
	crates->AddNode(trCrate13);
	crates->AddNode(trCrate14);
	crates->AddNode(trCrate15);
	crates->AddNode(trCrate16);
	crates->AddNode(trCrate17);
	crates->AddNode(trCrate18);
	crates->AddNode(trCrate19);
	crates->AddNode(trCrate20);
	crates->AddNode(trCrate21);
	crates->AddNode(trCrate22);
	crates->AddNode(trCrate23);
	crates->AddNode(trCrate24);
	crates->AddNode(trCrate25);
	crates->AddNode(trCrate26);
	crates->AddNode(trCrate27);
	crates->AddNode(trCrate28);
	crates->AddNode(trCrate29);
	crates->AddNode(trCrate30);





	Terrain* terrain = new Terrain(glm::vec2(-20, -20), 40);
	//Terrain* terrain = new Terrain(glm::vec2(0, 0), 2);

	rootNode->AddNode(terrain);
	rootNode->AddNode(trZombie);
	rootNode->AddNode(crates);

	

	//cubeDeb = cube;

	// this is skybox node

	skybox = new CubemapNode("./skybox/top.jpg", "./skybox/left.jpg", "./skybox/right.jpg", "./skybox/bottom.jpg", "./skybox/front.jpg", "./skybox/back.jpg");
	hudRenderer = new HUDRenderer(player);

	zombies.push_back(zombie);
}

void Engine::Update()
{
	SDL_Event e;

	float startTime = SDL_GetTicks() / 1000.0f;
	int frames = 0;

	bool quit = false;
	while (!quit)
	{
		float currentFrame = SDL_GetTicks() / 1000.0f;
		frames++;

		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

#ifdef FPS_COUNT
		if (currentFrame - startTime >= 1.0)
		{
			printf("%f ms/frame\n", 1000.0f / float(frames));
			frames = 0;
			startTime += 1.0f;
		}
#endif
		while (SDL_PollEvent(&e) != 0)
		{
			switch (e.type)
			{
			case SDL_QUIT:
				quit = true;
				break;
			case SDL_MOUSEMOTION:
				currentMouseX = e.motion.x;
				currentMouseY = e.motion.y;
				HandleMouseMotion(e.motion);
				
				SDL_WarpMouseInWindow(gWindow, 500, 500);
				break;
			case SDL_MOUSEBUTTONDOWN:
				HandleMouseClick(e.button);
				break;
			}
		}

		int count;

		const Uint8* keystates = SDL_GetKeyboardState(&count);
		HandleKeyDown(keystates);

		UpdateActions(); 

		Render();

		SDL_GL_SwapWindow(gWindow);
	}

	// close();
}

void Engine::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::mat4 view = player->camera->GetViewMatrix();
	glm::mat4 proj = player->camera->GetProjectionMatrix();

	ShaderLibrary::GetInstance()->SetPVGlobal(proj, view);
	ShaderLibrary::GetInstance()->SetGlobalLight(glm::vec3(-100.0f, 100.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), player->camera->pos);
	//Shader* objectShader = ShaderLibrary::GetInstance()->GetShader("object_shader");
	//cout<<objectShader->ID<<endl;
	//objectShader->use();
	//objectShader->setVec3("fogColor", 0.7f, 0.8f, 1.0f); // Example: light blue fog
	//objectShader->setFloat("fogStart", 10.0f);
	//objectShader->setFloat("fogEnd", 50.0f);

	skybox->Visualize();
	SceneGraph->Visualize(glm::mat4(1.0f));
	bulletEngine->Visualize();
	hudRenderer->Visualize();
}

void Engine::HandleKeyDown(const Uint8* keystates)
{
	if (keystates[SDL_GetScancodeFromKey(SDLK_w)])
	{
		// move forward
		actionVector.z += 1.0f;
	}
	if (keystates[SDL_GetScancodeFromKey(SDLK_s)])
	{
		// move backward
		actionVector.z -= 1.0f;
	}
	if (keystates[SDL_GetScancodeFromKey(SDLK_a)])
	{
		// move left
		actionVector.x -= 1.0f;
	}
	if (keystates[SDL_GetScancodeFromKey(SDLK_d)])
	{
		// move right
		actionVector.x += 1.0f;
	}
	if (keystates[SDL_GetScancodeFromKey(SDLK_SPACE)])
	{
		// jump
		actionVector.y += 1.0f;
	}
	if (keystates[SDL_GetScancodeFromKey(SDLK_ESCAPE)])
	{
		Close();
	}
}

void Engine::UpdateActions()
{
	if (firstStart)
	{

		firstStart = false;
		return;
	}

	player->Move(actionVector, deltaTime);
	if (actionVector.y == 1.0f)
		player->Jump();

	actionVector = glm::vec3(0.0f);

	player->UpdateGravity(deltaTime); 
	for (auto it = zombies.begin(); it != zombies.end(); ++it)
	{
		(*it)->Update(deltaTime);
	}

	bulletEngine->Update(deltaTime);

	for (auto it = zombies.begin(); it != zombies.end(); ++it)
	{
		(*it)->Update(deltaTime);
	}
}

void Engine::HandleMouseMotion(const SDL_MouseMotionEvent& motion)
{
	// player look around with the mouse motion when it is moved
	player->Look(glm::vec2(motion.xrel, motion.yrel));
}

void Engine::HandleMouseClick(const SDL_MouseButtonEvent& button)
{
	if (button.clicks != 1)
		// if the button is not clicked once,
		return;

	switch (button.button)
	{
	case SDL_BUTTON_LEFT:
		// shoot
		player->Shoot(bulletEngine);
		break;
	case SDL_BUTTON_RIGHT:
		break;
	}
}

void Engine::Close()
{
	// close the window
	ShaderLibrary::GetInstance()->UnloadShaders();
	// close program..
	exit(0);
}