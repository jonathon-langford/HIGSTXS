//
//
//

typedef std::vector<double> NumV;

//
// The input kinematics should be based on the truth quantites of
// defined according to:
// https://gitlab.cern.ch/LHCHIGGSXS/LHCHXSWG2/STXS/Classification/-/blob/master/HiggsTemplateCrossSections.h
// namely Higgs boson pT (in GeV!), jet multiplicity with 30 GeV pT threshold
// invariant mass of jets, ...
// namely the Stage 1.2 STXS categories
//
// This is the uncertainty scheme for the interpretation of the STXS measurement
// Stage 1.2
//
// Details in LHCHXSWG-2020-001
//
//
// Aug 12th, 2020
// Andrea Massironi (ggF lhchxswg CMS)
//

//
// NB: the only input from YR4 and higher order calculation is about jet binning
//     All the rest coming from scale variations using MINLO HJ sample with NNLOPS reweighting
//
//

//
// Stage 1.0 was here: https://indico.cern.ch/event/618048/attachments/1430472/2204126/ggF_qcd_uncertainty_2017.cxx
//


//
// Stage 1.2 :     17 bins
//
//
// Gluon fusion
//      GG2H_FWDH = 100,
//      GG2H_PTH_200_300 = 101,
//      GG2H_PTH_300_450 = 102,
//      GG2H_PTH_450_650 = 103,
//      GG2H_PTH_GT650 = 104,
//      GG2H_0J_PTH_0_10   = 105,
//      GG2H_0J_PTH_GT10   = 106,
//      GG2H_1J_PTH_0_60 = 107,
//      GG2H_1J_PTH_60_120 = 108,
//      GG2H_1J_PTH_120_200 = 109,
//      GG2H_GE2J_MJJ_0_350_PTH_0_60 = 110,
//      GG2H_GE2J_MJJ_0_350_PTH_60_120 = 111,
//      GG2H_GE2J_MJJ_0_350_PTH_120_200 = 112,
//      GG2H_GE2J_MJJ_350_700_PTH_0_200_PTHJJ_0_25 = 113,
//      GG2H_GE2J_MJJ_350_700_PTH_0_200_PTHJJ_GT25 = 114,
//      GG2H_GE2J_MJJ_GT700_PTH_0_200_PTHJJ_0_25 = 115,
//      GG2H_GE2J_MJJ_GT700_PTH_0_200_PTHJJ_GT25 = 116,
//

//
// Edges:
// Njets :    0/1   1/2   yield   res                    --->   4 nuisances
// ptH inclusive:                     200, 300, 450, 650 --->   4 nuisances
// pth 0 jet:                         10                 --->   1 nuisance
// pth 1 jet:                         60, 120            --->   2 nuisances
// pth 2 jet (mjj < 350) :            60, 120            --->   2 nuisances
// pthhjj 2 jet (350 < mjj < 700) :   25                 --->   1 nuisance (similar to 3rd jet veto)
// pthhjj 2 jet (mjj > 700)       :   25                 --->   1 nuisance (similar to 3rd jet veto) 
// mjj :      350    700                                 --->   2 nuisances
//


//
// Cross sections of ggF with =0, =1, and >=2 jets
// Obtained from Powheg NNLOPS. Scaled to sigma(N3LO) @125.09 = 48.52 pb
// set as global variables (sorry!) since used both by BLPTW and JVE
//
// NB: to be updated ??? FIXME
//
static double g_sig0=30.117, g_sig1=12.928, g_sig_ge2=5.475, g_sig_ge1 = g_sig1+g_sig_ge2, g_sig_tot=g_sig0+g_sig_ge1, g_sig_vbfTopo = 0.630, g_sig_ge2noVBF=g_sig_ge2-g_sig_vbfTopo, g_sig_ge1noVBF=g_sig_ge1-g_sig_vbfTopo;


//
// from 10% to 1.10
//
NumV qcd_ggF_uncertSF_stage_1p2(int STXS) {
  return unc2sf(qcd_ggF_uncert_stage_1p2(STXS));
}


