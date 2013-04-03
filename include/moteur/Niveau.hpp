/**
 * @file   Niveau.hpp
 * @author Bastien Brunnenstein
 */

#ifndef _NIVEAU_HPP_
#define _NIVEAU_HPP_

/**
 * @brief
 */
class Niveau
{
private:
	unsigned	_largeur;
	unsigned	_hauteur;
	Case **		_cases;			//!< Tableau de pointeurs de case (taille : largeur x hauteur)

public:
    Niveau();
    virtual ~Niveau();

    virtual void mise_a_jour();

};
// class Niveau

#endif // _NIVEAU_HPP_
