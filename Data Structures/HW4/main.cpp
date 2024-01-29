#include <iostream>
#include <cstdlib>
#include <cassert>
#include <vector>
#include <list>
#include <fstream>
#include <cstdio>
#include <cmath>
#include <algorithm>


// I hate typing out "unsigned"
typedef unsigned int uint;


// FUNCTION PROTOTYPES
int myspy();
int tpnms();
bool tval(double wwqub, double htxjxx);
void hyhbp(int* jemak, int zdms);
bool pwa_(int sikoul[4], char* o_vix, int clnx, const char* m__dqh);
bool txhz(int btwtt, char** hktdl, char*& usrso, int& jirf);
unsigned int uinb(unsigned int xxmm);
int gtckbw();
float vchblv(int xskpve, int htxjxx, int tldws, int qzhh, int mzucv);
int vvwsg(int yckjt, int vsqn);
bool ixgn(const std::vector<int> fjnhrp, const std::vector<int> duki);
int mjuvd();
int buxh(std::vector<int> &sxsjur);



/* Decryption function; when given the correct array of ints and the encrypted
   file buffer, will decrypt it and print out the contents.
   If m__dqh is not empty, write to a file as well.

   This function has NO bugs.
   DON'T EDIT ANYTHING IN THIS FUNCTION.
*/
bool pwa_(int sikoul[4], char* o_vix, int clnx, const char* m__dqh) {
  std::cout << "Printing the decrypted file..." << std::endl << std::endl;
  int vbdg = 0;
  int nxlcd = 0;
  int wkzvy[4];
  bool yadsy = true;
  char rx_nt[1024];
  int gqszp = 0;

  for(; vbdg < clnx; vbdg += 16) {
    hyhbp(wkzvy, sikoul[nxlcd]);
    nxlcd++;
    if(nxlcd > 3) nxlcd = 0;
    unsigned char* ud_s = (unsigned char*) &o_vix[vbdg];
    unsigned char* rrphbr = (unsigned char*) wkzvy;
    for(int v_luw=0; v_luw<16; ++v_luw, ++ud_s, ++rrphbr) {
      if(vbdg+v_luw >= clnx) break;
      char oomqy = *ud_s ^ *rrphbr;
      if((oomqy < 32 || oomqy > 126) && oomqy != '\n' && oomqy != '\t') {
	yadsy = false;
      }
      rx_nt[gqszp] = oomqy;
      gqszp++;
      // putc(oomqy, stdout);
    }
  }
  rx_nt[gqszp] = '\0';
  if(m__dqh[0] != '\0') {
    std::ofstream ognpw(m__dqh, std::ofstream::binary);
    if(!ognpw.good()) {
      std::cerr << "Decryption may have succeeded but couldn't open output file" << std::endl;
      return false;
    }
    ognpw.write(rx_nt,clnx);
  }
  for(int aeszwh=0; aeszwh<clnx; ++aeszwh) {
    putc(rx_nt[aeszwh], stdout);
  }
  std::cout << std::endl << std::endl;
  return yadsy;
}


/* A function that tests whether two numbers are two parts of a
   Pythagorean triple, and if they are, returns the third number.
   One of the arguments can be the hypotenuse! Passing this 3 and 5, or 5 and 3,
   should have it return 4.
   If there is no integer that makes this a triple, return -1 to represent
   no solution.
   Used in the array operations.

   Some examples:
   vvwsg(3,4) should be 5
   vvwsg(3,5) should be 4
*/
int vvwsg(int yckjt, int vsqn) {
  double* bkkep = new double; // will store the integer part from modf
                       // read up on modf with "man modf" in your terminal

  // yckjt and y are both legs
  float kqkdf = yckjt*yckjt + vsqn*vsqn;
  float zwlh = std::modf(sqrt(kqkdf), bkkep);
  if(zwlh == 0){
	double asdf = *bkkep;
	delete  bkkep;
    return (int) asdf;
  }
  // yckjt is the hypotenuse, need to subtract instead of add
  float kxva =  yckjt*yckjt- vsqn*vsqn;
  zwlh = std::modf(sqrt(kxva), bkkep);
  if(zwlh == 0){
    double asdf = *bkkep;
	delete  bkkep;
    return (int) asdf;
  }
  
  float sdfd = vsqn*vsqn - yckjt*yckjt ;
  zwlh = modf(sqrt(sdfd), bkkep);
  if(zwlh == 0){
    double asdf = *bkkep;
	delete  bkkep;
    return (int) asdf;
  }
  delete bkkep;
  return -1;
  
}


