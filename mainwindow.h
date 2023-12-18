#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "framelesswindow.h"
#include <QMainWindow>
#include "models/ModelDriverTableStandings.h"
#include "models/modeldrivertable.h"
#include "models/modelracestable.h"
#include "title_button.h"
#include "delegates/delegatedriverstable.h"
#include "delegates/delegatedriver.h"
#include "delegates/delegaterace.h"
#include "webviewcutsom.h"
#include <QSettings>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public CFramelessWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void tabChange(int tab);
    void filterTable(const QString &text);
    void tableViewDriverStandingPressed(QModelIndex index);
    void tableViewDriversPressed(QModelIndex index);
    void tableViewRacePressed(QModelIndex index);
private:
    Ui::MainWindow *ui;
    ModelDriverTableStandings* modelDriverStandings;
    ModelDriverTable* modelDrivers;
    ModelRacesTable* modelRaces;
    Title_button *title;
    WebViewCutsom* webView;
};
#endif // MAINWINDOW_H
