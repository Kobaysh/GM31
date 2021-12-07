#include "common.hlsl"

void main(in VS_IN In, out PS_IN Out)
{
    matrix wvp; //毎回お約束の頂点変換
    wvp = mul(World, View);
    wvp = mul(wvp, Projection);
    Out.Position = mul(In.Position, wvp);
    
        float4 worldNomal, normal;
        normal = float4(In.Normal.xyz, 0.0);
        
        worldNomal = mul(normal, World);
        worldNomal = normalize(worldNomal);
        Out.Normal = worldNomal;
        
    Out.Diffuse = In.Diffuse;
    Out.TexCoord = In.TexCoord; //頂点のテクスチャ座標を出力
    Out.WorldPosition = mul(In.Position, World);
}