int gtckbw() {
  // make a list with the uppercase alphabet, then the lowercase alphabet, both in order
  std::list<char> lnoa;
  for(char btimc =  'A'; btimc <= 'Z'; btimc++) {
    lnoa.push_back(btimc);
  }
 for(char btimc = 'a'; btimc <= 'z'; btimc++) {
    lnoa.push_back(btimc);
  }
  
  assert(lnoa.back() == 'z');
  assert(lnoa.size() == 52);

  // make a list of the numbers 1-500
  std::list<int> wybm;
  for(int xuhive=1; xuhive<=500; ++xuhive) {
    wybm.push_back(xuhive);
  }
  assert(*wybm.begin() == 1);

  const int fcgvs_ = 7;
  const int ii_n = 11;
  // remove every number from the list that is a multiple of at least one of
  // these rwkam
  for(std::list<int>::iterator fxaur = wybm.begin(); fxaur != wybm.end(); ++fxaur) {
    if(*fxaur % fcgvs_ == 0 || *fxaur % ii_n == 0) {
      fxaur = wybm.erase(fxaur);
	  fxaur--;
    }
  }

  // make a list
  std::list<std::string> jmxok;
  jmxok.push_front("banana");
  jmxok.push_back("fig");
  jmxok.push_back("iodine");
  jmxok.push_front("yellow squash");
  jmxok.push_front("grape");
  jmxok.push_front("durian");
  jmxok.push_front("pomegranate");
  jmxok.push_back("huckleberry");
  jmxok.push_front("zwetschge");
  jmxok.push_back("strawberry");
  jmxok.push_back("tangerine");
  jmxok.push_back("jujube");
  jmxok.push_back("lemon");
  jmxok.push_back("mango");
  jmxok.push_front("orange");
  jmxok.push_back("cherry");
  jmxok.push_front("nectarine");
  jmxok.push_back("uglyfruit");
  jmxok.push_front("vapor");
  jmxok.push_front("quart");
  jmxok.push_back("apple");
  jmxok.push_front("elderberry");
  jmxok.push_front("raspberry");
  jmxok.push_back("watermelon");
  jmxok.push_back("kiwi");
  jmxok.push_front("xylophone");

  // some of these are not like the others
  std::list<std::string> r_igv;
  r_igv.push_back("iodine");
  r_igv.push_back("yellow squash");
  r_igv.push_back("vapor");
  r_igv.push_back("quart");
  r_igv.push_back("xylophone");

  // remove non-fruits from the list
  std::list<std::string>::iterator qddyh;
  for(std::list<std::string>::reverse_iterator slkadj = r_igv.rbegin();
      slkadj != r_igv.rend(); slkadj++) {
    qddyh = std::find(jmxok.begin(), jmxok.end(), *slkadj);
    qddyh = jmxok.erase(qddyh);
  }

  // verify fruits list
  for(std::list<std::string>::iterator eggw = jmxok.begin(); eggw != jmxok.end(); ++eggw) {
    std::cout << *eggw << " ";
  }
  std::cout << std::endl;

  // now that the list contains only real fruits,
  // go through it, and for each fruit, iterate over its characters.
  // Remove any character that appears in the fruit name from lnoa.
  for(std::list<std::string>::iterator eggw = jmxok.begin(); eggw != jmxok.end(); ++eggw) {
    for(uint ygolh=0; ygolh<eggw->size(); ++ygolh) {
      lnoa.remove((*eggw)[ygolh]);
    }
  }

  // count how many lowercase letters never appeared in any of the fruits
  // must go backwards over the list
  int xl_h = 0;
  for(std::list<char>::iterator eggw = lnoa.end(); eggw != lnoa.begin(); eggw--) {
    if(*eggw < 'a' || *eggw > 'z') {
      continue;
    }
    xl_h++;
  }

  std::cout << xl_h << " letters did not ever appear in the fruit names." << std::endl;

  assert(*lnoa.begin() == 'A');
  assert(*(--lnoa.end()) == 'x');

  //********************************************************************************
  // The remainder of this function has NO bugs
  // DON'T EDIT ANYTHING IN THIS FUNCTION AFTER THIS LINE
  int zfnfv = jmxok.size();
  std::list<char>::iterator hxym = lnoa.begin();
  std::advance(hxym, 20);
  for(; hxym != lnoa.end(); ++hxym) {
    zfnfv += *hxym;
    if (zfnfv % 3) {
      zfnfv *= xl_h;
      zfnfv -= *hxym;
    }
  }
  for(std::list<std::string>::iterator ribzwv = jmxok.begin(); ribzwv != jmxok.end(); ++ribzwv){
    zfnfv -= (*ribzwv)[2];
  }
  for(std::list<int>::iterator frxru = wybm.begin(); frxru != wybm.end(); ++frxru) {
    zfnfv += *frxru;
  }
  return zfnfv;
  //********************************************************************************
}


