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
  /*  ~Couple(){
    qDebug()<<"destructeur de couple\n";
    }*/
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
    Couple** couples ;
    bool orient;
    unsigned int nbCouples;
    unsigned int nbMaxCouples;
public:
    Relation(const QString& t, const QString& d,bool o=false,Couple** c=nullptr,unsigned int nbC=0,unsigned int nbm=0):
        titre(t),desc(d),orient(o),couples(c),nbCouples(nbC),nbMaxCouples(nbm){}
  /* ~Relation(){
        for(unsigned int i=0;i<nbCouples;i++)delete couples[i];
        delete[] couples;
        qDebug()<<"destructeur de relation\n";
    }*/
    void addCouple(const Couple *c);
    void addCouple(const QString& lab, Note *x, Note *y, const QString& e="N");// seulement pour les notes de dernière version!
    void retirerCouple(unsigned int i);
    QString getTitre()const {return titre;}
    QString getDesc()const{return desc;}
    bool getOrient()const {return orient;}
    unsigned int getNbCouples()const {return nbCouples;}
    unsigned int getNbMaxCouples()const {return nbMaxCouples;}
    void setTitre(const QString& t){titre=t;}
    void setDesc(const QString& d){desc=d;}
    void setOrient(bool o){orient=o;}
    void setNbCouples(unsigned int i){nbCouples=i;nbMaxCouples=i;}
    Couple* getCouple(const QString& l);//get couple par label*
    Couple* getCoupleParIndice(unsigned int i);//get couple par la position dans le tableau
};

class Reference:public Relation{  //singleton
private:
    struct Handler {
            Reference* reference; // pointeur sur l'unique instance
            Handler():reference(nullptr){}//affectation pour objet unique
            ~Handler() { delete reference; }
        };
public:
    Reference():Relation("reference","\ref{idNote}"){}
    static Handler handler;
    static Reference* getRef();
    static void freeRef();

};
#endif // RELATION_H
//créer une note --- choisir le type --- remplir les attribues --- sauvegarder ( si on trouve \ref, addCouple()dans reference)
//choisir une note existant --- modifier / supprimer ce note --- sauvegarder ( si on trouve \ref, addCouple()dans reference)
//création d'une relation --- remplir le titre , description etc...
//choisir une relation existant --- supprimer/ ajouter les couples
