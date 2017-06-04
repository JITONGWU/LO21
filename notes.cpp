#include "Notes.h"
#include "relation.h"
#include <QFile>
NotesManager::Handler NotesManager::handler=Handler();

NotesManager& NotesManager::getManager(){
    if (!handler.instance) handler.instance=new NotesManager;
    return *handler.instance;
}

void NotesManager::freeManager(){
    delete handler.instance;
    handler.instance=nullptr;
}
bool NotesManager::rechercherNote(QString id){
    for(unsigned int i=0; i<nbNotes; i++){
        if (notes[i]->getId()==id) return true;
    }
    return false;
}

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

            Reference::getRef().addCouple(cp);
    }
}
}
void NotesManager::addNote(const Note& a){
    for(unsigned int i=0; i<nbNotes; i++){
        if (notes[i]->getId()==a.getId()) throw NotesException("error, creation of an already existent note");
    }
    if (nbNotes==nbMaxNotes){
        Note** newNotes= new Note*[nbMaxNotes+5];
        for(unsigned int i=0; i<nbNotes; i++) newNotes[i]=notes[i];
        Note** oldNotes=notes;
        notes=newNotes;
        nbMaxNotes+=5;
        if (oldNotes) delete[] oldNotes;
    }
    notes[nbNotes++]=const_cast<Note*>(&a);

}
//utiliser template pour simplifier???
void NotesManager::addTache(const QString & id,const QString & t, QDate c, QDate d,QString em,const QString& a,
                            const QString& p, QDate e,const QString& s="en_attente")
{
    for(unsigned int i=0; i<nbNotes; i++){
        if (notes[i]->getId()==id) throw NotesException("error, creation of an already existent note");
    }
    Tache* tache=new Tache(id,t,c,d,em,a,p,e,s);
    addNote(*tache);
    QString string=id+t+a;
    addCoupleDansReference(id,string);
}
void NotesManager::addArticle(const QString & id,const QString & t, QDate c, QDate d,QString em,const QString& te)
{
    for(unsigned int i=0; i<nbNotes; i++){
        if (notes[i]->getId()==id) throw NotesException("error, creation of an already existent note");
    }
    Article* a=new Article(id,t,c,d,em,te);
    addNote(*a);
    QString s=id+t+te;
    addCoupleDansReference(id,s);
}
void NotesManager::addImage(const QString& id,const QString& t, QDate c, QDate d,QString em,const QString& des, const QString& f)
{
    for(unsigned int i=0; i<nbNotes; i++){
        if (notes[i]->getId()==id) throw NotesException("error, creation of an already existent note");
    }
    Image* im=new Image(id,t,c,d,em,des,f);
    addNote(*im);
    QString s=id+t+des;
    addCoupleDansReference(id,s);
}
void NotesManager::addAudio(const QString& id,const QString& t, QDate c, QDate d,QString em,const QString& des, const QString& f,const QString& aud)
{
    for(unsigned int i=0; i<nbNotes; i++){
        if (notes[i]->getId()==id) throw NotesException("error, creation of an already existent note");
    }
    Audio* audio=new Audio(id,t,c,d,em,des,f,aud);
    addNote(*audio);
    QString s=id+t+des;
    addCoupleDansReference(id,s);
}
void NotesManager::addVideo(const QString& id,const QString& t, QDate c, QDate d,QString em,const QString& des, const QString& f,const QString& vid)
{
    for(unsigned int i=0; i<nbNotes; i++){
        if (notes[i]->getId()==id) throw NotesException("error, creation of an already existent note");
    }
    Video* video=new Video(id,t,c,d,em,des,f,vid);
    addNote(*video);
    QString s=id+t+des;
    addCoupleDansReference(id,s);
}
Note& NotesManager::getNote(const QString& id){
    // si l'Note existe d, on en renvoie une rrence
    for(unsigned int i=0; i<nbNotes; i++){
        if (notes[i]->getId()==id) return *notes[i];
    }

    throw NotesException("error, échoué de trouver ce note");
}
Note* NotesManager::getNote(unsigned int i){
    if(i<nbNotes) return notes[i];
    throw NotesException("erreur: didn't find note");
}
NotesManager::NotesManager():notes(nullptr),nbNotes(0),nbMaxNotes(0),filename(""){}

NotesManager::~NotesManager(){
    if (filename!="") save();
    for(unsigned int i=0; i<nbNotes; i++) delete notes[i];
    delete[] notes;
}

