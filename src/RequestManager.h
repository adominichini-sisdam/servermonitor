/*
 * RequestManager.h
 *
 *  Created on: Mar 17, 2013
 *      Author: alexander
 */

#ifndef REQUESTMANAGER_H_
#define REQUESTMANAGER_H_
#include <iostream>
#include <vector>
#include <gtkmm.h>

namespace std {

	class CurlManager {
		std::vector<string> urls;
		public:
			CurlManager();
			virtual ~CurlManager();
			void init();
			void addUrl(string url);
			void startLoop(Glib::RefPtr<Gtk::TextBuffer> buffer);
	};

} // end namespace std
#endif
