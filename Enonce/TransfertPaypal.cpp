/********************************************
* Titre: Travail pratique #4 - transfertPaypal.cpp
* Date: 19 octobre 2018
* Auteur: Wassim Khene & Ryan Hardie
*******************************************/

#include "transfertPaypal.h"

TransfertPaypal::TransfertPaypal(double montant, Utilisateur * expediteur, Utilisateur * receveur)
	: Transfert(montant, expediteur, receveur)
{
	//Initialise id paypal
	id_ = expediteur->getIdPaypal();
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
	double fraisTransfert = COMMISSION*montant_ + FRAIS;	//Frais pour les utilisateurs réguliers
	if (typeid(*expediteur_) == typeid(UtilisateurPremium)) {
		fraisTransfert = 0;	//Pas de frais pour les utilisateurs premium
	}
	return fraisTransfert;
}

