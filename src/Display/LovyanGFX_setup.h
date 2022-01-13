#ifndef LOVYANGFXTEST_DISPLAYSETTINGS_H
#define LOVYANGFXTEST_DISPLAYSETTINGS_H

#define LGFX_USE_V1
#define ARDUINO_LOLIN_D32_PRO

#include <LovyanGFX.hpp>

namespace lgfx {
class LGFX : public lgfx::LGFX_Device {

	lgfx::LOVYAN_PANEL _panel_instance;
	lgfx::Bus_SPI _bus_instance;

public:

	LGFX(void){
		{
			auto cfg = _bus_instance.config();


			cfg.spi_host = VSPI_HOST;
			cfg.spi_mode = 0;
			cfg.freq_write = LOVYAN_FREQ;
			cfg.freq_read = LOVYAN_FREQ;
			cfg.spi_3wire = false;
			cfg.use_lock = true;
			cfg.dma_channel = 1;
			cfg.pin_sclk = LOVYAN_SCK;
			cfg.pin_mosi = LOVYAN_MOSI;
			cfg.pin_miso = LOVYAN_MISO;
			cfg.pin_dc = LOVYAN_DC;

			_bus_instance.config(cfg);
			_panel_instance.setBus(&_bus_instance);
		}

		{
			auto cfg = _panel_instance.config();

			cfg.pin_cs = LOVYAN_CS;
			cfg.pin_rst = LOVYAN_RST;
			cfg.pin_busy = -1;



			cfg.memory_width = LOVYAN_WIDTH;
			cfg.memory_height = LOVYAN_HEIGHT;
			cfg.panel_width = LOVYAN_WIDTH;
			cfg.panel_height = LOVYAN_HEIGHT;
			cfg.offset_x = 0;
			cfg.offset_y = 0;
			cfg.offset_rotation = 0;
			cfg.dummy_read_pixel = 8;
			cfg.dummy_read_bits = 1;
			cfg.readable = true;
			cfg.invert = false;
			cfg.rgb_order = false;
			cfg.dlen_16bit = false;
			cfg.bus_shared = true;

			_panel_instance.config(cfg);
		}

		setPanel(&_panel_instance);
	}
};
}

#include <LGFX_TFT_eSPI.h>

#endif
