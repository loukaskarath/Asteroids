#include "game.h"
#include "graphics.h"
#include "config.h"

void Game::spawnMeteorite()
{
	if (!meteorite)
	{
		meteorite = new Meteorite(*this);
	}
}

void Game::spawnLaserBeam()
{
	if (!laserbeam)
	{
		laserbeam = new Laser(*this);
	}

}



void Game::checkMeteorite()
{
	if (meteorite && !meteorite->isActive())
	{
		delete meteorite;
		meteorite = nullptr;
	}
}

bool Game::checkCollision()
{
	if (!spaceship || !meteorite)
	{
		return false;
	}
	Disk d1 = spaceship->getCollisionHull();
	Disk d2 = meteorite->getCollisionHull();
	Disk l1 = laserbeam->getCollisionHull();

	float dx = d1.cx - d2.cx;
	float dy = d1.cy - d2.cy;

	float lx = l1.cx - d2.cx;
	float ly = l1.cy - d2.cy;

	if (sqrt(lx * lx + ly * ly) < l1.radius + d2.radius)
	{
		return true;
	} 
	else if (sqrt(dx * dx + dy * dy) < d1.radius + d2.radius)
	{
		spaceship->drainLife(0.2f);
		if (spaceship->getRemainingLife() == 0.0f)
		{
			delete spaceship;
			spaceship = nullptr;
			delete laserbeam;
			laserbeam = nullptr;
			active_game = false;

		}
		return true;
	}
	else {
		return false;
	}
}

void Game::update()
{
	if (!new_spaceship && graphics::getGlobalTime() > 00)
	{
		spaceship = new Spaceship(*this);
		laserbeam = new Laser(*this);
		new_spaceship = true;
	}

	graphics::Brush br;
	if (!active_game) {
		graphics::drawText(CANVAS_WIDTH / 2 - 80, CANVAS_HEIGHT / 2, 100, "END", br);
	}

	
	if (spaceship)
		spaceship->update();

	checkMeteorite();
	spawnMeteorite();

	if (meteorite)
		meteorite->update();

	if (laserbeam)
		laserbeam->update();

	spawnLaserBeam();

	//In case of a Collision
	if (checkCollision())
	{
		count++;
		//if a collision happens destroy both the meteorite and the laserbeam
		delete meteorite;
		meteorite = nullptr;
		delete laserbeam;
		laserbeam = nullptr;

		graphics::Brush br;


	}
}

void Game::draw()
{
	graphics::Brush br;
	br.texture = std::string(ASSET_PATH) + "space.png";
	br.outline_opacity = 0.0f;


	//draw background
	graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);

	//draw spaceship
	if (spaceship)
		spaceship->draw();

	//draw laserbeam
	if (laserbeam)
		laserbeam->draw();

	//draw meteorite
	if (meteorite)
	    meteorite->draw();

	//design lifebar
	float player_life = spaceship ? spaceship->getRemainingLife() : 0.0f;
	br.outline_opacity = 0.0f;
	br.fill_color[0] = 1.0f;
	br.fill_color[1] = 0.2f;
	br.fill_color[2] = 0.2f;
	br.texture = "";
	br.fill_secondary_color[0] = 0.2f;
	br.fill_secondary_color[1] = 0.2f;
	br.fill_secondary_color[2] = 1.0f;
	br.gradient = true;
	br.gradient_dir_u = 1.0f;
	br.gradient_dir_v = 0.0f;
	graphics::drawRect(CANVAS_WIDTH - 100 - ((1.0f - player_life) * 120 / 2), 30, player_life * 120, 20, br);

	br.outline_opacity = 1.0f;
	br.gradient = false;
	br.fill_opacity = 0.0f;
	graphics::drawRect(CANVAS_WIDTH - 100 - ((1.0f - player_life) * 120 / 2), 30, player_life * 120, 20, br);



	if (spaceship)
	{
		char info[40];
		sprintf_s(info, "(%6.2f, %6.2f)", spaceship->getPosX(), spaceship->getPosY());
		graphics::drawText(520, 520, 40, info, br);
	}
}

void Game::init()
{
	graphics::setFont(std::string(ASSET_PATH) + "bitstream.ttf");
	graphics::playMusic(std::string(ASSET_PATH) + "outter_space.mp3", 0.2f, true);
}

Game::Game()
{
}

Game::~Game()
{
	if (spaceship && laserbeam)
	{
		delete spaceship;
		delete laserbeam;
		delete meteorite;
	}

}
