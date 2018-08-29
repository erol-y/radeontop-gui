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

#ifndef CONF_H_INCLUDED
#define CONF_H_INCLUDED

#ifndef _WX_STDPATHS_H_
    #include <wx/stdpaths.h>
#endif // _WX_STDPATHS_H_

#ifndef   _FILECONF_H
    #include <wx/fileconf.h>
#endif // _FILECONF_H

#include "confdef.h"
#include <iostream>


class ConfigFile: public wxFileConfig
{
public:
    static ConfigFile * OnInit(const wxString& _name = wxEmptyString, const wxString& _path = wxEmptyString);

    void OnExit()
        { delete this; }

    static ConfigFile * GetConfigFile();

private:
    ConfigFile( const wxString& );
    ~ConfigFile();

public:
    template <typename T>
    bool cfgWrite( ConfKeyEnums key, T value )
    {
        wxString s( ConfKeys[key] );
        return Write( s, value );
    }

    template <typename T>
    bool cfgRead(ConfKeyEnums key, T* value, const T& defVal) const
    {
        wxString s( ConfKeys[key] );
        return Read( s, value, defVal );
    }

    template <typename T>
    bool cfgRead(ConfKeyEnums key, T* value) const
    {
        wxString s( ConfKeys[key] );
        return Read( s, value );
    }

};

#endif // CONF_H_INCLUDED
