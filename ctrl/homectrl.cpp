#include "ctrl/homectrl.h"

HomeCtrl::HomeCtrl(HomeView* v,Ctrl* parent) : Ctrl(v,nullptr,parent){
    //Collego i SIGNAL della View Ai SLOT del Controller
    connectViewCtrlSignalsSlots();
}

HomeView* HomeCtrl::getView() const{
    return static_cast<HomeView*>(Ctrl::getView());
}


void HomeCtrl::connectViewCtrlSignalsSlots() const{
    connect(getView(),SIGNAL(newProject()),this,SLOT(onNewProject()));
    connect(getView(),SIGNAL(openProject()),this,SLOT(onOpenProject()));
}

void HomeCtrl::onNewProject() const{
    qDebug("new Project");

    AdminView* adminView = new AdminView(new QSize(720,480),getView());
    AdminCtrl* adminCtrl = new AdminCtrl(adminView,new AdminModel(),const_cast<Ctrl*>(static_cast<const Ctrl*>(this)));
    adminCtrl->showView();
    getView()->hide();
}

void HomeCtrl::onOpenProject() const{
    qDebug("open Project");

    QString filepath = JSONFilePicker::selectJSONFileDialog();
    if(filepath.isNull()){
        getView()->showWarningDialog("Errore Apertura File", "Selezionare un file");
        return;
    }

    QJsonDocument* jsonData = JSONFilePicker::getJSONFileData(filepath);
    if(jsonData->isNull()){
        getView()->showWarningDialog("Errore Apertura File", "Riprova con un file valido");
        return;
    }


    //Apertura Nuova schermata Admin da progetto Salvato
    AdminView* adminView = new AdminView(new QSize(720,480),getView());
    AdminModel* adminModel = new AdminModel(jsonData);
    AdminCtrl* adminCtrl = new AdminCtrl(adminView,adminModel,const_cast<HomeCtrl*>(this));
    adminCtrl->showView();
    getView()->hide();

}

void HomeCtrl::onViewClosed() const {
    delete this;
}
