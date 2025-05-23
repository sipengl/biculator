#include "biculatormainwindow.h"
#include "./ui_biculatormainwindow.h"

BiculatorMainWindow::BiculatorMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::BiculatorMainWindow)
{
    ui->setupUi(this);

    for (int i = 0; i < 64; ++i) {
        // Build the button name: "BinDigit0", "BinDigit1", ...
        QString btnName = QString("BinDigit%1").arg(i);
        QPushButton *btn = findChild<QPushButton*>(btnName);
        if (btn) {
            btn->setCheckable(true);
            connect(btn, &QPushButton::toggled, this, &BiculatorMainWindow::onAnyButtonToggled);
        }
    }
}

BiculatorMainWindow::~BiculatorMainWindow()
{
    delete ui;
}

void BiculatorMainWindow::onAnyButtonToggled(bool checked)
{
    // sender() returns a QObject*, so cast it to QPushButton*
    QPushButton *btn = qobject_cast<QPushButton*>(sender());
    if (btn) {
        // Now you can access properties of the button
        QString buttonName = btn->objectName(); // e.g., "pushButton17"
        QString buttonText = btn->text();
        btn->setText(checked ? "1" : "0");

        // For debugging or logic:
        qDebug() << "Button toggled:" << buttonName << "Checked:" << checked;
    }
}