void NotesManager::save() const {
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
           case 2:      {

                        stream.writeStartElement("Article");
                        stream.writeTextElement("id",static_cast<Article*>(notes[i])->getId());
                        stream.writeTextElement("title",static_cast<Article*>((notes[i]))->getTitle());
                        stream.writeTextElement("date_de_creation",static_cast<Article*>((notes[i]))->getDateCreat().toString("dd.MM.yyyy"));

                        stream.writeTextElement("date_de_update",static_cast<Article*>((notes[i]))->getDateDernier().toString("dd.MM.yyyy"));
                         stream.writeTextElement("enplacement",static_cast<Video*>(notes[i])->getEmp());
                        stream.writeTextElement("text",static_cast<Article*>((notes[i]))->getText());
                        stream.writeEndElement();} break;
           case 1:     {stream.writeStartElement("Tache");
                        stream.writeTextElement("id",static_cast<Tache*>(notes[i])->getId());
                        stream.writeTextElement("title",static_cast<Tache*>(notes[i])->getTitle());
                        stream.writeTextElement("date_de_creation",static_cast<Tache*>(notes[i])->getDateCreat().toString("dd.MM.yyyy"));
                        stream.writeTextElement("date_de_update",static_cast<Tache*>(notes[i])->getDateDernier().toString("dd.MM.yyyy"));
                         stream.writeTextElement("enplacement",static_cast<Video*>(notes[i])->getEmp());
                        stream.writeTextElement("action",static_cast<Tache*>(notes[i])->getAction());
                        stream.writeTextElement("status",static_cast<Tache*>(notes[i])->getStatus());
                        stream.writeTextElement("priority",static_cast<Tache*>(notes[i])->getPriority());
                        stream.writeTextElement("echeance",static_cast<Tache*>(notes[i])->getExpDate().toString("dd.MM.yyyy"));
                        stream.writeEndElement();}break;
           case 3:     {stream.writeStartElement("Image");
                        stream.writeTextElement("id",static_cast<Image*>(notes[i])->getId());
                        stream.writeTextElement("title",static_cast<Image*>(notes[i])->getTitle());
                        stream.writeTextElement("date_de_creation",static_cast<Image*>(notes[i])->getDateCreat().toString("dd.MM.yyyy"));
                        stream.writeTextElement("date_de_update",static_cast<Image*>(notes[i])->getDateDernier().toString("dd.MM.yyyy"));
                        stream.writeTextElement("enplacement",static_cast<Video*>(notes[i])->getEmp());
                        stream.writeTextElement("descp",static_cast<Image*>(notes[i])->getDescpt());
                        stream.writeTextElement("ficher",static_cast<Image*>(notes[i])->getFicher());
                        stream.writeEndElement();}break;

           case 4:     {stream.writeStartElement("Audio");
                        stream.writeTextElement("id",static_cast<Audio*>(notes[i])->getId());
                        stream.writeTextElement("title",static_cast<Audio*>(notes[i])->getTitle());
                        stream.writeTextElement("date_de_creation",static_cast<Audio*>(notes[i])->getDateCreat().toString("dd.MM.yyyy"));
                        stream.writeTextElement("date_de_update",static_cast<Audio*>(notes[i])->getDateDernier().toString("dd.MM.yyyy"));
                        stream.writeTextElement("descp",static_cast<Audio*>(notes[i])->getDescpt());
                         stream.writeTextElement("enplacement",static_cast<Video*>(notes[i])->getEmp());
                        stream.writeTextElement("ficher",static_cast<Audio*>(notes[i])->getFicher());
                        stream.writeTextElement("A_ficher",static_cast<Audio*>(notes[i])->getAFile());
                        stream.writeEndElement();}break;
           case 5:     {stream.writeStartElement("Video");
                        stream.writeTextElement("id",static_cast<Video*>(notes[i])->getId());
                        stream.writeTextElement("title",static_cast<Video*>(notes[i])->getTitle());
                        stream.writeTextElement("date_de_creation",static_cast<Video*>(notes[i])->getDateCreat().toString("dd.MM.yyyy"));
                        stream.writeTextElement("date_de_update",static_cast<Video*>(notes[i])->getDateDernier().toString("dd.MM.yyyy"));
                        stream.writeTextElement("enplacement",static_cast<Video*>(notes[i])->getEmp());
                        stream.writeTextElement("descp",static_cast<Video*>(notes[i])->getDescpt());
                        stream.writeTextElement("ficher",static_cast<Video*>(notes[i])->getFicher());
                        stream.writeTextElement("V_ficher",static_cast<Video*>(notes[i])->getVFile());
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

                addArticle(identificateur,titre,creat,der_modif,enpl,text);
            } break;
            if(xml.name()== "Tache"){

                QString identificateur;
                QString titre;
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

                addTache(identificateur,titre,creat,der_modif,enpl,action,priorite,echeance,status);
            } break;
            if(xml.name()== "Image" ){

                QString identificateur;
                QString titre;

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

                addImage(identificateur,titre,creat,der_modif,enpl,desc,file);
            } break;
           if(xml.name()==  "Audio" ){

                QString identificateur;
                QString titre;

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

                addAudio(identificateur,titre,creat,der_modif, enpl,desc,file,afile);
            } break;

            if(xml.name()=="Video" ){

                QString identificateur;
                QString titre;

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

                addVideo(identificateur,titre,creat,der_modif,enpl,desc,file,vfile);
            } break;



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

