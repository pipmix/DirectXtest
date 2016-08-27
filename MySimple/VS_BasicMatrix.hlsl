
cbuffer ConstantBuffer : register(b0)
{
	matrix world;
	matrix camera;
	matrix screen;
}





struct VOut {

	float4 position : SV_POSITION;

};








VOut main( float4 pos : POSITION ) : SV_POSITION
{



	VOut output;




	output.position = mul(pos, world);
	output.position = mul(output.position, camera);
	output.position = mul(output.position, screen);

	return output;


}