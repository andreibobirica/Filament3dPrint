#include "view/homeview.h"

HomeView::HomeView(QSize* s,View* parent) : View(s,parent)
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
    buttonsLayout->setSpacing(100);
    buttonsLayout->setContentsMargins(100, 100, 100, 100);
    buttonsLayout->setAlignment(Qt::AlignCenter);

    newPButton = new QPushButton("New Project");
    openPButton = new QPushButton("Open Project");
    newPButton->setFixedSize(200,70);
    openPButton->setFixedSize(200,70);

    buttonsLayout->addWidget(newPButton);
    buttonsLayout->addWidget(openPButton);

    return buttonsLayout;
}

QLayout* HomeView::createDescriptionLayout(const QString& description, const QString& imgPath){
    //Parte destra immagine e descrizione
    QVBoxLayout* descrLayout = new QVBoxLayout;
    descrLayout->setMargin(10);
    descrLayout->setSpacing(10);
    descrLayout->setContentsMargins(50, 50, 50, 50);
    descrLayout->setAlignment(Qt::AlignCenter);

    //Immagine stampante descrizione
    QLabel* img = new QLabel();
    QPixmap pic = QPixmap(imgPath);
    pic = pic.scaledToHeight(400);
    img->setPixmap(pic);
    img->setFixedSize(400,400);
    descrLayout->addWidget(img);

    //Descrizione
    QLabel* desc = new QLabel(description);
    descrLayout->addWidget(desc,Qt::AlignCenter);

    return descrLayout;
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



