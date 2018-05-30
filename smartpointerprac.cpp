#include <iostream>
#include <memory>

using namespace std;

int main()
{
	cin.tie(NULL);
	ios_base::sync_with_stdio(false);

	int* sp = nullptr;
	unique_ptr<int> sp(new int(10));

	for (int i = 0; i < 10; ++i)
		cin >> sp[i];

	for (size_t i = 0; i < 10; i++)
		cout << sp[i] << ' ';
	cout << '\n';
	return 0;
}