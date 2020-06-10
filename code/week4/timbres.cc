#include <iostream>
#include <string>
using namespace std;

class Timbre
{
private:
  static constexpr unsigned int ANNEE_COURANTE = 2016;

  /*****************************************************
   * Compléter le code à partir d'ici
   *****************************************************/
protected:
    string nom;
    unsigned int annee;
    string pays;
    double valeur_faciale;

public:
    Timbre(const string & n, const unsigned int & a, const string & p = "Suisse", const  double & v = 1.0)
    :nom(n), annee(a), pays(p), valeur_faciale(v) {}

    double vente() const;
    unsigned int age() const;
    ostream& afficher(ostream&) const;
};

double Timbre::vente() const
{
    double price;
    if (age() < 5 )  {price =  valeur_faciale;}
    else { price = valeur_faciale * 2.5 * age();}
    return price;
};

unsigned int Timbre::age() const {return ANNEE_COURANTE-annee;};

ostream& Timbre::afficher(ostream& sortie) const 
{
    sortie << " de nom " << nom << " datant de " << annee <<  " (provenance " << pays << ") ayant pour valeur faciale " << valeur_faciale << " francs";
    return sortie;
};

ostream& operator<<(ostream& sortie, Timbre const & T) 
{  
    sortie << "Timbre";
    return T.afficher(sortie);
}

class Rare: public Timbre 
{
private:
    static constexpr unsigned int PRIX_BASE_TRES_RARE = 600;
    static constexpr unsigned int PRIX_BASE_RARE = 400;
    static constexpr unsigned int PRIX_BASE_PEU_RARE = 50;

protected:
    unsigned int nb;

public:
    Rare(const string & n, const unsigned int & a, const string & p = "Suisse", const double & v = 1.0, const unsigned int & nb=100)
    :Timbre(n, a, p,  v), nb(nb) {}

    double vente() const;
    unsigned int nb_exemplaires() const;
};

unsigned int Rare::nb_exemplaires() const {return nb;};

double Rare::vente() const
{
    unsigned int price_base;
    if (nb< 100) {price_base = PRIX_BASE_TRES_RARE;}
    else{ 
            if (nb< 1000) {price_base = PRIX_BASE_RARE;}
            else {price_base = PRIX_BASE_PEU_RARE;}
        }
    return price_base * age() / 10.0;
};

ostream& operator<<(ostream& sortie, Rare const & R) 
{  
    sortie << "Timbre rare (" << R.nb_exemplaires() << " ex.)";
    return R.afficher(sortie);
}

class Commemoratif: public Timbre 
{
public:
    Commemoratif(const string & n, const unsigned int &  a, const string & p = "Suisse",const double & v = 1.0)
    :Timbre(n, a, p,  v){}

    double vente() const;
};

double Commemoratif::vente() const
{
    return 2* Timbre::vente();
};

ostream& operator<<(ostream& sortie, Commemoratif const & C) 
{  
    sortie << "Timbre commémoratif ";
    return C.afficher(sortie);
}

/*******************************************
 * Ne rien modifier après cette ligne.
 *******************************************/
int main()
{
  /* Ordre des arguments :
  *  nom, année d'émission, pays, valeur faciale, nombre d'exemplaires
  */
  Rare t1( "Guarana-4574", 1960, "Mexique", 0.2, 98 );
  Rare t2( "Yoddle-201"  , 1916, "Suisse" , 0.8,  3 );

  /* Ordre des arguments :
  *  nom, année d'émission, pays, valeur faciale, nombre d'exemplaires
  */
  Commemoratif t3( "700eme-501"  , 2002, "Suisse", 1.5 );
  Timbre       t4( "Setchuan-302", 2004, "Chine" , 0.2 );

  /* Nous n'avons pas encore le polymorphisme :-(
   * (=> pas moyen de faire sans copie ici :-( )  */
  cout << t1 << endl;
  cout << "Prix vente : " << t1.vente() << " francs" << endl;
  cout << t2 << endl;
  cout << "Prix vente : " << t2.vente() << " francs" << endl;
  cout << t3 << endl;
  cout << "Prix vente : " << t3.vente() << " francs" << endl;
  cout << t4 << endl;
  cout << "Prix vente : " << t4.vente() << " francs" << endl;

  return 0;
}
