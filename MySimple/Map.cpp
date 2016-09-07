#include "Map.h"

Map::Map()
{
}

Map::~Map()
{

	delete r1, r2, r3;
}

void Map::Draw(){
	r1->Draw();
	r2->Draw();
	r3->Draw();
}

void Map::Update()
{
}

void Map::LoadMap() {

r1 = new ShapeRectangle(RectF{ 1.0f, 2, 6.0f, -6 });
r2 = new ShapeRectangle(RectF{ 2, 1, 10, 7 });
r3 = new ShapeRectangle(RectF{ 3, -1, 12, -10 });

}
