
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

/*
std::string createJson(double x, double y, double z, int id) {
	std::chrono::milliseconds tstamp = std::chrono::duration_cast< std::chrono::milliseconds >(std::chrono::system_clock::now().time_since_epoch());
	std::string json = "{ "; //Json Opening
	json += "\"id\": " + std::to_string(id) + ", ";
	json += "\"tstamp\": " + std::to_string(tstamp.count()) + ", "; // timestamp
	json += "\"data\": { "; //Data opening
	json += "\"x\": " + std::to_string(x) + "";
	//json += "\"y\": " + std::to_string(y) + "";
	//json += "\"z\": " + std::to_string(z);
	json += "} "; //Data closing
	json += "}"; //Json closing
	return json;
}
*/

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
	publisher.bind ("tcp://*:6666");

	while (true) {
/*
		//valeur
		double valeur = rand() % 11 + 40;
		std::cout << valeur << std::endl;

		std::string json = createJson(valeur,0,0,i++);
		//std::cout << json << std::endl;

		//message
		zmq::message_t message(json.length());

		std::cout << json << std::endl;
		char *c = const_cast<char*>(json.c_str());

		memcpy (message.data (), c, json.length());

		publisher.send (message);
*/
/*
		//timestamp
		std::chrono::nanoseconds tstamp = std::chrono::duration_cast< std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch());
		//convertion tstamp en string
		std::string bateau = std::to_string(tstamp.count());
		std::cout << bateau << std::endl;
		//convertion en chaine de caractere
		char *charette = const_cast<char*>(bateau.c_str());
		//init message zmq de la taille de la date
		zmq::message_t fleuve (bateau.length());
		//copie de la chaine dans le message
		memcpy (fleuve.data(),charette, bateau.length() );



		//value aleatoire 40..50
		int valeur = rand() % 11 + 40;
		//convertion value en string
		std::string barque = std::to_string(valeur);
		//convertion en chaine de caractere
		char *alouette = const_cast<char*>(barque.c_str());
		std::cout << alouette << std::endl;
		//init message zmq de taille 2
		zmq::message_t riviere (2);
		//copie de la chaine dans le message
		memcpy (riviere.data(),alouette, 2 );

*/


		//zmq::message_t topic_value (5);
		//memcpy(topic_value.data(), "value",5);

		for(int i = 0; i<10;i++){//marche avec 100 valeurs
			//init message zmq de taille 3
			zmq::message_t topic (3);
			//copie de la chaine dans le message
			memcpy (topic.data(), "fps", 3 );

			//publication du message
			publisher.send (topic,ZMQ_SNDMORE);


			int valeur = rand() % 11 + 40;
			std::string json = createJson(valeur);
			zmq::message_t message(json.length());
			char *c = const_cast<char*>(json.c_str());
			memcpy (message.data (), c, json.length());
			publisher.send (message,0);
			std::cout << valeur << std::endl;

		}


/*
		char buffer[32];
		for(int i = 0;i<10;++i){

			sprintf(buffer, "Message %d\0", i + 1);
			printf("Sender: Sending (%s)\n", buffer);
			publisher.send (buffer, strlen(buffer), 0);
		}
	*/

		//zmq::message_t ocean;
		//publisher.send(ocean,ZMQ_SNDMORE);


		//publication du message timestamp
		//publisher.send (fleuve, ZMQ_SNDMORE);




		//publisher.send (topic_value,ZMQ_SNDMORE);
		//publication du message valeur
		//publisher.send (riviere,0);
		//publisher.send(ocean,0);

/*
		//valeur
		int valeur = rand() % 11 + 40;
		std::cout << valeur << std::endl;

		//temps
		time_t rawtime;
		struct tm * timeinfo;
		char buffer[80];

		time (&rawtime);
		timeinfo = localtime(&rawtime);

		strftime(buffer,sizeof(buffer),"%d-%m-%Y %I:%M:%S",timeinfo);
		std::string str(buffer);

		std::cout << str << std::endl;
		char *c = const_cast<char*>(str.c_str());

		int len = (unsigned)strlen(c);

		//message
		zmq::message_t reply (len);
		zmq::message_t message(1);

		memset (message.data (), valeur, 1);
        	memcpy (reply.data (), c, len);

		publisher.send (message, ZMQ_SNDMORE);
        	publisher.send (reply, 0);
*/

		sleep (1);
	}
	return 0;
}
