#include "relationmanager.h"

// relationManager singleton
RelationManager::Handler RelationManager::handler=Handler();

RelationManager& RelationManager::getManager(){
    if (!handler.instance) handler.instance=new RelationManager;
    return *handler.instance;
}

void RelationManager::freeManager(){
    delete handler.instance;
    handler.instance=nullptr;
}

void RelationManager::addRelation(const QString& t, const QString& d, bool o, QList<Couple *> c){
    for(unsigned int i=0;i<relations.size();i++)
        {
            if (relations.at(i)->getTitre()==t)
                throw NotesException("Erreur : creation of an already existent relation");
        }
    Relation* r=new Relation(t,d,o,&c);
    relations.append(r);
}

RelationManager::RelationManager():filename(""){
    relations.append(&Reference::getRef());// enlever apres la premiere fois
}//ajouter Référence quand on crée le relationManager

RelationManager::~RelationManager(){
    if (filename!="") save();//
    relations.clear();
}
Relation* RelationManager::getRelation(const QString& t){
    for(unsigned int i=0;i<relations.size();i++)
        if (relations.at(i)->getTitre()==t) return relations.at(i);

    throw NotesException("Erreur : didnt find relation");
}

/*
Note* RelationManager::getAscendents(Note* y){
    for(unsigned int i=0;i<nbRe; i++)
    {
        for(unsigned int j=0;j<relations[i]->getNb(); j++)

            if(getRelation(i).getCouple(j)->getY()->getId()==y->getId())
                 getRelation(i).getCouple(j)->getX();
    }
}

Note* RelationManager::getDescendents(Note* x){
    for(unsigned int i=0;i<nbRe; i++)
    {
        for(unsigned int j=0;j<relations[i]->getNb(); j++)
            if(getRelation(i).getCouple[j]->getX()->getId()==x->getId())
                return getRelation(i).getCouple[j]->getY();
    }
}
*/

void RelationManager::save() const {
    QFile newfile(filename);
    if (!newfile.open(QIODevice::WriteOnly | QIODevice::Text))
        throw NotesException(QString("erreur sauvegarde relations : ouverture fichier xml"));
    QXmlStreamWriter stream(&newfile);
    stream.setAutoFormatting(true);
    stream.writeStartDocument();
    stream.writeStartElement("Relations");
       for(unsigned int i=0;i<relations.size();i++){
                        stream.writeStartElement("Relation");
                        stream.writeTextElement("titre",relations.at(i)->getTitre());
                        stream.writeTextElement("description",relations.at(i)->getDesc());
                        if(relations.at(i)->getOrient())
                            stream.writeTextElement("oriente","true");
                        else
                            stream.writeTextElement("oriente","false");

                        for(unsigned int j=0;j<relations.at(i)->getCouples().size();i++){
                        stream.writeStartElement("couple");
                        stream.writeTextElement("label",relations.at(i)->getCouples().at(j)->getLabel());
                        stream.writeTextElement("idx",relations.at(i)->getCouples().at(j)->getX()->getId());
                        stream.writeTextElement("idy",relations.at(i)->getCouples().at(j)->getY()->getId());
                        stream.writeTextElement("etat",relations.at(i)->getCouples().at(j)->getEtat());
                        stream.writeEndElement();
                        }
                        stream.writeEndElement();}
    stream.writeEndElement();
    stream.writeEndDocument();
    newfile.close();
}

void RelationManager::load() {
    QFile fin(filename);
    // If we can't open it, let's show an error message.
    if (!fin.open(QIODevice::ReadOnly | QIODevice::Text)) {
        throw NotesException("Erreur ouverture fichier relations");
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
            if(xml.name() == "Relations") continue;
            // If it's named tache, we'll dig the information from there



            if(xml.name()== "Relation") {

                QString titre;
                QString description;
                bool orient;
                QList<Couple*> couples ;
                //QXmlStreamAttributes attributes = xml.attributes();
                xml.readNext();
                //We're going to loop over the things because the order might change.
                //We'll continue the loop until we hit an EndElement named article.

                while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "Relation")) {

                    if(xml.tokenType() == QXmlStreamReader::StartElement) {
                        // We've found titre.
                        if(xml.name() == "titre") {
                            xml.readNext(); titre=xml.text().toString();
                        }

                        // We've found description.
                        if(xml.name() == "description") {
                            xml.readNext(); description=xml.text().toString();
                        }
                        if(xml.name() == "orient "){
                            xml.readNext();
                            if(xml.text().toString()=="true") orient=1;
                            if(xml.text().toString()=="false") orient=0;
                            qDebug()<<"ajout couple \n";

                        }
                        if(xml.name() == "couple") {
                            QString idx;
                            QString idy;
                            QString label;
                            QString etat;
                            xml.readNext();
                            while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "couple")) {
                                if(xml.tokenType() == QXmlStreamReader::StartElement) {
                                            if(xml.name() == "label") {
                                            xml.readNext(); label=xml.text().toString();}
                                            if(xml.name()=="idx"){
                                                xml.readNext();idx=xml.text().toString();}
                                            if(xml.name()=="idy"){
                                                xml.readNext();idy=xml.text().toString();}
                                            if(xml.name()=='etat'){
                                                xml.readNext();etat=xml.text().toString();}
                                            qDebug()<<"ajout couple "<<label<<"\n";


                            }

                            xml.readNext();
                            }

                            Note *x= NotesManager::getNoteManager().getNote(idx);
                            Note *y = NotesManager::getNoteManager().getNote(idy);

                            Couple *newC = new Couple(label,x,y,etat);

                            couples.append(newC);

                        }
                    }
                    xml.readNext();
                }
                qDebug()<<"ajout relation "<<titre<<"\n";
               addRelation(titre,description,orient,couples);
            }

            }
        }

    // Error handling.
    if(xml.hasError()) {
        throw NotesException("Erreur lecteur fichier notes, parser xml");
    }
    // Removes any device() or data from the reader * and resets its internal state to the initial state.
    xml.clear();
    qDebug()<<"fin load relation\n";
}
