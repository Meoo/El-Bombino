/**
 * @file   Case.hpp
 * @author Bastien Brunnenstein
 * @author Pascal-Pierre Sanchez-Carrion
 */

#ifndef _CASE_HPP_
#define _CASE_HPP_

#include "../Config.hpp"

#include <SFML/Graphics.hpp>

class Objet;

/**
 * @brief
 */
class Case : public sf::Drawable
{
private:
    Objet *         _objet;
    const sf::Texture * _texture;

    unsigned        _feu_duree;
    sf::Color       _feu_couleur;

    const unsigned  _x;
    const unsigned  _y;

public:
                    Case(unsigned x, unsigned y, const sf::Texture & texture);
    virtual         ~Case();

    Objet *         get_objet();
    const Objet *   get_objet() const;

    /// Renvoyer false si les flammes ne passe pas au travers de la case
    virtual bool    enflammer(unsigned          duree   = FIRE_DEFAULT_TIME,
                              const sf::Color & couleur = FIRE_DEFAULT_COLOR);

    bool            est_en_feu() const;
    unsigned        get_duree_flammes() const;

    virtual bool    est_praticable();

    // Fonction d'affichage de Drawable
    virtual void    draw(sf::RenderTarget & target, sf::RenderStates states) const;

    virtual void    mise_a_jour();

};
// class Case

#endif // _CASE_HPP_
