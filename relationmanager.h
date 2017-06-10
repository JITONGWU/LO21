#ifndef RELATIONMANAGER_H
#define RELATIONMANAGER_H
#include "relation.h"
class RelationManager{
    //friend class Relation;

    Relation** relations;
    mutable QString filename;
    unsigned int nbRelations;
    unsigned int nbMaxRelations;

    struct Handler {
        RelationManager* instance; // pointeur sur l'unique instance
        Handler():instance(nullptr){}
        ~Handler() { delete instance; }
    };
    static Handler handlerR;

    RelationManager():relations(nullptr),nbRelations(0),nbMaxRelations(0),filename(""){
        qDebug()<<"constructeur de RelationManager réussi\n";

    }
    ~RelationManager();
    RelationManager(const RelationManager& m);
   RelationManager& operator=(const RelationManager& m);


public:

    void addRelation(Relation *re);

    void addRelation(const QString& t, const QString& d, bool o=false, Couple **c=nullptr,unsigned int nbC=0,unsigned int nbM=0);
    QList<QString> getAscendents(const QString& idy);
    QList<QString> getDescendents(const QString& idx);

    Relation *getRelation(const QString& t); // return the relation avec titre t
    Relation* getRelation(unsigned int i);
    unsigned int getNbRelations(){return nbRelations;}


    void setFilename(const QString& f) { filename=f; }
    void load(); // load relation from file filename
    void save() const; // save relation in file filename

    static RelationManager& getManager();
    static void freeManager();
    class Iterator {
            friend class RelationManager;
            Relation** currentN;
            unsigned int nbRemain;
            Iterator(Relation** r, unsigned nb):currentN(r),nbRemain(nb){}
        public:
            Iterator():currentN(NULL),nbRemain(0){}
            bool isDone() const { return nbRemain==0; }
            void next() {
                if (isDone())
                    throw NotesException("error, next on an iterator which is done");
                nbRemain--;
                currentN++;
            }
           Relation& current() const {
                if (isDone())
                    throw NotesException("error, indirection on an iterator which is done");
                return **currentN;
            }
        };

        Iterator getIterator() {
            return Iterator(relations,nbRelations);
        }

};



#endif // RELATIONMANAGER_H
