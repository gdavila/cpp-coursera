#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Pour simplifier
typedef string Forme   ;
typedef string Couleur ;

class Brique
{
private:
  Forme   forme   ;
  Couleur couleur ;

public:
  /*****************************************************
    Compléter le code à partir d'ici
  *******************************************************/

  //Constructor
    Brique(Forme forme, Couleur couleur)
    : forme(forme), couleur(couleur) {}

    ostream& afficher(ostream& sortie) const 
    {
        if (couleur != ""){sortie << "(" << forme << ", " << couleur << ")"; }
        else {sortie << forme;}
        return sortie;
    }
};

ostream& operator<<(ostream& sortie, Brique const & B) {  return B.afficher(sortie);}

typedef vector<Brique> Line;
typedef vector<Line> Surface;
typedef vector<Surface> Volume;


class Construction
{
private:
    Volume contenu;
    friend class Grader;
public:
    Construction(Brique B)
    :contenu(Volume(1,Surface(1,Line(1,B))) ){}

    int height() const
    {
        return contenu.size();
    }

    int depth() const
    {
        /**
        int depth=0;
        for (int i=0; i<= height(); i++)
        {
           if (contenu[i].size() > depth)
           {
               depth = contenu[i].size();
           }
        }
        */
        int depth = contenu[0].size();
        return depth;
    }
  
    ostream& afficher(ostream& sortie) const 
    {
        for (int i=contenu.size() -1; i >= 0 ; i--)
        {
            sortie << "Couche " << i << " :" << endl;
            for (int j=0; j < contenu[i].size() ; j++ )
            {
                for (int k=0; k < contenu[i][j].size() ; k++)
                {
                    sortie<<contenu[i][j][k];
                }
                sortie << endl ;
            }
        }
        return sortie;
    }

    Construction& operator^=(Construction const&  C)
    {
        for (int i=0; i < C.contenu.size(); i++)
        {
            contenu.push_back(C.contenu[i]);
        }
        return *this;
    }

    Construction& operator-=(Construction const&  C)
    {
        if (height() <= C.height() )
        {
            for (int i=0; i < contenu.size(); i++)
            {
                for (int j=0; j < C.contenu[i].size(); j++)
                {
                    contenu[i].push_back(C.contenu[i][j]);
                }
            }
        }
        return *this;
    }

    Construction& operator+=(Construction const&  C)
    {
        if (height() <= C.height() && depth() <= C.depth() )
        {
            for (int i=0; i < contenu.size(); i++)
            {
                for (int j=0; j < contenu[i].size(); j++)
                {
                    for (int k=0; k < C.contenu[i][j].size(); k++)
                    {
                        contenu[i][j].push_back(C.contenu[i][j][k]);
                    }
                } 
            }
        }
        return *this;
    }
};


ostream& operator<<(ostream& sortie, Construction const & C) {  return C.afficher(sortie);}

const Construction operator^(Construction C1, Construction const& C2){ return C1^=C2;}
const Construction operator-(Construction C1, Construction const& C2){ return C1-=C2;}
const Construction operator+(Construction C1, Construction const& C2){ return C1+=C2;}


const Construction operator*(unsigned int n, Construction const& a)
{
    Construction aux = a;
    for (unsigned int i=0; i<n-1; i++ ){aux+=a; }
    return aux;
}

const Construction operator/(unsigned int n, Construction const& a)
{
    Construction aux = a;
    for (unsigned int i=0; i<n-1; i++ ){aux^=a; }
    return aux;
}

const Construction operator%(unsigned int n, Construction const& a)
{
    Construction aux = a;
    for (unsigned int i=0; i<n-1; i++ ){aux-=a; }
    return aux;
}

/*******************************************
 * Ne rien modifier après cette ligne.
 *******************************************/

int main()
{
  // Modèles de briques
  Brique toitD("obliqueD", "rouge");
  Brique toitG("obliqueG", "rouge");
  Brique toitM(" pleine ", "rouge");
  Brique mur  (" pleine ", "blanc");
  Brique vide ("                 ", "");

  unsigned int largeur(4);
  unsigned int profondeur(3);
  unsigned int hauteur(3); // sans le toit

  // on construit les murs
  Construction maison( hauteur / ( profondeur % (largeur * mur) ) );

  // on construit le toit
  Construction toit(profondeur % ( toitG + 2*toitM + toitD ));
  toit ^= profondeur % (vide + toitG + toitD);

  // on pose le toit sur les murs
  maison ^= toit;

  // on admire notre construction
  cout << maison << endl;

  return 0;
}
