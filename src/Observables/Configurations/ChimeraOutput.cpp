/*
 * ChimeraOutput.cpp
 *
 *  Created on: 22/Jan/2014
 *      Author: C. Matek
 */

#include <sstream>
#include "ChimeraOutput.h"

const std::string strtypes[] = { "ALA", "GLY", "CYS", "TYR", "ARG", "PHE", "LYS", "SER", "PRO", "VAL", "ASN", "ASP", "CYX", "HSP", "HSD", "MET", "LEU" };
const std::string chimera_colours[] = { "sandy brown", "blue", "red", "green", "purple", "dark gray", "yellow", "orange", "deep pink", "magenta", "sienna", "goldenrod", "gray", "plum", "olive drab", "dark red", "steel blue", "sandy brown" };

ChimeraOutput::ChimeraOutput() :
				Configuration() {
	_colour_by_seq = false;
}

ChimeraOutput::~ChimeraOutput() {

}

void ChimeraOutput::get_settings(input_file &my_inp, input_file &sim_inp) {
	Configuration::get_settings(my_inp, sim_inp);
	int tmp;
	if(getInputBoolAsInt(&my_inp, "colour_by_sequence", &tmp, 0) == KEY_FOUND) _colour_by_seq = (bool) tmp;
}

std::string ChimeraOutput::_headers(llint step) {
	std::stringstream headers;

	headers << "set bg_color white\n~bond #0\n";

	return headers.str();
}

std::string ChimeraOutput::_configuration(llint step) {
	std::stringstream conf;
	//conf.precision(15);
	this->_fill_strands_cdm();

	for(auto it = this->_visible_particles.begin(); it != this->_visible_particles.end(); it++) {
		char buf[128];
		BaseParticle *p = _config_info->particles()[*it];
		sprintf(buf, "bond #0:%i\n", p->get_index());
		conf << buf;
	}

	for(auto it = this->_visible_particles.begin(); it != this->_visible_particles.end(); it++) {
		BaseParticle *p = _config_info->particles()[*it];
		if(p->n5 != P_VIRTUAL) {
			BaseParticle *q = p->n5;
			if(this->_visible_particles.find(q->get_index()) != this->_visible_particles.end()) {
				char buf[128];
				sprintf(buf, "bond #0:%d.A,%d.A\n", p->get_index(), q->get_index());
				conf << buf;
			}
		}
	}

	for(int i = 0; i < 17; ++i) {
		char buf0[128];
		sprintf(buf0, "color %s #0:%s\n", chimera_colours[i].c_str(), strtypes[i].c_str());
		conf << buf0;
		if(_colour_by_seq) {
			char buf[512];
			sprintf(buf, "col cyan #0:%s@O\ncol coral #0:%s@S\ncol yellow #0:%s@K\ncol cornflower blue #0:%s@P\n", strtypes[i].c_str(), strtypes[i].c_str(), strtypes[i].c_str(), strtypes[i].c_str());
			conf << buf;
		}
		else {
			char buf[512];
			sprintf(buf, "col deep sky blue #0:%s@P\ncol deep sky blue #0:%s@O\ncol deep sky blue #0:%s@S\ncol deep sky blue #0:%s@K\n", strtypes[i].c_str(), strtypes[i].c_str(), strtypes[i].c_str(), strtypes[i].c_str());
			conf << buf;
		}
		char buf2[512];
		sprintf(buf2, "bondcolor %s #0:%s\n", chimera_colours[i].c_str(), strtypes[i].c_str());
		conf << buf2;
	}

	conf << "aniso scale 0.75 smoothing 4" << std::endl << "setattr m stickScale 0.6 #0" << std::endl;

	return conf.str();
}
