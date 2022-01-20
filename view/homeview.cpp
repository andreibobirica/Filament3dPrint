#include "view/homeview.h"

HomeView::HomeView(const QSize& s,View* parent) : View(s,parent)
{
    QHBoxLayout* mainLayout = new QHBoxLayout;
    mainLayout->setSpacing(0);
    mainLayout->setMargin(0);
    mainLayout->addLayout(createButtonsLayout());
    mainLayout->addLayout(createDescriptionLayout(
    "Questa è una descrizione della applicazione a grandi linee \n\
spiegando leggermente come funziona una stampante 3d,\n\
successivamente spiegando cosa utilizza una stampa \n\
introducendo ai futuri record\nche si vedranno nella pagina successiva.",
    "/Users/andreibobirica/OtherFIles/QtFiles/Filament3dPrint/3d.jpg"));
    //Imposto il Layout alla View per essere visualizzata
    setLayout(mainLayout);

    //Connessione dei SIGNAL dei Widget al Signal della HomeView
    connectViewSignals();
}

QLayout* HomeView::createButtonsLayout(){
    QVBoxLayout* buttonsLayout = new QVBoxLayout;

    buttonsLayout->setMargin(10);
    buttonsLayout->setSpacing(50);
    buttonsLayout->setContentsMargins(25,50,12,50);
    buttonsLayout->setAlignment(Qt::AlignCenter);

    newPButton = new QPushButton("New Project",this);
    openPButton = new QPushButton("Open Project",this);
    newPButton->setFixedSize(150,70);
    openPButton->setFixedSize(150,70);

    buttonsLayout->addWidget(newPButton);
    buttonsLayout->addWidget(openPButton);

    return buttonsLayout;
}

QLayout* HomeView::createDescriptionLayout(const QString& description, const QString& imgPath){
    //Parte destra immagine e descrizione
    QVBoxLayout* descrLayout = new QVBoxLayout;
    descrLayout->setAlignment(Qt::AlignCenter);

    //Immagine stampante descrizione
    QLabel* img = new QLabel(this);
    QPixmap pic = QPixmap(imgPath);
    pic = pic.scaledToHeight(300);
    img->setPixmap(pic);
    img->setFixedSize(300,300);
    descrLayout->addWidget(img,Qt::AlignCenter);

    //Descrizione
    QLabel* desc = new QLabel(description,this);
    descrLayout->addWidget(desc,Qt::AlignCenter);

    QHBoxLayout* groupLayout = new QHBoxLayout;
    groupLayout->setMargin(10);
    groupLayout->setSpacing(25);
    groupLayout->setContentsMargins(12, 50, 25, 50);
    groupLayout->setAlignment(Qt::AlignCenter);

    QGroupBox* gruppo = new QGroupBox("Descrizione Programma",this);
    gruppo->setLayout(descrLayout);
    groupLayout->addWidget(gruppo);

    return groupLayout;
}

void HomeView::connectViewSignals() const{
    connect(newPButton,SIGNAL(clicked()),this,SIGNAL(newProject()));
    connect(openPButton,SIGNAL(clicked()),this,SIGNAL(openProject()));
}


void HomeView::closeEvent(QCloseEvent* event){
    //Elaboro chiusura solo se intenzionata da evento esterno
    if(!event->spontaneous()) return;

    if(!showQuestionDialog(2,"Exit","Chiudere l'applicazione?\n")){
        //Ignoro l'evento di chiusura
        event->ignore();
    } else {
        //Accetto l'evento di chiusura della Window
        event->accept();
        //Emetto segnale di chiusura della View
        emit viewClosed();
    }
}



