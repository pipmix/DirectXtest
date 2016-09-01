#include "Object.h"

Object::Object()
{
}

void Object::Update()
{

	dy += GRAV;

	x += dx;
	y += dy;
}

void Object::Draw()
{


}
