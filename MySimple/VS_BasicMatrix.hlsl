cbuffer constantBufferFinalMatrix : register(b0) {
	matrix finalMatrix;
};


struct VS_IN {

	float4 pos : POSITION;

};

struct VS_OUT {

	float4 pos : SV_POSITION;

};



VS_OUT main(VS_IN vs_in)
{


	VS_OUT vs_out;
	
	vs_out.pos = mul(finalMatrix, vs_in.pos );
	//vs_out.pos = mul(vs_in.pos, finalMatrix);

	return vs_out;


}