#include <iostream>
#include <cmath>
using namespace std;

enum Pavillon { JollyRogers, CompagnieDuSenegal, CompagnieDOstende };

enum Etat { Intact, Endommage, Coule };

int sq(int x)
{
  return x*x;
}

class Coordonnees
{
public:
  Coordonnees(int un_x, int un_y) : x_(un_x), y_(un_y) {}
  int x() const {
    return x_;
  }
  int y() const {
    return y_;
  }
  void operator+=(Coordonnees const& autre); // à définir plus bas
private:
  int x_;
  int y_;
};

class Navire
{
  /*****************************************************
   * Compléter le code à partir d'ici
   *****************************************************/
  protected:
    Coordonnees position_;
    Pavillon pavillon_;
    Etat etat_;
    string name_;
    const double rayon_rencontre=10;

  public:
  Navire(int  x, int y, Pavillon  pavillon)
  : position_(x,y), pavillon_(pavillon), etat_(Intact) {}

  Coordonnees position() const {return position_;}

  const Pavillon & pavillon() const {return pavillon_;}

  void avancer(int de_x, int de_y)
  {
      Coordonnees avance(de_x, de_y);
      if (etat_ != Coule) position_+=avance;
  }

  void renflouer() {etat_ = Intact;}

  string name() const {return name_;}

  bool isAlive() 
  {
    if (etat_!= Coule) return true;
    else return false;
  }

  ostream& afficher(ostream& ) const;

  virtual void attaque(Navire &) = 0;
  virtual void replique(Navire &) = 0;
  virtual void est_touche() = 0 ;

  void rencontrer(Navire &);
};

ostream& operator<<(ostream& sortie, Navire const & navire){ return navire.afficher(sortie);}

ostream& operator<<(ostream& sortie, Coordonnees const & c) 
{
  sortie<<"("<<c.x()<<", "<<c.y()<<")";
  return sortie;
}

ostream& operator<<(ostream& sortie, Etat const & etat) 
{
  if (etat == Intact) return sortie<<"intact";
  if (etat ==  Endommage) return sortie<<"ayant subi des dommages";
  if (etat == Coule) return sortie<<"coulé";
  return  sortie<<"état inconnu";
}


ostream& operator<<(ostream& sortie, Pavillon const & pavillon) 
{
  if (pavillon == JollyRogers) return sortie<<"pirate";
  if (pavillon == CompagnieDuSenegal) return sortie<<"français";
  if (pavillon == CompagnieDOstende) return sortie<<"autrichien";
  return  sortie<<"pavillon inconnu";
}

ostream& Navire::afficher(ostream& sortie=cout) const
  {
      sortie << name() << " en "<< position() << " battant pavillon " << pavillon() << ", " << etat_;
      return sortie;
  }

double distance(Coordonnees  c1, Coordonnees  c2)
{ 
  return sqrt( sq( c1.x()-c2.x())  + sq(c1.y()-c2.y()));
}

double distance(Navire & n1, Navire & n2) {return distance(n1.position(), n2.position());}


void Navire::rencontrer(Navire & navire) 
{
    if (distance(*this, navire) < rayon_rencontre && pavillon()!=navire.pavillon() )
    {
        attaque(navire);
        navire.replique(*this);
    }
};
void Coordonnees::operator+=(Coordonnees const& autre)
{
  x_+=autre.x();
  y_+=autre.y();
}


class Pirate: public virtual Navire 
{
    public:
     Pirate(int  x, int y, Pavillon  pavillon)
     :Navire( x, y,pavillon){name_="bateau pirate";}

    virtual void attaque(Navire & navire) override 
    {
        if ( isAlive() && navire.isAlive()) 
        {
        cout<< "A l'abordage !" << endl;
        navire.est_touche();
        }
    }

    virtual void replique(Navire & navire) override 
    {
        if ( isAlive() && navire.isAlive()) 
        {
        cout<< "Non mais, ils nous attaquent ! On riposte !!"<<endl;
        attaque(navire);
        }
    }

