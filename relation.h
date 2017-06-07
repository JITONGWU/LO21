#ifndef RELATION_H
#define RELATION_H
#include<QStringList>
#include "notes.h"
#include <stdlib.h>

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
    void setX(Note* a){x=a;}
    void setY(Note* b){y=b;}
    void setLabel(const QString& l){label=l;}
    void setEtat(const QString& e){etat=e;}
    QString AfficherCouple();
};

class Relation{
protected:
    QString titre;
    QString desc;
    QList<Couple*> couples ;
    bool orient;
public:
    Relation(const QString& t, const QString& d,bool o=true,QList<Couple*> *c= nullptr):
        titre(t),desc(d),couples(*c),orient(o){}
    ~Relation(){couples.clear();}

    void addCouple(const QString& lab,Note* x,Note* y,const QString& e);// seulement pour les notes de dernière version!
    QString getTitre()const {return titre;}
    QString getDesc()const{return desc;}
    bool getOrient()const {return orient;}
    QList<Couple*> getCouples() const {return couples;}

    void setTitre(const QString& t){titre=t;}
    void setDesc(const QString& d){desc=d;}
    void setOrient(bool o){orient=o;}


    Couple* getCouple(const QString& l);//get couple par label
    Couple* getCouple(unsigned int i);//get couple par la position dans le tableau
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
#endif // RELATION_H
//créer une note --- choisir le type --- remplir les attribues --- sauvegarder ( si on trouve \ref, addCouple()dans reference)
//choisir une note existant --- modifier / supprimer ce note --- sauvegarder ( si on trouve \ref, addCouple()dans reference)
//création d'une relation --- remplir le titre , description etc...
//choisir une relation existant --- supprimer/ ajouter les couples
