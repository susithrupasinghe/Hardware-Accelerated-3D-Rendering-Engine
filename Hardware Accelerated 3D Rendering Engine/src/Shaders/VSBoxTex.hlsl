cbuffer CBuf {
	matrix transformMatrix;
};

struct VSOut {
	float2 uv : TEXCOORD0;
	float4 position : SV_POSITION;
};

VSOut main( float3 pos : POSITION, float2 uv : TEXCOORD )
{
	VSOut o;
	o.uv = uv;
	o.position = mul(float4(pos, 1.0f), transformMatrix);
	return o;
}