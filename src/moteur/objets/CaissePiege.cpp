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
        Soulevable(cse), _sprite(Jeu::instance().get_texture("caisse")), _explosive(true)
{
    _sprite.setOrigin(_sprite.getTexture()->getSize().x / 2,
            _sprite.getTexture()->getSize().y - _sprite.getTexture()->getSize().x / 2);
    _sprite.setPosition(get_case()->get_x() * TILE_SIZE + TILE_SIZE / 2,
            get_case()->get_y() * TILE_SIZE + TILE_SIZE / 2);
    _sprite.setColor(sf::Color(254, 75, 0));
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
    if(_explosive)
    {
        get_case()->enflammer_direction(nsUtil::BAS, 1);
        get_case()->enflammer_direction(nsUtil::DROITE, 1);
        get_case()->enflammer_direction(nsUtil::GAUCHE, 1);
        get_case()->enflammer_direction(nsUtil::HAUT, 1);
    }
}


// fin implementation class Caisse

void CaissePiege::glacee()
{
    _explosive = false;
    _sprite.setColor(sf::Color::Blue);
}// glacee()

void CaissePiege::laisser_tomber_objet(Case* cse)
{
    if(!_explosive)
    {
        int laisser_tomber = rand() % 4;

           if (laisser_tomber == 0){
               int bonus_ou_malus = rand() % 4;
               if(bonus_ou_malus != 0)
               {
                   int bonus_type = rand() % BONUS_BONUS_NB_DIFFERENTS_CAISSE;
                   switch (bonus_type) {
                       case Bonus::BONUS_BOMBE:
                           new Bonus(cse, Bonus::BONUS_BOMBE);
                           break;
                       case Bonus::BONUS_PUISSANCE:
                           new Bonus(cse, Bonus::BONUS_PUISSANCE);
                           break;
                       case Bonus::BONUS_VIE:
                           new Bonus(cse, Bonus::BONUS_VIE);
                           break;
                       case Bonus::BONUS_VITESSE:
                           new Bonus(cse, Bonus::BONUS_VITESSE);
                           break;
                   }
               }
               else {
                   int malus_type = (rand() % BONUS_MALUS_NB_DIFFERENTS_CAISSE) + BONUS_BONUS_NB_DIFFERENTS_CAISSE;
                   switch (malus_type) {
                       case Bonus::MALUS_BOMBE:
                           new Bonus(cse, Bonus::MALUS_BOMBE);
                           break;
                       case Bonus::MALUS_PUISSANCE:
                           new Bonus(cse, Bonus::MALUS_PUISSANCE);
                           break;
                       case Bonus::MALUS_VITESSE:
                           new Bonus(cse, Bonus::MALUS_VITESSE);
                           break;
                   }
               }
           }
    }
}// laisser_tomber_objet()
