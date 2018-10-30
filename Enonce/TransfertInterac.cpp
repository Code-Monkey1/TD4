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

double TransfertInterac::getFraisTransfert() const
{
	double fraisTransfert = FRAIS_TRANSFERT;	//Frais de base pour les utilisateurs réguliers
	if (typeid(*expediteur_) == typeid(UtilisateurPremium)) {
		fraisTransfert = -montant_* TAUX_EPARGNE;	//Les utilisateurs premium perçoivent un retour d'un certain pourcentage sur le montant transféré
	}
	return fraisTransfert;
}
