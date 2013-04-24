/**
 * @file   Niveau.hpp
 * @author Bastien Brunnenstein
 * @author Pascal-Pierre Sanchez-Carrion
 */

#ifndef _NIVEAU_HPP_
#define _NIVEAU_HPP_

#include "../Config.hpp"


#include <SFML/Graphics.hpp>
#include <list>

class Joueur;
class Case;
class MobileIA;

/**
 * @brief
 */
class Niveau : public sf::Drawable
{
private:
    const std::string       _fichier_rc;
	unsigned	            _largeur;
	unsigned	            _hauteur;
	Case **		            _cases;			//!< Tableau de pointeurs de case (taille : largeur x hauteur)
	Joueur *                _joueur;
	std::list<MobileIA *>   _pnjs;

#ifndef NDEBUG
    bool                _pret;
#endif

public:
    explicit            Niveau(const std::string & fic);
    virtual             ~Niveau();

    void                charger();
    void                liberer();

    Case *              get_case(unsigned x, unsigned y);
    const Case *        get_case(unsigned x, unsigned y) const;

    Joueur *            get_joueur();
    const Joueur *      get_joueur() const;

    void                delete_joueur();

    std::list<MobileIA *>  &        get_pnjs();
    const std::list<MobileIA *> &   get_pnjs() const;

    void                            delete_pnj(MobileIA* pnj);

    // Fonction d'affichage de Drawable
    virtual void        draw(sf::RenderTarget & target, sf::RenderStates states) const;

    virtual void        mise_a_jour();

};
// class Niveau

#endif // _NIVEAU_HPP_
