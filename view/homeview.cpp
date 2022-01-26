#include "view/homeview.h"

HomeView::HomeView(const QSize& s,View* parent) : View(s,parent)
{
    QHBoxLayout* mainLayout = new QHBoxLayout;
    mainLayout->setSpacing(0);
    mainLayout->setMargin(0);
    mainLayout->addLayout(createButtonsLayout());
    mainLayout->addLayout(createDescriptionLayout(tr(
    "Filament3dPrint è un programma che ti può aiutare a tenere\n"
    "traccia delle stampe fatte con una Stampante 3D.\n"
    "Quando si fa una stampa 3D è utile tenere traccia di:\n"
    "- Materiale\n"
    "- Durata\n"
    "- Consumo\n"
    "- Data\n"
    "\n"
    "Il materiale è organizzato in bobine vendute al Kg quindi\n"
    "è utili tenere traccia per ogni stampa quale e quanti grammi\n"
    "di materiale si sono usati.\n"
    "è importante tenere traccia della durata in quanto\n"
    "una stampa 3D può durare svariate ore.\n"
    "\n"
    "Questo programma infine offre dei utili grafici\n"
    "con cui esaminare queste informazioni"),
    ":/3dPrint.jpeg"));
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
    //Immagine stampante descrizione
    QLabel* img = new QLabel(this);
    QPixmap pic = QPixmap(imgPath);
    pic = pic.scaledToHeight(300);
    img->setPixmap(pic);
    img->setFixedSize(300,300);
    descrLayout->addWidget(img,Qt::AlignHCenter);

    //Descrizione
    QLabel* desc = new QLabel(description,this);
    QFont f("Calibri", 9);
    desc->setFont(f);
    descrLayout->addWidget(desc,Qt::AlignJustify);

    QHBoxLayout* groupLayout = new QHBoxLayout;
    groupLayout->setMargin(10);
    groupLayout->setSpacing(25);
    groupLayout->setContentsMargins(12, 50, 25, 50);

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



