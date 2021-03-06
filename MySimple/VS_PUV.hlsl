#include "Header.hlsli"


struct VS_IN {

	float4 pos : POSITION;
	float2 texcoord : TEXCOORD;

};

struct VS_OUT {

	float4 pos : SV_POSITION;
	float2 texcoord: TEXCOORD;      

};



VS_OUT main(VS_IN vs_in)
{


	VS_OUT vs_out;

	vs_out.pos = mul(finalMatrix, vs_in.pos);
	//vs_out.pos = mul(vs_in.pos, finalMatrix);

	vs_out.texcoord = vs_in.texcoord;

	return vs_out;


}