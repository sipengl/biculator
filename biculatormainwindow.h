#ifndef BICULATORMAINWINDOW_H
#define BICULATORMAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class BiculatorMainWindow;
}
QT_END_NAMESPACE

class BiculatorMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    BiculatorMainWindow(QWidget *parent = nullptr);
    ~BiculatorMainWindow();

private slots:
    void onBinButtonToggled(bool checked);
    void onClearButtonClicked();

private:
    Ui::BiculatorMainWindow *ui;
    uint64_t oprand1;
    uint64_t oprand2;

    void updateTextToButton();
    void updateButtonToText();
};
#endif // BICULATORMAINWINDOW_H
