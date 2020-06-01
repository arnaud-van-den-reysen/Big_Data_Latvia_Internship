
#include <zmq.hpp>
#include <string>
#include <iostream>
#ifndef _WIN32
#include <unistd.h>
#else
#include <windows.h>
#include <ctime>

#define sleep(n)    Sleep(n)
#endif

std::string createJson(double value) {
	std::chrono::nanoseconds tstamp = std::chrono::duration_cast< std::chrono::nanoseconds >(std::chrono::system_clock::now().time_since_epoch());
	std::string json = "{ "; //Json Opening
	json += "\"time\": " + std::to_string(tstamp.count()) + ", "; // timestamp
	json += "\"value\": " + std::to_string(value) + "";
	json += "}"; //Json closing
	return json;
}

int main () {
	zmq::context_t context (1); //thread(s)
	zmq::socket_t publisher (context, ZMQ_PUB);
	publisher.bind ("tcp://*:6667");

	while (true) {

		for(int i = 0; i<10;i++){//marche avec 100 valeurs
			//init message zmq de taille 3
			zmq::message_t topic (3);
			//copie de la chaine dans le message
			memcpy (topic.data(), "fps", 3 );

			//publication du message
			publisher.send (topic,ZMQ_SNDMORE);


			int valeur = rand() % 11 + 400;
			std::string json = createJson(valeur);
			zmq::message_t message(json.length());
			char *c = const_cast<char*>(json.c_str());
			memcpy (message.data (), c, json.length());
			publisher.send (message,0);
			std::cout << valeur << std::endl;

		}

		sleep (1);
	}
	return 0;
}
