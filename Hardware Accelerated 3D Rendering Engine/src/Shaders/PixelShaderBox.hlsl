cbuffer Cbuf {
	float4 colors[6];
};

float4 main(uint PrimitiveID : SV_PrimitiveID) : SV_TARGET
{
	return colors[PrimitiveID / 2];
}