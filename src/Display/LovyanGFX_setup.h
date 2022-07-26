#ifndef LOVYANGFXTEST_DISPLAYSETTINGS_H
#define LOVYANGFXTEST_DISPLAYSETTINGS_H

#define LGFX_USE_V1
#define ARDUINO_LOLIN_D32_PRO

#include <LovyanGFX.hpp>

#ifndef LOVYAN_HOST
#define LOVYAN_HOST VSPI_HOST
#endif

namespace lgfx {
class LGFX : public lgfx::LGFX_Device {
private:

	Panel_Device* panel = nullptr;
	Bus_SPI* bus = nullptr;

public:

	LGFX(void){
#ifndef LOVYAN_MANUAL
		bus = new lgfx::Bus_SPI();
		panel = new lgfx::LOVYAN_PANEL();

		{
			auto cfg = bus->config();


			cfg.spi_host = LOVYAN_HOST;
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

			bus->config(cfg);
			panel->setBus(bus);
		}

		{
			auto cfg = panel->config();

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

#ifdef LOVYAN_BGR
			cfg.rgb_order = true;
#endif

			panel->config(cfg);
		}

		setPanel(panel);
#endif
	}
};
}

#include <LGFX_TFT_eSPI.h>

#endif
