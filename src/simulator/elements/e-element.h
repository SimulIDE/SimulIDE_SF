/***************************************************************************
 *   Copyright (C) 2012 by santiago González                               *
 *   santigoro@gmail.com                                                   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, see <http://www.gnu.org/licenses/>.  *
 *                                                                         *
 ***************************************************************************/

#ifndef EELEMENT_H
#define EELEMENT_H

#include "simulator.h"

class ePin;

class eElement
{
    public:
        eElement(string id=0);
        virtual ~eElement();

        virtual void initEpins();
        virtual void setNumEpins( int n );

        virtual void initialize(){;}
        virtual void stamp(){;}

        virtual void updateStep(){;}
        virtual void setVChanged(){;}

        virtual ePin* getEpin( int pin );
        virtual ePin* getEpin( QString pinName );
        
        virtual void setEpin( int num, ePin* pin );

        string getId(){ return m_elmId; }

        static const double cero_doub = 1e-20;
        static const double high_imp = 1e20;
        static const double digital_high = 5.0;
        static const double digital_low = 0.0;
        static const double digital_threshold = 2.5;


    protected:
        std::vector<ePin*> m_ePin;

        string m_elmId;
};

#endif

