#include <QDialogButtonBox>
#include <QFormLayout>
#include <QLineEdit>
#include <QVBoxLayout>

#include "dialogs/SearchDialog.h"
using namespace std;

SearchDialog::SearchDialog(const string& title, const string& label, QWidget* parent) : QDialog(parent), searchLabel(label){
    setWindowTitle(QString::fromStdString(title));
    resize(300, 100);

    searchInput = new QLineEdit(this);
    searchInput->setPlaceholderText(QString::fromStdString(searchLabel) );
    QFormLayout* formLayout = new QFormLayout();
    formLayout->addRow(QString::fromStdString(searchLabel), searchInput );
    QDialogButtonBox* buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this );

    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept );
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject );

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addLayout(formLayout);
    layout->addWidget(buttonBox);
}

string SearchDialog::getSearchValue() const{
    return searchInput->text().trimmed().toUpper().toStdString();
}