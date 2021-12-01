#include "Color.h"

Color C_RGB(uint8_t r, uint8_t g, uint8_t b){
	return (((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3));
}

Color C_HEX(uint32_t hex){
	return C_RGB(
			(hex >> 16) & 0xFF,
			(hex >> 8) & 0xFF,
			hex & 0xFF
	);
}

uint32_t HSVtoRGB888(HSV hsv){
	double      hh, p, q, t, ff;
	long        i;
	uint32_t out;
	double r, g, b;

	if(hsv.s <= 0.0) {       // < is bogus, just shuts up warnings
		r = hsv.v;
		g = hsv.v;
		b = hsv.v;
	}else{
		hh = (double)(hsv.h) * 2.0;
		if(hh >= 360.0) hh = 0.0;
		hh /= 60.0;
		i = (long)hh;
		ff = hh - i;
		p = hsv.v * (1.0 - hsv.s);
		q = hsv.v * (1.0 - (hsv.s * ff));
		t = hsv.v * (1.0 - (hsv.s * (1.0 - ff)));

		switch(i){
			case 0:
				r = hsv.v;
				g = t;
				b = p;
				break;
			case 1:
				r = q;
				g = hsv.v;
				b = p;
				break;
			case 2:
				r = p;
				g = hsv.v;
				b = t;
				break;

			case 3:
				r = p;
				g = q;
				b = hsv.v;
				break;
			case 4:
				r = t;
				g = p;
				b = hsv.v;
				break;
			case 5:
			default:
				r = hsv.v;
				g = p;
				b = q;
				break;
		}
	}
	out = (((uint32_t)(r * 255.0) & 0xff) << 16) + (((uint32_t)(g * 255.0) & 0xff) << 8) + ((uint32_t)(b * 255.0) & 0xff);

	return out;
}

Color HSVtoRGB565(HSV hsv){
	uint32_t out = HSVtoRGB888(hsv);
	return C_HEX(out);
}

