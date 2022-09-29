#include "sgg/graphics.h"
#include "defines.h"
#include <string>
#include "game.h"

void draw()
{
	Game* mygame = Game::getInstance();
	mygame->draw();
}

void update(float ms)
{
	Game* mygame = Game::getInstance();
	mygame->update();
	if (mygame->gameIsOver() && mygame->quit()) 
	{
		graphics::stopMessageLoop();
	}	//Game::releaseInstance();
	if (mygame->gameIsOver() && mygame->RestartGame())
	{
		Game::releaseInstance();
	}
}

int main(int argc, char** argv)
{
	graphics::createWindow(1200, 800, "Strategy Game");

	Game* game = Game::getInstance();


	graphics::setCanvasSize(CANVAS_WIDTH, CANVAS_HEIGHT);
	graphics::setCanvasScaleMode(graphics::CANVAS_SCALE_FIT);

	graphics::setDrawFunction(draw);
	graphics::setUpdateFunction(update);

	graphics::startMessageLoop();

	Game::releaseInstance();

	

	return 0;
}