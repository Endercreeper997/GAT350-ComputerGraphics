cbuffer Uniforms : register(b0, space1)
{
    float4x4 mvp;
}

cbuffer LightUniforms : register(b1, space1)
{
    float3 ambient;
}

struct Input
{
    float3 position : TEXCOORD0;
    float2 texcoord : TEXCOORD1;
    float3 normal : TEXCOORD2;
};

struct Output
{
    float4 position : SV_Position;
    float2 texcoord : TEXCOORD0;
    float3 diffuse : TEXCOORD1;
};

Output main(Input input)
{
    Output output;
    output.texcoord = input.texcoord;
    output.position = mul(mvp, float4(input.position, 1.0f));
    
    // DIFFUSE
    float3 N = normalize(input.normal);
    float3 L = -float3(0, -1, 0);
    float NdotL = saturate(dot(N, L));
    
    float3 diffuse = NdotL;
    
    output.diffuse = ambient + diffuse;
    

    return output;
}