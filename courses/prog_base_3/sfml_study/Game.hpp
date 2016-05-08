#ifndef GAME_HPP_INCLUDED
#define GAME_HPP_INCLUDED

#include "Window.hpp"
#include <string>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Game{
public:
    Game();
    ~Game();

    void HandleInput();
    void Update();
    void Render();
    Window* GetWindow();
private:
    void MoveMushroom();
    Window m_window;
    sf::Texture m_mushroomTexture;
    sf::Sprite m_mushroom;
    sf::Vector2i m_increment;
};


#endif // GAME_HPP_INCLUDED
