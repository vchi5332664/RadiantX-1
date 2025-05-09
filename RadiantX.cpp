#include "RadiantXAPI.h"
#include <iostream>
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <GL/glu.h>
#include <memory>
#include <thread>
#include <chrono>

// ============================================================
// RadiantX System - Aggregates all subsystems into one framework.
// ============================================================
class RadiantXSystem {
public:
    RadiantXSystem() 
        : graphics(std::make_unique<GraphicsAPI>()),
          physics(std::make_unique<PhysicsAPI>()),
          networking(std::make_unique<NetworkingAPI>()),
          shader(std::make_unique<ShaderAPI>()),
          vrar(std::make_unique<VRARAPI>()),
          debug(std::make_unique<DebugAPI>()),
          objectY(10.0f) {}

    bool Initialize() {
        std::cout << "Initializing RadiantX System..." << std::endl;
        if (!graphics->InitGraphics("RadiantX Engine", 1920, 1080)) 
            return false;

        physics->EnablePhysics(true);
        networking->InitNetworking();
        shader->CompileShader("void main() { /* Default shader code */ }");
        vrar->InitVR();
        debug->StartProfiler();

        std::cout << "RadiantX System initialized successfully!" << std::endl;
        return true;
    }

    void Update(float deltaTime) {
        physics->SimulatePhysics(deltaTime);
        networking->SendNetworkPacket({0x01, 0x02, 0x03});
    }

    void Render() {
        graphics->RenderFrame();
    }

    void Shutdown() {
        graphics->Cleanup();
        std::cout << "RadiantX System shutdown complete." << std::endl;
    }

private:
    std::unique_ptr<GraphicsAPI> graphics;
    std::unique_ptr<PhysicsAPI> physics;
    std::unique_ptr<AIAPI> ai;
    std::unique_ptr<NetworkingAPI> networking;
    std::unique_ptr<ShaderAPI> shader;
    std::unique_ptr<VRARAPI> vrar;
    std::unique_ptr<DebugAPI> debug;
    float objectY;
};

// ============================================================
// Main Function - Runs RadiantX in a game loop.
// ============================================================
int main() {
    RadiantXSystem engine;
    if (!engine.Initialize()) {
        std::cerr << "Failed to initialize RadiantX!" << std::endl;
        return -1;
    }

    bool running = true;
    SDL_Event event;
    auto lastTime = std::chrono::high_resolution_clock::now();

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                running = false;
        }

        auto currentTime = std::chrono::high_resolution_clock::now();
        float deltaTime = std::chrono::duration<float>(currentTime - lastTime).count();
        lastTime = currentTime;

        engine.Update(deltaTime);
        engine.Render();
        std::this_thread::sleep_for(std::chrono::milliseconds(16)); // ~60 FPS
    }

    engine.Shutdown();
    return 0;
}
