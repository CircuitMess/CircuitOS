#include "HWRevision.h"
#include <soc/efuse_reg.h>
#include <esp_efuse.h>
#include <esp_log.h>

bool HWRevision::changes = false;

uint8_t HWRevision::get(){
	return REG_GET_FIELD(EFUSE_BLK3_RDATA0_REG, EFUSE_ADC1_TP_LOW);
}

void HWRevision::write(const uint8_t value){
	const auto trimmed = value & 0b01111111;
	if(trimmed != value){
		ESP_LOGE("HWRevision", "Trimmed value doesn't match provided.");
		return;
	}

	REG_SET_FIELD(EFUSE_BLK3_WDATA0_REG, EFUSE_ADC1_TP_LOW, trimmed);
	changes = true;
}

void HWRevision::commit(){
	if(!changes){
		ESP_LOGE("HWRevision", "No changes to commit.");
		return;
	}

	esp_efuse_burn_new_values();
	esp_efuse_reset();
	changes = false;
}

void HWRevision::reset(){
	esp_efuse_reset();
	changes = false;
}
