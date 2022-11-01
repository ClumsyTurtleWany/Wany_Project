// �ȼ� ���� ȣ��ȴ�.
// �ش� �ȼ��� �÷��� SV_Target �������Ϳ� ��ȯ �Ѵ�.
// Rasterizer(== Pixel) Stage ���� PixelShader ȣ�� �� Ƚ���� ����.

Texture2D		g_txTextureA		: register(t0); // register�� �� �ٿ��ָ� �⺻������ 0�� �������Ϳ� ��.
Texture2D		g_txTextureMaskA	: register(t1); // register�� �� �ٿ��ָ� �⺻������ 0�� �������Ϳ� ��.
SamplerState	g_SampleA			: register(s0); // ���ø��� �Ϸ��� ���÷��� �ʿ���

struct PixelShader_input
{
	float4 p : SV_POSITION;
	float3 n : NORMAL;
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
		discard; // ���� ������ �ƴϴ�.
	}
	return vFinalColor;
}
