#include <QComboBox>
#include <QDialogButtonBox>
#include <QFormLayout>
#include <QLineEdit>
#include <QVBoxLayout>

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

    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept );
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