#include "page1.h"
#include <QDateTime>
void Page1::ArticleEditeurVide(){
    Article *avid = new Article("","",QDateTime::currentDateTime(),QDateTime::currentDateTime(),"N",actuelle,0,"");
    av->article=avid;
    av->id->clear();
    av->titre->clear();
    av->t->clear();

    ie->setVisible(false);
    iv->setVisible(false);
    ae->setVisible(false);
    av->setVisible(true);
    te->setVisible(false);
    tv->setVisible(false);
    adv->setVisible(false);
    ade->setVisible(false);
    ve->setVisible(false);
    vv->setVisible(false);
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
}

void Page1::AudioEditeurVide(){
    Audio *advid = new Audio("","",QDateTime::currentDateTime(),QDateTime::currentDateTime(),"N",actuelle,0,"","","");
    adv->id->clear();
    adv->titre->clear();
    adv->desc->clear();
    adv->file->clear();
    adv->afile->clear();
    adv->audio=advid;

    ie->setVisible(false);
    iv->setVisible(false);
    ae->setVisible(false);
    av->setVisible(false);
    te->setVisible(false);
    tv->setVisible(false);
    adv->setVisible(true);
    ade->setVisible(false);
    ve->setVisible(false);
    vv->setVisible(false);
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
}

void Page1::ImageEditeurVide(){
    Image *ivid = new Image("","",QDateTime::currentDateTime(),QDateTime::currentDateTime(),"N",actuelle,0,"","");
    iv->id->clear();
    iv->titre->clear();
    iv->desc->clear();
    iv->file->clear();
    iv->image=ivid;
    ie->setVisible(false);
    iv->setVisible(true);
    ae->setVisible(false);
    av->setVisible(false);
    te->setVisible(false);
    tv->setVisible(false);
    adv->setVisible(false);
    ade->setVisible(false);
    ve->setVisible(false);
    vv->setVisible(false);
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
}
void Page1::TacheEditeurVide(){
    Tache *tvid = new Tache("","",QDateTime::currentDateTime(),QDateTime::currentDateTime(),"N",actuelle,0,"","",QDateTime::currentDateTime(),"");
    tv->id->clear();
    tv->titre->clear();
    tv->action->clear();
    tv->echeance->setDateTime(QDateTime::currentDateTime());
    tv->tache=tvid;
    ie->setVisible(false);
    iv->setVisible(false);
    te->setVisible(false);
    tv->setVisible(true);
    ae->setVisible(false);
    av->setVisible(false);
    adv->setVisible(false);
    ade->setVisible(false);
    ve->setVisible(false);
    vv->setVisible(false);
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
}


void Page1::VideoEditeurVide(){
    Video *vvid = new Video("","",QDateTime::currentDateTime(),QDateTime::currentDateTime(),"N",actuelle,0,"","","");
    vv->id->clear();
    vv->titre->clear();
    vv->desc->clear();
    vv->file->clear();
    vv->vfile->clear();
    vv->video=vvid;
    ie->setVisible(false);
    iv->setVisible(false);
    te->setVisible(false);
    tv->setVisible(false);
    ae->setVisible(false);
    av->setVisible(false);
    adv->setVisible(false);
    ade->setVisible(false);
    ve->setVisible(false);
    vv->setVisible(true);
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
}

