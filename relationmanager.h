#ifndef RELATIONMANAGER_H
#define RELATIONMANAGER_H
#include "relation.h"
class RelationManager{
    //friend class Relation;

    QList<Relation*> relations;
    mutable QString filename;

    struct Handler {
        RelationManager* instance; // pointeur sur l'unique instance
        Handler():instance(nullptr){}
        ~Handler() { delete instance; }
    };
    static Handler handler;

    RelationManager();
    ~RelationManager();
    RelationManager(const RelationManager& m);
   RelationManager& operator=(const RelationManager& m);


public:
    void addRelation(const QString& t, const QString& d, bool o, QList<Couple *> c);
    Note *getAscendents(Note* y);//
    Note *getDescendenets(Note* x);//

    Relation *getRelation(const QString& t); // return the relation avec titre t

    void setFilename(const QString& f) { filename=f; }
    void load(); // load relation from file filename
    void save() const; // save relation in file filename

    static RelationManager& getManager();
    static void freeManager();


};



#endif // RELATIONMANAGER_H
