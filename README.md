SimpleIni
=========
Very simple class to manage configuration file like .ini or .conf.

Introduction
============
This class allows you to easily manage configuration files with less than 10 methods.
To use, include in your project SimpleIni.cpp and SimpleIni.h.

Features
========
 - Get and Set key's values
 - Get and Set comments
 - Browse sections and keys
 - Comments identifed by ; or #
 - Removal of whitespace around sections, keys and values.
 - Don't support multi-line values.
 - Comments on the section line are lost during the save method.
 - Compile on Linux and Windows, Intel or ARM.

Portability
===========
Unit tests passed successfully on :
 - Windows Seven (CPU Intel Celeron)
 - Linux Ubuntu (CPU Intel Atom)
 - Linux Raspian on Raspberry Pi (CPU ARM)
 - Linux FunPlug on NAS DNS-320 (CPU ARM)
(Compilation directives define LINUX or WIN only necessary for colours in unit tests)

For more informations
=====================
See documentation in doc/html/index.html

Licence
=======
SimpleIni is free software : you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

SimpleIni is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with SimpleIni. If not, see http://www.gnu.org/licenses/.
