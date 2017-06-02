#ifndef RELATION_H
#define RELATION_H
#include<QStringList>
#include "notes.h"
class Couple{
    QString label;
    Note* x;
    Note* y;
    QString etat;
public:
    Couple(const QString& l, Note* a,Note* b,const QString& e="N"):label(l),x(a),y(b),etat(e){}
    QString getLabel()const{return label;}
    Note* getX() const {return x;}
    Note* getY() const {return y;}
    QString getEtat()const {return etat;}
    void setLabel(const QString& l){label=l;}
    void setEtat(const QString& e){etat=e;}
    QString AfficherCouple();
};

class Relation{
protected:
    QString titre;
    QString desc;
    Couple** couples ;
    bool orient;
    unsigned int nb;
    unsigned int nbmax;

public:
    void addCouple(Couple* c);
    Relation(const QString& t, const QString& d,bool o=true,Couple** c=nullptr,int n=0,int m=0):
        titre(t),desc(d),couples(c),orient(o),nb(n),nbmax(m){}

    void addCouple(const QString& lab,Note* x,Note* y,const QString& e);// seulement pour les notes de dernière version!
    void retirerCouple(QString& label);//
    QString getTitre()const {return titre;}
    QString getDesc()const{return desc;}
    unsigned int getNb()const {return nb;}
    bool getOrient()const {return orient;}
    Couple* getCouple(const QString& l);//get couple par label
    Couple* getCouple(unsigned int i);//get couple par la position dans le tableau

    class Iterator {
            friend class Relation;
            Couple** currentC;
            unsigned int nbRemain;
            Iterator(Couple** a, unsigned nb):currentC(a),nbRemain(nb){}
        public:
            Iterator():currentC(nullptr),nbRemain(0){}
            bool isDone() const { return nbRemain==0; }
            void next() {
                if (isDone())
                    throw NotesException("error, next on an iterator which is done");
                nbRemain--;
                currentC++;
            }
           Couple& current() const {
                if (isDone())
                    throw NotesException("error, indirection on an iterator which is done");
                return **currentC;
            }
        };
        Iterator getIterator() {
            return Iterator(couples,nb);
        }

// for(
};

class Reference:public Relation{  //singleton
private:
    struct Handler {
            Reference* reference; // pointeur sur l'unique instance
            Handler():reference(nullptr){}//affectation pour objet unique
            ~Handler() { delete reference; }
        };
public:
    Reference():Relation("Référence","\ref{idNote}"){}


    static Handler handler;
    static Reference& getRef();
    static void freeRef();

};
/*

void addReference(QString& s){
    // lier tous les attributs de type string
    QStringList lst=s.split("\ref{",QString::SkipEmptyParts,Qt::CaseSensitive);  // majuscule  ? minuscule ?
    for(int i=1;i<lst.count();i++)
    {
        QStringList l=lst.at(i).split("}",QString::SkipEmptyParts, Qt::CaseSensitive);
        std::cout<<l.at(0).trimmed().toStdString()<<std::endl;
        //if(getNote(l.at(0)) )  //si on trouve les notes avec id= l.at(0)
        // reference.addCouple(Couple::setCouple(getNote(id),getNote(l.at(0))));
    }

}*/
#endif // RELATION_H
//créer une note --- choisir le type --- remplir les attribues --- sauvegarder ( si on trouve \ref, addCouple()dans reference)
//choisir une note existant --- modifier / supprimer ce note --- sauvegarder ( si on trouve \ref, addCouple()dans reference)
//création d'une relation --- remplir le titre , description etc...
//choisir une relation existant --- supprimer/ ajouter les couples
