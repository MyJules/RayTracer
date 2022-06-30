#include "Images.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#define CHANNEL_NUM 3

void saveRenderResultJPG(const RenderResult_t &img, const std::string &fileName, const int width, const int height)
{
    uint8_t pixels[width * height * CHANNEL_NUM];
    int index = 0;
    for (const auto &pixel : img)
    {
        pixels[index++] = pixel.x;
        pixels[index++] = pixel.y;
        pixels[index++] = pixel.z;
    }

    stbi_write_jpg(fileName.c_str(), width, height, 3, pixels, 100);
}

void saveRenderResultPNG(const RenderResult_t &img, const std::string &fileName, const int width, const int height)
{
    uint8_t pixels[width * height * CHANNEL_NUM];
    int index = 0;
    for (const auto &pixel : img)
    {
        pixels[index++] = pixel.x;
        pixels[index++] = pixel.y;
        pixels[index++] = pixel.z;
    }

    stbi_write_png(fileName.c_str(), width, height, CHANNEL_NUM, pixels, width * CHANNEL_NUM);
}
