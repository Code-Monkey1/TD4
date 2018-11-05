/********************************************
* Titre: Travail pratique #4 - transfert.h
* Date: 19 octobre 2018
* Auteur: Wassim Khene & Ryan Hardie
*******************************************/

#ifndef TRANSFERT_H
#define TRANSFERT_H

#include "utilisateur.h"
#include "utilisateurPremium.h"

#include <iostream>

#include <stdio.h>

class Transfert {
public:
	// Constructeurs
	Transfert();
	Transfert(double montant, Utilisateur* expediteur, Utilisateur* receveur_);
	~Transfert();

	// Méthodes d'accès
	Utilisateur* getExpediteur() const;
	Utilisateur* getReceveur() const;
	double getMontant() const;

	//getFraisTransfert() est une fonction virtuelle pure,
	//car un transfert est soit un transfert paypal, soit un transfert interact, jamais juste un transfert.
	virtual double getFraisTransfert() const = 0; 

	// Méthodes d'affichage
	void setMontant(double montant);
	void setExpediteur(Utilisateur* expediteur);
	void setReceveur(Utilisateur* receveur);

	void effectuerTransfert();

	friend ostream& operator<<(ostream& os, const Transfert& transfert);

protected:
	double montant_;
	Utilisateur* expediteur_;
	Utilisateur* receveur_;
};

#endif