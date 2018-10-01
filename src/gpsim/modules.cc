/*
   Copyright (C) 1998,1999,2000 T. Scott Dattalo

This file is part of the libgpsim library of gpsim

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, see
<http://www.gnu.org/licenses/lgpl-2.1.html>.
*/


//#include "modules.h"

#include <stdio.h>
#include <ctype.h>
#include <errno.h>
#include <stdlib.h>
#include <string>
#include <list>
#include <vector>
#include <typeinfo>

#include "../config.h"

#ifndef _WIN32
#include <dlfcn.h>
#if !defined(_MAX_PATH)
  #define _MAX_PATH 1024
#endif

#else
#include <direct.h>
#include <windows.h>
/*
 * interface is a Module class member variable in gpsim,
 * in WIN32 Platform SDK it is a macro, defined in BaseTypes.h
 * the WIN32 Platform SDK definition should be undefined
 */
#undef interface
#endif

#include "pic-processor.h"
#include "stimuli.h"
//#include "symbol.h"
#include "value.h"
#include "packages.h"

// When a new library is loaded, all of the module types
// it supports are placed into the ModuleTypes map. This
// object is private to this file.

typedef map<string, Module_Types *> ModuleTypeInfo_t;
ModuleTypeInfo_t ModuleTypes;

/*****************************************************************************
 *
 * Module.cc
 *
 * Here's where much of the infrastructure of gpsim is defined.
 *
 * A Module is define to be something that gpsim knows how to simulate.
 * When gpsim was originally designed, a module was simple a pic processor.
 * This concept was expanded to accomodate devices like LEDs, switches,
 * LCDs and so on.
 */

Module::Module(const char *_name, const char *desc)
  : gpsimObject(_name, desc), package(0),
  simulation_mode(eSM_STOPPED), widget(0), Vdd(5.0), version(0)
{
  //xref = new XrefObject;

  /*if (_name) {
    // If there is a module symbol already with this
    // name, then print a warning before deleting.

    gpsimObject *pOldModule = globalSymbolTable().find(name());
    if (pOldModule) {
      cout << "Warning: There already is a symbol in the symbol table named " << _name << endl;
      return;
    }
  }
  globalSymbolTable().addModule(this);*/

  // Create position attribute place holders if we're not using the gui
  /*if(!get_interface().bUsingGUI()) {
    addSymbol(new Float("xpos",80.0));
    addSymbol(new Float("ypos",80.0));
  }*/
}

#if 0 // warning: 'void dumpOneSymbol(const SymbolEntry_t&)' defined but not used
static void dumpOneSymbol(const SymbolEntry_t &sym)
{
  cout << "  " << sym.second
       << " stored as " << sym.first
       << endl;
}
#endif


Module::~Module(void)
{
  //map<string ,ModuleScript *>::iterator si;

  /*for (si = m_scripts.begin();
       si != m_scripts.end();
       ++si) {
    ModuleScript *pMS = (*si).second;
    delete pMS;
  }
  m_scripts.clear();*/

  //deleteSymbol("xpos");
  //deleteSymbol("ypos");

  /*
  cout << "Stuff still in the symbol table:\n";
  mSymbolTable.ForEachSymbolTable(dumpOneSymbol);
  */
  delete package;
  //delete xref;
  package = 0;
  //xref = 0;

//  globalSymbolTable().removeModule(this);

}

void Module::reset(RESET_TYPE r)
{
  cout << " resetting module " << name() << endl;
}
/*
//-------------------------------------------------------------------
//-------------------------------------------------------------------
int Module::addSymbol(gpsimObject *pSym, string *ps_AliasedName)
{
  //return mSymbolTable.addSymbol(pSym, ps_AliasedName);
}

//-------------------------------------------------------------------
//-------------------------------------------------------------------
int Module::removeSymbol(gpsimObject *pSym)
{
  //return mSymbolTable.removeSymbol(pSym);
}

//-------------------------------------------------------------------
//-------------------------------------------------------------------
int Module::removeSymbol(const string &s)
{
  //return mSymbolTable.removeSymbol(s);
}

//-------------------------------------------------------------------
//-------------------------------------------------------------------
int Module::deleteSymbol(const string &s)
{
  //return mSymbolTable.deleteSymbol(s);
}

//-------------------------------------------------------------------
//-------------------------------------------------------------------
int Module::deleteSymbol(gpsimObject *pSym)
{
  if (!pSym) return 0;

  if (!removeSymbol(pSym)) return 0;

  delete pSym;
  return 1;
}

//-------------------------------------------------------------------
//-------------------------------------------------------------------
gpsimObject *Module::findSymbol(const string &searchString)
{
  //return mSymbolTable.findSymbol(searchString);
}*/

//-------------------------------------------------------------------
//-------------------------------------------------------------------
void Module::create_pkg(uint number_of_pins)
{
  if(package) delete package;

  package = new Package(number_of_pins);
}

void Module::assign_pin(uint pin_number, IOPIN *pin)
{
  if(package) package->assign_pin(pin_number, pin);
}

int Module::get_pin_count(void)
{
  if(package) return package->get_pin_count();

  return 0;

}

string &Module::get_pin_name(uint pin_number)
{
  static string invalid("");
  if(package) return package->get_pin_name(pin_number);
  return invalid;  //FIXME
}

int Module::get_pin_state(uint pin_number)
{
  if(package) return package->get_pin_state(pin_number);

  return 0;
}

IOPIN *Module::get_pin(uint pin_number)
{
  if(package) return package->get_pin(pin_number);

  return 0;
}
