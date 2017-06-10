#include "notes.h"
//#include "relation.h"
#include <QFile>
NotesManager::Handler NotesManager::handler=Handler();

NotesManager& NotesManager::getManager(){
    if (!handler.instance) handler.instance=new NotesManager;
    return *handler.instance;
}

void NotesManager::freeManager(){
    delete handler.instance;
    handler.instance=NULL;
}
bool NotesManager::rechercherNote(QString id){
    for(unsigned int i=0; i<nbNotes; i++){
        if (notes[i]->getId()==id) return true;
    }
    return false;
}




/*
void NotesManager::addCoupleDansReference(const QString& id,QString& s){
    //std::cout<<"entrer dans la fonction"<<std::endl;
    // lier tous les attributs de type string

    QStringList lst=s.split("ref{",QString::SkipEmptyParts,Qt::CaseSensitive);  // majuscule  ? minuscule ?

   for(int i=1;i<lst.count();i++)
    {

        QStringList l=lst.at(i).split("}",QString::SkipEmptyParts, Qt::CaseSensitive);
        QString idy=l.at(0);
        std::cout<<rechercherNote(idy)<<std::endl;

        if(rechercherNote(idy)) {//si on trouve les notes avec id= l.at(0)

            Couple *cp=new Couple("ref"+id,&getNote(id),&getNote(idy));

            Reference::getRef().getCouples().append(cp);
    }
}
}
*/
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
    *(notes[i])=*a;
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
            actual_Version->setNbVersions(0);
            actual_Version->setEtat(ancienne);
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
            oldVersions[j]=const_cast<Note*>(actual_Version);
            *(notes[i])=*n;
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
void NotesManager::addTache(const QString & id,const QString & t, QDate c, QDate d,QString em,Etat et, int nb, const QString& a,
                            const QString& p, QDate e,const QString& s="en_attente")
{
   /* for(unsigned int i=0; i<nbNotes; i++){
        if (notes[i]->getId()==id) throw NotesException("error, creation of an already existent note");
    } */
    Tache* tache=new Tache(id,t,c,d,em,et,nb,a,p,e,s);
    if(et==ancienne) { addOldVersion(tache);}
    if(et==non_traite) {nouvelleVersion(tache);}
    if(et==actuelle) {addNote(tache);}
    QString string=id+t+a;
   // addCoupleDansReference(id,string);
}



void NotesManager::addArticle(const QString & id,const QString & t, QDate c, QDate d,QString em,Etat et,int nb,const QString& te)
{
   /* for(unsigned int i=0; i<nbNotes; i++){
        if (notes[i]->getId()==id) throw NotesException("error, creation of an already existent note");
    } */
    Article* a=new Article(id,t,c,d,em,et,nb,te);
    if(et==ancienne) { addOldVersion(a);}
    if(et==non_traite) {nouvelleVersion(a);}
    if(et==actuelle) {addNote(a);}
    QString s=id+t+te;
  //  addCoupleDansReference(id,s);
}


void NotesManager::addImage(const QString& id,const QString& t, QDate c, QDate d,QString em,Etat et,int nb,const QString& des, const QString& f)
{
  /*  for(unsigned int i=0; i<nbNotes; i++){
        if (notes[i]->getId()==id) throw NotesException("error, creation of an already existent note");
    } */
    Image* im=new Image(id,t,c,d,em,et,nb,des,f);
    if(et==ancienne) { addOldVersion(im);}
    if(et==non_traite) {nouvelleVersion(im);}
    if(et==actuelle) {addNote(im);}
    QString s=id+t+des;
}



void NotesManager::addAudio(const QString& id,const QString& t, QDate c, QDate d,QString em,Etat et,int nb,const QString& des, const QString& f,const QString& aud)
{
   /* for(unsigned int i=0; i<nbNotes; i++){
        if (notes[i]->getId()==id) throw NotesException("error, creation of an already existent note");
    } */
    Audio* audio=new Audio(id,t,c,d,em,et,nb,des,f,aud);
    if(et==ancienne) { addOldVersion(audio);}
    if(et==non_traite) {nouvelleVersion(audio);}
    if(et==actuelle) {addNote(audio);}
    QString s=id+t+des;
}