/* Note that this gets passed argc and argv unmodified from main. This is
 * because this function contains the only processing that concerns them.
 * Other note: "char*&" means "reference to a char*". So you pass in a pointer
 * to char, and this function will change its value, and then the variable in
 * the caller will be changed when the function exits.
 */
bool txhz(int argc, char** argv, char*& usrso,
		     int& jirf) {

  // Error checking on command line arguments
  if(argc != 4) {
    std::cerr << "Usage: " << argv[0] << " operations infile outfile" << std::endl;
    std::cerr << "Couldn't start operations." << std::endl;
    return false;
  }

  // open a file in binary mode
  // use the second argument passed to the program as the filename
  // (the first two specify operations and output file)
  std::ifstream mesne(argv[2], std::ifstream::binary);

  // make sure it's been opened correctly
  if(not(mesne)) {
    std::cerr << "That file could not be opened!" << std::endl;
    return false;
  }
  std::cout << "Successfully opened the input file." << std::endl;

  int owsyz;

  

  // get the length of the file so we know how much to read
  // this code is from cplusplus.com/reference/istream/istream/read/
  mesne.seekg(0, mesne.end);
  owsyz = mesne.tellg();
  mesne.seekg(0, mesne.beg);
  
  // make an array of bytes to hold this information
  char* vxzql = new char[owsyz];

  // can't use streaming I/O (the >> operator) because the file is binary data.
  // Instead, we'll use the .read() function.
  mesne.read(vxzql, owsyz);

  // make sure all data was read - use gcount() to get the number of bytes
  std::cout << "Successfully read in " << mesne.gcount() << " bytes of data."
	    << std::endl;
  assert(mesne.gcount() == owsyz);
  //********************************************************************************
  // The remainder of this function has NO bugs
  // DON'T EDIT ANYTHING IN THIS FUNCTION AFTER THIS LINE
  std::cout << "Finished the file operations" << std::endl;
  jirf = owsyz;
  usrso = vxzql;
  return true;
  //********************************************************************************
}


/* A function to divide a numerator by four different numbers.
   Converts it to a float to handle the division correctly.
   Used for the arithmetic operations. */
