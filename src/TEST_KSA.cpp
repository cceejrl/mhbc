#include "TEST_KSA.h"

TEST_KSA::TEST_KSA(unsigned number_bits, bool dbg, long l){
	bits = number_bits;
	debug = dbg;
	set_params(l);
	initialize();
}
const string TEST_KSA::className(){
	return "TEST_KOGGE_STONE_ADDER";
}
void TEST_KSA::t_start(){
	if (debug){
		t.start();
	}
}
void TEST_KSA::t_end(string name){
	if (debug){
		double duration = t.end("silent");
		cout << className() << ": " << name << " - " << nslots << " operations done in " << duration << "ms" << endl;
		cout << className() << ": " << name << " - Time for each operation: " << duration/nslots << "ms" << endl;
	}
}

Errors TEST_KSA::test(){
	Errors e("TEST_KSA");
  e.add("Kogge-Stone ADDER swquential circuit", test_KSAdder());
	return e;
}

void TEST_KSA::set_params(long l){
	params.p = 2;
	params.r = 1;
	params.d = 0; // field p^d
	params.k = 128;//64;
	params.slb = 0;//800;
	params.L = 0;
	if(params.L == 0){ //L not set 
	//for the ripple carry adder so for circuits with complexity up to 3n+1
	//not valid for ripple comparator !
		switch(bits){
			case 1:
				params.L = 5;
				break;
			case 2:
				params.L = 7;
				break;
			case 3:
				params.L = 9;
				break;
			case 4:
				params.L = 12;
				break;
			case 5:
				params.L = 13;
				break;
			case 6:
				params.L = 15;
				break;
			case 7:
				params.L = 17;
				break;
			case 8:
				params.L = 19;
				break;
			case 9:
				params.L = 21;
				break;
			case 10:
				params.L = 23;
				break;
			case 11:
				params.L = 27;
				break;
			case 12:
				params.L = 29;
				break;
			case 13:
				params.L = 31;
				break;
			case 14:
				params.L = 34;
				break;
			case 15:
				params.L = 35;
				break;
			case 16:
				params.L = 37;
				break;
			if(params.L == 0){ // bits not in 1 .. 16
				params.L = 44; //should work with everything
			}
		}
	}
	
	
	
	if ((params.L > 42)&&(params.slb > 600)){
		params.L *= 1.2;
	}

  // params.L = l;
  // params.slb = 600;

	params.c = 3;
	params.w = 64;
	
  params.m = FindM(params.k,params.L,params.c,params.p,params.d,params.slb,0);
	// params.m = 14351;//FindM(params.k,params.L,params.c,params.p,params.d,params.slb,0);
}
void TEST_KSA::initialize(){
	N_numbers = 2;
	he.debug_on(debug);
	cout << className() << ": Number of bits n was set to " << bits << endl; 
  
	nslots = he.keyGen(params);
	mkt k_ones = he.setOnes(nslots);
	he.set01(k_ones);


	inputs.resize(N_numbers, vector < long > (nslots,0));
	v_in.resize(N_numbers,vector< vector<long> >(bits,vector<long>(nslots,0)));
	k_constant.resize(N_numbers, vector < mkt>(bits));

	
  //something wrong with the following loop which 
  //lead to a "floating point exception core dump"
	//inputs to N bit circuits
  unsigned u_max = pow(2, bits);
	for(unsigned i = 0; i < nslots; i++){
		inputs[0][i] = rand() % u_max;
		inputs[1][i] = rand() % u_max;
	}

	//Converts inputs to bits into v_in for parallel ciphertexts
	for(unsigned n = 0; n < N_numbers; n++){
		for(unsigned j = 0; j < nslots; j++){
			bitset<64> bin(inputs[n][j]); //max is 2^64 so max nbits = 64
			for(unsigned b = 0; b < bits; b++){
				v_in[n][b][j] = bin[b]; //first ctxt (b = 0) is LSB
			}
		}
	}

	//Encrypts all the vectors into ciphertexts
	if(debug){
		cout << "TEST_KSA: Encrypting input vectors (" << N_numbers * bits << " vectors)" << endl;
	}
	for(unsigned n = 0; n < N_numbers; n++){
		for (unsigned b = 0; b < bits; b++){
			k_constant[n][b] = he.encrypt(v_in[n][b]);
		}
	}
}
void TEST_KSA::make_copies(){
	for(unsigned n = 0; n < k.size(); n++){
		for (unsigned b = 0; b < k[n].size(); b++){
			he.erase(k[n][b]);
		}
	}
	k = vector< vector<mkt> >(N_numbers, vector<mkt>(bits));
	for(unsigned n = 0; n < N_numbers; n++){
		for (unsigned b = 0; b < bits; b++){
			k[n][b] = he.copy(k_constant[n][b]);
		}
	}
}

bool TEST_KSA::test_KSAdder(){
  make_copies();

  // std::cout << "======= KSAdder ======\n";
  // std::cout << "k[0] = ";
  // for(auto i : k[0])
    // std::cout << i << " ";
  // std::cout << std::endl;

  t_start();
  he.KoggeStoneAdder(k[0],k[1]);
  t_end(__FUNCTION__);

  vector<long> res(nslots);
  res = conv.matrix2LongVec(he.decryptNbits(k[0]));




  // std::cout << "======= KSAdder ======\n";
  for(unsigned i = 0; i < nslots; i++){
    if(res[i] != (inputs[0][i] + inputs[1][i])){
        return true;//error
    }
  }
  return false;
}
