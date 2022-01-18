#include "ctrl/adminctrl.h"

AdminCtrl::AdminCtrl(AdminView* v, AdminModel* m, Ctrl* parent) : Ctrl(v,m,parent){
    //Collego i SIGNAL della View Ai SLOT del Controller
    connectViewCtrlSignalsSlots();
    //Creao la Record Table
    getView()->createRecordTable(0,5,{ "Materiale", "Durata", "Consumo", "Data",""});

    //Creo Prima Row Pulsante Add
    getView()->createAddRowRecordTable(0);

    //Popolo La RecordTable con i Record presi da Model
    unsigned int id = 0;
    for (Record* r : getModel()->getRecordList()) {
        getView()->addItemRecordTable(id++,r);
    }

    //Creo la Material Table
    getView()->createMaterialTable(0,2,{"Materiale",""});

    //Creao Prima Row Pulsante Add
    getView()->createAddRowMaterialTable(0);

    //Popo la MaterialTable con i dati presi da Model
    id = 0;
    for (const QString& m : *getModel()->getMaterialList()) {
        getView()->addItemMaterialTable(id++,m);
    }

}

AdminView* AdminCtrl::getView() const {
    return static_cast<AdminView*>(Ctrl::getView());
}

AdminModel* AdminCtrl::getModel() const {
    return static_cast<AdminModel*>(Ctrl::getModel());
}



void AdminCtrl::connectViewCtrlSignalsSlots() const{
    connect(getView(),SIGNAL(recordTableRemoved(uint)),this,SLOT(onRecordTableRemoved(uint)));
    connect(getView(),SIGNAL(recordTableAdded(QString,uint,uint,QDate)),this,SLOT(onRecordTableAdded(QString,uint,uint,QDate)));
    connect(getView(),SIGNAL(recordTableMaterialeMod(uint,QString)),this,SLOT(onRecordTableMaterialeMod(uint,QString)));
    connect(getView(),SIGNAL(recordTableDurataMod(uint,uint)),this,SLOT(onRecordTableDurataMod(uint,uint)));
    connect(getView(),SIGNAL(recordTableMatUsatoMod(uint,uint)),this,SLOT(onRecordTableMatUsatoMod(uint,uint)));
    connect(getView(),SIGNAL(recordTableDataMod(uint,QDate)),this,SLOT(onRecordTableDataMod(uint,QDate)));

    connect(getView(),SIGNAL(materialTableAdded(QString)),this,SLOT(onMaterialTableAdded(QString)));
    connect(getView(),SIGNAL(materialTableRemoved(uint)),this,SLOT(onMaterialTableRemoved(uint)));
    connect(getView(),SIGNAL(materialTableMaterialeMod(uint,QString)),this,SLOT(onMaterialTableMaterialeMod(uint,QString)));

    connect(getView(),SIGNAL(newBPressed()),this,SLOT(onNewBPressed()));
    connect(getView(),SIGNAL(saveBPressed()),this,SLOT(onSaveBPressed()));
    connect(getView(),SIGNAL(saveAsBPressed()),this,SLOT(onSaveAsBPressed()));
    connect(getView(),SIGNAL(homeBPressed()),this,SLOT(onHomeBPressed()));
}

void AdminCtrl::onViewClosed() const {
    delete this;
}

void AdminCtrl::onRecordTableRemoved(unsigned int row){
    getModel()->removeRecord(row);
}

void AdminCtrl::onRecordTableAdded(const QString & m, unsigned int d, unsigned int mu, const QDate& da){
    Record* r = new Record(m,d,mu,da);
    getModel()->addRecord(r);
    getView()->addItemRecordTable(getModel()->getRecordListSize()-1,r);
}

void AdminCtrl::onRecordTableMaterialeMod(unsigned int row, const QString& m){
    getModel()->getRecord(row)->setMateriale(m);
}

void AdminCtrl::onRecordTableDurataMod(unsigned int row, unsigned int d){
    getModel()->getRecord(row)->setDurata(d);
}

void AdminCtrl::onRecordTableMatUsatoMod(unsigned int row, unsigned int mu){
    getModel()->getRecord(row)->setMatUsato(mu);
}

void AdminCtrl::onRecordTableDataMod(unsigned int row, const QDate& da){
    getModel()->getRecord(row)->setData(da);
}

void AdminCtrl::onMaterialTableAdded(const QString &m){
    getModel()->addMaterial(m);
    getView()->addItemMaterialTable(getModel()->getMaterialList()->size()-1,m);
}

void AdminCtrl::onMaterialTableMaterialeMod(unsigned int row, const QString &m){
    getModel()->setMaterial(row,m);
}

void AdminCtrl::onMaterialTableRemoved(unsigned int row){
    getModel()->removeMaterial(row);
}

void AdminCtrl::onNewBPressed(){
    if(!getView()->showQuestionDialog(3,"Nuovo Progetto","Vuoi aprire un nuovo progetto ?"))return;

    View* parentView = getView()->parent() ? static_cast<View*>(getView()->parent()) : nullptr;
    Ctrl* parentCtrl = parent() ? static_cast<Ctrl*>(parent()) : nullptr;

    AdminView* adminView = new AdminView(new QSize(720,480),parentView);
    adminView->setViewTitle(tr("Nuovo Progetto"));
    AdminCtrl* adminCtrl = new AdminCtrl(adminView,new AdminModel(),parentCtrl);
    adminCtrl->showView();
    getView()->hide();
    delete this;
}

void AdminCtrl::onSaveBPressed() const{
    // Se il file non esiste, magari perchè è un nuovo progetto, salvo con nome
    if(getModel()->getFilePath().isEmpty() || getModel()->getFilePath().isNull()){
        onSaveAsBPressed();
        return;
    }

    //Imposto il titolo alla schermata
    QStringList pieces = getModel()->getFilePath().split( "/" );
    QString last = pieces.value( pieces.length() - 1 );
    getView()->setViewTitle(last);

    //effettuo il salvataggio ed in base all'esito mostro un messaggio
    bool esito = JSONFilePicker::saveAdminModel(getModel()->toQJSonDocument(),getModel()->getFilePath());
    if(!esito)
        getView()->showCriticalDialog("Errore Salvataggio grave","Salvataggio NON riuscito");
    else
        getView()->showInformationDialog("Perfetto !","Salvataggio Riuscito");
}

void AdminCtrl::onSaveAsBPressed() const{
    //Faccio la richiesta per il nume del file
    QString jsonFilter = "JSON Files (*.json)";
    QString titolo = QString::fromStdString("Salva file con nome");
    QString fname = QFileDialog::getSaveFileName(getView(),titolo,QDir::homePath(),jsonFilter);

    //Verifico che il nume sia valido
    if(fname.isEmpty() || fname.isNull()){
        getView()->showCriticalDialog("Errore Salvataggio","Salvataggio NON riuscito - Inserire un nome file valido");
        return;
    }


    //Setto il nume del file al modello di dati
    getModel()->setFilePath(fname);

    //ora faccio il salvataggio automatico
    onSaveBPressed();
}

void AdminCtrl::onHomeBPressed(){
    if(!getView()->showQuestionDialog(3,"Back Home","Vuoi tornare alla Home?"))return;

    if(getView()->parent()) static_cast<View*>(getView()->parent())->show();
    getView()->hide();
    delete this;
}
