/**
 * @file   Case.hpp
 * @author Bastien Brunnenstein
 */

#ifndef _CASE_HPP_
#define _CASE_HPP_

#include <SFML/Graphics.hpp>

#include "../Config.hpp"

class Objet;

/**
 * @brief
 */
class Case : public sf::Drawable
{
private:
    Objet *     _objet;
    sf::Sprite  _sprite;

    unsigned    _feu_duree;
    sf::Color   _feu_couleur;

public:
    Case();
    virtual ~Case();

    void enflammer(unsigned          duree   = FIRE_DEFAULT_TIME,
                   const sf::Color & couleur = FIRE_DEFAULT_COLOR);

    bool est_en_feu() const;
    unsigned get_duree_flammes() const;

    // Fonction d'affichage de Drawable
    virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;

};
// class Case

#endif // _CASE_HPP_
