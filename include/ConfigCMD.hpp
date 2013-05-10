/*
 * ConfigCMD.hpp
 *
 *  Created on: 10 mai 2013
 *      Author: Sanpas
 */

#ifndef CONFIGCMD_HPP_
#define CONFIGCMD_HPP_

#include <SFML/Graphics.hpp>

class ConfigCMD
{
private:
    sf::Keyboard::Key   CMD_HAUT;
    sf::Keyboard::Key   CMD_BAS;
    sf::Keyboard::Key   CMD_DROITE;
    sf::Keyboard::Key   CMD_GAUCHE;
    sf::Keyboard::Key   CMD_BOMBE;
    sf::Keyboard::Key   CMD_SPECIAL;
public:

    ConfigCMD(): CMD_HAUT(CMD_HAUT_DEFAULT), CMD_BAS(CMD_BAS_DEFAULT), CMD_DROITE(CMD_DROITE_DEFAULT),
                 CMD_GAUCHE(CMD_GAUCHE_DEFAULT), CMD_BOMBE(CMD_BOMBE_DEFAULT), CMD_SPECIAL(CMD_SPECIA_DEFAULTL)

    {
    }
    sf::Keyboard::Key getCmdBas() const
    {
        return CMD_BAS;
    }

    void setCmdBas(sf::Keyboard::Key cmdBas)
    {
        CMD_BAS = cmdBas;
    }

    sf::Keyboard::Key getCmdBombe() const
    {
        return CMD_BOMBE;
    }

    void setCmdBombe(sf::Keyboard::Key cmdBombe)
    {
        CMD_BOMBE = cmdBombe;
    }

    sf::Keyboard::Key getCmdDroite() const
    {
        return CMD_DROITE;
    }

    void setCmdDroite(sf::Keyboard::Key cmdDroite)
    {
        CMD_DROITE = cmdDroite;
    }

    sf::Keyboard::Key getCmdGauche() const
    {
        return CMD_GAUCHE;
    }

    void setCmdGauche(sf::Keyboard::Key cmdGauche)
    {
        CMD_GAUCHE = cmdGauche;
    }

    sf::Keyboard::Key getCmdHaut() const
    {
        return CMD_HAUT;
    }

    void setCmdHaut(sf::Keyboard::Key cmdHaut)
    {
        CMD_HAUT = cmdHaut;
    }

    sf::Keyboard::Key getCmdSpecial() const
    {
        return CMD_SPECIAL;
    }

    void setCmdSpecial(sf::Keyboard::Key cmdSpecial)
    {
        CMD_SPECIAL = cmdSpecial;
    }

    ;


};



#endif /* CONFIGCMD_HPP_ */
