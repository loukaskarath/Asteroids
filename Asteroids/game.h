#pragma once
#include "spaceship.h"
#include "Meteorite.h"
#include "laser.h"


class Game {
	Spaceship* spaceship = nullptr;
	Meteorite* meteorite = nullptr;
	Laser* laserbeam = nullptr;
	int count = 0;
	bool new_spaceship = false;
	bool debug_mode = false;
	bool active_game = true;
	void spawnMeteorite();
	void checkMeteorite();
	bool checkCollision();
	void spawnLaserBeam();
public:
	void setDebugMode(bool d) { debug_mode = d; }
	bool getDebugMode() const { return debug_mode; }
	void update();
	void draw();
	void init(); //initialize data
	Game(); //constructor
	~Game(); //destructor
};