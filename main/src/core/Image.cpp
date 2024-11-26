

#include "Image.hpp"

namespace CORE
{

    void Image::SetPositon(int X , int y)
    {

        for (size_t i = 0; i < 2; i++)
        {

            this->position[i] = position[i];
        }
    }

    Image::Image(
        const char *imagePath,
        GLint internalFormat = GL_RGBA) : 
        imagePath( imagePath) ,
        internalFormat(internalFormat){}

    void Image::INIT()
    {
        this->Image::DESTROY();
        this->textureID = LoadImageTexture(imagePath, this->size[0], this->size[1]);
    }
    void Image::DESTROY()
    {
        if (!this->textureID)
            glDeleteTextures(1, &(this->textureID));
    }
    void Image::Draw(const ImVec2 &uv0 = ImVec2(0, 0),
                     const ImVec2 &uv1 = ImVec2(1, 1))
    {
        // this->Info();
        ImGui::SetCursorPos(ImVec2(position[0] + padding[0], position[1] + padding[1])); // Set the position (x, y) of the image

        ImGui::Image((void *)(intptr_t)(this->textureID),
                     ImVec2(abs(size[0] * scale[0]) - (padding[0] + padding[2]), abs(size[1] * scale[1]) - (padding[1] + padding[3])),
                     uv0, uv1);
        ImGui::SetCursorPos(ImVec2(abs(size[0] * scale[0]) + position[0], abs(size[1] * scale[1]) + position[1]));
    }
    void Image::Info()
    {

        // ImVec2  CursorPos = ImGui::GetCursorPos();
        ImGui::Begin(imagePath);
        ImGui::DragInt2("size", size, 0.5F);
        ImGui::DragFloat2("scale", scale, 0.005F);
        ImGui::DragInt2("position", position, 0.05F);
        ImGui::DragInt4("padding", padding, 0.05F);
        ImGui::End();
    }

    GLuint Image::LoadImageTexture(const char *imagePath, int &width, int &height)
    {
        stbi_set_flip_vertically_on_load(true);
        unsigned char *image = stbi_load(imagePath, &width, &height, nullptr, 4);

        if (!image)
        {
            // Handle error loading image
            return 0;
        }

        GLuint textureID;
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, (int)internalFormat, width, height, 0, internalFormat, GL_UNSIGNED_BYTE, image);

        stbi_image_free(image);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        return textureID;
    }

} // namespace CORE
