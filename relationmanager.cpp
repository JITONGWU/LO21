#include "relationmanager.h"



// relationManager singleton
RelationManager::HandlerM RelationManager::handler=HandlerM();
RelationManager& RelationManager::getManager(){
    if (!handler.RM) handler.RM=new RelationManager;
    return *handler.RM;
}
void RelationManager::freeManager(){
    delete handler.RM;
    handler.RM=nullptr;
}

void RelationManager::addRelation(const QString& t, const QString& d, bool o, Couple **c=nullptr){
    for(unsigned int i=0; i<nbRe; i++){
        if (relations[i]->getTitre()==t) throw NotesException("error, creation of an already existent relation");
    }
    Relation* r=new Relation(t,d,o,c);
    addRelation(r);
}

void RelationManager::addRelation(Relation* r){
    for(unsigned int i=0; i<nbRe; i++){
        if (relations[i]->getTitre()==r->getTitre()) throw NotesException("error, creation of an already existent relation");
    }
    if (nbRe==nbMaxRe){
        Relation** newRelations= new Relation*[nbMaxRe+5];
        for(unsigned int i=0; i<nbRe; i++) newRelations[i]=relations[i];
        Relation** old=relations;
        relations=newRelations;
        nbMaxRe+=5;
        if (old) delete[] old;
    }
   relations[nbRe++]=r;
}

RelationManager::RelationManager():relations(nullptr),nbRe(0),nbMaxRe(0),filename(""){
    addRelation(Reference::handler.reference);
}//ajouter Référence quand on crée le relationManager

RelationManager::~RelationManager(){
    if (filename!="") save();//
    for(unsigned int i=0; i<nbRe; i++) delete relations[i];
    delete[] relations;
}
Relation& RelationManager::getRelation(const QString& t){
    // si Relation existe déjà, on en renvoie une référence
    for(unsigned int i=0; i<nbRe; i++){
        if (relations[i]->getTitre()==t) return *relations[i];
    }
    // sinon il est créé
    Relation* a=new Relation(t,"",true);
    addRelation(a);
    return *a;
}
/*
void RelationManager::afficherAscendents(Note* y){
    for(unsigned int i=0;i<nbRe; i++)
    {
        for(unsigned int j=0;j<relations[i]->getNb(); j++)
            if(relations[i]->couples[j]->y==y) Couple[j]->x->afficherNote(); // ou getId();
    }
}
void RelationManager::afficherDescendents(Note* x){
    for(unsigned int i=0;i<nbRe; i++)
    {
        for(unsigned int j=0;j<relations[i]->nb; j++)
            if(relations[i]->couples[j]->x==x) Couple[j]->y->afficherNote();
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
    stream.writeStartElement("relations");
       for(unsigned int i=0; i<nbRe; i++){
                        stream.writeStartElement("Relation");
                        stream.writeTextElement("titre",(relations[i])->getTitre());
                        stream.writeTextElement("description",(relations[i])->getDesc());
                        if(relations[i]->getOrient())
                            stream.writeTextElement("oriente","true");
                        else
                            stream.writeTextElement("oriente","false");

                        for(unsigned int j=0;j<relations[i]->getNb();j++)
                        stream.writeTextElement("couples",relations[i]->getCouple(j)->getLabel());

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
            if(xml.name() == "relations") continue;
            // If it's named tache, we'll dig the information from there



            if(xml.name()== "Relation") {

                QString titre;
                QString description;
                QString orient;
                QString couples;
                QXmlStreamAttributes attributes = xml.attributes();
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
                            xml.readNext(); orient=xml.text().toString();
                        }
                        if(xml.name() == "couples") {
                            xml.readNext(); couples=xml.text().toString();
                        }

                    }
                    xml.readNext();
                }

              //  addRelation(titre,description,);
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
