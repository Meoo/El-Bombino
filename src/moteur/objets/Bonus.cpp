/**
 * @file   Bonus.cpp
 * @author Bastien Brunnenstein
 * @author Pascal-Pierre Sanchez-Carrion
 */

#include <moteur/objets/Immobile.hpp>
#include <moteur/objets/Mobile.hpp>
#include <moteur/objets/Bonus.hpp>
#include <moteur/Objet.hpp>
#include <moteur/Case.hpp>
#include <moteur/Jeu.hpp>

Bonus::Bonus(Case* cse, bonus_t type_bonus) : Immobile(cse)
{
    _type_bonus = type_bonus;
    switch(_type_bonus)
    {
        case(BONUS_BOMBE):
                _sprite.setTexture(Jeu::instance().get_texture("bonus_bombe"),true);
                break;
        case(BONUS_PUISSANCE):
                _sprite.setTexture(Jeu::instance().get_texture("bonus_puissance"),true);
                break;
        case(BONUS_VITESSE):
                _sprite.setTexture(Jeu::instance().get_texture("bonus_vitesse"),true);
                break;
        case(BONUS_VIE):
                _sprite.setTexture(Jeu::instance().get_texture("bonus_vie"),true);
                break;
    }
    _sprite.setOrigin(_sprite.getTexture()->getSize().x / 2,
                _sprite.getTexture()->getSize().y - _sprite.getTexture()->getSize().x / 2);
    _sprite.setPosition(get_case()->get_x() * TILE_SIZE + TILE_SIZE / 2,
                get_case()->get_y() * TILE_SIZE + TILE_SIZE / 2);
}

Bonus::~Bonus()
{
}

void Bonus::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_sprite, states);
}

void Bonus::mise_a_jour()
{
    Immobile::mise_a_jour();
}

void Bonus::blesser()
{
}

void Bonus::utiliser(Mobile * mobile)
{
    mobile->appliquer_bonus(_type_bonus);
    detruire();
}
