#include "calculatorwindow.h"
#include "ui_calculatorwindow.h"
#include "commands.h"
#include <QMessageBox>
#include <QGraphicsDropShadowEffect>
#include <QPushButton>

CalculatorWindow::CalculatorWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::CalculatorWindow),
    calculator([this](const std::string& msg) {
        QMetaObject::invokeMethod(this, [this, msg]() {
            QMessageBox::warning(this, "Error", QString::fromStdString(msg));
        });
    })
{
    ui->setupUi(this);
    ui->display->setLineWrapMode(QPlainTextEdit::WidgetWidth);
    ui->display->setReadOnly(true);

    for (QPushButton* button : findChildren<QPushButton*>()) {
        auto shadow = new QGraphicsDropShadowEffect(this);
        shadow->setBlurRadius(8);
        shadow->setOffset(2, 2);
        shadow->setColor(QColor(0, 0, 0, 60));
        button->setGraphicsEffect(shadow);
    }

    setupConnections();
}

CalculatorWindow::~CalculatorWindow() {
    delete ui;
}

void CalculatorWindow::setupConnections() {
    for (int i = 0; i <= 9; ++i) {
        QString buttonName = QString("button%1").arg(i);
        QPushButton* button = findChild<QPushButton*>(buttonName);
        if (button) connect(button, &QPushButton::clicked, this, &CalculatorWindow::onDigitClicked);
    }
    connect(ui->buttonPlus, &QPushButton::clicked, this, &CalculatorWindow::onOperatorClicked);
    connect(ui->buttonMinus, &QPushButton::clicked, this, &CalculatorWindow::onOperatorClicked);
    connect(ui->buttonMultiply, &QPushButton::clicked, this, &CalculatorWindow::onOperatorClicked);
    connect(ui->buttonDivide, &QPushButton::clicked, this, &CalculatorWindow::onOperatorClicked);
    connect(ui->buttonEquals, &QPushButton::clicked, this, &CalculatorWindow::onEqualsClicked);
    connect(ui->buttonClear, &QPushButton::clicked, this, &CalculatorWindow::onClearClicked);
    connect(ui->buttonDelete, &QPushButton::clicked, this, &CalculatorWindow::onDeleteClicked);
    connect(ui->buttonLeftParenthesis, &QPushButton::clicked, this, &CalculatorWindow::onParenthesisClicked);
    connect(ui->buttonRightParenthesis, &QPushButton::clicked, this, &CalculatorWindow::onParenthesisClicked);
    connect(ui->buttonDecimal, &QPushButton::clicked, this, &CalculatorWindow::onDecimalPointClicked);
    connect(ui->buttonSqrt, &QPushButton::clicked, this, &CalculatorWindow::onSqrtClicked);
    connect(ui->buttonReciprocal, &QPushButton::clicked, this, &CalculatorWindow::onReciprocalClicked);
    connect(ui->buttonSin, &QPushButton::clicked, this, &CalculatorWindow::onSinClicked);
    connect(ui->buttonCos, &QPushButton::clicked, this, &CalculatorWindow::onCosClicked);
    connect(ui->buttonTan, &QPushButton::clicked, this, &CalculatorWindow::onTanClicked);
    connect(ui->buttonCot, &QPushButton::clicked, this, &CalculatorWindow::onCotClicked);
}

void CalculatorWindow::executeCommand(std::unique_ptr<Command> command) {
    std::string currentText = ui->display->toPlainText().toStdString();
    std::string newText = command->execute(calculator, currentText);
    ui->display->setPlainText(QString::fromStdString(newText));
}

void CalculatorWindow::onDigitClicked() {
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    if (button)
        executeCommand(std::make_unique<AppendCommand>(button->text().toStdString()));
}

void CalculatorWindow::onOperatorClicked() {
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    if (button)
        executeCommand(std::make_unique<AppendCommand>(button->text().toStdString()));
}

void CalculatorWindow::onEqualsClicked() {
    executeCommand(std::make_unique<CalculateCommand>());
}

void CalculatorWindow::onClearClicked() {
    executeCommand(std::make_unique<ClearCommand>());
}

void CalculatorWindow::onDeleteClicked() {
    executeCommand(std::make_unique<DeleteCommand>());
}

void CalculatorWindow::onParenthesisClicked() {
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    if (button)
        executeCommand(std::make_unique<AppendCommand>(button->text().toStdString()));

}

void CalculatorWindow::onDecimalPointClicked() {
    executeCommand(std::make_unique<AppendCommand>("."));
}

void CalculatorWindow::onSqrtClicked() {
    executeCommand(std::make_unique<SquareRootCommand>());
}

void CalculatorWindow::onReciprocalClicked() {
    executeCommand(std::make_unique<ReciprocalCommand>());
}

void CalculatorWindow::onSinClicked() {
    executeCommand(std::make_unique<SineCommand>());
}

void CalculatorWindow::onCosClicked() {
    executeCommand(std::make_unique<CosineCommand>());
}

void CalculatorWindow::onTanClicked() {
    executeCommand(std::make_unique<TangentCommand>());
}

void CalculatorWindow::onCotClicked() {
    executeCommand(std::make_unique<CotangentCommand>());
}

void CalculatorWindow::handleError(const QString& message) {
    QMessageBox::warning(this, "Error", message);
}

void CalculatorWindow::handleError(const std::string& message) {
    QMessageBox::warning(this, "Error", QString::fromStdString(message));
}
