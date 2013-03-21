/*
 * ServerModel.h
 *
 *  Created on: Mar 17, 2013
 *      Author: alexander
 */
// Galicia: 0810 122 7472 9 15 int1
#ifndef SERVERMODEL_H_
#define SERVERMODEL_H_

#include <gtkmm.h>

namespace std {

class ServerModel: public Gtk::TreeModelColumnRecord {
public:
	ServerModel();
	virtual ~ServerModel();

	Gtk::TreeModelColumn<uint> col_id; 				// 0
	Gtk::TreeModelColumn<Glib::ustring> col_name; 	// 1
	Gtk::TreeModelColumn<Glib::ustring> col_ip; 	// 2
	Gtk::TreeModelColumn<Glib::ustring> col_time; 	// 3
	Gtk::TreeModelColumn<Glib::ustring> col_ttl; 	// 4
	Gtk::TreeModelColumn<Glib::ustring> col_status;// 5
};

} /* namespace std */
#endif /* SERVERMODEL_H_ */
