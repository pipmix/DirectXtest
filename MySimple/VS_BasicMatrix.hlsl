struct VS_IN {

	float4 pos : POSITION;

};

struct VS_OUT {

	float4 pos : SV_POSITION;

};



VS_OUT main(VS_IN vs_in)
{


	VS_OUT vs_out;
	

	vs_out.pos = vs_in.pos;

	return vs_out;


}