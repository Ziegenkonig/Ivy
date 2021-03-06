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

#ifdef USE_GL
        ShaderProgram program("vert.txt", "fragNoTextures.txt");
        program.Create();
        ShaderProgram programTextured("vert.txt", "fragWithTextures.txt");
        programTextured.Create();

        Camera camera(&programTextured, glm::vec3(0.0f, 2.0f, -10.0f), glm::vec3(0.0f, 2.0f, 0.0f),
            glm::radians(45.0f), 1080, 720, 0.1f, 1000.0f);
        camera.Create();

        Model model2(&programTextured);
        model2.Load("monocube.dae");
        model2.SetPosition(glm::vec3(0.0f, 5.0f, 0.0f));

        Model model3(&programTextured);
        model3.Load("monocube.dae");
        model3.SetPosition(glm::vec3(5.0f, 0.0f, 0.0f));

        Model model4(&programTextured);
        model4.Load("monocube.dae");
        model4.SetPosition(glm::vec3(-5.0f, 0.0f, 0.0f));
#endif
        while (window.open)
        {
            renderer->Clear(Colors::CornflowerBlue);
#ifdef USE_GL       
            model2.Draw();
            model3.Draw();
            model4.Draw();

            model2.SetRotation(glm::vec3(1.0f, 1.0f, 0.0f));
            model3.SetRotation(glm::vec3(0.0f, 1.0f, 0.0f));
            model4.SetRotation(glm::vec3(0.0f, 0.0f, 1.0f));
#endif
            renderer->Present();
            window.PollWindowEvents();
        }
    }

    return 0;
}