#if !defined(_NOTES_H)
#define _NOTES_H
#include <QString>
#include <QDate>
#include <iostream>
#include <Qlist> // remplir tableau de pointeur???
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QtXml>
#include <QDebug>
#include <string>


using namespace std;



class NotesException{
public:
    NotesException(const QString& message):info(message){}
    const QString & getInfo() const { return info; }
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
    const QString & getEmp()const{return emplacement;}
    const QString & getId() const{return id ;}
    const QString & getTitle()const {return title; }
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
    const QString & getAction()const {return action;}
    const QString & getStatus()const {return status;}
    const QString & getPriority()const {return priorite;}
    QDate getExpDate()const{return echeance;}
    void setAction(const QString& a);
    void setStatus(const QString& s){action=s;}
    void setPriority(const QString& p){priorite=p;}
    void setExpDate(const QDate e){echeance=e;}
    int type()const {return 1;}


};



class Article : public Note{

    QString text;
public:
    Article(const QString & i,const QString & t, QDate c, QDate d,QString em,const QString& te):
        Note(i,t,c,d,em),text(te){}
    const QString & getText() const { return text; }
    void setText(const QString& t){text=t;}
    int type()const {return 2;}
};


class Image : public Note {
    QString desc;
    QString file;
   public:
    Image(const QString& i,const QString& t, QDate c, QDate d,QString em,const QString& des, const QString& f):
        Note(i,t,c,d,em),desc(des),file(f){}
    const QString & getDescpt() const {return desc;}
    const QString & getFicher() const {return file;} // la valeur de retour est de type QString ou de type Image?
    void setDesc(const QString& des){desc=des;}
    void setFile(const QString& f){file=f;}
    int type()const {return 3;}

};


 class Audio : public Image{

     QString aud_file;
    public:
     Audio(const QString& i,const QString& t, QDate c, QDate d,QString em,const QString& des, const QString& f,const QString& aud):
         Image(i,t,c,d,em,des,f),aud_file(aud){}
     const QString & getAFile() const {return aud_file;}
     void setAFile(const QString& af){aud_file=af;}
    int type()const {return 4;}
 };
 class Video : public Image{
      QString vid_file;
     public:
      Video(const QString& i,const QString& t, QDate c, QDate d,QString em,const QString& des,const QString& f,const QString& vid):
         Image(i,t,c,d,em,des,f),vid_file(vid){}
      const QString & getVFile() const {return vid_file;}
      void setVFile(const QString& vf){vid_file=vf;}
      int type()const {return 5;}


 };





class NotesManager {
private:
    QList<Note*> notes;
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


public:
  /*  Note * dern_version(QSting id)
{   QDate t(1,0,0); Note* n;
    for(NotesManager::Iterator it=nm.getIterator; it.next(); !it.isDone())
    {
        if(it.currentN->getId()==id){if(it.currentN->der_modif>t){n=it.currentN;t=it.currentN->der_modif;}
    }
    return n;
}； */
    void addTache(const QString & id,const QString & t, QDate c, QDate d,QString em,const QString& a,
                  const QString& p, QDate e,const QString& s);
    void addArticle(const QString & i,const QString & t, QDate c, QDate d,QString em,const QString& te);
    void addImage(const QString& i,const QString& t, QDate c, QDate d,QString em,const QString& des, const QString& f);
    void addAudio(const QString& i,const QString& t, QDate c, QDate d,QString em,const QString& des, const QString& f,const QString& aud);
    void addVideo(const QString& i,const QString& t, QDate c, QDate d,QString em,const QString& des, const QString& f,const QString& vid);

    Note* getNote(const QString& id); // return the article with identificator id
    bool rechercherNote(QString id);
    void setFilename(QString f) { filename=f; }
    void load(); // load notes from file filename
    void save() const; // save notes in file filename
    void addCoupleDansReference(const QString& id,QString& s);

    static NotesManager& getNoteManager();
    static void freeNoteManager(); // free the memory used by the NotesManager; it can be rebuild later

};
#endif
