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

#include "confdef.h"

class ConfigFile: public wxFileConfig
{
public:
    static ConfigFile * OnInit(const wxString& _name = wxEmptyString, const wxString& _path = wxEmptyString);

    void OnExit()
        { delete this; }

    static ConfigFile * GetConfigFile();

    bool ResetConf()
        { return DeleteAll(); }

    bool bSave;

private:
    ConfigFile( const wxString& );
    ~ConfigFile();

public:
    template <typename T>
    bool cfgWrite( ConfKeyEnums key, T value )
    {
        if(bSave)
        {
            wxString s( ConfKeys[key] );
            return Write( s, value );
        }
        return false;
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
