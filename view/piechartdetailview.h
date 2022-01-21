#ifndef PIECHARTDETAILVIEW_H
#define PIECHARTDETAILVIEW_H

#include "view/piechartview.h"

/**
 * @brief The PieChartDetailView class Classe derivata da PieChartView
 * è la View per mostrare un grafico a torta con più dettagli
 */
class PieChartDetailView : public PieChartView
{
    Q_OBJECT
public:
    explicit PieChartDetailView(QSize s = QSize(800,500),View* parent = nullptr) : PieChartView(s,parent){}

    /**
     * @brief insertMaterial Metodo virtuale che serve ad inserire un materiale all'interno della QpieChard
     * con insieme anche il numero di occoreze, al contrario del metodo da cui è in ovverriding
     * questo imposta come materiale solamente il materiale come nome.
     * @param materiale materiale da inserire
     * @param occurences occorenze di questo materiale
     */
    void insertMaterial(const QString &materiale, unsigned int occurences) override;

    /**
     * @brief applyGraphics Metodo virtuale che imposta delle caratteristiche grafiche
     * per le fetta della PieChart impostando il titolo e cosa mostrare nella label
     * in questo caso viene mostrato il nome del materiale insieme alla Percentuale di utilizzi
     */
    void applyGraphics() override;
};

#endif // PIECHARTDETAILVIEW_H
