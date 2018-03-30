#include <cstdlib>
#include <string>
#include <cassert>
#include <iostream>
#include <cmath>

#define VECTOR_POISON -99999
#define VECTOR_DEFAULT_BLOCK_SIZE 10
#define VECTOR_DEFAULT_BLOCK_AMOUNT 1

using std::string;
using std::cout;
using std::endl;

typedef unsigned int uint;

typedef enum vector_error_codes
{
	VECTOR_OK = 0,
} vector_error_code;


template <typename data_T>
class vector
{
private:
	data_T* data; uint block_amount; uint count;
	
	void expand();
	void shorten();
public:
	vector();
	explicit vector(uint size);
	vector(const vector& v);
	
	~vector();
	
	uint length();
	void append(data_T value);
	void swap(vector& that);
	
	virtual data_T operator[](int n);
	virtual data_T operator[](double t);
	
	data_T max();
	data_T min();
	
	vector <data_T>& operator=(const vector <data_T>& that);
	//~ vector <data_T>& operator=(const vector <data_T>&& that);
	
	void dump(string name, string destination);
	vector_error_code check();
};

string vector_convert_error_code_to_string(vector_error_code code)
{
	switch (code)
	{
		#define _RET_CODE(code) case code: return #code;
		_RET_CODE(VECTOR_OK)
		default: return "VECTOR_UNKNOWN_ERROR"; 
		#undef _RET_CODE
	}
}

template <typename data_T>
vector <data_T>::vector(uint size)
{
	count = 0;
	block_amount = size/VECTOR_DEFAULT_BLOCK_SIZE + 1;
	data = (data_T* )malloc(block_amount*VECTOR_DEFAULT_BLOCK_SIZE*sizeof(data_T));
	for (uint i = 0; i < block_amount*VECTOR_DEFAULT_BLOCK_SIZE; i++) data[i] = VECTOR_POISON;
}

template <typename data_T>
vector <data_T>::vector()
{
	count = 0;
	block_amount = VECTOR_DEFAULT_BLOCK_AMOUNT;
	data = (data_T* )malloc(block_amount*VECTOR_DEFAULT_BLOCK_SIZE*sizeof(data_T));
	for (uint i = 0; i < block_amount*VECTOR_DEFAULT_BLOCK_SIZE; i++) data[i] = VECTOR_POISON;
}

template <typename data_T>
vector <data_T>::vector(const vector <data_T>& v)
{
	count = v.count;
	block_amount = v.block_amount;
	data = (data_T* )malloc(block_amount*VECTOR_DEFAULT_BLOCK_SIZE*sizeof(data_T));
	for (uint i = 0; i < block_amount*VECTOR_DEFAULT_BLOCK_SIZE; i++) data[i] = v.data[i];
}

template <typename data_T>
void vector <data_T>::expand()
{
	block_amount++;
	data_T* tmp = data;
	data = (data_T* )malloc(block_amount*VECTOR_DEFAULT_BLOCK_SIZE*sizeof(data_T));
	for (uint i = 0; i < (block_amount - 1)*VECTOR_DEFAULT_BLOCK_SIZE; i++)
	{
		data[i] = tmp[i];
		tmp[i] = VECTOR_POISON;
	}
	for (uint i = (block_amount - 1)*VECTOR_DEFAULT_BLOCK_SIZE; i < block_amount*VECTOR_DEFAULT_BLOCK_SIZE; i++)
		data[i] = VECTOR_POISON;
	free(tmp);
}

template <typename data_T>
void vector <data_T>::shorten()
{
	block_amount--;
	data_T* tmp = data;
	data = (data_T* )malloc(block_amount*VECTOR_DEFAULT_BLOCK_SIZE, sizeof(data_T));
	for (uint i = 0; i < block_amount*VECTOR_DEFAULT_BLOCK_SIZE; i++)
	{
		data[i] = tmp[i];
		tmp[i] = VECTOR_POISON;
	}
	free(tmp);
}

template <typename data_T>
vector <data_T>::~vector()
{
	for (uint i = 0; i < block_amount*VECTOR_DEFAULT_BLOCK_SIZE; i++) data[i] = VECTOR_POISON;
	block_amount = 0;
	count = 0;
	free(data);
}

template <typename data_T>
uint vector <data_T>::length()
{
	return block_amount*VECTOR_DEFAULT_BLOCK_SIZE;
}

template <typename data_T>
vector_error_code vector <data_T>::check()
{
	return VECTOR_OK;
}

template <typename data_T>
void vector <data_T>::dump(string name, string destination)
{
	if (destination == "stdout")
	{
		cout << "Vector \"" << name << "\" dump [" << vector_convert_error_code_to_string(check()) << "].\n{\n";
		cout << "	length = " << block_amount*VECTOR_DEFAULT_BLOCK_SIZE << "\n";
		cout << "	count = " << count << endl;
		cout << "	data:\n";
		for (uint i = 0; i < block_amount*VECTOR_DEFAULT_BLOCK_SIZE; i++)
			if (data[i] == VECTOR_POISON)
				cout << "		data[" << i << "] = " << "POISON" << endl;
			else
				cout << "		data[" << i << "] = " << data[i] << endl;
		cout << "}\n\n";
		
	}
	else
	{
		assert(!"Not implemented.");
	}
}

template <typename data_T>
void vector <data_T>::append(data_T value)
{
	if (count+1 >= block_amount*VECTOR_DEFAULT_BLOCK_SIZE)
		expand();
	data[count++] = value;
}

template <typename data_T>
data_T vector <data_T>::operator[](int n)
{
	return data[n];
}

template <typename data_T>
data_T vector <data_T>::operator[](double t)
{
	uint a = trunc(t+1);
	uint b = trunc(t);
	#define db data[b]
	#define da data[a]
	return da*(t-b)-db*(t-a);
}

template <typename data_T>
void vector <data_T>::swap(vector& that)
{
	std::swap(block_amount, that.block_amount);
	std::swap(count, that.count);
	std::swap(data, that.data);
}

template <typename data_T>
vector <data_T>& vector <data_T>::operator=(const vector <data_T>& that)
{
	vector <data_T> tmp (that);
	tmp.swap(*this);

	//~ swap(that);
	return *this;
}

template <typename data_T>
data_T vector <data_T>::max()
{
	data_T tmp = data[0];
	for (uint i = 0; i < count; i++)
		if (data[i] > tmp)
			tmp = data[i];
	return tmp;
}

template <typename data_T>
data_T vector <data_T>::min()
{
	data_T tmp = data[0];
	for (uint i = 0; i < count; i++)
		if (data[i] < tmp)
			tmp = data[i];
	return tmp;
}
