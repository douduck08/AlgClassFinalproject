#include <iostream>
#include "pattern.h"
using namespace std;
# include <algorithm>
# include <ctime>
# include <cstdlib>
#define INIT_CAND_NUM 4
#define ITER_NUM 1000

bool sortByWinNum(Component *i, Component *j)
{
  return (i->_winInComp.size() < j->_winInComp.size());
}
bool sortByDiffSum(Component *i, Component *j)
{
  return (i->_diffSum < j->_diffSum);
}

int main(int argc, char **argv)
{
  srand(time(NULL));
  Pattern pat;
  pat.readfile( argv[1] );
  //pat.readfile( "input/test1" );
  pat.nodeInitailize();
  pat.edgeInitailize();

  pat.findcomponent();
  pat.color_comps();

  pat.setBox();
  pat.setWindows();
  pat.setGeneBase();
  // for(int i = 0 ; i < pat._compSize ; i++)
  //   cout << "#" << i+1 <<" "<<pat._comps[i]->_colorable << endl;
  Example best;
  pat.genGene(best);
  pat.measureArea(best);
  for(int i=0; i<ITER_NUM; ++i){
    Example tmp;
    pat.genGene(tmp);
    pat.measureArea(tmp);
    if(pat.getScore(tmp) < pat.getScore(best))
      best = tmp;
  /*  cout <<endl<< "tmp = ";
    for(int j=0; j<4;++j)
      cout << tmp._colorGene[j];
    cout << " score = "<<pat.getScore(tmp) << endl;
  */
  }
  cout <<"best = "<< pat.getScore(best)<<endl;

  Example parUnsort;
  Example parSort;
  Example parDiffSumSort;

  pat.greedy(parUnsort);
  
  sort(pat._colorComps.begin(), pat._colorComps.end(), sortByWinNum);
  pat.greedy(parSort);

  sort(pat._colorComps.begin(), pat._colorComps.end(), sortByDiffSum);
  pat.greedy(parDiffSumSort);

  cout << "unsort = " << pat.getScore(parUnsort) << endl;
  cout << "sort = " << pat.getScore(parSort) << endl;
  cout << "diff = " << pat.getScore(parDiffSumSort) << endl;
  /*
  Example initExp[8];
  Example tmpExp[8];

  for(int i=0; i < 8; ++i)
    pat.genGene(tmpExp[i]);
  
  Example* seleteExp;

  for(int i=0; i < ITER_NUM; ++i){
    seleteExp = pat.findbest(tmpExp); // return INIT_CAND_NUM / 2 number of Example
    
    for(int j=0; j < 8; ++j){
      if(j < 8/2)
        tmpExp[j] = seleteExp[j];
      else
        pat.genGene(tmpExp[j]);
    }
    if(i!=ITER_NUM-1)
      delete [] seleteExp;
  }
  for(int i=0; i<4; ++i)
    cout << pat.getScore(seleteExp[i])<<endl;
  */
  return 0;
}
