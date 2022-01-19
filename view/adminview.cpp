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
    mainLayout->addWidget(homeB,0,13,1,1,Qt::AlignRight);

    //Pulsanti Grafici
    mainLayout->addWidget(new QPushButton("Consumo Materiale %",this),2,1,1,1,Qt::AlignCenter);
    mainLayout->addWidget(new QPushButton("Rapporto Consumo",this),2,2,1,1,Qt::AlignCenter);
    mainLayout->addWidget(new QPushButton("Consumo pER mESE",this),2,3,1,1,Qt::AlignCenter);


    //implementazione
    setLayout(mainLayout);

    //Connessione dei SIGNAL dei Widget al Signal della AdminView
    connectViewSignals();
}

void AdminView::createRecordTable(unsigned int row, unsigned int column, QStringList headers) const{
    //Prints Table
    filamentTable->setRowCount(row);
    filamentTable->setColumnCount(column);
    filamentTable->setHorizontalHeaderLabels(headers);
    filamentTable->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    filamentTable->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    filamentTable->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContentsOnFirstShow);
    mainLayout->addWidget(filamentTable,1,0,1,6);
}

void AdminView::createMaterialTable(unsigned int row, unsigned int column, QStringList headers) const{
    //Material Table
    materialTable->setRowCount(row);
    materialTable->setColumnCount(column);
    materialTable->setHorizontalHeaderLabels(headers);
    materialTable->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    materialTable->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    materialTable->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
    mainLayout->addWidget(materialTable,1,11,1,3);
}

void AdminView::createAddRowRecordTable(unsigned int row){
    //Inserismo una nuova riga per fare spazio
    filamentTable->insertRow(row);
    //Materiale Widget Select Box
    QTextEdit* materialeW = new QTextEdit(this);
    filamentTable->setCellWidget(row,0,materialeW);

    //Durata Widget
    QSpinBox* durataW = new QSpinBox(this);
    durataW->setRange(1,100000);
    durataW->setSuffix(" h");
    filamentTable->setCellWidget(row,1,durataW);

    //matUsato Widget
    QSpinBox* matUsatoW = new QSpinBox(this);
    matUsatoW->setRange(1,100000);
    matUsatoW->setSuffix(" g");
    filamentTable->setCellWidget(row,2,matUsatoW);

    //data Widget
    QDateEdit* dataW = new QDateEdit(QDate::currentDate(),this);
    filamentTable->setCellWidget(row,3,dataW);

    //Add Button Widget
    QPushButton* addW = new QPushButton("+",this);
    filamentTable->setCellWidget(row,4,addW);

    connect(addW, &QPushButton::clicked,
            [this, materialeW, durataW, matUsatoW, dataW]() {
        emit recordTableAdded(materialeW->toPlainText(), durataW->value(), matUsatoW->value(), dataW->date());
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
        emit materialTableAdded(materialeW->toPlainText());
    });
}

void AdminView::addItemRecordTable(unsigned int row,Record* r){
    //Creo La ADD Row più in basso
    createAddRowRecordTable(row+1);

    //Materiale Widget Select Box
    QTextEdit* materialeW = new QTextEdit(this);
    materialeW->setText(r->getMateriale());
    filamentTable->setCellWidget(row,0,materialeW);

    connect(materialeW, &QTextEdit::textChanged,[this,materialeW]() {
        unsigned int row = filamentTable->indexAt(materialeW->pos()).row();
        emit recordTableMaterialeMod(row,materialeW->toPlainText());
    });

    //Durata Widget
    QSpinBox* durataW = new QSpinBox(this);
    durataW->setRange(1,100000);
    durataW->setSuffix(" h");
    durataW->setValue(r->getDurata());
    filamentTable->setCellWidget(row,1,durataW);

    connect(durataW, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),[this,durataW](int value) {
        unsigned int row = filamentTable->indexAt(durataW->pos()).row();
        emit recordTableDurataMod(row,value);
        //durataW->value() == value
    });

    //matUsato Widget
    QSpinBox* matUsatoW = new QSpinBox(this);
    matUsatoW->setRange(1,100000);
    matUsatoW->setSuffix(" g");
    matUsatoW->setValue(r->getMatUsato());
    filamentTable->setCellWidget(row,2,matUsatoW);

    connect(matUsatoW, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged),[this,matUsatoW](int value) {
        unsigned int row = filamentTable->indexAt(matUsatoW->pos()).row();
        emit recordTableMatUsatoMod(row,value);
        //matUsatoW->value() == value
    });

    //data Widget
    QDateEdit* dataW = new QDateEdit(r->getData(),this);
    filamentTable->setCellWidget(row,3,dataW);

    connect(dataW, &QDateEdit::dateChanged,[this,dataW](const QDate& da) {
        unsigned int row = filamentTable->indexAt(dataW->pos()).row();
        emit recordTableDataMod(row,da);
        //dataW->date() == da
    });

    //Delete Button Widget
    QPushButton* deleteW = new QPushButton("-",this);
    //deleteW->setObjectName(QString::number(row));
    filamentTable->setCellWidget(row,4,deleteW);//Widget

    connect(deleteW, &QPushButton::clicked,[this,deleteW]() {
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
        materialTable->removeRow(row);
    });
}

void AdminView::setViewTitle(const QString &title){
    setWindowTitle("Progetto "+title);
}

void AdminView::connectViewSignals() const{
    connect(newB,SIGNAL(clicked()),this,SIGNAL(newBPressed()));
    connect(saveB,SIGNAL(clicked()),this,SIGNAL(saveBPressed()));
    connect(saveAsB,SIGNAL(clicked()),this,SIGNAL(saveAsBPressed()));
    connect(homeB,SIGNAL(clicked()),this,SIGNAL(homeBPressed()));
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





