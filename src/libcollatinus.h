/*
 *                          libcollatinus.h
 *
 *  This file is part of COLLATINVS.
 *                                                                            
 *  COLLATINVS is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *                                                                            
 *  COLLATINVS is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *                                                                            
 *  You should have received a copy of the GNU General Public License
 *  along with COLLATINVS; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

#ifndef LIBCOLLATINUS_H
#define LIBCOLLATINUS_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <QBitArray>
#include <QMap>
#include <QMultiMap>
#include <QPair>
#include <QHash>

/*
 * TODO 
 * 1. Remplacer char Entree::pars () par int
 * Entree::pars (), ces int étant des constantes
 * const int Entree::parsNul = 0;
 * const int Entree::parsNom = 1;
 * const int Entree::parsAdj = 2;
 * const int Entree::parsPron = 3;
 * etc.
 * const int Entree::prepAcc = 18;
 * const int Entree::prepAbl = 19;
 * const int Entree::prepAccAbl = 20; 
 *
 * on pourra ensuite convertir facilement se
 * switch...case de flexio (),
 * et utiliser la propriété pars dans le module de
 * syntaxe.
 *
 * 2. Entree devient Entree, Lexicum Lexicum, Radix
 *   Radix, etc.
 */


namespace Ch
{
    /*   Fonctions de conversion  */
    void deQuant (QString *c);
    QString ini (QString c, int n); // ini  donne la chaine c tronquée de n caractères à droite
    QString jviu (QString ch);      // jviu transforme la graphie ramiste en graphie ancienne
    void minuscules (QString &f);   // toutes les lettres en minuscules sauf la première.
    int aRomano (QString R); // Fonction de conversion des chiffres romains en chiffres arabes.
    QString ote_diacritiques (QString k);
    QString deramise (QString k);
    const QString consonnes = "bcdfgjklmnpqrstvxz";
    const QString voyelles = QString::fromUtf8 ("a\u0101\u0103e\u0113\u0115i\u012b\u012do\u014d\u014fu\u016b\u016dy\u0233\u045e");
    const QString longues = QString::fromUtf8 ("\\x0101\\x0113\\x012b\\x014d\\x016b\u045e");
    const QString aaq = QString::fromUtf8 ("\u0101dc,\u0101df,\u0101dg,\u0101dl,\u0101dp,\u0101dq,\u0101dr,\u0101dst,\u0101dsc,\u0101dsp,"
                      "\u0101ds,\u0101dt,\u0101ps,c\u014dnl,c\u014dnm,c\u014dnp,c\u014dnr,\u0113xs,\u012bnb,\u012bnl,\u012bnm,\u012bnp,"
                      "\u012bnr,\u014dbc,\u014dbf,\u014dbp,\u014dps,s\u016bbc,s\u016bbf,s\u016bbg,s\u016bbm,s\u016bpt");
    const QString apq = QString::fromUtf8 ("\u0101cc,\u0101ff,\u0101gg,\u0101ll,\u0101pp,\u0101cq,\u0101rr,\u0101st,\u0101sc,\u0101sp,"
                       "\u0101ss,\u0101tt,\u0101bs,c\u014dll,c\u014dmm,c\u014dmp,c\u014drr,\u0113x,\u012bmb,\u012bll,\u012bmm,\u012bmp,"
                       "\u012brr,\u014dcc,\u014dff,\u014dpp,\u014dbs,s\u016bcc,s\u016bff,s\u016bgg,s\u016bmm,s\u016bbt");

    const QString aa ("adc,adf,adg,adl,adp,adq,adr,adst,adsc,adsp,"
                      "ads,adt,aps,conl,conm,conp,conr,exs,inb,inl,inm,inp,"
                      "inr,obc,obf,obp,ops,subc,subf,subg,subm,supt");
    const QString ap ("acc,aff,agg,all,app,acq,arr,ast,asc,asp,"
                      "ass,att,abs,coll,comm,comp,corr,ex,imb,ill,imm,imp,"
                      "irr,occ,off,opp,obs,succ,suff,sugg,summ,subt");
    const QStringList assimAnte = aa.split (",");
    const QStringList assimPost = ap.split (",");
    const QStringList assimAnteq = aaq.split (",");
    const QStringList assimPostq = apq.split (",");
    QString assimile (QString f, int &i);
    QString assimileq (QString f, int i);
    bool estNombre (QString s);
    // expressions rationnelles
    const QRegExp reB ("\\b");
    const QRegExp reLettres ("\\w+");
    const QRegExp reNombre ("\\d");
    const QRegExp reEspace ("\\s+");
    const QRegExp rePonct ("[\\.?!;:]");
    const QRegExp rePoncPrem ("^[\\W]+");
    const QRegExp rePoncDer ("\\W+$");
    const QRegExp reAlphas ("(\\w+)");
    const QRegExp reNonAlphas ("\\W+");
}

