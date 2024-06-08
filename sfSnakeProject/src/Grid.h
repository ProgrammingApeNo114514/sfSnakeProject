#ifndef GRID_H
#define GRID_H

#include <SFML/Graphics.hpp>

namespace sfSnake {

    class Grid
    {
    public:
        Grid(int gridSize, int width, int height);

        void setGridColor(sf::Color color);
        sf::Color GetGridColor();

        void draw(sf::RenderWindow& window);

    private:
        int m_gridSize;
        int m_width;
        int m_height;
        sf::Color m_gridColor;
    };
}

#endif 