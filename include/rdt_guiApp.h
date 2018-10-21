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

#ifndef RDT_GUIAPP_H
#define RDT_GUIAPP_H

#include <wx/app.h>
#include "conf.h"
#include "rdt_guiMain.h"
#include "radeontop.h"

class rdt_guiApp : public wxApp
{
    private:
        class rdt_guiFrame * frame;

    public:
        virtual bool OnInit();
        virtual int OnExit();

};

#endif // RDT_GUIAPP_H