/* classes */

class Traits: public QObject
{
    Q_OBJECT
    private:
        QBitArray bits;
    public:
        Traits (int k, int g, int n, int d, int p, int t, int m, int v);
        virtual ~Traits ();
        QBitArray getBits ();
        QString humain ();
        int casus ();
        int genus ();
        int numerus ();
        int gradus ();
        int persona ();
        int tempus ();
        int modus ();
        int uox ();
        bool contient (Traits * t);
        /*
        QString cas ();
        QString genre ();
        QString nombre ();
        QString degre ();
        QString personne ();
        QString temps ();
        QString mode ();
        QString voix ();
        */
};

class Desinence
{
    private:
        QString gr;  // graphie
        Traits * traits; 
        QList<int> mo;      // modèle (paradigma)
        int rn;      // numéro de radical (radix_num)
        QString grq; // graphie avec quantités
    public:
        /*
         * Format d'une ligne de lemmata.fr :
         * graph|casus|genus|numerus|gradus|persona|tempus|modus|uox|paradigma|radix_num
         */
        Desinence (QString linea);
        QString graphie ();
        QList<int> mdl ();
        QString grquant (); // accesseur de grq
        QStringList modele ();
        int nr ();
        Traits * getTraits ();
        QString morpho ();
        QString doc ();
};

class Irreg;

/* classe des entrées */
class Entree: public QObject
{
    Q_OBJECT
    private:
        QString k; // canon sans quantités
        QString kq; // canon avec quantités, comme dans le dictionnaire
        QString fcq; // forme canonique entièrement mesurée
        QString kjv; // canon ramiste
        int nh; // numéro d'homonymie 
        int mdl;
        QString cf;
        QMap<int,QStringList> radq;
        QList<Irreg*> irregs;
        QMap<QString,QString*> trad;
        QString indMorph; // indications morphologiques
        QList<Entree*> adv; // entrée adj. utilisée pour les degrés d'un ou plusieurs adv. 
        // caractéristiques morpho
        bool init_neutre ();
        bool neutre;
        int nombre;
        void init_nombre ();
        bool init_deponent ();
        bool deponent;
        bool init_intrans ();
        bool intrans;
        void init_radicaux (QStringList eclats); 
        void init_quantites ();
    public:
        Entree (QString linea);
        virtual ~Entree ();
        bool egale (Entree * e);
        QString canon ();
        QString canonR (); // canon ramiste
        int numh (); // accesseur pour h
        static QString ote2 (QString k, int &h);
        QString getCf ();
        int modele ();
        char pars ();
        QStringList radicalq (int n);
        QString grmodele ();
        QString quantite ();
        QString defBulle (QString l); // l : langue
        QString definition (QString l); // l : langue
        void ajTrad (QString lang, QString * tr);
        void setAdv (Entree * e);
        void setIndMorph (QString im);
        QList<Entree*> getAdv ();
        QString * traduction (QString lang);
        QString ambrogio ();
        bool est_neutre (); 
        int getNombre ();
        bool aUnSingulier ();
        bool aUnPluriel ();
        bool est_deponent ();
        bool est_intransitif ();
        QList<Irreg*> irreguliers ();
        void ajIrr (Irreg * irr);
        QString doc ();
};

/* classe des radicaux */

class Radix
{
    private:
        Entree * e;
        int mo;    // modèle
        int num;   // numéro de radical
        bool eni;
        QString k; // canon
        QString grq;
    public:
        Radix (Entree *entree, int m, int n, QString q, bool ii=false);
        int mdl ();
        bool en_i ();
        int nr ();
        int nbl (); // nombre de langues pointées par private:e
        Entree * entree ();
        void ajouteEntree (Entree *entree);
        QString canon ();
        QString grquant (); // accesseur de grq
        QString doc ();
};   

