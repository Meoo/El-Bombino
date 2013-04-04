/**
 * @file   Niveau.hpp
 * @author Bastien Brunnenstein
 */

#ifndef _NIVEAU_HPP_
#define _NIVEAU_HPP_

#include "../Config.hpp"

#include <SFML/Graphics.hpp>

class Case;

/**
 * @brief
 */
class Niveau : public sf::Drawable
{
private:
    const std::string   _fichier_rc;
	unsigned	_largeur;
	unsigned	_hauteur;
	Case **		_cases;			//!< Tableau de pointeurs de case (taille : largeur x hauteur)

public:
                    Niveau(const std::string & fic);
    virtual         ~Niveau();

    void            charger();
    void            liberer();

    // Fonction d'affichage de Drawable
    virtual void    draw(sf::RenderTarget & target, sf::RenderStates states) const;

    virtual void    mise_a_jour();

};
// class Niveau

#endif // _NIVEAU_HPP_
