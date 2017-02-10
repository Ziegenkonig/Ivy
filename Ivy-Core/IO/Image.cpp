#include "Image.h"

bool Ivy::IO::Image::Load(std::string filePath) {
    FREE_IMAGE_FORMAT fif = FreeImage_GetFIFFromFilename(filePath.c_str());
    if (!FreeImage_FIFSupportsReading(fif))
        return false;

    FIBITMAP* bitmap = FreeImage_Load(fif, filePath.c_str());
    if (!bitmap)
        return false;

    // Needs to be a 32 bit bitmap.
    if (FreeImage_GetBPP(bitmap) != 32) {
        FIBITMAP* temp = bitmap;
        bitmap = FreeImage_ConvertTo32Bits(bitmap);
        FreeImage_Unload(temp);
    }

    // Get bitmap attributes.
    m_Width = FreeImage_GetWidth(bitmap);
    m_Height = FreeImage_GetHeight(bitmap);
    m_Pitch = FreeImage_GetPitch(bitmap);

    m_Bitmap = FreeImage_GetBits(bitmap);

    // We are now done with bitmap, unload to prevent leaks.
    FreeImage_Unload(bitmap);

    return m_Bitmap != nullptr ? true : false;
}
