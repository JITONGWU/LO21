#include "notes.h"
#include "relation.h"
#include <QFile>
bool NotesManager::comparerDate(Tache &t1,Tache &t2){
    if(t1.getExpDate()<t2.getExpDate()) return true;
    else return false;
}
QList<QString> NotesManager::ordonnerTaches(){

    QList<QString> id_taches;
    id_taches.clear();
    QList<Tache> taches;
    taches.clear();
    for(Iterator it=getIterator();!it.isDone();it.next()){
        if (it.current().type()==1){
            Tache t= static_cast<Tache&>(it.current());
            taches.append(t);
        }
    }
    qSort(taches.begin(),taches.end(),NotesManager::comparerDate);
    for(unsigned int i=0; i<taches.size();i++){
        id_taches.append(taches.at(i).getId());
    }

    return id_taches;
}

void NotesManager::supprimerDefinitivement(QString id){
    for(int i=0;i<nbCorbeille;i++){
      if(Corbeille[i]->getId()==id){
          for(int j=i;j<nbCorbeille;j++){
              Corbeille[i]=Corbeille[i+1];
              nbCorbeille=nbCorbeille-1;
          }
      }
    }
}


void NotesManager::desarchiver(QString id){
    for(int i=0;i<nbNotes;i++)
    {
        if(notes[i]->getId()==id){
            notes[i]->setEmplacement("N");
        }
    }
}

NotesManager::NotesManager():
    notes(nullptr),nbNotes(0),nbMaxNotes(0),Corbeille(nullptr),nbCorbeille(0),nbMaxCorbeille(0),filename(""),
    oldVersions(nullptr),nbOldVersions(0),nbMaxOldVersions(0){
    qDebug()<<"constructeur de notesManager reussi\n";

}
NotesManager::~NotesManager(){
    if (filename!="") save();
    for(unsigned int i=0; i<nbNotes; i++) delete notes[i];
    delete[] notes;

    for(unsigned int j=0; j<nbOldVersions; j++) delete oldVersions[j];
    delete[] oldVersions;
    for(unsigned int j=0; j<nbCorbeille; j++) delete Corbeille[j];
    delete[] Corbeille;
    qDebug()<<"destructeur de notesManager reussi\n";

}

NotesManager::Handler NotesManager::handler=Handler();

NotesManager& NotesManager::getManager(){
    if (!handler.instance) handler.instance=new NotesManager;
    return *handler.instance;
}

void NotesManager::freeManager(){
    delete handler.instance;
    handler.instance=NULL;
}
void NotesManager::addCoupleDansReference(const QString& id,QString& s){
    NotesManager &nm = NotesManager::getManager();
    // lier tous les attributs de type string
    QStringList lst=s.split("ref{",QString::SkipEmptyParts,Qt::CaseSensitive);  // majuscule  ? minuscule ?
   for(int i=1;i<lst.count();i++)
    {
        QStringList l=lst.at(i).split("}",QString::SkipEmptyParts, Qt::CaseSensitive);
        QString idy=l.at(0);
        if(nm.rechercherNote(idy)) {//si on trouve les notes avec id= l.at(0)
            Couple *cp=new Couple("ref_"+id+"_"+idy,&nm.getNote(id),&nm.getNote(idy));
            Reference::getRef()->addCouple(cp);
    }
}
}
void NotesManager::supprimerCoupleDansReference(const QString& id,QString& s){
    NotesManager &nm = NotesManager::getManager();
    // lier tous les attributs de type string
    QStringList lst=s.split("ref{",QString::SkipEmptyParts,Qt::CaseSensitive);  // majuscule  ? minuscule ?
   for(int i=1;i<lst.count();i++)
    {
        QStringList l=lst.at(i).split("}",QString::SkipEmptyParts, Qt::CaseSensitive);
        QString idy=l.at(0);
        //std::cout<<rechercherNote(idy)<<std::endl;
        if(nm.rechercherNote(idy)) {//si on trouve les notes avec id= l.at(0)
            Couple *cp=new Couple("ref_"+id+"_"+idy,&nm.getNote(id),&nm.getNote(idy));
            Reference::getRef()->retirerCouple(cp);
    }
}
}
bool NotesManager::rechercherNote(QString id){
    for(unsigned int i=0; i<nbNotes; i++){
        if (notes[i]->getId()==id) return true;
    }
    return false;
}


