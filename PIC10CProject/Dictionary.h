#ifndef DICTIONARY_H
#define DICTIONARY_H
#include <vector>
#include <unordered_map>
/*
template <typename Container>
struct container_hash {
std::size_t operator()(Container const& c) const {
return boost::hash_range(c.begin(), c.end());

}
};
*/
class Matrix;
class Dictionary {
public:
	friend class Matrix;
	Dictionary();
	Dictionary(const Dictionary &b);
	Dictionary& operator = (const Dictionary& b);
	~Dictionary();

	void add(int key, std::vector<int> value);
	void remove_feasible_value_from_entry(int key, int num);
	std::vector<int> get(int key) const;
	int get_num_guesses(int key) const;

	void remove_all_feasible_values_from_entry(int key);

private:
	std::unordered_map<int, std::vector<int>> feasible_values_dict;

};


#endif