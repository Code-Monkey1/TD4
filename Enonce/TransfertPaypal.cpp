/********************************************
* Titre: Travail pratique #4 - transfertPaypal.cpp
* Date: 19 octobre 2018
* Auteur: Wassim Khene & Ryan Hardie
*******************************************/

#include "transfertPaypal.h"

TransfertPaypal::TransfertPaypal(double montant, Utilisateur * expediteur, Utilisateur * receveur)
	: Transfert(montant, expediteur, receveur)
{
}

string TransfertPaypal::getId() const
{
	return id_;
}

void TransfertPaypal::setId(string id)
{
	id_ = id;
}

double TransfertPaypal::getFraisTransfert() const
{
	double fraisTransfert = COMMISSION*montant_ + FRAIS;	//Frais de base pour les utilisateurs réguliers
	if (typeid(*expediteur_) == typeid(UtilisateurPremium)) {
		fraisTransfert -= FRAIS;	//Les utilisateurs premium ont juste besoin de payer la commission.
	}
	return fraisTransfert;
}

