#pragma once
#include "Headers.h"
#include "Data.h"

extern ComPtr<ID3D11Device>			device;
extern ComPtr<ID3D11DeviceContext>	context;
extern Data dat;

class UI {

public:
	UI();
	void Initialize();

private:
	ComPtr<ID3D11Buffer>		m_indexBuffer;
	ComPtr<ID3D11Buffer>		m_vertexBuffer;
	ComPtr<ID3D11InputLayout>	m_inputLayout;
	size_t						m_vbPosition;

	std::vector<int>			m_indices;
	UINT vsIndex;
	UINT psIndex;

};


