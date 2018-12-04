#ifndef PERSONNE
#define PERSONNE

#include <QString>

// index i pour get() et set()
#define NOM 	0
#define PRENOM 	1
#define DDN 	2

class Personne
{
    private:
        QString nom,
                prenom,
                ddn;
		
    public:
        Personne(QString nom="", QString prenom="", QString ddn="");
        ~Personne();

        QString get(int i) const;
        void    set(int i, QString val);
        bool operator==(const Personne &p);
};

#endif