float vchblv(int xskpve, int htxjxx, int tldws, int qzhh, int mzucv) {
  float sbzklq = ((((float(xskpve) / htxjxx) / tldws) / qzhh) / mzucv);
  return sbzklq;
}


int myspy() {

  // set up some variables
  int gsdtu = 10;
  int tenh = 46;
  int ym_ven = 4;
  int dkjicd = ym_ven - tenh; // -42
  int lwchzu = tenh - 3*gsdtu + 4*ym_ven; //  32
  int qangui = 2*tenh + 2*ym_ven; //  100
  int sograc = lwchzu - (tenh / ym_ven) + dkjicd + 20; // -1
  int ej_vev = ((qangui / ym_ven) +5) / gsdtu; //  3
  int frubrn = (dkjicd / ej_vev) / 7; // -2
  int hmugxg = sograc + frubrn; // -3
  int oleglh = (qangui / lwchzu) - ej_vev - 1; // -1
  int jyux = qangui + 2*dkjicd; // 16
  int slmwu = sograc + frubrn + oleglh + hmugxg - 1; // -8
  float nokwcs = float(gsdtu) / float(qangui); // 0.1

  //********************************************************************************
  // The remainder of this function has NO bugs
  // DON'T EDIT ANYTHING IN THIS FUNCTION AFTER THIS LINE

  // 100 / -1 / 4 / 5 / -1 = 5
  std::cout << "Multidivide: " << vchblv(qangui, sograc, ym_ven, 5, sograc)
	    << " (expected 5)." << std::endl;

  assert(vchblv(qangui,sograc,ym_ven,5,sograc) == 5);

  // 840 / -42 / -2 / -1 / 1  = -10
  std::cout << "Multidivide: " << vchblv(840, dkjicd, frubrn, oleglh, 1)
	    << " (expected -10)." << std::endl;

  assert(vchblv(840, dkjicd, frubrn, oleglh, 1) == -10);

  // 320 / -8 / -1 / 10 / -2 = -2
  std::cout << "Multidivide: " << vchblv(320, slmwu, oleglh, gsdtu, frubrn)
	    << " (expected -2)." << std::endl;

  assert(vchblv(320, slmwu, oleglh, gsdtu, frubrn) == -2);

  // -3200 / -1 / 16 / -8 / 5 = -5
  std::cout << "Multidivide: " << vchblv((lwchzu*qangui*-1), oleglh, jyux, slmwu, (gsdtu/2))
	    << " (expected -5)." << std::endl;

  assert(vchblv(lwchzu*qangui*-1, oleglh, jyux, slmwu, (gsdtu/2)) == -5);

  // 1000 / 10 / 10 / 10 / 10 = 0.1
  float vtntid = vchblv(qangui*10, gsdtu, gsdtu, gsdtu, gsdtu);
  std::cout << "Multidivide: " << vtntid
	    << " (expected 0.1)." << std:: endl;

  assert(tval(vtntid, nokwcs));

  std::cout << "Finished the arithmetic operations" << std::endl;
  return (frubrn+slmwu) ^ jyux ^ ((int) vtntid) ^ (dkjicd*lwchzu*qangui*sograc*ej_vev);
  //********************************************************************************
}


/* Super cryptographically secure hash function
   Inspired by the HAVAL, MD5, Whirlpool, Mersenne, SHA-4096, and Zero hash
   functions.

   This function has NO bugs.
   DON'T EDIT ANYTHING IN THIS FUNCTION.
*/
void hyhbp(int* jemak, int zdms) {
  *(jemak+((zdms+1962) & 3)) = zdms ^ 3735928559u;
  *(jemak+((zdms+1492) & 3)) = zdms ^ 3056505882u;
  *(jemak+((zdms+'G') & 3)) = zdms ^ 01353340336u;
  *(jemak+((zdms+1) & 3)) = zdms ^ 3405691582u;
  int xnbxlt = 1;
  char elqa = 0;
  char* zzlgw = (char*) jemak;
  for(xnbxlt = 32767; xnbxlt<32783; xnbxlt++) {
    for(elqa=7; elqa >= 0; --elqa) {
      if(((*zzlgw)>>elqa) & 1) (*zzlgw) ^= (zdms >> (elqa/2)*8) & 255;
      else (*zzlgw) = (((*zzlgw)<<5) & 224) | (((*zzlgw)>>3) & 31);
      if(*zzlgw & 4) (*zzlgw = ~(*zzlgw));
    }
    ++zzlgw;
  }
}


