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

#include "rdt_guiMain.h"

static radeontop::rdtop * rdt;

QDialog::QDialog(wxWindow * parent)
    : QueryDialog(parent)
{
    this->rdtFrame = (rdt_guiFrame *) parent;
    rdt = rdtFrame->GetRadeonHandler();
    wxLog::SetActiveTarget(new wxLogTextCtrl(QtextCtrl1));

    wxLogMessage("Bus: %s", rdt->get_str_busid());
    wxLogMessage("%s", rdt->get_str_devid());
    wxLogMessage("Path: %s",rdt->get_str_devpath());
    wxLogMessage("Driver: %s  %u.%u.%u\n",
                 rdt->get_drm_name(),
                 rdtFrame->GetDrmVerInfo().version_major,
                 rdtFrame->GetDrmVerInfo().version_minor,
                 rdtFrame->GetDrmVerInfo().version_patchlevel);

    if(rdt != NULL && !rdt->haserror())
    {
        if (rdt->get_driver_enum() == radeontop::_AmdGpuDriver::radeon)
        {
            QchoiceAMD->Hide();
            bSizer2->Remove((wxSizer*) QchoiceAMD);
        }
        else if(rdt->get_driver_enum() == radeontop::_AmdGpuDriver::amdgpu)
        {
            QchoiceRadeon->Hide();
        }
    }
    else
    {
        QchoiceAMD->Hide();
        QchoiceRadeon->Enable(false);
    }
}

QDialog::~QDialog()
{

}

void QDialog::OnQueryClose(wxCloseEvent& event)
{
    rdtFrame->DestroyDialogWindow(this);
    wxUnusedVar(event);
}

void QDialog::OnQChoiceR(wxCommandEvent& event)
{
    if (rdt->get_driver_enum() == radeontop::_AmdGpuDriver::radeon)
    {
        unsigned long val = 0;
        signed long sval = 0;

        switch(QchoiceRadeon->GetSelection())
        {
        case 1: //CLOCK_CRYSTAL_FREQ
            {
                if(!rdt->GetQueryR(RADEON_INFO_CLOCK_CRYSTAL_FREQ, &val))
                {
                    wxLogMessage("Crystal Frequency: %u Hz (%u kHz)", (unsigned)val, unsigned (val/1000));
                }
                //else Error message
                break;
            }
        case 2: //NUM_TILE_PIPES
            {
                if(!rdt->GetQueryR(RADEON_INFO_NUM_TILE_PIPES, &val))
                    wxLogMessage("Tile Pipes count: %u", (unsigned)val);
                //else
                break;
            }
        case 3: //RADEON_INFO_MAX_SE
            {
                if(!rdt->GetQueryR(RADEON_INFO_MAX_SE, &val))
                    wxLogMessage("Number of Shader Engines: %u", (unsigned)val);
                //else
                break;
            }
        case 4: //MAX_SH_PER_SE
            {
                if(!rdt->GetQueryR(RADEON_INFO_MAX_SH_PER_SE, &val))
                    wxLogMessage("Number of shaders per engine: %u", (unsigned)val);

                break;
            }
        case 5: //MAX_SCLK
            {
                if(!rdt->GetQueryR(RADEON_INFO_MAX_SCLK, &val))
                    wxLogMessage("Maximum source clock: %u kHz (%u mHz)", (unsigned)val, unsigned(val/1000));

                break;
            }
        case 6: //VCE_FW_VERSION
            {
                if(!rdt->GetQueryR(RADEON_INFO_VCE_FW_VERSION, &val))
                    wxLogMessage("VCE firmware version: %u", (unsigned)val);

                break;
            }
        case 7: //VCE_FB_VERSION
            {
                if(!rdt->GetQueryR(RADEON_INFO_VCE_FB_VERSION, &val))
                    wxLogMessage("VCE FB Version: %u", (unsigned)val);

                break;
            }
        case 8: //ACTIVE_CU_COUNT
            {
                if(!rdt->GetQueryR(RADEON_INFO_ACTIVE_CU_COUNT, &val))
                    wxLogMessage("Active Compute Unit count: %u", (unsigned)val);

                break;
            }
        case 9: //CURRENT_GPU_TEMP
            {
                if(!rdt->GetQueryR(RADEON_INFO_CURRENT_GPU_TEMP, &sval))
                    wxLogMessage("GPU Temperature: %d", (signed)sval);

                break;
            }
        default:
            break;
        }
    }

    wxUnusedVar(event);
}

