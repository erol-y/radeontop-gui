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

#include "conf.h"

static ConfigFile * conf = NULL;

ConfigFile * ConfigFile::OnInit(const wxString& _name, const wxString& _path)
{
    wxString file;

    if(_path == wxEmptyString)
        file.append(CONFIGFILE_DEF_PATH);
    else
        file.append(_path);

    if(wxDirExists(file) == false)
        wxMkdir(file);
    //else
        //wxChmod(file, 0777);

    if(_name == wxEmptyString)
        file.append(CONFIGFILE_DEF_NAME);
    else
        file.append(_name);

    conf = new ConfigFile(file);

    //conf->SetUmask(0677);

    return conf;
}

ConfigFile::ConfigFile( const wxString& _file )
    :wxFileConfig(wxEmptyString, wxEmptyString, _file)
{
    conf = this;
    bSave = true;
    //this->SetRecordDefaults();
}

ConfigFile::~ConfigFile()
{
    conf = NULL;
}

ConfigFile * ConfigFile::GetConfigFile()
{
    return conf;
}
