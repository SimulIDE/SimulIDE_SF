/***************************************************************************
 *   Copyright (C) 2018 by santiago González                               *
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

#include <math.h>   // fabs(x,y)
#include <QDebug>

#include "e-volt_reg.h"
#include "circuit.h"

eVoltReg::eVoltReg( std::string id )
    : eResistor( id )
{
    m_ePin.resize(3);
}
eVoltReg::~eVoltReg()
{ 
}

void eVoltReg::initialize()
{
    eResistor::setRes( 1e-6 );
    
    int exp = Circuit::self()->nlAcc();
    m_accuracy = 1/pow(10,exp);
    
    m_lastOut = 0;
    if( m_ePin[0]->isConnected() ) m_ePin[0]->getEnode()->addToNoLinList(this);
    if( m_ePin[1]->isConnected() ) m_ePin[1]->getEnode()->addToNoLinList(this);
    if( m_ePin[2]->isConnected() ) m_ePin[2]->getEnode()->addToNoLinList(this);
    
    eResistor::initialize();
}

void eVoltReg::setVChanged() 
{
    double inVolt = m_ePin[0]->getVolt();
    
    m_voltPos = inVolt;
    if( m_voltPos > 0.7 ) m_voltPos -= 0.7;
    else                  m_voltPos = 0;
    
    double outVolt = m_ePin[2]->getVolt()+m_vRef;
    
    if     ( outVolt > m_voltPos ) outVolt = m_voltPos;
    else if( outVolt < m_voltNeg ) outVolt = m_voltNeg;
    //qDebug()<< outVolt <<m_lastOut;

    if( fabs(outVolt-m_lastOut)<m_accuracy ) return;
    
    m_lastOut = outVolt;
    
    double current = (inVolt-outVolt)/m_resist;
    m_ePin[0]->stampCurrent( current );
    m_ePin[1]->stampCurrent(-current );
}

