
#include "relation.h"
// relationManager singleton

void RelationManager::restaurerLesCoupleContenantNoteX(QString id){
 qDebug()<<"0\n";
if(nbRelations==0) { qDebug()<<"0.5\n"; return;}
 qDebug()<<"1\n";
    for(unsigned int i=0;i<nbRelations;i++){
         qDebug()<<"2\n";
        for(unsigned int j=0;j<relations[i]->getNbCouples();j++)
        {
            if(relations[i]->couples[j]->getX()->getId()==id||relations[i]->couples[j]->getY()->getId()==id)
                relations[i]->couples[j]->setEtat("N");
 qDebug()<<"3\n";
        }
    } qDebug()<<"4\n";
     return ;

}

void RelationManager::supprimerLesCoupleContenantNoteX(QString id){
    if(nbRelations==0) return;

    for(unsigned int i=0;i<nbRelations;i++){
        for(unsigned int j=0;j<relations[i]->getNbCouples();j++)
        {
            if(relations[i]->couples[j]->getX()->getId()==id||relations[i]->couples[j]->getY()->getId()==id)
                relations[i]->couples[j]->setEtat("C");
        }
    }


}

void RelationManager::archiverLesCoupleContenantNoteX(QString id){
    if(nbRelations==0) return;

    for(unsigned int i=0;i<nbRelations;i++){
        for(unsigned int j=0;j<relations[i]->getNbCouples();j++)
        {
            if(relations[i]->couples[j]->getX()->getId()==id||relations[i]->couples[j]->getY()->getId()==id)
                relations[i]->couples[j]->setEtat("A");
        }
    }
}

RelationManager::Handler RelationManager::handlerR=Handler();

RelationManager& RelationManager::getManager(){
    if (!handlerR.instance) handlerR.instance=new RelationManager;
    return *handlerR.instance;
}

void RelationManager::freeManager(){
    delete handlerR.instance;
    handlerR.instance=nullptr;
}

void RelationManager::addRelation(Relation *re){

    if (nbRelations==nbMaxRelations){
        Relation** newRelations= new Relation*[nbMaxRelations+5];
        for(unsigned int i=0; i<nbRelations; i++) newRelations[i]=relations[i];
        Relation** oldRelations=relations;
        relations=newRelations;
        nbMaxRelations+=5;
        if (oldRelations) delete[] oldRelations;
    }
    relations[nbRelations++]=const_cast<Relation*>(re);
}

void RelationManager::addRelation(const QString& t, const QString& d, bool o, Couple** c, unsigned int nbC, unsigned int nbM){



    for(unsigned int i=0;i<nbRelations;i++)
        {
            if (relations[i]->getTitre()==t)
                throw NotesException("Erreur : creation of an already existent relation");
        }
    Relation* r=new Relation(t,d,o,c,nbC,nbM);
    addRelation(r);


}

void RelationManager::supprimerRelation(unsigned int i){
   for(unsigned int j=i;j<nbRelations;j++)
       relations[j]=relations[j+1];
               nbRelations=nbRelations-1;
}


RelationManager::~RelationManager(){
    if (filename!="") save();
    for(unsigned int i=0;i<nbRelations;i++) delete relations[i];
    delete[] relations;
    qDebug()<<"destructeur de RelationManager réussi\n";

}

Relation* RelationManager::getRelation(const QString& t){
    for(unsigned int i=0;i<nbRelations;i++)
        if (relations[i]->getTitre()==t) return relations[i];

    throw NotesException("Erreur : didnt find relation");
}
Relation* RelationManager::getRelation(unsigned int i){

        if (i<nbRelations) return relations[i];

    else throw NotesException("Erreur : didnt find relation");
}

QList<QString> RelationManager::getAscendents(const QString& idy){
    QList<QString> listAscendents;
    for(RelationManager::Iterator it=getIterator();!it.isDone();it.next())
    {
        for(unsigned int i=0;i<it.current().getNbCouples(); i++)
            if(it.current().getCoupleParIndice(i)->getY()->getId()==idy)
                 listAscendents.append(it.current().getCoupleParIndice(i)->getX()->getId());
    }
    return listAscendents;
}

QList<QString> RelationManager::getDescendents(const QString& idx){
    QList<QString> listDescendents;
    for(RelationManager::Iterator it=getIterator();!it.isDone();it.next())
    {
        for(unsigned int i=0;i<it.current().getNbCouples(); i++)
            if(it.current().getCoupleParIndice(i)->getX()->getId()==idx)
                 listDescendents.append(it.current().getCoupleParIndice(i)->getY()->getId());
    }
    return listDescendents;
}


void RelationManager::save() const {
    qDebug()<<"save relation begin\n";

    QFile newfile(filename);
    if (!newfile.open(QIODevice::WriteOnly | QIODevice::Text))
        throw NotesException(QString("erreur sauvegarde relations : ouverture fichier xml"));
    QXmlStreamWriter stream(&newfile);
    stream.setAutoFormatting(true);
    stream.writeStartDocument();
    stream.writeStartElement("Relations");
       for(unsigned int i=0;i<nbRelations;i++){
                        stream.writeStartElement("Relation");
                        stream.writeTextElement("titre",relations[i]->getTitre());
                        stream.writeTextElement("description",relations[i]->getDesc());
                        if(relations[i]->getOrient())
                            stream.writeTextElement("oriente","true");
                        else
                            stream.writeTextElement("oriente","false");
                        for(unsigned int j=0;j<relations[i]->getNbCouples();j++){
                        stream.writeStartElement("couple");



                        stream.writeTextElement("label",relations[i]->getCoupleParIndice(j)->getLabel());

                        stream.writeTextElement("idx",relations[i]->getCoupleParIndice(j)->getX()->getId());


                        stream.writeTextElement("idy",relations[i]->getCoupleParIndice(j)->getY()->getId());


                        stream.writeTextElement("etat",relations[i]->getCoupleParIndice(j)->getEtat());

                        stream.writeEndElement();
                        }

                        stream.writeEndElement();}
    stream.writeEndElement();
    stream.writeEndDocument();
    qDebug()<<"save relation\n";

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
                Couple** couples = new Couple*;
                unsigned int nbCouples=0;
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
                            xml.readNext();
                            if(xml.text().toString()=="true") orient=1;
                            if(xml.text().toString()=="false") orient=0;


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
                            }

                            xml.readNext();
                            }

                            NotesManager &nm=NotesManager::getManager();
                            Note &x= nm.getNote(idx);
                            Note &y =nm.getNote(idy);
                            Couple *newC = new Couple(label,&x,&y,etat);
                            couples[nbCouples++]=newC;
                            qDebug()<<"ajout couple "<<label<<"\n";

                        }
                    }
                    xml.readNext();
                }
               // qDebug()<<"ajout relation "<<titre<<"\n";
               addRelation(titre,description,orient,couples,nbCouples,nbCouples+20);
            }
            }
        }
    // Error handling.
    if(xml.hasError()) {
        throw NotesException("Erreur lecteur fichier relation, parser xml");
    }
    // Removes any device() or data from the reader * and resets its internal state to the initial state.
    xml.clear();
    qDebug()<<"fin load relation\n";
}

