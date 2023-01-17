#ifndef RTS_OPENGL_SELECTIONAREA_H
#define RTS_OPENGL_SELECTIONAREA_H

#include "Transformable.h"

class SelectionArea {
private:
    bool isMousePressed = false;
public:
    Transformable transform;

    void setMousePressed(bool isPressed);
    bool getIfMousePressed();

    void clear();
};


#endif //RTS_OPENGL_SELECTIONAREA_H
