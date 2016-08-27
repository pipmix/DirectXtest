
cbuffer ConstantBuffer : register(b0)
{
	matrix world;
	matrix camera;
	matrix screen;

}





struct VOut {

	float4 p : SV_POSITION;

};



VOut main( float4 pos : POSITION ) : SV_POSITION
{



	VOut output;

	output.p = mul(world, pos);

	return output;


}