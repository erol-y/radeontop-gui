/*
	Copyright (C) 2018 Erol Yesilyurt

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

#ifndef CONFDEF_H_INCLUDED
#define CONFDEF_H_INCLUDED


#ifndef _WX_STDPATHS_H_
    #include <wx/stdpaths.h>
#endif // _WX_STDPATHS_H_

#ifndef   _FILECONF_H
    #include <wx/fileconf.h>
#endif // _FILECONF_H


#define CONFIGFILE_DEF_NAME wxT("settings.ini")
#define CONFIGFILE_DEF_PATH wxStandardPaths::Get().GetUserLocalDataDir() + wxFileName::GetPathSeparator()

enum ConfKeyEnums
    {
        GEN_UPDATE_INTERVAL = 0,    //int
        GEN_SIZER_X,                //int
        GEN_SIZER_Y,                //int
        GPU_ITEM_GUI,               //bool
        GPU_ITEM_EE,                // "
        GPU_ITEM_VGT,
        GPU_ITEM_TA,
        GPU_ITEM_TC,
        GPU_ITEM_SX,
        GPU_ITEM_SH,
        GPU_ITEM_SPI,
        GPU_ITEM_SMX,
        GPU_ITEM_SC,
        GPU_ITEM_PA,
        GPU_ITEM_DB,
        GPU_ITEM_CB,
        GPU_ITEM_CR,
        GPU_ITEM_VRAM,
        GPU_ITEM_GTT,
        CPU_GUI_LIMIT_COUNT,        //int
        CPU_GUI_SHOW_AVARAGE,       //bool
        CPU_GUI_SIZER_X,            //int
        CPU_GUI_SIZER_Y,            //int
        PWR_GUI_SIZER_X,            //int
        PWR_GUI_SIZER_Y             //int
    };

static const wchar_t* ConfKeys[] = {wxT("GENERAL/update-interval"),
                                    wxT("GENERAL/frameX"),
                                    wxT("GENERAL/frameY"),
                                    wxT("GPU/gui"),
                                    wxT("GPU/ee"),
                                    wxT("GPU/vgt"),
                                    wxT("GPU/ta"),
                                    wxT("GPU/tc"),
                                    wxT("GPU/sx"),
                                    wxT("GPU/sh"),
                                    wxT("GPU/spi"),
                                    wxT("GPU/smx"),
                                    wxT("GPU/sc"),
                                    wxT("GPU/pa"),
                                    wxT("GPU/db"),
                                    wxT("GPU/cb"),
                                    wxT("GPU/cr"),
                                    wxT("GPU/vram"),
                                    wxT("GPU/gtt"),
                                    wxT("CPU/limit-count"),
                                    wxT("CPU/show-avarage"),
                                    wxT("CPU/frameX"),
                                    wxT("CPU/frameY"),
                                    wxT("POWER/frameX"),
                                    wxT("POWER/frameY")
                                    };

#endif // CONFDEF_H_INCLUDED
