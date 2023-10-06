//
// sfmenu.cpp
//
// mt32-pi - A baremetal MIDI synthesizer for Raspberry Pi
// Copyright (C) 2020-2023 Dale Whinham <daleyo@gmail.com>
//
// This file is part of mt32-pi.
//
// mt32-pi is free software: you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the Free Software
// Foundation, either version 3 of the License, or (at your option) any later
// version.
//
// mt32-pi is distributed in the hope that it will be useful, but WITHOUT ANY
// WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
// FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
// details.
//
// You should have received a copy of the GNU General Public License along with
// mt32-pi. If not, see <http://www.gnu.org/licenses/>.
//

#include <circle/timer.h>
#include <circle/util.h>

#include <cstdio>

#include "lcd/ui.h"
#include "lcd/sfmenu.h"

#include "synth/synthbase.h"
#include "utility.h"


CSFMenu::CSFMenu()
    : m_ActiveMenu(TMenu::Program),
      m_nChannel(0),
      m_nPosition(1),
      m_nNewPosition(0),
      m_bStart(false),
      m_bStop(false),
      m_nTimeOut(5000)
{
}

bool CSFMenu::Update(CLCD& LCD, CSynthBase& Synth, unsigned int nTicks)
{

    if (m_nPosition != m_nNewPosition  || m_bStart)
    {
        m_nPosition = m_nNewPosition;
        m_bStart = false;

        // TODO: Update screen
        LCD.Clear(false);
        LCD.DrawChar('M', 0, 0);
        LCD.DrawChar('E', 0, 1);
        LCD.DrawChar('N', 0, 2);
        LCD.DrawChar('U', 0, 3);
        LCD.Flip();


    }
    if (m_bStop)
    {
        m_bStop=false;
        return false;
    }
    return true;
}

void CSFMenu::MoveUp(void)
{
    m_nNewPosition++;
}

void CSFMenu::MoveDown(void)
{
    m_nNewPosition--;
}

void CSFMenu::Select(void)
{
    // TODO: Send midi message to fluid synth
    Stop();
}

void CSFMenu::Start(void)
{
    m_bStart = true;
}
void CSFMenu::Stop(void)
{
    m_bStop = true;
}

