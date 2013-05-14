/**
 * @file   CaissePiege.cpp
 * @author Bastien Brunnenstein
 * @author Pascal-Pierre Sanchez-Carrion
 */

#include <moteur/objets/CaissePiege.hpp>
#include <moteur/objets/Mobile.hpp>
#include <moteur/objets/Bombe.hpp>
#include <moteur/Jeu.hpp>
#include <moteur/Case.hpp>

CaissePiege::CaissePiege(Case * cse) :
        Soulevable(cse), _sprite(Jeu::instance().get_texture("caisse"))
{
    _sprite.setOrigin(_sprite.getTexture()->getSize().x / 2,
            _sprite.getTexture()->getSize().y - _sprite.getTexture()->getSize().x / 2);
    _sprite.setPosition(get_case()->get_x() * TILE_SIZE + TILE_SIZE / 2,
            get_case()->get_y() * TILE_SIZE + TILE_SIZE / 2);
    _sprite.setColor(FEU_COLOR_DEFAULT);
}


CaissePiege::~CaissePiege()
{
}


void CaissePiege::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_sprite, states);
}// draw()


void CaissePiege::mise_a_jour()
{
    Soulevable::mise_a_jour();

    if (get_porteur() == NULL)
    {
        _sprite.setPosition(get_case()->get_x() * TILE_SIZE + TILE_SIZE / 2,
                get_case()->get_y() * TILE_SIZE + TILE_SIZE / 2);
    }
    else
    {
        _sprite.setPosition(get_porteur()->get_position_objet_souleve());
    }
}// mise_a_jour()


void CaissePiege::blesser()
{
    Soulevable::blesser();
    get_case()->enflammer_direction(nsUtil::BAS, 1);
    get_case()->enflammer_direction(nsUtil::DROITE, 1);
    get_case()->enflammer_direction(nsUtil::GAUCHE, 1);
    get_case()->enflammer_direction(nsUtil::HAUT, 1);
}


// fin implementation class Caisse

