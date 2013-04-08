/**
 * @file   Caisse.cpp
 * @author Bastien Brunnenstein
 * @author Pascal-Pierre Sanchez-Carrion
 */

#include <moteur/objets/Caisse.hpp>
#include <moteur/Jeu.hpp>
#include <moteur/Case.hpp>

Caisse::Caisse(Case * cse) :
        Soulevable(cse), _sprite(Jeu::instance().get_texture("caisse"))
{
    _sprite.setOrigin(_sprite.getTexture()->getSize().x / 2,
            _sprite.getTexture()->getSize().y - _sprite.getTexture()->getSize().x / 2);
    _sprite.setPosition(get_case()->get_x() * TILE_SIZE + TILE_SIZE / 2,
            get_case()->get_y() * TILE_SIZE + TILE_SIZE / 2);
}

Caisse::~Caisse()
{
}

void Caisse::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_sprite, states);
}
