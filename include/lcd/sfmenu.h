//
// sfmenu.h
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

#ifndef _sfmenu_h
#define _sfmenu_h


#include <circle/types.h>

#include "lcd/barchars.h"
#include "lcd/lcd.h"

class CSynthBase;

class CSFMenu
{
public:
	enum class TMenu
	{
		SoundFont,
		Program,
	};

	CSFMenu();

	bool Update(CLCD& LCD, CSynthBase& Synth, unsigned int nTicks);
    void MoveUp(void);
    void MoveDown(void);
    void Select(void);
    void Start(void);
    void Stop(void);

private:

    // private methods

    // temporary but constant (TODO: Get the from the proper place)
	static constexpr unsigned LCDWitdh = 128;
	static constexpr unsigned LCDHeight = 64;


    // private properties
    TMenu m_ActiveMenu;
    u8 m_nChannel;
    u8 m_nPosition;
    u8 m_nNewPosition;
    bool m_bStart;
    bool m_bStop;
    unsigned int m_nTimeOut;
    unsigned int m_nLastActionTime;



};


#endif
