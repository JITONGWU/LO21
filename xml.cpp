#include "notes.h"
#include "relation.h"
#include <QFile>

void NotesManager::save() const {
    qDebug()<<"save note begin\n";
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
                        stream.writeTextElement("corbeille","0");
                        stream.writeTextElement("id",static_cast<Article*>(notes[i])->getId());
                        stream.writeTextElement("version","1");
                        stream.writeTextElement("title",static_cast<Article*>((notes[i]))->getTitle());
                        stream.writeTextElement("date_de_creation",static_cast<Article*>((notes[i]))->getDateCreat().toString("dd.MM.yyyy  h:mm:ss AP"));

                        stream.writeTextElement("date_de_update",static_cast<Article*>((notes[i]))->getDateDernier().toString("dd.MM.yyyy  h:mm:ss AP"));
                         stream.writeTextElement("emplacement",static_cast<Article*>(notes[i])->getEmp());
                        stream.writeTextElement("text",static_cast<Article*>((notes[i]))->getT());
                        stream.writeEndElement();

                       if(notes[i]->getNbVersions() > 0) {
                            for(unsigned int j=0; j<nbOldVersions; j++){
                                if(notes[i]->getId() == oldVersions[j]->getId()) {

                                    stream.writeStartElement("Article");
                                     stream.writeTextElement("corbeille","0");
                                    stream.writeTextElement("id",static_cast<Article*>(oldVersions[j])->getId());
                                    stream.writeTextElement("version","0");
                                    stream.writeTextElement("title",static_cast<Article*>((oldVersions[j]))->getTitle());
                                    stream.writeTextElement("date_de_creation",static_cast<Article*>((oldVersions[j]))->getDateCreat().toString("dd.MM.yyyy  h:mm:ss AP"));

                                    stream.writeTextElement("date_de_update",static_cast<Article*>((oldVersions[j]))->getDateDernier().toString("dd.MM.yyyy  h:mm:ss AP"));
                                     stream.writeTextElement("emplacement",static_cast<Article*>(oldVersions[j])->getEmp() );
                                    stream.writeTextElement("text",static_cast<Article*>((oldVersions[j]))->getT());
                                    stream.writeEndElement();}
                            }
                        }

                       qDebug()<<"save ok\n";

                        } break;
           case 1:     {

                        stream.writeStartElement("Tache");
                         stream.writeTextElement("corbeille","0");
                        stream.writeTextElement("id",static_cast<Tache*>(notes[i])->getId());
                        stream.writeTextElement("version","1");
                        stream.writeTextElement("title",static_cast<Tache*>(notes[i])->getTitle());
                        stream.writeTextElement("date_de_creation",static_cast<Tache*>(notes[i])->getDateCreat().toString("dd.MM.yyyy  h:mm:ss AP"));
                        stream.writeTextElement("date_de_update",static_cast<Tache*>(notes[i])->getDateDernier().toString("dd.MM.yyyy  h:mm:ss AP"));
                         stream.writeTextElement("emplacement",static_cast<Tache*>(notes[i])->getEmp());
                        stream.writeTextElement("action",static_cast<Tache*>(notes[i])->getAction());
                        stream.writeTextElement("status",static_cast<Tache*>(notes[i])->getStatus());
                        stream.writeTextElement("priority",static_cast<Tache*>(notes[i])->getPriority());
                        stream.writeTextElement("echeance",static_cast<Tache*>(notes[i])->getExpDate().toString("dd.MM.yyyy  h:mm:ss AP"));
                        stream.writeEndElement();

                        if(notes[i]->getNbVersions() > 0) {
                            for(unsigned int j=0; j<nbOldVersions; j++){
                                if(notes[i]->getId() == oldVersions[j]->getId()) {

                                    stream.writeStartElement("Tache");
                                     stream.writeTextElement("corbeille","0");
                                    stream.writeTextElement("id",static_cast<Tache*>(oldVersions[j])->getId());
                                    stream.writeTextElement("version","0");
                                    stream.writeTextElement("title",static_cast<Tache*>(oldVersions[j])->getTitle());
                                    stream.writeTextElement("date_de_creation",static_cast<Tache*>(oldVersions[j])->getDateCreat().toString("dd.MM.yyyy  h:mm:ss AP"));
                                    stream.writeTextElement("date_de_update",static_cast<Tache*>(oldVersions[j])->getDateDernier().toString("dd.MM.yyyy  h:mm:ss AP"));
                                     stream.writeTextElement("emplacement",static_cast<Tache*>(oldVersions[j])->getEmp());
                                    stream.writeTextElement("action",static_cast<Tache*>(oldVersions[j])->getAction());
                                    stream.writeTextElement("status",static_cast<Tache*>(oldVersions[j])->getStatus());
                                    stream.writeTextElement("priority",static_cast<Tache*>(oldVersions[j])->getPriority());
                                    stream.writeTextElement("echeance",static_cast<Tache*>(oldVersions[j])->getExpDate().toString("dd.MM.yyyy  h:mm:ss AP"));
                                    stream.writeEndElement();

                                }
                            }
                        }
                }break;
           case 3:     {stream.writeStartElement("Image");
            stream.writeTextElement("corbeille","0");
                        stream.writeTextElement("id",static_cast<Image*>(notes[i])->getId());
                        stream.writeTextElement("version","1");
                        stream.writeTextElement("title",static_cast<Image*>(notes[i])->getTitle());
                        stream.writeTextElement("date_de_creation",static_cast<Image*>(notes[i])->getDateCreat().toString("dd.MM.yyyy  h:mm:ss AP"));
                        stream.writeTextElement("date_de_update",static_cast<Image*>(notes[i])->getDateDernier().toString("dd.MM.yyyy  h:mm:ss AP"));
                        stream.writeTextElement("emplacement",static_cast<Image*>(notes[i])->getEmp());
                        stream.writeTextElement("descp",static_cast<Image*>(notes[i])->getDescpt());
                        stream.writeTextElement("ficher",static_cast<Image*>(notes[i])->getFicher());
                        stream.writeEndElement();
                        if(notes[i]->getNbVersions() > 0) {
                            for(unsigned int j=0; j<nbOldVersions; j++){
                                if(notes[i]->getId() == oldVersions[j]->getId()) {

                                    stream.writeStartElement("Image");
                                     stream.writeTextElement("corbeille","0");
                                    stream.writeTextElement("id",static_cast<Image*>(oldVersions[j])->getId());
                                    stream.writeTextElement("version","0");
                                    stream.writeTextElement("title",static_cast<Image*>(oldVersions[j])->getTitle());
                                    stream.writeTextElement("date_de_creation",static_cast<Image*>(oldVersions[j])->getDateCreat().toString("dd.MM.yyyy  h:mm:ss AP"));
                                    stream.writeTextElement("date_de_update",static_cast<Image*>(oldVersions[j])->getDateDernier().toString("dd.MM.yyyy  h:mm:ss AP"));
                                    stream.writeTextElement("emplacement",static_cast<Image*>(oldVersions[j])->getEmp());
                                    stream.writeTextElement("descp",static_cast<Image*>(oldVersions[j])->getDescpt());
                                    stream.writeTextElement("ficher",static_cast<Image*>(oldVersions[j])->getFicher());
                                    stream.writeEndElement();

                                }
                            }
                        }
       }break;

           case 4:     { stream.writeStartElement("Audio");
            stream.writeTextElement("corbeille","0");
                        stream.writeTextElement("id",static_cast<Audio*>(notes[i])->getId());
                        stream.writeTextElement("version","1");
                        stream.writeTextElement("title",static_cast<Audio*>(notes[i])->getTitle());
                        stream.writeTextElement("date_de_creation",static_cast<Audio*>(notes[i])->getDateCreat().toString("dd.MM.yyyy  h:mm:ss AP"));
                        stream.writeTextElement("date_de_update",static_cast<Audio*>(notes[i])->getDateDernier().toString("dd.MM.yyyy  h:mm:ss AP"));
                        stream.writeTextElement("descp",static_cast<Audio*>(notes[i])->getDescpt());
                         stream.writeTextElement("emplacement",static_cast<Video*>(notes[i])->getEmp());
                        stream.writeTextElement("ficher",static_cast<Audio*>(notes[i])->getFicher());
                        stream.writeTextElement("A_ficher",static_cast<Audio*>(notes[i])->getAFile());
                        stream.writeEndElement();

                        if(notes[i]->getNbVersions() > 0) {
                            for(unsigned int j=0; j<nbOldVersions; j++){
                                if(notes[i]->getId() == oldVersions[j]->getId()) {

                                    stream.writeStartElement("Audio");
                                     stream.writeTextElement("corbeille","0");
                                    stream.writeTextElement("id",static_cast<Audio*>(oldVersions[j])->getId());
                                    stream.writeTextElement("version","0");
                                    stream.writeTextElement("title",static_cast<Audio*>(oldVersions[j])->getTitle());
                                    stream.writeTextElement("date_de_creation",static_cast<Audio*>(oldVersions[j])->getDateCreat().toString("dd.MM.yyyy  h:mm:ss AP"));
                                    stream.writeTextElement("date_de_update",static_cast<Audio*>(oldVersions[j])->getDateDernier().toString("dd.MM.yyyy  h:mm:ss AP"));
                                    stream.writeTextElement("descp",static_cast<Audio*>(oldVersions[j])->getDescpt());
                                    stream.writeTextElement("emplacement",static_cast<Video*>(oldVersions[j])->getEmp());
                                    stream.writeTextElement("ficher",static_cast<Audio*>(oldVersions[j])->getFicher());
                                    stream.writeTextElement("A_ficher",static_cast<Audio*>(oldVersions[j])->getAFile());
                                    stream.writeEndElement();

                                }
                            }
                        }
    }
           break;
         case 5:     {stream.writeStartElement("Video");
            stream.writeTextElement("corbeille","0");
                        stream.writeTextElement("id",static_cast<Video*>(notes[i])->getId());
                        stream.writeTextElement("version","1");
                        stream.writeTextElement("title",static_cast<Video*>(notes[i])->getTitle());
                        stream.writeTextElement("date_de_creation",static_cast<Video*>(notes[i])->getDateCreat().toString("dd.MM.yyyy  h:mm:ss AP"));
                        stream.writeTextElement("date_de_update",static_cast<Video*>(notes[i])->getDateDernier().toString("dd.MM.yyyy  h:mm:ss AP"));
                        stream.writeTextElement("emplacement",static_cast<Video*>(notes[i])->getEmp());
                        stream.writeTextElement("descp",static_cast<Video*>(notes[i])->getDescpt());
                        stream.writeTextElement("ficher",static_cast<Video*>(notes[i])->getFicher());
                        stream.writeTextElement("V_ficher",static_cast<Video*>(notes[i])->getVFile());
                        stream.writeEndElement();


                        if(notes[i]->getNbVersions() > 0) {
                            for(unsigned int j=0; j<nbOldVersions; j++){
                                if(notes[i]->getId() == oldVersions[j]->getId()) {

                                    stream.writeStartElement("Video");
                                     stream.writeTextElement("corbeille","0");
                                    stream.writeTextElement("id",static_cast<Video*>(oldVersions[j])->getId());
                                    stream.writeTextElement("version","0");
                                    stream.writeTextElement("title",static_cast<Video*>(oldVersions[j])->getTitle());
                                    stream.writeTextElement("date_de_creation",static_cast<Video*>(oldVersions[j])->getDateCreat().toString("dd.MM.yyyy  h:mm:ss AP"));
                                    stream.writeTextElement("date_de_update",static_cast<Video*>(oldVersions[j])->getDateDernier().toString("dd.MM.yyyy  h:mm:ss AP"));
                                    stream.writeTextElement("emplacement",static_cast<Video*>(oldVersions[j])->getEmp());
                                    stream.writeTextElement("descp",static_cast<Video*>(oldVersions[j])->getDescpt());
                                    stream.writeTextElement("ficher",static_cast<Video*>(oldVersions[j])->getFicher());
                                    stream.writeTextElement("V_ficher",static_cast<Video*>(oldVersions[j])->getVFile());
                                    stream.writeEndElement();

                                }
                            }
                        }
       }break;
       }}
    for(unsigned int i=0; i<nbCorbeille; i++){
    int type=(Corbeille[i])->type();
qDebug()<<"corbeille2\n";
    switch(type){
        case 2:      {
                     stream.writeStartElement("Article");
                      stream.writeTextElement("corbeille","1");
                     qDebug()<<"corbeille4\n";
                     stream.writeTextElement("id",static_cast<Article*>(Corbeille[i])->getId());
                     qDebug()<<"corbeille5\n";
                     if(Corbeille[i]->getEtat()==ancienne)
                     stream.writeTextElement("version","0");
                     else stream.writeTextElement("version","1");
                      qDebug()<<"corbeille6\n";
                     stream.writeTextElement("title",static_cast<Article*>((Corbeille[i]))->getTitle());
                     stream.writeTextElement("date_de_creation",static_cast<Article*>((Corbeille[i]))->getDateCreat().toString("dd.MM.yyyy  h:mm:ss AP"));

                     stream.writeTextElement("date_de_update",static_cast<Article*>((Corbeille[i]))->getDateDernier().toString("dd.MM.yyyy  h:mm:ss AP"));
                     stream.writeTextElement("emplacement",static_cast<Article*>(Corbeille[i])->getEmp());
                     stream.writeTextElement("text",static_cast<Article*>((Corbeille[i]))->getT());
                     stream.writeEndElement();
                    qDebug()<<"save ok corbeille\n";

                     } break;


        case 1:     {

                     stream.writeStartElement("Tache");
                      stream.writeTextElement("corbeille","1");
                     stream.writeTextElement("id",static_cast<Tache*>(Corbeille[i])->getId());
                     if(Corbeille[i]->getEtat()==ancienne)
                                     stream.writeTextElement("version","0");
                                     else stream.writeTextElement("version","1");

                     stream.writeTextElement("title",static_cast<Tache*>(Corbeille[i])->getTitle());
                     stream.writeTextElement("date_de_creation",static_cast<Tache*>(Corbeille[i])->getDateCreat().toString("dd.MM.yyyy  h:mm:ss AP"));
                     stream.writeTextElement("date_de_update",static_cast<Tache*>(Corbeille[i])->getDateDernier().toString("dd.MM.yyyy  h:mm:ss AP"));
                      stream.writeTextElement("emplacement",static_cast<Tache*>(Corbeille[i])->getEmp());
                     stream.writeTextElement("action",static_cast<Tache*>(Corbeille[i])->getAction());
                     stream.writeTextElement("status",static_cast<Tache*>(Corbeille[i])->getStatus());
                     stream.writeTextElement("priority",static_cast<Tache*>(Corbeille[i])->getPriority());
                     stream.writeTextElement("echeance",static_cast<Tache*>(Corbeille[i])->getExpDate().toString("dd.MM.yyyy  h:mm:ss AP"));
                     stream.writeEndElement();
             }break;

        case 3:     {stream.writeStartElement("Image");
                     stream.writeTextElement("corbeille","1");
                     stream.writeTextElement("id",static_cast<Image*>(Corbeille[i])->getId());
                     if(Corbeille[i]->getEtat()==ancienne)
                                     stream.writeTextElement("version","0");
                                     else stream.writeTextElement("version","1");
                     stream.writeTextElement("title",static_cast<Image*>(Corbeille[i])->getTitle());
                     stream.writeTextElement("date_de_creation",static_cast<Image*>(Corbeille[i])->getDateCreat().toString("dd.MM.yyyy  h:mm:ss AP"));
                     stream.writeTextElement("date_de_update",static_cast<Image*>(Corbeille[i])->getDateDernier().toString("dd.MM.yyyy  h:mm:ss AP"));
                     stream.writeTextElement("emplacement",static_cast<Image*>(Corbeille[i])->getEmp());
                     stream.writeTextElement("descp",static_cast<Image*>(Corbeille[i])->getDescpt());
                     stream.writeTextElement("ficher",static_cast<Image*>(Corbeille[i])->getFicher());
                     stream.writeEndElement();
    }break;

        case 4:     { stream.writeStartElement("Audio");
                      stream.writeTextElement("corbeille","1");
                     stream.writeTextElement("id",static_cast<Audio*>(Corbeille[i])->getId());
                     if(Corbeille[i]->getEtat()==ancienne)
                                     stream.writeTextElement("version","0");
                                     else stream.writeTextElement("version","1");
                     stream.writeTextElement("title",static_cast<Audio*>(Corbeille[i])->getTitle());
                     stream.writeTextElement("date_de_creation",static_cast<Audio*>(Corbeille[i])->getDateCreat().toString("dd.MM.yyyy  h:mm:ss AP"));
                     stream.writeTextElement("date_de_update",static_cast<Audio*>(Corbeille[i])->getDateDernier().toString("dd.MM.yyyy  h:mm:ss AP"));
                     stream.writeTextElement("descp",static_cast<Audio*>(Corbeille[i])->getDescpt());
                      stream.writeTextElement("emplacement",static_cast<Video*>(Corbeille[i])->getEmp());
                     stream.writeTextElement("ficher",static_cast<Audio*>(Corbeille[i])->getFicher());
                     stream.writeTextElement("A_ficher",static_cast<Audio*>(Corbeille[i])->getAFile());
                     stream.writeEndElement();
 }
        break;


        case 5:     {stream.writeStartElement("Video");
                     stream.writeTextElement("corbeille","1");
                     stream.writeTextElement("id",static_cast<Video*>(Corbeille[i])->getId());
                     if(Corbeille[i]->getEtat()==ancienne)
                                     stream.writeTextElement("version","0");
                                     else stream.writeTextElement("version","1");
                     stream.writeTextElement("title",static_cast<Video*>(Corbeille[i])->getTitle());
                     stream.writeTextElement("date_de_creation",static_cast<Video*>(Corbeille[i])->getDateCreat().toString("dd.MM.yyyy  h:mm:ss AP"));
                     stream.writeTextElement("date_de_update",static_cast<Video*>(Corbeille[i])->getDateDernier().toString("dd.MM.yyyy  h:mm:ss AP"));
                     stream.writeTextElement("emplacement",static_cast<Video*>(Corbeille[i])->getEmp());
                     stream.writeTextElement("descp",static_cast<Video*>(Corbeille[i])->getDescpt());
                     stream.writeTextElement("ficher",static_cast<Video*>(Corbeille[i])->getFicher());
                     stream.writeTextElement("V_ficher",static_cast<Video*>(Corbeille[i])->getVFile());
                     stream.writeEndElement();
    }break;

    }}
    stream.writeEndElement();
    stream.writeEndDocument();

    qDebug()<<"save note end\n";
    newfile.close();
}