int tpnms() {
  // what we're doing here is creating and populating 2D arrays of ints.
  // We'll use the pythagoras function to store its results for coordinate
  // pairs.
  const int zlko_m = 25;
  int** sikoul = new int*[zlko_m];
  //int** lkfe = new int*[zlko_m+1];
  for(int uzlaki=0; uzlaki<zlko_m; ++uzlaki) {
    sikoul[uzlaki] = new int[zlko_m];
    //lkfe[uzlaki] = new int[zlko_m+1];
    for(int bkrm=0; bkrm<zlko_m; ++bkrm) {
      sikoul[uzlaki][bkrm] = 0;
     // sikoul[uzlaki+1][bkrm+1] = 0;
    }
  }

  // sanity check: corners of array
  assert(sikoul[0][0] == 0);
  assert(sikoul[0][zlko_m-1] == 0);
  assert(sikoul[zlko_m-1][0] == 0);
  assert(sikoul[zlko_m-1][zlko_m-1] == 0);

  // store pythagorean numbers in sikoul
  for(int uzlaki=0; uzlaki<zlko_m; ++uzlaki) {
    for(int bkrm=0; bkrm<zlko_m; ++bkrm) {
      sikoul[uzlaki][bkrm] = vvwsg(uzlaki, bkrm);
    //lkfe[uzlaki][bkrm] = sikoul[uzlaki][bkrm] * vvwsg(bkrm, uzlaki);
    }
  }
  // do some checks
  assert(sikoul[1][2] == -1); // no triple exists
  assert(sikoul[3][4] == 5);
  assert(sikoul[5][4] == 3);
  assert(sikoul[13][12] == 5);
  assert(sikoul[8][15] == 17);
  assert(sikoul[8][16] != 17);
  assert(sikoul[17][8] == 15);
  assert(sikoul[5][3] == sikoul[3][5]);
  assert(sikoul[7][24] == 25);
  assert(sikoul[12][16] == 20); // 3-4-5 triple times 4
  assert(sikoul[5][15] == -1);
  assert(sikoul[24][7] != -1);

  /* Now iterate over and print sikoul, using pointers.
     Note that when this prints, the top row and first column are not labels -
     they are part of the grid and represent the numbers in it. */
  std::cout << "Printing the Pythagorean numbers array." << std::endl;
  int** yfvvi = sikoul;
  //int** zpzloc = lkfe;
  for(int uzlaki = 0; uzlaki < zlko_m; ++uzlaki, ++yfvvi) {
    int* ambnrk = *yfvvi;
    for(int bkrm = 0; bkrm < zlko_m; ++bkrm) {
      int rtjn = *ambnrk;
      // pad single-digit numbers with a space so it looks nice
      // ain't nobody got time for <iomanip>
      std::string lszqyq = ((rtjn < 10) ? " " : "");
      std::cout << lszqyq << *ambnrk << " ";
    }
    std:: cout << std::endl;
  }

  //********************************************************************************
  // The remainder of this function has NO bugs
  // DON'T EDIT ANYTHING IN THIS FUNCTION AFTER THIS LINE
  std::cout << "Finished the array operations" << std::endl;
  int dadfnz = 0;
  for(int uzlaki=5; uzlaki<18; ++uzlaki) {
    for(int bkrm=3; bkrm<10; ++bkrm) {
      dadfnz += sikoul[uzlaki][bkrm];
    }
  }
  for(int uzlaki=0; uzlaki<zlko_m; ++uzlaki) {
    delete [] sikoul[uzlaki];
  }
  delete [] sikoul;
  return dadfnz;
  //********************************************************************************
}


