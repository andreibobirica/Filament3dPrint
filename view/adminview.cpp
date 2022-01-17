#include "view/adminview.h"

AdminView::AdminView(QSize* s,View* parent) : View(s,parent), mainLayout(new QGridLayout)
{
    // Grid layout with 3 buttons
    mainLayout->setSpacing(10);
    mainLayout->setMargin(10);

    mainLayout->addWidget(new QPushButton("New"),0,0,1,1,Qt::AlignJustify);
    mainLayout->addWidget(new QPushButton("Save"),0,1,1,1,Qt::AlignJustify);
    mainLayout->addWidget(new QPushButton("Save As"),0,2,1,1,Qt::AlignJustify);
    mainLayout->addWidget(new QPushButton("Home"),0,13,1,1,Qt::AlignRight);

    //Prints Table
    QTableWidget* filamentTable = new QTableWidget();
    filamentTable->setRowCount(50);
    filamentTable->setColumnCount(5);
    QStringList headersFilamentTable = { "Materiale", "Durata", "Consumo", "Data",""};
    filamentTable->setHorizontalHeaderLabels(headersFilamentTable);
    filamentTable->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    filamentTable->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    filamentTable->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContentsOnFirstShow);
    //filamentTable->setFixedWidth(filamentTable->width());
    //Elementi
    filamentTable->setItem(1,1,new QTableWidgetItem("ciao"));//Testo
    filamentTable->setCellWidget(0,4,new QPushButton("+"));//Widget


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


    mainLayout->addWidget(filamentTable,1,0,1,6);
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

void AdminView::connectViewSignals() const{}

void AdminView::closeEvent(QCloseEvent* event){
    //Elaboro chiusura solo se intenzionata da evento esterno
    if(!event->spontaneous()) return;

    //Creazione POPup Messaggio di conferma
    QMessageBox::StandardButton resBtn = QMessageBox::Yes;
    resBtn = QMessageBox::question( this, "APP_NAME",tr("Sei sicuro di voler uscire?\n"),
    QMessageBox::No | QMessageBox::Yes, QMessageBox::Yes);

    if (resBtn != QMessageBox::Yes) {
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




