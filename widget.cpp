#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setFixedSize(327, 271);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_chooseFileButton_clicked()
{
    QString fname = QFileDialog::getOpenFileName(0, "Choose .css file", "", "*.css");
    ui->fileName->setText(fname);
}

void Widget::on_generateButton_clicked()
{
    QString result;
    QStringList stringContent;
    double rem = 0;

    if(!ui->selectAll->isChecked())     //adding all unselected options into array
    {
        if(!ui->backgroundPosition->isChecked())
        {
            uncheckedOptions.append("background");
        }
        if(!ui->borders->isChecked())
        {
            uncheckedOptions.append("border");
        }
        if(!ui->position->isChecked())
        {
            uncheckedOptions.append("top");
            uncheckedOptions.append("right");
            uncheckedOptions.append("bottom");
            uncheckedOptions.append("left");
        }
        if(!ui->clip->isChecked())
        {
            uncheckedOptions.append("clip");
        }
        if(!ui->wh->isChecked())
        {
            uncheckedOptions.append("width");
            uncheckedOptions.append("height");
        }
        if(!ui->mwh->isChecked())
        {
            uncheckedOptions.append("min-width");
            uncheckedOptions.append("max-width");
            uncheckedOptions.append("min-height");
            uncheckedOptions.append("max-height");
        }
        if(!ui->marker->isChecked())
        {
            uncheckedOptions.append("marker-offset");
        }
        if(!ui->margin->isChecked())
        {
            uncheckedOptions.append("margin");
            uncheckedOptions.append("padding");
        }
        if(!ui->outline->isChecked())
        {
            uncheckedOptions.append("outline");
        }
        if(!ui->letter->isChecked())
        {
            uncheckedOptions.append("letter-spacing");
        }
        if(!ui->indent->isChecked())
        {
            uncheckedOptions.append("text-indent");
        }
        if(!ui->shadows->isChecked())
        {
            uncheckedOptions.append("shadows");
        }
        if(!ui->font->isChecked())
        {
            uncheckedOptions.append("font");
        }
    }

    oldFile.setFileName(ui->fileName->text());
    if(oldFile.open(QIODevice::ReadOnly))
    {
        QTextStream stream(&oldFile);
        bool flag = false;

        while(!stream.atEnd())
        {
            QString current = stream.readLine();
            stringContent = current.split(QRegExp("\\s+"));
            flag = false;

            if(stringContent[0] == "")      //add tabulation for .css file (i use 4 spaces)
            {
                stringContent[0] = "    ";
            }

            if(uncheckedOptions.length() > 0)   //if we have any unchecked options
            {
                for(int i = 0; i < uncheckedOptions.length(); i++)  //we compare current option (like width, height, etc) with the array
                {
                    if(stringContent.value(0).contains(uncheckedOptions.value(i), Qt::CaseInsensitive) || stringContent.value(1).contains(uncheckedOptions.value(i), Qt::CaseInsensitive))
                    {
                        flag = true;    //and if we should not translate current option
                    }
                }
            }

            if(!flag)       //we just skip current string
            {
                for(int i = 0; i < stringContent.length(); i++)
                {
                    QString temp = stringContent[i];
                    if(temp.length() >= 3 && temp.right(3) == "px;") //if px at the end (like width: 100px;)
                    {
                        temp = temp.remove(temp.length() - 3, 3);
                        rem = temp.toDouble() / 16;
                        stringContent[i] = ((QString::number(rem, 'f', 4)).remove(QRegExp("0+$"))).remove(QRegExp("\\.$")) + "rem;"; //really difficult to understand translation :)
                    }
                    else if (temp.length() >= 2 && temp.right(2) == "px")   //if px in middle (like border: 1px solid black;)
                    {
                        temp = temp.remove(temp.length() - 2, 2);
                        rem = temp.toDouble() / 16;
                        stringContent[i] = ((QString::number(rem, 'f', 4)).remove(QRegExp("0+$"))).remove(QRegExp("\\.$")) + "rem";
                    }
                }
            }
            stringContent.append("\n");
            result += stringContent.join(" ");
        }

        oldFile.rename(ui->fileName->text() + ".old");
        oldFile.close();
    }
    else
    {
        QMessageBox::information(0, "Message", "Error occured while opening file!");
    }

    newFile.setFileName(ui->fileName->text());
    if(newFile.open(QIODevice::WriteOnly))
    {
        QTextStream stream(&newFile);

        stream << result;
        newFile.close();
    }
    else
    {
        QMessageBox::information(0, "Message", "Error occured while opening file!");
    }

    ui->fileName->clear();
    uncheckedOptions.clear();
    QMessageBox::information(0, "Message", "Completed!");
}

void Widget::on_selectAll_toggled(bool)
{
    ui->backgroundPosition->setChecked(!ui->backgroundPosition->checkState());
    ui->borders->setChecked(!ui->borders->checkState());
    ui->position->setChecked(!ui->position->checkState());
    ui->clip->setChecked(!ui->clip->checkState());
    ui->wh->setChecked(!ui->wh->checkState());
    ui->mwh->setChecked(!ui->mwh->checkState());
    ui->marker->setChecked(!ui->marker->checkState());
    ui->margin->setChecked(!ui->margin->checkState());
    ui->outline->setChecked(!ui->outline->checkState());
    ui->letter->setChecked(!ui->letter->checkState());
    ui->indent->setChecked(!ui->indent->checkState());
    ui->shadows->setChecked(!ui->shadows->checkState());
    ui->font->setChecked(!ui->font->checkState());
}
