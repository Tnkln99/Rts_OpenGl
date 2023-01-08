#ifndef RTS_3D_GAME_H
#define RTS_3D_GAME_H

#include "graphics/Window.h"
#include "logic/Battlefield.h"

class Game {
private:
    float deltaTime = 0.0f;	// Time between current frame and last frame
    float lastFrame = 0.0f; // Time of last frame

    Window window;
    Battlefield battlefield;

    bool gameRunning = true;
public:
    Game();

    void run();
    void terminate();

    void update();
};


#endif //RTS_3D_GAME_H