bool NotesManager::IdUniqueDansNotes(QString id){
   for(unsigned int i=0;i<nbNotes;i++)
       if(notes[i]->getId()==id)return false;
   return true;
}


void NotesManager::restaurerDeCorbeille(QString id)
{   int i=0;
    while (i<nbCorbeille) {

        if(Corbeille[i]->getId()==id){

            if(Corbeille[i]->getEtat()==actuelle){
                if(IdUniqueDansNotes(id)){
                    qDebug()<<"idunique\n";
                if (nbNotes==nbMaxNotes){
                    Note** newNotes= new Note*[nbMaxNotes+5];
                    for(unsigned int i=0; i<nbNotes; i++) newNotes[i]=notes[i];
                    Note** oldNotes=notes;
                    notes=newNotes;
                    nbMaxNotes+=5;
                    if (oldNotes) delete[] oldNotes;
                   }

                notes[nbNotes++]=const_cast<Note*>(Corbeille[i]);
                 qDebug()<<"ajouter dans notes\n";
                for(unsigned int j=i;j<nbCorbeille;j++) Corbeille[j]=Corbeille[j+1];
                nbCorbeille=nbCorbeille-1;
                 qDebug()<<"retirer de corbeille\n";}

        }
            if(Corbeille[i]->getEtat()==ancienne){

                if (nbOldVersions==nbMaxOldVersions){
                    Note** newNotes= new Note*[nbMaxOldVersions+5];
                    for(unsigned int i=0; i<nbOldVersions; i++) newNotes[i]=oldVersions[i];
                    Note** oldNotes=oldVersions;
                    oldVersions=newNotes;
                    nbMaxOldVersions+=5;
                    if (oldNotes) delete[] oldNotes;
                   }

                oldVersions[nbOldVersions++]=const_cast<Note*>(Corbeille[i]);
                for(unsigned int j=i;j<nbCorbeille;j++) Corbeille[j]=Corbeille[j+1];
                 nbCorbeille=nbCorbeille-1;

            }

} else{i=i+1;}}
    return;
}


void NotesManager::archiverNoteX(QString id)
{for(unsigned int i=0;i<nbNotes;i++)
        if(notes[i]->getId()==id)
            notes[i]->setEmplacement("A");
    for(unsigned int i=0;i<nbOldVersions;i++)
            if(oldVersions[i]->getId()==id)
                oldVersions[i]->setEmplacement("A");


}
void NotesManager::addCorbeille(const Note* a){
    if (nbCorbeille==nbMaxCorbeille){
        Note** newNotes= new Note*[nbMaxCorbeille+5];
        for(unsigned int i=0; i<nbCorbeille; i++) newNotes[i]=Corbeille[i];
        Note** oldNotes=Corbeille;
        Corbeille=newNotes;
        nbMaxCorbeille+=5;
        if (oldNotes) delete[] oldNotes;
       }

    Corbeille[nbCorbeille++]=const_cast<Note*>(a);
     qDebug()<<"addCorbeille reussi\n";
}


void NotesManager::supprimerNote(QString id)
{
    for(unsigned int i=0;i<nbNotes;i++)
    {
        if(notes[i]->getId()==id){
            Note * mid;
            mid=notes[i];
            addCorbeille(mid);
            for(unsigned int j=i;j<nbNotes-1;j++){
                notes[j]=notes[j+1];
                }
            nbNotes=nbNotes-1;
        }
    }
    return;
}

void NotesManager::supprimertousNotes(QString id){
    int i=0;
   supprimerNote(id);
   while(i<nbOldVersions)
   {
       qDebug()<<"oldversions corbeille"<<oldVersions[i]->getTitle();

       if(oldVersions[i]->getId()==id){
           Note * mid;
           mid=oldVersions[i];
           addCorbeille(mid);
           for(unsigned int j=i;j<nbOldVersions-1;j++){
               oldVersions[j]=oldVersions[j+1];

           }
            nbOldVersions=nbOldVersions-1;

       }
       else{i=i+1;}
   }
   return;
}

void NotesManager::addOldVersion(const Note* a) {

    if (nbOldVersions==nbMaxOldVersions){
        Note** newNotes= new Note*[nbMaxOldVersions+5];
        for(unsigned int i=0; i<nbOldVersions; i++) newNotes[i]=oldVersions[i];
        Note** oldNotes=oldVersions;
        oldVersions=newNotes;
        nbMaxOldVersions+=5;
        if (oldNotes) delete[] oldNotes;
       }

    oldVersions[nbOldVersions++]=const_cast<Note*>(a); //On ajoute tmp dans oldVersions

    Note* update_Version = &getNote(a->getId());
    update_Version->setNbVersions(1);

    return;


}


