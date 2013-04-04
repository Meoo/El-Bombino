/**
 * @file   Niveau.hpp
 * @author Bastien Brunnenstein
 */

#ifndef _NIVEAU_HPP_
#define _NIVEAU_HPP_

#include <SFML/Graphics.hpp>

/**
 * @brief
 */
class Niveau : public sf::Drawable
{
private:
	unsigned	_largeur;
	unsigned	_hauteur;
	Case **		_cases;			//!< Tableau de pointeurs de case (taille : largeur x hauteur)

public:
                    Niveau();
    virtual         ~Niveau();

    void            charger();
    void            liberer();

    // Fonction d'affichage de Drawable
    virtual void    draw(sf::RenderTarget & target, sf::RenderStates states) const;

    virtual void    mise_a_jour();

};
// class Niveau

#endif // _NIVEAU_HPP_
