cbuffer Uniforms : register(b0, space3)
{
    float4 color;
}

struct Input
{
    float2 texcoord : TEXCOORD0;
};

struct Output
{
	float4 color : SV_Target0;
};

Output main(Input input)
{
	Output output;
    //output.color = u_texture.Sample(u_sampler, input.texcoord) * color; 
    
    //old code v
    output.color = color;

	return output;
}
