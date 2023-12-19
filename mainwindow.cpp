#include "mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent)
    : CFramelessWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setResizeable(false);
    modelDriverStandings=new ModelDriverTableStandings();
    ui->tableViewDriverStanding->setModel(modelDriverStandings);
    ui->tableViewDriverStanding->setColumnWidth(0,65);
    ui->tableViewDriverStanding->setColumnWidth(1,286);
    ui->tableViewDriverStanding->setColumnWidth(2,152);
    ui->tableViewDriverStanding->setColumnWidth(3,211);
    ui->tableViewDriverStanding->setColumnWidth(4,92);
    ui->tableViewDriverStanding->setItemDelegate(new DelegateDriversTable(ui->tableViewDriverStanding));
    QObject::connect(ui->tableViewDriverStanding, &QTableView::pressed, this, &MainWindow::tableViewDriverStandingPressed);
    modelDrivers=new ModelDriverTable();
    ui->tableDrivers->setModel(modelDrivers);
    ui->tableDrivers->setColumnWidth(0,317);
    ui->tableDrivers->setColumnWidth(1,204);
    ui->tableDrivers->setColumnWidth(2,171);
    ui->tableDrivers->setItemDelegate(new DelegateDriver(ui->tableDrivers));
    QObject::connect(ui->tableDrivers, &QTableView::pressed, this, &MainWindow::tableViewDriversPressed);
    modelRaces=new ModelRacesTable();
    ui->tableRaces->setModel(modelRaces);
    ui->tableRaces->setColumnWidth(0,92);
    ui->tableRaces->setColumnWidth(1,272);
    ui->tableRaces->setColumnWidth(2,191);
    ui->tableRaces->setColumnWidth(3,323);
    ui->tableRaces->setItemDelegate(new DelegateRace(ui->tableRaces));
    QObject::connect(ui->tableRaces, &QTableView::pressed, this, &MainWindow::tableViewRacePressed);
    title=new Title_button(this);
    setTitleBar(title);
    QObject::connect(ui->hide_button,SIGNAL(clicked()),this,SLOT(showMinimized()));
    QObject::connect(ui->close_button,SIGNAL(clicked()),this,SLOT(close()));
    QObject::connect(ui->pushButton,&QPushButton::clicked,ui->tabWidget,[=](){
        ui->tabWidget->setCurrentIndex(0);
    });
    QObject::connect(ui->pushButton_2,&QPushButton::clicked,ui->tabWidget,[=](){
        ui->tabWidget->setCurrentIndex(1);
    });
    QObject::connect(ui->pushButton_3,&QPushButton::clicked,ui->tabWidget,[=](){
        ui->tabWidget->setCurrentIndex(2);
    });
    QObject::connect(ui->tabWidget,SIGNAL(currentChanged(int)),this,SLOT(tabChange(int)));
    QObject::connect(ui->spinBox,&QSpinBox::valueChanged,ui->tabWidget,[=](int i){
        webView->hide();
        switch (ui->tabWidget->currentIndex()) {
        case 0:
            modelDriverStandings->takeData(ui->spinBox->value());
            break;
        case 1:
            modelDrivers->takeData(ui->spinBox->value());
            break;
        case 2:
            modelRaces->takeData(ui->spinBox->value());
            break;
        }

    });
    QObject::connect(ui->lineEdit, &QLineEdit::textChanged, this, &MainWindow::filterTable);
    ui->tabWidget->setCurrentIndex(0);
    webView = new WebViewCutsom(ui->tabWidget);
    webView->setGeometry(0,0,900,314);
    webView->hide();
    QSettings settings("conf.txt", QSettings::IniFormat);
    ui->tabWidget->setCurrentIndex( settings.value("currentIndex", 0).toInt());
    ui->spinBox->setValue(settings.value("spinBoxValue", 2023).toInt());
}

MainWindow::~MainWindow()
{
    QSettings settings("conf.txt", QSettings::IniFormat);
    settings.setValue("currentIndex", ui->tabWidget->currentIndex());
    settings.setValue("spinBoxValue", ui->spinBox->value());
    delete ui;
}

void MainWindow::tabChange(int tab)
{
webView->hide();
    switch (tab) {
    case 0:
        modelDriverStandings->takeData(ui->spinBox->value());
        ui->pushButton->setStyleSheet("background: #A30202;border-radius: 8px;font-size:20px;");
        ui->pushButton_2->setStyleSheet("background: #232323;border: 4px solid #000000;border-radius: 8px;font-size:20px;");
        ui->pushButton_3->setStyleSheet("background: #232323;border: 4px solid #000000;border-radius: 8px;font-size:20px;");
        break;
    case 1:
        modelDrivers->takeData(ui->spinBox->value());
        ui->pushButton_2->setStyleSheet("background: #A30202;border-radius: 8px;font-size:20px;");
        ui->pushButton->setStyleSheet("background: #232323;border: 4px solid #000000;border-radius: 8px;font-size:20px;");
        ui->pushButton_3->setStyleSheet("background: #232323;border: 4px solid #000000;border-radius: 8px;font-size:20px;");
        break;
    case 2:
        modelRaces->takeData(ui->spinBox->value());
        ui->pushButton_3->setStyleSheet("background: #A30202;border-radius: 8px;font-size:20px;");
        ui->pushButton_2->setStyleSheet("background: #232323;border: 4px solid #000000;border-radius: 8px;font-size:20px;");
        ui->pushButton->setStyleSheet("background: #232323;border: 4px solid #000000;border-radius: 8px;font-size:20px;");
        break;
    }
}
void MainWindow::filterTable(const QString &text)
{
    QString textToLover=text.toLower();
    ui->tableDrivers->setSortingEnabled(false);
    for (int row = 0; row < modelDrivers->rowCount(); ++row) {
        bool matchFound = false;
        for (int col = 0; col < modelDrivers->columnCount(); ++col) {
            QModelIndex index = modelDrivers->index(row, col);
            QString cellData = modelDrivers->data(index, Qt::DisplayRole).toString();
            cellData=cellData.toLower();
            if(cellData.contains(textToLover))
                matchFound = true;
        }
        ui->tableDrivers->setRowHidden(row, !matchFound);
    }
    ui->tableDrivers->setSortingEnabled(true);
}
void MainWindow::tableViewDriverStandingPressed(QModelIndex index)
{
    int column = index.column();
    switch (column) {
    case 1:
        webView->setUrl(modelDriverStandings->returnDriverUrl(index).toUrl());
        webView->show();
        break;
    case 2:
        webView->setUrl(modelDriverStandings->returnConstructorUrl(index).toUrl());
        webView->show();
        break;
    }
}

void MainWindow::tableViewDriversPressed(QModelIndex index)
{
    int column = index.column();
    switch (column) {
    case 0:
        webView->setUrl(modelDrivers->returnDriverUrl(index).toUrl());
        webView->show();
        break;
    }
}

void MainWindow::tableViewRacePressed(QModelIndex index)
{
    int column = index.column();
    switch (column) {
    case 1:
        webView->setUrl(modelRaces->returnGrandPrixUrl(index).toUrl());
        webView->show();
        break;
    case 3:
        webView->setUrl(modelRaces->returnCircuitUrl(index).toUrl());
        webView->show();
        break;
    }
}

