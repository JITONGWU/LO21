#define _NOTES_H
#include <QString>
using namespace std;

class Article;
class NotesManager;

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
    Date creat;
    Date der_modf;
public:
    Note(const QString & i,const QString & t, Date c, date d):id(i),title(t),create(c),der_modf(d){}
     QString getId() const{return id ;}
    QString getTitle()const {return title; }
    Date getDateCreat() const {return creat;}
    Date getDateDernier() const {return der_modf;}
}


class Image {
    QString descpt;
    QString fichier;
   public:
    Image(const QString& i,const QString& t, Date c, Date da,const QString& d, const QString& f)Note(i,,t,c,da),descpt(d),fichier(f){}
    QString getDescpt() const {return descpt;}
    QString getFicher() const {return fichier;}

}





class Article : public Note{

    QString text;
public:
    Article(const QString& i,const QString& t, Date c, Date da,const QString& te):Note(i,,t,c,da),text(te){}
    QString getText() const { return text; }
    void setText(const QString& t);
};


class Tache : public Note {
    QString action;
    QString status;
    int priorite;
    Date echeance;
public :
    Tache(const QString& i,const QString& t, Date c, Date da,const QString & i,const QString& a,const QString s,int p, Date e):Note(i,,t,c,da),action(a),statut("en attente"),priorite(p),echeance(e){}
    QString getAction()const {return action;}   
    QString getStatus()const {return status;}
    int getPriorite()const {return priorite;}
    Date getDate_echeance()const{return echeance;}
    void setAction(const QString& s){action=s;}
    void setStatus(const QString& s){action=s;}
    void setPriorite(const int p){priorite=p;}
    void setDate(const date e){echeance=d;}
    ~Tache();

}







class NotesManager {
private:
    Note** notes;
    unsigned int nbNotes;
    unsigned int nbMaxNotes;
    void addNotes(Note* a);  //
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
    Note& getNote(const QString& id); // return the article with identificator id (create a new one if it not exists)
    QString getFilename() const { return filename; }
    void setFilename(const QString& f) { filename=f; }
    void load(); // load notes from file filename
    void save() const; // save notes in file filename
    static NotesManager& getManager();
    static void freeManager(); // free the memory used by the NotesManager; it can be rebuild later

    class Iterator {
            friend class NotesManager;
            Article** currentA;
            unsigned int nbRemain;
            Iterator(Article** a, unsigned nb):currentA(a),nbRemain(nb){}
        public:
            Iterator():currentA(nullptr),nbRemain(0){}
            bool isDone() const { return nbRemain==0; }
            void next() {
                if (isDone())
                    throw NotesException("error, next on an iterator which is done");
                nbRemain--;
                currentA++;
            }
            Article& current() const {
                if (isDone())
                    throw NotesException("error, indirection on an iterator which is done");
                return **currentA;
            }
        };
        Iterator getIterator() {
            return Iterator(articles,nbArticles);
        }

        class ConstIterator {   //non modifiable
            friend class NotesManager;
            Article** currentA;
            unsigned int nbRemain;
            ConstIterator(Article** a, unsigned nb):currentA(a),nbRemain(nb){}
        public:
            ConstIterator():nbRemain(0),currentA(0){}
            bool isDone() const { return nbRemain==0; }
            void next() {
                if (isDone())
                    throw NotesException("error, next on an iterator which is done");
                nbRemain--;
                currentA++;
            }
            const Article& current() const {
                if (isDone())
                    throw NotesException("error, indirection on an iterator which is done");
                return **currentA;
            }
        };
        ConstIterator getIterator() const {
            return ConstIterator(articles,nbArticles);
        }
};
#endif
