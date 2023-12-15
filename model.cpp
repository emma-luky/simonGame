#include "model.h"
#include "QDebug"
#include <iostream>
#include <QTimer>

Model::Model(QObject *parent)
    : QObject{parent}, gameSequence({0,1}), sequenceIndex(0),
    waitTime(1000)
{
}

void Model::createGameSequence(){
    srand(time(NULL));
    int randomBit = (rand() % 3);
    this->gameSequence.push_back(randomBit);
    sendGameSequence(0);
}

void Model::sendGameSequence(int index){
    if(index < (int) gameSequence.size()){
        if(gameSequence[index] == 0){
            emit flashRed();
        }
        else if (gameSequence[index] == 1){
            emit flashBlue();
        }
        else{
            emit flashGreen();
        }
        // every time the sequence has an interval of 5 moves, the speed increases
        if(gameSequence.size() % 5 == 0 && waitTime > 300){
            waitTime = waitTime/1.25;
        }
        QTimer::singleShot(waitTime, this, [this, index](){sendGameSequence(index + 1);});
    }
    else{
        emit sequenceStarted();
    }
}

void Model::gameOver(){
    waitTime = 1000;
    sequenceIndex = 0;
    gameSequence = {0,1};
    emit updateProgressBar(0);
    emit youLose();
}

void Model::updateProgress(){
    float percentDone = (float)sequenceIndex/(float)gameSequence.size();
    int value = (int) (percentDone * 100);
    emit updateProgressBar(value);
}

void Model::redButtonClicked(){
    if(gameSequence.at(sequenceIndex) != 0){
        gameOver();
    }
    else if(sequenceIndex + 1 == (int) gameSequence.size()){
        sequenceIndex++;
        updateProgress();
        emit sequenceCompleted();
    }
    else{
        sequenceIndex++;
        updateProgress();
    }
}

void Model::blueButtonClicked(){
    if(gameSequence.at(sequenceIndex) != 1){
        gameOver();
    }
    else if(sequenceIndex + 1 == (int) gameSequence.size()){
        sequenceIndex++;
        updateProgress();
        emit sequenceCompleted();
    }
    else{
        sequenceIndex++;
        updateProgress();
    }
}

void Model::greenButtonClicked(){
    if(gameSequence.at(sequenceIndex) != 2){
        gameOver();
    }
    else if(sequenceIndex + 1 == (int) gameSequence.size()){
        sequenceIndex++;
        updateProgress();
        emit sequenceCompleted();
    }
    else{
        sequenceIndex++;
        updateProgress();
    }
}

void Model::startButtonClicked(){
    sequenceIndex = 0;
    createGameSequence();
}
