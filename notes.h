#if !defined(_NOTES_H)
#define _NOTES_H
#include <QString>
#include <QDateTime>
#include <iostream>
#include <QList>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QtXml>
#include <QDebug>
#include <string>
#include "notemanager.h"

using namespace std;

class NotesManager;





class Note {
    QString id;
    QString title;
    QDateTime creat;
    QDateTime der_modif;
    QString emplacement;
    Etat etat;
    unsigned int nbVersions;
    friend class Suppression;

public:
    const QString & getVersion()const{if(etat==actuelle) return QString::fromStdString("1");
                                      if(etat==ancienne) return QString::fromStdString("0");}
    friend void NotesManager::archiverNoteX(QString id);
    Note(const QString & i,const QString & t, QDateTime c, QDateTime d,QString e, Etat et=non_traite, unsigned int n=0):
        id(i),title(t),creat(c),der_modif(d),emplacement(e), etat(et), nbVersions(n){}
    const QString & getEmp()const{return emplacement;}
    const QString & getId() const{return id ;}
    const QString & getTitle()const {return title; }
    QDateTime getDateCreat() const {return creat;}
    QDateTime getDateDernier() const {return der_modif;}
    void setId(const QString& i){id=i;}
     void setEmplacement(const QString& i){emplacement=i;}
    void setTitle(const QString& t){title=t;}
    void setDateCreat();//ajouter
    void setDateDerModif(const QDateTime d) {der_modif=d;}


    unsigned int getNbVersions() const {return nbVersions;}
    Etat getEtat() {return etat;}
    void setEtat(Etat et) {etat=et;}
    void setNbVersions(unsigned int i) { nbVersions = nbVersions + i;}

    virtual int type()const=0;

    virtual ~Note(){}

};




class Tache : public Note {
    QString action;
    QString priorite;
    QDateTime echeance;
    QString status;
public :

    Tache(const QString & i,const QString & t, QDateTime c, QDateTime d,QString em, Etat et, unsigned int n, const QString& a,
          const QString& p, QDateTime e,const QString& s):
        Note(i,t,c,d,em,et,n),action(a),priorite(p),echeance(e),status(s){}
    const QString & getAction()const {return action;}
    const QString & getStatus()const {return status;}
    const QString & getPriority()const {return priorite;}
    QDateTime getExpDate()const{return echeance;}
    void setAction(const QString& a){action=a;}
    void setStatus(const QString& s){status=s;}
    void setPriority(const QString& p){priorite=p;}
    void setExpDate(const QDateTime e){echeance=e;}
    int type()const {return 1;}


};



class Article : public Note{

    QString text;
public:
    Article(const QString & i,const QString & t, QDateTime c, QDateTime d,QString em, Etat et, unsigned int n, const QString& te):
        Note(i,t,c,d,em,et,n),text(te){}
    const QString & getT() const { return text; }
    void setT(const QString& te){qDebug()<<"article\n";text=te;}
    int type()const {return 2;}
};


class Image : public Note {
    QString desc;
    QString file;
   public:
    Image(const QString& i,const QString& t, QDateTime c, QDateTime d,QString em,Etat et, unsigned int n,const QString& des, const QString& f):
        Note(i,t,c,d,em,et,n),desc(des),file(f){}
    const QString & getDescpt() const {return desc;}
    const QString & getFicher() const {return file;} // la valeur de retour est de type QString ou de type Image?
    void setDesc(const QString& des){desc=des;}
    void setFile(const QString& f){file=f;}
    int type()const {return 3;}

};


 class Audio : public Image{

     QString aud_file;
    public:
     Audio(const QString& i,const QString& t, QDateTime c, QDateTime d,QString em,Etat et, unsigned int n,const QString& des, const QString& f,const QString& aud):
         Image(i,t,c,d,em,et,n,des,f),aud_file(aud){}
     const QString & getAFile() const {return aud_file;}
     void setAFile(const QString& af){aud_file=af;}
    int type()const {return 4;}
 };
 class Video : public Image{
      QString vid_file;
     public:
      Video(const QString& i,const QString& t, QDateTime c, QDateTime d,QString em,Etat et, unsigned int n,const QString& des,const QString& f,const QString& vid):
         Image(i,t,c,d,em,et,n,des,f),vid_file(vid){}
      const QString & getVFile() const {return vid_file;}
      void setVFile(const QString& vf){vid_file=vf;}
      int type()const {return 5;}


 };

#endif
