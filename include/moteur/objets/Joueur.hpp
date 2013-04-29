/**
 * @file   Joueur.hpp
 * @author Bastien Brunnenstein
 * @author Pascal-Pierre Sanchez-Carrion
 */

#ifndef _JOUEUR_HPP_
#define _JOUEUR_HPP_

#include "Mobile.hpp"

/**
 * @brief
 */
class Joueur : public Mobile
{
private:
    sf::Sprite          _sprite;
    Case*               _case_deposer_objet;
    unsigned            _bombe_cooldown;
    unsigned            _objet_souleve_cooldown;
    unsigned            _nb_bombes_simultanee;
    unsigned            _puissance_bombe;

public:
    explicit            Joueur(Case * cse);
    virtual             ~Joueur();

    virtual const sf::Vector2f get_position_objet_souleve() const;

    // Fonction d'affichage de Drawable
    virtual void        draw(sf::RenderTarget & target, sf::RenderStates states) const;

    virtual void        mise_a_jour();

};
// class Joueur

#endif // _JOUEUR_HPP_
