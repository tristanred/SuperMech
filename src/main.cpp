#include <stdio.h>

#include <GameEngine.h>

int main(int argc, char** argv)
{
	GameEngine* eng = new GameEngine();
	eng->Initialize();

	eng->Play();

	printf("Super Mech !");

	return 0;
}