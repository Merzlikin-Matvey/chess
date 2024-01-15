#include <iostream>

using namespace std;

class position {
public:
	string pos;
	bool active = true;

	position& up() {
		if (active) {
			if (pos[1] == '8') {
				active = false;
			}
			else {
				pos[1] = static_cast<char>(pos[1] + 1);
			}
		}
		return *this;
	}

	friend ostream& operator<<(ostream& os, const position& pos) {
		os << pos;
		return os;
	}
};

int main() {
	position pos;
	pos.pos = "e2";
	pos.up();
	cout << pos;
}