void NotesManager::nouvelleVersion(Note* a) { //si on ÃƒÂ©dite une nouvelle version d'un article, on la met dans notes[i]
// et on met l'ancienne version dans oldVersions

    for(unsigned int i=0;i<nbNotes;i++) {

        if(notes[i]->getId() == a->getId()) {

    Note* actual_Version = copieNote(a->getId());

    a->setEtat(actuelle);
    a->setNbVersions(actual_Version->getNbVersions()+1);
    notes[i]=a;
    qDebug()<<"notes"<<i<<notes[i]->getTitle();

    actual_Version->setNbVersions(0);
    actual_Version->setEtat(ancienne);

    if (nbOldVersions==nbMaxOldVersions){
        Note** newNotes= new Note*[nbMaxOldVersions+5];
        for(unsigned int i=0; i<nbOldVersions; i++) newNotes[i]=oldVersions[i];
        Note** oldNotes=oldVersions;
        oldVersions=newNotes;
        nbMaxOldVersions+=5;
        if (oldNotes) delete[] oldNotes;
    }

     oldVersions[nbOldVersions++]=const_cast<Note*>(actual_Version);
    qDebug()<<"oldVersions[0]"<<oldVersions[0]->getTitle();
    if(nbOldVersions>1) { qDebug()<<"oldVersions[1]"<<oldVersions[1]->getTitle();}
    if(nbOldVersions>2) { qDebug()<<"oldVersions[2]"<<oldVersions[2]->getTitle();}

     return;
    }
        }

    addNote(const_cast<Note*>(a));
}
void NotesManager::restaurerVersionNote(Note* n, int j) { //n est une note de oldversions[j] accessible par l'interface
    for(unsigned int i=0; i<nbNotes; i++) {
        if(notes[i]->getId()==n->getId()) {

            Note* actual_Version = copieNote(notes[i]->getId());
            qDebug()<<actual_Version->type();
            qDebug()<<static_cast<Article*>(actual_Version)->getT();
            actual_Version->setNbVersions(0);
            actual_Version->setEtat(ancienne);

            qDebug()<<static_cast<Article*>(n)->getT();
            n->setNbVersions(notes[i]->getNbVersions());
            n->setEtat(actuelle);

            if (nbOldVersions==nbMaxOldVersions){
                Note** newNotes= new Note*[nbMaxOldVersions+5];
                for(unsigned int i=0; i<nbNotes; i++) newNotes[i]=oldVersions[i];
                Note** oldNotes=oldVersions;
                oldVersions=newNotes;
                nbMaxOldVersions+=5;
                if (oldNotes) delete[] oldNotes;
            }
            oldVersions[j]=actual_Version;
            qDebug()<<static_cast<Article*>(oldVersions[j])->getT();
           // *(notes[i])=*n;
            notes[i]=n;
            qDebug()<<static_cast<Article*>(n)->getT();
            qDebug()<<static_cast<Article*>(notes[i])->getT();

        }
    }
}

void NotesManager::addNote(const Note* a){


    if (nbNotes==nbMaxNotes){
        Note** newNotes= new Note*[nbMaxNotes+5];
        for(unsigned int i=0; i<nbNotes; i++) newNotes[i]=notes[i];
        Note** oldNotes=notes;
        notes=newNotes;
        nbMaxNotes+=5;
        if (oldNotes) delete[] oldNotes;
    }
    notes[nbNotes++]=const_cast<Note*>(a);

}

//utiliser template pour simplifier???
void NotesManager::addTache(const QString & id,const QString & t, QDateTime c, QDateTime d,QString em,Etat et, int nb, const QString& a,
                            const QString& p, QDateTime e,const QString& s="en_attente")
{
   /* for(unsigned int i=0; i<nbNotes; i++){
        if (notes[i]->getId()==id) throw NotesException("error, creation of an already existent note");
    } */
    Tache* tache=new Tache(id,t,c,d,em,et,nb,a,p,e,s);
    if(et==ancienne) { addOldVersion(tache);}
    if(et==non_traite) {nouvelleVersion(tache);}
    if(et==actuelle) {addNote(tache);}

}

