//
//	shapes.h
//
#pragma once

#include <SFML/Graphics.hpp>

#include "defines.h" // for font folder macro

//
// manages all of our shape objects, only has one of each shape that we reuse
// to remove the overhead for when the project gets larger and we have a million shapes
//
// singleton so that there is only one instance of each shap
//
class shape_manager_t
{
private:

    //
    // made private so that new instances cant be created, sets all of our shapes default values
    // for when we first go to use them
    //
    shape_manager_t()
    {
        // try load our default font, and throw an error if we cant
        if (!m_font.loadFromFile(CONCAT(FONT_FOLDER, "pixel.ttf")))
            throw std::runtime_error("[error] default font file not found!");

        // Initialize rectangle
        m_rect.setSize(sf::Vector2f(100, 50));
        m_rect.setFillColor(sf::Color::Green);

        // Initialize line (as thin rectangle)
        m_line.setSize(sf::Vector2f(200, 5));
        m_line.setFillColor(sf::Color::Red);

        // Initialize circle
        m_circle.setRadius(50);
        m_circle.setFillColor(sf::Color::Blue);
        m_circle.setPointCount(50);

        // Initialize polygon (convex shape)
        m_poly.setPointCount(4);
        m_poly.setPoint(0, sf::Vector2f(0, 0));
        m_poly.setPoint(1, sf::Vector2f(100, 0));
        m_poly.setPoint(2, sf::Vector2f(75, 50));
        m_poly.setPoint(3, sf::Vector2f(25, 50));
        m_poly.setFillColor(sf::Color::Yellow);

        // Initialize text
        m_text.setPosition(0, 0);
        m_text.setFont(m_font);
        m_text.setString("not set");
        m_text.setCharacterSize(12);
        m_text.setFillColor(sf::Color::Transparent);
    }

public:

    // rectangle shape
    sf::RectangleShape m_rect;

    // line shape
    sf::RectangleShape m_line;

    // circle shape
    sf::CircleShape m_circle;

    // polygon shape
    sf::ConvexShape m_poly;

    // text label
    sf::Text m_text;

    // our default font
    // TODO : maybe move elsewhere
    sf::Font m_font;

    //
    // returns our singleton instance
    //
    static shape_manager_t& get()
    {
        static shape_manager_t inst;
        return inst;
    }
};

//
// simple wrapper for readability
//
namespace shape
{
    inline sf::RectangleShape*  rect()  { return &shape_manager_t::get().m_rect; }
    inline sf::RectangleShape*  line()  { return &shape_manager_t::get().m_line; }
    inline sf::CircleShape*     circle(){ return &shape_manager_t::get().m_circle; }
    inline sf::ConvexShape*     poly()  { return &shape_manager_t::get().m_poly; }
    inline sf::Text*            text()  { return &shape_manager_t::get().m_text; }

    // TODO : Vertex line / freedraw line
}