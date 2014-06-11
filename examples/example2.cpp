/***********************************************************************************************/
/**                                                                                           **/
/** EXAMPLE 2                                                                                 **/
/**                                                                                           **/
/** Browse sections and keys                                                                  **/
/** Parcourir des sections et des clés                                                        **/
/**                                                                                           **/
/***********************************************************************************************/

/***********************************************************************************************/
/**                                                                                           **/
/** example2.ini                                                                              **/
/**                                                                                           **/
/**  [section1]                                                                               **/
/**  cle10=valeur10                                                                           **/
/**  cle11=valeur11                                                                           **/
/**                                                                                           **/
/**  [section2]                                                                               **/
/**  cle20=valeur20                                                                           **/
/**  cle22=valeur22                                                                           **/
/**  cle24=valeur24                                                                           **/
/**                                                                                           **/
/***********************************************************************************************/

#include <iostream>
#include "SimpleIni.h"

using namespace std;


int main()
{
    SimpleIni ini;
    SimpleIni::SectionIterator itSection;
    SimpleIni::KeyIterator itKey;


    if(!ini.Load("examples\\example2.ini"))
    {
        cout << "Impossible de charger example2.ini." << endl;
        return -1;
    }

    cout << "Liste des sections" << endl;
    for (itSection = ini.beginSection(); itSection != ini.endSection(); ++itSection)
    {
        cout << itSection->first << endl;
    }
    cout << endl;

    cout << "Liste des cles de la section2" << endl;
    for (itKey = ini.beginKey("section2"); itKey != ini.endKey("section2"); ++itKey)
    {
        cout << itKey->first << endl;
    }

    return 0;
}
