#include "common.hlsl"
Texture2D g_Texture : register(t0); //テクスチャ０番
SamplerState g_SamplerState : register(s0); //サンプラー０番
void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
    float4 normal = normalize(In.Normal);
        
    float light = 0.5f - 0.5f * dot(normal.xyz, Light.Direction.xyz);
//    float light = -dot(Light.Direction.xyz, normal.xyz);
    outDiffuse = g_Texture.Sample(g_SamplerState, In.TexCoord); //テクスチャの色を取得
    outDiffuse.rgb *= In.Diffuse.rgb * light;
//    outDiffuse.rgb *= In.Diffuse.rgb;
    outDiffuse.a *= In.Diffuse.a; //デフューズ(頂点の明るさ)を合成
    

    
    float3 eyev = In.WorldPosition.xyz - CameraPosition.xyz;
    eyev = normalize(eyev);
    float3 halfv = eyev + Light.Direction.xyz;
    halfv = normalize(halfv);    

    float specular = -dot(halfv, normal.xyz);
    specular = saturate(specular);
    specular = pow(specular, 70);
    outDiffuse.rgb += specular;
    
    float rim = dot(eyev, normal.xyz) + 1.0f;
    rim = pow(rim, 5) * 1.0f;
    
    outDiffuse.rb += rim;
    outDiffuse.g += rim * 0.5f; 
    
}