#include "Notes.h"
#include <QFile>
#include <QTextCodec>
#include <QtXml>
#include <QMessageBox>



NotesManager::Handler NotesManager::handler=Handler();

NotesManager& NotesManager::getManager(){
    if (!handler.instance) handler.instance=new NotesManager;
    return *handler.instance;
}

void NotesManager::freeManager(){
    delete handler.instance;
    handler.instance=nullptr;
}

void NotesManager::addNote(Note* a){
    for(unsigned int i=0; i<nbNotes; i++){
        if (notes[i]->getId()==a->getId()) throw NotesException("error, creation of an already existent note");
    }
    if (nbNotes==nbMaxNotes){
        Note** newNotes= new Note*[nbMaxNotes+5];
        for(unsigned int i=0; i<nbNotes; i++) newNotes[i]=notes[i];
        Note** oldNotes=notes;
        notes=newNotes;
        nbMaxNotes+=5;
        if (oldNotes) delete[] oldNotes;
    }
    notes[nbNotes++]=a;
}
//utiliser template pour simplifier???
void NotesManager::addTache(const QString & id,const QString & t, Date c, Date d,const QString& a,int p, Date e,enum Status s=en_attente)
{
    for(unsigned int i=0; i<nbNotes; i++){
        if (notes[i]->getId()==id) throw NotesException("error, creation of an already existent note");
    }
    Tache* t=new Tache(id,t,c,d,a,p,e,s);
    addNote(t);
}
void NotesManager::addArticle(const QString & id,const QString & t, Date c, Date d,const QString& te)
{
    for(unsigned int i=0; i<nbNotes; i++){
        if (notes[i]->getId()==id) throw NotesException("error, creation of an already existent note");
    }
    Article* a=new Article(id,t,c,d,te);
    addNote(a);
}
void NotesManager::addImage(const QString& id,const QString& t, Date c, Date d,const QString& des, const QString& f,int i=3)
{
    for(unsigned int i=0; i<nbNotes; i++){
        if (notes[i]->getId()==id) throw NotesException("error, creation of an already existent note");
    }
    Image* im=new Image(id,t,c,d,des,f,i);
    addNote(im);
}
void NotesManager::addAudio(const QString& id,const QString& t, Date c, Date d,const QString& des, const QString& f,const QString& aud)
{
    for(unsigned int i=0; i<nbNotes; i++){
        if (notes[i]->getId()==id) throw NotesException("error, creation of an already existent note");
    }
    Audio* t=new Audio(id,t,c,d,des,f,aud);
    addNote(t);
}
void NotesManager::addVideo(const QString& id,const QString& t, Date c, Date d,const QString& d, const QString& f,const QString& vid)
{
    for(unsigned int i=0; i<nbNotes; i++){
        if (notes[i]->getId()==id) throw NotesException("error, creation of an already existent note");
    }
    Video* t=new Video(id,t,c,d,d,f,vid);
    addNote(t);
}
Note& NotesManager::getNote(const QString& id){
    // si l'Note existe d, on en renvoie une rrence
    for(unsigned int i=0; i<nbNotes; i++){
        if (Notes[i]->getId()==id) return *Notes[i];
    }

    throw NotesException("error, échoué de trouver ce note");
}

NotesManager::NotesManager():Notes(nullptr),nbNotes(0),nbMaxNotes(0),filename(""){}

NotesManager::~NotesManager(){
    if (filename!="") save();//
    for(unsigned int i=0; i<nbNotes; i++) delete Notes[i];
    delete[] Notes;
}

void NotesManager::save() const {
    QFile newfile(filename);
    if (!newfile.open(QIODevice::WriteOnly | QIODevice::Text))
        throw NotesException(QString("erreur sauvegarde notes : ouverture fichier xml"));
    QXmlStreamWriter stream(&newfile);
    stream.setAutoFormatting(true);
    stream.writeStartDocument();
    stream.writeStartElement("notes");
                        stream.writeStartElement("Article");
                        stream.writeTextElement("id",notes[i]->getId());
                        stream.writeTextElement("title",notes[i]->getTitle());
                        stream.writeTextElement("date de creation",notes[i]->getDate());
        stream.writeTextElement("text",Notes[i]->getText());
        stream.writeEndElement();

    stream.writeEndElement();
    stream.writeEndDocument();
    newfile.close();
}

void NotesManager::load() {
    QFile fin(filename);
    // If we can't open it, let's show an error message.
    if (!fin.open(QIODevice::ReadOnly | QIODevice::Text)) {
        throw NotesException("Erreur ouverture fichier notes");
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
            if(xml.name() == "Note") {
                qDebug()<<"new Note\n";
                QString identificateur;
                QString titre;
                QString text;
                QXmlStreamAttributes attributes = xml.attributes();
                xml.readNext();
                //We're going to loop over the things because the order might change.
                //We'll continue the loop until we hit an EndElement named Note.
                while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "Note")) {
                    if(xml.tokenType() == QXmlStreamReader::StartElement) {
                        // We've found identificteur.
                        if(xml.name() == "id") {
                            xml.readNext(); identificateur=xml.text().toString();
                            qDebug()<<"id="<<identificateur<<"\n";
                        }

                        // We've found titre.
                        if(xml.name() == "title") {
                            xml.readNext(); titre=xml.text().toString();
                            qDebug()<<"titre="<<titre<<"\n";
                        }
                        // We've found text
                        if(xml.name() == "text") {
                            xml.readNext();
                            text=xml.text().toString();
                            qDebug()<<"text="<<text<<"\n";
                        }
                    }
                    // ...and next...
                    xml.readNext();
                }
                qDebug()<<"ajout note "<<identificateur<<"\n";
                addNote(identificateur,titre,text);
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

