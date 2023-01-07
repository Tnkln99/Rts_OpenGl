#ifndef ENGINE_02_FRAMEBUFFER_H
#define ENGINE_02_FRAMEBUFFER_H

#include <iostream>


class Framebuffer {
private:
    int textureWidth = 1920;
    int textureHeight = 1080;

    unsigned int quadVAO;

    unsigned int fbo;
    unsigned int texture;
    unsigned int rbo;
public:
    void load();

    [[nodiscard]]int getTexture() const;
    [[nodiscard]]int getTextureWidth() const;
    [[nodiscard]]int getTextureHeight() const;

    // binds to framebuffer and enables depth
    void bind();

    // unbinds from frame buffer and draws everything to texture
    void prepareToTextureRender(int windowsWidth, int windowsHeight);
};


#endif //ENGINE_02_FRAMEBUFFER_H
