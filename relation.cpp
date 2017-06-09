#include "relation.h"
#include <QDebug>
// reference singleton
Reference::Handler Reference::handler=Handler();

Reference *Reference::getRef(){
    if (!handler.reference) handler.reference=new Reference;
    return handler.reference;
}

void Reference::freeRef(){
    delete handler.reference;
    handler.reference=nullptr;
}
void Relation::addCouple(const Couple* c){
    if (nbCouples==nbMaxCouples){
        Couple** newCouples= new Couple*[nbMaxCouples+5];
        for(unsigned int i=0; i<nbCouples; i++) newCouples[i]=couples[i];
        Couple** oldCouples=couples;
        couples=newCouples;

        nbMaxCouples+=5;
        if (oldCouples) delete[] oldCouples;
    }
    couples[nbCouples++]=const_cast<Couple*>(c);

}


void Relation::addCouple(const QString& lab, Note &x, Note &y, const QString &e){
    qDebug()<<"\n";

    for(unsigned int i=0;i<getNbCouples();i++)
        {                qDebug()<<"addcouple! réussi\n";

            if (couples[i]->getLabel()==lab ){

            throw NotesException("Erreur : creation of an already existent couple");}
        }
    qDebug()<<"addcouple réussi\n";
    Couple* c=new Couple(lab,x,y,e);
    qDebug()<<"addcouple réussi\n";
    addCouple(c);
    qDebug()<<"addcouple réussi\n";
    if (orient==false){ // relation non orienté
        Couple* c2= new Couple(lab,y,x,e);
        addCouple(c2);
    }

}
//retirer couple : couples.removeOne(Couple*)
void Relation::retirerCouple(unsigned int i){
    qDebug()<<"retirer couple réussi\n";

    if(i<nbCouples) {
        Couple * supprimer=couples[i];
        delete supprimer;
    qDebug()<<"retirer couple réussi\n";}

    else throw NotesException("didn't find couple\n");
    nbCouples--;
    qDebug()<<"retirer couple réussi\n";

    while(i<nbCouples){
        couples[i]=couples[i+1];
        i++;
    }
    qDebug()<<"retirer couple réussi\n";

}

Couple* Relation::getCouple(const QString &l){
    for(unsigned int i=0;i<nbCouples;i++)
        {
            if (couples[i]->getLabel()==l)
               return couples[i];
        }

    throw NotesException("erreur: didn't find couple");
}
Couple* Relation::getCoupleParIndice(unsigned int i){
    if(i<getNbCouples()) return couples[i];
    else throw NotesException("erreur: didn't find couple");
    qDebug()<<"xingbuxinga\n";

}

QString Couple::AfficherCouple(){

    QString s="("+this->getX()->getId()+","+this->getY()->getId()+")";
    return s;
}

