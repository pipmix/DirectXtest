#include "Map.h"

Map::Map()
{
}

Map::~Map()
{

	delete r1, r2, r3, r4, r5, r6;
}

void Map::Draw(){
	r1->Draw();
	r2->Draw();
	r3->Draw();
	r4->Draw();
	r5->Draw();
	r6->Draw();
}

void Map::Update()
{
}

void Map::LoadMap() {

	r1 = new ShapeRectangle();
	r2 = new ShapeRectangle();
	r3 = new ShapeRectangle();
	r4 = new ShapeRectangle();
	r5 = new ShapeRectangle();
	r6 = new ShapeRectangle();

	r1->SetDepth(0.0f);
	r2->SetDepth(0.0f);
	r3->SetDepth(0.0f);
	r4->SetDepth(0.0f);
	r5->SetDepth(0.0f);
	r6->SetDepth(0.0f);

	r1->Create(0.0f, -5.0f, 6.0f, -10);
	r2->Create(6.0f, -3.0f, 9.0f, -10);
	r3->Create(10.0f, -6.0, 14.0f, -10);
	r4->Create(-10.0f, 11.0f, 22.0f, 2);
	r5->Create(7.0f, 15.0f, 9.0f, -10);
	r6->Create(-15.0f, 14.0, -1.0f, -3);

}
