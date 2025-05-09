#ifndef RADIANTX_API_H
#define RADIANTX_API_H

#include <string>
#include <vector>

// ============================================================
// RadiantX API Suite - Advanced Game Development Framework
// ============================================================

class RadiantXAPI {
public:
    // 🔥 System Initialization & Shutdown
    static bool Initialize();
    static void Shutdown();

    // 🎮 Graphics API (Vulkan/OpenGL-based Rendering)
    static bool InitGraphics(const std::string &title, int width, int height);
    static void RenderFrame();
    static void ToggleGraphicsMode();
    static void EnableRayTracing(bool enabled);
    static void SetShader(const std::string& shaderFile);

    // 🏗 Physics Simulation
    static void EnablePhysics(bool enabled);
    static void ApplyForce(int objectID, float x, float y, float z);
    static void SetGravity(float strength);

    // 🌐 Networking & Multiplayer
    static void ConnectToServer(const std::string &ip, int port);
    static void SendNetworkPacket(const std::vector<char>& data);

    // 🎨 Asset & Shader Management
    static void LoadModel(const std::string &modelFile);
    static void LoadTexture(const std::string &textureFile);
    static void CompileShader(const std::string &shaderCode);
};

#endif // RADIANTX_API_H
