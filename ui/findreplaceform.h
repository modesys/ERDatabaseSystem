#ifndef FINDREPLACEFORM_H
#define FINDREPLACEFORM_H

#include <QWidget>
#include <QTextCursor>

namespace Ui {
    class FindReplaceForm;
}

class QTextEdit;
class QSettings;

class FindReplaceForm : public QWidget {
    Q_OBJECT
public:
    FindReplaceForm(QWidget *parent = nullptr);
    virtual ~FindReplaceForm();
    void setTextEdit(QTextEdit *textEdit_);
    void hideReplaceWidgets();
    virtual void writeSettings(QSettings &settings, const QString &prefix = "FindReplaceDialog");
    virtual void readSettings(QSettings &settings, const QString &prefix = "FindReplaceDialog");

public slots:

    void find(bool down);
    void find();  // find next occurrence
    void findNext() { find(true); }  // find next occurrence
    void findPrev() { find(false); }  // find previous occurrence
    void replace();  // Replaces the found occurrences and goes to the next occurrence
    void replaceAll();  // Replaces all the found occurrences

protected:
    void changeEvent(QEvent *e);
    void showError(const QString &error);  // shows an error in the dialog
    void showMessage(const QString &message);  // shows a message in the dialog

protected slots:

    void textToFindChanged();  // when the text edit contents changed
    void validateRegExp(const QString &text);  // checks whether the passed text is a valid regexp
    void regexpSelected(bool sel);  // the regexp checkbox was selected

protected:

    Ui::FindReplaceForm *ui;
    QTextCursor textCursor;  // for searching into the text
    QTextEdit *textEdit;  // the text editor (possibly) associated with this form
};

#endif // FINDREPLACEFORM_H
