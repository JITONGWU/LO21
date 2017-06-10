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
    qDebug()<<"addcouple réussi!\n";

    if (nbCouples==nbMaxCouples){
        qDebug()<<"addcouple réussi!\n";

        Couple** newCouples= new Couple*[nbMaxCouples+5];
        for(unsigned int i=0; i<nbCouples; i++) newCouples[i]=couples[i];
        Couple** oldCouples=couples;
        couples=newCouples;
        nbMaxCouples+=10;
        if (oldCouples) {
            for(unsigned int i=0; i<nbCouples; i++) delete oldCouples[i];
            qDebug()<<"addcouple réussi!\n";
            //delete[] oldCouples;
            //qDebug()<<"addcouple réussi!\n";


        }
    }
    couples[nbCouples++]=const_cast<Couple*>(c);

}


void Relation::addCouple(const QString& lab, Note *x, Note *y, const QString &e){


    for(unsigned int i=0;i<getNbCouples();i++)
        {
            if (couples[i]->getLabel()==lab ){
            throw NotesException("Erreur : creation of an already existent couple");}
        }
    Couple* c=new Couple(lab,x,y,e);
    addCouple(c);
    if (orient==false){ // relation non orienté
        Couple* c2= new Couple(lab,y,x,e);
        addCouple(c2);
    }

}
/*
void Relation::retirerCouple(unsigned int i){
    qDebug()<<"retirer couple réussi\n";

    if(i<nbCouples) {
        Couple * supprimer=couples[i];
        delete supprimer;
    else throw NotesException("didn't find couple\n");
    nbCouples--;


    while(i<nbCouples){
        couples[i]=couples[i+1];
        i++;
    }

}
*/
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

