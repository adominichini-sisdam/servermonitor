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

	class RequestManager {

		public:
			RequestManager();
			virtual ~RequestManager();
			void init();
			void addUrl(string url);
			void startLoopThread();
			static int DELAY;
			void setBuffer(Glib::RefPtr<Gtk::TextBuffer> buffer);
			Glib::RefPtr<Gtk::TextBuffer> getBuffer();


		private:
			std::vector<string> urls;
			Glib::RefPtr<Gtk::TextBuffer> buffer;
			void loop();
	};
}
#endif
