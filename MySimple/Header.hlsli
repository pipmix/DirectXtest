cbuffer constantBufferFinalMatrix :register(b0) {
	matrix finalMatrix;
};

cbuffer cBufferFramePS : register(b1) {
	float2 spos;
};




Texture2D Texture : register(t0);
SamplerState ss : register(s0);
