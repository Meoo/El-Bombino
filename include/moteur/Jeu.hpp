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
#include <moteur/Menu.hpp>

#include <SFML/Graphics.hpp>

#include <map>
#include <vector>

/**
 * @brief
 */
class Jeu : public sf::Drawable
{
private:
    Jeu();                                  //!< Constructeur private car c'est un singleton

    sf::RenderWindow    _fenetre;

    std::map<std::string, std::vector<sf::Texture> > _textures;

    unsigned            _mondes_count;
    Monde **            _mondes;
    Monde *             _monde_courant;
    sf::Font            _default_font;

    Menu *              _menu;
    unsigned            _num_monde_courant;


    //Sauvegarde des données du joueur
    float               _vitesse_joueur;
    unsigned            _nb_bombe_joueur;
    unsigned            _puissance_joueur;
    unsigned            _vie_joueur;
    bool                _bonus_soulevable_joueur;
    bool                _bonus_bombe_special_joueur;

#ifndef NDEBUG
    bool                _pret;
#endif

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

    const sf::Font &    get_default_font() const;

    void                clic(int x, int y);

    void                lost_focus();

    void                press_pause();

    const Menu *        get_menu() const;
    Menu *              get_menu();

    //
    // sauvegarde donnée du joueur
    const unsigned      get_num_monde_courant() const;
    unsigned            get_num_monde_courant();

    const float         get_vitesse_joueur() const;
    float               get_vitesse_joueur();

    const unsigned      get_nb_bombe_joueur() const;
    unsigned            get_nb_bombe_joueur();

    const unsigned      get_puissance_joueur() const;
    unsigned            get_puissance_joueur();

    const unsigned      get_vie_joueur() const;
    unsigned            get_vie_joueur();

    const bool          get_bonus_soulevable_joueur() const;
    bool                get_bonus_soulevable_joueur();

    const bool          get_bonus_bombe_special_joueur() const;
    bool                get_bonus_bombe_special_joueur();

    void                sauve_donnees_joueur();

    void                charger_donnees_joueur(float vitesse_joueur, unsigned nb_bombe_joueur,
                                               unsigned puissance_joueur, unsigned vie_joueur,
                                               bool bonus_soulevable_joueur, bool  bonus_bombe_special_joueur);

    void                set_num_monde_courant(unsigned num);
/*TODO protected:*/
    void                set_monde_courant(unsigned num);
};
// class Jeu

#endif // _JEU_HPP_
