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

	r1 = new ShapeRectangle();
	r2 = new ShapeRectangle();
	r3 = new ShapeRectangle();

	r1->SetDepth(-0.1f);
	r2->SetDepth(-0.1f);
	r3->SetDepth(-0.1f);

	r1->Create(0.0f, -5.0f, 6.0f, -10);
	r2->Create(6.0f, -3.0f, 9.0f, -10);
	r3->Create(10.0f, -6.0, 14.0f, -10);

}
