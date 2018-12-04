#include "MainWindow.h"
#include "cpersonnetablemodele.h"
#include "cpersonnedelegate.h"
MainWindow::MainWindow(QString titre)
{
    this->nomLineEdit    = new QLineEdit(this);
    this->prenomLineEdit = new QLineEdit(this);
    this->ddnDateEdit    = new QLineEdit(this);

    this->nomLineEdit->setFixedHeight(22);
    this->prenomLineEdit->setFixedHeight(22);
    this->ddnDateEdit->setFixedHeight(22);

    this->boutonA = new QPushButton("Ajouter", this);
    this->boutonA->setDefault(true);
    this->boutonS = new QPushButton("Supprimer", this);
    this->boutonS->setEnabled(false);
    // bouton pour enregistre
    saveButton = new QPushButton(tr("&Save..."));
       saveButton->setToolTip(tr("Save contacts to a file"));
       saveButton->setEnabled(true);


    QHBoxLayout *mainLayout     = new QHBoxLayout(NULL);
    QVBoxLayout *lineEditLayout = new QVBoxLayout(NULL),
                *buttonLayout   = new QVBoxLayout(NULL),
                *rightLayout    = new QVBoxLayout(NULL);
    QLabel	    *labelNom       = new QLabel("Nom", this),
                *labelPrenom    = new QLabel(QString::fromUtf8("Prénom"), this),
                *labelDdn       = new QLabel("Date de naissance", this);
    QWidget     *centralWidget  = new QWidget(this);
    personneTableModel = new CPersonneTableModele();
    CPersonneDelegate *myDelegate = new CPersonneDelegate(DDN,this);

    proxyModel = new QSortFilterProxyModel(this);
    proxyModel->setSourceModel(personneTableModel);
    proxyModel->setDynamicSortFilter(true);
    proxyModel->setFilterKeyColumn(NOM);
    proxyModel->sort(0, Qt::AscendingOrder);


    labelNom->setFixedHeight(18);
    labelPrenom->setFixedHeight(18);
    labelDdn->setFixedHeight(18);
	
    // TODO
    this->tView = new QTableView(this);

    tView->verticalHeader()->hide();
    tView->verticalHeader()->setFixedWidth(100);
    tView->verticalHeader()->setDefaultSectionSize(30); // hauteur d'une ligne
#if QT_VERSION >= 0x050000
    tView->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
#else
    tView->verticalHeader()->setResizeMode(QHeaderView::Fixed);
#endif
    tView->horizontalHeader()->setFixedHeight(18);
    tView->horizontalHeader()->setStretchLastSection(true);
#if QT_VERSION >= 0x050000
    tView->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
#else
    tView->horizontalHeader()->setResizeMode(QHeaderView::Fixed);
#endif

    tView->setColumnWidth(0, 200);
    tView->setColumnWidth(1, 200);
    tView->setColumnWidth(2, 200);
    tView->setMinimumWidth(100 + 3*200 + 20);
    tView->setMaximumWidth(this->minimumWidth());
    tView->setSelectionMode(QAbstractItemView::SingleSelection);
    tView->setSelectionBehavior(QAbstractItemView::SelectRows);
    tView->setSortingEnabled(true);
    tView->sortByColumn(0, Qt::AscendingOrder);
    tView->setHorizontalScrollMode(QAbstractItemView::ScrollPerItem);
    tView->setVerticalScrollMode(QAbstractItemView::ScrollPerItem);
    tView->setAlternatingRowColors(true);
   tView->setModel(personneTableModel);
    tView->setItemDelegate(myDelegate);
    tView->setModel(proxyModel);

    lineEditLayout->setAlignment(Qt::AlignTop);
    lineEditLayout->setMargin(2);
    lineEditLayout->setSpacing(2);
    lineEditLayout->addWidget(labelNom);
    lineEditLayout->addWidget(this->nomLineEdit);
    lineEditLayout->addWidget(labelPrenom);
    lineEditLayout->addWidget(this->prenomLineEdit);
    lineEditLayout->addWidget(labelDdn);
    lineEditLayout->addWidget(this-> ddnDateEdit);

    buttonLayout->setAlignment(Qt::AlignTop);
    buttonLayout->setMargin(2);
    buttonLayout->setSpacing(10);
    buttonLayout->addWidget(this->boutonA);
    buttonLayout->addWidget(this->boutonS);
    buttonLayout->addWidget(saveButton);

    rightLayout->addLayout(lineEditLayout);
    rightLayout->addSpacing(30);
    rightLayout->addLayout(buttonLayout);

    mainLayout->setMargin(2);
    mainLayout->setSpacing(2);
    mainLayout->addWidget(this->tView);
    mainLayout->addLayout(rightLayout);

    centralWidget->setLayout(mainLayout);

    this->setCentralWidget(centralWidget);
    this->setWindowTitle(titre);

    connect(this->boutonA,    SIGNAL(clicked()),           this, SLOT(personneAjouter()));
    connect(this->boutonS,    SIGNAL(clicked()),           this, SLOT(personneSupprimer()));
    connect(this->nomLineEdit,    SIGNAL(textEdited(QString)), this, SLOT(effacerSelect()));
    connect(this->prenomLineEdit, SIGNAL(textEdited(QString)), this, SLOT(effacerSelect()));
    connect(this-> ddnDateEdit,    SIGNAL(textEdited(QString)), this, SLOT(effacerSelect()));
    connect(this-> ddnDateEdit,    SIGNAL(editingFinished()),   this, SLOT(nomSetFocus()));
    connect(tView->selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)),this,
    SLOT(selectionChanged(QItemSelection, QItemSelection)));
    connect(saveButton, SIGNAL(clicked()), this, SLOT(saveToFile()));
}

