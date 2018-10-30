/********************************************
* Titre: Travail pratique #4 - depense.h
* Date: 19 octobre 2018
* Auteur: Wassim Khene & Ryan Hardie
*******************************************/

#ifndef DEPENSE_H
#define DEPENSE_H

#include <string>
#include <iostream>

using namespace std;

class Depense {
public:
	// Constructeurs
	Depense(const Depense& depense);
	Depense(const string& nom = "", double montant = 0 , const string& lieu = "Montreal");


	//Surcharge de l'opérateur d'affectation
	Depense& operator=(const Depense& depense);

	// Methodes d'acces
	string getNom() const;
	double getMontant() const;
	string* getLieu() const;

	// Methodes de modifications
	void setNom(const string& nom);
	void setMontant(double montant);
	void setLieu(const string& lieu);

	// Affichage
	friend ostream& operator<<(ostream& os, const Depense& depense);
private:
	string nom_;
	double montant_;
	string* lieu_;

};
#endif