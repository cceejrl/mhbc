#include "TEST_GATES.h"

TEST_GATES::TEST_GATES(){
	set_params();
	initialize();
}
Errors TEST_GATES::test(){
	Errors e("TEST_GATES");
	e.add("AND gate", test_AND());
	e.add("XOR gate", test_XOR());
	e.add("NOT gate", test_NOT());
	e.add("NAND gate", test_NAND());
	e.add("OR gate", test_OR());
	e.add("NOR gate", test_NOR());
	e.add("XNOR gate", test_XNOR());
	return e;
}

void TEST_GATES::t_start(){
  t_.start();
}

std::string TEST_GATES::className(){
  return "TEST_GATES";
}

void TEST_GATES::t_end(std::string name){
  double duration = t_.end("silent");
  std::cout << "-----------------------------------------------------" << std::endl;
  cout << className() << ": " << name << " - " << " m = " << params.m << std::endl;
  cout << className() << ": " << name << " - " << nslots << " operations done in " << duration << "ms" << endl;
  cout << className() << ": " << name << " - Time for each operation: " << duration/nslots << "ms" << endl;
}

void TEST_GATES::set_params(){
	params.p = 2;
	params.r = 1;
	params.d = 0;
	params.k = 128;
	params.L = 3;
	params.c = 3;
	params.w = 64;
	params.slb = 0;
	params.m = FindM(params.k,params.L,params.c,params.p,params.d,params.slb,0);
}
void TEST_GATES::initialize(){
	IO = 2;
	he.debug_on(false);
	nslots = he.keyGen(params);
	mkt k_ones = he.setOnes(nslots);
	he.set01(k_ones);
	v_out.resize(IO, vector<long> (nslots,0));
	k_constant.resize(IO);
	v_in.resize(IO, vector<long> (nslots,0));
	v_in[0][0] = 0; v_in[1][0] = 0;
	v_in[0][1] = 0; v_in[1][1] = 1;
	v_in[0][2] = 1; v_in[1][2] = 0;
	v_in[0][3] = 1; v_in[1][3] = 1;
	for (int i = 0; i < IO; i++){
		k_constant[i] = he.encrypt(v_in[i]);
	}
}
void TEST_GATES::make_copies(){
	for (int i = 0; i < k.size(); i++){
		he.erase(k[i]);
	}
	k = vector< mkt >(IO);
	for (int i = 0; i < IO; i++){
		k[i] = he.copy(k_constant[i]);
	}
}
bool TEST_GATES::test_AND(){
	make_copies();

  // std::cout << "The flowing is k[0]:\n";
  // for(auto i : k[0])
    // std::cout << i << " ";
  // std::cout << std::endl;

  // std::cout << "The flowing is k[1]:\n";
  // for(auto i : k[1])
    // std::cout << i << " ";
  // std::cout << std::endl;

  t_start();
	he.AND(k[0],k[1]);
  t_end(__FUNCTION__);
	for (int i = 0; i < IO; i++){
		v_out[i] = he.decrypt(k[i]);
	}
  /* //here make some test print */
  // std::cout <<"The flowing is v_in:\n";
  // for(auto iter : v_in){
    // for(auto i : iter){
      // std::cout << i << " ";
    // }
      // std::cout << std::endl;
  // }

  // std::cout << "The flowing is v_out:\n";
  // for(auto iter : v_out){
    // for(auto i : iter)
      // std::cout << i << " ";
    // std::cout << std::endl;
  // }

	for (int i = 0; i < nslots; i++){
		if (v_out[0][i] != (v_in[0][i] & v_in[1][i])){
			return true; //error
		}
	}
	return false;
}
bool TEST_GATES::test_XOR(){
	make_copies();
  t_start();
	he.XOR(k[0],k[1]);
  t_end(__FUNCTION__);
	for (int i = 0; i < IO; i++){
		v_out[i] = he.decrypt(k[i]);
	}
	for (int i = 0; i < nslots; i++){
		if (v_out[0][i] != (v_in[0][i] ^ v_in[1][i])){
			return true; //error
		}
	}
	return false;
}
bool TEST_GATES::test_NOT(){
	make_copies();
  t_start();
	he.NOT(k[0]);
  t_end(__FUNCTION__);
	for (int i = 0; i < IO; i++){
		v_out[i] = he.decrypt(k[i]);
	}
	for (int i = 0; i < nslots; i++){
		if (v_out[0][i] != !v_in[0][i]){
			return true; //error
		}
	}
	return false;
}
bool TEST_GATES::test_NAND(){
	make_copies();
  t_start();
	he.NAND(k[0],k[1]);
  t_end(__FUNCTION__);
	for (int i = 0; i < IO; i++){
		v_out[i] = he.decrypt(k[i]);
	}
	for (int i = 0; i < nslots; i++){
		if (v_out[0][i] != !(v_in[0][i] & v_in[1][i])){
			return true; //error
		}
	}
	return false;
}
bool TEST_GATES::test_OR(){
	make_copies();
  t_start();
	he.OR(k[0],k[1]);
  t_end(__FUNCTION__);
	for (int i = 0; i < IO; i++){
		v_out[i] = he.decrypt(k[i]);
	}
	for (int i = 0; i < nslots; i++){
		if (v_out[0][i] != (v_in[0][i] | v_in[1][i])){
			return true; //error
		}
	}
	return false;
}
bool TEST_GATES::test_NOR(){
	make_copies();
  t_start();
	he.NOR(k[0],k[1]);
  t_end(__FUNCTION__);
	for (int i = 0; i < IO; i++){
		v_out[i] = he.decrypt(k[i]);
	}
	for (int i = 0; i < nslots; i++){
		if (v_out[0][i] != !(v_in[0][i] | v_in[1][i])){
			return true; //error
		}
	}
	return false;
}
bool TEST_GATES::test_XNOR(){
	make_copies();
  t_start();
	he.XNOR(k[0],k[1]);
  t_end(__FUNCTION__);
	for (int i = 0; i < IO; i++){
		v_out[i] = he.decrypt(k[i]);
	}
	for (int i = 0; i < nslots; i++){
		if (v_out[0][i] != !(v_in[0][i] ^ v_in[1][i])){
			return true; //error
		}
	}
	return false;
}
