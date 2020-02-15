#include "object_t.h"


void draw(const document& x, std::ostream& out, std::size_t position)
{
	out << std::string(position, ' ') << "<document>" << std::endl;
	for (const auto& e : x) draw(e, out, position + 2);
	out << std::string(position, ' ') << "</document>" << std::endl;
}

void commit(history& x) { assert(!x.empty()); x.push_back(x.back()); }
void undo(history& x) { assert(!x.empty()); x.pop_back(); }
document& current(history& x) { assert(!x.empty()); return x.back(); }
