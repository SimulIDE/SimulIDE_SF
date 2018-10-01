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

/*
  modules.h
  The base class for modules is defined here.
  Include this file into yours for creating custom modules.
 */

#ifndef __MODULES_H__
#define __MODULES_H__

#include <cstdlib>
#include <cstring>
#include <list>
#include <string>
#include <map>
#include <vector>
#include <assert.h>

#include "gpsim_object.h"
#include "gpsim_classes.h"
//#include "symbol.h"

class Module;
class Module_Types;
class Processor;
class IOPIN;
class Value;
class Package;

typedef  Module * (*Module_FPTR)();
typedef  Module_Types * (*Module_Types_FPTR)();


enum SIMULATION_MODES
{
  eSM_INITIAL,
  eSM_STOPPED,
  eSM_RUNNING,
  eSM_SLEEPING,
  eSM_SINGLE_STEPPING,
  eSM_STEPPING_OVER,
  eSM_RUNNING_OVER
};


/*
 * interface is a Module class member variable in gpsim,
 * in WIN32 Platform SDK it is a macro, defined in BaseTypes.h
 * the WIN32 Platform SDK definition should be undefined
 */

#ifdef interface
#undef interface
#endif

//------------------------------------------------------------------------
//
/// Module - Base class for all gpsim behavior models.

class Module : public gpsimObject
{
    public:

      Package  *package;                // A package for the module
      //ModuleInterface *interface;       // An interface to the module.
      SIMULATION_MODES simulation_mode; // describes the simulation state for this module

      /// I/O pin specific
      virtual int get_pin_count();
      virtual string &get_pin_name(uint pin_number);
      virtual int get_pin_state(uint pin_number);
      virtual IOPIN *get_pin(uint pin_number);
      virtual void assign_pin(uint pin_number, IOPIN *pin);
      virtual void create_pkg(uint number_of_pins);
      virtual double get_Vdd() { return Vdd; }
      virtual void set_Vdd(double v) { Vdd = v; }

      /// Symbols
      /// Each module has its own symbol table. The global symbol
      /// table can access this table too.
      /*SymbolTable_t & getSymbolTable() { return mSymbolTable;}
      int addSymbol(gpsimObject *, string *AliasedName=0);
      gpsimObject *findSymbol(const string &);
      int removeSymbol(gpsimObject *);
      int removeSymbol(const string &);
      int deleteSymbol(const string &);
      int deleteSymbol(gpsimObject *);*/

      /// Registers - mostly processors, but can apply to complex modules
      virtual uint register_mask () const { return 0xff;}
      virtual uint register_size () const { return 1;}

      /// Reset
      virtual void reset(RESET_TYPE r);

      /// Version
      virtual char *get_version() { return version;}

      /// gui
      /// The simulation engine doesn't know anything about the gui.
      /// However, the set_widget and get_widget provide a mechanism
      /// for the gui to associate a pointer with a module.
      virtual void set_widget(void * a_widget) {widget = a_widget;}
      virtual void *get_widget() {return widget;}

      /// cli
      /// Modules can have gpsim CLI scripts associated with them.
      /// add_command will add a single CLI command to a script
      void add_command(string &script_name, string &command);

      /// run_script will pass a script to the gpsim CLI. This script
      /// executes immediately (i.e. it'll execute before any commands
      /// that may already be queued).
      void run_script(string &script_name);

      const char *type(void) { return module_type.c_str(); }
      void set_module_type(string type) { module_type = type; }

      Module(const char *_name=0, const char *desc=0);
      virtual ~Module();

      /// Functions to support actual hardware
      virtual bool isHardwareOnline() { return true; }

    private:
      void *widget;   // GtkWidget * that is put in the breadboard.
      string module_type;

    protected:
      double	Vdd;
      // Derived modules should assign more reasonable values for this.
      char *version;
      //SymbolTable_t mSymbolTable;
};

class Module_Types
{
    public:

      const char *names[2];
      Module * (*module_constructor) (const char *module_name);
};

#endif // __MODULES_H__
