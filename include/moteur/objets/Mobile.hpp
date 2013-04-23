/**
 * @file   Mobile.hpp
 * @author Bastien Brunnenstein
 * @author Pascal-Pierre Sanchez-Carrion
 */

#ifndef _MOBILE_HPP_
#define _MOBILE_HPP_

#include "../Objet.hpp"

class Soulevable;

/**
 * @brief
 */
class Mobile : public Objet
{
    friend class Soulevable;

public:
    enum Direction
    {
        DROITE,
        GAUCHE,
        HAUT,
        BAS,
    };

private:
    Soulevable *        _objet_souleve;
    float               _vitesse;

    Direction           _direction;
    bool                _bouge;
    float               _deplacement;
    sf::Vector2f        _position_ecran;
    bool                _change_case;

public:
                        Mobile(Case * cse, float vitesse);
    virtual             ~Mobile();

    Soulevable *        get_objet_souleve();
    const Soulevable *  get_objet_souleve() const;

    void                bouger(Direction dir);
    bool                est_en_mouvement() const;

    float               get_vitesse() const;
    void                set_vitesse(float vitesse);

    Direction           get_direction() const;
    const sf::Vector2f & get_position_ecran() const;
    virtual const sf::Vector2f get_position_objet_souleve() const;

    virtual void        mise_a_jour();

    virtual void        blesser();

};
// class Mobile

#endif // _MOBILE_HPP_
