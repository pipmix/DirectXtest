#include "UI.h"

UI::UI()
{
}

void UI::Initialize()
{

	D3D11_BUFFER_DESC vbd = { 0 };
	vbd.Usage = D3D11_USAGE_DYNAMIC;
	vbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	//vbd.ByteWidth = sizeof(VertexPU) * maxBatch * vertsPerSprite;
	device->CreateBuffer(&vbd, nullptr, &m_vertexBuffer);

}