void NotesManager::addArticle(const QString & id,const QString & t, QDateTime c, QDateTime d,QString em,Etat et,int nb,const QString& te)
{
   /* for(unsigned int i=0; i<nbNotes; i++){
        if (notes[i]->getId()==id) throw NotesException("error, creation of an already existent note");
    } */
    Article* a=new Article(id,t,c,d,em,et,nb,te);
    if(et==ancienne) { addOldVersion(a);}
    if(et==non_traite) {nouvelleVersion(a);}
    if(et==actuelle) {addNote(a);}

}

void NotesManager::addImage(const QString& id,const QString& t, QDateTime c, QDateTime d,QString em,Etat et,int nb,const QString& des, const QString& f)
{
  /*  for(unsigned int i=0; i<nbNotes; i++){
        if (notes[i]->getId()==id) throw NotesException("error, creation of an already existent note");
    } */
    Image* im=new Image(id,t,c,d,em,et,nb,des,f);
    if(et==ancienne) { addOldVersion(im);}
    if(et==non_traite) {nouvelleVersion(im);}
    if(et==actuelle) {addNote(im);}

}

void NotesManager::addAudio(const QString& id,const QString& t, QDateTime c, QDateTime d,QString em,Etat et,int nb,const QString& des, const QString& f,const QString& aud)
{
   /* for(unsigned int i=0; i<nbNotes; i++){
        if (notes[i]->getId()==id) throw NotesException("error, creation of an already existent note");
    } */
    Audio* audio=new Audio(id,t,c,d,em,et,nb,des,f,aud);
    if(et==ancienne) { addOldVersion(audio);}
    if(et==non_traite) {nouvelleVersion(audio);}
    if(et==actuelle) {addNote(audio);}

}

void NotesManager::addVideo(const QString& id,const QString& t, QDateTime c, QDateTime d,QString em,Etat et,int nb,const QString& des, const QString& f,const QString& vid)
{
    /* for(unsigned int i=0; i<nbNotes; i++){
        if (notes[i]->getId()==id) throw NotesException("error, creation of an already existent note");
    } */
    Video* video=new Video(id,t,c,d,em,et,nb,des,f,vid);
    if(et==ancienne) { addOldVersion(video);}
    if(et==non_traite) {nouvelleVersion(video);}
    if(et==actuelle) {addNote(video);}
  }

Note &NotesManager::getNote(const QString& id){
    // si l'Note existe d, on en renvoie une rrence
    for(unsigned int i=0; i<nbNotes; i++){
        if (notes[i]->getId()==id) return *notes[i];
    }

    throw NotesException("error, Ã©chouÃ© de trouver ce note");
}

Note &NotesManager::getOldVersion2(unsigned int i){
    if(i<nbOldVersions) return *oldVersions[i];
    throw NotesException("erreur: didn't find note");
}

Note* NotesManager::copieNote(const QString& id){
    // si l'Note existe d, on en renvoie une rrence

    for(unsigned int i=0; i<nbNotes; i++){
        if (notes[i]->getId()==id) {

          switch(notes[i]->type()) {
          case 2:{
              Article* tmp=new Article(notes[i]->getId(), notes[i]->getTitle(), notes[i]->getDateCreat(), notes[i]->getDateDernier(),
                                       notes[i]->getEmp(), notes[i]->getEtat(),notes[i]->getNbVersions(), static_cast<Article*>(notes[i])->getT());
              return tmp;

          }break;
          case 1:{
              Tache* tmp=new Tache(notes[i]->getId(), notes[i]->getTitle(), notes[i]->getDateCreat(), notes[i]->getDateDernier(),
                                       notes[i]->getEmp(), notes[i]->getEtat(),notes[i]->getNbVersions(), static_cast<Tache*>(notes[i])->getAction(),
                                   static_cast<Tache*>(notes[i])->getPriority(), static_cast<Tache*>(notes[i])->getExpDate(), static_cast<Tache*>(notes[i])->getStatus());
              return tmp;

          }break;

          case 3:{
              Image* tmp=new Image(notes[i]->getId(), notes[i]->getTitle(), notes[i]->getDateCreat(), notes[i]->getDateDernier(),
                                       notes[i]->getEmp(), notes[i]->getEtat(),notes[i]->getNbVersions(), static_cast<Image*>(notes[i])->getDescpt(),
                                        static_cast<Image*>(notes[i])->getFicher());
              return tmp;

          }break;

          case 4:{
              Audio* tmp=new Audio(notes[i]->getId(), notes[i]->getTitle(), notes[i]->getDateCreat(), notes[i]->getDateDernier(),
                                       notes[i]->getEmp(), notes[i]->getEtat(),notes[i]->getNbVersions(), static_cast<Audio*>(notes[i])->getDescpt(),
                                        static_cast<Audio*>(notes[i])->getFicher(),static_cast<Audio*>(notes[i])->getAFile());
              return tmp;

          }break;

          case 5:{
              Video* tmp=new Video(notes[i]->getId(), notes[i]->getTitle(), notes[i]->getDateCreat(), notes[i]->getDateDernier(),
                                       notes[i]->getEmp(), notes[i]->getEtat(),notes[i]->getNbVersions(), static_cast<Video*>(notes[i])->getDescpt(),
                                        static_cast<Video*>(notes[i])->getFicher(),static_cast<Video*>(notes[i])->getVFile());
              return tmp;

          }break;

           default: qDebug()<<"default"; break;
          }

    }
}
    return NULL;
}

