/********************************************
* Titre: Travail pratique #4 - transfertInterac.cpp
* Date: 19 octobre 2018
* Auteur: Wassim Khene & Ryan Hardie
*******************************************/

#include "transfertInterac.h"

TransfertInterac::TransfertInterac(double montant, Utilisateur* expediteur, Utilisateur* receveur)
	: Transfert(montant, expediteur, receveur)
{
}

string TransfertInterac::getCourriel() const
{
	return courriel_;
}

void TransfertInterac::setcourriel(string courriel)
{
	courriel_ = courriel;
}
