
// VertexShader.txt, PixelShader.txt 따로 구분하지 않고 하나의 파일에 합쳐놓아도 된다.

// HLSL (High Level Shader Language)
// 정점쉐이더란 정점 버퍼에 있는 모든 정점을 1번씩 작업한다.
// 정점 위치(SV_POSITION : System Value Position 레지스터)는 반드시 float4로 반환해야 한다.
// SV_POSITION(시멘틱 : 의미 구조) 시스템상 고정되어 있음. COLOR0 과 COLOR1 등도 있음.

// float3 p : POSITION 에서 POSITION은 Sample.hpp->CreateVertexLayout->InputElementDescs 의 요소 이름과 같아야함. 
// 고정적으로 쓰는게 아니라 그냥 변수 이름처럼 쓰지만 밖의 소스코드와 이름만 동일하면 됨.
// 정점 쉐이더랑 인풋 레이아웃이랑 다르면 만들 수가 없다.
// SV_POSITION: 출력 영역을 만들기 위한 위치 레지스터

struct VertexShader_input
{
	float3 p : POSITION;
	float4 c : COLOR;
	float2 t : TEXTURE;
};

struct VertexShader_output
{
	float4 p : SV_POSITION;
	float4 c : COLOR0; // COLOR0 과 COLOR1 밖에 없음.
	float2 t : TEXCOORD0; // TEXCOORD0 ~ TEXCOORD7 (15) 까지 있음. 
};

VertexShader_output VS(VertexShader_input _input)
{
	VertexShader_output output; // = (VertexShader_output)0;

	output.p = float4(_input.p, 1.0f);
	output.c = _input.c;
	output.t = _input.t;
	return output;
}

//float4 main(float4 pos : POSITION) : SV_POSITION
//{
//	return pos;
//}