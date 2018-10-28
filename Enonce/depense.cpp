/********************************************
* Titre: Travail pratique #4 - depense.cpp
* Date: 19 octobre 2018
* Auteur: Wassim Khene & Ryan Hardie
*******************************************/

#include "depense.h"

// Constucteurs

Depense::Depense(const string& nom, double montant, const string& lieu) {
}


// Methodes d'acces
string Depense::getNom() const {
	return nom_;
}

double Depense::getMontant() const {
	return montant_;
}

string* Depense::getLieu() const
{
	return lieu_;
}

// Methodes de modifications
void Depense::setNom(const string& nom) {
	nom_ = nom;
}

void Depense::setMontant(double montant) {
	montant_ = montant;
}

void Depense::setLieu(const string& nom)
{
	*lieu_ = nom;
}

// Methode d'affichage
ostream & operator<<(ostream& os, const Depense& depense)
{
	return os << "- Depense (a " << *depense.lieu_ << ") : "  << depense.nom_ << ". Prix : " << depense.montant_ << "$" << endl;
}
