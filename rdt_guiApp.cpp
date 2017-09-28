/*
	Copyright (C) 2017 Erol Yesilyurt

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, version 3 of the License.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifdef WX_PRECOMP
#include "wx_pch.h"
#endif

#include "rdt_guiApp.h"

IMPLEMENT_APP(rdt_guiApp);

bool rdt_guiApp::OnInit()
{
    frame = new rdt_guiFrame(0L);
    frame->Show();

    rdt = new radeontop::rdtop();
    if(!rdt->init_rdtop())
    {
        frame->SetStatusText(_T("Radeontop not initialized!"), 0);
        return true;
    }

    frame->rdt = rdt;
    frame->SetMenuPresent();
    frame->mSetTimerVal(500, true);


    return true;
}

