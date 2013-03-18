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
		cout << "* CurlManager::addUrl "<< url <<"..." << endl;
		urls.push_back(url);
	}

	void CurlManager::start() {

		try {
			cout << curlpp::options::Url("http://www.google.com") << endl;
		}
		catch(curlpp::RuntimeError &e) {
			cout << e.what() << endl;
		}
		catch(curlpp::LogicError &e) {
			cout << e.what() << endl;
		}
	}
}
