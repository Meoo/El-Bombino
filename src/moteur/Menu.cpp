/**
 * @file   Jeu.cpp
 * @author Bastien Brunnenstein
 * @author Pascal-Pierre Sanchez-Carrion
 */


#include <moteur/Menu.hpp>
#include <moteur/Jeu.hpp>
#include <moteur/objets/Joueur.hpp>

#include <Config.hpp>

#include <cmath>
#include <ctime>
#include <cstdlib>

#include <SFML/Graphics.hpp>

Menu::Menu():  _menu_type(MENU_PRINCIPAL), _pause_frame(0)
{
    //
    // MENU PRINCIPAL
    //
    _menu_principal_play = sf::Text("NOUVELLE PARTIE",Jeu::instance().get_default_font());
    _menu_principal_play.setCharacterSize(32);
    _menu_principal_play.setColor(sf::Color::Black);
    _menu_principal_play.setOrigin(_menu_principal_play.getLocalBounds().width / 2, _menu_principal_play.getLocalBounds().height / 2);
    _menu_principal_play.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT * 2/ 8);

    _menu_principal_charger = sf::Text("CHARGER PARTIE", Jeu::instance().get_default_font());
    _menu_principal_charger.setCharacterSize(32);
    _menu_principal_charger.setColor(sf::Color::Black);
    _menu_principal_charger.setOrigin(_menu_principal_charger.getLocalBounds().width / 2, _menu_principal_charger.getLocalBounds().height / 2);
    _menu_principal_charger.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT * 3/ 8);

    _menu_principal_config = sf::Text("CONFIGURATION",Jeu::instance().get_default_font());
    _menu_principal_config.setCharacterSize(32);
    _menu_principal_config.setColor(sf::Color::Black);
    _menu_principal_config.setOrigin(_menu_principal_config.getLocalBounds().width / 2, _menu_principal_config.getLocalBounds().height / 2);
    _menu_principal_config.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT * 4/ 8);


    _menu_principal_quitter = sf::Text("QUITTER", Jeu::instance().get_default_font());
    _menu_principal_quitter.setCharacterSize(32);
    _menu_principal_quitter.setColor(sf::Color::Black);
    _menu_principal_quitter.setOrigin(_menu_principal_quitter.getLocalBounds().width / 2, _menu_principal_quitter.getLocalBounds().height / 2);
    _menu_principal_quitter.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT * 5/ 8);

    _fond_mp_play = sf::RectangleShape(sf::Vector2f(_menu_principal_play.getLocalBounds().width, _menu_principal_play.getGlobalBounds().height * 2));
    _fond_mp_play.setOrigin(_menu_principal_play.getOrigin());
    _fond_mp_play.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT * 2/ 8);
    _fond_mp_play.setFillColor(sf::Color::White);

    _fond_mp_charger = sf::RectangleShape(sf::Vector2f(_menu_principal_charger.getLocalBounds().width, _menu_principal_charger.getLocalBounds().height * 2));
    _fond_mp_charger.setOrigin(_menu_principal_charger.getLocalBounds().width / 2, _menu_principal_charger.getLocalBounds().height / 2);
    _fond_mp_charger.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT * 3/ 8);
    _fond_mp_charger.setFillColor(sf::Color::White);

    _fond_mp_config = sf::RectangleShape(sf::Vector2f(_menu_principal_config.getLocalBounds().width, _menu_principal_config.getLocalBounds().height * 2));
    _fond_mp_config.setOrigin(_menu_principal_config.getLocalBounds().width / 2, _menu_principal_config.getLocalBounds().height / 2);
    _fond_mp_config.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT * 4/ 8);
    _fond_mp_config.setFillColor(sf::Color::White);

    _fond_mp_quitter = sf::RectangleShape(sf::Vector2f(_menu_principal_quitter.getLocalBounds().width, _menu_principal_quitter.getLocalBounds().height * 2));
    _fond_mp_quitter.setOrigin(_menu_principal_quitter.getLocalBounds().width / 2, _menu_principal_quitter.getLocalBounds().height / 2);
    _fond_mp_quitter.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT * 5/ 8);
    _fond_mp_quitter.setFillColor(sf::Color::White);

    //
    // MENU CONFIGURATION
    //
    _menu_config_retour = sf::Text("RETOUR", Jeu::instance().get_default_font());
    _menu_config_retour.setCharacterSize(32);
    _menu_config_retour.setColor(sf::Color::Black);
    _menu_config_retour.setOrigin(_menu_config_retour.getLocalBounds().width / 2, _menu_config_retour.getLocalBounds().height / 2);
    _menu_config_retour.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT * 5/ 8);

    _fond_mc_retour = sf::RectangleShape(sf::Vector2f(_menu_config_retour.getLocalBounds().width, _menu_config_retour.getGlobalBounds().height * 2));
    _fond_mc_retour.setOrigin(_menu_config_retour.getOrigin());
    _fond_mc_retour.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT * 5/ 8);
    _fond_mc_retour.setFillColor(sf::Color::White);


    fond_menu_picture.loadFromFile(RC_FOLDER + RC_FONDMENU);

    //
    // MENU PAUSE
    //
    _sauvegarder = sf::Text("SAUVEGARDER",Jeu::instance().get_default_font());
    _sauvegarder.setCharacterSize(28);
    _sauvegarder.setColor(sf::Color::Black);
    _sauvegarder.setOrigin(_sauvegarder.getLocalBounds().width / 2, _sauvegarder.getLocalBounds().height / 2);
    _sauvegarder.setPosition(WINDOW_WIDTH / 4, WINDOW_HEIGHT / 4);


    _sauvegarder_fond = sf::RectangleShape(sf::Vector2f(_sauvegarder.getLocalBounds().width, _sauvegarder.getGlobalBounds().height * 2));
    _sauvegarder_fond.setOrigin(_sauvegarder.getOrigin());
    _sauvegarder_fond.setPosition(WINDOW_WIDTH / 4, WINDOW_HEIGHT / 4);
    _sauvegarder_fond.setFillColor(sf::Color(255, 255, 255, 128));

    _retour_menu_principal = sf::Text("RETOUR MENU PRINCIPAL",Jeu::instance().get_default_font());
    _retour_menu_principal.setCharacterSize(28);
    _retour_menu_principal.setColor(sf::Color::Black);
    _retour_menu_principal.setOrigin(_retour_menu_principal.getLocalBounds().width / 2, _retour_menu_principal.getLocalBounds().height / 2);
    _retour_menu_principal.setPosition(WINDOW_WIDTH * 3 / 4, WINDOW_HEIGHT / 4);


    _retour_menu_principal_fond = sf::RectangleShape(sf::Vector2f(_retour_menu_principal.getLocalBounds().width, _retour_menu_principal.getGlobalBounds().height * 2));
    _retour_menu_principal_fond.setOrigin(_retour_menu_principal.getOrigin());
    _retour_menu_principal_fond.setPosition(WINDOW_WIDTH * 3/ 4, WINDOW_HEIGHT / 4);
    _retour_menu_principal_fond.setFillColor(sf::Color(255, 255, 255, 128));

    _texte_pause = sf::Text("PAUSE", Jeu::instance().get_default_font());
    _texte_pause.setCharacterSize(128);
    _texte_pause.setColor(sf::Color::White);
    _texte_pause.setOrigin(_texte_pause.getLocalBounds().width / 2, _texte_pause.getLocalBounds().height / 2);
    _texte_pause.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);

    _texte_pause_fond = sf::Text(_texte_pause);
    _texte_pause_fond.move(4, 4);
    _texte_pause_fond.setColor(sf::Color::Black);
    _texte_pause_fond.setStyle(sf::Text::Bold);

    _fond_pause = sf::RectangleShape(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
    _fond_pause.setFillColor(sf::Color(0, 0, 0, 128));


    //
    // NIVEAU SUIVANT
    //
    _niveau_suivant = sf::Text("NIVEAU SUIVANT",Jeu::instance().get_default_font());
    _niveau_suivant.setCharacterSize(32);
    _niveau_suivant.setColor(sf::Color::Black);
    _niveau_suivant.setOrigin(_niveau_suivant.getLocalBounds().width / 2, _niveau_suivant.getLocalBounds().height / 2);
    _niveau_suivant.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);


    _niveau_suivant_fond = sf::RectangleShape(sf::Vector2f(_niveau_suivant.getLocalBounds().width, _niveau_suivant.getGlobalBounds().height * 2));
    _niveau_suivant_fond.setOrigin(_niveau_suivant.getOrigin());
    _niveau_suivant_fond.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
    _niveau_suivant_fond.setFillColor(sf::Color(255, 255, 255, 128));

    //
    // MONDE SUIVANT
    //
    _monde_suivant = sf::Text("MONDE SUIVANT",Jeu::instance().get_default_font());
    _monde_suivant.setCharacterSize(32);
    _monde_suivant.setColor(sf::Color::Black);
    _monde_suivant.setOrigin(_monde_suivant.getLocalBounds().width / 2, _monde_suivant.getLocalBounds().height / 2);
    _monde_suivant.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);


    _monde_suivant_fond = sf::RectangleShape(sf::Vector2f(_monde_suivant.getLocalBounds().width, _monde_suivant.getGlobalBounds().height * 2));
    _monde_suivant_fond.setOrigin(_monde_suivant.getOrigin());
    _monde_suivant_fond.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
    _monde_suivant_fond.setFillColor(sf::Color(255, 255, 255, 128));

    //
    // GAME OVER
    //
    _game_over = sf::Text("GAME OVER RECOMMENCER",Jeu::instance().get_default_font());
    _game_over.setCharacterSize(32);
    _game_over.setColor(sf::Color::Black);
    _game_over.setOrigin(_game_over.getLocalBounds().width / 2, _game_over.getLocalBounds().height / 2);
    _game_over.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);


    _game_over_fond = sf::RectangleShape(sf::Vector2f(_game_over.getLocalBounds().width, _game_over.getGlobalBounds().height * 2));
    _game_over_fond.setOrigin(_game_over.getOrigin());
    _game_over_fond.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
    _game_over_fond.setFillColor(sf::Color(255, 255, 255, 128));

    //
    // JEU FINI
    //
    _fin_jeu = sf::Text("FIN DU JEU FELICITATION",Jeu::instance().get_default_font());
    _fin_jeu.setCharacterSize(32);
    _fin_jeu.setColor(sf::Color::Black);
    _fin_jeu.setOrigin(_fin_jeu.getLocalBounds().width / 2, _fin_jeu.getLocalBounds().height / 2);
    _fin_jeu.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);


    _fin_jeu_fond = sf::RectangleShape(sf::Vector2f(_fin_jeu.getLocalBounds().width, _fin_jeu.getGlobalBounds().height * 2));
    _fin_jeu_fond.setOrigin(_fin_jeu.getOrigin());
    _fin_jeu_fond.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
    _fin_jeu_fond.setFillColor(sf::Color(255, 255, 255, 128));

    //
    //QUITTER
    //
    _quitter_1 = sf::Text("Jeu realiser dans le cadre du projet de fin de quatrieme annees",Jeu::instance().get_default_font());
    _quitter_1.setCharacterSize(28);
    _quitter_1.setColor(sf::Color::White);
    _quitter_1.setOrigin(_quitter_1.getLocalBounds().width / 2, _quitter_1.getLocalBounds().height / 2);
    _quitter_1.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 4);

    _quitter_2 = sf::Text("Bastien & Pascal-Pierre (r) Polytech'Marseille",Jeu::instance().get_default_font());
    _quitter_2.setCharacterSize(28);
    _quitter_2.setColor(sf::Color::White);
    _quitter_2.setOrigin(_quitter_2.getLocalBounds().width / 2, _quitter_2.getLocalBounds().height / 2);
    _quitter_2.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT * 2 / 4);
}


