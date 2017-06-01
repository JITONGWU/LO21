#if !defined(_NOTES_H)
#define _NOTES_H
#include <QString>
#include <QDate>
#include <iostream>
#include <Qlist> // remplir tableau de pointeur???
#include <QXmlStreamWriter>
using namespace std;



class NotesException{
public:
    NotesException(const QString& message):info(message){}
    QString getInfo() const { return info; }
private:
    QString info;
};


class Note {
    QString id;
    QString title;
    QDate creat;
    QDate der_modif;
    QString emplacement;
    friend class Suppression;

public:
    Note(const QString & i,const QString & t, QDate c, QDate d,QString e):
        id(i),title(t),creat(c),der_modif(d),emplacement(e){}
    QString getEmp()const{return emplacement;}
    QString getId() const{return id ;}
    QString getTitle()const {return title; }
    QDate getDateCreat() const {return creat;}
    QDate getDateDernier() const {return der_modif;}
    void setTitle(const QString& t){title=t;}
    void setDateCreat();//ajouter
    void setDateDerModif();//modifier
    virtual int type()const=0;
    virtual ~Note(){}
};




class Tache : public Note {
    QString action;
    QString priorite;
    QDate echeance;
    QString status;
public :
    Tache(const QString & i,const QString & t, QDate c, QDate d,QString em,const QString& a,
          const QString& p, QDate e,const QString& s):
        Note(i,t,c,d,em),action(a),priorite(p),echeance(e),status(s){}
    QString getAction()const {return action;}
    QString getStatus()const {return status;}
    QString getPriority()const {return priorite;}
    QDate getExpDate()const{return echeance;}
    void setAction(const QString& s){action=s;}
    void setStatus(const QString& s){action=s;}
    void setPriority(const QString& p){priorite=p;}
    void setExpDate(const QDate e){echeance=e;}
    int type()const {return 1;}
    ~Tache();

};



class Article : public Note{

    QString text;
public:
    Article(const QString & i,const QString & t, QDate c, QDate d,QString em,const QString& te):
        Note(i,t,c,d,em),text(te){}
    QString getText() const { return text; }
    void setText(const QString& t){text=t;}
    int type()const {return 2;}
};


class Image : public Note {
    QString desc;
    QString file;
   public:
    Image(const QString& i,const QString& t, QDate c, QDate d,QString em,const QString& des, const QString& f):
        Note(i,t,c,d,em),desc(des),file(f){}
    QString getDescpt() const {return desc;}
    QString getFicher() const {return file;} // la valeur de retour est de type QString ou de type Image?
    void setDesc(const QString& des){desc=des;}
    void setFile(const QString& f){file=f;}
    int type()const {return 3;}

};


 class Audio : public Image{

     QString aud_file;
    public:
     Audio(const QString& i,const QString& t, QDate c, QDate d,QString em,const QString& des, const QString& f,const QString& aud):
         Image(i,t,c,d,em,des,f),aud_file(aud){}
     QString getAFile() const {return aud_file;}
     void setAFile(const QString& af){aud_file=af;}
    int type()const {return 4;}
 };
 class Video : public Image{
      QString vid_file;
     public:
      Video(const QString& i,const QString& t, QDate c, QDate d,QString em,const QString& des,const QString& f,const QString& vid):
         Image(i,t,c,d,em,des,f),vid_file(vid){}
      QString getVFile() const {return vid_file;}
      void setVFile(const QString& vf){vid_file=vf;}
      int type()const {return 5;}


 };





class NotesManager {
private:
    Note** notes;  //QList<Note*> notes;
    unsigned int nbNotes;
    unsigned int nbMaxNotes;
    void addNote(Note* n);  // sauvegarder version ancienne
    mutable QString filename;

    struct Handler {
        NotesManager* instance; // pointeur sur l'unique instance
        Handler():instance(nullptr){}
        ~Handler() { delete instance; }
    };
    static Handler handler;

    NotesManager();
    ~NotesManager();
    NotesManager(const NotesManager& m);
    NotesManager& operator=(const NotesManager& m);

    void addTache(const QString & id,const QString & t, QDate c, QDate d,QString em,const QString& a,
                  const QString& p, QDate e,const QString& s);
    void addArticle(const QString & i,const QString & t, QDate c, QDate d,QString em,const QString& te);
    void addImage(const QString& i,const QString& t, QDate c, QDate d,QString em,const QString& des, const QString& f);
    void addAudio(const QString& i,const QString& t, QDate c, QDate d,QString em,const QString& des, const QString& f,const QString& aud);
    void addVideo(const QString& i,const QString& t, QDate c, QDate d,QString em,const QString& des, const QString& f,const QString& vid);
public:
  /*  Note * dern_version(QSting id)
{   QDate t(1,0,0); Note* n;
    for(NotesManager::Iterator it=nm.getIterator; it.next(); !it.isDone())
    {
        if(it.currentN->getId()==id){if(it.currentN->der_modif>t){n=it.currentN;t=it.currentN->der_modif;}
    }
    return n;
}； */


    Note& getNote(const QString& id); // return the article with identificator id
    void setFilename(const QString& f) { filename=f; }
    void load(); // load notes from file filename
    void save() const; // save notes in file filename

    static NotesManager& getManager();
    static void freeManager(); // free the memory used by the NotesManager; it can be rebuild later

    class Iterator {
            friend class NotesManager;
            Note** currentN;
            unsigned int nbRemain;
            Iterator(Note** a, unsigned nb):currentN(a),nbRemain(nb){}
        public:
            Iterator():currentN(nullptr),nbRemain(0){}
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
};
#endif
