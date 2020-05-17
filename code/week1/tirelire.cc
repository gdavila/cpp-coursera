#include <iostream>
using namespace std;

/*******************************************
 * Complétez le programme à partir d'ici.
 *******************************************/
class Tirelire {
  private:
    double montant;

  public:
  double getMontant() const { return montant;};

  void afficher() const {
    if (montant == 0) {
      cout << "Vous etes sans le sou.\n";
    }
    else {
      cout << "Vous avez : " << montant << " euros dans votre tirelire.\n";
    }
  };

  void secouer() const {
    if (montant != 0) {
      cout << "Bing bing\n";
    }
  };

  void remplir( double amount) {
    if (amount > 0 ) {
      montant = montant + amount;
    }
  };

  void vider() { montant=0;};

  void puiser( double amount) {
    if (amount > 0 && amount <= montant) {
      montant = montant - amount;
    }
    else {    
      if (amount > montant){
        montant = 0;
    }}
  };

  bool montant_suffisant (double boudget, double &solde) {
    if (boudget < 0 ) {boudget=0; }
    if (montant >= boudget) {
      solde = montant - boudget;
      return true;
    }
    else {
      solde = - montant + boudget;
      return false;
    }
  };
};

/*******************************************
 * Ne rien modifier après cette ligne.
 *******************************************/

int main()
{
  Tirelire piggy;

  piggy.vider();
  piggy.secouer();
  piggy.afficher();

  piggy.puiser(20.0);
  piggy.secouer();
  piggy.afficher();

  piggy.remplir(550.0);
  piggy.secouer();
  piggy.afficher();

  piggy.puiser(10.0);
  piggy.puiser(5.0);
  piggy.afficher();

  cout << endl;

  // le budget de vos vacances de rève.
  double budget;

  cout << "Donnez le budget de vos vacances : ";
  cin >> budget;

  // ce qui resterait dans la tirelire après les
  // vacances
  double solde(0.0);

  if (piggy.montant_suffisant(budget, solde)) {
    cout << "Vous êtes assez riche pour partir en vacances !"
         << endl
         << "Il vous restera " << solde << " euros"
         << " à la rentrée." << endl << endl;
    piggy.puiser(budget);
  } else {
    cout << "Il vous manque " << solde << " euros"
         << " pour partir en vacances !" << endl << endl;
  }
  return 0;
}
