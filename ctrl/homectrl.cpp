#include "ctrl/homectrl.h"

HomeCtrl::HomeCtrl(HomeView* v,Ctrl* parent) : Ctrl(v,nullptr,parent){
    //Collego i SIGNAL della View Ai SLOT del Controller
    connectViewCtrlSignalsSlots();
}

HomeView* HomeCtrl::getView() const{
    return static_cast<HomeView*>(view);
}


void HomeCtrl::connectViewCtrlSignalsSlots() const{
    connect(view,SIGNAL(newProject()),this,SLOT(onNewProject()));
    connect(view,SIGNAL(openProject()),this,SLOT(onOpenProject()));
}

void HomeCtrl::onNewProject() const{
    AdminView* adminView = new AdminView(view->size(),view);
    adminView->setViewTitle(tr("Nuovo"));
    AdminCtrl* adminCtrl = new AdminCtrl(adminView,new AdminModel(),const_cast<Ctrl*>(static_cast<const Ctrl*>(this)));
    adminCtrl->showView();
    view->hide();
}

void HomeCtrl::onOpenProject() const{
    QString filepath = JSONFilePicker::selectJSONFileDialog();
    if(filepath.isNull()){
        view->showWarningDialog("Errore Apertura File", "Selezionare un file");
        return;
    }

    QJsonDocument* jsonData = JSONFilePicker::getJSONFileData(filepath);
    if(jsonData->isNull()){
        view->showWarningDialog("Errore Apertura File", "Riprova con un file valido");
        return;
    }

    //Apertura Nuova schermata Admin da progetto Salvato
    AdminView* adminView = new AdminView(view->size(),view);
    AdminModel* adminModel = new AdminModel(jsonData,new QString(filepath));

    //Imposto il titolo alla schermata
    QStringList pieces = adminModel->getFilePath().split( "/" );
    QString last = pieces.value( pieces.length() - 1 );
    adminView->setViewTitle(last);

    AdminCtrl* adminCtrl = new AdminCtrl(adminView,adminModel,const_cast<HomeCtrl*>(this));
    adminCtrl->showView();
    view->hide();

}

void HomeCtrl::onViewClosed() const {
    delete this;
}
