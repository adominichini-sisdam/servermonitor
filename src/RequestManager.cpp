/*
 * RequestManager.cpp
 *
 *  Created on: Mar 17, 2013
 *      Author: alexander
 */
#include "RequestManager.h"
#include <stdlib.h>
#include <string>
#include <sstream>
#include <iostream>
// sudo apt-get install libcurl4-openssl-dev
// https://code.google.com/p/curlpp/
#include <gtkmm.h>
#include <boost/thread.hpp>
#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include "ServerModel.h"

namespace std {

	RequestManager::RequestManager() {}
	RequestManager::~RequestManager() {}

	int RequestManager::DELAY = 1;

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

		while(true) {
			for(std::vector<int>::size_type i=0; i!=urls.size(); i++) {

				curlpp::Easy request;
				ostringstream os;
//				string pos = (i);
//				pos += ":" + pos;
				Gtk::TreePath path = Gtk::TreePath(i);
				Gtk::TreeIter iter = refListStore->get_iter(path);
				Gtk::TreeModel::Row row = *iter;

				try {
					request.setOpt(new curlpp::options::Url(urls[i]));
					curlpp::options::WriteStream ws(&os);
					request.setOpt(ws);
					request.perform();

					if(os.rdbuf()->in_avail() != 0) {
						cout << "[ OK ] " << urls[i] << endl;
						row[pServerModel->col_status] = "alive";
					}
				}
				catch( curlpp::RuntimeError &e ) {
					cout << "*** ERROR : " << e.what() << " " << urls[i] << " ***"<< endl;
					row[pServerModel->col_status] = "down";
					continue;
				}
			}
			boost::this_thread::sleep(boost::posix_time::seconds(DELAY));
		}
	}
}
