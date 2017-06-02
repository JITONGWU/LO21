#include "relation.h"
// reference singleton
Reference::Handler Reference::handler=Handler();

Reference& Reference::getRef(){
    if (!handler.reference) handler.reference=new Reference;
    return *handler.reference;
}

void Reference::freeRef(){
    delete handler.reference;
    handler.reference=nullptr;
}



void Relation::addCouple(Couple* c){
    for(unsigned int i=0; i<nb; i++){
        if (couples[i]->getLabel()==c->getLabel()) throw NotesException("error, creation of an already existent relation");
    }
    if (nb==nbmax){
        Couple** newCouples= new Couple*[nbmax+5];
        for(unsigned int i=0; i<nb; i++) newCouples[i]=couples[i];
        Couple** old=couples;
        couples=newCouples;
        nbmax+=5;
        if (old) delete[] old;
    }
    couples[nb++]=c;
}

void Relation::addCouple(const QString& lab, Note* x, Note* y, const QString &e){
    for(unsigned int i=0; i<nb; i++){
        if (couples[i]->getLabel()==lab) throw NotesException("Erreur : creation of an already existent relation");
    }
    //tester si x et y sont les notes de dernière version
    Couple* c=new Couple(lab,x,y,e);
    addCouple(c);
    if (orient==false){ // relation non orienté
        Couple* c2= new Couple(lab,y,x);
        addCouple(c2);
    }
}
void  Relation::retirerCouple(QString& lab){ //si non oriente ,retirer deux fois
    Couple** supprimer= new Couple*[nbmax];
    for(unsigned int i=0; i<nb; i++){
        if (couples[i]->getLabel()==lab) supprimer[i]=couples[i];
    }
    if(supprimer) delete[] supprimer;

    else throw NotesException("erreur: didn't find couple");
}
Couple* Relation::getCouple(const QString &l){
    for(unsigned int i=0; i<nb; i++){
        if (couples[i]->getLabel()==l) return couples[i];
    }

    throw NotesException("erreur: didn't find couple");
}
QString Couple::AfficherCouple(){

    QString s="("+this->getX()->getId()+","+this->getY()->getId()+")";
    return s;
}
Couple* Relation::getCouple(unsigned int i){
    if(i<nb) return couples[i];
    throw NotesException("erreur: didn't find couple");
}
