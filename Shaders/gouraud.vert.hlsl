#include "Lighting.hlsli"

cbuffer VertexUniforms : register(b0, space1)
{
    float4x4 mvp;
    float4x4 model;
    float3 cameraPosition;
    float padding1;
}

cbuffer LightUniforms : register(b1, space1)
{
    Light light;
}

cbuffer MaterialUniforms : register(b2, space1)
{
    Material material;
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
    float3 specular : TEXCOORD2;
};

Output main(Input input)
{
    Output output;
    output.texcoord = (input.texcoord * material.tiling) + material.offset;
    output.position = mul(mvp, float4(input.position, 1.0f));
    
    //float3 worldPosition = mul(model, float4(input.position, 1.0f));
    float3 N = normalize(mul((float3x3) model, input.normal));
    float3 V = normalize(cameraPosition - input.position);
    
    
    float attenuation;
    float3 L = getLightVector(light, input.position, attenuation);
    float radiance = light.color * light.intensity * attenuation;
    
    
    
    
    // DIFFUSE
    float NdotL = saturate(dot(N, L));
    float3 diffuse = radiance * NdotL * attenuation;
    output.diffuse = light.ambient + diffuse;

    //calculateLighting(light, material, worldPosition, N, V, output.diffuse, output.specular);
    
    
    //output.specular = light.ambient + calculateSpecular(radiance, N, L);
    output.specular = float3( 0.0f, 0.0f, 0.0f );
    if (NdotL > 0)
    {
        // Blinn-Phong Specular
        float3 V = normalize(cameraPosition - input.position);
        float3 H = normalize(V + L);
        float HdotN = saturate(dot(H, N));
        HdotN = pow(HdotN, material.shininess);
        output.specular = radiance * HdotN;
    }
    
    return output;
}
