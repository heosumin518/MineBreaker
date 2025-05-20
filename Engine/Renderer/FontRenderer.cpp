#include "glad/glad.h"
#include "FontRenderer.h"
#define STB_TRUETYPE_IMPLEMENTATION
#include "../../Dependencies/stb/stb_truetype.h"    // 인클루드 필요함 지우지 말 것!
#include <fstream>
#include <vector>
#include <iostream>

bool FontRenderer::LoadFont(const char* path, float size)
{
    std::ifstream file(path, std::ios::binary);
    if (!file) {
        std::cerr << "Font file open failed: " << path << std::endl;
        return false;
    }

    std::vector<unsigned char> buffer((std::istreambuf_iterator<char>(file)),
        std::istreambuf_iterator<char>());

    unsigned char bitmap[512 * 512] = {};
    if (stbtt_BakeFontBitmap(buffer.data(), 0, size, bitmap, 512, 512, 32, 96, m_CharData) <= 0) {
        std::cerr << "stbtt_BakeFontBitmap failed\n";
        return false;
    }

    glGenTextures(1, &m_FontTexture);
    glBindTexture(GL_TEXTURE_2D, m_FontTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 512, 512, 0, GL_RED, GL_UNSIGNED_BYTE, bitmap);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Swizzle 설정
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_R, GL_ONE);  // R = 1
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_G, GL_ONE);  // G = 1
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_B, GL_ONE);  // B = 1
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_A, GL_RED);  // A = RED 채널
    return true;
}

void FontRenderer::RenderText(const char* text, float x, float y, Color color)
{
    glColor4f(color.r, color.g, color.b, color.a);

    glBindTexture(GL_TEXTURE_2D, m_FontTexture);
    glEnable(GL_TEXTURE_2D);
    glBegin(GL_QUADS);

    while (*text) {
        if (*text < 32 || *text >= 128) {
            ++text;
            continue;
        }

        const stbtt_bakedchar& ch = m_CharData[*text - 32];

        float x0 = x + ch.xoff;
        float y0 = y - ch.yoff;
        float x1 = x0 + (ch.x1 - ch.x0);
        float y1 = y0 - (ch.y1 - ch.y0);

        float s0 = ch.x0 / 512.0f;
        float t0 = ch.y0 / 512.0f;
        float s1 = ch.x1 / 512.0f;
        float t1 = ch.y1 / 512.0f;

        glTexCoord2f(s0, t0); glVertex2f(x0, y0);
        glTexCoord2f(s1, t0); glVertex2f(x1, y0);
        glTexCoord2f(s1, t1); glVertex2f(x1, y1);
        glTexCoord2f(s0, t1); glVertex2f(x0, y1);

        x += ch.xadvance;
        ++text;
    }

    glEnd();
    glDisable(GL_TEXTURE_2D);

    glColor4f(1.0f, 1.0f, 1.0f, 1.0f); // 상태 초기화
}

void FontRenderer::Cleanup()
{
    if (m_FontTexture != 0) {
        glDeleteTextures(1, &m_FontTexture);
        m_FontTexture = 0;
    }
}
