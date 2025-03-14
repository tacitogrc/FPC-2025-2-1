#include <iostream>
#include "jogo_engine.cpp"

struct Choice {
    std::string option;
    int nextSceneId;
};

int main(){
    Game game;
    game.run();
    return 0;
}