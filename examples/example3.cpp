/***********************************************************************************************/
/**                                                                                           **/
/** EXAMPLE 3                                                                                 **/
/**                                                                                           **/
/** Modify and save a configuration file                                                      **/
/** Modifier et enregistrer un fichier de configuration                                       **/
/**                                                                                           **/
/***********************************************************************************************/

/***********************************************************************************************/
/**                                                                                           **/
/** example3.ini                                                                              **/
/**                                                                                           **/
/**  [sectionA]                                                                               **/
/**  cleA1=valeurA1                                                                           **/
/**  cleA2=valeurA2                                                                           **/
/**                                                                                           **/
/***********************************************************************************************/

#include <iostream>
#include "SimpleIni.h"

using namespace std;


int main()
{
    SimpleIni ini;


    if(!ini.Load("examples\\example3.ini"))
    {
        cout << "Impossible de charger example3.ini." << endl;
        return -1;
    }

    ini.SetValue<string>("sectionA", "cleA2", "valeurA2-bis");  //Modify existing value
    ini.SetValue<string>("sectionB", "cleB1", "valeurB1");      //Add section and key with value
    ini.SetValue<float>("sectionB", "cleB2", 0.5);              //Add key with value

    if(!ini.SaveAs("examples\\example3bis.ini"))
    {
        cout << "Impossible de sauver example3bis.ini." << endl;
        return -1;
    }

    cout << "Le fichier de configuration : example3bis.ini." << endl;

    return 0;
}
