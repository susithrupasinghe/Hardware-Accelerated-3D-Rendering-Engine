cbuffer CBuf
{
	float4x4 transformationMatrix;
}

struct VSOut
{
	float3 normal : NORMAL;
	float2 uv : TEXCOORD;
	float4 pos : SV_POSITION;
};

VSOut main(float3 pos : POSITION, float3 normal : NORMAL, float2 uv : TEXCOORD)
{
	VSOut o;
	o.pos = mul(float4(pos, 1.0f), transformationMatrix);
	o.normal = normal;
	o.uv = uv;
	return o;
}