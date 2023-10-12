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

#include <fluidsynth.h>

#include "lcd/ui.h"
#include "lcd/sfmenu.h"

#include "synth/synthbase.h"
#include "synth/soundfontsynth.h"
#include "utility.h"


CSFMenu::CSFMenu()
    : m_ActiveMenu(TMenu::Program),
      m_nChannel(0),
      m_nPosition(1),
      m_nNewPosition(0),
      m_bStart(false),
      m_bStop(false),
      m_bSelect(false),
      m_nTimeOut(5000)
{
}

bool CSFMenu::Update(CLCD& LCD, CSynthBase& Synth, unsigned int nTicks)
{
    static u8 start = 0;

    if (m_nPosition != m_nNewPosition  || m_bStart)
    {

        m_nPosition = m_nNewPosition;
        m_bStart = false;

        if (m_nPosition < -100) m_nPosition = 127;
        if (m_nPosition < 0) m_nPosition = 0;

        if (m_nPosition > (start + 3))
            start = m_nPosition - 3;
        if (m_nNewPosition < start)
            start = m_nPosition;
        //u8 maxlength = 16;
        //char* tempname[maxlength];

        LCD.Clear(false);

        for (u8 i=0; i<4; i++)
        {
            // MLI-Possibly
            LCD.Print(dynamic_cast<CSoundFontSynth&>(Synth).GetPresetName(start+i), 1, i, true, false);
            // if selected position, display something special
            if ((i+start) == m_nPosition)
                LCD.DrawChar('>',0,i);
        }

        LCD.Flip();

        m_nNewPosition = m_nPosition;
    }
    if (m_bSelect)
    {
        m_bSelect=false;
        Synth.HandleMIDIShortMessage(m_nPosition<<8 | 0xC0);
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
void CSFMenu::Move(s8 delta)
{
    m_nNewPosition += delta;
}

void CSFMenu::Select(void)
{
    m_bSelect = true;
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