Menu::~Menu()
{
}


void Menu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    sf::Sprite sp_fond(fond_menu_picture);
    switch (_menu_type) {
        case MENU_CONFIGURATION:
            target.draw(sp_fond);
            target.draw(_fond_mc_retour);
            target.draw(_menu_config_retour);
            break;
        case MENU_PAUSE:
            target.draw(_fond_pause);

            target.draw(_sauvegarder_fond);
            target.draw(_sauvegarder);
            target.draw(_retour_menu_principal_fond);
            target.draw(_retour_menu_principal);
            target.draw(_texte_pause_fond);
            target.draw(_texte_pause);
            break;
        case MENU_PRINCIPAL:
            target.draw(sp_fond);
            target.draw(_fond_mp_play);
            target.draw(_menu_principal_play);
            target.draw(_fond_mp_charger);
            target.draw(_menu_principal_charger);
            target.draw(_fond_mp_config);
            target.draw(_menu_principal_config);
            target.draw(_fond_mp_quitter);
            target.draw(_menu_principal_quitter);
            break;
        case NIVEAU_SUIVANT:
            target.draw(_fond_pause);
            target.draw(_niveau_suivant_fond);
            target.draw(_niveau_suivant);
            break;
        case MONDE_SUIVANT:
            target.draw(_fond_pause);
            target.draw(_monde_suivant_fond);
            target.draw(_monde_suivant);
            break;
        case GAME_OVER:
            target.draw(_fond_pause);
            target.draw(_game_over_fond);
            target.draw(_game_over);
            break;
        case JEU_FINI:
            target.draw(_fond_pause);
            target.draw(_fin_jeu_fond);
            target.draw(_fin_jeu);
            break;
        case AUCUN_MENU:
            break;
        case QUITTER:
            target.draw(_quitter_1);
            target.draw(_quitter_2);
            break;
        default:
            break;
    }
}// draw()


