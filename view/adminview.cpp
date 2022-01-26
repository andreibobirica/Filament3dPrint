#include "view/adminview.h"


AdminView::AdminView(const QSize& s,View* parent) :
    View(s,parent), mainLayout(new QGridLayout(this)), filamentTable(new QTableWidget(this)), materialTable(new QTableWidget(this))
{
    // Grid layout with 3 buttons
    mainLayout->setSpacing(10);
    mainLayout->setMargin(10);

    newB = new QPushButton("New",this);
    mainLayout->addWidget(newB,0,0,1,1,Qt::AlignJustify);

    saveB = new QPushButton("Save",this);
    mainLayout->addWidget(saveB,0,1,1,1,Qt::AlignJustify);

    saveAsB = new QPushButton("Save As",this);
    mainLayout->addWidget(saveAsB,0,2,1,1,Qt::AlignJustify);

    homeB = new QPushButton("Home",this);
    mainLayout->addWidget(homeB,0,4,1,1,Qt::AlignRight);

    //Pulsanti Grafici
    pieChartB = new QPushButton("Materiale Usato N.",this);
    mainLayout->addWidget(pieChartB,2,0,1,1,Qt::AlignCenter);
    pieChartDetailB = new QPushButton("Materiale Usato %",this);
    mainLayout->addWidget(pieChartDetailB,2,1,1,1,Qt::AlignCenter);

    lineChartB = new QPushButton("Rapporto Consumo Durata",this);
    mainLayout->addWidget(lineChartB,2,2,1,1,Qt::AlignCenter);
    barChartB = new QPushButton("Consumo Totale Mensile Dark",this);
    mainLayout->addWidget(barChartB,2,3,1,1,Qt::AlignCenter);
    barChartOldB = new QPushButton("Consumo Totale Mensile Old",this);
    mainLayout->addWidget(barChartOldB,2,4,1,1,Qt::AlignCenter);

    //implementazione
    setLayout(mainLayout);

    //Connessione dei SIGNAL dei Widget al Signal della AdminView
    connectViewSignals();
}

void AdminView::createRecordTable(const QStringList& headers) const{
    //Prints Table
    filamentTable->setRowCount(0);
    filamentTable->setColumnCount(5);
    filamentTable->setHorizontalHeaderLabels(headers);
    filamentTable->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    filamentTable->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    filamentTable->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContentsOnFirstShow);
    filamentTable->setColumnWidth(4,25);
    mainLayout->addWidget(filamentTable,1,0,1,3);
}

void AdminView::createMaterialTable(const QStringList& headers) const{
    //Material Table
    materialTable->setRowCount(0);
    materialTable->setColumnCount(2);
    materialTable->setHorizontalHeaderLabels(headers);
    materialTable->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    materialTable->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    materialTable->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
    materialTable->setColumnWidth(1,25);
    mainLayout->addWidget(materialTable,1,3,1,2);
}

void AdminView::createAddRowRecordTable(unsigned int row, const QStringList& materialList){
    //Inserismo una nuova riga per fare spazio
    filamentTable->insertRow(row);

    //Material Table con la compbo selectg box
    QComboBox* materialeW = new QComboBox(this);
    //Aggiungo la lista degli elementi tra cui scegliere
    materialeW->addItems(materialList);
    //Imposto il widget sulla cella
    filamentTable->setCellWidget(row,0,materialeW);


    //Aggiornamento della lista di materiali alla aggiunta di un materiale
    connect(this,&AdminView::materialTableAddedChecked,materialeW,[materialeW](const QString& m){
        materialeW->addItem(m);
    });
    //Aggiornamento della lista di materiali alla rimozione di un materiale
    connect(this,&AdminView::materialTableRemovedChecked,materialeW,[materialeW](uint i){
        materialeW->removeItem(i);
    });
    //Aggiornamento della list adi materiali alla modifica di un materiale
    connect(this,&AdminView::materialTableMaterialeModChecked,materialeW,[materialeW](uint i, const QString& m){
        //verifico se l'elemento attualmente selezionato è quello da modificare, adrà poi riselezionato
        bool iSelected = (materialeW->currentIndex() == (int)i);
        materialeW->removeItem(i);
        materialeW->insertItem(i,m);
        if(iSelected)
            materialeW->setCurrentIndex(i);
    });


    //Durata Widget
    QSpinBox* durataW = new QSpinBox(this);
    durataW->setRange(0,100000);
    durataW->setSuffix(" h");
    filamentTable->setCellWidget(row,1,durataW);

    //matUsato Widget
    QSpinBox* matUsatoW = new QSpinBox(this);
    matUsatoW->setRange(0,100000);
    matUsatoW->setSuffix(" g");
    filamentTable->setCellWidget(row,2,matUsatoW);

    //data Widget
    QDateEdit* dataW = new QDateEdit(QDate::currentDate(),this);
    filamentTable->setCellWidget(row,3,dataW);

    //Add Button Widget
    QPushButton* addW = new QPushButton("+",this);
    filamentTable->setCellWidget(row,4,addW);

    connect(addW, &QPushButton::clicked,this,
            [this, materialeW, durataW, matUsatoW, dataW]() {
        if(materialeW->currentIndex() != -1)
            emit recordTableAdded(materialeW->currentText(), durataW->value(), matUsatoW->value(), dataW->date());
        else
           showCriticalDialog("Inserimento non concesso","Inserire prima dei materiali");
    });
}

