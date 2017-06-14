#include "window.h"
#include "page1.h"
#include "page2.h"
#include "page3.h"
FenPrincipale::FenPrincipale() {
    QTabWidget *onglet = new QTabWidget;
    onglet->addTab(new Page1(this), tr("Notes"));
    onglet->addTab(new Page2(this), tr("Relations"));
    onglet->addTab(new Page3(this), tr("Corbeille"));

    setCentralWidget( onglet );
    QTabWidget::TabPosition(0);
    setWindowTitle(tr("Interface"));

}

ListeNotes::ListeNotes() {
        for(int i=0;i< NotesManager::getManager().getNb();i++)
            if(NotesManager::getManager().getNote(i)->getEmp()=="N")
                insertItem(i,new QListWidgetItem(NotesManager::getManager().getNote(i)->getId()));

}
ListeOldNotes::ListeOldNotes() {}
void ListeOldNotes::afficherOldNotes(QListWidgetItem *item) {
    clear();
    unsigned int i=0; unsigned int j=0;
    NotesManager::OldIterator it=NotesManager::getManager().getOldIterator();

    while(!it.isDone()) {
          QString ident=item->text();
          QString id= it.current().getId();
          qDebug()<<j<<it.current().getId(); qDebug()<<"item clické"<<ident;
          if (id==ident) {
              qDebug()<<"id==ident";
              this->setVisible(true);

              QString num=QString::number(i+1);qDebug()<<num;
              qDebug()<<"j dans afficher OldNotes"<<j;
              this->insertItem(j, new QListWidgetItem("Version anterieure n" +  num));
              i++;}
          else { QListWidgetItem *item2 = new QListWidgetItem("");
                this->insertItem(j, item2); item2->setHidden(true);
                this->setRowHidden(j, true);
           }
                j++;
                it.next();
    }
}

ListeRelation::ListeRelation(){
    for(RelationManager::Iterator it = RelationManager::getManager().getIterator();!it.isDone();it.next())
        addItem(it.current().getTitre());
}

