#include "cpersonnedelegate.h"
#include <QDebug>

CPersonneDelegate::CPersonneDelegate(int colonne, QObject *parent): QItemDelegate(parent)
{
    // Itération 6
    this->colonne = colonne;
}

QWidget *CPersonneDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (index.column() == colonne)
    {
        QDateEdit *dateEdit = new QDateEdit(parent);
        dateEdit->setDisplayFormat("dd/MM/yyyy");
        connect(dateEdit, SIGNAL(editingFinished()), this, SLOT(commitAndCloseEditor()));
        qDebug()<< "createEditor";
        return dateEdit;
    }
    else
    {
        return QItemDelegate::createEditor(parent, option, index);
    }
}

void CPersonneDelegate::commitAndCloseEditor()
{
    QDateEdit *editor = qobject_cast<QDateEdit *>(sender());
    emit commitData(editor);
    emit closeEditor(editor);
}

void CPersonneDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    if (index.column() == colonne)
    {
        QString laDate = index.model()->data(index, Qt::DisplayRole).toString();
        QDate date = QDate::fromString(laDate, "dd/MM/yyyy");
        QDateEdit *dateEdit = qobject_cast<QDateEdit *>(editor);
        dateEdit->setDate(date);
    }
    else
    {
        QItemDelegate::setEditorData(editor, index);
    }
}

void CPersonneDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    if (index.column() == colonne)
    {
        QDateEdit *dateEdit = qobject_cast<QDateEdit *>(editor);
        QString laDate = dateEdit->date().toString("dd/MM/yyyy");
        model->setData(index, laDate);
    }
    else
    {
        QItemDelegate::setModelData(editor, model, index);
    }
}
