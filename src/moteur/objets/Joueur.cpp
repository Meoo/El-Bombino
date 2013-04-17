/**
 * @file   Joueur.cpp
 * @author Bastien Brunnenstein
 * @author Pascal-Pierre Sanchez-Carrion
 */

#include <moteur/objets/Joueur.hpp>
#include <moteur/Jeu.hpp>
#include <moteur/objets/Bombe.hpp>

#include <SFML/Window.hpp>

Joueur::Joueur(Case * cse) :
        Mobile(cse, JOUEUR_VIT_DEFAULT), _sprite(Jeu::instance().get_texture("joueur")), _case_charge_bombe(NULL)
{
    _sprite.setOrigin(_sprite.getTexture()->getSize().x / 2, _sprite.getTexture()->getSize().y - _sprite.getTexture()->getSize().x / 2);
}

Joueur::~Joueur()
{
}


void Joueur::charger_bombe()
{
    new Bombe(this,100,10);
}


void Joueur::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
    target.draw(_sprite, states);

    if (get_objet_souleve() != NULL)
        target.draw(*get_objet_souleve());
}

void Joueur::mise_a_jour()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) bouger(HAUT);

    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) bouger(BAS);

    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) bouger(GAUCHE);

    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) bouger(DROITE);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
        if(get_objet_souleve() == NULL){
            charger_bombe();
            _case_charge_bombe = this->get_case();
        }
    }

    Mobile::mise_a_jour();

    if(_case_charge_bombe != NULL && _case_charge_bombe != this->get_case())
    {
        get_objet_souleve()->deposer(_case_charge_bombe);
        _case_charge_bombe = NULL;
    }

    _sprite.setPosition(get_position_ecran());

    // TODO Gérer la direction
}

