#include "relation.h"

void Relation::addCouple(Couple* c){
    for(unsigned int i=0; i<nbNotes; i++){
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

void Relation:addCouple(const QString& lab,Note* x,Note* y){
    for(unsigned int i=0; i<nb; i++){
        if (couples[i]->getLabel()==label) throw NotesException("Erreur : creation of an already existent relation");
    }
    Couple* c=new Couple(lab,x,y);
    addCouple(c);
    if (orient==false){
        Couple* c2= new Couple(label,y,x);
        addCouple(c2);
    }
}
void  Relation::retirerCouple(QString& lab){ //si non oriente ,retirer deux fois
    Couple* supprimer= new Couple;
    for(unsigned int i=0; i<nb; i++){
        if (couples[i]->getLabel()==lab) supprimer=couples[i];
    }
    if(supprimer) delete[] supprimer;

    else throw NotesException("erreur: didn't find couple");
}
void ReManager::afficherAscendents(Note* y){
    for(unsigned int i=0;i<nbRe; i++)
    {
        for(unsigned int j=0;j<relations[i]->nb; j++)
            if(relations[i]->couples[j]->y==y) Couple[j]->x->afficherNote(); // ou getId();
    }
}
void ReManager::afficherDescendents(Note* x){
    for(unsigned int i=0;i<nbRe; i++)
    {
        for(unsigned int j=0;j<relations[i]->nb; j++)
            if(relations[i]->couples[j]->x==x) Couple[j]->y->afficherNote();
    }
}
