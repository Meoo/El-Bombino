/**
 * @file   Objet.hpp
 * @author Bastien Brunnenstein
 * @author Pascal-Pierre Sanchez-Carrion
 */

#ifndef _OBJET_HPP_
#define _OBJET_HPP_

#include "../Config.hpp"

#include <SFML/Graphics.hpp>

class Case;
class Soulevable;

/**
 * @brief
 */
class Objet : public sf::Drawable
{
    friend class Soulevable;

private:
    Case *          _case;
    bool            _valide;

                    Objet();        //!< Réservé pour Soulevable

public:
                    Objet(Case * cse);
    virtual         ~Objet();

    virtual Case *  get_case();
    virtual const Case * get_case() const;
    void            set_case(Case * cse);

    bool            est_valide() const;

    // Fonction d'affichage de Drawable
    virtual void    draw(sf::RenderTarget & target, sf::RenderStates states) const = 0;

    virtual void    mise_a_jour();

    virtual void    blesser();

    virtual void    glacee();

    virtual void    laisser_tomber_objet(Case * cse);

protected:
    void            detruire();

};
// class Objet

#endif // _OBJET_HPP_
