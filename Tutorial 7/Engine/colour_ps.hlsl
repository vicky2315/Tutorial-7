// Colour pixel/fragment shader
// Basic fragment shader outputting a colour
Texture2D<float4> Texture : register(t1);
sampler TextureSampler : register(s1);

cbuffer ColorBuffer : register(b1)
{
    float4 Colour;
    float2 Coord;
}

float4 main(float4 color : COLOR0, float2 texCoord : TEXCOORD0) : SV_Target0
{
    float4 greycolor;
    float greyscaleAverage = (color.r + color.g + color.b) / 3.0f;
    greycolor = float4(greyscaleAverage, greyscaleAverage, greyscaleAverage, color.a);
	
    return greycolor;
}