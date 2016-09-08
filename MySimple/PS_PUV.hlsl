Texture2D Texture : register(t0);
SamplerState ss : register(s0);

cbuffer cBufferFramePS : register(b1) {
	float2 spos;
};





float4 main(float4 position : SV_POSITION, float2 texcoord : TEXCOORD) : SV_TARGET
{

	return  Texture.Sample(ss, texcoord);
}

//output.pos.x = (input.pos.x / (g_viewportWidth / 2.0)) - 1;
//output.pos.y = -(input.pos.y / (g_viewportHeight / 2.0)) + 1;
//output.pos.z = input.pos.z;
//output.pos.w = 1;