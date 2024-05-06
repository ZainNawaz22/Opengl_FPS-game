#include "Camera.h"
#include "Player.h"
#include "Engine.h"


int main(int argc, char* argv[])
{
	
	Camera* cam = new Camera();
	
	Player* player = new Player(cam);
	Engine* engine = new Engine(player);

	engine->Start();

	return 0;
}