void Menu::mise_a_jour()
{
    float a;
    switch (_menu_type) {
        case MENU_CONFIGURATION:

            break;
        case MENU_PAUSE:
             a = std::sin(_pause_frame++ * 0.015f) * 3.f;
            _texte_pause.setRotation(a);
            _texte_pause_fond.setRotation(a);
            break;
        case MENU_PRINCIPAL:

            break;
        case NIVEAU_SUIVANT:

            break;
        case MONDE_SUIVANT:

            break;
        case GAME_OVER:

            break;
        case JEU_FINI:

            break;
        case AUCUN_MENU:
        default:
            break;
    }
}// mise_a_jour()


void Menu::clic(int x, int y)
{
    unsigned niveau_courant;
    unsigned monde_courant;
    switch (_menu_type) {
        case MENU_CONFIGURATION:
            if(_fond_mc_retour.getGlobalBounds().contains(x,y))
            {
                active_menu(Menu::MENU_PRINCIPAL);
            }
            break;
        case MENU_PAUSE:
            // #TODO ajouter une option sauvegarde
            // retour au menu principal ?
            if(_sauvegarder_fond.getGlobalBounds().contains(x,y))
            {
                Sauvegarde sauv;
                sauv.sauver_sauvegarde();
            }
            else if (_retour_menu_principal_fond.getGlobalBounds().contains(x,y))
            {
                Jeu::instance().get_monde_courant().get_niveau_courant().liberer();
                Jeu::instance().get_monde_courant().liberer();
                Jeu::instance().charger_donnees_joueur(JOUEUR_VIT_DEFAULT, JOUEUR_NB_BOMBES_DEFAULT, BOMBE_POWER_DEFAULT, JOUEUR_VIE_DEFAULT, false, false);
                active_menu(Menu::MENU_PRINCIPAL);
            }
            break;
        case MENU_PRINCIPAL:
            if(_fond_mp_charger.getGlobalBounds().contains(x,y))
            {
                // charger la sauvegarde #TODO
                Sauvegarde sauv;
                sauv.charger_sauvegarde();
                active_menu(Menu::AUCUN_MENU);
            }
            else if (_fond_mp_config.getGlobalBounds().contains(x,y))
            {
                active_menu(Menu::MENU_CONFIGURATION);
            }
            else if (_fond_mp_play.getGlobalBounds().contains(x,y))
            {
                Jeu::instance().set_monde_courant(0);
                Jeu::instance().get_monde_courant().set_niveau_courant(0);
                _pause_frame = 0;
                active_menu(Menu::AUCUN_MENU);
            }
            else if (_fond_mp_quitter.getGlobalBounds().contains(x,y))
            {
                active_menu(Menu::QUITTER);
            }
            break;
        case NIVEAU_SUIVANT:
            // recuperer les bonnus et valeur du joueur #TODO
            //monde_courant = Jeu::instance().get_num_monde_courant();
            Jeu::instance().sauve_donnees_joueur();
            niveau_courant = Jeu::instance().get_monde_courant().get_num_niveau_courant();
            Jeu::instance().get_monde_courant().get_niveau_courant().liberer();
            Jeu::instance().get_monde_courant().set_niveau_courant(niveau_courant + 1);
            active_menu(Menu::AUCUN_MENU);
            break;
        case MONDE_SUIVANT:
            // recuperer les bonnus et valeur du joueur #TODO
            Jeu::instance().sauve_donnees_joueur();
            monde_courant = Jeu::instance().get_num_monde_courant();
            Jeu::instance().get_monde_courant().get_niveau_courant().liberer();
            Jeu::instance().get_monde_courant().liberer();
            Jeu::instance().set_monde_courant(monde_courant + 1);
            Jeu::instance().get_monde_courant().set_niveau_courant(0);
            active_menu(Menu::AUCUN_MENU);
            break;
        case GAME_OVER:
            if(_game_over_fond.getGlobalBounds().contains(x,y))
            {
                //unsigned monde_courant = Jeu::instance().get_num_monde_courant();
                niveau_courant = Jeu::instance().get_monde_courant().get_num_niveau_courant();
                Jeu::instance().get_monde_courant().get_niveau_courant().liberer();
                Jeu::instance().get_monde_courant().set_niveau_courant(niveau_courant);
                active_menu(Menu::AUCUN_MENU);
            }
            break;
        case JEU_FINI:
            if(_fin_jeu_fond.getGlobalBounds().contains(x,y))
            {
                Jeu::instance().get_monde_courant().get_niveau_courant().liberer();
                Jeu::instance().get_monde_courant().liberer();
                active_menu(Menu::MENU_PRINCIPAL);
            }
            break;
        default:
            break;
    }
}// clic()


