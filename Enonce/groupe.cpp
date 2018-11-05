/********************************************
* Titre: Travail pratique #4 - groupe.cpp
* Date: 5 novembre 2018
* Auteur: Jules Lefebvre et Raphael Geoffrion
*******************************************/

#include "groupe.h"

// Constructeurs

Groupe::Groupe() {
	nom_ = "";
}

Groupe::Groupe(const string& nom) : nom_(nom) {
}

Groupe::~Groupe()
{
}

// Methodes d'acces
string Groupe::getNom() const {
	return nom_;
}

vector<Depense*> Groupe::getDepenses() const
{
	return depenses_;
}

vector<Utilisateur*> Groupe::getUtilisateurs() const
{
	return utilisateurs_;
}

vector<Transfert*> Groupe::getTransferts() const
{
	return transferts_;
}

vector<double> Groupe::getComptes() const
{
	return comptes_;
}

double Groupe::getTotalDepenses() const {
	double totalDepenses = 0;
	for (unsigned int i = 0; i < depenses_.size(); i++) {
		totalDepenses += depenses_[i]->getMontant();
	}
	return totalDepenses;
}

// Methodes de modifications
void Groupe::setNom(const string& nom) {
	nom_ = nom;
}


Groupe & Groupe::ajouterDepense(double montant, Utilisateur * payePar, const string & nom, const string & lieu)
{
	//Verifie que l'utilisateur qui a paye fait parti du groupe
	bool utilDansGroupe = false;
	for (unsigned int i = 0; i < utilisateurs_.size(); i++) {
		if (utilisateurs_[i]->getNom() == payePar->getNom()){
			utilDansGroupe = true;
		}
	}

	if (utilDansGroupe == true) {
		//Le depense est creee et ajoutee au groupe.
		Depense* nouvDepense = new Depense(nom, montant, lieu);
		depenses_.push_back(nouvDepense);
		
		//Les comptes de chaque utilisateurs sont mis a jour.
		for (unsigned int i = 0; i < utilisateurs_.size(); i++) {
			// Le compte de l'utilisateur qui a paye la depense augmente du montant de la depense.
			if (utilisateurs_[i]->getNom() == payePar->getNom())
				comptes_[i] = comptes_[i] + montant - (montant / utilisateurs_.size());
			// Les comptes des utilisateurs qui n'ont pas paye la depense diminuent du montant de la depense divise par le nombre d'utilisateurs dans le groupe.
			else
				comptes_[i] = comptes_[i] - (montant / utilisateurs_.size());
		}
	}
	else
	{
		cout << "L'utilisateur qui a paye la depense " << nom << "ne fait pas partie du groupe " << this->getNom() << "." << endl;
	}
	
	return *this; //Retourne une reference au groupe pour les appels en cascade.
}

Groupe & Groupe::operator+=(Utilisateur * utilisateur)
{
	// Verifie si l'utilisateur est deja dans le groupe.
	bool estDansGroupe = false;
	for (unsigned int i = 0; i < utilisateurs_.size(); i++) {
		if (utilisateurs_[i] == utilisateur)
			estDansGroupe = true;
	}
	
	if (estDansGroupe == false) {
		// Appartenance a un groupe (regulier).
		if (utilisateur->getPossedeGroupe() == false) {
			// Validite de l'abonnement (premium)
			if (utilisateur->getJoursRestants() > 0) {
				utilisateurs_.push_back(utilisateur);
				comptes_.push_back(0);
				if (typeid(*utilisateur) == typeid(UtilisateurRegulier)) {
					UtilisateurRegulier* pointeurUtilReg = dynamic_cast<UtilisateurRegulier*>(utilisateur);
					pointeurUtilReg->setPossedeGroupe(true);
				}
			}
			else
			{
				cout << "Erreur : l'utilisateur " << utilisateur->getNom() << " doit renouveler son abonnement premium."<< endl;
			}
		}
		else
		{
			cout << "Erreur : l'utilisateur " << utilisateur->getNom() << " n'est pas un utilisateur premium et est deja dans un groupe." << endl;
		}
	}
	else {
		cout << "Erreur : l'utilisateur " << utilisateur->getNom() << " fait déjà parti du groupe." << endl;
	}
	
	return *this; //Retourne une reference au groupe pour les appels en cascade.
}

// Methode de calcul

void Groupe::equilibrerComptes() {

	bool calcul = true;
	unsigned int count = 0;
	while (calcul == true) {
		double max = 0;
		double min = 0;
		int indexMax = 0;
		int indexMin = 0;

		// On cherche le compte le plus eleve et le moins eleve
		for (unsigned int i = 0; i < utilisateurs_.size(); i++) {
			if (comptes_[i] > max) {
				max = comptes_[i];
				indexMax = i;
			}
			if (comptes_[i] < min) {
				min = comptes_[i];
				indexMin = i;
			}
		}

		// On cherche lequel des deux a la dette la plus grande
		if (-min <= max && min != 0 && max != 0) {
			// Faire le transfert  du bon type
			switch (utilisateurs_[indexMin]->getMethodePaiement()) {
				case Paypal:
					transferts_.push_back(new TransfertPaypal(-min,		utilisateurs_[indexMin], utilisateurs_[indexMax]));
				case Interac:
					transferts_.push_back(new TransfertInterac(-min,	utilisateurs_[indexMin], utilisateurs_[indexMax]));
			}
			comptes_[indexMax] += min;
			comptes_[indexMin] = 0;
		}
		else if (-min > max  && min != 0 && max != 0) {
			// Faire le transfert du bon type
			switch (utilisateurs_[indexMin]->getMethodePaiement()) {
			case Paypal:
				transferts_.push_back(new TransfertPaypal(max, utilisateurs_[indexMin], utilisateurs_[indexMax]));
			case Interac:
				transferts_.push_back(new TransfertInterac(max, utilisateurs_[indexMin], utilisateurs_[indexMax]));
			}
			comptes_[indexMax] = 0;
			comptes_[indexMin] += max;
		}

		// On incremente le nombre de comptes mis a 0
		count++;
		if (-min == max) {
			count++;
		}
		if (count >= utilisateurs_.size() - 1) {
			calcul = false;
		}
	}

	for (int i = 0; i < transferts_.size(); i++)
		transferts_[i]->effectuerTransfert();
}

// Methode d'affichage
ostream & operator<<(ostream& os, const Groupe& groupe)
{
	os << "\nGroupe " << groupe.nom_ << ".\nCout total: " << groupe.getTotalDepenses() << "$ \nUtilisateurs:    \n\n";
	for (unsigned int i = 0; i < groupe.utilisateurs_.size(); i++) {
		os <<"\t- " << *groupe.utilisateurs_[i];
	}
	os << endl;

	if (groupe.transferts_.size() != 0) {
		os << "Transferts :" << endl;
		for (unsigned int i = 0; i < groupe.transferts_.size(); i++)
			os << "\t" << *(groupe.transferts_[i]);
	}
	else {
		os << "Les comptes ne sont pas equilibres" << endl << endl;
		for (unsigned int i = 0; i < groupe.comptes_.size(); i++) {
			os << groupe.utilisateurs_[i]->getNom() << " : " << groupe.comptes_[i] << endl;
		}
	}

	os << endl;
	return os;
}
