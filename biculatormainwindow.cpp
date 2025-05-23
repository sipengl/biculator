#include "biculatormainwindow.h"
#include "./ui_biculatormainwindow.h"

BiculatorMainWindow::BiculatorMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::BiculatorMainWindow)
{
    ui->setupUi(this);

    // setup the binary toggle buttons
    for (int i = 0; i < 64; ++i) {
        // Build the button name: "BinDigit0", "BinDigit1", ...
        QString btnName = QString("BinDigit%1").arg(i);
        QPushButton *btn = findChild<QPushButton*>(btnName);
        if (btn) {
            btn->setCheckable(true);
            connect(btn, &QPushButton::toggled, this, &BiculatorMainWindow::onBinButtonToggled);
        }
    }

    // setup/init the HEX/DEC display text fields
    ui->Display_Hex->setText("0x0");
    ui->Display_Dec->setText("0");

    // setup the clear button
    connect(ui->ClearButton, &QPushButton::clicked, this, &BiculatorMainWindow::onClearButtonClicked);
}

BiculatorMainWindow::~BiculatorMainWindow()
{
    delete ui;
}

void BiculatorMainWindow::onBinButtonToggled(bool checked)
{
    // sender() returns a QObject*, so cast it to QPushButton*
    QPushButton *btn = qobject_cast<QPushButton*>(sender());
    if (btn) {
        // Now you can access properties of the button
        QString buttonName = btn->objectName(); // e.g., "pushButton17"
        QString buttonText = btn->text();
        btn->setText(checked ? "1" : "0"); // update button value

        // update text display fields
        this->updateButtonToText();

        // For debugging or logic:
        qDebug() << "Button toggled:" << buttonName << "Checked:" << checked;
    }
}


void BiculatorMainWindow::onClearButtonClicked()
{
    // set all binary buttons to 0
    for(int i = 0; i < 64; i++)
    {
        QString tmpBtnName = QString("BinDigit%1").arg(i);
        QPushButton *tmpBtn = findChild<QPushButton*>(tmpBtnName);
        tmpBtn->setText("0");
        tmpBtn->setChecked(false);
    }
    // update text display fields
    this->updateButtonToText();
}


void BiculatorMainWindow::updateTextToButton()
{

}


void BiculatorMainWindow::updateButtonToText()
{
    uint64_t input = 0;
    for(int i = 0; i < 64; i++)
    {
        QString tmpBtnName = QString("BinDigit%1").arg(i);
        QPushButton *tmpBtn = findChild<QPushButton*>(tmpBtnName);
        uint64_t tmp = tmpBtn->text().toUInt();
        input += (tmp << i);
    }

    ui->Display_Hex->setText("0x" + QString::number(input, 16));
    ui->Display_Dec->setText(QString::number(input, 10));
}












