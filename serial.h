#ifndef RIFTIA_SERIAL_H
#define RIFTIA_SERIAL_H
//serial:20140313
#include <iostream>
#include <vector>
#include <string>
#include <boost/asio.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>

namespace riftia
{

void print_bytes(const std::vector<unsigned char>& bytes){
	for(std::size_t i = 0; i < bytes.size(); ++i){
		std::cout << static_cast<unsigned int>(bytes[i]) << " ";
	}
	std::cout << "\n";
}

class serial{
public:
    serial(boost::asio::io_service& io_service) : 
		io_service_(io_service), serial_port_(io_service){}

	void init_serial(const std::string& port_name, unsigned int baud_rate){
		serial_port_.open(port_name.c_str());
		serial_port_.set_option(boost::asio::serial_port_base::baud_rate(baud_rate));
	}

	void start_main_loop(){
			boost::asio::streambuf buf;
			std::string line;
		while(true){
			std::cout << "command?: " << std::flush;
			std::string line;
			std::getline(std::cin, line);
			std::vector<std::string> token_list;
			boost::split(token_list, line, boost::is_any_of(" "));
			try{
				if(token_list[0] == "move"){
					std::vector<unsigned char> message;
					message.push_back(0x10);
					for(std::size_t i = 0; i < 4; ++i){
						int di = boost::lexical_cast<int>(token_list.at(i+1));
						message.push_back((di>>8)&0xff);
						message.push_back((di)&0xff);
					}
					print_bytes(message);
					boost::asio::write(serial_port_, boost::asio::buffer(message));
				}
				else {
					throw std::invalid_argument("command not found");
				}

				//result
				{
					std::vector<unsigned char> buf(2);
					boost::asio::read(serial_port_, boost::asio::buffer(buf));
					print_bytes(buf);
					if(buf[1] != 0){
						throw std::runtime_error("result failed");
					}
				}

				//complete
				{
					std::vector<unsigned char> buf(1);
					boost::asio::read(serial_port_, boost::asio::buffer(buf));
					print_bytes(buf);
				}

			}
			catch(std::exception& e){
				std::cout << e.what() << std::endl;
			}

		}
	}

private:
	boost::asio::io_service& io_service_;
	boost::asio::serial_port serial_port_; 

};
}

#endif //RIFTIA_SERIAL_H
