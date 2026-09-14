#include <QComboBox>
#include <QDialogButtonBox>
#include <QFormLayout>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QMessageBox>

#include "dialogs/ParkDialog.h"
using namespace std;

ParkDialog::ParkDialog(QWidget* parent) : QDialog(parent){
    setWindowTitle("Park Vehicle");
    setFixedSize(300, 200);

    registrationInput = new QLineEdit(this);
    registrationInput->setPlaceholderText("Enter registration number");

    vehicleTypeInput = new QComboBox(this);
    vehicleTypeInput->addItem("CAR");
    vehicleTypeInput->addItem("BIKE");
    vehicleTypeInput->addItem("ELECTRIC");

    pricingInput = new QComboBox(this);
    pricingInput->addItem("Hourly Pricing");
    pricingInput->addItem("Flat Rate Pricing");

    QFormLayout* formLayout = new QFormLayout();
    formLayout->addRow("Registration:", registrationInput);
    formLayout->addRow("Vehicle Type:", vehicleTypeInput);
    formLayout->addRow("Pricing:", pricingInput);

    QDialogButtonBox* buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);

    connect(buttonBox, &QDialogButtonBox::accepted, this, [this](){
            string registrationNumber = registrationInput->text().trimmed().toUpper().toStdString();

            if(!isValidRegistrationNumber(registrationNumber)){
                QMessageBox messageBox(this);
                messageBox.setWindowTitle("Invalid Registration Number");
                messageBox.setText("Registration number must follow the format:\n" "XX00XX0000");
                messageBox.setIcon(QMessageBox::Warning);
                messageBox.resize(350, 150);
                messageBox.exec();
                return;
            }
            QDialog::accept();
        }
    );
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject );

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addLayout(formLayout);
    layout->addWidget(buttonBox);
}

string ParkDialog::getRegistrationNumber() const{
    return registrationInput->text().trimmed().toUpper().toStdString();
}

string ParkDialog::getVehicleType() const{
    return vehicleTypeInput->currentText().toStdString();
}

string ParkDialog::getPricingType() const{
    return pricingInput->currentText().toStdString();
}

bool ParkDialog::isValidRegistrationNumber(const string& registrationNumber){
    if(registrationNumber.length() != 10)
        return false;

    for(int i = 0; i < 2; i++){
        if(registrationNumber[i] < 'A' || registrationNumber[i] > 'Z')
            return false;
    }

    for(int i = 2; i < 4; i++){
        if(registrationNumber[i] < '0' || registrationNumber[i] > '9')
            return false;
    }

    for(int i = 4; i < 6; i++){
        if(registrationNumber[i] < 'A' || registrationNumber[i] > 'Z')
            return false;
    }

    for(int i = 6; i < 10; i++){
        if(registrationNumber[i] < '0' || registrationNumber[i] > '9')
            return false;
    }

    return true;
}