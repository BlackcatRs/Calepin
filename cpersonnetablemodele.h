#ifndef CPERSONNETABLEMODELE_H
#define CPERSONNETABLEMODELE_H
#include "Personne.h"
#include <QItemSelection>
#include <QVector>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QDebug>

class CPersonneTableModele : public QAbstractTableModel
{
    Q_OBJECT
    QVector<Personne> personnes; // Les personnes sont stockées dans un liste de type QVector
    QFile *fichier;               // Déclarer un fichier
public:
    CPersonneTableModele();
    CPersonneTableModele(const QVector<Personne> &personnes);
    ~CPersonneTableModele();
    // Il faut redéfinir les méthodes héritées de la classe QAbstractTableModel
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    bool insertRow(int position, const QModelIndex &index);
    bool removeRow(int position, const QModelIndex &index);
    bool setData(const QModelIndex &index, const QVariant &value, int role=Qt::EditRole);
    Qt::ItemFlags flags(const QModelIndex &index) const;
};
#endif // CPERSONNETABLEMODELE_H
