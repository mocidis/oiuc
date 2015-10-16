#include "oiuc-config.h"
OIUCConfig* OIUCConfig::_oiuc_config=0;
OIUCConfig* OIUCConfig::getOIUCConfig() {
	if (_oiuc_config == NULL) {
		_oiuc_config = new OIUCConfig();	
	}
	return _oiuc_config;
}
OIUCConfig::OIUCConfig() {
	asterisk_ip = "127.0.0.1";
	port_connect_asterisk = 1111;
	arbiter_ip = "127.0.0.1";
	port_sendto_arbiter = 6789;
	port_oiuc_listen = 9876;
	oiuc_description = "OIUC-DESC-DF"; 
	speaker_volume = 0.5;
	microphone_volume = 0.5;
}
/**************ADD and SET FUNCTIONS*****/
void OIUCConfig::setAsteriskIP(QString value) {
	asterisk_ip = value;
}
void OIUCConfig::setPortAsterisk(int value) {
	port_connect_asterisk = value;
}
void OIUCConfig::setArbiterIP(QString value ) {
	arbiter_ip = value;
}
void OIUCConfig::setPortSendToArbiter(int value) {
	port_sendto_arbiter = value;
}
void OIUCConfig::setPortOIUCListen(int value) {
	port_oiuc_listen = value;
}
void OIUCConfig::setOIUCDescription(QString value) {
	oiuc_description = value;
}
void OIUCConfig::setSpeakerVolume(double value) {
	speaker_volume = value;
}
void OIUCConfig::setMicrophoneVolume(double value) {
	microphone_volume = value;
}
/**************GET FUNCTIONS*************/
QString OIUCConfig::getAsteriskIP() {
	return asterisk_ip;
}
int OIUCConfig::getPortAsterisk() {
	return port_connect_asterisk;
}
QString OIUCConfig::getArbiterIP() {
	return arbiter_ip;
}
int OIUCConfig::getPortSendToArbiter() {
	return port_sendto_arbiter;
}
int OIUCConfig::getPortOIUCListen() {
	return port_oiuc_listen;
}
QString OIUCConfig::getOIUCDescription() {
	return oiuc_description;
}
double OIUCConfig::getSpeakerVolume() {
	return speaker_volume;
}
double OIUCConfig::getMicrophoneVolume() {
	return microphone_volume;
}
