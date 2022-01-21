#include "piechartdetailview.h"

void PieChartDetailView::insertMaterial(const QString &materiale, unsigned int occurences){
    series->append(materiale, occurences);
}

void PieChartDetailView::applyGraphics(){
    for(QPieSlice* slice : series->slices()){
        slice->setExploded();
        slice->setLabelVisible();
        slice->setPen(QPen(Qt::darkCyan, 3));
        slice->setLabel(slice->label() + tr(" ") + QString::number((slice->percentage()*100),'f',1) + " %");
    }
    chart->setTitle("Materiale Usato - Percentuale");
}
