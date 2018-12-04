#include "Personne.h"

Personne::Personne(QString nom, QString prenom, QString ddn)
{

}

Personne::~Personne()
{
}

QString Personne::get(int i) const
{
    switch (i)
    {
        case NOM:
        return nom;
        break;
        case PRENOM:
        return prenom;
        break;
        case DDN:
        return ddn;
        break;
        default:
        break;
    }
}

void Personne::set(int i, QString val)
{
    switch (i)
    {
        case NOM:
         nom = val;
        break;
        case PRENOM:
         prenom = val;
        break;
        case DDN:
        ddn = val;
        break;
        default:
        break;
    }
}

bool Personne::operator==(const Personne &p)
{
    return (this->nom == p.nom && this->prenom == p.prenom && this->ddn == p.ddn);
}
