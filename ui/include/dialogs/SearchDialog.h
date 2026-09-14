#ifndef SEARCHDIALOG_H
#define SEARCHDIALOG_H

#include <QDialog>

#include <bits/stdc++.h>
using namespace std;

class QLineEdit;

class SearchDialog : public QDialog{
    Q_OBJECT
    QLineEdit* searchInput;
    string searchLabel;

public:
    SearchDialog(
        const string& title,
        const string& label,
        QWidget* parent = nullptr
    );

    string getSearchValue() const;
};

#endif