/**
 * @file   Joueur.cpp
 * @author Bastien Brunnenstein
 * @author Pascal-Pierre Sanchez-Carrion
 */

#include <moteur/objets/Joueur.hpp>
#include <moteur/objets/Bombe.hpp>
#include <moteur/Jeu.hpp>
#include <moteur/Case.hpp>

#include <SFML/Window.hpp>

Joueur::Joueur(Case * cse) :
        Mobile(cse, JOUEUR_VIT_DEFAULT), _sprite(
                Jeu::instance().get_texture("joueur")), _case_charge_bombe(NULL), _bombe_cooldown(BOMBE_COOLDOWN)
{
    _sprite.setOrigin(_sprite.getTexture()->getSize().x / 2,
            _sprite.getTexture()->getSize().y
                    - _sprite.getTexture()->getSize().x / 2);
}

Joueur::~Joueur()
{
}

void Joueur::charger_bombe()
{
    // TODO Utiliser les bons paramètres
    new Bombe(this, 150, 3);
}

void Joueur::draw(sf::RenderTarget & target, sf::RenderStates states) const
{

    if (get_objet_souleve() != NULL)
    {
        if (_case_charge_bombe == NULL)
        {
            target.draw(_sprite, states);
            target.draw(*get_objet_souleve());
        }
        else
        {
            target.draw(*get_objet_souleve());
            target.draw(_sprite, states);
        }
    }
    else
        target.draw(_sprite, states);
}

const sf::Vector2f Joueur::get_position_objet_souleve() const
{
    if (_case_charge_bombe != NULL)
        return sf::Vector2f(
                get_objet_souleve()->get_case()->get_x() * TILE_SIZE
                        + TILE_SIZE / 2,
                get_objet_souleve()->get_case()->get_y() * TILE_SIZE
                        + TILE_SIZE / 2);
    else
        return Mobile::get_position_ecran();
}

void Joueur::mise_a_jour()
{
    if (_bombe_cooldown > 0)
        --_bombe_cooldown;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        bouger(HAUT);

    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        bouger(BAS);

    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        bouger(GAUCHE);

    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        bouger(DROITE);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        // Si le joueur ne porte pas d'objets
        if (get_objet_souleve() == NULL)
        {
            // Petit cooldown
            if (_bombe_cooldown == 0)
            {
                // Alors il peut sortir une bombe
                charger_bombe();
                _case_charge_bombe = this->get_case();
                _bombe_cooldown = BOMBE_COOLDOWN;
            }
        }
    }

    Mobile::mise_a_jour();

    //TODO soulever l'objet present dans la direction
    //TODO ou poser l'objet si il est en notre posetion
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::E))
    {
        if(get_objet_souleve() == NULL)
        {
            if(get_direction() == HAUT && get_case()->get_case_haut()->get_objet() != NULL)
            {
                //TODO si la case du haut est soulevable prendre l'objet
            }
            else if (get_direction() == BAS && get_case()->get_case_bas()->get_objet() != NULL)
            {
                //TODO si la case du bas est soulevable prendre l'objet
            }
            else if (get_direction() == DROITE && get_case()->get_case_droite()->get_objet() != NULL)
            {
                //TODO si la case de droite est soulevable prendre l'objet
            }
            else if (get_direction() == GAUCHE && get_case()->get_case_gauche()->get_objet() != NULL)
            {
                //TODO si la case de gauche est soulevable prendre l'objet
            }
        }
        else
        {
            //TODO poser l'objet
            if(get_direction() == HAUT && get_case()->get_case_haut()->get_objet() == NULL)
            {
               //TODO poser l'objet get_case()->get_case_haut()
            }
            else if (get_direction() == BAS && get_case()->get_case_bas()->get_objet() == NULL)
            {
               //TODO poser l'objet get_case()->get_case_bas()
            }
            else if (get_direction() == DROITE && get_case()->get_case_droite()->get_objet() == NULL)
            {
               //TODO poser l'objet get_case()->get_case_droite()
            }
            else if (get_direction() == GAUCHE && get_case()->get_case_gauche()->get_objet() == NULL)
            {
               //TODO poser l'objet get_case()->get_case_gauche()
            }
        }
    }

    if (_case_charge_bombe != NULL && _case_charge_bombe != this->get_case())
    {
        get_objet_souleve()->deposer(_case_charge_bombe);
        _case_charge_bombe->get_objet()->mise_a_jour();
        _case_charge_bombe = NULL;
    }

    _sprite.setPosition(get_position_ecran());

// TODO Gérer la direction
}
