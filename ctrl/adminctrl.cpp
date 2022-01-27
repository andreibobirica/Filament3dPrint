#include "ctrl/adminctrl.h"

AdminCtrl::AdminCtrl(AdminView* v, AdminModel* m, Ctrl* parent) : Ctrl(v,m,parent){
    //Collego i SIGNAL della View Ai SLOT del Controller
    connectViewCtrlSignalsSlots();

    //è essenziale che si crei prima la materialTable e solo poi la record table
    //Questo perchè in caso contrario si verificano dei problemi sulle QComboBox della
    //view che vengono registrati doppiamente.

    //Creo la Material Table
    getView()->createMaterialTable({"MATERIALI",""});

    //Creao Prima Row Pulsante Add
    getView()->createAddRowMaterialTable(0);

    //Popo la MaterialTable con i dati presi da Model
    unsigned int id = 0;
    for (const QString& m : *getModel()->getMaterialList()) {
        getView()->addItemMaterialTable(id++,m);
    }

    //Creao la Record Table
    getView()->createRecordTable({ "Materiale", "Durata", "Consumo", "Data",""});

    //Creo Prima Row Pulsante Add
    getView()->createAddRowRecordTable(0,*getModel()->getMaterialList());

    //Popolo La RecordTable con i Record presi da Model
    id = 0;
    for (Record* r : getModel()->getRecordList()) {
        getView()->addItemRecordTable(id++,*r,*getModel()->getMaterialList());
    }
}

AdminView* AdminCtrl::getView() const {
    return static_cast<AdminView*>(view);
}

AdminModel* AdminCtrl::getModel() const {
    return static_cast<AdminModel*>(model);
}

void AdminCtrl::connectViewCtrlSignalsSlots() const{

    //connessioni per la RecordTable
    connect(view,SIGNAL(recordTableRemoved(uint)),this,SLOT(onRecordTableRemoved(uint)));
    connect(view,SIGNAL(recordTableAdded(QString,uint,uint,QDate)),this,SLOT(onRecordTableAdded(QString,uint,uint,QDate)));
    connect(view,SIGNAL(recordTableMaterialeMod(uint,QString)),this,SLOT(onRecordTableMaterialeMod(uint,QString)));
    connect(view,SIGNAL(recordTableDurataMod(uint,uint)),this,SLOT(onRecordTableDurataMod(uint,uint)));
    connect(view,SIGNAL(recordTableMatUsatoMod(uint,uint)),this,SLOT(onRecordTableMatUsatoMod(uint,uint)));
    connect(view,SIGNAL(recordTableDataMod(uint,QDate)),this,SLOT(onRecordTableDataMod(uint,QDate)));

    //connessioni per la ModelTable
    connect(view,SIGNAL(materialTableAdded(QString)),this,SLOT(onMaterialTableAdded(QString)));
    connect(view,SIGNAL(materialTableRemoved(uint)),this,SLOT(onMaterialTableRemoved(uint)));
    connect(view,SIGNAL(materialTableMaterialeMod(uint,QString)),this,SLOT(onMaterialTableMaterialeMod(uint,QString)));

    //connessioni per i pulsanti di interrazione
    connect(view,SIGNAL(newBPressed()),this,SLOT(onNewBPressed()));
    connect(view,SIGNAL(saveBPressed()),this,SLOT(onSaveBPressed()));
    connect(view,SIGNAL(saveAsBPressed()),this,SLOT(onSaveAsBPressed()));
    connect(view,SIGNAL(homeBPressed()),this,SLOT(onHomeBPressed()));

    connect(view,SIGNAL(pieChartBPressed(bool)),this,SLOT(onPieChartBPressed(bool)));
    connect(view,SIGNAL(lineChartBPressed()),this,SLOT(onLineChartBPressed()));
    connect(view,SIGNAL(barChartBPressed(bool)),this,SLOT(onBarChartBPressed(bool)));
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
    getView()->addItemRecordTable(getModel()->getRecordListSize()-1,*r,*getModel()->getMaterialList());
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
    for(const QString& mAdd : *getModel()->getMaterialList()){
        if(mAdd == m){
            getView()->showCriticalDialog("Inserimento Fallito","Inserimento non concesso\nassicurarsi che il nome sia univoco");
            return;
        }
    }
    getModel()->addMaterial(m);
    getView()->addItemMaterialTable(getModel()->getMaterialList()->size()-1,m);
}

