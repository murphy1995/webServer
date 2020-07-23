#include <boost/operators.hpp>

class Timestamp
{
public:
	Timestamp();
	~Timestamp();
private:
	int64_t microSecondsSinceEpoch_;
	
};

int main(int argc, char const *argv[])
{
	static_assert(sizeof(Timestamp) == sizeof(int64_t),
              "Timestamp is same size as int64_t");
	//static_assert(sizeof(int) == sizeof(short));
	return 0;
}