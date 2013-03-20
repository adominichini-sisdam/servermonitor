/*
 * ServerModel.h
 *
 *  Created on: Mar 17, 2013
 *      Author: alexander
 */

#ifndef SERVERMODEL_H_
#define SERVERMODEL_H_

#include <gtkmm.h>

namespace std {

class ServerModel: public Gtk::TreeModelColumnRecord {
public:
	ServerModel();
	virtual ~ServerModel();

	Gtk::TreeModelColumn<Glib::ustring> col_name;
	Gtk::TreeModelColumn<Glib::ustring> col_ip;
	Gtk::TreeModelColumn<Glib::ustring> col_time;
	Gtk::TreeModelColumn<Glib::ustring> col_ttl;
	Gtk::TreeModelColumn<Glib::ustring> col_status;
};

} /* namespace std */
#endif /* SERVERMODEL_H_ */
