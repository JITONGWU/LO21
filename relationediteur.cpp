#include "relationediteur.h"
#include <QMessageBox>

RelationEditeur::RelationEditeur(Relation &re, QWidget *parent,bool newR):

    QWidget(parent),relation(&re),newRelation(newR)

{
    titre=new QLineEdit(this);
    if(!newRelation) titre->setReadOnly(true);
    desc=new QTextEdit(this);
    couples = new QListWidget(this);
    orient = new QRadioButton(this);
    titre1=new QLabel("Titre",this);
    desc1=new QLabel("description",this);
    orient1 = new QLabel("orient",this);
    couples1= new QLabel("couples",this);

    save=new QPushButton("sauvegarder",this);
    supprimerC=new QPushButton("supprimer couple",this);
    ajouter=new QPushButton("ajouter",this);

    ctitre=new QHBoxLayout;
    ctitre->addWidget(titre1);
    ctitre->addWidget(titre);

    cdesc=new QHBoxLayout ;
    cdesc->addWidget(desc1);
    cdesc->addWidget(desc);

    corient=new QHBoxLayout ;
    corient->addWidget(orient1);
    corient->addWidget(orient);

    ccouples=new QHBoxLayout ;
    ccouples->addWidget(couples1);
    ccouples->addWidget(couples);

    button = new QHBoxLayout;
    button->addWidget(supprimerC);
    button->addWidget(ajouter);

    couche=new QVBoxLayout;

    couche->addLayout(ctitre);
    couche->addLayout(cdesc);
    couche->addLayout(corient);
    couche->addLayout(ccouples);
    couche->addLayout(button);
    couche->addWidget(save);

    setLayout(couche);
    save->setEnabled(false);

    QObject::connect(save,SIGNAL(clicked()),this,SLOT(saveRelation()));
    QObject::connect(supprimerC,SIGNAL(clicked()),this,SLOT(supprimerCouple()));
    QObject::connect(ajouter,SIGNAL(clicked()),this,SLOT(ajouterCouple()));
    QObject::connect(orient,SIGNAL(clicked()),this,SLOT(IsOriente()));
    QObject::connect(titre,SIGNAL(textEdited(QString)),this,SLOT(activerSave()));
    QObject::connect(desc,SIGNAL(textChanged()),this,SLOT(activerSave()));

}

void RelationEditeur::saveRelation(){
    relation->setTitre(titre->text());
    relation->setDesc(desc->toPlainText());

    if(newRelation)   RelationManager::getManager().addRelation(relation);
    QMessageBox::information(this,"sauvegarder","bien sauvegarder");
    qDebug()<<"saveRelation réussi\n";
    save->setEnabled(false);

    emit SendToPage2(titre->text());//

}

void RelationEditeur::supprimerCouple(){
    relation->retirerCouple(couples->currentRow());//label de couple à supprimer
     QMessageBox::information(this,"supprimer","bien supprimer une couple");
}

void RelationEditeur::activerSave(QString){
    save->setEnabled(true);
}
void RelationEditeur::ajouterCouple(){
    CoupleEditeur addCouple(*relation,this,*this);
    addCouple.exec();
    qDebug()<<"ajouterCouple réussi\n";
}
void RelationEditeur::IsOriente(){
    relation->setOrient(true);
}

CoupleEditeur::CoupleEditeur(Relation& relation,QWidget *parent,RelationEditeur &re):

    QDialog(parent),relation(&relation),relationediteur(&re){

    idx = new QLineEdit ;
    idy = new QLineEdit;
    label = new QLineEdit;
    notes = new QListWidget;
    for(NotesManager::Iterator it= NotesManager::getManager().getIterator();!it.isDone();it.next())

        notes->addItem(it.current().getId());


    idx1 = new QLabel ("note1",this);
    idy1 = new QLabel ("note2",this);
    label1 = new QLabel ("label",this);
    notes1 = new QLabel ("notes",this);

    save = new QPushButton("sauvegarder",this);

    clabel = new QHBoxLayout;
    clabel->addWidget(label1);
    clabel->addWidget(label);

    cidx = new QHBoxLayout;
    cidx->addWidget(idx1);
    cidx->addWidget(idx);

    cidy = new QHBoxLayout;
    cidy->addWidget(idy1);
    cidy->addWidget(idy);

    cnotes = new QHBoxLayout;
    cnotes->addWidget(notes1);
    cnotes->addWidget(notes);

    couche = new QVBoxLayout;
    couche->addLayout(clabel);
    couche->addLayout(cidx);
    couche->addLayout(cidy);
    couche->addLayout(cnotes);
    couche->addWidget(save);
    setLayout(couche);

    save->setEnabled(false);

    QObject::connect(notes,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(afficherId(QListWidgetItem*)));
    QObject::connect(save,SIGNAL(clicked()),this,SLOT(saveCouple()));


}
void CoupleEditeur::afficherId(QListWidgetItem *item){
    if(idx->text()==nullptr)    idx->setText(item->text());
    else    idy->setText(item->text());
    if(idx->text()!=nullptr && idy ->text()!=nullptr) save->setEnabled(true);

}
void CoupleEditeur::saveCouple(){
    relationediteur->couples->addItem(label->text());
    NotesManager &nm = NotesManager::getManager();
    Note& x=nm.getNote(idx->text());
    Note& y=nm.getNote(idy->text());
    relationediteur->relation->addCouple(label->text(),&x,&y);
    QMessageBox::information(this,"sauvegarder","bien sauvegarder");
    save->setEnabled(false);
    this->close();
}
