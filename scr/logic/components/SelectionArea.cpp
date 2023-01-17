#include "SelectionArea.h"

void SelectionArea::setMousePressed(bool isPressed) {
    isMousePressed = isPressed;
}

bool SelectionArea::getIfMousePressed() {
    return isMousePressed;
}

void SelectionArea::clear() {
    transform.setPosition(-100,-100,-100);
}
