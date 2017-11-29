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

#include <math.h>
#include <QDebug>

#include "e-inbus.h"

eInBus::eInBus( std::string id )
    : eLogicDevice( id )
{
}
eInBus::~eInBus()
{ 
}

void eInBus::initialize()
{
    eNode* enode = m_input[0]->getEpin()->getEnode();
    if( enode ) enode->addToChangedFast(this);

    eLogicDevice::initialize();
}

void eInBus::setVChanged()
{
    double volt = m_input[0]->getVolt();

    int address = volt*m_maxAddr/m_maxVolt;

    for( int i=0; i<m_numOutputs; i++ )
    {
        //qDebug() << "eInBus::setVChanged" << i << (address & 1);
        eLogicDevice::setOut( i, address & 1 );
        address >>= 1;

    }
    //qDebug() << "eInBus::setVChanged"<<volt << address<<(volt*m_maxAddr/m_maxVolt)<<"\n";
}