NumV qcd_ggF_uncert_stage_1p2(int STXS) { // 17 nuisances

  // Njets :    0/1   1/2   yield   res                    --->   4 nuisances
  // ptH inclusive:                     200, 300, 450, 650 --->   4 nuisances
  // pth 0 jet:                         10                 --->   1 nuisance
  // pth 1 jet:                         60, 120            --->   2 nuisances
  // pth 2 jet (mjj < 350) :            60, 120            --->   2 nuisances
  // pthhjj 2 jet (350 < mjj < 700) :   25                 --->   1 nuisance (similar to 3rd jet veto)
  // pthhjj 2 jet (mjj > 700)       :   25                 --->   1 nuisance (similar to 3rd jet veto) 
  // mjj :      350    700                                 --->   2 nuisances
  
  NumV result = jetBinUnc(STXS);
  result.push_back (ptInclusive(STXS));
  result.push_back (pt0j(STXS));
  result.push_back (pt1j(STXS));
  result.push_back (pt2j(STXS));
  result.push_back (pthjjlowmjj(STXS));
  result.push_back (pthjjhighmjj(STXS));
  result.push_back (mjj(STXS));
  
  return result;
  
}



// Gaussian uncertainty propagation
// event weight = 1.0 + % uncertainty
//
// e.g.   10% -> 1.10
//

NumV unc2sf(const NumV &unc) {
  NumV sfs; 
  for (auto u:unc) sfs.push_back(1.0+u);
  return sfs;
}




NumV jetBinUnc(int STXS) {
  int Njets30;
  
  // pTH > 200 inclusive in njet, return inclusive norm and resummation unc (0 for njet migrations)
  if (STXS >= 101 && STXS <= 104) return {0.0453,0.0209,0,0}
  
  if (STXS == 105 || STXS == 106)                Njets30 = 0;
  if (STXS == 107 || STXS == 108 || STXS == 109) Njets30 = 1;
  if (STXS >= 110 && STXS <= 116)                Njets30 = 2;
  
  NumV result = blptw(Njets30);
  
  // FIXME: VBF region currently given GE2J unc. Is this valid? Previously set to 0?
  return result;
}


//
// Jet bin uncertainties 
//
// e.g. 1%, 20%, ...
//
NumV blptw(int Njets30) {
  
  static std::vector<double> sig({g_sig0,g_sig1,g_sig_ge2noVBF}); // NNLOPS subtracting VBF
  
  // BLPTW absolute uncertainties in pb
  static vector<double> yieldUnc({ 1.12, 0.66, 0.42});
  static vector<double> resUnc  ({ 0.03, 0.57, 0.42});
  static vector<double> cut01Unc({-1.22, 1.00, 0.21});
  static vector<double> cut12Unc({    0,-0.86, 0.86});
  
  // account for missing EW+quark mass effects by scaling BLPTW total cross section to sigma(N3LO)
  double sf = 48.52/47.4;
  int jetBin = (Njets30 > 1 ? 2 : Njets30);
  double normFact = sf/sig[jetBin];
  
  return {
    yieldUnc[jetBin]*normFact, 
    resUnc[jetBin]*normFact,
    cut01Unc[jetBin]*normFact,
    cut12Unc[jetBin]*normFact 
  };
}


//      GG2H_PTH_200_300 = 101,
//      GG2H_PTH_300_450 = 102,
//      GG2H_PTH_450_650 = 103,
//      GG2H_PTH_GT650 = 104,
//      GG2H_0J_PTH_0_10   = 105,
//      GG2H_0J_PTH_GT10   = 106,
//      GG2H_1J_PTH_0_60 = 107,
//      GG2H_1J_PTH_60_120 = 108,
//      GG2H_1J_PTH_120_200 = 109,
//      GG2H_GE2J_MJJ_0_350_PTH_0_60 = 110,
//      GG2H_GE2J_MJJ_0_350_PTH_60_120 = 111,
//      GG2H_GE2J_MJJ_0_350_PTH_120_200 = 112,
//      GG2H_GE2J_MJJ_350_700_PTH_0_200_PTHJJ_0_25 = 113,
//      GG2H_GE2J_MJJ_350_700_PTH_0_200_PTHJJ_GT25 = 114,
//      GG2H_GE2J_MJJ_GT700_PTH_0_200_PTHJJ_0_25 = 115,
//      GG2H_GE2J_MJJ_GT700_PTH_0_200_PTHJJ_GT25 = 116,
//

NumV ptInclusive(int STXS) {
  // ptH inclusive:                     200, 300, 450, 650 --->   4 nuisances
  
  // < 200 GeV
  if (STXS >= 105 && STXS <= 116) return {-0.002408, 0.0, 0.0, 0.0};
  // > 200 GeV
  else if (STXS >= 101 && STXS <= 104) {
    if (STXS == 101)  return {0.193581, -0.002713,  0.000000,  0.000000};
    if (STXS == 102)  return {0.193581,  0.010221, -0.001005,  0.000000};
    if (STXS == 103)  return {0.193581,  0.010221,  0.005824, -0.000385};
    if (STXS == 104)  return {0.193581,  0.010221,  0.005824,  0.002701};
  }
  else { // nuisance = 0
    return {0.00, 0.00, 0.00, 0.00};
  }
  
}