void NotesManager::load() {
    QFile fin(filename);
    qDebug()<<"start load note\n";
    // If we can't open it, let's show an error message.
    if (!fin.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug()<<"Erreur ouverture fichier notes\n";
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
                QString corb;
                QString identificateur;
                QString titre;
                QString version; Etat et;
                QString text;
                QDateTime creat;
                QDateTime der_modif;QString enpl;
            //    QXmlStreamAttributes attributes = xml.attributes();
                xml.readNext();
                //We're going to loop over the things because the order might change.
                //We'll continue the loop until we hit an EndElement named article.
                while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "Article")) {
                    if(xml.tokenType() == QXmlStreamReader::StartElement) {
                        // We've found identificteur.
                        if(xml.name() == "corbeille") {
                            xml.readNext(); corb=xml.text().toString();
                        }
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
                            xml.readNext(); creat=creat.fromString(xml.text().toString(),"dd.MM.yyyy  h:mm:ss AP");
                        }
                        if(xml.name() == "date_de_update") {
                            xml.readNext(); der_modif=der_modif.fromString(xml.text().toString(),"dd.MM.yyyy  h:mm:ss AP");
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
                if(corb=="0")

                addArticle(identificateur,titre,creat,der_modif,enpl,et,0,text);
                if(corb=="1")
                {
                    Article * a=new Article(identificateur,titre,creat,der_modif,enpl,et,0,text);
                    addCorbeille(a);
                }
            }
            if(xml.name()== "Tache"){
                QString corb;
                QString identificateur;
                QString titre;
                QString version; Etat et;
                QDateTime creat;
                QDateTime der_modif;
                QString action;
                QString priorite;
                QDateTime echeance;
                QString status;QString enpl;
            //    QXmlStreamAttributes attributes = xml.attributes();
                xml.readNext();
                //We're going to loop over the things because the order might change.
                //We'll continue the loop until we hit an EndElement named article.
                while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "Tache")) {
                    if(xml.tokenType() == QXmlStreamReader::StartElement) {
                        // We've found identificteur.
                        if(xml.name() == "corbeille") {
                            xml.readNext(); corb=xml.text().toString();
                        }
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
                            xml.readNext(); creat=creat.fromString(xml.text().toString(),"dd.MM.yyyy  h:mm:ss AP");
                        }
                        if(xml.name() == "date_de_update") {
                            xml.readNext(); der_modif=der_modif.fromString(xml.text().toString(),"dd.MM.yyyy  h:mm:ss AP");
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
                            echeance=echeance.fromString(xml.text().toString(),"dd.MM.yyyy  h:mm:ss AP");
                        }
                      if(xml.name() == "status") {
                            xml.readNext();
                            status=xml.text().toString();
                        }
                    }
                    xml.readNext();
                }
                if(corb=="0")
                addTache(identificateur,titre,creat,der_modif,enpl,et,0,action,priorite,echeance,status);
                if(corb=="1")
                    {Tache * t=new Tache(identificateur,titre,creat,der_modif,enpl,et,0,action,priorite,echeance,status);addCorbeille(t);}
            }
            if(xml.name()== "Image" ){
                QString corb;
                QString identificateur;
                QString titre;
                QString version; Etat et;
                QDateTime creat;
                QDateTime der_modif;
                QString desc;
                QString file;QString enpl;
            //    QXmlStreamAttributes attributes = xml.attributes();
                xml.readNext();
                //We're going to loop over the things because the order might change.
                //We'll continue the loop until we hit an EndElement named article.
                while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "Image")) {
                    if(xml.tokenType() == QXmlStreamReader::StartElement) {
                        // We've found identificteur.
                        if(xml.name() == "corbeille") {
                            xml.readNext(); corb=xml.text().toString();
                        }
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
                            xml.readNext(); creat=creat.fromString(xml.text().toString(),"dd.MM.yyyy  h:mm:ss AP");
                        }
                        if(xml.name() == "date_de_update") {
                            xml.readNext(); der_modif=der_modif.fromString(xml.text().toString(),"dd.MM.yyyy  h:mm:ss AP");
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
                if(corb=="0")
                addImage(identificateur,titre,creat,der_modif,enpl,et,0,desc,file);
                if(corb=="1"){Image *i=new Image(identificateur,titre,creat,der_modif,enpl,et,0,desc,file); addCorbeille(i); }
            }
           if(xml.name()==  "Audio" ){
                QString corb;
                QString identificateur;
                QString titre;
                QString version; Etat et;
                QDateTime creat;
                QDateTime der_modif;
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
                        if(xml.name() == "corbeille") {
                            xml.readNext(); corb=xml.text().toString();
                        }
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
                            xml.readNext(); creat=creat.fromString(xml.text().toString(),"dd.MM.yyyy  h:mm:ss AP");
                        }
                        if(xml.name() == "date_de_update") {
                            xml.readNext(); der_modif=der_modif.fromString(xml.text().toString(),"dd.MM.yyyy  h:mm:ss AP");
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
                    if(corb=="0")
                addAudio(identificateur,titre,creat,der_modif, enpl,et,0,desc,file,afile);
                    if(corb=="1"){Audio * a=new Audio(identificateur,titre,creat,der_modif, enpl,et,0,desc,file,afile);
                 addCorbeille(a);    }
            }

            if(xml.name()=="Video" ){
                QString corb;
                QString identificateur;
                QString titre;
                QString version; Etat et;
                QDateTime creat;
                QDateTime der_modif;
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
                        if(xml.name() == "corbeille") {
                            xml.readNext(); corb=xml.text().toString();
                        }
                        if(xml.name() == "id") {
                            xml.readNext(); identificateur=xml.text().toString();
                        }

                        if(xml.name() == "version") {
                            xml.readNext();version=xml.text().toString();
                            //qDebug()<<"version="<<version<<"\n";
                            if (version=="0") {et=ancienne;}
                            else{et=actuelle;}
                        }

                        // We've found titre.
                        if(xml.name() == "title") {
                            xml.readNext(); titre=xml.text().toString();
                        }
                        if(xml.name() == "date_de_creation") {
                            xml.readNext(); creat=creat.fromString(xml.text().toString(),"dd.MM.yyyy  h:mm:ss AP");
                        }
                        if(xml.name() == "date_de_update") {
                            xml.readNext(); der_modif=der_modif.fromString(xml.text().toString(),"dd.MM.yyyy  h:mm:ss AP");
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
                if(corb=="0")
                addVideo(identificateur,titre,creat,der_modif,enpl,et,0,desc,file,vfile);
                if(corb=="1")
                {
                    Video*v=new Video(identificateur,titre,creat,der_modif,enpl,et,0,desc,file,vfile);
                    addCorbeille(v);
                }

            }



            }
        }

    // Error handling.
    if(xml.hasError()) {
        throw NotesException("Erreur lecteur fichier notes, parser xml");
    }
    // Removes any device() or data from the reader * and resets its internal state to the initial state.
  xml.clear();
  qDebug()<<"fin load note \n";

}