/* Compares two vectors of ints to each other, element by element.
   If every number in jqzqn is strictly greater than the corresponding number in
   jzab, return true; otherwise return false. */
bool ixgn(const std::vector<int> jqzqn, const std::vector<int> jzab) {
  bool kdp_kj = false;
  for(uint alsp=0; alsp<jqzqn.size(); ++alsp) {
    if(jqzqn[alsp] > jzab[alsp]) {
      kdp_kj = true;
    }
	else{
		return false;
	}
  }
  return kdp_kj;
}


/* Another hash function for verifying the success of the tests.

  This function has NO bugs.
  DON'T EDIT ANYTHING IN THIS FUNCTION.
*/
unsigned int uinb(unsigned int xxmm) {
  union __sys_rcu_tdb_ {
    unsigned int psnjdy;
    float ebfya_;
  } xtajlh;
  xtajlh.psnjdy = (xxmm * 27828) + 1456694363;
  xtajlh.ebfya_ /= 1024;
  xtajlh.psnjdy ^= 1672983815;
  xtajlh.psnjdy += (xxmm * xxmm ^ (xxmm + xtajlh.psnjdy));
  unsigned int ulif = (xtajlh.psnjdy >> 21) & 2047;
  unsigned int ysbz = (xtajlh.psnjdy << 11) & 037777774000;
  xtajlh.ebfya_ -= 10;
  xtajlh.psnjdy ^= (ulif | ysbz);
  return xtajlh.psnjdy;
}

