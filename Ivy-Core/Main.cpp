#define USE_GL
#ifdef USE_GL
// Force Ivy to use OpenGL on Windows.
#define IVY_FORCE_OPENGL
#endif

#include "Window.h"
#include "Graphics/Camera.h"
#include "Graphics/Objects/Model/Model.h"
#include "Graphics/Colors.h"
#include "Graphics/Renderer/RendererFactory.h"
#include "Graphics/Shaders/ShaderProgramFactory.h"
#include "IO/Image.h"

using namespace Ivy::Graphics;

int main(int argc, char** argv)
{
    Window window(1080, 720, 100, 100, "Ivy", false);
    if (window.Create())
    {
        std::shared_ptr<IRenderer> renderer;
        // Generate a renderer object we can use.
        if (!RendererFactory::GetRenderer(window.GetPlatformWindow(),
            window.GetPlatformDisplay(), RendererPath::Forward, 32,
            24, 8, 1, 1, true, false, &renderer))
            return false;

        renderer->Startup();

#ifdef USE_GL
        ShaderProgram programNoTextures("vert.txt", "fragNoTextures.txt");
        programNoTextures.Create();
        ShaderProgram programWithTextures("vert.txt", "fragWithTextures.txt");
        programWithTextures.Create();

        Camera camera(glm::vec3(0.0f, 2.0f, -10.0f), glm::vec3(0.0f, 2.0f, 0.0f),
            glm::radians(45.0f), 1080, 720, 0.1f, 1000.0f);

        Model model(&programNoTextures);
        model.Load("monocube.dae");
        model.SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));

        Model model2(&programNoTextures);
        model2.Load("monocube.dae");
        model2.SetPosition(glm::vec3(0.0f, 5.0f, 0.0f));

        Model model3(&programWithTextures);
        model3.Load("monocube.dae");
        model3.SetPosition(glm::vec3(5.0f, 0.0f, 0.0f));

        Model model4(&programWithTextures);
        model4.Load("monocube.dae");
        model4.SetPosition(glm::vec3(-5.0f, 0.0f, 0.0f));
#endif
        while (window.open)
        {
            renderer->Clear(Colors::CornflowerBlue);
#ifdef USE_GL

            camera.SetShader(&programNoTextures);
            model.Draw();
            model2.Draw();
            camera.SetShader(&programWithTextures);
            model3.Draw();
            model4.Draw();

            model2.SetRotation(glm::vec3(1.0f, 1.0f, 0.0f));
            model3.SetRotation(glm::vec3(0.0f, 1.0f, 0.0f));
            model4.SetRotation(glm::vec3(0.0f, 0.0f, 1.0f));
#endif
            renderer->Present();
            window.PollWindowEvents();
        }

        renderer->Shutdown();
    }

    return 0;
}