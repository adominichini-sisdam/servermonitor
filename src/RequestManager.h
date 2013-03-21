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
#include "ServerModel.h"

namespace std {

	class RequestManager {

		public:
			RequestManager();
			virtual ~RequestManager();
			void init();
			void addUrl(string url);
			void startLoopThread();
			static int DELAY;
			Glib::RefPtr<Gtk::ListStore> refListStore;
			ServerModel* pServerModel;

		private:
			std::vector<string> urls;
			void loop();
	};
}
#endif
