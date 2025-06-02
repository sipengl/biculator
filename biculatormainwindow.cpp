#include "biculatormainwindow.h"
#include "./ui_biculatormainwindow.h"

BiculatorMainWindow::BiculatorMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::BiculatorMainWindow)
{
    ui->setupUi(this);

    setWindowTitle("Bindows Calc.exe");

    this->opLock = 0;

    // setup the binary toggle buttons
    for(int i = 0; i < 64; ++i)
    {
        // Build the button name: "BinDigit0", "BinDigit1", ...
        QString btnName = QString("BinDigit%1").arg(i);
        QPushButton *btn = findChild<QPushButton*>(btnName);
        if(btn)
        {
            btn->setCheckable(true);
            connect(btn, &QPushButton::toggled, this, &BiculatorMainWindow::onBinButtonToggled);
        }
    }

    // setup/init the HEX/DEC display text fields
    ui->Display_Hex->setText("0x0");
    ui->Display_Dec->setText("0");
    connect(ui->Display_Hex, &QLineEdit::textChanged, this, &BiculatorMainWindow::onLineEditTextChanged);
    connect(ui->Display_Dec, &QLineEdit::textChanged, this, &BiculatorMainWindow::onLineEditTextChanged);

    // setup the clear button
    connect(ui->ClearButton, &QPushButton::clicked, this, &BiculatorMainWindow::onClearButtonClicked);
    // setup << and >> button
    connect(ui->LeftShiftButton, &QPushButton::clicked, this, &BiculatorMainWindow::onOpButtonClicked);
    connect(ui->RightShiftButton, &QPushButton::clicked, this, &BiculatorMainWindow::onOpButtonClicked);


    // setup hex dispaly uppercase option check box
    connect(ui->HexUpperOption, &QCheckBox::clicked, this, &BiculatorMainWindow::onTextDisplayOptionChanged);

    // setup/init the nib text display
    for(int i = 0; i < 16; ++i)
    {
        // Build the button name: "BinDigit0", "BinDigit1", ...
        QString labelName = QString("nib%1").arg(i);
        QLabel *label = findChild<QLabel*>(labelName);
        if(label)
        {
            label->setText("0");
        }
    }


}

BiculatorMainWindow::~BiculatorMainWindow()
{
    delete ui;
}

void BiculatorMainWindow::onBinButtonToggled(bool checked)
{
    // sender() returns a QObject*, so cast it to QPushButton*
    QPushButton *btn = qobject_cast<QPushButton*>(sender());
    if (btn)
    {
        if(!this->opLock)
        {
             // update button value
            btn->setText(checked ? "1" : "0");
            // update text display fields
            this->updateButtonToText();
        }

        // update the nibs
        for(int i = 0; i < 16; ++i)
        {
            uint8_t nibSum = 0;
            // Build the button name: "BinDigit0", "BinDigit1", ...
            QString labelName = QString("nib%1").arg(i);
            QLabel *label = findChild<QLabel*>(labelName);
            if(label)
            {
                for(int j = 0; j < 4; j++)
                {
                    QPushButton *tmpBtn = findChild<QPushButton*>(QString("BinDigit%1").arg(4*i+j));
                    nibSum += (tmpBtn->text().toUInt() << j);
                }
                label->setText(QString::number(nibSum, 16).toUpper());
            }
        }

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

    // update oprand1
    this->oprand1 = 0;
}

// this will update this->oprand1 by onBinButtonToggled callback!
// if this update is called from left/right shift, make sure to lock
// so that oprand1 doesn't get overwritten during the onBinButtonToggled callback.
void BiculatorMainWindow::updateTextToButton()
{
    for(int i = 0; i < 64; i++)
    {
        QString tmpBtnName = QString("BinDigit%1").arg(i);
        QPushButton *tmpBtn = findChild<QPushButton*>(tmpBtnName);
        if(this->oprand1 & (1ULL << i))
        {
            tmpBtn->setText("1");
            tmpBtn->setChecked(true);
        }
        else
        {
            tmpBtn->setText("0");
            tmpBtn->setChecked(false);
        }
    }
}


// keep oprand1 consistant with text displays
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
    if(ui->HexUpperOption->isChecked())
        ui->Display_Hex->setText("0x" + QString::number(input, 16).toUpper());
    else
        ui->Display_Hex->setText("0x" + QString::number(input, 16));
    ui->Display_Dec->setText(QString::number(input, 10));

    // update oprand1
    this->oprand1 = input;
}


void BiculatorMainWindow::onTextDisplayOptionChanged()
{
    this->updateButtonToText();
}


void BiculatorMainWindow::onOpButtonClicked()
{
    // find out what button is clicked
    this->opLock = 1;

    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if(button == ui->LeftShiftButton )
    {
        this->oprand1 <<= 1;
        this->updateTextToButton();
    }
    else if(button == ui->RightShiftButton)
    {
        this->oprand1 >>= 1;
        this->updateTextToButton();
    }
    else
    {
        qDebug() << "unidentified OpButton pressed";
    }

    this->updateButtonToText();

    this->opLock = 0;

}

void BiculatorMainWindow::onLineEditTextChanged(const QString &newText)
{
    QLineEdit *qle = qobject_cast<QLineEdit*>(sender());
    if(qle == ui->Display_Dec)
    {
        qDebug() << "DEC is now " << newText;
    }
    else if(qle == ui->Display_Hex)
    {
        qDebug() << "HEX is now " << newText;
    }
    else
    {
        qDebug() << "unidentified qlineedit";
    }
}






