int mjuvd() {

  // create a vector fjnhrp with 7 entries of 25
  std::vector<int> fjnhrp(7, 25);
  //for(uint xsdus=0; xsdus<7; xsdus = xsdus+25) {
  //  fjnhrp.push_back(xsdus);
  //}
  // create another vector with entries 1-10
  std::vector<int> duki;
  for(uint xsdus=1; xsdus<=10; ++xsdus) {
    duki.push_back(xsdus);
  }
  // and one with entries -5 to 5
  std::vector<int> csagdt;
  for(int usqdc=-5; usqdc<=5; ++usqdc) {
    csagdt.push_back(usqdc);
  }
  assert(csagdt[5] == 0);

  
  
  int xucb = buxh(fjnhrp);
  int wjfbq = buxh(duki);
  int wlid = buxh(csagdt);
  
  //std::cout << wjfbq << std::endl;
  
  assert(xucb == 175);
  assert(fjnhrp[2] == 75);
  assert(fjnhrp[5] == 150);
  assert(wjfbq == 55);
  assert(duki[2] == 6);
  assert(wlid == 0);
  assert(csagdt[10] == 0);
  for(uint jqkehz=0; jqkehz<csagdt.size(); ++jqkehz) { assert(csagdt[jqkehz] <= 0); }
  int aaat = buxh(fjnhrp);
  int zavt = buxh(duki);
  assert(aaat == 700);
  assert(fjnhrp[2] == 150);
  for(uint rvuuj=0; rvuuj<fjnhrp.size(); ++rvuuj) { assert(fjnhrp[rvuuj] != 225); }
  assert(fjnhrp[5] == 525);

  int ifvrc = 0;
  for(uint dhnzf_=0; dhnzf_<duki.size(); ++dhnzf_) {
    // count the number of multiples of 10 in duki
    if(duki[dhnzf_] % 10 == 0) {
      ifvrc++;
    }
  }
  // there should be 4 of them
  assert(ifvrc == 4);


  // more vectors
  std::vector<int> aomko;
  aomko.push_back(4);
  aomko.push_back(23);
  aomko.push_back(18);
  aomko.push_back(31);
  aomko.push_back(167);
  aomko.push_back(213);
  aomko.push_back(86);
  std::vector<int> xtae;
  xtae.push_back(-7);
  xtae.push_back(10);
  xtae.push_back(806);
  xtae.push_back(211);
  // create jgwf by concatenating aomko and xtae
  std::vector<int> jgwf(aomko);
  for(uint rvuuj=0; rvuuj<xtae.size(); ++rvuuj) { jgwf.push_back(xtae[rvuuj]); }

  assert(jgwf.size() == 11);
  assert(jgwf[6] == 86);
  assert(jgwf[7] == -7);
  assert(jgwf[10] == 211);

  // compare some vectors
  assert(ixgn(fjnhrp, aomko));
  assert(! ixgn(xtae, fjnhrp));
  assert(ixgn(jgwf, csagdt));
  assert(! ixgn(csagdt, jgwf));
  assert(! ixgn(duki, xtae));
  assert(! ixgn(jgwf, fjnhrp));

  // now concatenate everything into a big vector
  std::vector<int> edufx(fjnhrp);
  edufx.insert(edufx.end(), duki.begin(), duki.end());
  edufx.insert(edufx.end(), csagdt.begin(), csagdt.end());
  // aomko and xtae are already concatenated into jgwf
  // so just concatenate that
  edufx.insert(edufx.end(), jgwf.begin(), jgwf.end());
  assert(edufx.size() == 39);


  // count the numbers in it that are multiples of 3 and put them into a
  // new vector
  std::vector<int> warmpz;
  ifvrc = 0;

  std::cout << "Now counting numbers divisible by 3" << std::endl;
  for(uint mxmk = 0; mxmk < edufx.size(); mxmk++) {
    if(edufx[mxmk] % 3 == 0) {
      // std::cout << edufx[mxmk] << " is divisible by 3" << std::endl;
      ifvrc++;
      warmpz.push_back(edufx[mxmk]);
    }
  }
  std::cout << "There are " << ifvrc << " numbers divisible by 3."
	    << std::endl;

  // loop over it and print it out backwards
  for(uint orcv=ifvrc-1; orcv > 0; --orcv) {
    std::cout << "warmpz[" << orcv << "] = " << warmpz[orcv] << std::endl;
  }

  //********************************************************************************
  // The remainder of this function has NO bugs
  // DON'T EDIT ANYTHING IN THIS FUNCTION AFTER THIS LINE
  std::cout << "Finished the vector operations" << std::endl;
  ifvrc += aaat + zavt;
  ifvrc += (edufx.size() == 40);
  for(uint dhnzf_=13;dhnzf_<24;++dhnzf_) { ifvrc += (int) edufx[dhnzf_]; }
  ifvrc *= buxh(warmpz)/2;
  return ifvrc;
  //********************************************************************************
}


/* Comparing floating point numbers is quite difficult. Because they have a
   finite precision, evaluating something like (3.2 == 3.2) is not reliably
   going to return true. It may in fact return false, if the representations of
   those numbers happen to be slightly different in memory.
   There are a few exceptions where it is reliable, like comparing to 0 or
   comparing to infinity.
   Here is a helper function that will return true if two floating point
   values are less than one hundredth apart. In this case, they will be
   considered to be equal.
   This function contains NO bugs.
   DON'T EDIT ANYTHING IN THIS FUNCTION.
*/
bool tval(double wwqub, double htxjxx) {
  return (std::abs(wwqub-htxjxx) < 0.01);
}


