//TO DO : Compile multi-plateforme
#include <iostream>
#include "SimpleIni.h"

using namespace std;

#define COULEUR_VERTE 1
#define COULEUR_ROUGE 2
#define COULEUR_INVERSE 3
#define COULEUR_NORMALE 4

#ifdef WIN
#define OSSEP "\\"
#endif // WIN

#ifdef LINUX
#define OSSEP "/"
#endif // LINUX

#ifdef WIN
#include <Windows.h>
void EcrireEnCouleur(int couleur, string msg)
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    switch(couleur)
    {
        case COULEUR_VERTE  :
            SetConsoleTextAttribute(consoleHandle, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
            break;
        case COULEUR_ROUGE  :
            SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_INTENSITY);
            break;
        case COULEUR_INVERSE:
            SetConsoleTextAttribute(consoleHandle, BACKGROUND_INTENSITY | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_RED);
            break;
        case COULEUR_NORMALE:
            SetConsoleTextAttribute(consoleHandle, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
            break;
    }
    cout << msg;
}
#endif // WIN

#ifdef LINUX
void EcrireEnCouleur(int couleur, string msg)
{
    switch(couleur)
    {
        case COULEUR_VERTE  :
            printf("\033[32m");
            break;
        case COULEUR_ROUGE  :
            printf("\033[31m");
            break;
        case COULEUR_INVERSE:
            printf("\033[30;47m");
            break;
        case COULEUR_NORMALE:
            printf("\033[0m");
            break;
    }
    cout << msg;
}
#endif // LINUX

void Titre(string myTitre)
{
    string complete(60, '°');

    cout << endl;
    complete = complete.substr(0, 60-myTitre.length());
    EcrireEnCouleur(COULEUR_INVERSE, "°°° ");
    EcrireEnCouleur(COULEUR_INVERSE, myTitre);
    EcrireEnCouleur(COULEUR_INVERSE, " ");
    EcrireEnCouleur(COULEUR_INVERSE, complete);
    EcrireEnCouleur(COULEUR_NORMALE, "");
    cout << endl;
}

void Resultat(string myTest, bool myResult)
{
    cout << " - " << myTest << " : ";

    if(myResult)
        EcrireEnCouleur(COULEUR_VERTE, "OK :-)");
    else
        EcrireEnCouleur(COULEUR_ROUGE, "KO :-(");
    EcrireEnCouleur(COULEUR_NORMALE, "");
    cout << endl;
}

bool TestLoadFichierInexistant()
{
    SimpleIni ini;

    if(!ini.Load("configz.ini")) return true;
    ini.Free();
    return false;
}

bool TestLoadFichierExistant()
{
    SimpleIni ini;
    string pathFile;

    pathFile = "test";
    pathFile += OSSEP;
    pathFile += "config.ini";
    if(!ini.Load(pathFile))  return false;
    ini.Free();
    return true;
}

bool TestGetValueChaine(SimpleIni ini)
{
    return ( ini.GetValue<std::string>("section2", "cle2", "KO") == "valeur2" );
}

bool TestGetValueFloat(SimpleIni ini)
{
    float valPi = 3.14;

    return ( ini.GetValue<float>("section2", "pi", 0) == valPi );
}

bool TestGetValueInexistante(SimpleIni ini)
{
    return ( ini.GetValue<std::string>("section2", "zz", "Pas trouvé") == "Pas trouvé" );
}

bool TestSetValueModif(SimpleIni ini)
{
	ini.SetValue<std::string>("section", "cle", "NewValue");
    return (ini.GetValue<std::string>("section", "cle", "Pas trouvé")=="NewValue");
}

bool TestSetValueCreat(SimpleIni ini)
{
	ini.SetValue<std::string>("section2", "cle1", "test1");

    return (ini.GetValue<std::string>("section2", "cle1", "Pas trouvé")=="test1");
}

bool TestGetComment(SimpleIni ini)
{
    return (ini.GetComment("section2", "cle2")=="Le commentaire");
}

bool TestSetCommentCreat(SimpleIni ini)
{
    ini.SetComment("section2", "cle1", "Comm1");
    return (ini.GetComment("section2", "cle1")=="Comm1");
}

bool TestSetComment(SimpleIni ini)
{
    ini.SetComment("section2", "cle1", "Comm12");
    return (ini.GetComment("section2", "cle1")=="Comm12");
}

bool TestDeleteKey(SimpleIni ini)
{
	ini.DeleteKey("section2", "cle1");

    if (ini.GetValue<std::string>("section2", "cle1", "Pas trouvé")!="Pas trouvé") return false;
    if (ini.GetComment("section2", "cle1")!="") return false;

    return true;
}

