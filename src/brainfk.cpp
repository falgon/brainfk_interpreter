#include<srook/brainfk/brainfk.hpp>

template<class... T>
constexpr auto make_array(T&&... ts) -> std::array<std::decay_t<srook::First_t<T...>>,sizeof...(ts)>
{
	return std::array<srook::First_t<T...>,sizeof...(ts)>{{std::forward<T>(ts)...}};
}

int main(const int argc,const char* argv[])
{
	using namespace std::string_literals;
	if(argc<2)return -1;

	const auto brainfuck=make_array(">"s,"<"s,"+"s,"-"s,"."s,","s,"["s,"]"s);
	srook::brainfk_syntax<std::string,unsigned char> bksy(brainfuck);

	const auto& status=bksy.file_open(argv[1]);
	if(status==boost::none)return -1;

	bksy.analyze();
	bksy.exec();
}
