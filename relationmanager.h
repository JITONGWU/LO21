#ifndef RELATIONMANAGER_H
#define RELATIONMANAGER_H
#include "relation.h"



class RelationManager{
    friend class Relation;

    Relation** relations;
    unsigned int nbRe;
    unsigned int nbMaxRe;
    void addRelation(Relation* r);
    mutable QString filename;

    RelationManager();
    ~RelationManager();
    RelationManager(const RelationManager& m);
    RelationManager& operator=(const RelationManager& m);
    //éviter l'affection = et constructeru par recopie


    struct HandlerM {   // singleton
            RelationManager* RM;
            HandlerM():RM(nullptr){}
            ~HandlerM() { delete RM; }
        };
        static HandlerM handler;



public:

    void addRelation(const QString& t,const QString& d,bool o, Couple** c,unsigned int nb=0);
    void afficherAscendents(Note* y);//
    void afficherDescendenets(Note* x);//

    Relation& getRelation(const QString& t); // return the relation avec titre t
    void setFilename(const QString& f) { filename=f; }
    void load(); // load relation from file filename
    void save() const; // save relation in file filename

    static RelationManager& getManager();
    static void freeManager();

        class Iterator {
                friend class RelationManager;
                Relation** currentR;
                unsigned int nbRemain;
                Iterator(Relation** a, unsigned nb):currentR(a),nbRemain(nb){}
            public:
                Iterator():currentR(nullptr),nbRemain(0){}
                bool isDone() const { return nbRemain==0; }
                void next() {
                    if (isDone())
                        throw NotesException("error, next on an iterator which is done");
                    nbRemain--;
                    currentR++;
                }
               Relation& current() const {
                    if (isDone())
                        throw NotesException("error, indirection on an iterator which is done");
                    return **currentR;
                }
            };
            Iterator getIterator() {
                return Iterator(relations,nbRe);
            }

};



#endif // RELATIONMANAGER_H
