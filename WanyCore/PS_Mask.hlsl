// 픽셀 마다 호출된다.
// 해당 픽셀의 컬러를 SV_Target 레지스터에 반환 한다.
// Rasterizer(== Pixel) Stage 에서 PixelShader 호출 할 횟수를 결정.

Texture2D		g_txTextureA		: register(t0); // register를 안 붙여주면 기본적으로 0번 레지스터에 들어감.
Texture2D		g_txTextureMaskA	: register(t1); // register를 안 붙여주면 기본적으로 0번 레지스터에 들어감.
SamplerState	g_SampleA			: register(s0); // 샘플링을 하려면 샘플러가 필요함

struct PixelShader_input
{
	float4 p : SV_POSITION;
	float4 c : COLOR0;
	float2 t : TEXCOORD0;
};


float4 PS(PixelShader_input _input) : SV_Target
{
	float4 vColor = g_txTextureA.Sample(g_SampleA, _input.t);
	float4 vMask = g_txTextureMaskA.Sample(g_SampleA, _input.t);
	float4 vFinalColor = vColor;
	if (vMask.r > 0.5f)
	{
		discard; // 투명도 조절은 아니다.
	}
	return vFinalColor;
}
