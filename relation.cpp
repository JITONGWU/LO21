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


void Relation::addCouple(const QString& lab, Note* x, Note* y, const QString &e){
    for(unsigned int i=0;i<couples.size();i++)
        {
            if (couples.at(i)->getLabel()==lab)
                throw NotesException("Erreur : creation of an already existent relation");
        }
    //tester si x et y sont les notes de dernière version
    Couple* c=new Couple(lab,x,y,e);
    couples.append(c);
    if (orient==false){ // relation non orienté
        Couple* c2= new Couple(lab,y,x,e);
        couples.append(c2);
    }
}
//retirer couple : couples.removeOne(Couple*)
Couple* Relation::getCouple(const QString &l){
    for(unsigned int i=0;i<couples.size();i++)
        {
            if (couples.at(i)->getLabel()==l)
               return couples.at(i);
        }

    throw NotesException("erreur: didn't find couple");
}
QString Couple::AfficherCouple(){

    QString s="("+this->getX()->getId()+","+this->getY()->getId()+")";
    return s;
}
//couples.at(i)