bool TestSectionIterator(SimpleIni ini)
{
    int i=0;
    string section[]={"section","section2","section3"};

    for (SimpleIni::SectionIterator itSection = ini.beginSection(); itSection != ini.endSection(); ++itSection)
    {
        if(section[i]!=itSection->first) return false;
        i++;
    }
    return true;
}

bool TestKeyIterator(SimpleIni ini)
{
    int i=0;
    string cle[]={"cle2","pi"};

    for (SimpleIni::KeyIterator itKey = ini.beginKey("section2"); itKey != ini.endKey("section2"); ++itKey)
    {
        if(cle[i]!=itKey->first)
        {
            cout << "Lu -" << itKey->first << "-" << endl;
            cout << "At -" << cle[i] << "-" << endl;
            return false;
        }
        i++;
    }
    return true;
}

bool TestSaveAs(SimpleIni ini)
{
    SimpleIni ini2;
    SimpleIni::SectionIterator itSection;
    SimpleIni::KeyIterator itKey;
    SimpleIni::SectionIterator itSection2;
    SimpleIni::KeyIterator itKey2;
    string pathFile;

    pathFile = "test";
    pathFile += OSSEP;
    pathFile += "getset2.ini";
    remove(pathFile.c_str());
    try
    {
        ini.SaveAs(pathFile);
    }
    catch(string const& errorMsg)
    {
        return false;
    }

    try
    {
        ini2.Load(pathFile);
    }
    catch(string const& errorMsg)
    {
        return false;
    }

    itSection2 = ini2.beginSection();
    for (itSection = ini.beginSection(); itSection != ini.endSection(); ++itSection)
    {
        if(itSection2==ini2.endSection()) return false;
        if(itSection->first!=itSection2->first) return false;

        itKey2 = ini2.beginKey(itSection2->first);
        for (itKey = ini.beginKey(itSection->first); itKey != ini.endKey(itSection->first); ++itKey)
        {
            if(itKey2==ini2.endKey(itSection2->first)) return false;
            if(itKey->first!=itKey2->first) return false;
            if(itKey->second.value!=itKey2->second.value) return false;
            if(itKey->second.comment!=itKey2->second.comment) return false;
            ++itKey2;
        }
        if(itKey2!=ini2.endKey(itSection2->first)) return false;
        ++itSection2;
    }
    if(itSection2!=ini2.endSection()) return false;

    return true;
}

int main()
{
    SimpleIni ini;
    string pathFile;


    //--------------------------------------------------------------------------
    Titre("Test de la methode Load");
    Resultat("Sur un fichier inextistant",  TestLoadFichierInexistant());
    Resultat("Sur un fichier existant",     TestLoadFichierExistant());

    //--------------------------------------------------------------------------
    pathFile = "test";
    pathFile += OSSEP;
    pathFile += "getset.ini";

    if(!ini.Load(pathFile))
    {
        cerr << "Impossible de charger le fichier " << pathFile << endl;
        return -1;
    }

    //--------------------------------------------------------------------------
    Titre("Test de la methode GetValue");
    Resultat("Sur une valeur string",  TestGetValueChaine(ini));
    Resultat("Sur une valeur float",  TestGetValueFloat(ini));
    Resultat("Sur une valeur inexistante",  TestGetValueInexistante(ini));

    //--------------------------------------------------------------------------
    Titre("Test de la methode SetValue");
    Resultat("Modification d'une valeur",  TestSetValueModif(ini));
    Resultat("Creation d'une valeur",  TestSetValueCreat(ini));

    //--------------------------------------------------------------------------
    Titre("Test des methodes sur commentaire");
    Resultat("Lecture d'un commentaire",  TestGetComment(ini));
    Resultat("Ajout d'un commentaire",  TestSetCommentCreat(ini));
    Resultat("Modification d'un commentaire",  TestSetComment(ini));

    //--------------------------------------------------------------------------
    Titre("Test de la methode DeleteKey");
    Resultat("Suppression d'une cle",  TestDeleteKey(ini));

    //--------------------------------------------------------------------------
    Titre("Test des iterateurs");
    Resultat("Iterateur de section",  TestSectionIterator(ini));
    Resultat("Iterateur de cle",  TestKeyIterator(ini));

    //--------------------------------------------------------------------------
    Titre("Test de la methode SaveAs");
    Resultat("Fichier identique a l'original",  TestSaveAs(ini));

    ini.Free();

    return 0;
}
