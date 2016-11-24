#include<fstream>
#include<sstream>
#include<experimental/optional>
#include<array>
#include<iostream>
#include<cstdio>

namespace{
	typedef unsigned char byte;
	constexpr unsigned int BUFFER_SIZE=300000;
}

std::experimental::optional<std::string> file_open(const char* file_name)
{
	std::ifstream ifs(file_name,std::ios::in);
	if(ifs.fail())return {};
	std::ostringstream os;
	os<<ifs.rdbuf();
	return os.str();
}

int main(const int argc,const char* argv[])
{
	if(argc<2)return -1;
	auto fl=file_open(argv[1]);
	if(fl==std::experimental::nullopt)return -1;

	std::array<byte,BUFFER_SIZE> buff{};
	std::size_t index=0,buff_ptr=0,loop_b=0;

	for(; index<(*fl).size(); ++index){
		switch((*fl)[index]){
			case '>': ++buff_ptr; break;
			case '<': --buff_ptr; break;
			case '+': ++buff[buff_ptr]; break;
			case '-': --buff[buff_ptr]; break;
			case '.': std::cout<<buff[buff_ptr]; break;
			case ',': buff[buff_ptr]=std::getchar(); break;
			case '[':
				if(buff[buff_ptr]==0)
					for(++index; loop_b>0 || (*fl)[index]!=']'; ++index){
						if((*fl)[index]=='[')++loop_b;
						if((*fl)[index]==']')--loop_b;
					}
				break;
			case ']':
				if(buff[buff_ptr]!=0){
					for(--index; loop_b>0 || (*fl)[index]!='['; --index){
						if((*fl)[index]==']')++loop_b;
						if((*fl)[index]=='[')--loop_b;
					}
					--index;
				}
				break;
		}
	}
}