//      GG2H_0J_PTH_0_10   = 105,
//      GG2H_0J_PTH_GT10   = 106,

NumV pt0j(int STXS) {
  // pth 0 jet:                         10                 --->   1 nuisance
  
  // < 10
  if (STXS == 105 ) return {-0.103177};
  // > 10
  else if (STXS == 106 ) return {0.032871};
  //
  else { // nuisance = 0
    return {0.00};
  }
}




//      GG2H_1J_PTH_0_60 = 107,
//      GG2H_1J_PTH_60_120 = 108,
//      GG2H_1J_PTH_120_200 = 109,

NumV pt1j(int STXS) {
  // pth 1 jet:                         60, 120            --->   2 nuisances
  
  // pt < 60
  if (STXS == 107 ) return {-0.031176, -0.008705};
  // 60 < pt < 120
  else if (STXS == 108 ) return {0.042038, -0.008705};
  // 120 < pt < 200
  else if (STXS == 109 ) return {0.042038, 0.140754};
  //
  else { // nuisance = 0
    return {0.00, 0.00};
  } 
}



//      GG2H_GE2J_MJJ_0_350_PTH_0_60 = 110,
//      GG2H_GE2J_MJJ_0_350_PTH_60_120 = 111,
//      GG2H_GE2J_MJJ_0_350_PTH_120_200 = 112,

NumV pt2j(int STXS) {
  // pth 2 jet (mjj < 350) :            60, 120            --->   2 nuisances
  
  // pt < 60
  if (STXS == 110 ) return {-0.051793, -0.017905};
  // 60 < pt < 120
  else if (STXS == 111 ) return {0.023678, -0.017905};
  // 120 < pt < 200
  else if (STXS == 112 ) return {0.023678, 0.061627};
  //
  else { // nuisance = 0
    return {0.00, 0.00};
  } 
}







//      GG2H_GE2J_MJJ_350_700_PTH_0_200_PTHJJ_0_25 = 113,
//      GG2H_GE2J_MJJ_350_700_PTH_0_200_PTHJJ_GT25 = 114,

NumV pthjjlowmjj(int STXS) {
  // pthhjj 2 jet (350 < mjj < 700) :   25                 --->   1 nuisance (similar to 3rd jet veto)
  
  // pthjj < 25
  if (STXS == 113 ) return {-0.015516};
  // pthjj > 25
  else if (STXS == 114 ) return {0.010452};
  //
  else { // nuisance = 0
    return {0.00};
  } 
}





//      GG2H_GE2J_MJJ_GT700_PTH_0_200_PTHJJ_0_25 = 115,
//      GG2H_GE2J_MJJ_GT700_PTH_0_200_PTHJJ_GT25 = 116,

NumV pthjjhighmjj(int STXS) {
  // pthhjj 2 jet (mjj > 700)       :   25                 --->   1 nuisance (similar to 3rd jet veto) 
  
  // pthjj < 25
  if (STXS == 115 ) return {-0.014963};
  // pthjj > 25
  else if (STXS == 116 ) return {0.009898};
  //
  else { // nuisance = 0
    return {0.00};
  } 
}



//      GG2H_GE2J_MJJ_0_350_PTH_0_60 = 110,
//      GG2H_GE2J_MJJ_0_350_PTH_60_120 = 111,
//      GG2H_GE2J_MJJ_0_350_PTH_120_200 = 112,
//      GG2H_GE2J_MJJ_350_700_PTH_0_200_PTHJJ_0_25 = 113,
//      GG2H_GE2J_MJJ_350_700_PTH_0_200_PTHJJ_GT25 = 114,
//      GG2H_GE2J_MJJ_GT700_PTH_0_200_PTHJJ_0_25 = 115,
//      GG2H_GE2J_MJJ_GT700_PTH_0_200_PTHJJ_GT25 = 116,

NumV mjj(int STXS) {
  // mjj :      350    700                                 --->   2 nuisances
  
  // mjj < 350
  if (STXS == 110 || STXS == 112 || STXS == 113) return {-0.005716, -0.001748};
  // 350 < mjj < 700
  else if (STXS == 113 || STXS == 114) return {0.026375, -0.001748};
  // mjj > 700
  else if (STXS == 115 || STXS == 116) return {0.026375, 0.030696};
  //
  else { // nuisance = 0
    return {0.00, 0.00};
  } 
}





