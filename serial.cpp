#ifdef SERIAL_UNIT_TEST
#include "serial.h"
#include <iostream>

using namespace riftia;

int main(int argc, char* argv[])
{
	boost::asio::io_service io_service;
	serial s(io_service);
	s.init_serial("/dev/ttyACM0", 9600);
	s.start_main_loop();

    return 0;
}

#endif
