#ifndef IVY_IMAGE_H
#define IVY_IMAGE_H

#include <string>
#include <vector>
#include <FreeImage.h>

namespace Ivy {
    namespace IO {
        class Image {
        public:
            bool Load(std::string filePath);
            unsigned int GetWidth();
            unsigned int GetHeight();
            unsigned int GetPitch();
            unsigned char* GetBitmap();
        private:
            unsigned int m_Width;
            unsigned int m_Height;
            unsigned int m_Pitch;
            unsigned char* m_Bitmap;
        };
    }
}

#endif // IVY_FILE_H