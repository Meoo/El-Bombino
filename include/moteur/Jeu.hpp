/**
 * @file   Jeu.hpp
 * @author Bastien Brunnenstein
 * @author Pascal-Pierre Sanchez-Carrion
 */

#ifndef _JEU_HPP_
#define _JEU_HPP_

#include "../Config.hpp"
#include "Sauvegarde.hpp"
#include "Monde.hpp"

#include <SFML/Graphics.hpp>

#include <map>

/**
 * @brief
 */
class Jeu : public sf::Drawable
{
private:
    Jeu();                                  //!< Constructeur private car c'est un singleton

    sf::RenderWindow    _fenetre;

    std::map<std::string, sf::Texture> _textures;

    unsigned            _mondes_count;
    Monde **            _mondes;
    Monde *             _monde_courant;

    /*Sauvegarde          _sauvegarde;*/

    /*sf::Texture         _flammes_texture;   //!< Texture des flammes
    sf::Sprite          _flammes_coin;      //!< Sprite de flamme qui fait un coin
    sf::Sprite          _flammes_bord;      //!< Sprite de flamme qui fait un bord
    sf::Sprite          _flammes_jointure;  //!< Sprite de flamme qui fait une jointure
    sf::Sprite          _flammes_plein;     //!< Sprite de flamme qui est plein*/

    static Jeu          s_jeu;              //!< Singleton

public:
    virtual             ~Jeu();

    static Jeu &        instance();

    void                charger();
    void                liberer();

    const sf::Texture & get_texture(const std::string & res) const;

    Monde &             get_monde_courant();
    const Monde &       get_monde_courant() const;

    // Fonction d'affichage de Drawable
    virtual void        draw(sf::RenderTarget & target, sf::RenderStates states) const;

    virtual void        mise_a_jour();

/*TODO protected:*/
    void                set_monde_courant(unsigned num);

};
// class Jeu

#endif // _JEU_HPP_
