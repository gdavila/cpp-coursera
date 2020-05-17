#include <iostream>
using namespace std;

/*****************************************************
 * Compléter le code à partir d'ici
 *****************************************************/

class Patient{
private:
    double masse;
    double hauteur;
    
public:
    void init(double m, double h){
        if (m < 0 || h < 0 ) {
            masse=0;
            hauteur =0;}
        else {
            masse=m;
            hauteur = h;}
    }
    void afficher(){
        cout<<"Patient: "<< poids()<< " kg pour "<<taille()<<" m"<<endl;
    }
    
    double poids(){
        return masse;
    }
    double taille(){
        return hauteur;
    }
    double imc(){
        if (taille()!=0.0) return poids()/(taille()*taille());
        else return 0;
    }
    
};

/*******************************************
 * Ne rien modifier après cette ligne.
 *******************************************/

int main()
{
    Patient quidam;
    double poids, taille;
    do {
        cout << "Entrez un poids (kg) et une taille (m) : ";
        cin >> poids >> taille;
        quidam.init(poids, taille);
        quidam.afficher();
        cout << "IMC : " << quidam.imc() << endl;
    } while (poids * taille != 0.0);
    return 0;
}