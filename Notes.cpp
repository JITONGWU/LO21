#include "Notes.h"



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
void NotesManager::addTache(const QString & id,const QString & t, QDate c, QDate d,const QString& a,int p, QDate e,enum Status s=en_attente)
{
    for(unsigned int i=0; i<nbNotes; i++){
        if (notes[i]->getId()==id) throw NotesException("error, creation of an already existent note");
    }
    Tache* t=new Tache(id,t,c,d,a,p,e,s);
    addNote(t);
}
void NotesManager::addArticle(const QString & id,const QString & t, QDate c, QDate d,const QString& te)
{
    for(unsigned int i=0; i<nbNotes; i++){
        if (notes[i]->getId()==id) throw NotesException("error, creation of an already existent note");
    }
    Article* a=new Article(id,t,c,d,te);
    addNote(a);
}
void NotesManager::addImage(const QString& id,const QString& t, QDate c, QDate d,const QString& des, const QString& f,int i=3)
{
    for(unsigned int i=0; i<nbNotes; i++){
        if (notes[i]->getId()==id) throw NotesException("error, creation of an already existent note");
    }
    Image* im=new Image(id,t,c,d,des,f,i);
    addNote(im);
}
void NotesManager::addAudio(const QString& id,const QString& t, QDate c, QDate d,const QString& des, const QString& f,const QString& aud)
{
    for(unsigned int i=0; i<nbNotes; i++){
        if (notes[i]->getId()==id) throw NotesException("error, creation of an already existent note");
    }
    Audio* t=new Audio(id,t,c,d,des,f,aud);
    addNote(t);
}
void NotesManager::addVideo(const QString& id,const QString& t, QDate c, QDate d,const QString& d, const QString& f,const QString& vid)
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
       for(unsigned int i=0; i<nbArticles; i++){
       int type=notes[i]->type();
       switch(type){
           case 2:      { stream.writeStartElement("Article");
                        stream.writeTextElement("id",notes[i]->getId());
                        stream.writeTextElement("title",notes[i]->getTitle());
                        stream.writeTextElement("date de creation",notes[i]->getDateCreat().toString(dd.MM.yyyy));
                        stream.writeTextElement("date de update",notes[i]->getDateDernier().toString(dd.MM.yyyy));
                        stream.writeTextElement("text",Notes[i]->getText());
                        stream.writeEndElement();} break;
           case 1:     {stream.writeStartElement("Tache");
                        stream.writeTextElement("id",notes[i]->getId());
                        stream.writeTextElement("title",notes[i]->getTitle());
                        stream.writeTextElement("date de creation",notes[i]->getDateCreat());
                        stream.writeTextElement("date de update",notes[i]->getDateDernier());
                        stream.writeTextElement("action",Notes[i]->getAction());
                        stream.writeTextElement("status",Notes[i]->getStatus());
                        stream.writeTextElement("priority",Notes[i]->getPriority());
                        stream.writeTextElement("echeance",Notes[i]->getExpDate().toString(dd.MM.yyyy));
                        stream.writeEndElement();}break;
           case 3:     {stream.writeStartElement("Image");
                        stream.writeTextElement("id",notes[i]->getId());
                        stream.writeTextElement("title",notes[i]->getTitle());
                        stream.writeTextElement("date de creation",notes[i]->getDateCreat().toString(dd.MM.yyyy));
                        stream.writeTextElement("date de update",notes[i]->getDateDernier().toString(dd.MM.yyyy));
                        stream.writeTextElement("descp",Notes[i]->getDescpt());
                        stream.writeTextElement("ficher",Notes[i]->getFicher());
                        stream.writeEndElement();}break;

           case 4:     {stream.writeStartElement("Audio");
                        stream.writeTextElement("id",notes[i]->getId());
                        stream.writeTextElement("title",notes[i]->getTitle());
                        stream.writeTextElement("date de creation",notes[i]->getDateCreat().toString(dd.MM.yyyy));
                        stream.writeTextElement("date de update",notes[i]->getDateDernier().toString(dd.MM.yyyy));
                        stream.writeTextElement("descp",Notes[i]->getDescpt());
                        stream.writeTextElement("ficher",Notes[i]->getFicher());
                        stream.writeTextElement("A_ficher",Notes[i]->getAFile());
                        stream.writeEndElement();}break;
           case 5:     {stream.writeStartElement("Video");
                        stream.writeTextElement("id",notes[i]->getId());
                        stream.writeTextElement("title",notes[i]->getTitle());
                        stream.writeTextElement("date de creation",notes[i]->getDateCreat().toString(dd.MM.yyyy));
                        stream.writeTextElement("date de update",notes[i]->getDateDernier().toString(dd.MM.yyyy));
                        stream.writeTextElement("descp",Notes[i]->getDescpt());
                        stream.writeTextElement("ficher",Notes[i]->getFicher());
                        stream.writeTextElement("V_ficher",Notes[i]->getVFile());
                        stream.writeEndElement();}break;




       }}
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
            if(xml.name() == "article")

            QString typename=xml.name();
            switch(typename){


            case "Article": {
                qDebug()<<"new article\n";
                QString identificateur;
                QString titre;
                QString text;
                QDate creat;
                QDate der_modif;
                QXmlStreamAttributes attributes = xml.attributes();
                xml.readNext();
                //We're going to loop over the things because the order might change.
                //We'll continue the loop until we hit an EndElement named article.
                while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "Article")) {
                    if(xml.tokenType() == QXmlStreamReader::StartElement) {
                        // We've found identificteur.
                        if(xml.name() == "id") {
                            xml.readNext(); identificateur=xml.text().toString();                            
                        }

                        // We've found titre.
                        if(xml.name() == "title") {
                            xml.readNext(); titre=xml.text().toString();                            
                        }
                        if(xml.name() == "date de creation") {
                            xml.readNext(); creat=creat.fromString(xml.text().toString(),dd.MM.yyyy);                         
                        }
                        if(xml.name() == "date de update") {
                            xml.readNext(); der_modif=der_modif.fromString(xml.text().toString(),dd.MM.yyyy);                            
                        }                      
                      if(xml.name() == "text") {
                            xml.readNext();
                            text=xml.text().toString();                            
                        }
                    }                    
                    xml.readNext();
                }
                
                addArticle(identificateur,titre,creat,der_modif,text);
            } break;
            case "Tache":{
                qDebug()<<"new article\n";
                QString identificateur;
                QString titre;                
                QDate creat;
                QDate der_modif;
                QString action;
                int priorite;
                QDate echeance;
                QString status;
                QXmlStreamAttributes attributes = xml.attributes();
                xml.readNext();
                //We're going to loop over the things because the order might change.
                //We'll continue the loop until we hit an EndElement named article.
                while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "Article")) {
                    if(xml.tokenType() == QXmlStreamReader::StartElement) {
                        // We've found identificteur.
                        if(xml.name() == "id") {
                            xml.readNext(); identificateur=xml.text().toString();                            
                        }

                        // We've found titre.
                        if(xml.name() == "title") {
                            xml.readNext(); titre=xml.text().toString();                            
                        }
                        if(xml.name() == "date de creation") {
                            xml.readNext(); creat=creat.fromString(xml.text().toString(),dd.MM.yyyy);                         
                        }
                        if(xml.name() == "date de update") {
                            xml.readNext(); der_modif=der_modif.fromString(xml.text().toString(),dd.MM.yyyy);                            
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
                            echeance=echeance.fromString(xml.text().toString(),dd.MM.yyyy);                            
                        }
                      if(xml.name() == "status") {
                            xml.readNext();
                            status=xml.text().toString();                            
                        }
                    }                    
                    xml.readNext();
                }
                
                addArticle(identificateur,titre,creat,der_modif,action,priorite,echeance,status);
            } break;
            case "Image" :{
                qDebug()<<"new article\n";
                QString identificateur;
                QString titre;
                
                QDate creat;
                QDate der_modif;
                QString desc;
                QString file;
                QXmlStreamAttributes attributes = xml.attributes();
                xml.readNext();
                //We're going to loop over the things because the order might change.
                //We'll continue the loop until we hit an EndElement named article.
                while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "Article")) {
                    if(xml.tokenType() == QXmlStreamReader::StartElement) {
                        // We've found identificteur.
                        if(xml.name() == "id") {
                            xml.readNext(); identificateur=xml.text().toString();                            
                        }

                        // We've found titre.
                        if(xml.name() == "title") {
                            xml.readNext(); titre=xml.text().toString();                            
                        }
                        if(xml.name() == "date de creation") {
                            xml.readNext(); creat=creat.fromString(xml.text().toString(),dd.MM.yyyy);                         
                        }
                        if(xml.name() == "date de update") {
                            xml.readNext(); der_modif=der_modif.fromString(xml.text().toString(),dd.MM.yyyy);                            
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
                
                addArticle(identificateur,titre,creat,der_modif,desc,file);
            } break;
            case "Audio" :{
                qDebug()<<"new article\n";
                QString identificateur;
                QString titre;
                
                QDate creat;
                QDate der_modif;
                QString desc;
                QString file;
                QString afile;
                QXmlStreamAttributes attributes = xml.attributes();
                xml.readNext();
                //We're going to loop over the things because the order might change.
                //We'll continue the loop until we hit an EndElement named article.
                while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "Article")) {
                    if(xml.tokenType() == QXmlStreamReader::StartElement) {
                        // We've found identificteur.
                        if(xml.name() == "id") {
                            xml.readNext(); identificateur=xml.text().toString();                            
                        }

                        // We've found titre.
                        if(xml.name() == "title") {
                            xml.readNext(); titre=xml.text().toString();                            
                        }
                        if(xml.name() == "date de creation") {
                            xml.readNext(); creat=creat.fromString(xml.text().toString(),dd.MM.yyyy);                         
                        }
                        if(xml.name() == "date de update") {
                            xml.readNext(); der_modif=der_modif.fromString(xml.text().toString(),dd.MM.yyyy);                            
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
                
                addArticle(identificateur,titre,creat,der_modif,desc,file,afile);
            } break;
                
            case "Video" :{
                qDebug()<<"new article\n";
                QString identificateur;
                QString titre;
                
                QDate creat;
                QDate der_modif;
                QString desc;
                QString file;
                QString vfile;
                QXmlStreamAttributes attributes = xml.attributes();
                xml.readNext();
                //We're going to loop over the things because the order might change.
                //We'll continue the loop until we hit an EndElement named article.
                while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "Article")) {
                    if(xml.tokenType() == QXmlStreamReader::StartElement) {
                        // We've found identificteur.
                        if(xml.name() == "id") {
                            xml.readNext(); identificateur=xml.text().toString();                            
                        }

                        // We've found titre.
                        if(xml.name() == "title") {
                            xml.readNext(); titre=xml.text().toString();                            
                        }
                        if(xml.name() == "date de creation") {
                            xml.readNext(); creat=creat.fromString(xml.text().toString(),dd.MM.yyyy);                         
                        }
                        if(xml.name() == "date de update") {
                            xml.readNext(); der_modif=der_modif.fromString(xml.text().toString(),dd.MM.yyyy);                            
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
                
                addArticle(identificateur,titre,creat,der_modif,desc,file,vfile);
            } break;



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
