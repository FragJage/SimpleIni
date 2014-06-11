/*** LICENCE ***************************************************************************************/
/*
  SimpleIni - Simple class for configuration file like .ini

  This file is part of SimpleIni.

    SimpleIni is free software : you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    SimpleIni is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with SimpleIni.  If not, see <http://www.gnu.org/licenses/>.
*/
/***************************************************************************************************/
#include <iostream>
#include <sstream>
#include "SimpleIni.h"

using namespace std;

SimpleIni::SimpleIni(string filename)
{
    if(filename!="")
    {
        if(!Load(filename)) throw string("Unable to open the file "+filename+" in read mode.");
    }
}

SimpleIni::~SimpleIni()
{
    Free();
}

bool SimpleIni::Load(string filename)
{
    size_t pos;
    size_t pos2;
    size_t length;
    string line;
    string section;
    string key;
    string comment;
    ifstream file;
    IniLine iniLine;


    Free();
    FileName = filename;

    //*** Ouverture du fichier
    file.open(FileName.c_str(), ifstream::in);
    if(!file) return false;

    //*** Parcours du fichier
	while(getline(file, line))
    {
        line = ParasitCar(line);
        if(line.empty()) continue;
        length = line.length();

        //*** Raz
        key = "";
        iniLine.value = "";
        iniLine.comment = "";

        //*** Section ?
        if(line.at(0)=='[')
        {
            pos = line.find_first_of(']');
            if(pos==string::npos) pos = line.length();
            section = Trim(line.substr(1, pos-1));
            if(comment!="")
            {
                DescriptionMap[section][""] = comment;
                comment = "";
            }
            continue;
        }

        //*** Commentaire ?
        pos = line.find_first_of(';');
        pos2= line.find_first_of('#');
        if( (pos!=string::npos) && (pos2!=string::npos) && (pos>pos2) ) pos = pos2;
        if( (pos==string::npos) && (pos2!=string::npos) ) pos = pos2;
        if(pos!=string::npos)
        {
            if(pos>0)
            {
                iniLine.comment = line.substr(pos+1, length-pos);
                line.erase(pos, length-pos);
            }
            else
            {
                if(comment!="") comment += '\n';
                comment += line.substr(pos+1, length-pos);
                continue;
            }
        }

        //*** Valeur ?
        pos = line.find_first_of('=');
        if(pos!=string::npos)
        {
            iniLine.value = Trim(line.substr(pos+1, length-pos));
            line.erase(pos, length-pos);
        }

        //*** Mémorisation
        key = Trim(line);
        IniMap[section][key] = iniLine;
        if(comment!="")
        {
            DescriptionMap[section][key] = comment;
            comment = "";
        }

    }

    file.close();
    return true;
}

bool SimpleIni::Save()
{
    return SaveAs(FileName);
}

bool SimpleIni::SaveAs(string filename)
{
	SectionIterator itSection;
	KeyIterator itKey;
    IniLine iniLine;
	ofstream file;
	bool first = true;

	file.open(filename.c_str());
    if(!file) return false;

	for(itSection=IniMap.begin(); itSection!=IniMap.end(); ++itSection)
	{
	    if(!first) file << endl;
	    SaveDescription(itSection->first, "", file);
		if(itSection->first!="") file << "[" << itSection->first << "]" << endl;

		for(itKey=itSection->second.begin(); itKey!=itSection->second.end(); ++itKey)
        {
            SaveDescription(itSection->first, itKey->first, file);
            iniLine = itKey->second;
            if(itKey->first != "") file << itKey->first << "=" << iniLine.value;
            if(iniLine.comment != "")
            {
                if(itKey->first != "")
                    file << "\t;";
                else
                    file << "#";
                file << iniLine.comment;
            }
            file << endl;
        }
        first = false;
	}

	file.close();
	return true;
}

void SimpleIni::SaveDescription(string section, string key, ofstream &file)
{
    stringstream ss(DescriptionMap[section][key]);
    string item;
    while (std::getline(ss, item, '\n'))
    {
        file << "#" << item << endl;
    }
}

void SimpleIni::Free()
{
    IniMap.clear();
}

string SimpleIni::GetValue(string section, string key, string defaultValue)
{
	map<string, map<string, SimpleIni::IniLine> >::iterator itSection=IniMap.find(section);
	if(itSection == IniMap.end()) return defaultValue;

	map<string, SimpleIni::IniLine>::iterator itKey=itSection->second.find(key);
	if(itKey == itSection->second.end()) return defaultValue;

	return itKey->second.value;
}

void SimpleIni::SetValue(string section, string key, string value)
{
    IniLine iniLine;

	iniLine = IniMap[section][key];
	iniLine.value = value;
	IniMap[section][key] = iniLine;
}

string SimpleIni::GetComment(string section, string key)
{
	map<string, map<string, SimpleIni::IniLine> >::iterator itSection=IniMap.find(section);
	if(itSection == IniMap.end()) return "";

	map<string, SimpleIni::IniLine>::iterator itKey=itSection->second.find(key);
	if(itKey == itSection->second.end()) return "";

	return itKey->second.comment;
}

void SimpleIni::SetComment(string section, string key, string comment)
{
    IniLine iniLine;

	iniLine = IniMap[section][key];
	iniLine.comment = comment;
	IniMap[section][key] = iniLine;
}

void SimpleIni::DeleteKey(string section, string key)
{
    IniMap[section].erase(key);
}

SimpleIni::SectionIterator SimpleIni::beginSection()
{
    return IniMap.begin();
}

SimpleIni::SectionIterator SimpleIni::endSection()
{
    return IniMap.end();
}

SimpleIni::KeyIterator SimpleIni::beginKey(std::string section)
{
   	map<string, map<string, SimpleIni::IniLine> >::iterator itSection=IniMap.find(section);
	if(itSection == IniMap.end())
    {
        itSection = IniMap.begin();
        return itSection->second.end();
    }

    return itSection->second.begin();
}

SimpleIni::KeyIterator SimpleIni::endKey(std::string section)
{
   	map<string, map<string, SimpleIni::IniLine> >::iterator itSection=IniMap.find(section);
	if(itSection == IniMap.end()) itSection = IniMap.begin();

    return itSection->second.end();
}

string SimpleIni::ParasitCar(string str)
{
    size_t fin=str.size();

    if(fin<1) return str;

    if(str.at(fin-1)<' ') fin--;

    return str.substr(0, fin);
}

string SimpleIni::Trim(string str)
{
    size_t deb=0;
    size_t fin=str.size();
    char   chr;

    while(deb<fin)
    {
        chr = str.at(deb);
        if( (chr!=' ') && (chr!='\t') ) break;
        deb++;
    }

    while(fin>0)
    {
        chr = str.at(fin-1);
        if( (chr!=' ') && (chr!='\t') ) break;
        fin--;
    }

    return str.substr(deb, fin-deb);
}
