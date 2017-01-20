/*
MIT License

Copyright (c) 2017 Ben Brown

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "Texture.h"

bool Ivy::Graphics::Texture::CreateFromFile(Program* program) {
    // Use free image to get load the image and retrieve its m_Bitmap.
    FREE_IMAGE_FORMAT fif = FreeImage_GetFIFFromFilename(m_FilePath.c_str());
    if (!FreeImage_FIFSupportsReading(fif))
        return false;

    FIBITMAP* bitmap = FreeImage_Load(fif, m_FilePath.c_str());
    if (!bitmap)
        return false;

    // Needs to be a 32 bit bitmap.
    if (FreeImage_GetBPP(bitmap) != 32) {
        FIBITMAP* temp = bitmap;
        bitmap = FreeImage_ConvertTo32Bits(bitmap);
        FreeImage_Unload(temp);
    }

    // We have to flip the bitmap for it to appear properly.
    FreeImage_FlipVertical(bitmap);

    // Get bitmap attributes.
    m_Width = FreeImage_GetWidth(bitmap);
    m_Height = FreeImage_GetHeight(bitmap);
    m_Pitch = FreeImage_GetPitch(bitmap);
    
    // Retrieve the bits of the bitmap.
    m_Bitmap = reinterpret_cast<GLubyte*>(FreeImage_GetBits(bitmap));
    if (!m_Bitmap)
        return false;

    glGenTextures(1, &m_TextureID);
    glBindTexture(GL_TEXTURE_2D, m_TextureID);

    // Set our texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, 
        0, GL_RGBA, GL_UNSIGNED_BYTE, m_Bitmap);
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, GL_NONE);

    m_SamplerLocation = glGetUniformLocation(program->GetProgramID(), "ivy_Sampler0");

    // We are now done with bitmap, unload to prevent leaks.
    FreeImage_Unload(bitmap);

    return true;
}

void Ivy::Graphics::Texture::MakeActive() {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_TextureID);
    glUniform1i(m_SamplerLocation, 0);
}
