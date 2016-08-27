Texture2D Texture;
SamplerState ss;




float4 main() : SV_TARGET
{
	return float4(1.0f, 1.0f, 1.0f, 1.0f);
}



float4 main(float4 position : SV_POSITION, float2 texcoord : TEXCOORD) : SV_TARGET
{


	return Texture.Sample(ss, texcoord);
}