void AdminView::createAddRowMaterialTable(unsigned int row){
    //Inserismo una nuova riga per fare spazio
    materialTable->insertRow(row);

    //Materiale Widget Select Box
    QTextEdit* materialeW = new QTextEdit(this);
    materialTable->setCellWidget(row,0,materialeW);

    //ADD Button Widget
    QPushButton* addW = new QPushButton("+",this);
    materialTable->setCellWidget(row,1,addW);

    connect(addW, &QPushButton::clicked,
            [this, materialeW]() {
        if(materialeW->toPlainText().isNull() || materialeW->toPlainText().isEmpty())
            showCriticalDialog("Inserimento Non Concesso", "Inserire un nome valido");
        else
            emit materialTableAdded(materialeW->toPlainText());
    });
}

void AdminView::addItemRecordTable(unsigned int row,const Record& r, const QStringList& materialList){
    //Creo La ADD Row più in basso
    createAddRowRecordTable(row+1,materialList);

    //Material Table con la compbo selectg box
    QComboBox* materialeW = new QComboBox(this);
    //Aggiungo la lista degli elementi tra cui scegliere
    materialeW->addItems(materialList);
    //Seleziono l'elemento predefinito scelto
    int index = materialeW->findText(r.getMateriale());
    if(index != -1)
        materialeW->setCurrentIndex(index);
    //Imposto il widget sulla cella
    filamentTable->setCellWidget(row,0,materialeW);


    //Aggiornamento della lista di materiali alla aggiunta di un materiale dalla MaterialList
    connect(this,&AdminView::materialTableAddedChecked,materialeW,[materialeW](const QString& m){
        materialeW->addItem(m);
    });
    //Aggiornamento della lista di materiali alla rimozione di un materiale dalla MaterialList
    connect(this,&AdminView::materialTableRemovedChecked,materialeW,[materialeW](uint i){
        materialeW->removeItem(i);
    });
    //Aggiornamento della lista di materiali alla modifica di un materiale
    connect(this,&AdminView::materialTableMaterialeModChecked,materialeW,[materialeW](uint i, const QString& m){
        //verifico se l'elemento attualmente selezionato è quello da modificare, sarà poi riselezionato
        bool iSelected = (materialeW->currentIndex() == (int)i);
        materialeW->removeItem(i);
        materialeW->insertItem(i,m);
        if(iSelected)
            materialeW->setCurrentIndex(i);
    });

    connect(materialeW, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),this,[this,materialeW]() {
        unsigned int row = filamentTable->indexAt(materialeW->pos()).row();
        emit recordTableMaterialeMod(row,materialeW->currentText());
    });

    //Durata Widget
    QSpinBox* durataW = new QSpinBox(this);
    durataW->setRange(0,100000);
    durataW->setSuffix(" h");
    durataW->setValue(r.getDurata());
    filamentTable->setCellWidget(row,1,durataW);

    connect(durataW, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),this,[this,durataW](int value) {
        unsigned int row = filamentTable->indexAt(durataW->pos()).row();
        emit recordTableDurataMod(row,value);
        //durataW->value() == value
    });

    //matUsato Widget
    QSpinBox* matUsatoW = new QSpinBox(this);
    matUsatoW->setRange(0,100000);
    matUsatoW->setSuffix(" g");
    matUsatoW->setValue(r.getMatUsato());
    filamentTable->setCellWidget(row,2,matUsatoW);

    connect(matUsatoW, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged),this,[this,matUsatoW](int value) {
        unsigned int row = filamentTable->indexAt(matUsatoW->pos()).row();
        emit recordTableMatUsatoMod(row,value);
        //matUsatoW->value() == value
    });

    //data Widget
    QDateEdit* dataW = new QDateEdit(r.getData(),this);
    filamentTable->setCellWidget(row,3,dataW);

    connect(dataW, &QDateEdit::dateChanged,this,[this,dataW](const QDate& da) {
        unsigned int row = filamentTable->indexAt(dataW->pos()).row();
        emit recordTableDataMod(row,da);
        //dataW->date() == da
    });

    //Delete Button Widget
    QPushButton* deleteW = new QPushButton("-",this);
    filamentTable->setCellWidget(row,4,deleteW);//Widget

    //Connessione al pulsante delete per eliminare la riga e aggiornare il modello di dati con l'eliminazione
    connect(deleteW, &QPushButton::clicked,this,[this,deleteW]() {
        unsigned int row = filamentTable->indexAt(deleteW->pos()).row();
        emit recordTableRemoved(row);
        filamentTable->removeRow(row);
    });
}

