/**
 * @file   Caisse.cpp
 * @author Bastien Brunnenstein
 * @author Pascal-Pierre Sanchez-Carrion
 */

#include <moteur/objets/Caisse.hpp>
#include <moteur/objets/Mobile.hpp>
#include <moteur/objets/Bonus.hpp>
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
}// draw()


void Caisse::mise_a_jour()
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


void Caisse::laisser_tomber_objet(Case* cse)
{
    int laisser_tomber = rand() % 4;

    if (laisser_tomber == 0){
        int bonus_ou_malus = rand() % 4;
        if(bonus_ou_malus == 0 || bonus_ou_malus == 1)
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
        else if(bonus_ou_malus == 2 || bonus_ou_malus == 3){
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
}// laisser_tomber_objet()

sf::Sprite& Caisse::get_sprite()
{
    return _sprite;
}//get_sprite()
// fin implementation class Caisse
