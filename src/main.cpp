//============================================================================
// Name			: ServerMonitor.cpp
// Author		: Alejandro Dominichini
// Version		: 0.1
// Copyright	: MIT License
// Date			: Mar 2013
//============================================================================
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>

// sudo apt-get install libgtkmm-2.4.dev
#include <gtkmm.h>
// sudo apt-get install libboost-all-dev
#include <boost/algorithm/string.hpp>

// Custom
#include "ServerModel.h"
#include "RequestManager.h"

using namespace std;

int main(int argc, char *argv[]) {
	cout << "=================================" << endl;
	cout << "Servers Monitor" << endl;
	system("date");
	cout << "=================================" << endl;

	Gtk::Main kit(argc, argv);
	Gtk::Window* pWindow;
	Gtk::TreeView* pServersTable;
	Gtk::TextView* pOutputView;
	Gtk::TreeModel::iterator iter;
	Gtk::TreeModel::Row row;
	Glib::RefPtr<Gtk::TextBuffer> refTextBuffer;
	Glib::RefPtr<Gtk::Builder> refBuilder;
	Glib::RefPtr<Gtk::ListStore> refListStore;

	ServerModel* pServerModel = new ServerModel;
	CurlManager* pCurlManager = new CurlManager;

	string configLine;
	ifstream config;
	vector<vector<string> > seversList;

	refBuilder = Gtk::Builder::create();

	try {
		refBuilder->add_from_file("ui/main.glade");
		refBuilder->get_widget("serversTable", pServersTable);
		refBuilder->get_widget("mainWindow", pWindow);
		refBuilder->get_widget("outputView", pOutputView);

		refTextBuffer = Gtk::TextBuffer::create();
		pOutputView->set_buffer(refTextBuffer);
		refTextBuffer->set_text(refTextBuffer->get_text() + "Reading config file...");

		// Read the config file
		config.open("config/servers.txt");

		if(config.is_open()) {
			while(config.good()) {
				getline(config, configLine);
				vector<string> strs;
				boost::split(strs, configLine, boost::is_any_of("="));
				seversList.push_back(strs);
			}
			config.close();

			// Fill the table with the config file data
			refListStore = Gtk::ListStore::create(*pServerModel);
			for(uint i =0; i < seversList.size(); i++) {
				iter = refListStore->append();
				row = *iter;
				row[pServerModel->col_name] = seversList.at(i)[0];
				row[pServerModel->col_ip] = seversList.at(i)[1];
				row[pServerModel->col_time] = "";
				row[pServerModel->col_ttl] = "";
				row[pServerModel->col_status] = 0;
			}
			pServersTable->set_model(refListStore);
			refTextBuffer->set_text(refTextBuffer->get_text() + "Done.\n");
		}
	}
	catch(const Glib::Exception& ex) {
		refTextBuffer->set_text(refTextBuffer->get_text() + "Error reading config file.\n");
		cout << ex.what() << endl;
	}

	pCurlManager->init();
	for(uint i =0; i < seversList.size(); i++) {
		pCurlManager->addUrl(seversList.at(i)[1]);
	}
	// refTextBuffer->set_text(refTextBuffer->get_text() + "Reading config file...");


//	delete *pServerModel;
//	delete pServerModel;

	pCurlManager->startLoop(refTextBuffer);
	Gtk::Main::run(*pWindow);
	return 0;
}
