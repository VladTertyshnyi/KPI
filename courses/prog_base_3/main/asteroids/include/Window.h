#ifndef WINDOW_H_INCLUDED
#define WINDOW_H_INCLUDED

#include <string>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class gameWindow{
public:
    gameWindow();
    gameWindow(const std::string& l_title,const sf::Vector2u& l_size);
    ~gameWindow();

    void BeginDraw(); // Clear the window.
    void EndDraw(); // Display the changes.
    void Update();
    bool IsDone();
    bool IsFullscreen();
    sf::Vector2u GetWindowSize();
    void ToggleFullscreen();
    void Draw(sf::Drawable& l_drawable);
    sf::RenderWindow* GetRenderWindow();

    void Setup(const std::string l_title,
    const sf::Vector2u& l_size);
    void Destroy();
    void Create();

    sf::RenderWindow m_window;
    sf::Vector2u m_windowSize;
    std::string m_windowTitle;
    bool m_isDone;
    bool m_isFullscreen;

private:

};

#endif // WINDOW_H_INCLUDED
