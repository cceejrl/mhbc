#ifndef TEST_KSA_H
#define TEST_KSA_H
#include "helper_functions.h"
#include "he.h"
#include <bitset>
#include <stdlib.h> //rand

class TEST_KSA {
	public:
		TEST_KSA(unsigned bits, bool dbg, long l);
		Errors test();
	private:
		const string className();
		bool debug;
		unsigned bits; //number of bits
		HE he;
		Timing t;
		Conversion conv;
		unsigned N_numbers;
		long nslots;
		key_params params;
		vector< vector < long > > inputs;
		vector< vector < vector<long> > >  v_in;
		vector< vector < mkt > > k_constant, k;
		void t_start();
		void t_end(string name);
		void initialize();
		void set_params(long l);
		void make_copies();
    bool test_KSAdder();
};
#endif
