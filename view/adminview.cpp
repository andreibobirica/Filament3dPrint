#include "view/adminview.h"


AdminView::AdminView(QSize* s,View* parent) :
    View(s,parent), mainLayout(new QGridLayout), filamentTable(new QTableWidget)
{
    // Grid layout with 3 buttons
    mainLayout->setSpacing(10);
    mainLayout->setMargin(10);

    mainLayout->addWidget(new QPushButton("New"),0,0,1,1,Qt::AlignJustify);
    mainLayout->addWidget(new QPushButton("Save"),0,1,1,1,Qt::AlignJustify);
    mainLayout->addWidget(new QPushButton("Save As"),0,2,1,1,Qt::AlignJustify);
    mainLayout->addWidget(new QPushButton("Home"),0,13,1,1,Qt::AlignRight);

    //Material Table
    QTableWidget* materialTable = new QTableWidget();
    materialTable->setRowCount(10);
    materialTable->setColumnCount(2);
    QStringList headersMaterialTable = { "Materiale", ""};
    materialTable->setHorizontalHeaderLabels(headersMaterialTable);
    materialTable->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    materialTable->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    materialTable->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
    //materialTable->setMinimumWidth(materialTable->minimumWidth());
    //Elementi
    materialTable->setItem(0,0,new QTableWidgetItem("ciao"));//Testo
    materialTable->setCellWidget(0,1,new QPushButton("+"));//Widget

    mainLayout->addWidget(materialTable,1,11,1,3);

    //Pulsanti Grafici
    mainLayout->addWidget(new QPushButton("Consumo Materiale %"),2,1,1,1,Qt::AlignCenter);
    mainLayout->addWidget(new QPushButton("Rapporto Consumo"),2,2,1,1,Qt::AlignCenter);
    mainLayout->addWidget(new QPushButton("Consumo pER mESE"),2,3,1,1,Qt::AlignCenter);


    //implementazione
    setLayout(mainLayout);
    setWindowTitle("Admin Page");


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

    //Delete Button Widget
    QPushButton* addW = new QPushButton("+");
    filamentTable->setCellWidget(row,4,addW);

    connect(addW, &QPushButton::clicked,
            [this, materialeW, durataW, matUsatoW, dataW]() {
        emit recordTableAdded(materialeW->toPlainText(), durataW->value(), matUsatoW->value(), dataW->date());
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

    connect(matUsatoW, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),[this,matUsatoW](int value) {
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
    QPushButton* deleteW = new QPushButton("-");
    //deleteW->setObjectName(QString::number(row));
    filamentTable->setCellWidget(row,4,deleteW);//Widget

    connect(deleteW, &QPushButton::clicked,[this,deleteW]() {
        unsigned int row = filamentTable->indexAt(deleteW->pos()).row();
        emit recordTableRemoved(row);
        filamentTable->removeRow(row);
    });
}

void AdminView::connectViewSignals() const{}



void AdminView::closeEvent(QCloseEvent* event){
    //Elaboro chiusura solo se intenzionata da evento esterno
    if(!event->spontaneous()) return;

    if(!showQuestionDialog(3,"Exit","Sei sicuro di voler uscire?\n")){
        //Ignoro l'evento di chiusura
        event->ignore();
    } else {
        //Accetto l'evento di chiusura della Window
        event->accept();
        //Se esiste una View parent la mostro
        if(parent()) static_cast<View*>(parent())->show();
        //Emetto segnale di chiusura della View
        emit viewClosed();
    }
}





