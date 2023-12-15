#include "view.h"
#include "ui_view.h"
#include "QDebug"
#include <QTimer>

View::View(Model& m, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::view)
{
    ui->setupUi(this);
    ui->blueButton->setEnabled(false);
    ui->redButton->setEnabled(false);
    ui->greenButton->setEnabled(false);

    connect(ui->redButton,
            &QPushButton::clicked,
            &m,
            &Model::redButtonClicked);
    connect(ui->blueButton,
            &QPushButton::clicked,
            &m,
            &Model::blueButtonClicked);
    connect(ui->greenButton,
            &QPushButton::clicked,
            &m,
            &Model::greenButtonClicked);
    connect(ui->startButton,
            &QPushButton::clicked,
            &m,
            &Model::startButtonClicked);

    connect(&m,
            &Model::updateProgressBar,
            ui->progressBar,
            &QProgressBar::setValue);

    connect(&m,
            &Model::flashBlue,
            this,
            &View::flash_blue);
    connect(&m,
            &Model::flashRed,
            this,
            &View::flash_red);
    connect(&m,
            &Model::flashGreen,
            this,
            &View::flash_green);

    connect(&m,
            &Model::sequenceStarted,
            this,
            &View::sequence_started);
    connect(&m,
            &Model::youLose,
            this,
            &View::you_lose);
    connect(&m,
            &Model::sequenceCompleted,
            this,
            &View::sequence_completed);
}

View::~View()
{
    delete ui;
}

void View::on_startButton_clicked(){
    ui->progressBar->setValue(0);
    ui->startButton->setEnabled(false);
    ui->statusLabel->setText("await sequence");

}

void View::flash_red(){
    ui->redButton->setStyleSheet( QString("QPushButton {background-color: rgb(240,34,34);}"));
    QTimer::singleShot(200, this, [this](){this->ui->redButton->setStyleSheet( QString("QPushButton {background-color: rgb(241,241,241);}"));});
    ui->blueButton->setStyleSheet( QString("QPushButton {background-color: rgb(241,241,241);}"));
    ui->greenButton->setStyleSheet( QString("QPushButton {background-color: rgb(241,241,241);}"));

}

void View::flash_blue(){
    ui->blueButton->setStyleSheet( QString("QPushButton {background-color: rgb(34,140,240);}"));
    QTimer::singleShot(200, this, [this](){this->ui->blueButton->setStyleSheet( QString("QPushButton {background-color: rgb(241,241,241);}"));});
    ui->redButton->setStyleSheet( QString("QPushButton {background-color: rgb(241,241,241);}"));
    ui->greenButton->setStyleSheet( QString("QPushButton {background-color: rgb(241,241,241);}"));

}

void View::flash_green(){
    ui->greenButton->setStyleSheet( QString("QPushButton {background-color: rgb(50, 168, 82);}"));
    QTimer::singleShot(200, this, [this](){this->ui->greenButton->setStyleSheet( QString("QPushButton {background-color: rgb(241,241,241);}"));});
    ui->blueButton->setStyleSheet( QString("QPushButton {background-color: rgb(241,241,241);}"));
    ui->redButton->setStyleSheet( QString("QPushButton {background-color: rgb(241,241,241);}"));
}

void View::sequence_started(){
    ui->statusLabel->setText("go for it");
    ui->blueButton->setEnabled(true);
    ui->redButton->setEnabled(true);
    ui->greenButton->setEnabled(true);
}

void View::sequence_completed(){
    ui->blueButton->setEnabled(false);
    ui->redButton->setEnabled(false);
    ui->greenButton->setEnabled(false);
    ui->startButton->setEnabled(true);
    ui->statusLabel->setText("sequence completed! press start");
    QTimer::singleShot(200, this, [](){});
}

void View::you_lose(){
    ui->blueButton->setEnabled(false);
    ui->redButton->setEnabled(false);
    ui->greenButton->setEnabled(false);
    ui->startButton->setEnabled(true);
    ui->statusLabel->setText("you lose!");
}
