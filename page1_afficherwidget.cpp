#include "page1.h"


void Page1::afficherWidget(QListWidgetItem* item){

    //mettre tous les editeur setvisible(false)

        ve->setVisible(false);
        vv->setVisible(false);
        ie->setVisible(false);
        iv->setVisible(false);
        ae->setVisible(false);
        av->setVisible(false);
        te->setVisible(false);
        tv->setVisible(false);
        ade->setVisible(false);
        adv->setVisible(false);
        ar->setVisible(false);
        ir->setVisible(false);
        tar->setVisible(false);
        adr->setVisible(false);
        vr->setVisible(false);
        aa->setVisible(false);
        ia->setVisible(false);
        ta->setVisible(false);
        ada->setVisible(false);
        va->setVisible(false);
        vide->setVisible(false);
    NotesManager &nm = NotesManager::getManager();
    switch (nm.getNote(item->text()).type()) {   //choisir quelle editeur on a besoin.
         case 1:{
                Tache &choisir=static_cast<Tache&>(nm.getNote(item->text()));
                te->tache = &choisir;
                te->id->setText(item->text());
                te->titre->setText(choisir.getTitle());
                te->action->setText(choisir.getAction());
                te->echeance->setDateTime(choisir.getExpDate());
                te->setVisible(true);}
            break;
        case 2: {
                Article &choisir=static_cast<Article&>(nm.getNote(item->text()));
                ae->article = &choisir;
                ae->id->setText(item->text());
                ae->titre->setText(choisir.getTitle());
                ae->t->setText(choisir.getT());
                qDebug()<<choisir.getT()<<"getT reussi\n";
                ae->setVisible(true);}
            break;
        case 3:
                 {
                Image &choisir=static_cast<Image&>(nm.getNote(item->text()));
                ie->image = &choisir;
                ie->id->setText(item->text());
                ie->titre->setText(choisir.getTitle());
                ie->desc->setText(choisir.getDescpt());
                ie->file->setText(choisir.getFicher());

                ie->movie->setFileName(choisir.getFicher());
                ie->position->setMovie(ie->movie);
                ie->movie->start();
                ie->position->show();

                ie->setVisible(true);}
            break;
       case 4: {
                Audio &choisir=static_cast<Audio&>(nm.getNote(item->text()));
                ade->audio = &choisir;
                ade->id->setText(item->text());
                ade->titre->setText(choisir.getTitle());
                ade->desc->setText(choisir.getDescpt());
                ade->file->setText(choisir.getFicher());
                ade->afile->setText(choisir.getAFile());

                ade->sound->setMedia(QUrl::fromLocalFile(ade->afile->text()));
                ade->start->setVisible(true);

                ade->setVisible(true);}
            break;

        case 5: { Video &choisir=static_cast<Video&>(nm.getNote(item->text()));
                ve->video = &choisir;
                ve->id->setText(item->text());
                ve->titre->setText(choisir.getTitle());
                ve->desc->setText(choisir.getDescpt());
                ve->file->setText(choisir.getFicher());
                ve->vfile->setText(choisir.getVFile());

                ve->player->setMedia(QUrl::fromLocalFile(ve->vfile->text()));
                ve->vw->setGeometry(100,100,300,400);
                ve->vw->show();
                ve->player->play();

                ve->setVisible(true);}break;
       default: throw NotesException("erreur de visualiser une note");
            break;
        }
}



void Page1::afficherNotesArch(QListWidgetItem* item){

    //mettre tous les editeur setvisible(false)

        ve->setVisible(false);
        vv->setVisible(false);
        ie->setVisible(false);
        iv->setVisible(false);
        ae->setVisible(false);
        av->setVisible(false);
        te->setVisible(false);
        tv->setVisible(false);
        ade->setVisible(false);
        adv->setVisible(false);
        ar->setVisible(false);
        ir->setVisible(false);
        tar->setVisible(false);
        adr->setVisible(false);
        vr->setVisible(false);
        aa->setVisible(false);
        ia->setVisible(false);
        ta->setVisible(false);
        ada->setVisible(false);
        va->setVisible(false);
        vide->setVisible(false);
    NotesManager &nm = NotesManager::getManager();
    switch (nm.getNote(item->text()).type()) {   //choisir quelle editeur on a besoin.
         case 1:{
                Tache &choisir=static_cast<Tache&>(nm.getNote(item->text()));
                ta->tache = &choisir;
                ta->id->setText(item->text());
                ta->titre->setText(choisir.getTitle());
                ta->action->setText(choisir.getAction());
                te->echeance->setDateTime(choisir.getExpDate());


                ta->setVisible(true);}
            break;
        case 2: {
                qDebug() <<"archive article" ;
                Article &choisir=static_cast<Article&>(nm.getNote(item->text()));
                aa->article = &choisir;
                aa->id->setText(item->text());
                aa->titre->setText(choisir.getTitle());
                aa->t->setText(choisir.getT());
                qDebug()<<choisir.getT()<<"getT reussi\n";

                aa->setVisible(true);}
            break;
        case 3:
                 {
                Image &choisir=static_cast<Image&>(nm.getNote(item->text()));
                ia->image = &choisir;
                ia->id->setText(item->text());
                ia->titre->setText(choisir.getTitle());
                ia->desc->setText(choisir.getDescpt());
                ia->file->setText(choisir.getFicher());

                ia->setVisible(true);}
            break;
       case 4: {
                Audio &choisir=static_cast<Audio&>(nm.getNote(item->text()));
                ada->audio = &choisir;
                ada->id->setText(item->text());
                ada->titre->setText(choisir.getTitle());
                ada->desc->setText(choisir.getDescpt());
                ada->file->setText(choisir.getFicher());
                ada->afile->setText(choisir.getAFile());

                ada->setVisible(true);}
            break;

        case 5: { Video &choisir=static_cast<Video&>(nm.getNote(item->text()));
                va->video = &choisir;
                va->id->setText(item->text());
                va->titre->setText(choisir.getTitle());
                va->desc->setText(choisir.getDescpt());
                va->file->setText(choisir.getFicher());
                va->vfile->setText(choisir.getVFile());

                va->setVisible(true);}break;
       default: throw NotesException("erreur d'ouvrir une note archieve");
           break;
        }

    }



