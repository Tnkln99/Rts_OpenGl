#include "Game.h"

Game::Game() {
    window.load();

    battlefield.load();

    window.loadUi();
}

void Game::run() {
    while (gameRunning)
    {
        update();

        window.render(battlefield);
    }
    terminate();
}

void Game::terminate() {

}

void Game::update() {
    if(window.shouldClose()){
        gameRunning = false;
    }

    window.update();

    window.getInputs();

    battlefield.update(window.getPointer());
}


