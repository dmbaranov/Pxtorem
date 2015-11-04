#ifndef WIDGET_H
#define WIDGET_H
#include <QtWidgets>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    //void on_selectAll_clicked();

    void on_chooseFileButton_clicked();

    void on_generateButton_clicked();

    void on_selectAll_toggled(bool);

private:
    Ui::Widget *ui;
    QStringList uncheckedOptions;
    QFile oldFile;
    QFile newFile;
};

#endif // WIDGET_H