Note* NotesManager::copieOldNote(unsigned int j) {


     if (oldVersions[j]==NULL) { throw NotesException("error, impossible de trouver cette note");}
     switch(oldVersions[j]->type()) {
           case 2:{
               Article* tmp=new Article(oldVersions[j]->getId(), oldVersions[j]->getTitle(), oldVersions[j]->getDateCreat(), oldVersions[j]->getDateDernier(),
                                        oldVersions[j]->getEmp(), oldVersions[j]->getEtat(),oldVersions[j]->getNbVersions(), static_cast<Article*>(oldVersions[j])->getT());
               return tmp;

           }break;
           case 1:{
               Tache* tmp=new Tache(oldVersions[j]->getId(), oldVersions[j]->getTitle(), oldVersions[j]->getDateCreat(), oldVersions[j]->getDateDernier(),
                                        oldVersions[j]->getEmp(), oldVersions[j]->getEtat(),oldVersions[j]->getNbVersions(), static_cast<Tache*>(oldVersions[j])->getAction(),
                                    static_cast<Tache*>(oldVersions[j])->getPriority(), static_cast<Tache*>(oldVersions[j])->getExpDate(), static_cast<Tache*>(oldVersions[j])->getStatus());
               return tmp;

           }break;

           case 3:{
               Image* tmp=new Image(oldVersions[j]->getId(), oldVersions[j]->getTitle(), oldVersions[j]->getDateCreat(), oldVersions[j]->getDateDernier(),
                                        oldVersions[j]->getEmp(), oldVersions[j]->getEtat(),oldVersions[j]->getNbVersions(), static_cast<Image*>(oldVersions[j])->getDescpt(),
                                         static_cast<Image*>(oldVersions[j])->getFicher());
               return tmp;

           }break;

           case 4:{
               Audio* tmp=new Audio(oldVersions[j]->getId(), oldVersions[j]->getTitle(), oldVersions[j]->getDateCreat(), oldVersions[j]->getDateDernier(),
                                        oldVersions[j]->getEmp(), oldVersions[j]->getEtat(),oldVersions[j]->getNbVersions(), static_cast<Audio*>(oldVersions[j])->getDescpt(),
                                         static_cast<Audio*>(oldVersions[j])->getFicher(),static_cast<Audio*>(oldVersions[j])->getAFile());
               return tmp;

           }break;

           case 5:{
               Video* tmp=new Video(oldVersions[j]->getId(), oldVersions[j]->getTitle(), oldVersions[j]->getDateCreat(), oldVersions[j]->getDateDernier(),
                                        oldVersions[j]->getEmp(), oldVersions[j]->getEtat(),oldVersions[j]->getNbVersions(), static_cast<Video*>(oldVersions[j])->getDescpt(),
                                         static_cast<Video*>(oldVersions[j])->getFicher(),static_cast<Video*>(oldVersions[j])->getVFile());
               return tmp;

           }break;

            default: qDebug()<<"default"; break;
           }

     }

Note* NotesManager::getNote(unsigned int i){
    if(i<nbNotes) return notes[i];
    throw NotesException("erreur: didn't find note!!");
}
Note* NotesManager::getOldVersion(unsigned int j){
    if(j<nbOldVersions) return oldVersions[j];
    throw NotesException("erreur: didn't find note");
}

