#ifndef CALCULATORWINDOW_H
#define CALCULATORWINDOW_H

#include <QMainWindow>
#include <memory>
#include "calculatorfacade.h"
#include "command.h"

QT_BEGIN_NAMESPACE
namespace Ui { class CalculatorWindow; }
QT_END_NAMESPACE

class CalculatorWindow : public QMainWindow {
    Q_OBJECT

public:
    CalculatorWindow(QWidget *parent = nullptr);
    ~CalculatorWindow();

private slots:
    void onDigitClicked();
    void onOperatorClicked();
    void onEqualsClicked();
    void onClearClicked();
    void onDeleteClicked();
    void onParenthesisClicked();
    void onDecimalPointClicked();
    void onSqrtClicked();
    void onReciprocalClicked();
    void onSinClicked();
    void onCosClicked();
    void onTanClicked();
    void onCotClicked();
    void handleError(const QString& message);

private:
    Ui::CalculatorWindow *ui;
    CalculatorFacade calculator;

    void setupConnections();
    void executeCommand(std::unique_ptr<Command> command);
    void handleError(const std::string& message);
};

#endif // CALCULATORWINDOW_H
