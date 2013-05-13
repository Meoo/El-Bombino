/**
 * @file   ConfigCMD.hpp
 * @author Bastien Brunnenstein
 * @author Pascal-Pierre Sanchez-Carrion
 */

#ifndef CONFIGCMD_HPP_
#define CONFIGCMD_HPP_

#include <SFML/Graphics.hpp>


/**
 * @brief
 */
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
    }//getCmdBas()

    void setCmdBas(sf::Keyboard::Key cmdBas)
    {
        CMD_BAS = cmdBas;
    }// setCmdBas()

    sf::Keyboard::Key getCmdBombe() const
    {
        return CMD_BOMBE;
    }// getCmdBombe()

    void setCmdBombe(sf::Keyboard::Key cmdBombe)
    {
        CMD_BOMBE = cmdBombe;
    }// setCmdBombe()

    sf::Keyboard::Key getCmdDroite() const
    {
        return CMD_DROITE;
    }// getCmdDroite()

    void setCmdDroite(sf::Keyboard::Key cmdDroite)
    {
        CMD_DROITE = cmdDroite;
    }// setCmdDroite()

    sf::Keyboard::Key getCmdGauche() const
    {
        return CMD_GAUCHE;
    }// getCmdGauche()

    void setCmdGauche(sf::Keyboard::Key cmdGauche)
    {
        CMD_GAUCHE = cmdGauche;
    }// setCmdGauche()

    sf::Keyboard::Key getCmdHaut() const
    {
        return CMD_HAUT;
    }// getCmdHaut()

    void setCmdHaut(sf::Keyboard::Key cmdHaut)
    {
        CMD_HAUT = cmdHaut;
    }// setCmdHaut()

    sf::Keyboard::Key getCmdSpecial() const
    {
        return CMD_SPECIAL;
    }// getCmdSpecial()

    void setCmdSpecial(sf::Keyboard::Key cmdSpecial)
    {
        CMD_SPECIAL = cmdSpecial;
    }// setCmdSpecial()


};
// class ConfigCMD


#endif /* CONFIGCMD_HPP_ */
