#include "helper_functions.h"
#include "TEST_GATES.h"
#include "TEST_CIRC_COMB.h"
#include "TEST_CIRC_SEQ.h"
#include "TEST_CIRC_ARITHM.h"
#include "TEST_KSA.h"

unsigned int BITWIDTH = 2;

int main(int argc, char **argv)
{
	//a vector contains L, for loop testing
  // std::vector<long> vL = {15,16,17,18,19,20};
  std::vector<long> vL = {5,7,10,15};
  for(auto i : vL)
  {
  cout << "======================================\n";
	bool verbose = true;//false;{
	Timing t_all("Overall");
    std::cout << "==== L = " << i << " ====" << std::endl;
	t_all.start();
	Errors e("test");

  // TEST_GATES tg;
  // e = tg.test();
  // e.display();

  // std::vector<long> v_L = {3, 5, 10, 15, 30};

  // for(auto l : v_L)
  // {
    // std::cout << "======= L = " << l << " =======" << std::endl;
    // TEST_CIRC_COMB t_combinational(l, verbose);
    // e = t_combinational.test();
    // e.display();
    // std::cout << "----------------------" << std::endl;
  // }
  
  TEST_KSA t_ksa(BITWIDTH,verbose, i);
  
  e = t_ksa.test();
  e.display();


  TEST_CIRC_SEQ t_sequential(BITWIDTH, verbose, i);
  e = t_sequential.test();
  e.display();

	//max 3 bits because of average circuit (can be disabled thought)
	//TEST_CIRC_ARITHM t_arithmetic(2, verbose); //set to 2 so we don't require 6.6GB of ram !
	//e = t_arithmetic.test();
	//e.display();
	
  t_all.end();
	cout << "======================================\n";
  }
	return 0;
}
