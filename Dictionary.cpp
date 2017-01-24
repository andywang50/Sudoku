#include "Matrix.h"

void Dictionary::add(int key, std::vector<int> value)
{
	feasible_values_dict[key] = value;
}

void Dictionary::remove_feasible_value_from_entry(int key, int num)
{
	std::vector<int>* v_ptr = &(feasible_values_dict[key]);

	auto it = std::find(v_ptr->begin(), v_ptr->end(), num);
	if (it != v_ptr->end()) {
		v_ptr->erase(it);
	}
}

std::vector<int> Dictionary::get(int key) const
{
	std::vector<int> v = {};
	std::unordered_map<int, std::vector<int>>::const_iterator got = feasible_values_dict.find(key);
	if (got != feasible_values_dict.end())
		v = got->second;
	return v;
}

int Dictionary::get_num_guesses(int key) const
{

	return get(key).size();
}

void Dictionary::remove_all_feasible_values_from_entry(int key) {
	std::vector<int>* v_ptr = &(feasible_values_dict[key]);
	std::vector<int> v = get(key);
	for (int num : v) {
		auto it = std::find(v_ptr->begin(), v_ptr->end(), num);
		if (it != v_ptr->end()) {
			v_ptr->erase(it);
		}
	}
	return;
}

Dictionary::Dictionary() {
	feasible_values_dict = std::unordered_map<int, std::vector<int>>();
}

Dictionary::Dictionary(const Dictionary & b)
{
	feasible_values_dict = b.feasible_values_dict;
}

Dictionary & Dictionary::operator=(const Dictionary & b)
{
	feasible_values_dict = b.feasible_values_dict;
	return *this;
	// TODO: insert return statement here
}

Dictionary::~Dictionary()
{
}
