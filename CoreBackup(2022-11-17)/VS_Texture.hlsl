
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
	float3 n : NORMAL;
	float4 c : COLOR;
	float2 t : TEXTURE;
};

struct VertexShader_output
{
	float4 p : SV_POSITION;
	float3 n : NORMAL;
	float4 c : COLOR0; // COLOR0 �� COLOR1 �ۿ� ����.
	float2 t : TEXCOORD0; // TEXCOORD0 ~ TEXCOORD7 (15) ���� ����. 
};

VertexShader_output VS(VertexShader_input _input)
{
	VertexShader_output output; // = (VertexShader_output)0;

	output.p = float4(_input.p, 1.0f);
	output.n = _input.n;
	output.c = _input.c;
	output.t = _input.t;
	return output;
}

//float4 main(float4 pos : POSITION) : SV_POSITION
//{
//	return pos;
//}