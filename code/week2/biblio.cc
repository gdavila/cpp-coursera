#include <iostream>
#include <vector>
#include <string>
using namespace std;

/*******************************************
 * Completez le programme a partir d'ici.
 *******************************************/
// Chaines de caractÃ¨res Ã  utiliser pour les affichages:
/*

Ã©tÃ© jetÃ©

d'un

n'est

L'oeuvre

bibliothÃ¨que

dÃ©truit

*/

class Auteur{
    private:
        string name;
        bool prix;

    public:
        Auteur(string name, bool prix=false) : name(name), prix(prix) {}

        string getNom() const {return name;}

        bool getPrix() const {return prix;}
};




class Oeuvre {
    private:
        string titre;
        Auteur auteur;
        string langue;

    public:

        Oeuvre(string titre, Auteur const&  auteur, string langue) 
        : titre(titre), auteur(auteur), langue(langue) {}

        ~Oeuvre(){
            cout << "L'oeuvre \""<< titre << ", " << auteur.getNom() << ", "<< "en " << langue << "\" n'est plus disponible." << endl;
        }

        string getTitre() const {return titre;}

        const Auteur &  getAuteur() const {return auteur;}

        string getLangue() const {return langue;}

        void affiche() {
            cout << titre << ", " << auteur.getNom() << ", "<< "en " << langue << endl;
        }
};

class Exemplaire 
{
private:
    Oeuvre const &  oeuvre;

public:
    Exemplaire(const Oeuvre & o)
    :  oeuvre(o) {
        cout << "Nouvel exemplaire de : " <<oeuvre.getTitre()<< ", " << oeuvre.getAuteur().getNom() << ", en "<< oeuvre.getLangue() << endl; 
    }

    Exemplaire(Exemplaire const& exemplaire)
    : oeuvre(exemplaire.oeuvre) { 
        cout << "Copie d’un exemplaire de : " <<oeuvre.getTitre()<< ", " << oeuvre.getAuteur().getNom() << ", en "<< oeuvre.getLangue() << endl; 
    }

    ~Exemplaire(){
        cout << "Un exemplaire de  \"" <<oeuvre.getTitre()<< ", " << oeuvre.getAuteur().getNom() << ", en "<< oeuvre.getLangue() << "\"" << " a été jeté !" <<endl; 
    }

    const Oeuvre & getOeuvre() const { return oeuvre;}

    void affiche() {
        cout << "Exemplaire de : " << oeuvre.getTitre()<< ", " << oeuvre.getAuteur().getNom() << ", en "<< oeuvre.getLangue(); 
    }
    
};

class Bibliotheque
{
private:
    string name;
    vector<Exemplaire *>  exemplaires;

public:
    Bibliotheque(string name)
    : name(name) {
        cout << "La bibliothèque "<< name << " est ouverte !" << endl;
    }

    ~Bibliotheque(){
        cout << "La bibliothèque "<< name << " ferme ses portes," << endl;
        cout << "et détruit ses exemplaires : "<< endl;
        for (vector<Exemplaire *>::iterator i = exemplaires.begin() ; i != exemplaires.end(); ++i){
            delete *i;
        }
        exemplaires.clear();
    }

    string getNom(){return name;}

    void stocker (Oeuvre & oeuvre, int n=1){
        while(n){
            exemplaires.push_back(new Exemplaire(oeuvre));
            n--;
        }
    }

    void lister_exemplaires(string langue=""){
        for (vector<Exemplaire *>::iterator i = exemplaires.begin() ; i != exemplaires.end(); ++i){
        if (langue == "") {
            (*i)->affiche();
            cout<<endl;
        }
        else {
            string l= (*i)->getOeuvre().getLangue();
            if(langue == l){
                (*i)->affiche();
                cout<<endl;
            }
          }
        }
    }
    int compter_exemplaires(Oeuvre & oeuvre) {
        int counter=0;
        for (vector<Exemplaire *>::iterator i = exemplaires.begin() ; i != exemplaires.end(); ++i){
            if ( (*i)->getOeuvre().getTitre() == oeuvre.getTitre()){
                counter++;
            }
        }
        return counter;
    }

    void afficher_auteurs(bool prix = false){ 
        for (vector<Exemplaire *>::iterator i = exemplaires.begin() ; i != exemplaires.end(); ++i){
            bool p = (*i)->getOeuvre().getAuteur().getPrix();
            if (!prix || p){
                cout << (*i)->getOeuvre().getAuteur().getNom() << endl;
            }

        }

    }


};



/*******************************************
 * Ne rien modifier apres cette ligne.
 *******************************************/

int main()
{
  Auteur a1("Victor Hugo"),
         a2("Alexandre Dumas"),
         a3("Raymond Queneau", true);

  Oeuvre o1("Les Misérables"           , a1, "français" ),
         o2("L'Homme qui rit"          , a1, "français" ),
         o3("Le Comte de Monte-Cristo" , a2, "français" ),
         o4("Zazie dans le métro"      , a3, "français" ),
         o5("The Count of Monte-Cristo", a2, "anglais" );

  Bibliotheque biblio("municipale");
  biblio.stocker(o1, 2);
  biblio.stocker(o2);
  biblio.stocker(o3, 3);
  biblio.stocker(o4);
  biblio.stocker(o5);

  cout << "La bibliothèque " << biblio.getNom()
       << " offre les exemplaires suivants :" << endl;
  biblio.lister_exemplaires();

  const string langue("anglais");
  cout << " Les exemplaires en "<< langue << " sont :" << endl;
  biblio.lister_exemplaires(langue);

  cout << " Les auteurs à succès sont :" << endl;
  biblio.afficher_auteurs(true);

  cout << " Il y a " << biblio.compter_exemplaires(o3) << " exemplaires de "
       << o3.getTitre() << endl;

  return 0;
}