#ifndef PARKDIALOG_H
#define PARKDIALOG_H

#include <QDialog>

#include <bits/stdc++.h>
using namespace std;

class QLineEdit;
class QComboBox;

using namespace std;

class ParkDialog : public QDialog{
    Q_OBJECT
    QLineEdit* registrationInput;
    QComboBox* vehicleTypeInput;
    QComboBox* pricingInput;

    bool isValidRegistrationNumber(const string& registrationNumber);

public:
    explicit ParkDialog(QWidget* parent = nullptr);

    string getRegistrationNumber() const;
    string getVehicleType() const;
    string getPricingType() const;
};

#endif