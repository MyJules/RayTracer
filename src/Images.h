#pragma once

#include <string>
#include <Renderer.h>

void saveRenderResultJPG(const RenderResult_t &img, const std::string &fileName, const int width, const int height);
void saveRenderResultPNG(const RenderResult_t &img, const std::string &fileName, const int width, const int height);