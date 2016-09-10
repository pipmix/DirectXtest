#ifndef SHAPE_H
#define SHAPE_H
#include "Headers.h"
#include "DataTypes.h"
#include "Helpers.h"
#include "Camera.h"
#include "Data.h"

extern ComPtr<ID3D11Device>			device;
extern ComPtr<ID3D11DeviceContext>	context;

extern ComPtr<ID3D11Buffer> constantBuffer_finalMatrix;
extern Camera* camera;
extern HWND hWnd;
extern HINSTANCE hInst;
extern Data* dat;

class Shape {

public:

	
	void Draw();
	void Update();


protected:
	//ComPtr<ID3D11VertexShader>	_vertexShader;
	//ComPtr<ID3D11PixelShader>	_pixelShader;
	ComPtr<ID3D11Buffer>		_vertexBuffer;
	PixelShader* ps;
	VertexShader* vs;
	//ComPtr<ID3D11InputLayout>	_inputLayout;
	UINT						_numElements;
	bool _Init = 0;


};

class ShapeRectangle : public Shape {

public:
			ShapeRectangle();
			void Create(float left, float top, float right, float bottom);
			void SetDepth(float z);
			XMFLOAT4 GetCollision();

private:
			float _left, _top, _right, _bottom, _depth;
			XMFLOAT4 _collision;


};

class ShapeCircle {

public:
	ShapeCircle();



};

class ShapeLine {

public:
	ShapeLine();



};

class ShapePoint {
public:
	ShapePoint();
	void Create(float x, float y, float z);
private:
	XMFLOAT3 _position;
};

class LineShape3d : Shape {

public:
	LineShape3d();
	void Create();
	void Draw();


};





#endif // SHAPE_H