    virtual void est_touche( ) override
    {
        if (etat_== Intact)
        {
            etat_ = Endommage;
            return;
        }

        if (etat_== Endommage) 
        {
            etat_ = Coule;
            return;
        }
    }
};

class Marchand: public virtual Navire 
{
    public:
     Marchand(int  x, int y, Pavillon  pavillon)
     :Navire( x, y,pavillon){name_="navire marchand";}

    virtual void attaque(Navire & navire) override 
    {
        cout<< "On vous aura ! (insultes)"<<endl;
    }

    virtual void replique(Navire & navire) override 
    {
        if (etat_==Coule) cout<< "SOS je coule !"<<endl;
        else cout<< "Même pas peur !"<<endl;
    }

    virtual void est_touche( ) override
    {
        etat_ = Coule;
    }

};

class Felon: public Pirate, public Marchand
{
    public:
     Felon(int  x, int y, Pavillon pavillon)
     :Navire( x, y,pavillon), Pirate(x, y,pavillon), Marchand(x, y,pavillon){ name_="navire félon";}

    virtual void attaque(Navire & navire) override 
    {
        Pirate::attaque(navire);
    }

    virtual void replique(Navire & navire) override 
    {
        Marchand::replique(navire);
    }

    virtual void est_touche( ) override
    {
        Pirate::est_touche();
    }
};



/*******************************************
 * Ne rien modifier après cette ligne.
 *******************************************/

void rencontre(Navire& ship1, Navire& ship2)
{
  cout << "Avant la rencontre :" << endl;
  cout << ship1 << endl;
  cout << ship2 << endl;
  cout << "Distance : " << distance(ship1, ship2) << endl;
  ship1.rencontrer(ship2);
  cout << "Apres la rencontre :" << endl;
  cout << ship1 << endl;
  cout << ship2 << endl;
}

int main()
{
  // Test de la partie 1
  cout << "===== Test de la partie 1 =====" << endl << endl;

  // Un bateau pirate 0,0
  Pirate ship1(0, 0, JollyRogers);
  cout << ship1 << endl;

  // Un bateau marchand en 25,0
  Marchand ship2(25, 0, CompagnieDuSenegal);
  cout << ship2 << endl;

  cout << "Distance : " << distance(ship1, ship2) << endl;

  cout << "Quelques déplacements..." << endl;
  cout << "  en haut à droite :" << endl;
  // Se déplace de 75 unités à droite et 10 en haut
  ship1.avancer(75, 10);
  cout << ship1 << endl;

  cout << "  vers le bas :" << endl;
  ship1.avancer(0, -5);
  cout << ship1 << endl;

  cout << endl << "===== Test de la partie 2 =====" << endl << endl;

  cout << "Bateau pirate et marchand ennemis (trop loins) :" << endl;
  rencontre(ship1, ship2);

  cout << endl << "Bateau pirate et marchand ennemis (proches) :" << endl;
  ship1.avancer(-40, -2);
  ship2.avancer(10, 2);
  rencontre(ship1, ship2);

  cout << endl << "Deux bateaux pirates ennemis intacts (proches) :" << endl;
  Pirate ship3(33, 8, CompagnieDOstende);
  rencontre(ship1, ship3);

  cout << endl << "Bateaux pirates avec dommages, ennemis :" << endl;
  rencontre(ship1, ship3);

  cout << endl << "Bateaux marchands ennemis :" << endl;
  Marchand ship4(21, 7, CompagnieDuSenegal);
  Marchand ship5(27, 2, CompagnieDOstende);
  rencontre(ship4, ship5);

  cout << endl << "Pirate vs Felon :" << endl;
  ship3.renflouer();
  Felon ship6(32, 10, CompagnieDuSenegal);
  rencontre(ship3, ship6);

  cout << endl << "Felon vs Pirate :" << endl;
  rencontre(ship6, ship3);

  return 0;
}
