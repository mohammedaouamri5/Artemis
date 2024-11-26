

#ifndef _IMAGE_H_
#define _IMAGE_H_

#include "imgui.h"
#include "GL/gl.h"
#include <stdio.h>
#ifndef STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#endif // STB_IMAGE_IMPLEMENTATION

namespace CORE
{
    struct Image
    {
        Image(
            const char *imagePath,
            GLint internalFormat  );
        void INIT();
        void Draw(const ImVec2 &uv0  ,
                  const ImVec2 &uv1   );
        void DESTROY();
        void Info();
        int size[2] = {300 , 300};
        float scale[2] = {1.0f, 1.0f};
        int position[2]  ;
        int padding[4] = {0 , 0 , 0 , 0}; // (TL , TR , BR , BL )
        void SetPositon(int X , int y);

    private:
        GLuint textureID;
        const char *imagePath;
        GLint internalFormat;

        GLuint LoadImageTexture(const char *imagePath, int &width, int &height);

        /* data */
    };
} // namespace CORE
#endif // _IMAGE_H_
