/**
 * @file   Monde.hpp
 * @author Bastien Brunnenstein
 * @author Pascal-Pierre Sanchez-Carrion
 */

#ifndef _MONDE_HPP_
#define _MONDE_HPP_

#include "../Config.hpp"
#include "Niveau.hpp"

#include <SFML/Graphics.hpp>

#include <map>
#include <vector>


/**
 * @brief
 */
class Monde : public sf::Drawable
{
private:
    struct Tuile
    {
        std::string classe_case;
        std::string texture_case;
        std::string classe_objet;
    };

    std::map<std::string, std::vector<sf::Texture> > _textures;

    const std::string   _fichier_rc;
    unsigned            _niveaux_count;
    Niveau **           _niveaux;
    Niveau *            _niveau_courant;
    unsigned            _num_niveau_courant;
    bool                _fini;

    std::map<char, Tuile> _usine_cases;

#ifndef NDEBUG
    bool                _pret;
#endif

public:
    explicit            Monde(const std::string & fic);
    virtual             ~Monde();

    Niveau &            get_niveau_courant();
    const Niveau &      get_niveau_courant() const;

    void                charger();
    void                liberer();

    bool                has_texture(const std::string & res) const;
    const sf::Texture & get_texture(const std::string & res) const;

    // Fonction d'affichage de Drawable
    virtual void        draw(sf::RenderTarget & target, sf::RenderStates states) const;

    virtual void        mise_a_jour();

    Case *              creer_case(unsigned x, unsigned y, char tuile) const;

    const unsigned      get_num_niveau_courant() const;
    unsigned            get_num_niveau_courant();

    bool                est_fini();

/*TODO protected:*/
    void                set_niveau_courant(unsigned num);


    unsigned            get_count_niveaux(){ return _niveaux_count; }

};
// class Monde

#endif // _MONDE_HPP_
