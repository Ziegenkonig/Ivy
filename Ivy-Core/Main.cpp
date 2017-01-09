#include "Renderer.h"
#include "Shader.h"
#include "Program.h"
#include "VertexBuffer.h"
#include "ElementBuffer.h"
#include "Window.h"

int main()
{
    Window window(1080, 720, 100, 100, "Ivy", false);
    if (window.Create())
    {
        Renderer renderer(8, 8, 8, 8, 24, 8, 0, false, false, true);
        renderer.Create(window.GetPlatformWindow(), window.GetPlatformDisplay());

        std::vector<Shader> shaders;
        Shader vert("vert.txt", GL_VERTEX_SHADER);
        if (vert.Create())
            shaders.push_back(vert);
        Shader frag("frag.txt", GL_FRAGMENT_SHADER);
        if (frag.Create())
            shaders.push_back(frag);

        Program program(shaders);
        program.Create();

        GLfloat vertices[] =
        {
            0.0f,  0.5f, 0.0f,
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
        };

        GLfloat colors[] =
        {
            1.0f, 0.0f, 0.0f, 1.0f,
            0.0f, 1.0f, 0.0f, 1.0f,
            0.0f, 0.0f, 1.0f, 1.0f
        };

        VertexBuffer vBuffer(program);
        vBuffer.Bind(vertices, colors);

        GLushort indices[] = { 0, 1, 2 };

        ElementBuffer eBuffer;
        eBuffer.Bind(indices);

        while (window.open)
        {
            renderer.Clear(Color::CornflowerBlue);

            program.MakeActive();
            eBuffer.Draw();
            program.MakeInactive();

            renderer.SwapBuffers();
            window.PollWindowEvents();
        }
    }

    return 0;
}