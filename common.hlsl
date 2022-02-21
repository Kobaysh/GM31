


cbuffer WorldBuffer : register(b0)
{
	matrix World;
}
cbuffer ViewBuffer : register(b1)
{
	matrix View;
}
cbuffer ProjectionBuffer : register(b2)
{
	matrix Projection;
}

uniform int g_Loacation;
Texture2D g_VATexture;


struct MATERIAL
{
	float4 Ambient;
	float4 Diffuse;
	float4 Specular;
	float4 Emission;
	float Shininess;
	float3 Dummy;
};

cbuffer MaterialBuffer : register(b3)
{
	MATERIAL Material;
}




struct LIGHT
{
	bool Enable;
	bool3 Dummy;
	float4 Direction;
	float4 Diffuse;
	float4 Ambient;
};

cbuffer LightBuffer : register(b4)
{
	LIGHT Light;
}





struct VS_IN
{
	float4 Position		: POSITION0;
	float4 Normal		: NORMAL0;
	float4 Diffuse		: COLOR0;
	float2 TexCoord		: TEXCOORD0;
};

//struct VS_OUT
//{
//	float4 HPos : SV_Position;
//	float3 VATColor : TEXCOORD1;
//};

//VS_OUT VS(VS_IN In)
//{
//	VS_OUT Out = (VS_OUT)0;
//	float3 w_pos = mul(In.Position, World).xyz;
//	float3 vat_pos = g_VATexture.Load(int3(int(In.TexCoord.x), g_Loacation, 0)).xyz;
//	w_pos = w_pos + vat_pos;
//	Out.HPos = mul(mul(float4(w_pos, 1.0f), View), Projection);
//	Out.VATColor = vat_pos;
//	return Out;
//}

struct PS_IN
{
	float4 Position : SV_POSITION;
    float4 WorldPosition : POSITION0;
    float4 Normal : NORMAL0;
	float4 Diffuse : COLOR0;
	float2 TexCoord : TEXCOORD0;
};

//float4 PS(VS_OUT In) :SV_Target
//{
//	return float4(In.VATColor, 1.0);

//}

//technique11 VertexAnimationTexture
//{
//	pass p0
//	{
//		SetVertexShader(CompileShader(vs_4_0, VS()));
//		SetGeometryShader(NULL);
//		SetPixelShader(CompileShader(ps_4_0, PS()));
//	}
//}


cbuffer CameraBuffer : register(b5)
{
    float3 CameraPosition;
}

cbuffer ParameterBuffer : register(b6)
{
    float3 Paramater;
}
