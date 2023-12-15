#ifndef VIEW_H
#define VIEW_H

#include <QMainWindow>
#include "model.h"

QT_BEGIN_NAMESPACE
namespace Ui { class view; }
QT_END_NAMESPACE

class View : public QMainWindow
{
    Q_OBJECT

public:
    View(Model& m, QWidget *parent = nullptr);
    ~View();

private slots:
    /// disables start button, updates the statusLabel, resets the progress bar
    void on_startButton_clicked();

    /// flashes the red button while keeps the blue and green button to the default color
    void flash_red();

    /// flashes the blue button while keeps the red and green button to the default color
    void flash_blue();

    /// flashes the green button while keeps the red and blue button to the default color
    void flash_green();

    /// user can now play, it enables the color buttons
    void sequence_started();

    /// disables the color buttons, enables the start button, updates the status label
    void you_lose();

    /// disables the color buttons, updates the status label
    void sequence_completed();

private:
    Ui::view *ui;
};
#endif // VIEW_H
