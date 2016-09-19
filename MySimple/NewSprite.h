#pragma once
class SpriteMaterial
{
public:

	// ...

	void SetTexture(ID3D11DeviceContext* deviceContext, ID3D11ShaderResourceView* texture);
	void SetAtlasBuffer(ID3D11DeviceContext* deviceContext, float sliceWidth, float sliceHeight);
	void SetPerFrameBuffer(ID3D11DeviceContext* deviceContext, D3DXMATRIX view, D3DXMATRIX projection);
	void SetPerObjectBuffer(ID3D11DeviceContext* deviceContext, D3DXMATRIX world, int sliceIndex);

private:

	struct GridAtlasBuffer
	{
		float sliceWidth;
		float sliceHeight;
	};

	struct PerObjectBuffer
	{
		D3DXMATRIX world;
		int sliceIndex;
	};

	struct PerFrameBuffer
	{
		D3DXMATRIX view;
		D3DXMATRIX projection;
	};

	// ...

	ID3D11Buffer* mGridAtlasBuffer;
	ID3D11Buffer* mPerObjectBuffer;
	ID3D11Buffer* mPerFrameBuffer;
};