class AnalyseMorpho: public QObject
{
    Q_OBJECT
private:
    Entree * e;
    Desinence * des;
    Traits * traits;
    QString q; // devient le seul radical (le 4 mars 2014)
    QString dq; // nécessaire pour le superlatif de l'adverbe
    QString suffixe; // le suffixe sera conservé ici
    bool db_i;
public:
    AnalyseMorpho (QString rq, Desinence * d, Entree * en, QString
                   suff="", bool ii = false);
    AnalyseMorpho (QString rq, Traits * t, Entree * en, QString ddq="");
    ~AnalyseMorpho ();
    // pour les indéclinables et la 3ème décl, la
    // forme entière est dans rq.
    Entree * entree ();
    void setSuff (QString s); // Pour les enclitiques, je dois pouvoir ajouter un suffixe après coup
    QString getD (); // pour récupérer la désinence
    void setQ (QString nq); // pour changer le radical;
    QString getQ (); // pour récupérer le radical
    QString getForm (); // Le collage radical+désinence+suffixe se fera ici
    void setUpper ();
    void assimileq (int i);
    Traits * getTraits ();
    QString humain ();
};

typedef QMultiMap<QString, AnalyseMorpho*> ListeAnalyses;

/* classe des irréguliers */
class Irreg: public QObject
{
    Q_OBJECT
    private:
        QString gr;
        QString grq;
        Entree * e;        
        Traits * traits;
        bool excl;
    public:
        Irreg (QString linea, Entree * entr);
        virtual ~Irreg ();
        Entree * entree ();        
        QString graphie ();
        QString graphieq ();
        QString morpho ();
        bool exclusif ();
        Traits * getTraits ();
        bool homomorphe (Desinence * des);
};


/* classe lexique */
class Lexicum: public QObject
{
    Q_OBJECT
    private:
        QMap <QString, QString> metae;
        bool MajPert;
        // liste d'entrées
        QString lingua; // langue courante
        QString linguaTr; // langue, nom vernaculaire complet
        Traits * bitsComp; // morpho de l'adv au comparatif
        Traits * bitsSup;  // au superlatif
        typedef QHash<QString, Entree*> c2e;
        // liste des listes d'entrées, par langue (ca, de, es, fr, gl, uk)
        // liste des entrées
        c2e entrees;
        QList<Entree*> adjAdv; // entrées d'adj utilisés pour les degrés d'un ou plusieurs adv.
        QList<Entree*> entreesCf; // entrées utlisisant la trad. d'une autre
        typedef QMultiMap<QString, Desinence> c2d;
        // liste des désinences
        c2d desinentiae;
        // liste des irréguliers
        typedef QMultiMap<QString, Irreg*> c2i;
        c2i irregulares;
        // liste des radicaux
        QMap<int,QList<int> > modelesRad;
        typedef QMultiMap<QString, Radix> c2r;
        c2r radices;
        // type liste de radicaux
        typedef QList<Radix> lr;
        typedef QPair<QRegExp,QString> Regle;
        void lemmataLege ();
        void pronominaLege ();
        void linguamLege (QString lang);
        QList<Regle> regles;
        QString voyelles;
        QString ponctPhr;
        ListeAnalyses lanalysesE (QString forme); // enclitiques
        ListeAnalyses lanalysesA (QString forme); // assimilations
        ListeAnalyses corAnalyses (QString forme); // cœur du moteur d'analyse

    public:
        Lexicum ();
        virtual ~Lexicum ();
        QMap <QString, QString> cible ();
        void changeMajPert (bool m);
        Entree *renvoi (Entree *e);  // renvoi d'entrée si la déf. commence par cf.
        Entree * entree (QString k);
        void dicLinguam (QString lang);
        QString lang ();
        QString ambrogio (Entree * e);
        void deleteAnalyses (ListeAnalyses la);
        QString radical (QString r);
        QString assimile (QString f);
        QString analyses (QString f);
        void lajoute (QString l, ListeAnalyses& la, AnalyseMorpho * am);
        ListeAnalyses lanalyses (QString forme, bool deb_phr=false);
        QStringList lemmatiseM (QString f, bool mm=true, bool deb_phr = false); // analyse morphologique, début de phrase
        QString lemmatiseTxt (QString txt, bool alpha=0, bool cumVocibus = false);
        QString par_position (QString f);
        QStringList synthA (Entree* e, int c, int n, int g, int d);
        QStringList synthPart (Entree* e, int c, int g, int n, int t, int v);
        QStringList synthN (Entree *e, int c, int n);
        QStringList synthP (Entree* e, int c, int n, int g);
        QStringList synthV (Entree* e, int p, int n, int t, int m, int v);
        QString flechis (Entree* e);
        QStringList formeq (QString forme, bool *nonTrouve, bool deb_phr=true);
        QString scandeTxt (QString texte, bool stats = false);
        QStringList frequences (QString txt);
};

bool sort_i (const QString &s1, const QString &s2);

#endif
