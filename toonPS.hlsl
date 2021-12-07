#include "common.hlsl"
Texture2D g_Texture : register(t0); //テクスチャ０番
SamplerState g_SamplerState : register(s0); //サンプラー０番
void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
    float4 normal = normalize(In.Normal);
        
    float light = 0.5 - 0.5 * dot(Light.Direction.xyz, normal.xyz);
    if(light > 0.7f)
        light = 1.0f;
    else if(light > 0.5f)
        light = 0.8f;
    else if (light > 0.3f)
        light = 0.6f;
    else
        light = 0.4f;
    
        
    outDiffuse = g_Texture.Sample(g_SamplerState, In.TexCoord); //テクスチャの色を取得
    outDiffuse.rgb *= (light * In.Diffuse.rgb);
    outDiffuse.a *= In.Diffuse.a; //デフューズ(頂点の明るさ)を合成
    

    
    float3 eyev = In.WorldPosition.xyz - CameraPosition.xyz;
    eyev = normalize(eyev);
    float3 halfv = eyev + Light.Direction.xyz;
    halfv = normalize(halfv);
    float d = -dot(normal.xyz, eyev);
    if (d <= 0.2f)
    {
        outDiffuse.r *= 0.0f;
        outDiffuse.g *= 0.0f;
        outDiffuse.b *= 0.5f;
    }
    
    
    float3 refv = reflect(Light.Direction.xyz, normal.xyz);
    refv = normalize(refv);
    
    float specular = -dot(eyev, refv);
    specular = saturate(specular);
    specular = pow(specular, 30);


 //   outDiffuse.rgb += specular;
}