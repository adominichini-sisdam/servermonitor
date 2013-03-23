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

		Multi requests;
		Cleanup cleanup;
		int nbLeft;

		for(uint i=0; i< urls.size(); i++) {
			cout << i <<  " = " << urls[i] << endl;
			Easy req;
			req.setOpt(new options::Url(urls[i]));
			req.setOpt(new options::Verbose(true));
			requests.add(&req);
		}

		while(true) {
			try {
				while(!requests.perform(&nbLeft)) {};
				while(nbLeft) {
					struct timeval timeout;
					int rc;

					timeout.tv_sec = 1;
					timeout.tv_usec = 0;

					fd_set fdread;
					fd_set fdwrite;
					fd_set fdexcep;
					int maxfd;

					FD_ZERO(&fdread);
					FD_ZERO(&fdwrite);
					FD_ZERO(&fdexcep);

					requests.fdset(&fdread, &fdwrite, &fdexcep, &maxfd);
					rc = select(maxfd + 1, &fdread, &fdwrite, &fdexcep, &timeout);

					switch (rc) {
						case -1:
							nbLeft = 0;
							printf("select() returns error.\n");
							break;
						case 0:
						default:
							while (!requests.perform(&nbLeft)) {};
							break;
					}
				}

				std::cout << "NB lefts: " << nbLeft << std::endl;
			}
			catch ( curlpp::LogicError & e ) {
				std::cout << e.what() << std::endl;
			}
			catch ( curlpp::RuntimeError & e ) {
				std::cout << e.what() << std::endl;
			}
			boost::this_thread::sleep(boost::posix_time::seconds(DELAY));
		} // end while
	}
}
