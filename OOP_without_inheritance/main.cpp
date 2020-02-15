#include "object_t.h"

#include <iostream>


class my_class_t {

};

void draw(const my_class_t&, std::ostream& out, std::size_t position)
{
	std::cout << std::string(position, ' ') << "my_class!" << std::endl;
}


int main()
{
	history h{ 1 };
	current(h).emplace_back(0);
	current(h).emplace_back(std::string{ "Hello!" });

	draw(current(h), std::cout, 0);
	std::cout << "-----------------------------------------------------" << std::endl;

	commit(h);

	current(h)[0] = object_t(42.5);
	current(h)[1] = object_t(std::string{ "World" });
	current(h).emplace_back(current(h));
	current(h).emplace_back(my_class_t{});

	draw(current(h), std::cout, 0);
	std::cout << "-----------------------------------------------------" << std::endl;

	undo(h);

	draw(current(h), std::cout, 0);

	return 0;
}
