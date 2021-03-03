#include "Meteorite.h"
#include "graphics.h"
#include "config.h"
#include "game.h"
#include "func.h"
#include <random>

void Meteorite::update()
{
	pos_x -= 1.5f * speed * graphics::getDeltaTime();
	rotation += 0.1f * graphics::getDeltaTime();
	rotation = fmodf(rotation, 360);

	if (pos_x < -size)
	{
		active = false;
	}
}

void Meteorite::draw()
{
	graphics::setOrientation(rotation);
	brush.texture = brush.texture = std::string(ASSET_PATH) + "meteorite.png";
	brush.fill_opacity = 1.0f;
	graphics::drawRect(pos_x, pos_y, size, size, brush);
	graphics::resetPose(); //otan xrisimopoiw to setOrientation sto telos panta to anairw me to resetPose();

	if (game.getDebugMode())
	{
		brush.outline_opacity = 1.0f;
		brush.texture = "";
		brush.fill_color[0] = 1.0f;
		brush.fill_color[1] = 0.3f;
		brush.fill_color[2] = 0.3f;
		brush.gradient = false;
		Disk hull = getCollisionHull();
		graphics::drawDisk(hull.cx, hull.cy, hull.radius, brush);
	}
}

void Meteorite::init()
{
	speed = 0.3f;
	pos_x = CANVAS_WIDTH + 1.1f * size; //arxikh thesi meteoriti ektos othonis paixnidiou
	pos_y = CANVAS_HEIGHT * rand0to1();
	size = 50 + 100 * rand0to1();
	rotation = 360 * rand0to1();
	brush.outline_opacity = 0.0f;
}

Meteorite::Meteorite(const Game& mygame)
	:GameObject(mygame)
{
	init();
}

Meteorite::~Meteorite()
{
}

Disk Meteorite::getCollisionHull() const
{
	Disk disk;
	disk.cx = pos_x;
	disk.cy = pos_y;
	disk.radius = size*0.45f;
	return disk;
}