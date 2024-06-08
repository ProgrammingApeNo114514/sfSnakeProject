#include "Grid.h"
#include "Game.h"
using namespace sfSnake;

Grid::Grid(int gridSize, int width, int height)
    : m_gridSize(gridSize), m_width(width), m_height(height)
{
    m_gridColor = Game::GridColor;
}

void Grid::setGridColor(sf::Color color)
{
    m_gridColor = color;
}

void Grid::draw(sf::RenderWindow& window)
{
    for (int x = 0; x < m_width; x += m_gridSize)
    {
        sf::Vertex line[] =
        {
            sf::Vertex(sf::Vector2f(x, 0), m_gridColor),
            sf::Vertex(sf::Vector2f(x, m_height), m_gridColor)
        };
        window.draw(line, 2, sf::Lines);
    }

    for (int y = 0; y < m_height; y += m_gridSize)
    {
        sf::Vertex line[] =
        {
            sf::Vertex(sf::Vector2f(0, y), m_gridColor),
            sf::Vertex(sf::Vector2f(m_width, y), m_gridColor)
        };
        window.draw(line, 2, sf::Lines);
    }
}

sf::Color Grid::GetGridColor()
{
    return m_gridColor;
}