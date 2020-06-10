#include <iostream>
#include <string>
#include <cmath>
using namespace std;

int distance(int x, int y)
{
  return abs(x - y);
}

class Creature
{
  /*****************************************************
   * Compléter le code à partir d'ici
   *****************************************************/
protected:
    //atributes
    string nom_;
    int niveau_;
    int points_de_vie_;
    int force_;
    int position_;

public:
    //constructor
    Creature(string nom, int niveau, int pdv, int force, int pos=0)
    :nom_(nom), niveau_(niveau), points_de_vie_(pdv), force_(force), position_(pos) {}

    //methods
    bool vivant() const {return points_de_vie_>0;}

    int points_attaque() const 
    {
        int pa;
        if (vivant()) {pa = niveau_*force_;}
        else {pa = 0;}
        return pa;
    }

    void deplacer (int d){ if ( vivant() ) position_+=d;}

    void adieux() const {cout << nom_ << " n'est plus!" << endl;}

    void faiblir (int f) 
    {
        points_de_vie_-=f;
        if ( !vivant() ) 
        {
            points_de_vie_=0;
            adieux();
        }
    }

    void afficher() const
    {
        cout << nom_ << ", niveau: "<< niveau_<< ", points de vie: " << points_de_vie_ << ", force: " << force_ << ", points d'attaque: "<< points_attaque() << ", position: " <<position_ << endl;
    }

    int position() const {return position_;}
};


class Dragon: public Creature
{
protected:
    int portee_flamme_;

public:
    Dragon(string nom, int niveau, int pdv, int force, int flamme, int pos=0)
    :Creature(nom, niveau, pdv, force, pos), portee_flamme_(flamme){}

    void voler(int pos) {if ( vivant() )position_=pos;}

    void souffle_sur(Creature& bete)
    {
        bool inrange;
        inrange = distance(position_, bete.position()) <= portee_flamme_;
        if (vivant() and bete.vivant() and inrange)
        {
            bete.faiblir(points_attaque());
            faiblir(distance(position_, bete.position()));
            if (vivant() and !bete.vivant()) { niveau_ +=1;}
        }
    }
};

class Hydre: public Creature
{
protected:
    int longueur_cou_;
    int dose_poison_;

public:
    Hydre(string nom, int niveau, int pdv, int force, int cou, int  dose, int pos=0)
    :Creature(nom, niveau, pdv, force, pos), longueur_cou_(cou), dose_poison_(dose){}

    void empoisonne(Creature& bete) 
    {
        bool inrange;
        inrange = distance(position_, bete.position()) <= longueur_cou_;
        if (vivant() and bete.vivant() and inrange)
        {
            bete.faiblir(points_attaque()+dose_poison_);
            if (vivant() and !bete.vivant()) { niveau_ +=1;}
        }
    }

};

void combat (Dragon & dragon, Hydre & hydre) 
{
    hydre.empoisonne(dragon);
    dragon.souffle_sur(hydre);
    return;
};
/*******************************************
 * Ne rien modifier après cette ligne.
 *******************************************/
int main()
{
  Dragon dragon("Dragon rouge"   , 2, 10, 3, 20         );
  Hydre  hydre ("Hydre maléfique", 2, 10, 1, 10, 1,  42 );

  dragon.afficher();
  cout << "se prépare au combat avec :" << endl;
  hydre.afficher();

  cout << endl;
  cout << "1er combat :" << endl;
  cout << "    les créatures ne sont pas à portée, donc ne peuvent pas s'attaquer."
       << endl;
  combat(dragon, hydre);

  cout << "Après le combat :" << endl;
  dragon.afficher();
  hydre.afficher();

  cout << endl;
  cout << "Le dragon vole à proximité de l'hydre :" << endl;
  dragon.voler(hydre.position() - 1);
  dragon.afficher();

  cout << endl;
  cout << "L'hydre recule d'un pas :" << endl;
  hydre.deplacer(1);
  hydre.afficher();

  cout << endl;
  cout << "2e combat :" << endl;
  cout << "\
  + l'hydre inflige au dragon une attaque de 3 points\n\
      [ niveau (2) * force (1) + poison (1) = 3 ] ;\n\
  + le dragon inflige à l'hydre une attaque de 6 points\n\
      [ niveau (2) * force (3) = 6 ] ;\n\
  + pendant son attaque, le dragon perd 2 points de vie supplémentaires\n\
       [ correspondant à la distance entre le dragon et l'hydre : 43 - 41 = 2 ].\
" << endl;
  combat(dragon, hydre);

  cout << "Après le combat :" << endl;
  dragon.afficher();
  hydre.afficher();

  cout << endl;
  cout << "Le dragon avance d'un pas :" << endl;
  dragon.deplacer(1);
  dragon.afficher();

  cout << endl;
  cout << "3e combat :" << endl;
  cout << "\
  + l'hydre inflige au dragon une attaque de 3 points\n\
      [ niveau (2) * force (1) + poison (1) = 3 ] ;\n\
  + le dragon inflige à l'hydre une attaque de 6 points\n\
      [ niveau (2) * force (3) = 6 ] ;\n\
  + pendant son attaque, le dragon perd 1 point de vie supplémentaire\n\
       [ correspondant à la distance entre le dragon et l'hydre : 43 - 42 = 1 ] ;\n\
  + l'hydre est vaincue et le dragon monte au niveau 3.\
" << endl;
  combat(dragon, hydre);

  cout << "Après le combat :" << endl;
  dragon.afficher();
  hydre.afficher();

  cout << endl;
  cout << "4e Combat :" << endl;
  cout << "    quand une créature est vaincue, rien ne se passe." << endl;
  combat(dragon, hydre);

  cout << "Après le combat :" << endl;
  dragon.afficher();
  hydre.afficher();

  return 0;
}
