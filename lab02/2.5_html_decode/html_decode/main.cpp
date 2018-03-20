#include <iostream>
#include <iterator>

#include "HTMLDecode.hpp"

bool HtmlDecode(std::istream& input, std::ostream& output)
{
	std::string html(std::istreambuf_iterator<char>(input), {});

	output << HtmlDecode(html) << std::endl;

	return static_cast<bool>(output);
}

int main()
{
	bool ok = HtmlDecode(std::cin, std::cout);

	if (!ok)
	{
		std::cerr << "Error occured\n";
		return 1;
	}

	return 0;
}
