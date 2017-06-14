#ifndef NOTEMANAGER_H
#define NOTEMANAGER_H
#include <QString>
#include <QDateTime>
#include <iostream>
#include <QList>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QtXml>
#include <QDebug>
#include <string>
class Note;
class Article;
class Tache;
class Image;
class Audio;
class Video;
class NotesException{
public:
    NotesException(const QString& message):info(message){}
    const QString & getInfo() const { return info; }
private:
    QString info;
};
typedef enum { actuelle, ancienne, non_traite } Etat;
class NotesManager {
private:

    Note** notes;  //QList<Note*> notes;
    unsigned int nbNotes;
    unsigned int nbMaxNotes;

    mutable QString filename;

    Note** oldVersions;
    unsigned int nbOldVersions;
    unsigned int nbMaxOldVersions;


    Note** Corbeille;
    unsigned int nbCorbeille;
    unsigned int nbMaxCorbeille;

    struct Handler {
        NotesManager* instance; // pointeur sur l'unique instance
        Handler():instance(NULL){}
        ~Handler() { delete instance; }
    };
    static Handler handler;

    NotesManager();
    ~NotesManager();
    NotesManager(const NotesManager& m);
    NotesManager& operator=(const NotesManager& m);


public:
    QList<QString> ordonnerTaches();
   static bool comparerDate(Tache& t1,Tache&t2);
    void desarchiver(QString id);
    bool IdUniqueDansNotes(QString id);
    void restaurerDeCorbeille(QString id);
    void archiverNoteX(QString id);
    void addCorbeille(const Note *);
    void supprimerNote(QString id);
    void supprimertousNotes(QString id);
    void supprimerDefinitivement(QString id);
    void addNote(const Note* n);
    void addTache(const QString & id, const QString & t, QDateTime c, QDateTime d, QString em, Etat et, int nb, const QString& a,
                  const QString& p, QDateTime e, const QString& s);
    void addArticle(const QString & i,const QString & t, QDateTime c, QDateTime d,QString em, Etat et, int nb,const QString& te);
    void addImage(const QString& i,const QString& t, QDateTime c, QDateTime d,QString em,Etat et,int nb,const QString& des, const QString& f);
    void addAudio(const QString& i,const QString& t, QDateTime c, QDateTime d,QString em,Etat et,int nb,const QString& des, const QString& f,const QString& aud);
    void addVideo(const QString& i,const QString& t, QDateTime c, QDateTime d,QString em,Etat et,int nb,const QString& des, const QString& f,const QString& vid);

    void restaurerVersionNote(Note* note, int j);

    Note* copieNote(const QString& id);
    Note* copieOldNote(unsigned int j);
    Note& getNote(const QString& id); // return the article with identificator id
    Note* getNote(unsigned int i);

    int getNb()const {return nbNotes;}
    bool rechercherNote(QString id);
    void setFilename(QString f) { filename=f; }
    void load(); // load notes from file filename
    void save() const; // save notes in file filename
    static void addCoupleDansReference(const QString& id,QString& s);
    static void supprimerCoupleDansReference(const QString& id, QString& s);

    static NotesManager& getManager();
    static void freeManager(); // free the memory used by the NotesManager; it can be rebuild later

    Note* getOldVersion(unsigned int j);
    Note &getOldVersion2(unsigned int i);
    void addOldVersion(const Note* a);
    void nouvelleVersion(Note* a);
    int getNbOldVersions()const{return nbOldVersions;}
    class Iterator {
            friend class NotesManager;
            Note** currentN;
            unsigned int nbRemain;
            Iterator(Note** a, unsigned nb):currentN(a),nbRemain(nb){}
        public:
            Iterator():currentN(NULL),nbRemain(0){}
            bool isDone() const { return nbRemain==0; }
            void next() {
                if (isDone())
                    throw NotesException("error, next on an iterator which is done");
                nbRemain--;
                currentN++;
            }
           Note& current() const {
                if (isDone())
                    throw NotesException("error, indirection on an iterator which is done");
                return **currentN;
            }
        };
        Iterator getIterator() {
            return Iterator(notes,nbNotes);
        }

        class ConstIterator {   //non modifiable
            friend class NotesManager;
           Note** currentNC;
            unsigned int nbRemain;
            ConstIterator(Note** a, unsigned nb):currentNC(a),nbRemain(nb){}
        public:
            ConstIterator():nbRemain(0),currentNC(0){}
            bool isDone() const { return nbRemain==0; }
            void next() {
                if (isDone())
                    throw NotesException("error, next on an iterator which is done");
                nbRemain--;
                currentNC++;
            }
            const Note& current() const {
                if (isDone())
                    throw NotesException("error, indirection on an iterator which is done");
                return **currentNC;
            }
        };
        ConstIterator getIterator() const {
            return ConstIterator(notes,nbNotes);
        }
        class OldIterator {
                    friend class NotesManager;
                   Note** currentNC;
                    unsigned int nbRemain;
                    OldIterator(Note** a, unsigned nb):currentNC(a),nbRemain(nb){}

                public:
                    OldIterator():nbRemain(0),currentNC(0){}
                    bool isDone() const { return nbRemain==0; }
                    void next() {
                        if (isDone())
                            throw NotesException("error, next on an iterator which is done");
                        nbRemain--;
                        currentNC++;
                    }
                    const Note& current() const {
                       if (isDone())
                           throw NotesException("error, indirection on an iterator which is done");
                       return **currentNC;
                   }
               };
                OldIterator getOldIterator() const {
                    return OldIterator(oldVersions,nbOldVersions);}


                class IteratorCorb {
                        friend class NotesManager;
                        Note** currentC;
                        unsigned int nbRemain;
                        IteratorCorb(Note** a, unsigned nb):currentC(a),nbRemain(nb){}
                    public:
                        IteratorCorb():currentC(NULL),nbRemain(0){}
                        bool isDone() const { return nbRemain==0; }
                        void next() {
                            if (isDone())
                                throw NotesException("error, next on an iterator which is done");
                            nbRemain--;
                            currentC++;
                        }
                       Note& current() const {
                            if (isDone())
                                throw NotesException("error, indirection on an iterator which is done");
                            return **currentC;
                        }
                    };
                    IteratorCorb getIteratorCorb() {
                        return IteratorCorb(Corbeille,nbCorbeille);
                    }


};
#endif // NOTEMANAGER_H
