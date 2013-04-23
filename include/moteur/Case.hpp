/**
 * @file   Case.hpp
 * @author Bastien Brunnenstein
 * @author Pascal-Pierre Sanchez-Carrion
 */

#ifndef _CASE_HPP_
#define _CASE_HPP_

#include "../Config.hpp"
#include "Objet.hpp"

#include <SFML/Graphics.hpp>

class Objet;
class Soulevable;

/**
 * @brief
 */
class Case : public sf::Drawable
{
    friend class Objet;
    friend class Soulevable;

    typedef void (Objet::* objet_effet_t) (void);

private:
    Objet *         _objet;
    const sf::Texture * _texture;

    unsigned        _feu_duree;
    sf::Color       _feu_couleur;
    objet_effet_t   _feu_effet;


    const unsigned  _x;
    const unsigned  _y;

public:
                    Case(unsigned x, unsigned y, const sf::Texture & texture);
    virtual         ~Case();

    Objet *         get_objet();
    const Objet *   get_objet() const;

    unsigned        get_x() const;
    unsigned        get_y() const;

    Case *          get_case_droite();
    const Case *    get_case_droite() const;

    Case *          get_case_gauche();
    const Case *    get_case_gauche() const;

    Case *          get_case_haut();
    const Case *    get_case_haut() const;

    Case *          get_case_bas();
    const Case *    get_case_bas() const;

    /// Renvoyer false si les flammes ne passe pas au travers de la case
    virtual bool    enflammer(unsigned          duree   = FEU_TIME_DEFAULT,
                              const sf::Color & couleur = FEU_COLOR_DEFAULT,
                              objet_effet_t     effet   = &Objet::blesser);

    bool            est_en_feu() const;
    unsigned        get_duree_flammes() const;

    virtual bool    est_praticable();

    // Fonction d'affichage de Drawable
    virtual void    draw(sf::RenderTarget & target, sf::RenderStates states) const;

    virtual void    mise_a_jour();

private:
    void            set_objet(Objet * objet);
};
// class Case

#endif // _CASE_HPP_
