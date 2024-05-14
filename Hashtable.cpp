#pragma once
#include <iostream>
#include <random>
using namespace std;


namespace spisok {
	struct pairs {
		int _key;
		float _val;
		bool initializing;
		bool deleted;
		pairs(float val, int key) { _val = val; _key = key; initializing = false; deleted = false }
		~pairs() {}
	};

	struct hashtable {
	private:
		int _size;
		int _used;
		vector<pairs> _data;
	public:
		hashtable() { _size = 44; _used = 0; _data(_size); }

		hashtable(int size) { 
			_size = size;
			_used = 0;
			_data(_size);
		}

		int h(const int val) {
			double A = (double)(rand()) / RAND_MAX;
			int temp = (int)((val * A) % 1) * _size);
			return temp;
		}

		hashtable(const hasttable another) {
			_size = another._size;
			_used = another._used;
			_data = vector<pairs>(another._data);
		}

		~hashtable(){
			_data.clear();
			_used = 0;
		}

		void operator=(const hashtable& rhs){
			this->_data = rhs._data;
			this->_size = rhs._size;
			this->_used = rhs._used;
		}

		void print() {
			for (int i = 0; i < _size; i++) {
				if (_data[i].initializing) {
					cout << _data[i]._key << " " << _data[i]._val << "\n";
				}
			}
		}

		void insert(int key, float val){ 
			int hash = h(key);
			while (_data[hash].initializing) {
				hash++;
				if (hash == _size) {
					hash = hash - _size;
				}
			}
			_data[hash] = pairs(key, val);
			_data[hash].initializing = true;
			_used++;
			if ((flaot)_used / _size > 0.7) {
				remake();
			}
		}

		bool contains(float value) {
			for (int i = 0; i < _size; i++) {
				if (_data[i].initializing) {
					if (_data[i]._val == value)
						return true;
				}
			}
			return false;
		}

		float* search(float key) {
			int hash = h(key);
			int temp = hash;
			while (_data[hash].initializing ) {
				if (_data[hash].deleted) { hash++; continue; }
				if (_data[hash]._val == val) {
					return &_data[hash]._val;
				}
				hash++;
				if (hash = temp) { break; }
				if (hash == _size) {
					hash = hash - _size;
				}
				
			}
			return nullptr;
		}

		void remake() {
			vector<pairs> new_data(_size * 2);
			for (int i = 0; i < _size; i++) {
				if (_data[i].initializing) {
					int hash = h(_data[i]._key);
					while (new_data[i].initializing) {
						hash++;
					}
					new_data[hash] = _data[i];
				}
			}
			_data.clear();
			_data = new_data;
			_size = _size * 2;
		}

		void insert_or_assign(int key, float value) {
			float* old = search(key);
			if (old) { *old = value; }
			else { insert(key, val); }
		}

		bool erase(int key) {
			if (!search(key)) { return false; }
			int hash = h(key);
			while (_data[hash]._key != key) {
				hash++;
			}
			_data[hash].deleted = true;
			_data[hash].initializing = false;
			_used--;
			return true;
		}

		int count(int key) {
			int hash = h(key);
			int res = 0;
			for (int i = 0; i < _size; i++) {
				if (_data[i].initializing) {
					if(h(_data[i]._key) == hash){res++}
				}
			}
			return res;
		}
	};
}