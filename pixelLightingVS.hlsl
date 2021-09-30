#include "common.hlsl"

void main(in VS_IN In, out PS_IN Out)
{
    matrix wvp; //���񂨖񑩂̒��_�ϊ�
    wvp = mul(World, View);
    wvp = mul(wvp, Projection);
    Out.Position = mul(In.Position, wvp);
    
        float4 worldNomal, normal;
        normal = float4(In.Normal.xyz, 0.0);
        
        worldNomal = mul(normal, World);
        worldNomal = normalize(worldNomal);
        Out.Normal = worldNomal;
        
    Out.Diffuse = In.Diffuse;
    Out.TexCoord = In.TexCoord; //���_�̃e�N�X�`�����W���o��
    Out.WorldPosition = mul(In.Position, World);
}