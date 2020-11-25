Texture2D tex;

SamplerState samplState;

float4 main(float3 normal : NORMAL, float2 uv : TEXCOORD) : SV_TARGET
{
	return tex.Sample(samplState, uv);
}