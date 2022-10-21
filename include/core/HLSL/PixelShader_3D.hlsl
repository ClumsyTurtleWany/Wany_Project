//float4 main() : SV_TARGET
//{
//	return float4(1.0f, 1.0f, 1.0f, 1.0f);
//}


// VertexShader.txt, PixelShader.txt ���� �������� �ʰ� �ϳ��� ���Ͽ� ���ĳ��Ƶ� �ȴ�.


// HLSL (High Level Shader Language)
// �������̴��� ���� ���ۿ� �ִ� ��� ������ 1���� �۾��Ѵ�.
// ���� ��ġ(SV_POSITION : System Value Position ��������)�� �ݵ�� float4�� ��ȯ�ؾ� �Ѵ�.
// SV_POSITION(�ø�ƽ : �ǹ� ����) �ý��ۻ� �����Ǿ� ����. COLOR0 �� COLOR1 � ����.

// float3 p : POSITION ���� POSITION�� Sample.hpp->CreateVertexLayout->InputElementDescs �� ��� �̸��� ���ƾ���. 
// ���������� ���°� �ƴ϶� �׳� ���� �̸�ó�� ������ ���� �ҽ��ڵ�� �̸��� �����ϸ� ��.
// ���� ���̴��� ��ǲ ���̾ƿ��̶� �ٸ��� ���� ���� ����.
// SV_POSITION: ��� ������ ����� ���� ��ġ ��������

struct VertexShader_input
{
	float3 p : POSITION;
	float4 c : COLOR;
	float2 t : TEXTURE;
};

struct VertexShader_output
{
	float4 p : SV_POSITION;
	float4 c : COLOR0; // COLOR0 �� COLOR1 �ۿ� ����.
	float2 t : TEXCOORD0; // TEXCOORD0 ~ TEXCOORD7 (15) ���� ����. 
};

// ��� ���۴� �������� �����θ� �����.
// �������� ���� : float4(x, y, z, w)
// ��� ���۷� �Ѿ�� �ֵ��� ���� ������� ��.
cbuffer ConstantData : register(b0)
{
	matrix g_matWorld : packoffset(c0); // packoffset �� ������ �ʾƵ� �⺻������ c0���� �����ϳ� �ٿ��ִ°� ����
	matrix g_matView : packoffset(c4);
	matrix g_matProj : packoffset(c8);
	float g_nx : packoffset(c12.x);
	float g_ny : packoffset(c12.y);
	float g_nz : packoffset(c12.z);
	float g_nw : packoffset(c12.w);
	//float  fTimer : packoffset(c12.z); // �̷������� �������Ϳ��� ������ ���� ��� �� ���� ����.
}



// �ȼ� ���� ȣ��ȴ�.
// �ش� �ȼ��� �÷��� SV_Target �������Ϳ� ��ȯ �Ѵ�.
// Rasterizer(== Pixel) Stage ���� PixelShader ȣ�� �� Ƚ���� ����.

//struct PixelShader_input
//{
//	float4 p : SV_POSITION;
//	float4 c : COLOR0;
//	float2 t : TEXCOORD0;
//};

Texture2D		g_txTextureA	: register(t0); // register�� �� �ٿ��ָ� �⺻������ 0�� �������Ϳ� ��.
SamplerState	g_SampleA		: register(s0); // ���ø��� �Ϸ��� ���÷��� �ʿ���

// SV_Target: ��� ������ �Ѹ� ����.
float4 main(VertexShader_output _input) : SV_Target
{
	float4 vColor = g_txTextureA.Sample(g_SampleA, _input.t);
	return vColor * _input.c;
}
