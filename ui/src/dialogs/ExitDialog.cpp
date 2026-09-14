#include <QDialogButtonBox>
#include <QFormLayout>
#include <QLineEdit>
#include <QVBoxLayout>

#include "dialogs/ExitDialog.h"
using namespace std;

ExitDialog::ExitDialog(QWidget* parent) : QDialog(parent){
    setWindowTitle("Exit Vehicle");
    resize(250, 120);

    ticketInput = new QLineEdit(this);
    ticketInput->setPlaceholderText("Enter ticket ID");

    QFormLayout* formLayout = new QFormLayout();
    formLayout->addRow("Ticket ID:", ticketInput);

    QDialogButtonBox* buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addLayout(formLayout);
    layout->addWidget(buttonBox);
}

string ExitDialog::getTicketId() const{
    return ticketInput->text().trimmed().toUpper().toStdString();
}