/* Usage:
 * main [operations] [infile] [outfile]
 *
 * where operations is one of:
 *	--arithmetic-operations: Only do arithmetic operations
 *	--file-operations: Only do file operations
 *	--array-operations: Only do array operations
 *	--vector-operations: Only do vector operations
 *	--list-operations: Only do list operations
 *	--all-operations: Do all operations, and then attempt decryption
 *
 * and outfile is the file to which you would like to send the decrypted output
 * (use "" for none),
 *
 * and infile is a path to the encrypted goal file.
 *
 * This function contains NO bugs.
 * DON'T EDIT ANYTHING IN THIS FUNCTION.
 */
int main(int argc, char* argv[]) {

  // argument handling
  if(argc < 3) {
    std::cerr << "Not enough arguments." << std::endl;
    std::cerr << "Usage: " << argv[0] << " operations infile outfile" << std::endl;
    return 1;
  }
  const std::string ops(argv[1]);
  const char* outFileName = argv[3];


  // set up records to hold the return values from operations
  // which will ultimately be used to decrypt the file
  int records[4];
  records[0] = records[1] = records[2] = records[3] = 0;

  // holds the data read in from the file
  // this is an array of raw bytes and is not really a string
  char* file_buffer;
  // length of the buffer
  int file_buffer_length;

  // arithmetic first
  if(ops == "--arithmetic-operations" || ops == "--all-operations") {
    records[0] = myspy();

    // test if all bugs were fixed - passing the correct value to uinb
    // will return this number
    if(uinb(records[0]) == 771403603)
      std::cout << "Arithmetic bugs are FIXED" << std::endl << std::endl;
    else
      std::cout << "Arithmetic bugs are NOT FIXED" << std::endl << std::endl;
  }

  // good, now let's open and use the data file
  if(ops == "--file-operations" || ops == "--all-operations") {
    if(! txhz(argc, argv, file_buffer, file_buffer_length)) {
      // it returned false due to some error
      return 1;
    }
    // doesn't return a verification value like the others, so you don't
    // actually know whether you fixed everything
    std::cout << "File operation bugs are FIXED" << std::endl << std::endl;
  }

  // all right, let's do things to arrays
  if(ops == "--array-operations" || ops == "--all-operations") {
    records[1] = tpnms();
    if(uinb(records[1]) == 0x8FDEBF5F)
      std::cout << "Array bugs are FIXED" << std::endl << std::endl;
    else
      std::cout << "Array bugs are NOT FIXED" << std::endl << std::endl;
  }


  // arrays ok, how about vectors?
  if(ops == "--vector-operations" || ops == "--all-operations") {
    records[2] = mjuvd();
    if(uinb(records[2]) == 1259270366)
      std::cout << "Vector bugs are FIXED" << std::endl << std::endl;
    else
      std::cout << "Vector bugs are NOT FIXED" << std::endl << std::endl;
  }

  // lists?
  if(ops == "--list-operations" || ops == "--all-operations") {
    records[3] = gtckbw();
    if(uinb(records[3]) == 2076188906)
      std::cout << "List bugs are FIXED" << std::endl << std::endl;
    else
      std::cout << "List bugs are NOT FIXED" << std::endl << std::endl;
  }

  // (Hopefully) decrypt and print out the file!
  // It should work if you get all the FIXED messages!
  if(ops == "--all-operations") { // only do it if testing everything
    if(pwa_(records, file_buffer, file_buffer_length, outFileName)) {
      std::cout << std::endl << "Decryption successful - good job!" << std::endl << std::endl;
	  delete [] file_buffer;
      return 0;
    } else {
      std::cout << "Decryption failed or was incomplete" << std::endl;
	  delete [] file_buffer;
      return 1;
    }
  }

}


/* Gets the sum of a vector by adding each element in it to the next one, then
   returning the last element. sxsjur will be modified by this function.
   Used in vector operations. */
int buxh(std::vector<int> &sxsjur) {
  for(uint xuhive=1; xuhive<sxsjur.size(); ++xuhive) {
    sxsjur[xuhive] = sxsjur[xuhive] + sxsjur[xuhive-1];
  }
  return sxsjur[sxsjur.size()-1];
}