void Page1::restaurerVersion(QListWidgetItem* item) {
    ve->setVisible(false);
    vv->setVisible(false);
    ie->setVisible(false);
    iv->setVisible(false);
    ae->setVisible(false);
    av->setVisible(false);
    te->setVisible(false);
    tv->setVisible(false);
    ade->setVisible(false);
    adv->setVisible(false);
    ar->setVisible(false);
    ir->setVisible(false);
    tar->setVisible(false);
    adr->setVisible(false);
    vr->setVisible(false);
    aa->setVisible(false);
    ia->setVisible(false);
    ta->setVisible(false);
    ada->setVisible(false);
    va->setVisible(false);
    vide->setVisible(false);

    unsigned int j=item->listWidget()->row(item);
    qDebug()<<"restaurer versions :"<<j;
    qDebug()<<NotesManager::getManager().getOldVersion(j)->getId();
    if (NotesManager::getManager().getOldVersion(j)==NULL) { throw NotesException("error, impossible de trouver cette note");}
    switch(NotesManager::getManager().getOldVersion(j)->type()) {

        case 1:{
            Tache &choisir=static_cast<Tache&>(NotesManager::getManager().getOldVersion2(j));
            tar->tache = &choisir;
            tar->id->setText(choisir.getId());
            qDebug()<<"choisir id"<<choisir.getId();
            tar->titre->setText(choisir.getTitle());
            tar->action->setText(choisir.getAction());
           // te->echeance->setDateTime(choisir.getExpDate());
            tar->setRest(j);

            tar->setVisible(true);}break;
       case 2:{
            Article &choisir=static_cast<Article&>(NotesManager::getManager().getOldVersion2(j));
            qDebug()<<choisir.getId()<<choisir.getTitle()<<choisir.getT();
            ar->article = &choisir;
            ar->id->setText(choisir.getId());
            ar->titre->setText(choisir.getTitle());
            ar->t->setText(choisir.getT());
           // te->echeance->setDateTime(choisir.getExpDate());
            ar->setRest(j);

            ar->setVisible(true);}break;
         case 3:{
            Image &choisir=static_cast<Image&>(NotesManager::getManager().getOldVersion2(j));
            ir->image = &choisir;
            ir->id->setText(choisir.getId());
            ir->titre->setText(choisir.getTitle());
            ir->desc->setText(choisir.getDescpt());
            ir->file->setText(choisir.getFicher());
            ir->setRest(j);

            ir->setVisible(true);}break;
          case 4:{
            Audio &choisir=static_cast<Audio&>(NotesManager::getManager().getOldVersion2(j));
            adr->audio = &choisir;
            adr->id->setText(choisir.getId());
            adr->titre->setText(choisir.getTitle());
            adr->desc->setText(choisir.getDescpt());
            adr->file->setText(choisir.getFicher());
            adr->afile->setText(choisir.getAFile());
            adr->setRest(j);

            adr->setVisible(true);}break;
          case 5:{
            Video &choisir=static_cast<Video&>(NotesManager::getManager().getOldVersion2(j));
            vr->video = &choisir;
            vr->id->setText(choisir.getId());
            vr->titre->setText(choisir.getTitle());
            vr->desc->setText(choisir.getDescpt());
            vr->file->setText(choisir.getFicher());
            vr->vfile->setText(choisir.getVFile());
            vr->setRest(j);

            vr->setVisible(true);}break;
           default: qDebug()<<"default"; break;
          }
    }
