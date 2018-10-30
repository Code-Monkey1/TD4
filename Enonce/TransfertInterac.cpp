/********************************************
* Titre: Travail pratique #4 - transfertInterac.cpp
* Date: 19 octobre 2018
* Auteur: Wassim Khene & Ryan Hardie
*******************************************/

#include "transfertInterac.h"

TransfertInterac::TransfertInterac(double montant, Utilisateur* expediteur, Utilisateur* receveur)
	: Transfert(montant, expediteur, receveur)
{
	//Initialise le courriel
	courriel_ = expediteur->getCourriel();
}

string TransfertInterac::getCourriel() const
{
	return courriel_;
}

void TransfertInterac::setcourriel(string courriel)
{
	courriel_ = courriel;
}

double TransfertInterac::getFraisTransfert() const
{
	double fraisTransfert = 0.0;	
	if (typeid(*expediteur_) == typeid(UtilisateurPremium)) {
		fraisTransfert = 0;	//Pas de frais pour les utilisateurs premium
	}
	else
	{
		fraisTransfert = FRAIS_TRANSFERT;	//Frais pour les utilisateurs réguliers
	}
	return fraisTransfert;
}