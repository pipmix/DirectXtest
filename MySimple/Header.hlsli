cbuffer constantBufferFinalMatrix :register(b0) {
	matrix finalMatrix;
};

cbuffer cBufferFramePS : register(b1) {
	float2 spos;
	float2 pad;
};

cbuffer ScreenSizeBuffer : register(b2) {
	float screenWidth;
	float3 padding;
};




Texture2D Texture : register(t0);
SamplerState ss : register(s0);
