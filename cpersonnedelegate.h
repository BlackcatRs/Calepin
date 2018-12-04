#ifndef CPERSONNEDELEGATE_H
#define CPERSONNEDELEGATE_H

#include <QItemDelegate>
#include <QTimeEdit>
class CPersonneDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    CPersonneDelegate(int colonne, QObject *parent=0);
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
 //  Pour quelle colonne un éditeur a été demandé au délégué. S'il s'agit de la colonne da la date de naissance, nous crérons
   void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;

private:
    int colonne;

public slots:
    void commitAndCloseEditor();
};


#endif // CPERSONNEDELEGATE_H
