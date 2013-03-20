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
				try {
					curlpp::Easy request;
					ostringstream os;

					request.setOpt(new curlpp::options::Url(urls[i]));
					curlpp::options::WriteStream ws(&os);
					request.setOpt(ws);
					request.perform();

					if(os.rdbuf()->in_avail() != 0) {
//						string s = buffer->get_text() + urls[i] + " [ OK ]\n";
//						buffer->set_text(s);
						cout << "[ OK ] " << urls[i] << endl;

					}
				}
				catch( curlpp::RuntimeError &e ) {
					cout << "*** ERROR : " << e.what() << " " << urls[i] << " ***"<< endl;
//					buffer->set_text(buffer->get_text() + urls[i] + " [FAIL]\n");
					continue;
				}
			}
			boost::this_thread::sleep(boost::posix_time::seconds(DELAY));
		}
	}

	void RequestManager::setBuffer(Glib::RefPtr<Gtk::TextBuffer> b) {
		buffer = b;
	}
	Glib::RefPtr<Gtk::TextBuffer> RequestManager::getBuffer() {
		return buffer;
	}
}
