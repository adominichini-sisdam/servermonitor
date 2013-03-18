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

namespace std {

	class CurlManager {
		std::vector<string> urls;
		public:
			CurlManager();
			virtual ~CurlManager();
			void init();
			void addUrl(string url);
			void start();
	};

} // end namespace std
#endif
