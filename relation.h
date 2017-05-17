#ifndef RELATION_H_INCLUDED
#define RELATION_H_INCLUDED
#include <QString>

class Couple{
    QString label;
    Note* x;
    Note* y;
public:
    Couple(Note* a,Note* b):x(a),y(b){}
    QString& getLabel(){return label;}
    Note* getX(){return x;}
    Note* getY(){return y;}
    bool getOrient()const {return orient;}
    void setCouple(Note* a, Note* b){x=a;y=b;}
};
class Relation{
    QString titre;
    QString desc;
    Couple** couples ;
    bool orient;
    unsigned int nb;
    unsigned int nbmax;

public:
    void addCouple(Couple* c);
    void addCouple(Note** x,Note** y);
    void retireCouple(QString& label);
    QString& getTitre()const {return titre;}
    QString& getDesc()const{return desc;}

    struct Handler {
        NotesManager* instance; // pointeur sur l'unique instance
        Handler():instance(nullptr){}
        ~Handler() { delete instance; }
    };
    static Handler handler;
};

class ReManager{
    Relation** relations;
    unsigned int nbRe;
    unsigned int nbMaxRe;
public:
    void afficherAscendents(Note* y);
    void afficherDescendenets(Note* x);
};

#endif // RELATION_H_INCLUDED