void AdminCtrl::onMaterialTableMaterialeMod(unsigned int row, const QString &m){
    //Counter per controllare che il duplicato esista e non sia se stesso.
    unsigned int counter = 0;
    for(const QString& mAdd : *getModel()->getMaterialList()){
        //Se esiste un diplicato e NON è se stesso
        if(mAdd == m && counter != row){
            //Duplicato trovato , modifico modello e materiale nella view con appeso '_'
            getModel()->setMaterial(row,m);
            getView()->modifyItemMaterialTable(row,m+"_");
            return;
        }//Se esiste un duplicato ed è se stesso
        else if(mAdd == m && counter == row)
            return;
        counter++;
    }

    //Duplicato non trovato, modifico il modello, la view è già corretta, emetto un segnale
    //per aggiornare anche i QComboBox della View nella recordTable
    getModel()->setMaterial(row,m);
    emit getView()->materialTableMaterialeModChecked(row,m);
}

void AdminCtrl::onMaterialTableRemoved(unsigned int row){
    QString m = getModel()->getMaterial(row);
    for(Record* r : getModel()->getRecordList()){
        if(r->getMateriale() == m){
            getView()->showCriticalDialog("Impossibile Rimuovere","Rimozione non concessa\nAssicurarsi che il materiale non sia usato nella lista di Record");
            return;
        }
    }
    getView()->removeItemMaterialTable(row);
    getModel()->removeMaterial(row);
}

void AdminCtrl::onNewBPressed(){
    if(!view->showQuestionDialog(3,"Nuovo Progetto","Vuoi aprire un nuovo progetto ?"))return;

    View* parentView = view->parent() ? static_cast<View*>(view->parent()) : nullptr;
    Ctrl* parentCtrl = parent() ? static_cast<Ctrl*>(parent()) : nullptr;

    AdminView* adminView = new AdminView(view->size(),parentView);
    adminView->setViewTitle(tr("Nuovo"));
    adminView->setWindowSize(view->size());
    AdminCtrl* adminCtrl = new AdminCtrl(adminView,new AdminModel(),parentCtrl);
    adminCtrl->showView();
    view->hide();
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
    view->setViewTitle(last);

    //effettuo il salvataggio ed in base all'esito mostro un messaggio
    bool esito = JSONFilePicker::saveAdminModel(getModel()->toQJSonDocument(),getModel()->getFilePath());
    if(!esito)
        view->showCriticalDialog("Errore Salvataggio grave","Salvataggio NON riuscito");
    else
        view->showInformationDialog("Perfetto !","Salvataggio Riuscito");
}

void AdminCtrl::onSaveAsBPressed() const{
    //Faccio la richiesta per il nume del file
    QString jsonFilter = "JSON Files (*.json)";
    QString titolo = QString::fromStdString("Salva file con nome");
    QString fname = QFileDialog::getSaveFileName(view,titolo,QDir::homePath(),jsonFilter);

    //Verifico che il nume sia valido
    if(fname.isEmpty() || fname.isNull()){
        view->showCriticalDialog("Errore Salvataggio","Salvataggio NON riuscito\nInserire un nome file valido");
        return;
    }

    if (!fname.endsWith(".json"))
        fname+= tr(".json");

    //Setto il nume del file al modello di dati
    getModel()->setFilePath(fname);

    //ora faccio il salvataggio automatico
    onSaveBPressed();
}

void AdminCtrl::onHomeBPressed(){
    if(!view->showQuestionDialog(3,"Back Home","Vuoi tornare alla Home?"))return;
    if(view->parent())
        static_cast<View*>(view->parent())->show();
    view->hide();
    delete this;
}

void AdminCtrl::onPieChartBPressed(bool detail) const{
    if(getModel()->getRecordList().size() == 0){
        view->showWarningDialog("Attenzione","Inserire dei dati prima");
        return;
    }

    //Inizializzazione polimorfa del PieChartView in base se si vogliono i detagli o meno
    PieChartView* pcView;
    pcView = detail ? new PieChartDetailView(QSize(800,700),view) :
                      new PieChartView(QSize(800,700),view);

    PieChartModel* pcModel = new PieChartModel(getModel());
    PieChartCtrl* pcCtrl = new PieChartCtrl(pcView,pcModel,const_cast<AdminCtrl*>(this));
    pcCtrl->showView();
}

void AdminCtrl::onLineChartBPressed() const{
    if(getModel()->getRecordList().size() == 0){
        view->showWarningDialog("Attenzione","Inserire dei dati prima");
        return;
    }

    LineChartView* lcView = new LineChartView(QSize(800,700),view);
    LineChartCtrl* lcCtrl = new LineChartCtrl(lcView,getModel(),const_cast<AdminCtrl*>(this));
    lcCtrl->showView();
}

void AdminCtrl::onBarChartBPressed(bool old) const{
    if(getModel()->getRecordList().size() == 0){
        view->showWarningDialog("Attenzione","Inserire dei dati prima");
        return;
    }

    BarChartView * bView = old ? new BarChartView(QSize(800,700),view) :
                                 new BarChartOldView(QSize(800,700),view);
    BarChartModel* bModel = new BarChartModel(getModel());
    BarChartCtrl* bCtrl = new BarChartCtrl(bView,bModel,const_cast<AdminCtrl*>(this));
    bCtrl->showView();
}