void AdminView::addItemMaterialTable(unsigned int row,const QString& m){
    //Creo La ADD Row più in basso
    createAddRowMaterialTable(row+1);

    //Materiale Widget Select Box
    QTextEdit* materialeW = new QTextEdit(this);
    materialeW->setText(m);
    materialTable->setCellWidget(row,0,materialeW);

    connect(materialeW, &QTextEdit::textChanged,[this,materialeW]() {
        unsigned int row = materialTable->indexAt(materialeW->pos()).row();
        emit materialTableMaterialeMod(row,materialeW->toPlainText());
    });

    //Delete Button Widget
    QPushButton* deleteW = new QPushButton("-",this);
    //deleteW->setObjectName(QString::number(row));
    materialTable->setCellWidget(row,1,deleteW);//Widget

    connect(deleteW, &QPushButton::clicked,[this,deleteW]() {
        unsigned int row = materialTable->indexAt(deleteW->pos()).row();
        emit materialTableRemoved(row);
        //L'eliminazione effettiva avviene solamente al responso del controller
        //che richiama il metodo
        //this->removeItemMaterialTable();
    });

    //Emissione di segnale per aggiornare i QComboBox Selezionabili che esiste un nuovo Material
    //tra cui scegliere
    emit materialTableAddedChecked(m);
}

void AdminView::modifyItemMaterialTable(unsigned int row, const QString &m){
    QTextEdit* textEdit = static_cast<QTextEdit*>(materialTable->cellWidget(row,0));
    textEdit->setText(m);
    emit materialTableMaterialeModChecked(row,m);
}

void AdminView::removeItemMaterialTable(unsigned int row){
    materialTable->removeRow(row);
    emit materialTableRemovedChecked(row);
}

void AdminView::setViewTitle(const QString &title){
    setWindowTitle("Progetto "+title);
}

void AdminView::connectViewSignals() const{
    connect(newB,SIGNAL(clicked()),this,SIGNAL(newBPressed()));
    connect(saveB,SIGNAL(clicked()),this,SIGNAL(saveBPressed()));
    connect(saveAsB,SIGNAL(clicked()),this,SIGNAL(saveAsBPressed()));
    connect(homeB,SIGNAL(clicked()),this,SIGNAL(homeBPressed()));

    connect(pieChartB,&QPushButton::clicked,this,[this](){emit pieChartBPressed(false);});
    connect(pieChartDetailB,&QPushButton::clicked,this,[this](){emit pieChartBPressed(true);});
    connect(lineChartB,SIGNAL(clicked()),this,SIGNAL(lineChartBPressed()));
    connect(barChartB,&QPushButton::clicked,this,[this](){emit barChartBPressed(true);});
    connect(barChartOldB,&QPushButton::clicked,this,[this](){emit barChartBPressed(false);});
}

void AdminView::closeEvent(QCloseEvent* event){
    //Elaboro chiusura solo se intenzionata da evento esterno
    if(!event->spontaneous()) return;

    if(!showQuestionDialog(3,"Exit","Sei sicuro di voler uscire?\n")){
        //Ignoro l'evento di chiusura
        event->ignore();
    } else {
        //Accetto l'evento di chiusura della Window
        event->accept();
        emit viewClosed();
    }
}





