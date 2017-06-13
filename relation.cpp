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
    for(unsigned int i=0;i<nbCouples;i++)
    {
        if (couples[i]->getLabel()==c->getLabel()&&(couples[i]->getX()->getId()==c->getY()->getId()||couples[i]->getY()->getId()==c->getX()->getId())) return;
    }

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
        const QString lab2=lab+"_inverse";
        Couple* c2= new Couple(lab2,y,x,e);
        addCouple(c2);
    }

}

void Relation::retirerCouple(unsigned int i){
    for(unsigned int j=i;j<nbCouples;j++)
        couples[j]=couples[j+1];
    nbCouples=nbCouples-1;
}
void Relation::retirerCouple(const Couple *c){
    for(unsigned int i=0;i<nbCouples;i++)
        if (couples[i]->getLabel()==c->getLabel()) retirerCouple(i);
}
Couple* Relation::getCouple(const QString &l){
    for(unsigned int i=0;i<nbCouples;i++)
        {
            if (couples[i]->getLabel()==l)
               return couples[i];
        }

    return nullptr;
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
