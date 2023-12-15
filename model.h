#ifndef MODEL_H
#define MODEL_H
#include <list>
#include <QObject>
using std::vector;

class Model : public QObject
{
    Q_OBJECT
    vector<int> gameSequence;
    int sequenceIndex;
    int waitTime;
public:
    explicit Model(QObject *parent = nullptr);
    /// creates the game sequence, ie the order sequence that the buttons will flash in
    void createGameSequence();

    /// sends the corresponding single, determinent on what int
    /// (color (0:red, 1:blue, 2:green)) is at gameSequence[index]
    /// @param index an integer that repersents a index within gameSequence
    void sendGameSequence(int index);

    /// resets the game instance variables
    /// ex. gameSequence = {0,1}
    /// ex. sequenceIndex = 0
    /// ex. waitTime = 1000
    void gameOver();

public slots:
    /// once the red button(represented by 0) is clicked, checks if that was
    /// the correct move by the user
    /// if so: goes to the next move(ie increases the index within the sequence), if it's
    /// at the end of sequence sends signal to start the next sequence of flashing
    /// if not: game is over
    void redButtonClicked();

    /// once the blue button(represented by 1) is clicked, checks if that was the
    /// correct move by the user
    /// if so: goes to the next move(ie increases the index within the sequence), if it's
    /// at the end of sequence sends signal to start the next sequence of flashing
    /// if not: game is over
    void blueButtonClicked();

    /// once the green button(represented by 2) is clicked, checks if that was the
    /// correct move by the user
    /// if so: goes to the next move(ie increases the index within the sequence), if it's
    /// at the end of sequence sends signal to start the next sequence of flashing
    /// if not: game is over
    void greenButtonClicked();

    /// once the start button is clicked, game has started and sequence created.
    void startButtonClicked();

    /// checks at what part of the game sequence the user is at, and sends it as a
    /// signal to update the progress bar
    void updateProgress();

signals:
    /// sent when a user makes a move
    /// @param an integer that is a number 0-100 representing the percentage completed
    /// by the user
    void updateProgressBar(int);

    /// sent when a user makes a mistake
    void youLose();

    /// sent when a user has correctly completed the gameSequence
    void sequenceCompleted();

    /// sent when we call sendGameSequence and the value at gameSequence[index] == 0
    void flashRed();

    /// sent when we call sendGameSequence and the value at gameSequence[index] == 1
    void flashBlue();

    /// sent when we call sendGameSequence and the value at gameSequence[index] == 2
    void flashGreen();

    /// sent when we call sendGameSequence and we've fully looped through the gameSequence
    void sequenceStarted();

};

#endif // MODEL_H
