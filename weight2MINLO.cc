#include "TFile.h"
#include "TGraph.h"

#include <algorithm>  // ---- for std::min



std::vector<TGraph*> _weightSources;

TFile* _source = TFile::Open("NNLOPS_reweight.root");


void initialize_weight2MINLO (){
  
  for (unsigned iJet = 0; iJet != 4; iJet++) {
    _weightSources.push_back( (TGraph*) (_source->Get(TString::Format("gr_NNLOPSratio_pt_powheg_%djet", iJet))) );
  }
  
}


float weight2MINLO(float HTXS_Higgs_pt, int HTXS_njets30){
  
  return 1.0;
    
  switch (HTXS_njets30) {
    case 0:
//       return _weightSources[0]->Eval(    std::min (HTXS_Higgs_pt, float(125.) ) );
      return _weightSources[0]->Eval(    std::min (HTXS_Higgs_pt, float(80.) ) );  // AM
    case 1:                                                             
      return _weightSources[1]->Eval(    std::min (HTXS_Higgs_pt, float(625.) ) );
    case 2:                                                             
      return _weightSources[2]->Eval(    std::min (HTXS_Higgs_pt, float(800.) ) );
    case 3:                                                             
      return _weightSources[3]->Eval(    std::min (HTXS_Higgs_pt, float(925.) ) );
    default:
      return 1.;
  }
  
   
}


