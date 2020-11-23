Texture2D tex;

SamplerState samplState;

float4 main(float2 uv : TEXCOORD0) : SV_TARGET
{
	return tex.Sample(samplState, uv);
}