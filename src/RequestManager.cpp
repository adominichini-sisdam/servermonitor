/*
 * RequestManager.cpp
 *
 *  Created on: Mar 17, 2013
 *      Author: alexander
 */
#include <stdlib.h>
#include <string>
#include <sstream>
#include <iostream>
#include <gtkmm.h>
#include <boost/thread.hpp>
#include <boost/lexical_cast.hpp>
#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Multi.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/Exception.hpp>
#include "RequestManager.h"
#include "ServerModel.h"


namespace std {

	RequestManager::RequestManager() {
		pServerModel = 0;
	}
	RequestManager::~RequestManager() {}

	int RequestManager::DELAY = 3;

	void RequestManager::init() {
		cout << "[ CurlManager::init ]" << endl;
	}

	void RequestManager::addUrl(string url) {
		urls.push_back(url);
	}

	void RequestManager::startLoopThread() {
		boost::thread th(boost::bind(&RequestManager::loop, this));
	}

	void RequestManager::loop() {
		using namespace curlpp;

		Gtk::TreeIter iter;
		Gtk::TreeModel::Row row;
		Glib::ustring status;
		Glib::ustring path;
		Cleanup cleanup;
		Easy req;
		ostringstream os;
		options::WriteStream ws(&os);
		bool success;

		while(true) {

			for(uint i=0; i< urls.size(); i++) {
				path = boost::lexical_cast<string>(i);
				iter = refListStore->get_iter(path);
				row = *iter;
				req.setOpt(new options::Url(urls[i]));
				req.setOpt(ws);

				try {
					req.perform();
					success = true;
				}
				catch (curlpp::RuntimeError &e) {
					success = false;
					std::cout << e.what() << std::endl;
				}

				if(success) { status = "alive"; }
				else { status = "down"; }
				row.set_value(pServerModel->col_status, status);
			}

			boost::this_thread::sleep(boost::posix_time::seconds(DELAY));
		}
	}
}
