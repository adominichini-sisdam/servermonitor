/*
 * ServerModel.cpp
 *
 *  Created on: Mar 17, 2013
 *      Author: alexander
 */

#include "ServerModel.h"

namespace std {

	ServerModel::ServerModel() {
		add(col_id);
		add(col_name);
		add(col_ip);
		add(col_time);
		add(col_ttl);
		add(col_status);
	}
	ServerModel::~ServerModel() {}
}

