#ifndef TIME_H
#define TIME_H

class Date {
    public:

        Date(unsigned int short j=1, unsigned int short m=1, unsigned int a=0):jour(1),mois(1),annee(0){ setDate(j,m,a); }

        unsigned short int  getJour() const { return jour; }
        unsigned short int  getMois() const { return mois; } //<! Retourne le mois de la date
        unsigned int getAnnee() const { return annee; } //<! Retourne l'année de la date
        void setDate(unsigned short int j, unsigned short int m, unsigned int a); //!< initialisation de la date
        void afficher(std::ostream& f=std::cout) const; //!< affiche le date sous le format JJ/MM/AAAA
        bool operator==(const Date& d) const; //<! d1==d2 retourne vrai si les deux dates sont égales
        bool operator<(const Date& d) const; //<! Compare deux dates dans le temps : d1<d2 retourne true si d1 est avant d2
        int operator-(const Date& d) const; //<! Retourne le nombre de jours séparant les deux dates
        Date demain() const; //<! Retourne la date du lendemain
        Date operator+(unsigned int nb) const; //<!Retourne la date de dans nb jours
    private:
        // attributs
        unsigned short int jour; // jour entre 1 et 31
        unsigned short int mois; // mois entre 1 et 12
        unsigned int annee;
    };




#endif // TIME_H