void Menu::lost_focus()
{
    if(_menu_type == AUCUN_MENU)
    {
        active_menu(Menu::MENU_PAUSE);
    }
}// lost_focus()


void Menu::press_pause()
{
    if(_menu_type == AUCUN_MENU)
    {
        active_menu(Menu::MENU_PAUSE);
    }
    else if (_menu_type == MENU_PAUSE)
    {
        active_menu(Menu::AUCUN_MENU);
    }
}// press_pause()


Menu::menu_type Menu::get_menu_type()
{
    return _menu_type;
}// get_menu_type()


void Menu::active_menu(Menu::menu_type type)
{
    switch (type) {
        case MENU_CONFIGURATION:
            _menu_type = MENU_CONFIGURATION;
            break;
        case MENU_PRINCIPAL:
            _menu_type = MENU_PRINCIPAL;
            break;
        case MENU_PAUSE:
            _menu_type = MENU_PAUSE;
            break;
        case AUCUN_MENU:
            _menu_type = AUCUN_MENU;
            break;
        case NIVEAU_SUIVANT:
            _menu_type = NIVEAU_SUIVANT;
            break;
        case MONDE_SUIVANT:
            _menu_type = MONDE_SUIVANT;
            break;
        case GAME_OVER:
            _menu_type = GAME_OVER;
            break;
        case JEU_FINI:
            _menu_type = JEU_FINI;
            break;
        case QUITTER:
            _menu_type = QUITTER;
            break;
        default:
            _menu_type = AUCUN_MENU;
            break;
    }
}// active_menu()


// fin implementation class Menu
