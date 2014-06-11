/***********************************************************************************************/
/**                                                                                           **/
/** EXAMPLE 1                                                                                 **/
/**                                                                                           **/
/** Read 3 key's value in example1.ini                                                        **/
/** Lire les 3 valeurs dans example1.ini                                                      **/
/**                                                                                           **/
/***********************************************************************************************/

/***********************************************************************************************/
/**                                                                                           **/
/** example1.ini                                                                              **/
/**                                                                                           **/
/** [SGBD]                                                                                    **/
/** Host=192.168.0.1	;IP du serveur SQL                                                    **/
/** PortTCP=3307		#Port du serveur SQL                                                  **/
/** BDD=MyExample		;Nom de la base                                                       **/
/**                                                                                           **/
/***********************************************************************************************/

#include <iostream>
#include "SimpleIni.h"

using namespace std;

int main()
{
    SimpleIni ini;
    string host;
    int port;


    ini.Load("examples\\example1.ini");
    host = ini.GetValue<string>("SGBD", "Host", "127.0.0.1");
    port = ini.GetValue<int>("SGBD", "PortTCP", 3306);
    cout << "SGBD Host : " << host << endl;
    cout << "Port TCP : " << port << endl;
    cout << "Database : " << ini.GetValue<string>("SGBD", "BDD", "MyBDD") << endl;

    return 0;
}
