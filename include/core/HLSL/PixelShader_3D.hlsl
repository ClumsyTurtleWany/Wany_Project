//float4 main() : SV_TARGET
//{
//	return float4(1.0f, 1.0f, 1.0f, 1.0f);
//}


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

// 상수 버퍼는 레지스터 단위로만 저장됨.
// 레지스터 단위 : float4(x, y, z, w)
// 상수 버퍼로 넘어온 애들은 전역 변수취급 됨.
cbuffer ConstantData : register(b0)
{
	matrix g_matWorld : packoffset(c0); // packoffset 을 해주지 않아도 기본적으로 c0부터 시작하나 붙여주는게 좋음
	matrix g_matView : packoffset(c4);
	matrix g_matProj : packoffset(c8);
	float g_nx : packoffset(c12.x);
	float g_ny : packoffset(c12.y);
	float g_nz : packoffset(c12.z);
	float g_nw : packoffset(c12.w);
	//float  fTimer : packoffset(c12.z); // 이런식으로 레지스터에서 일정한 값만 등록 할 수도 있음.
}



// 픽셀 마다 호출된다.
// 해당 픽셀의 컬러를 SV_Target 레지스터에 반환 한다.
// Rasterizer(== Pixel) Stage 에서 PixelShader 호출 할 횟수를 결정.

//struct PixelShader_input
//{
//	float4 p : SV_POSITION;
//	float4 c : COLOR0;
//	float2 t : TEXCOORD0;
//};

Texture2D		g_txTextureA	: register(t0); // register를 안 붙여주면 기본적으로 0번 레지스터에 들어감.
SamplerState	g_SampleA		: register(s0); // 샘플링을 하려면 샘플러가 필요함

// SV_Target: 출력 영역에 뿌릴 색상.
float4 main(VertexShader_output _input) : SV_Target
{
	float4 vColor = g_txTextureA.Sample(g_SampleA, _input.t);
	return vColor * _input.c;
}
