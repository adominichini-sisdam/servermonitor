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
#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
namespace std {

	const long PORT = 80;

	CurlManager::CurlManager() {}
	CurlManager::~CurlManager() {}

	void CurlManager::init() {
		cout << "[ CurlManager::init ]" << endl;
	}

	void CurlManager::addUrl(string url) {
		urls.push_back(url);
	}

	void CurlManager::startLoop(Glib::RefPtr<Gtk::TextBuffer> buffer) {

		curlpp::Cleanup cleanup;


		for(std::vector<int>::size_type i = 0; i != this->urls.size(); i++) {
			try {
				curlpp::Easy request;
				ostringstream os;

				cout << "* Trying to reach "<< this->urls[i] << "..." << endl;

				request.setOpt(new curlpp::options::Url(this->urls[i]));
				curlpp::options::WriteStream ws(&os);
				request.setOpt(ws);
				request.perform();

				if(os.rdbuf()->in_avail() != 0) {
					string append = this->urls[i] + "\t"
							"..................[ OK ]";
					buffer->set_text(buffer->get_text() + append);
					cout << append << endl;
				}
			}
			catch( curlpp::RuntimeError &e ) {
				std::cout << e.what() << std::endl;
				continue;
	        }
		}
	}
}