void QDialog::OnQChoiceA(wxCommandEvent& event)
{
#ifdef ENABLE_AMDGPU
    class radeontop::m_amdgpu_info * amd = new radeontop::m_amdgpu_info(rdt->get_drm_handle());

    /**TODO: Edit labels as readable as much */
    switch(QchoiceAMD->GetSelection())
    {
        case 1: //SENSORS
            {
                struct radeontop::m_amdgpu_sensor * sensor = new radeontop::m_amdgpu_sensor();
                QtextCtrl1->Clear();
                amd->ReadSensor(sensor, 0);
#ifdef AMDGPU_INFO_SENSOR_STABLE_PSTATE_GFX_SCLK
                wxLogMessage("GPU:%d\nMEM:%d\nTemp:%d\nLoad:%d\nPower:%d\nVDDNB:%d\nVDDGFX:%d\npstate_sclk:%d\npstate_mclk:%d\n",
                             sensor->gfx_sclk,
                             sensor->gfx_mclk,
                             sensor->gpu_temp /100, /* get temperature in millidegrees C */
                             sensor->gpu_load,
                             sensor->gpu_avg_power,
                             sensor->vddnb,
                             sensor->vddgfx,
                             sensor->pstate_sclk,
                             sensor->pstate_mclk);

#else
                wxLogMessage("\nGPU:%d\nMEM:%d\nTemp:%d\nLoad:%d\nPower:%d\nVDDNB:%d\nVDDGFX:%d\n",
                             sensor->gfx_sclk,
                             sensor->gfx_mclk,
                             sensor->gpu_temp /100, /* get temperature in millidegrees C */
                             sensor->gpu_load,
                             sensor->gpu_avg_power,
                             sensor->vddnb,
                             sensor->vddgfx);
#endif // AMDGPU_INFO_SENSOR_STABLE_PSTATE_GFX_SCLK

                delete sensor;
            } break;
        case 2: //HARDWARE
            {
                radeontop::amdgpu_dev_info info;
                QtextCtrl1->Clear();
                wxString w(">>>>> Device Info: <<<<<\n");

                if(!amd->GetDevInfo(&info))
                {
                    wxLogMessage("Could not get device info!");
                    break;
                }

                w << wxString::Format("Chip Revision: %.2X , External Revision: %.2X\n",
                                      info.chip_rev, info.external_rev);

                w << wxString::Format("num_cu_per_sh: %d\n", info.num_cu_per_sh);

                w << wxString::Format("Shader Arrays per Engine: %d , Shader Engines: %d\n",
                                      info.num_shader_engines, info.num_shader_arrays_per_engine);

                w << wxString::Format("cu_active_number: %d\n", info.cu_active_number);
                w << wxString::Format("gpu_counter_freq: %dMHz\n", (int)info.gpu_counter_freq / 1000);
                w << wxString::Format("max_engine_clock: %dMHz\n", (int)info.max_engine_clock / 1000);
                w << wxString::Format("max_memory_clock: %dMHz\n", (int)info.max_memory_clock / 1000);

                std::string s("???");
                switch(info.vram_type)
                {
                case VRAM_TYPE_UNKNOWN: { s.assign("UNKNOWN"); } break;
                case VRAM_TYPE_GDDR1: { s.assign("GDDR1"); } break;
                case VRAM_TYPE_DDR2: { s.assign("DDR2"); } break;
                case VRAM_TYPE_GDDR3: { s.assign("GDDR3"); } break;
                case VRAM_TYPE_GDDR4: { s.assign("GDDR4"); } break;
                case VRAM_TYPE_GDDR5: { s.assign("GDDR5"); } break;
                case VRAM_TYPE_HBM: { s.assign("HBM"); } break;
                case VRAM_TYPE_DDR3: { s.assign("DDR3"); } break;
                }
                w << wxString::Format("VRAM Type: \"%s\"\n", s.c_str());

                w << wxString::Format("vram_bit_width: %d\n", info.vram_bit_width);

                w << wxString::Format("ce_ram_size: %dKb\n", (unsigned)info.ce_ram_size / 1024);
                w << wxString::Format("num_tcc_blocks: %d\n", info.num_tcc_blocks);
                w << wxString::Format("gs_vgt_table_depth: %d\n", info.gs_vgt_table_depth);
                w << wxString::Format("gs_prim_buffer_depth: %d\n", info.gs_prim_buffer_depth);
                w << wxString::Format("max_gs_waves_per_vgt: %d", info.max_gs_waves_per_vgt);
                wxLogMessage(w);

            } break;
        case 3: // UVD
            {
                radeontop::amdgpu_uvd_handles uvd;
                memset(&uvd, 0, sizeof(uvd));
                radeontop::amdgpu_uvd_handles * p = &uvd;
                amd->GetQueryA(AMDGPU_INFO_NUM_HANDLES, (unsigned long long*)p, sizeof(uvd));
                QtextCtrl1->Clear();

                if(p == NULL)
                    break;

                wxLogMessage("UVD: Used:%d -- Max:%d\n", uvd.uvd_used_handles, uvd.uvd_max_handles);

            } break;
        case 4: // VCE
            {
                unsigned char c;
                c = amd->GetClockTable().size();
                wxString s;
                QtextCtrl1->Clear();
                s << wxString::Format("VCE table entry count: %d\n", c);
                for(unsigned char i = 0; i < c; ++i)
                    s << wxString::Format("\t%u --> sclk:%u  eclk:%u  mclk:%u\n",
                                          i+1,
                                          amd->GetClockTable()[i].sclk,
                                          amd->GetClockTable()[i].eclk,
                                          amd->GetClockTable()[i].mclk);

                wxLogMessage(s);

            } break;

    }

    delete amd;
#endif // ENABLE_AMDGPU
    wxUnusedVar(event);
}
