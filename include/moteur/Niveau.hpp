/**
 * @file   Niveau.hpp
 * @author Bastien Brunnenstein
 * @author Pascal-Pierre Sanchez-Carrion
 */

#ifndef _NIVEAU_HPP_
#define _NIVEAU_HPP_

#include "../Config.hpp"
#include <moteur/Case.hpp>
#include <moteur/objets/Bombe.hpp>

#include <SFML/Graphics.hpp>
#include <list>

class Joueur;
class Case;
class Monde;
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
	std::list<Bombe *>      _bombes_actives;
	bool                    _fini;
	unsigned                _timer_fini;
	unsigned                _timer_game_over;

#ifndef NDEBUG
    bool                _pret;
#endif

public:
    explicit            Niveau(const std::string & fic);
    virtual             ~Niveau();

    void                charger(const Monde * parent);
    void                liberer();

    Case *              get_case(unsigned x, unsigned y);
    const Case *        get_case(unsigned x, unsigned y) const;

    Joueur *            get_joueur();
    const Joueur *      get_joueur() const;

    void                delete_joueur();
    void                ajouter_joueur(Joueur *joueur);


    std::list<MobileIA *>  &        get_pnjs();
    const std::list<MobileIA *> &   get_pnjs() const;

    void                            delete_pnj(MobileIA* pnj);
    void                            ajouter_pnj(MobileIA* pnj);

    std::list<Bombe *> &            get_bombes_actives();
    const std::list<Bombe *> &      get_bombes_actives() const;

    void                            delete_bombe(Bombe* bombe);
    void                            ajouter_bombe_active(Bombe* bombe);

    bool                            est_fini();

    // Fonction d'affichage de Drawable
    virtual void        draw(sf::RenderTarget & target, sf::RenderStates states) const;

    virtual void        mise_a_jour();

private :
    void                generer_info_case(Case *cse, unsigned distance = 0, nsUtil::direction_t direction = nsUtil::ORIGINE);
};
// class Niveau

#endif // _NIVEAU_HPP_
