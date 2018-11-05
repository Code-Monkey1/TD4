/********************************************
* Titre: Travail pratique #4 - utilisateurPremium.cpp
* Date: 19 octobre 2018
* Auteur: Wassim Khene & Ryan Hardie
*******************************************/

#include "utilisateurPremium.h"


UtilisateurPremium::UtilisateurPremium(const string& nom, MethodePaiement methodePaiement,
	unsigned int joursRestants, const string& courriel, const string& idPaypal)
	: Utilisateur(nom, methodePaiement, courriel, idPaypal), joursRestants_(joursRestants)
{}

unsigned int UtilisateurPremium::getJoursRestants() const {
	return joursRestants_;
}

bool UtilisateurPremium::getPossedeGroupe() const {
	return false;
}

void UtilisateurPremium::setJoursRestants(unsigned int joursRestants) {
	joursRestants_ = joursRestants;
}

void UtilisateurPremium::print(ostream & os) const
{
	os << "- Utilisateur (premium) " << nom_ << " :" << endl
		<< "\t Total a payer: " << balanceTransferts_ << "$ (" << balanceFrais_ << "$ de frais)" << endl
		<< "Jours restants: " << joursRestants_ << endl
		<< "Depenses :" << endl;
	for (unsigned i = 0; i < depenses_.size(); i++)
	{
		os << *depenses_[i];
	}
}
