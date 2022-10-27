// 픽셀 마다 호출된다.
// 해당 픽셀의 컬러를 SV_Target 레지스터에 반환 한다.
// Rasterizer(== Pixel) Stage 에서 PixelShader 호출 할 횟수를 결정.

struct PixelShader_input
{
	float4 p : SV_POSITION;
	float4 c : COLOR0;
	float2 t : TEXCOORD0;
};

float4 PS(PixelShader_input _input) : SV_Target
{
	return _input.c;
}