MainWindow::~MainWindow()
{
}

void MainWindow::personneAjouter()
{
    int n = proxyModel->sourceModel()->rowCount();
        (static_cast<CPersonneTableModele *> (proxyModel->sourceModel()))->insertRow(n, QModelIndex());
        n++;
        proxyModel->sourceModel()->setData(this->proxyModel->sourceModel()->index(n - 1, 0, QModelIndex()),
        nomLineEdit->text(), Qt::EditRole);
        proxyModel->sourceModel()->setData(proxyModel->sourceModel()->index(n - 1, 1, QModelIndex()),
        prenomLineEdit->text(), Qt::EditRole);
        proxyModel->sourceModel()->setData(proxyModel->sourceModel()->index(n - 1, 2, QModelIndex()),
        ddnDateEdit->text(), Qt::EditRole);


}

void MainWindow::personneSupprimer()
{

    if(ligneSelectionnee >=0)
        {
            qDebug() << "Numero de ligne a supprimer : " << ligneSelectionnee;
                (static_cast<CPersonneTableModele *> (this->proxyModel->sourceModel()))
            ->removeRow(ligneSelectionnee,QModelIndex());
                // Effacer la sélection pour récupérer la bonne indice après avoir supprimer une ligne
                tView->clearSelection();
        }


}

void MainWindow::deSelect()
{
    this-> nomLineEdit->setText("");

    this-> prenomLineEdit->setText("");
    this-> ddnDateEdit->setText("");
    this->boutonS->setEnabled(false);
    this-> nomLineEdit->setFocus();
}

void MainWindow::nomSetFocus()
{
    this-> nomLineEdit->selectAll();
    this-> nomLineEdit->setFocus();
}

void MainWindow::effacerSelect()
{
    supprimerEnable(false);
}

void MainWindow::supprimerEnable(bool etat)
{
    this->boutonS->setEnabled(etat);
}
void MainWindow::selectionChanged(QItemSelection itemSelected, QItemSelection itemDeSelected)
{
    QModelIndexList indexes = itemSelected.indexes();
        if (!indexes.empty())
        {
            QModelIndex index = indexes.takeFirst(); // Récupère le numéro de la première ligne sélectionnée
            ligneSelectionnee = proxyModel->mapToSource(index).row();
            qDebug() << "Numero de ligne selectionnee : " << ligneSelectionnee;
            this->boutonA->setEnabled(true);
            this->boutonS->setEnabled(true);
        }
        else
        {
            ligneSelectionnee = -1;
            qDebug() << "Aucune ligne n'est selectionnee ";
        }


}
void MainWindow::saveToFile()
{
    QString fileName = QFileDialog::getSaveFileName(this,
        tr("Save Address Book"), "",
        tr("Address Book (*.abk);;All Files (*)"));

    if (fileName.isEmpty())
        return;
    else {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly)) {
            QMessageBox::information(this, tr("Unable to open file"),
                file.errorString());
            return;
        }

        QDataStream out(&file);
        out.setVersion(QDataStream::Qt_4_5);
        out << contacts;
    }
}
