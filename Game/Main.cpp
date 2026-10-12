#include "Engine.h"
#include "Core/File.h"
#include "Renderer/Shader.h"
#include "Renderer/VertexBuffer.h"
#include "Renderer/Pipeline.h"

#include "Resources/ResourceManager.h"

using namespace nu;

namespace nu 
{
    struct Color4
    {
        float r, g, b, a;
    };
}

struct Vertex
{
    Vector3 position;
    Color4 color;
};

std::vector<Vertex> vertices =
{
    Vertex{ { -1.0f, -1.0f, 0.0f}, Color4{ 1, 0, 0, 1 } }, // Bottom-Left
    Vertex{  {1.0f, -1.0f, 0.0f}, Color4{ 1, 0, 0, 1 } }, // Bottom-Right
    Vertex{  {0.4f,  -0.3f, 0.0f}, Color4{ 1, 0, 0, 1 } }, // Top-Middle
};

int main()
{
    SetWorkingDirectory("Assets");

    // INITIALIZATION
    Engine::Instance().Initialize();

    // Triangle rendering
    auto vb = std::make_shared<VertexBuffer>();
    vb->Create<Vertex>(vertices, Engine::Instance().GetRenderer().GetGPUDevice());

    auto vshader = Resources().Get<nu::Shader>("shaders/position.vert", Engine::Instance().GetRenderer());
    auto fshader = Resources().Get<nu::Shader>("shaders/color.frag", Engine::Instance().GetRenderer());

    auto pipeline = std::make_shared<Pipeline>();
    pipeline->AddVertexBuffer(sizeof(Vertex));
    //position
    pipeline->AddVertexAttribute(
        0,
        SDL_GPU_VERTEXELEMENTFORMAT_FLOAT3,
        offsetof(Vertex, position));
    //color
    pipeline->AddVertexAttribute(
        1,
        SDL_GPU_VERTEXELEMENTFORMAT_FLOAT4,
        offsetof(Vertex, color));

    pipeline->Create(*vshader.get(), *fshader.get(),
        Engine::Instance().GetRenderer().GetGPUDevice(),
        Engine::Instance().GetRenderer().GetWindow());


    // MAIN LOOP
    bool quit = false;
    while (!quit) 
    {
        // UPDATE
        SDL_Event event;
        while (SDL_PollEvent(&event)) 
        {
            if (event.type == SDL_EVENT_QUIT) 
            {
                quit = true;
            }
            if (event.type == SDL_EVENT_KEY_DOWN && event.key.scancode == SDL_SCANCODE_ESCAPE)
            {
                quit = true;
            }
        }

        // ENGINE
        Engine::Instance().Update();
        float dt = Engine::Instance().GetTime().GetDeltaTime();


        // RENDER
        Engine::Instance().GetRenderer().BeginFrame();

        Engine::Instance().GetRenderer().SetPipeline(*pipeline);
        Engine::Instance().GetRenderer().SetVertexBuffer(*vb);
        Engine::Instance().GetRenderer().Draw(vb->GetVertexCount());

        Engine::Instance().GetRenderer().EndFrame();
    }

    // SHUTDOWN
    Engine::Instance().Shutdown();    

    return 0;
}

