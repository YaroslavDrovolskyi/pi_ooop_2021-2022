#include "AuxFunctions.h"
#include <ctime>

/*!
	Function that allow to get current date and time as string

	\returns string in a format: "dd-mm-yyyy_hh-mm-ss"
*/
std::string getCurrentTimeAsString() {
	time_t time = std::time(nullptr);
	tm local_time;
	localtime_s(&local_time, &time);
	char buffer[80];

	strftime(buffer, sizeof(buffer), "%d-%m-%Y_%H-%M-%S", &local_time);

	return std::string(buffer);
}