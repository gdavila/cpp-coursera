#include <iostream>
#include <string>
#include <cmath>
using namespace std;

class Flacon
{
private:
  string nom;
  double volume;
  double pH;

public:
  /*****************************************************
    Compléter le code à partir d'ici
  *******************************************************/
    Flacon(const string nom, const double& volume, const  double& pH) : nom(nom), volume(volume), pH(pH) {}

    ostream& etiquette(ostream& sortie) const 
    {
        sortie << nom << " : " << volume << " ml, pH " << pH;
        return sortie;
    }

    Flacon& operator+=(Flacon const& f)
    {
        nom = nom + " + " + f.nom;
        pH = -log10( ( (volume*pow(10.0, -pH)) + (f.volume*pow(10.0, -f.pH)) ) / (volume + f.volume));
        volume = volume + f.volume;
        return *this;
    }

    const Flacon operator+(Flacon const& f) const {return Flacon(*this) += f;}
};


ostream& operator<<(ostream& sortie, Flacon const & F) {  return F.etiquette(sortie);}



#define BONUS

/*******************************************
 * Ne rien modifier après cette ligne.
 *******************************************/

void afficher_melange(Flacon const& f1, Flacon const& f2)
{
  cout << "Si je mélange " << endl;
  cout << "\t\"" << f1 << "\"" << endl;
  cout << "avec" << endl;
  cout << "\t\"" << f2 << "\"" << endl;
  cout << "j'obtiens :" << endl;
  cout << "\t\"" << (f1 + f2) << "\"" << endl;
}

int main()
{
  Flacon flacon1("Eau", 600.0, 7.0);
  Flacon flacon2("Acide chlorhydrique", 500.0, 2.0);
  Flacon flacon3("Acide perchlorique",  800.0, 1.5);

  afficher_melange(flacon1, flacon2);
  afficher_melange(flacon2, flacon3);

  return 0;

}
