/*
 * Pause.cpp
 *
 *  Created on: 8 mai 2013
 *      Author: Sanpas
 */

#include <moteur/Pause.hpp>
#include <moteur/Jeu.hpp>

#include <Config.hpp>

#include <cmath>
#include <ctime>
#include <cstdlib>

#include <SFML/Graphics.hpp>


Pause::Pause(): _pause(false), _pause_frame(0)
{
    texte_pause = sf::Text("PAUSE", Jeu::instance().get_default_font());
    texte_pause.setCharacterSize(128);
    texte_pause.setColor(sf::Color::White);
    texte_pause.setOrigin(texte_pause.getLocalBounds().width / 2, texte_pause.getLocalBounds().height / 2);
    texte_pause.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);

    texte_pause_fond = sf::Text(texte_pause);
    texte_pause_fond.move(4, 4);
    texte_pause_fond.setColor(sf::Color::Black);
    texte_pause_fond.setStyle(sf::Text::Bold);

    fond_pause = sf::RectangleShape(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
    fond_pause.setFillColor(sf::Color(0, 0, 0, 128));

}

Pause::~Pause()
{
}

void Pause::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(fond_pause);

    target.draw(texte_pause_fond);
    target.draw(texte_pause);
}

void Pause::mise_a_jour()
{
    float a = std::sin(_pause_frame++ * 0.015f) * 3.f;
    texte_pause.setRotation(a);
    texte_pause_fond.setRotation(a);
}

void Pause::clic(int x, int y)
{
}

void Pause::set_active(bool pause)
{
    _pause = pause;
}

bool Pause::est_active()
{
    return _pause;
}
