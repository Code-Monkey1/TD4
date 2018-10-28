/********************************************
* Titre: Travail pratique #4 - utilisateurRegulier.cpp
* Date: 19 octobre 2018
* Auteur: Wassim Khene & Ryan Hardie
*******************************************/

#include "utilisateurRegulier.h"

UtilisateurRegulier::UtilisateurRegulier(const string & nom, MethodePaiement methodePaiement, const string & courriel, const string & idPaypal)
	: Utilisateur(nom, methodePaiement, courriel, idPaypal), possedeGroupe_(false)
{}


bool UtilisateurRegulier::getPossedeGroupe() const {
	return possedeGroupe_;
}

void UtilisateurRegulier::setPossedeGroupe(bool possedeGroupe) {
	possedeGroupe_ = possedeGroupe;
}

void UtilisateurRegulier::print(ostream & os) const
{
	os << "- Utilisateur (regulier, ";

	if (possedeGroupe_) { os << "dans un groupe) "; }
	else { os << "pas dans un groupe) "; }
	
	os << nom_ << " :" << endl
		<< "\t Total a payer: " << balanceTransferts_ << "$ (" << balanceFrais_ << "$ de frais)" << endl
		<< "Depenses :" << endl;
	for (unsigned i = 0; i < depenses_.size(); i++)
	{
		os << *depenses_[i];
	}

}
