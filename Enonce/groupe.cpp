/********************************************
* Titre: Travail pratique #4 - groupe.cpp
* Date: 19 octobre 2018
* Auteur: Wassim Khene & Ryan Hardie
*******************************************/

#include "groupe.h"

// Constructeurs

Groupe::Groupe() {
	nom_ = "";
}

Groupe::Groupe(const string& nom) : nom_(nom) {
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
	for (int i = 0; i < depenses_.size(); i++) {
		totalDepenses += depenses_[i]->getMontant();
	}
	return totalDepenses;
}

// Methodes de modifications
void Groupe::setNom(const string& nom) {
	nom_ = nom;
}

void Groupe::equilibrerComptes() {

	bool calcul = true;
	int count = 0;
	while (calcul) {
		double max = 0;
		double min = 0;
		int indexMax = 0;
		int indexMin = 0;

		// On cherche le compte le plus eleve et le moins eleve
		for (int i = 0; i < utilisateurs_.size(); i++) {
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
			comptes_[indexMax] += min;
			comptes_[indexMin] = 0;
		}
		else if (-min > max  && min != 0 && max != 0) {
			// Faire le transfert du bon type
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

}

// Methode d'affichage
ostream & operator<<(ostream& os, const Groupe& groupe)
{
	os << "\nGroupe " << groupe.nom_ << ".\nCout total: " << groupe.getTotalDepenses() << "$ \nUtilisateurs:    \n\n";
	for (int i = 0; i < groupe.utilisateurs_.size(); i++) {
		os <<"\t- " << *groupe.utilisateurs_[i];
	}
	os << endl;

	if (groupe.transferts_.size() != 0) {
		os << "Transferts :" << endl;
		for (int i = 0; i < groupe.transferts_.size(); i++)
			os << "\t" << *(groupe.transferts_[i]);
	}
	else {
		os << "Les comptes ne sont pas equilibres" << endl << endl;
		for (int i = 0; i < groupe.comptes_.size(); i++) {
			os << groupe.utilisateurs_[i]->getNom() << " : " << groupe.comptes_[i] << endl;
		}
	}

	os << endl;
	return os;
}
