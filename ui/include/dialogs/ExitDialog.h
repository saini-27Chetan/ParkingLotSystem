#ifndef EXITDIALOG_H
#define EXITDIALOG_H

#include <QDialog>

#include <bits/stdc++.h>
using namespace std;

class QLineEdit;

class ExitDialog : public QDialog{
    Q_OBJECT
    QLineEdit* ticketInput;

public:
    explicit ExitDialog(QWidget* parent = nullptr);
    string getTicketId() const;
};

#endif