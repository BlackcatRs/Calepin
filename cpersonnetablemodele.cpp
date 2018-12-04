/*********************************************************************************************
 * CPersonneTableModele()
 * Constructeur par défaut de la classe CPersonneTableModele()
 * Il lit le fichier personnes.txt puis insère les personnes dans la liste
 ********************************************************************************************/
#include "cpersonnetablemodele.h"
#include "MainWindow.h"
//#define FICHIER_PERSONNES "personnes.txt"
CPersonneTableModele::CPersonneTableModele()
{
    Personne personne;
    QString nomFichier ="C:/Users/iris/Desktop/calepin1-y/personnes.txt";// FICHIER_PERSONNES; // Récupérer le nom de fichier
    fichier = new QFile(nomFichier);        // Instancier un objet fichier
    if(fichier->open(QIODevice::ReadOnly))   // Ouvrir le fichier afin de récupérer les données
    {
        qDebug() << "Le fichier personne.txt est ouvert";
        QTextStream stream(fichier);
        while (!stream.atEnd()) //Tant qu'il reste des données à lire
        {
            QString ligneLue = stream.readLine(); // Lire une ligne de données du fichier
            QStringList champ = ligneLue.split((";")); // Les champs de données sont séparés par un ;
            personne.set(NOM,champ.at(NOM));        // Récupère le champ nom
            personne.set(PRENOM,champ.at(PRENOM));  // Récupère le champ prénom
            personne.set(DDN,champ.at(DDN));        // Récupère le champ date de naissance
            personnes.push_back(personne);          // Insérer une personne dans la liste
        }
    }
    else
    {
        // Afficher un message d'erreur dans un MessageBox
        QMessageBox::critical(0, "Message", "Impossible d'ouvrir le fichier personnes.txt !");
        qDebug() << "Impossible d'ouvrir le fichier";
    }
}
QVariant CPersonneTableModele::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();
    if (orientation == Qt::Horizontal)
    {
       // les entêtes des colonnes
        switch(section)
        {
            case NOM : return QString("Nom");
            case PRENOM : return QString::fromUtf8("Prénom");
            case DDN : return QString("Date de naissance");
            default: return QVariant();
        }
    }
    else
        return QString("Ligne %1").arg(section); // peut être caché par la vue*
}

int CPersonneTableModele::rowCount(const QModelIndex &parent) const
{
    if (parent != QModelIndex())
        return 0;
    else
        return personnes.size();    // Retourne la taille de la liste personnes
}
int CPersonneTableModele::columnCount(const QModelIndex &parent) const
{
    return 3;
}bool CPersonneTableModele::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole)
    {
        this->personnes[index.row()].set(index.column(), value.toString());
        emit(dataChanged(index, index));
        return true;
    }
    else
        return false;
}CPersonneTableModele:: ~CPersonneTableModele()
{
    if(fichier != NULL)
    {
    delete fichier;
        qDebug() << ("Fichier supprimé");
        }
        else
        qDebug() <<"Fichier non supprimé";
    }
QVariant CPersonneTableModele::data(const QModelIndex &index, int role) const
{
    if (index.isValid() && (role == Qt::DisplayRole ||role == Qt::EditRole))
    {
        switch (index.column())
        {
            case NOM: return personnes.at(index.row()).get(NOM);        // Retourner le nom de la personne
            break;
            case PRENOM: return personnes.at(index.row()).get(PRENOM);  // Retourner le prénom de la personne
            break;
            case DDN: return personnes.at(index.row()).get(DDN);        // Retourner la date de naissance de la personne
            break;
            default:    return QVariant();
            break;
        }
    }
    else
       return QVariant();
}

Qt::ItemFlags CPersonneTableModele::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;
    else
        return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
}
bool CPersonneTableModele::insertRow(int position, const QModelIndex &index)
{
    Q_UNUSED(index);
    beginInsertRows(QModelIndex(), position, position);
    personnes.push_back(Personne("", "", ""));
    endInsertRows();
    return true;
}

bool CPersonneTableModele::removeRow(int position, const QModelIndex &index)
{
    beginRemoveRows(QModelIndex(), position, position); // Supprimer une seule ligne
    personnes.removeAt(position);
    endRemoveRows();
    return true;
}
