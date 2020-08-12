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
//     All the rest is coming from scale variations
//
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
static double g_sig0=30.117, g_sig1=12.928, g_sig_ge2=5.475,
g_sig_ge1 = g_sig1+g_sig_ge2, g_sig_tot=g_sig0+g_sig_ge1, g_sig_vbfTopo = 0.630,
g_sig_ge2noVBF=g_sig_ge2-g_sig_vbfTopo, g_sig_ge1noVBF=g_sig_ge1-g_sig_vbfTopo;




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


NumV jetBinUnc(int STXS) {
  int Njets30;
  
  if (STXS == 105 || STXS == 106)                Njets30 = 0;
  if (STXS == 107 || STXS == 108 || STXS == 109) Njets30 = 1;
  if (STXS >= 110 && STXS <= 116)                Njets30 = 2;
  
  NumV result = blptw(Njets30);
  
  // set jet bin uncertainties to zero if we are in the VBF phase-space  ----> why???? FIXME
//   if (result.back()!=0.0) result[0]=result[1]=result[2]=result[3]=0.0;
  return result;
}


//
// Jet bin uncertainties 
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


NumV ptInclusive(int STXS) {
  // ptH inclusive:                     200, 300, 450, 650 --->   4 nuisances
  
  // < 200 GeV
  if (STXS >= 105 && STXS <= 116) return {1.00, 1.00, 1.00, 1.00};
  // > 200 GeV
  if (STXS >= 101 && STXS <= 104) {
    if (STXS == 101)  return {1.00, 1.00, 1.00, 1.00};
    if (STXS == 102)  return {1.00, 1.00, 1.00, 1.00};
    if (STXS == 103)  return {1.00, 1.00, 1.00, 1.00};
    if (STXS == 104)  return {1.00, 1.00, 1.00, 1.00};
  }
  
}







// migration uncertaitny around the 60 GeV boundary
double pT60(double pT, int Njets30) {
  if (Njets30==0) return 0;
  if (Njets30==1) return interpol(pT,20,-0.1,100,0.1);
  return interpol(pT,0,-0.1,180,0.10); // >=2 jets
}



NumV qcd_ggF_uncert_wg1(int Njets30, double pT, int STXS) {
  NumV result = jetBinUnc(Njets30,STXS);
  
  // High pT uncertainty 
  static double y1_1 = -0.12, y2_1 = 0.16, x2_1 = 150;
  static double y1_ge2 = -0.12, y2_ge2 = 0.16, x2_ge2 = 225;
  double pTH_unc = 0.0;
  if      (Njets30==1) pTH_unc = interpol(pT,0,y1_1,x2_1,y2_1);
  else if (Njets30>=2) pTH_unc = interpol(pT,0,y1_ge2,x2_ge2,y2_ge2);
  result.push_back(pTH_unc);
  
  // finite top mass uncertainty
  result.push_back(qm_t(pT));
  
  return result;
}

NumV qcd_ggF_uncert_stxs(int Njets30, double pT, int STXS) {
  NumV result = jetBinUnc(Njets30,STXS);
  // Dsig60, Dsig120 and Dsig200 are extracted from Powheg NNLOPS
  // scale variations (envelope of 26 variations)
  //   sig(60,200)  = 9.095 +/- 1.445 pb, BLPTW 10.9%
  //   sig(120,200) = 1.961 +/- 0.401 pb, BLPTW 13.1%
  //   sig(200,inf) = 0.582 +/- 0.121 pb, BLPTW 15.1%
  static double sig0_60=8.719, sig60_200=9.095, sig120_200=1.961, 
  sig0_120=sig0_60+sig60_200-sig120_200, sig200_plus=0.582; // 0.121 (-) 0.151*0.582
  static double Dsig60_200=1.055, Dsig120_200=0.206, Dsig200_plus=0.0832; // with 2M evts, and subtraction
  double dsig60=0, dsig120=0, dsig200=0;
  if (Njets30>=1) {
    if      (pT<60)  dsig60=-Dsig60_200/sig0_60;  // -17.2%
    else if (pT<200) dsig60=Dsig60_200/sig60_200; // +16.0%
    
    if      (pT<120) dsig120 = -Dsig120_200/sig0_120;   //  -2.6%
    else if (pT<200) dsig120 =  Dsig120_200/sig120_200; // +20.8%
    
    if (pT>200) dsig200=Dsig200_plus/sig200_plus; // +14.3%
  }
  result.push_back(dsig60);
  result.push_back(dsig120);
  result.push_back(dsig200);
  return result;
}

NumV qcd_ggF_uncert_jve(int Njets30, double pT, int STXS) {
  NumV result;
  // Central values for eps0 and eps1 from Powheg NNLOPS
  //   eps0 = 0.617 +- 0.012 <= from Fabrizio and Pier
  //   eps1 = 0.681 +- 0.057 <= from Fabrizio and Pier
  // and setting inclusive uncertainty to 3.9% (YR4 for N3LO)
  static double D01=g_sig_tot*0.012, D12=g_sig_ge1*0.057;
  
  result.push_back(0.039); // YR4 inclusive cross section (Gaussian)
  
  // mig 0 -> 1 from eps0. Taking out VBF topology piece
  double d01 = Njets30==0 ? -D01/g_sig0 : D01/g_sig_ge1noVBF; 
  result.push_back(d01);
  
  double d12 = 0.0;
  if      (Njets30==1) d12 = -D12/g_sig1;
  else if (Njets30>=2) d12 =  D12/g_sig_ge2noVBF;
  result.push_back(d12);
  
  // VBF-topology
  result.push_back(vbf_2j(STXS));
  result.push_back(vbf_3j(STXS));
  // set jet bin uncertainties to zero if we are in the VBF phase-space
  if (result.back()!=0.0) result[0]=result[1]=result[2]=0.0;
  
  // pTH uncertainties from 2017 scheme
  result.push_back(pT60(pT,Njets30));
  result.push_back(pT120(pT,Njets30));
  result.push_back(qm_t(pT));
  return result;
}


// Gaussian uncertainty propagation
// event weihgt = 1.0 + 1-stdDev-fractional-uncertainty-amplitudie * NumberOfStdDev
NumV unc2sf(const NumV &unc, double Nsigma) {
  NumV sfs; for (auto u:unc) sfs.push_back(1.0+Nsigma*u); return sfs;
}

NumV qcd_ggF_uncertSF_wg1(int Njets30, double pT, int STXS_Stage1, double Nsigma) {
  return unc2sf(qcd_ggF_uncert_wg1(Njets30,pT,STXS_Stage1),Nsigma);
}

NumV qcd_ggF_uncertSF_stxs(int Njets30, double pT, int STXS_Stage1, double Nsigma) {
  return unc2sf(qcd_ggF_uncert_stxs(Njets30,pT,STXS_Stage1),Nsigma);
}

NumV qcd_ggF_uncertSF_2017(int Njets30, double pT, int STXS_Stage1, double Nsigma) {
  return unc2sf(qcd_ggF_uncert_2017(Njets30,pT,STXS_Stage1),Nsigma);
}

NumV qcd_ggF_uncertSF_jve(int Njets30, double pT, int STXS_Stage1, double Nsigma) {
  return unc2sf(qcd_ggF_uncert_jve(Njets30,pT,STXS_Stage1),Nsigma);
}