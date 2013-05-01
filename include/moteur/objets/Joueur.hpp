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

    unsigned            _vies;
    mutable bool        _clignote;
    unsigned            _protection;

public:
    explicit            Joueur(Case * cse);
    virtual             ~Joueur();

    virtual const sf::Vector2f get_position_objet_souleve() const;

    // Fonction d'affichage de Drawable
    virtual void        draw(sf::RenderTarget & target, sf::RenderStates states) const;

    virtual void        mise_a_jour();

    virtual void        appliquer_bonus(Bonus::bonus_t type_bonus);

    virtual bool        est_joueur();

    virtual void        blesser();

    // Fonction utile pour l'affichage d'information du Joueur
    // < get_Vie, get_Puissance, get_BombeDisponible>
    const unsigned      get_nb_bombe_simultanee()const;
    unsigned            get_nb_bombe_simultanee();

    const unsigned      get_puissance_bombe() const;
    unsigned            get_puissance_bombe();

    const unsigned      get_vie() const;
    unsigned            get_vie();

};
// class Joueur

#endif // _JOUEUR_HPP_