void NotesManager::addVideo(const QString& id,const QString& t, QDate c, QDate d,QString em,Etat et,int nb,const QString& des, const QString& f,const QString& vid)
{
    /* for(unsigned int i=0; i<nbNotes; i++){
        if (notes[i]->getId()==id) throw NotesException("error, creation of an already existent note");
    } */
    Video* video=new Video(id,t,c,d,em,et,nb,des,f,vid);
    if(et==ancienne) { addOldVersion(video);}
    if(et==non_traite) {nouvelleVersion(video);}
    if(et==actuelle) {addNote(video);}
    QString s=id+t+des;
}


Note& NotesManager::getNote(const QString& id){
    // si l'Note existe d, on en renvoie une rrence
    for(unsigned int i=0; i<nbNotes; i++){
        if (notes[i]->getId()==id) return *notes[i];
    }

    throw NotesException("error, ÃƒÂ©chouÃƒÂ© de trouver ce note");
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

/*
void NotesManager::addArticle(Article* a) {
Article* art = a;
art->setEtat(non_traite);
addNote(art);

//Couple rÃƒÂ©fÃƒÂ©rence?? Ãƒ  voir !

}


void NotesManager::addTache(Tache* a) {
Tache* art = a;
art->setEtat(non_traite);
addNote(art); }


void NotesManager::addAudio(Audio* a) {
Audio* art = a;
art->setEtat(non_traite);
addNote(art); }


void NotesManager::addVideo(Video* a) {
Video* art = a;
art->setEtat(non_traite);
addNote(art); }

void NotesManager::addImage(Image* a) {
Image* art = a;
art->setEtat(non_traite);
addNote(art); } */

Note* NotesManager::getNote(unsigned int i){
    if(i<nbNotes) return notes[i];
    throw NotesException("erreur: didn't find note");
}

Note* NotesManager::getOldVersion(unsigned int j){
    if(j<nbOldVersions) return oldVersions[j];
    throw NotesException("erreur: didn't find note");
}
NotesManager::NotesManager():notes(NULL),nbNotes(0),nbMaxNotes(0),nbOldVersions(0), nbMaxOldVersions(0), oldVersions(NULL), filename(""){}

NotesManager::~NotesManager(){
    if (filename!="") save();
    for(unsigned int i=0; i<nbNotes; i++) delete notes[i];
    delete[] notes;

    for(unsigned int i=0; i<nbOldVersions; i++) delete oldVersions[i];
    delete[] oldVersions;
}

void NotesManager::save() const {
    std::cout<<"entree"<<std::endl;
    QFile newfile(filename);

    if (!newfile.open(QIODevice::WriteOnly | QIODevice::Text))

        throw NotesException(QString("erreur sauvegarde notes : ouverture fichier xml"));
    QXmlStreamWriter stream(&newfile);
    stream.setAutoFormatting(true);
    stream.writeStartDocument();
    stream.writeStartElement("notes");

       for(unsigned int i=0; i<nbNotes; i++){
       int type=(notes[i])->type();

       switch(type){
           case 2:      {    std::cout<<"article"<<std::endl;


                        stream.writeStartElement("Article");
                        stream.writeTextElement("id",static_cast<Article*>(notes[i])->getId());
                        qDebug()<<"notes["<<i<<"]:"<<notes[i]->getId();
                        stream.writeTextElement("version","1");
                        stream.writeTextElement("title",static_cast<Article*>((notes[i]))->getTitle());
                        qDebug()<<"notes["<<i<<"]:"<<notes[i]->getTitle();
                        stream.writeTextElement("date_de_creation",static_cast<Article*>((notes[i]))->getDateCreat().toString("dd.MM.yyyy"));

                        stream.writeTextElement("date_de_update",static_cast<Article*>((notes[i]))->getDateDernier().toString("dd.MM.yyyy"));
                         stream.writeTextElement("enplacement",static_cast<Article*>(notes[i])->getEmp());
                        stream.writeTextElement("text",static_cast<Article*>((notes[i]))->getT());
                        stream.writeEndElement();

                    if(notes[i]->getNbVersions() > 0) {
                            qDebug()<<"notes"<<i<<"nbVersions:"<<notes[i]->getNbVersions();
                            for(unsigned int j=0; j<nbOldVersions; j++){
                                if(notes[i]->getId() == oldVersions[j]->getId()) {
                                    qDebug()<<"oldversions"<<j<<oldVersions[j]->getId();
                                    stream.writeStartElement("Article");
                                    stream.writeTextElement("id",static_cast<Article*>(oldVersions[j])->getId());
                                    stream.writeTextElement("version","0");
                                    stream.writeTextElement("title",static_cast<Article*>((oldVersions[j]))->getTitle());
                                    stream.writeTextElement("date_de_creation",static_cast<Article*>((oldVersions[j]))->getDateCreat().toString("dd.MM.yyyy"));

                                    stream.writeTextElement("date_de_update",static_cast<Article*>((oldVersions[j]))->getDateDernier().toString("dd.MM.yyyy"));
                                     stream.writeTextElement("enplacement",static_cast<Article*>(oldVersions[j])->getEmp() );
                                    stream.writeTextElement("text",static_cast<Article*>((oldVersions[j]))->getT());
                                    stream.writeEndElement();}
                            }
                        }


                        } break;


           case 1:     {

                        stream.writeStartElement("Tache");
                        stream.writeTextElement("id",static_cast<Tache*>(notes[i])->getId());
                        stream.writeTextElement("version","1");
                        stream.writeTextElement("title",static_cast<Tache*>(notes[i])->getTitle());
                        stream.writeTextElement("date_de_creation",static_cast<Tache*>(notes[i])->getDateCreat().toString("dd.MM.yyyy"));
                        stream.writeTextElement("date_de_update",static_cast<Tache*>(notes[i])->getDateDernier().toString("dd.MM.yyyy"));
                         stream.writeTextElement("enplacement",static_cast<Tache*>(notes[i])->getEmp());
                        stream.writeTextElement("action",static_cast<Tache*>(notes[i])->getAction());
                        stream.writeTextElement("status",static_cast<Tache*>(notes[i])->getStatus());
                        stream.writeTextElement("priority",static_cast<Tache*>(notes[i])->getPriority());
                        stream.writeTextElement("echeance",static_cast<Tache*>(notes[i])->getExpDate().toString("dd.MM.yyyy"));
                        stream.writeEndElement();

                        if(notes[i]->getNbVersions() > 0) {
                            for(unsigned int j=0; j<nbOldVersions; j++){
                                if(notes[i]->getId() == oldVersions[j]->getId()) {

                                    stream.writeStartElement("Tache");
                                    stream.writeTextElement("id",static_cast<Tache*>(oldVersions[j])->getId());
                                    stream.writeTextElement("version","0");
                                    stream.writeTextElement("title",static_cast<Tache*>(oldVersions[j])->getTitle());
                                    stream.writeTextElement("date_de_creation",static_cast<Tache*>(oldVersions[j])->getDateCreat().toString("dd.MM.yyyy"));
                                    stream.writeTextElement("date_de_update",static_cast<Tache*>(oldVersions[j])->getDateDernier().toString("dd.MM.yyyy"));
                                     stream.writeTextElement("enplacement",static_cast<Tache*>(oldVersions[j])->getEmp());
                                    stream.writeTextElement("action",static_cast<Tache*>(oldVersions[j])->getAction());
                                    stream.writeTextElement("status",static_cast<Tache*>(oldVersions[j])->getStatus());
                                    stream.writeTextElement("priority",static_cast<Tache*>(oldVersions[j])->getPriority());
                                    stream.writeTextElement("echeance",static_cast<Tache*>(oldVersions[j])->getExpDate().toString("dd.MM.yyyy"));
                                    stream.writeEndElement();

                                }
                            }
                        }


                }break;



           case 3:     {stream.writeStartElement("Image");
                        stream.writeTextElement("id",static_cast<Image*>(notes[i])->getId());
                        stream.writeTextElement("version","1");
                        stream.writeTextElement("title",static_cast<Image*>(notes[i])->getTitle());
                        stream.writeTextElement("date_de_creation",static_cast<Image*>(notes[i])->getDateCreat().toString("dd.MM.yyyy"));
                        stream.writeTextElement("date_de_update",static_cast<Image*>(notes[i])->getDateDernier().toString("dd.MM.yyyy"));
                        stream.writeTextElement("enplacement",static_cast<Image*>(notes[i])->getEmp());
                        stream.writeTextElement("descp",static_cast<Image*>(notes[i])->getDescpt());
                        stream.writeTextElement("ficher",static_cast<Image*>(notes[i])->getFicher());
                        stream.writeEndElement();


                        if(notes[i]->getNbVersions() > 0) {
                            for(unsigned int j=0; j<nbOldVersions; j++){
                                if(notes[i]->getId() == oldVersions[j]->getId()) {
                                    qDebug()<<"oldversions"<<j<<oldVersions[j]->getId();
                                    stream.writeStartElement("Image");
                                    stream.writeTextElement("id",static_cast<Image*>(oldVersions[j])->getId());
                                    stream.writeTextElement("version","0");
                                    stream.writeTextElement("title",static_cast<Image*>(oldVersions[j])->getTitle());
                                    stream.writeTextElement("date_de_creation",static_cast<Image*>(oldVersions[j])->getDateCreat().toString("dd.MM.yyyy"));
                                    stream.writeTextElement("date_de_update",static_cast<Image*>(oldVersions[j])->getDateDernier().toString("dd.MM.yyyy"));
                                    stream.writeTextElement("enplacement",static_cast<Image*>(oldVersions[j])->getEmp());
                                    stream.writeTextElement("descp",static_cast<Image*>(oldVersions[j])->getDescpt());
                                    stream.writeTextElement("ficher",static_cast<Image*>(oldVersions[j])->getFicher());
                                    stream.writeEndElement();

                                }
                            }
                        }




       }break;

           case 4:     { stream.writeStartElement("Audio");
                        stream.writeTextElement("id",static_cast<Audio*>(notes[i])->getId());
                        stream.writeTextElement("version","1");
                        stream.writeTextElement("title",static_cast<Audio*>(notes[i])->getTitle());
                        stream.writeTextElement("date_de_creation",static_cast<Audio*>(notes[i])->getDateCreat().toString("dd.MM.yyyy"));
                        stream.writeTextElement("date_de_update",static_cast<Audio*>(notes[i])->getDateDernier().toString("dd.MM.yyyy"));
                        stream.writeTextElement("descp",static_cast<Audio*>(notes[i])->getDescpt());
                         stream.writeTextElement("enplacement",static_cast<Video*>(notes[i])->getEmp());
                        stream.writeTextElement("ficher",static_cast<Audio*>(notes[i])->getFicher());
                        stream.writeTextElement("A_ficher",static_cast<Audio*>(notes[i])->getAFile());
                        stream.writeEndElement();

                        if(notes[i]->getNbVersions() > 0) {
                            for(unsigned int j=0; j<nbOldVersions; j++){
                                if(notes[i]->getId() == oldVersions[j]->getId()) {

                                    stream.writeStartElement("Audio");
                                    stream.writeTextElement("id",static_cast<Audio*>(oldVersions[j])->getId());
                                    stream.writeTextElement("version","0");
                                    stream.writeTextElement("title",static_cast<Audio*>(oldVersions[j])->getTitle());
                                    stream.writeTextElement("date_de_creation",static_cast<Audio*>(oldVersions[j])->getDateCreat().toString("dd.MM.yyyy"));
                                    stream.writeTextElement("date_de_update",static_cast<Audio*>(oldVersions[j])->getDateDernier().toString("dd.MM.yyyy"));
                                    stream.writeTextElement("descp",static_cast<Audio*>(oldVersions[j])->getDescpt());
                                    stream.writeTextElement("enplacement",static_cast<Video*>(oldVersions[j])->getEmp());
                                    stream.writeTextElement("ficher",static_cast<Audio*>(oldVersions[j])->getFicher());
                                    stream.writeTextElement("A_ficher",static_cast<Audio*>(oldVersions[j])->getAFile());
                                    stream.writeEndElement();

                                }
                            }
                        }


    }
           break;


           case 5:     {stream.writeStartElement("Video");
                        stream.writeTextElement("id",static_cast<Video*>(notes[i])->getId());
                        stream.writeTextElement("version","1");
                        stream.writeTextElement("title",static_cast<Video*>(notes[i])->getTitle());
                        stream.writeTextElement("date_de_creation",static_cast<Video*>(notes[i])->getDateCreat().toString("dd.MM.yyyy"));
                        stream.writeTextElement("date_de_update",static_cast<Video*>(notes[i])->getDateDernier().toString("dd.MM.yyyy"));
                        stream.writeTextElement("enplacement",static_cast<Video*>(notes[i])->getEmp());
                        stream.writeTextElement("descp",static_cast<Video*>(notes[i])->getDescpt());
                        stream.writeTextElement("ficher",static_cast<Video*>(notes[i])->getFicher());
                        stream.writeTextElement("V_ficher",static_cast<Video*>(notes[i])->getVFile());
                        stream.writeEndElement();


                        if(notes[i]->getNbVersions() > 0) {
                            for(unsigned int j=0; j<nbOldVersions; j++){
                                if(notes[i]->getId() == oldVersions[j]->getId()) {

                                    stream.writeStartElement("Video");
                                    stream.writeTextElement("id",static_cast<Video*>(oldVersions[j])->getId());
                                    stream.writeTextElement("version","0");
                                    stream.writeTextElement("title",static_cast<Video*>(oldVersions[j])->getTitle());
                                    stream.writeTextElement("date_de_creation",static_cast<Video*>(oldVersions[j])->getDateCreat().toString("dd.MM.yyyy"));
                                    stream.writeTextElement("date_de_update",static_cast<Video*>(oldVersions[j])->getDateDernier().toString("dd.MM.yyyy"));
                                    stream.writeTextElement("enplacement",static_cast<Video*>(oldVersions[j])->getEmp());
                                    stream.writeTextElement("descp",static_cast<Video*>(oldVersions[j])->getDescpt());
                                    stream.writeTextElement("ficher",static_cast<Video*>(oldVersions[j])->getFicher());
                                    stream.writeTextElement("V_ficher",static_cast<Video*>(oldVersions[j])->getVFile());
                                    stream.writeEndElement();

                                }
                            }
                        }


       }break;




       }}
    stream.writeEndElement();
    stream.writeEndDocument();
    newfile.close();
}

void NotesManager::load() {
    QFile fin(filename);
    // If we can't open it, let's show an error message.
    if (!fin.open(QIODevice::ReadOnly | QIODevice::Text)) {
        std::cout<<"Erreur ouverture fichier notes"<<std::endl;
    }
    // QXmlStreamReader takes any QIODevice.
    QXmlStreamReader xml(&fin);
    //qDebug()<<"debut fichier\n";
    // We'll parse the XML until we reach end of it.
    while(!xml.atEnd() && !xml.hasError()) {
        // Read next element.
        QXmlStreamReader::TokenType token = xml.readNext();
        // If token is just StartDocument, we'll go to next.
        if(token == QXmlStreamReader::StartDocument) continue;
        // If token is StartElement, we'll see if we can read it.
        if(token == QXmlStreamReader::StartElement) {
            // If it's named taches, we'll go to the next.
            if(xml.name() == "notes") continue;
            // If it's named tache, we'll dig the information from there.






            if(xml.name()== "Article") {

                QString identificateur;
                QString titre;
                QString version; Etat et;
                QString text;
                QDate creat;
                QDate der_modif;QString enpl;
            //    QXmlStreamAttributes attributes = xml.attributes();
                xml.readNext();
                //We're going to loop over the things because the order might change.
                //We'll continue the loop until we hit an EndElement named article.
                while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "Article")) {
                    if(xml.tokenType() == QXmlStreamReader::StartElement) {
                        // We've found identificteur.
                        if(xml.name() == "id") {
                            xml.readNext(); identificateur=xml.text().toString();
                            qDebug()<<"id="<<identificateur<<"\n";

                        }

                        if(xml.name() == "version") {
                            xml.readNext();version=xml.text().toString();
                            qDebug()<<"version="<<version<<"\n";
                            if (version=="0") {et=ancienne;}
                            else{et=actuelle;}
                        }

                        // We've found titre.
                        if(xml.name() == "title") {
                            xml.readNext(); titre=xml.text().toString();
                        }
                        if(xml.name() == "date_de_creation") {
                            xml.readNext(); creat=creat.fromString(xml.text().toString(),"dd.MM.yyyy");
                        }
                        if(xml.name() == "date_de_update") {
                            xml.readNext(); der_modif=der_modif.fromString(xml.text().toString(),"dd.MM.yyyy");
                        }
                        if(xml.name() == "emplacement") {
                            xml.readNext(); enpl=xml.text().toString();
                        }
                      if(xml.name() == "text") {
                            xml.readNext();
                            text=xml.text().toString();
                        }
                    }
                    xml.readNext();
                }

                addArticle(identificateur,titre,creat,der_modif,enpl,et,0,text);
            }
            if(xml.name()== "Tache"){

                QString identificateur;
                QString titre;
                QString version; Etat et;
                QDate creat;
                QDate der_modif;
                QString action;
                QString priorite;
                QDate echeance;
                QString status;QString enpl;
            //    QXmlStreamAttributes attributes = xml.attributes();
                xml.readNext();
                //We're going to loop over the things because the order might change.
                //We'll continue the loop until we hit an EndElement named article.
                while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "Tache")) {
                    if(xml.tokenType() == QXmlStreamReader::StartElement) {
                        // We've found identificteur.
                        if(xml.name() == "id") {
                            xml.readNext(); identificateur=xml.text().toString();
                        }

                        if(xml.name() == "version") {
                            xml.readNext();version=xml.text().toString();
                            qDebug()<<"version="<<version<<"\n";
                            if (version=="0") {et=ancienne;}
                            else{et=actuelle;}
                        }

                        // We've found titre.
                        if(xml.name() == "title") {
                            xml.readNext(); titre=xml.text().toString();
                        }
                        if(xml.name() == "date_de_creation") {
                            xml.readNext(); creat=creat.fromString(xml.text().toString(),"dd.MM.yyyy");
                        }
                        if(xml.name() == "date_de_update") {
                            xml.readNext(); der_modif=der_modif.fromString(xml.text().toString(),"dd.MM.yyyy");
                        }
                        if(xml.name() == "emplacement") {
                            xml.readNext(); enpl=xml.text().toString();
                        }
                      if(xml.name() == "action") {
                            xml.readNext();
                            action=xml.text().toString();
                        }
                      if(xml.name() == "priorite") {
                            xml.readNext();
                            priorite=xml.text().toString();
                        }
                      if(xml.name() == "echeance") {
                            xml.readNext();
                            echeance=echeance.fromString(xml.text().toString(),"dd.MM.yyyy");
                        }
                      if(xml.name() == "status") {
                            xml.readNext();
                            status=xml.text().toString();
                        }
                    }
                    xml.readNext();
                }

                addTache(identificateur,titre,creat,der_modif,enpl,et,0,action,priorite,echeance,status);
            }
            if(xml.name()== "Image" ){

                QString identificateur;
                QString titre;
                QString version; Etat et;
                QDate creat;
                QDate der_modif;
                QString desc;
                QString file;QString enpl;
            //    QXmlStreamAttributes attributes = xml.attributes();
                xml.readNext();
                //We're going to loop over the things because the order might change.
                //We'll continue the loop until we hit an EndElement named article.
                while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "Image")) {
                    if(xml.tokenType() == QXmlStreamReader::StartElement) {
                        // We've found identificteur.
                        if(xml.name() == "id") {
                            xml.readNext(); identificateur=xml.text().toString();
                        }

                        if(xml.name() == "version") {
                            xml.readNext();version=xml.text().toString();
                            qDebug()<<"version="<<version<<"\n";
                            if (version=="0") {et=ancienne;}
                            else{et=actuelle;}
                        }

                        // We've found titre.
                        if(xml.name() == "title") {
                            xml.readNext(); titre=xml.text().toString();
                        }
                        if(xml.name() == "date_de_creation") {
                            xml.readNext(); creat=creat.fromString(xml.text().toString(),"dd.MM.yyyy");
                        }
                        if(xml.name() == "date_de_update") {
                            xml.readNext(); der_modif=der_modif.fromString(xml.text().toString(),"dd.MM.yyyy");
                        }
                        if(xml.name() == "emplacement") {
                            xml.readNext(); enpl=xml.text().toString();
                        }
                      if(xml.name() == "descp") {
                            xml.readNext();
                            desc=xml.text().toString();
                        }
                      if(xml.name() == "ficher") {
                            xml.readNext();
                            file=xml.text().toString();
                        }
                    }
                    xml.readNext();
                }

                addImage(identificateur,titre,creat,der_modif,enpl,et,0,desc,file);
            }
           if(xml.name()==  "Audio" ){

                QString identificateur;
                QString titre;
                QString version; Etat et;
                QDate creat;
                QDate der_modif;
                QString desc;
                QString file;
                QString afile;QString enpl;
               // QXmlStreamAttributes attributes = xml.attributes();
                xml.readNext();
                //We're going to loop over the things because the order might change.
                //We'll continue the loop until we hit an EndElement named article.
                while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "Audio")) {
                    if(xml.tokenType() == QXmlStreamReader::StartElement) {
                        // We've found identificteur.
                        if(xml.name() == "id") {
                            xml.readNext(); identificateur=xml.text().toString();
                        }

                        if(xml.name() == "version") {
                            xml.readNext();version=xml.text().toString();
                            qDebug()<<"version="<<version<<"\n";
                            if (version=="0") {et=ancienne;}
                            else{et=actuelle;}
                        }

                        // We've found titre.
                        if(xml.name() == "title") {
                            xml.readNext(); titre=xml.text().toString();
                        }
                        if(xml.name() == "date_de_creation") {
                            xml.readNext(); creat=creat.fromString(xml.text().toString(),"dd.MM.yyyy");
                        }
                        if(xml.name() == "date_de_update") {
                            xml.readNext(); der_modif=der_modif.fromString(xml.text().toString(),"dd.MM.yyyy");
                        }
                        if(xml.name() == "emplacement") {
                            xml.readNext(); enpl=xml.text().toString();
                        }
                      if(xml.name() == "descp") {
                            xml.readNext();
                            desc=xml.text().toString();
                        }
                      if(xml.name() == "ficher") {
                            xml.readNext();
                            file=xml.text().toString();
                        }
                      if(xml.name() == "A_ficher") {
                            xml.readNext();
                            afile=xml.text().toString();
                        }
                    }
                    xml.readNext();
                }

                addAudio(identificateur,titre,creat,der_modif, enpl,et,0,desc,file,afile);
            }

            if(xml.name()=="Video" ){

                QString identificateur;
                QString titre;
                QString version; Etat et;
                QDate creat;
                QDate der_modif;
                QString desc;
                QString file;
                QString vfile;
                QString enpl;
               // QXmlStreamAttributes attributes = xml.attributes();
                xml.readNext();
                //We're going to loop over the things because the order might change.
                //We'll continue the loop until we hit an EndElement named article.
                while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "Video")) {
                    if(xml.tokenType() == QXmlStreamReader::StartElement) {
                        // We've found identificteur.
                        if(xml.name() == "id") {
                            xml.readNext(); identificateur=xml.text().toString();
                        }

                        if(xml.name() == "version") {
                            xml.readNext();version=xml.text().toString();
                            qDebug()<<"version="<<version<<"\n";
                            if (version=="0") {et=ancienne;}
                            else{et=actuelle;}
                        }

                        // We've found titre.
                        if(xml.name() == "title") {
                            xml.readNext(); titre=xml.text().toString();
                        }
                        if(xml.name() == "date_de_creation") {
                            xml.readNext(); creat=creat.fromString(xml.text().toString(),"dd.MM.yyyy");
                        }
                        if(xml.name() == "date_de_update") {
                            xml.readNext(); der_modif=der_modif.fromString(xml.text().toString(),"dd.MM.yyyy");
                        }
                        if(xml.name() == "emplacement") {
                            xml.readNext(); enpl=xml.text().toString();
                        }
                      if(xml.name() == "descp") {
                            xml.readNext();
                            desc=xml.text().toString();
                        }
                      if(xml.name() == "ficher") {
                            xml.readNext();
                            file=xml.text().toString();
                        }
                      if(xml.name() == "V_ficher") {
                            xml.readNext();
                            vfile=xml.text().toString();
                        }
                    }
                    xml.readNext();
                }

                addVideo(identificateur,titre,creat,der_modif,enpl,et,0,desc,file,vfile);
            }



            }
        }

    // Error handling.
    if(xml.hasError()) {
        throw NotesException("Erreur lecteur fichier notes, parser xml");
    }
    // Removes any device() or data from the reader * and resets its internal state to the initial state.
  xml.clear();
  qDebug()<<"fin load\n";

}
