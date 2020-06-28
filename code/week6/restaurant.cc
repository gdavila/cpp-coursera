#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

/*****************************************************
  * Compléter le code à partir d'ici
 *****************************************************/


string fmt(string str)
{
    if(str.find('.') != std::string::npos)
    {
        // Remove trailing zeroes
        str = str.substr(0, str.find_last_not_of('0')+1);
        // If the decimal point is now the last character, remove that as well
        if(str.find('.') == str.size()-1)
        {
            str = str.substr(0, str.size()-1);
        }
    }
    return str;
}


class Produit {
  protected:
    string name;
    string unit;

  public:
    Produit(string name, string unit="")
    : name(name), unit(unit) {}

    string getNom() const {return name;}

    string getUnite() const {return unit;}

    virtual string toString() const {return name;}

    virtual const Produit* adapter(double n) const {return this;}

    virtual double quantiteTotale(const string& n) const
    {
      if (name==n) return 1;
      else return 0;
    }
};


class Ingredient 
{
  protected:
    const Produit & product;
    double quantity;

  public:
    Ingredient(const Produit & product, double quantity)
    : product(product), quantity(quantity) {}

    const Produit &  getProduit() const {return product;}

    double getQuantite() const {return quantity;}

    string descriptionAdaptee() const 
    {
      const Ingredient adapted_ingredient = adapter();
      return adapted_ingredient.toString();
    }

    Ingredient adapter(double n=1) const{return Ingredient(*product.adapter(n*quantity), n*quantity); }

    string toString() const 
    {
      //"<quantity> <unit> de <product_representation>"
      return to_string(quantity) + " " + product.getUnite() + " de " + product.toString();
    }

    double quantiteTotale(const string& n) const
    {
      return quantity*product.quantiteTotale(n);
    }

};

class Recette
{
  protected:
    string name;
    double nbFois_;
    vector<Ingredient*> ingredients;
  
  public:
    Recette(string name, double nbFois=1)
    : name(name), nbFois_(nbFois) {}

    void ajouter(const Produit& p, double quantite)
    {
      Ingredient* I = new Ingredient(p,quantite*nbFois_);
      ingredients.push_back(I);

      return;
    }

    Recette adapter(double n) const 
    {
      Recette adapted_recet(name, nbFois_*n);
      for (auto adaptaed_ingredient:ingredients )
      {
        adapted_recet.ajouter(adaptaed_ingredient->getProduit(), adaptaed_ingredient->getQuantite()/nbFois_);
      }
      return adapted_recet;
    }

    string toString() const
    {
      string out;
      out = "   Recette \"" + name + "\" x " + fmt(to_string(nbFois_)) + ":\n";
      int count(0);
      string endline("\n");
      for (auto i:ingredients )
      {
        count+=1;
        if (i==ingredients.back()) endline="";
        out+= "   " + to_string(count) + ". " + i->descriptionAdaptee() + endline;
      }
      return out;
    }

    const vector<Ingredient*> & getIngredients() const
    {
      return ingredients;
    }

    double quantiteTotale(const string& n) const
    {
      double sum(0);
      for (auto i: ingredients)
      {
        sum+=i->quantiteTotale(n);
      }
      return sum;
    }

};

class ProduitCuisine: public Produit
{
  protected:
    Recette  recet;
  public:
    ProduitCuisine(string name)
    : Produit(name, "portion(s)"), recet(name) {}

    void ajouterARecette(const Produit& produit, double quantite)
    {
      recet.ajouter(produit, quantite);
    }

    void setRecet(Recette r)
    {
      recet = r;
    }

    virtual string toString() const override 
    {
      string s = Produit::toString() + "\n" + recet.toString();
      return s;
    } 

    virtual const Produit* adapter(double n) const override 
    {
      ProduitCuisine* adapted_prod = new ProduitCuisine(name);
      adapted_prod->setRecet(recet.adapter(n));
      return adapted_prod;
    }

    double quantiteTotale(const string& n) const override
    {
      if (name==n) return 1;
      else return recet.quantiteTotale(n);
    }

};



/*******************************************
 * Ne rien modifier après cette ligne.
 *******************************************/
void afficherQuantiteTotale(const Recette& recette, const Produit& produit)
{
  string nom = produit.getNom();
  cout << "Cette recette contient " << recette.quantiteTotale(nom)
       << " " << produit.getUnite() << " de " << nom << endl;
}

int main()
{
  // quelques produits de base
  Produit oeufs("oeufs");
  Produit farine("farine", "grammes");
  Produit beurre("beurre", "grammes");
  Produit sucreGlace("sucre glace", "grammes");
  Produit chocolatNoir("chocolat noir", "grammes");
  Produit amandesMoulues("amandes moulues", "grammes");
  Produit extraitAmandes("extrait d'amandes", "gouttes");

  ProduitCuisine glacage("glaçage au chocolat");
  // recette pour une portion de glaçage:
  glacage.ajouterARecette(chocolatNoir, 200);
  glacage.ajouterARecette(beurre, 25);
  glacage.ajouterARecette(sucreGlace, 100);
  cout << glacage.toString() << endl;

  ProduitCuisine glacageParfume("glaçage au chocolat parfumé");
  // besoin de 1 portions de glaçage au chocolat et de 2 gouttes
  // d'extrait d'amandes pour 1 portion de glaçage parfumé

  glacageParfume.ajouterARecette(extraitAmandes, 2);
  glacageParfume.ajouterARecette(glacage, 1);
  cout << glacageParfume.toString() << endl;

  Recette recette("tourte glacée au chocolat");
  recette.ajouter(oeufs, 5);
  recette.ajouter(farine, 150);
  recette.ajouter(beurre, 100);
  recette.ajouter(amandesMoulues, 50);
  recette.ajouter(glacageParfume, 2);

  cout << "===  Recette finale  =====" << endl;
  cout << recette.toString() << endl;
  afficherQuantiteTotale(recette, beurre);
  cout << endl;

  // double recette
  Recette doubleRecette = recette.adapter(2);
  cout << "===  Recette finale x 2 ===" << endl;
  cout << doubleRecette.toString() << endl;

  afficherQuantiteTotale(doubleRecette, beurre);
  afficherQuantiteTotale(doubleRecette, oeufs);
  afficherQuantiteTotale(doubleRecette, extraitAmandes);
  afficherQuantiteTotale(doubleRecette, glacage);
  cout << endl;

  cout << "===========================\n" << endl;
  cout << "Vérification que le glaçage n'a pas été modifié :\n";
  cout << glacage.toString() << endl;

  return 0;
}
