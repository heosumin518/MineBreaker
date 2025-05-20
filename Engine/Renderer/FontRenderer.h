#pragma once
#include <GLFW/glfw3.h>
#include "../../Dependencies/stb/stb_truetype.h"

struct Color
{
    float r, g, b, a;
};

class FontRenderer
{
public:
    bool LoadFont(const char* path, float size = 32.0f);
    void RenderText(const char* text, float x, float y, Color color);
    void Cleanup();

private:
    GLuint m_FontTexture = 0;
    stbtt_bakedchar m_CharData[96]; // ASCII 32~126
};
