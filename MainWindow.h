#ifndef MAIN_WINDOW
#define MAIN_WINDOW

#include "Personne.h"
#include "cpersonnetablemodele.h"
#include <qglobal.h>
#if QT_VERSION >= 0x050100
#include <QtWidgets> /* tous les widgets de Qt5 */
#else
#include <QtGui> /* tous les widgets de Qt4 */
#endif

class MainWindow : public QMainWindow
{
    Q_OBJECT

    private:
        QLineEdit              *nomLineEdit,
                               *prenomLineEdit,
                               *ddnDateEdit;

        QPushButton            *boutonA,
                               *boutonS;
          QPushButton *saveButton;
        QSortFilterProxyModel  *proxyModel;

        QTableView             *tView;
        QModelIndex             index;
        QString contacts;

        CPersonneTableModele *personneTableModel;
        void supprimerEnable(bool etat);
        int  ligneSelectionnee;
    void removeRow(int position, const QModelIndex &index);
    public:
        MainWindow(QString titre);
        ~MainWindow();

    signals:

    public slots:
        void personneAjouter();
        void personneSupprimer();
        void deSelect();
        void nomSetFocus();
        void effacerSelect();
        void selectionChanged(QItemSelection itemSelected, QItemSelection itemDeSelected);
        void saveToFile();
};

#endif
