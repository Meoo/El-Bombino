/*
 * CaseInfo.hpp
 *
 *  Created on: 11 mai 2013
 *      Author: Sanpas
 */

#ifndef CASEINFO_HPP_
#define CASEINFO_HPP_

class CaseInfo
{
private:
    bool    _praticable;
    bool    _bombe;
    bool    _bonus;
    bool    _joueur;
    bool    _malus;
    bool    _pnj;
    bool    _caisse;

public:

    CaseInfo():_praticable(false), _bombe(false), _bonus(false), _joueur(false),
               _malus(false), _pnj(false), _caisse(false){}
    ~CaseInfo(){}

    bool isBombe() const
    {
        return _bombe;
    }// isBombe()

    void setBombe(bool bombe)
    {
        _bombe = bombe;
    }// setBombe()

    bool isBonus() const
    {
        return _bonus;
    }// isBonus()

    void setBonus(bool bonus)
    {
        _bonus = bonus;
    }// setBonus()

    bool isCaisse() const
    {
        return _caisse;
    }// isCaisse()

    void setCaisse(bool caisse)
    {
        _caisse = caisse;
    }// setCaisse()

    bool isJoueur() const
    {
        return _joueur;
    }// isJoueur()

    void setJoueur(bool joueur)
    {
        _joueur = joueur;
    }// setJoueur()

    bool isMalus() const
    {
        return _malus;
    }// isMalus()

    void setMalus(bool malus)
    {
        _malus = malus;
    }// setMalus()

    bool isPnj() const
    {
        return _pnj;
    }// isPnj()

    void setPnj(bool pnj)
    {
        _pnj = pnj;
    }// setPnj()

    bool isPraticable() const
    {
        return _praticable;
    }// isPraticable()

    void setPraticable(bool praticable)
    {
        _praticable = praticable;
    }// setPraticable()
};


#endif /* CASEINFO_HPP_ */
