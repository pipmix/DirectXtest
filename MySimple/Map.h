#pragma once
#include "Shape.h"

using namespace std;

class Map {

public:

	Map();
	~Map();

	void Draw();
	void Update();

	void LoadMap();



	ShapeRectangle* r1;
	ShapeRectangle* r2;
	ShapeRectangle* r3;
	ShapeRectangle* r4;
	ShapeRectangle* r5;
	ShapeRectangle* r6;




};