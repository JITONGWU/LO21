#ifndef RELATION_H
#define RELATION_H
#include<QStringList>
#include "notes.h"
#include "relationmanager.h"

class Couple{
    QString label;
    Note* x;
    Note* y;
    QString etat;
public:
    friend void  RelationManager::restaurerLesCoupleContenantNoteX(QString id);
    friend void  RelationManager::archiverLesCoupleContenantNoteX(QString id);
    friend void  RelationManager::supprimerLesCoupleContenantNoteX(QString id);
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
    class Iterator {
            friend class Relation;
           Couple** currentN;
            unsigned int nbRemain;
            Iterator(Couple** a, unsigned nb):currentN(a),nbRemain(nb){}
        public:
            Iterator():currentN(NULL),nbRemain(0){}
            bool isDone() const { return nbRemain==0; }
            void next() {
                if (isDone())
                    throw NotesException("error, next on an iterator which is done");
                nbRemain--;
                currentN++;
            }
           Couple& current() const {
                if (isDone())
                    throw "error, indirection on an iterator which is done";
                return **currentN;
            }
        };
        Iterator getIterator() {
            return Iterator(couples,nbCouples);
        }




    friend void  RelationManager::restaurerLesCoupleContenantNoteX(QString id);
    friend void  RelationManager::archiverLesCoupleContenantNoteX(QString id);
    friend void  RelationManager::supprimerLesCoupleContenantNoteX(QString id);
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
    void retirerCouple(const Couple *c);
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
    bool supprimeroupas(QString id);

};
#endif // RELATION_H






















