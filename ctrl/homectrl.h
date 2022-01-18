#ifndef HOMECTRL_H
#define HOMECTRL_H

#include <QFileDialog>
#include <QStringList>
#include <QJsonDocument>

#include "ctrl/ctrl.h"
#include "view/homeview.h"
#include "view/adminview.h"
#include "ctrl/adminctrl.h"
#include "ctrl/jsonfilepicker.h"





/**
 * @brief The HomeCtrl class
 * Classe Derivata da Ctrl, è il Controller specifico per la View HomeView
 * Serve a controllare tutto quello che riguarda la schermata Home della App
 */
class HomeCtrl : public Ctrl
{
    Q_OBJECT
private:

    /**
     * @brief connectViewCtrlSignalsSlots Metodo virtuale
     * Questo Metodo serve a connettere i SIGNAL della HomeView ai Slot del HomeCtrl
     */
    void connectViewCtrlSignalsSlots() const override;

public:
    /**
     * @brief HomeCtrl
     * @param v View collegata al Controller
     */
    explicit HomeCtrl(View* v, Ctrl* parent = nullptr);

    /**
     * @brief getView
     * Metodo virtuale che restituisce la View del controller castata al tipo corretto
     * @return VIEW del Controller interpretata come HomeView
     */
    HomeView* getView() const override;

signals:

public slots:
    void onNewProject() const;
    void onOpenProject() const;
    void onViewClosed() const override;
};

#endif // HOMECTRL_H
