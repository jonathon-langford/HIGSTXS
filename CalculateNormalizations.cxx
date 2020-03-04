
#include "tdrstyle.C"
#include <stdlib.h>


#include "weight2MINLO.cc"


void setupHisto(TH1F* histo, int icolor) {
  
  Color_t* color = new Color_t [200];
  color[0] = kRed ;
  color[1] = kAzure + 10 ;
  color[2] = kYellow + 2 ;
  color[3] = kGreen ;
  color[4] = kGreen + 4 ;
  color[5] = kBlue ;
  color[6] = kCyan ;
  color[7] = kPink + 1 ;
  color[8] = kBlack ;
  color[9] = kYellow + 4 ;
  for (int i=0; i<30; i++) {
    color[i+10] = kBlue + i;
  }
  
  
  
  histo->SetLineWidth(2);
  histo->SetLineColor(color[icolor]);
  histo->SetMarkerColor(color[icolor]);
  histo->SetMarkerSize(1);
  histo->SetMarkerStyle(20+icolor);
}






void CalculateNormalizations (std::string input_file_root = "nanoAOD__Fall2017_nAOD_v2_94X__GluGluHToWWTo2L2NuPowheg_M125_1.root") {
  
  gStyle->SetOptStat(0);
  setTDRStyle();
  
  //---- defined in weight2MINLO.cc
  initialize_weight2MINLO();
  
  
  
  TFile *file = TFile::Open(input_file_root.c_str());
  TTree* Events = (TTree*) file->Get("Events");
  
  int max_number_of_STXS_bins = 500;
  
  TH1F* histo = new TH1F ("histo", "", max_number_of_STXS_bins, 0, max_number_of_STXS_bins);

  TH1F* histo_scale[9];
  
  
  Events->Draw("HTXS_stage_1_pTjet30 >> histo", "1");
  
//   ... including powheg to minlo reweighting
  
//   Events->Draw("HTXS_stage_1_pTjet30 >> histo", "weight2MINLO(HTXS_Higgs_pt,HTXS_njets30)");
  
  
  
    
//   LHEWeight_originalXWGTUP
//   LHEScaleWeight  [9]          (and then LHEPdfWeight)  [103]
//   https://cms-nanoaod-integration.web.cern.ch/integration/master-102X/mc102X_doc.html#HTXS
//   
//   LHEScaleWeight[4] --> always "1" ---> this is already the ratio!
//
  
  for (int i=0; i<9; i++) {
    
    TString name = Form ("histo_%d", i);
    histo_scale[i] = new TH1F (name.Data(), "", max_number_of_STXS_bins, 0, max_number_of_STXS_bins);
    
    TString weight = Form ("LHEScaleWeight[%d]", i);
    TString whattodraw = Form ("HTXS_stage_1_pTjet30 >> %s", name.Data());
    
    //   ... including powheg to minlo reweighting
//     TString weight = Form ("LHEScaleWeight[%d]*weight2MINLO(HTXS_Higgs_pt,HTXS_njets30)", i);
    
    Events->Draw(whattodraw.Data(), weight.Data());
  
    
    
  }
  
  //---- now write
//   for (int iBin=0; iBin<max_number_of_STXS_bins; iBin++) {
//     float integral_nominal = histo->GetBinContent (iBin+1);
//     if (integral_nominal != 0) {
//       std::cout << " [" << iBin << "] => " << integral_nominal ;
//       std::cout << std::endl;
//     }
//   }
//   
//   std::cout << std::endl;
//   std::cout << std::endl;
//   std::cout << std::endl;
  
  
  
  for (int iBin=0; iBin<max_number_of_STXS_bins; iBin++) {
    float integral_nominal = histo->GetBinContent (iBin+1);
    if (integral_nominal != 0) {
      std::cout << " [" << iBin << "] => " << integral_nominal << " ::: ";
      for (int i=0; i<9; i++) {
        if (i==2 || i==6) continue;  // exclude the cases where up*down = 1
        
        float integral_varied = histo_scale[i]->GetBinContent (iBin+1);
        std::cout << " " << integral_varied << " , ";
      } 
      std::cout << std::endl;
    }
  }
  
  
  std::cout << std::endl;
  std::cout << std::endl;
  std::cout << std::endl;
  
  std::cout << " Normalized " << std::endl;
  
  //---- normalized
  
  for (int iBin=0; iBin<max_number_of_STXS_bins; iBin++) {   
    float integral_nominal = histo->GetBinContent (iBin+1);
    if (integral_nominal != 0) {
      std::cout << " [" << iBin << "] =>  ::: ";
      for (int i=0; i<9; i++) {
        if (i==2 || i==6) continue;  // exclude the cases where up*down = 1
        float integral_varied = histo_scale[i]->GetBinContent (iBin+1);
        std::cout << " " << (integral_varied-integral_nominal)/integral_nominal*100. << " % , ";
      }
      std::cout << std::endl;
    }
  }
  
  
  std::cout << std::endl;
  std::cout << std::endl;
  std::cout << std::endl;
  
  
  
  
  
  //   # Gluon fusion
  //   'GG2H_FWDH' : 100,                             |   |eta_h| > 2.5
  //   'GG2H_VBFTOPO_JET3VETO' : 101,                 |    2 jet
  //   'GG2H_VBFTOPO_JET3' : 102,                     |    3 jet
  //   'GG2H_0J'   : 103,                             |    0 jet
  //   'GG2H_1J_PTH_0_60' : 104,                      |    1 jet
  //   'GG2H_1J_PTH_60_120' : 105,                    |    1 jet
  //   'GG2H_1J_PTH_120_200' : 106,                   |    1 jet
  //   'GG2H_1J_PTH_GT200' : 107,                     |    1 jet
  //   'GG2H_GE2J_PTH_0_60' : 108,                    |    2 jet
  //   'GG2H_GE2J_PTH_60_120' : 109,                  |    2 jet
  //   'GG2H_GE2J_PTH_120_200' : 110,                 |    2 jet
  //   'GG2H_GE2J_PTH_GT200' : 111,                   |    2 jet
  //   
  
  //   
  //   N = nominal, U = up, D = down
  // 
  //   DU and UD not considered later
  //   
  std::map< int, float > integral_DD;
  std::map< int, float > integral_DN;
  std::map< int, float > integral_DU; // *
  std::map< int, float > integral_ND;
  std::map< int, float > integral_NN;
  std::map< int, float > integral_NU;
  std::map< int, float > integral_UD; // *
  std::map< int, float > integral_UN;
  std::map< int, float > integral_UU;
  
  std::vector< std::map< int, float > >  integrals;
  integrals.push_back(integral_DD);       // 0
  integrals.push_back(integral_DN);       // 1
  integrals.push_back(integral_DU); // *  // 2
  integrals.push_back(integral_ND);       // 3
  integrals.push_back(integral_NN);       // 4  -> NN
  integrals.push_back(integral_NU);       // 5
  integrals.push_back(integral_UD); // *  // 6
  integrals.push_back(integral_UN);       // 7
  integrals.push_back(integral_UU);       // 8
  
  
  //   
  //   LHEScaleWeight      
  //   
  //   https://cms-nanoaod-integration.web.cern.ch/integration/master-94X/mc94Xv2_doc.html#LHEScaleWeight
  //   
  //   Float_t LHE scale variation weights (w_var / w_nominal);
  //   [0] is renscfact=0.5d0 facscfact=0.5d0 ;                    DD
  //   [1] is renscfact=0.5d0 facscfact=1d0 ;                      DN
  //   [2] is renscfact=0.5d0 facscfact=2d0 ;                      DU  *
  //   [3] is renscfact=1d0 facscfact=0.5d0 ;                      ND
  //   [4] is renscfact=1d0 facscfact=1d0 ;                        NN
  //   [5] is renscfact=1d0 facscfact=2d0 ;                        NU
  //   [6] is renscfact=2d0 facscfact=0.5d0 ;                      UD  *
  //   [7] is renscfact=2d0 facscfact=1d0 ;                        UN
  //   [8] is renscfact=2d0 facscfact=2d0                          UU
  //   
  
  
  for (int iBin=0; iBin<max_number_of_STXS_bins; iBin++) {
    float integral_nominal = histo->GetBinContent (iBin+1);
    if (integral_nominal != 0) {
      for (int i=0; i<9; i++) {
        (integrals.at(i))[iBin] = histo_scale[i]->GetBinContent (iBin+1);
      }
    }
  }
  
  
  //   
  //   ---- bins to add for njets   ( it could be useful )
  //   
  //   
  //   103  ->  == 0 jets                             ---> 0 index
  //   104, 105, 106, 107   -> == 1 jet               ---> 1 index
  //   108, 109, 110, 111, 101, 102 --> >= 2 jets     ---> 2 index
  //   
  
  std::cout << " ------------------------------- " << std::endl;
  std::cout << " ---- after merging jt bins ---- " << std::endl;
  std::cout << std::endl;
  
  for (int i=0; i<9; i++) {
    
    (integrals.at(i))[0]  = (integrals.at(i))[103];
    
    (integrals.at(i))[1]  = (integrals.at(i))[104];
    (integrals.at(i))[1] += (integrals.at(i))[105];
    (integrals.at(i))[1] += (integrals.at(i))[106];
    (integrals.at(i))[1] += (integrals.at(i))[107];
    
    (integrals.at(i))[2]  = (integrals.at(i))[108];
    (integrals.at(i))[2] += (integrals.at(i))[109];
    (integrals.at(i))[2] += (integrals.at(i))[110];
    (integrals.at(i))[2] += (integrals.at(i))[111];
    (integrals.at(i))[2] += (integrals.at(i))[101];
    (integrals.at(i))[2] += (integrals.at(i))[102];
    
  }
  
  
  //---- now write:
  
  ofstream file_CrossSections;
  file_CrossSections.open ("CrossSections.txt");
  file_CrossSections << "# "  << std::left << std::setw(12) << "  STXSbin ";
  file_CrossSections << "  "  << std::left << std::setw(12) << "  DD ";
  file_CrossSections << "  "  << std::left << std::setw(12) << "  DN ";
  file_CrossSections << "  "  << std::left << std::setw(12) << "  DU ";
  file_CrossSections << "  "  << std::left << std::setw(12) << "  ND ";
  file_CrossSections << "  "  << std::left << std::setw(12) << "  NN ";
  file_CrossSections << "  "  << std::left << std::setw(12) << "  NU ";
  file_CrossSections << "  "  << std::left << std::setw(12) << "  UD ";
  file_CrossSections << "  "  << std::left << std::setw(12) << "  UN ";
  file_CrossSections << "  "  << std::left << std::setw(12) << "  UU ";
  file_CrossSections << " (cross sections, D = down = 0.5, N = nominal = 1.0, U = up = 2.0) " << std::endl;
  
  
  for (int iBin=0; iBin<max_number_of_STXS_bins; iBin++) {
    float integral_nominal = histo->GetBinContent (iBin+1);
    if (integral_nominal != 0) {
      file_CrossSections << "  " << std::left << std::setw(12) << iBin ;
      for (int i=0; i<9; i++) {
        file_CrossSections << "  " << std::left << std::setw(12) << (integrals.at(i))[iBin];
      }
      file_CrossSections << std::endl;
    }
  }
  
  file_CrossSections.close(); 
  
  
  
  
  ofstream file_Normalization;
  file_Normalization.open ("Normalization.txt");
  file_Normalization << "# "  << std::left << std::setw(12) << "  STXSbin ";
  file_Normalization << "  "  << std::left << std::setw(12) << "  DD ";
  file_Normalization << "  "  << std::left << std::setw(12) << "  DN ";
  file_Normalization << "  "  << std::left << std::setw(12) << "  DU ";
  file_Normalization << "  "  << std::left << std::setw(12) << "  ND ";
  file_Normalization << "  "  << std::left << std::setw(12) << "  NN ";
  file_Normalization << "  "  << std::left << std::setw(12) << "  NU ";
  file_Normalization << "  "  << std::left << std::setw(12) << "  UD ";
  file_Normalization << "  "  << std::left << std::setw(12) << "  UN ";
  file_Normalization << "  "  << std::left << std::setw(12) << "  UU ";
  file_Normalization << " (nominal / varied, D = down = 0.5, N = nominal = 1.0, U = up = 2.0) " << std::endl;
  
  
  for (int iBin=0; iBin<max_number_of_STXS_bins; iBin++) {
    float integral_nominal = histo->GetBinContent (iBin+1);
    if (integral_nominal != 0) {
      file_Normalization << "  " << std::left << std::setw(12) << iBin ;
      for (int i=0; i<9; i++) {
        file_Normalization << "  " << std::left << std::setw(12) << integral_nominal / (integrals.at(i))[iBin];
      }
      file_Normalization << std::endl;
    }
  }
  
  file_Normalization.close(); 
  
  
  
  
  // ---- 1001 = weights_LHE[0] ---> nominal
  //                                                         https://indico.cern.ch/event/494682/contributions/1172505/attachments/1223578/1800218/mcaod-Feb15-2016.pdf
  //      [ 0 ] = 1001                                       <weight id="1001"> muR=0.10000E+01 muF=0.10000E+01 </weight>             Nominal
  //      [ 1 ] = 1002                                       <weight id="1002"> muR=0.10000E+01 muF=0.20000E+01 </weight>             NU
  //      [ 2 ] = 1003                                       <weight id="1003"> muR=0.10000E+01 muF=0.50000E+00 </weight>             ND
  //      [ 3 ] = 1004                                       <weight id="1004"> muR=0.20000E+01 muF=0.10000E+01 </weight>             UN
  //      [ 4 ] = 1005                                       <weight id="1005"> muR=0.20000E+01 muF=0.20000E+01 </weight>             UU
  //      [ 5 ] = 1006                                       <weight id="1006"> muR=0.20000E+01 muF=0.50000E+00 </weight>             UD   -> not used
  //      [ 6 ] = 1007                                       <weight id="1007"> muR=0.50000E+00 muF=0.10000E+01 </weight>             DN
  //      [ 7 ] = 1008                                       <weight id="1008"> muR=0.50000E+00 muF=0.20000E+01 </weight>             DU   -> not used
  //      [ 8 ] = 1009                                       <weight id="1009"> muR=0.50000E+00 muF=0.50000E+00 </weight>             DD
  
  
  
  // improved plotting
  
  int number_of_STXS_bins = 0;
  for (int iBin=0; iBin<max_number_of_STXS_bins; iBin++) {
    float integral_nominal = histo->GetBinContent (iBin+1);
    if (integral_nominal != 0) {
      number_of_STXS_bins++;
    }
  }
    
  TH1F* histo_nice_scale[9];
  
  for (int i=0; i<9; i++) {
    
    TString name = Form ("histo_nice_%d", i);
    histo_nice_scale[i] = new TH1F (name.Data(), "", number_of_STXS_bins, 0, number_of_STXS_bins);

    number_of_STXS_bins = 0;
    for (int iBin=0; iBin<max_number_of_STXS_bins; iBin++) {
      float integral_nominal = histo->GetBinContent (iBin+1);
      if (integral_nominal != 0) {
        number_of_STXS_bins++;
        histo_nice_scale[i] -> SetBinContent (number_of_STXS_bins,  integral_nominal / (integrals.at(i))[iBin]);
      }
    }
    
  }
  
  
  
  TCanvas* cc_nice = new TCanvas ("cc_nice" , "", 900,600);
  cc_nice->SetRightMargin(0.2);
  
  
  TLegend* legend_nice = new TLegend(0.81,0.25,0.99,0.90);
  
  for (int i=0; i<9; i++) {
    setupHisto( histo_nice_scale[i], i);
    if (i==0 || i==8) {
      histo_nice_scale[i]->SetLineWidth(2.0);
    }
    if (i==0) {
      histo_nice_scale[i] -> Draw();
      histo_nice_scale[i] -> GetYaxis() -> SetRangeUser(0.5, 1.5);
      histo_nice_scale[i] -> GetYaxis() -> SetTitle("#sigma nominal / #sigma varied");
    }
    else      histo_nice_scale[i] -> Draw("same");
  }
  
  
  number_of_STXS_bins = 0;
  for (int iBin=0; iBin<max_number_of_STXS_bins; iBin++) {
    float integral_nominal = histo->GetBinContent (iBin+1);
    if (integral_nominal != 0) {
      number_of_STXS_bins++;
      histo_nice_scale[0]->GetXaxis()->SetBinLabel(number_of_STXS_bins, (std::to_string(iBin)).c_str() );
    }  
  }
  
  
  //   # Gluon fusion
  //   'GG2H_FWDH' : 100,                             |   |eta_h| > 2.5
  //   'GG2H_VBFTOPO_JET3VETO' : 101,                 |    2 jet
  //   'GG2H_VBFTOPO_JET3' : 102,                     |    3 jet
  //   'GG2H_0J'   : 103,                             |    0 jet
  //   'GG2H_1J_PTH_0_60' : 104,                      |    1 jet
  //   'GG2H_1J_PTH_60_120' : 105,                    |    1 jet
  //   'GG2H_1J_PTH_120_200' : 106,                   |    1 jet
  //   'GG2H_1J_PTH_GT200' : 107,                     |    1 jet
  //   'GG2H_GE2J_PTH_0_60' : 108,                    |    2 jet
  //   'GG2H_GE2J_PTH_60_120' : 109,                  |    2 jet
  //   'GG2H_GE2J_PTH_120_200' : 110,                 |    2 jet
  //   'GG2H_GE2J_PTH_GT200' : 111,                   |    2 jet
  //   
  
  
  
  legend_nice->AddEntry(histo_nice_scale[0],"#mu_{r} = 0.5, #mu_{f} = 0.5","f");
  legend_nice->AddEntry(histo_nice_scale[1],"#mu_{r} = 0.5, #mu_{f} = 1.0","f");
  legend_nice->AddEntry(histo_nice_scale[2],"#mu_{r} = 0.5, #mu_{f} = 2.0","f");
  legend_nice->AddEntry(histo_nice_scale[3],"#mu_{r} = 1.0, #mu_{f} = 0.5","f");
  legend_nice->AddEntry(histo_nice_scale[4],"#mu_{r} = 1.0, #mu_{f} = 1.0","f");
  legend_nice->AddEntry(histo_nice_scale[5],"#mu_{r} = 1.0, #mu_{f} = 2.0","f");
  legend_nice->AddEntry(histo_nice_scale[6],"#mu_{r} = 2.0, #mu_{f} = 0.5","f");
  legend_nice->AddEntry(histo_nice_scale[7],"#mu_{r} = 2.0, #mu_{f} = 1.0","f");
  legend_nice->AddEntry(histo_nice_scale[8],"#mu_{r} = 2.0, #mu_{f} = 2.0","f");
  legend_nice->Draw();
  
  
  
  
  
  
  
  
  
  
  TH1F* histo_useful_scale[9];
  
  for (int i=0; i<9; i++) {
    
    TString name = Form ("histo_useful_%d", i);
    histo_useful_scale[i] = new TH1F (name.Data(), "", number_of_STXS_bins, 0, number_of_STXS_bins);
    
    number_of_STXS_bins = 0;
    for (int iBin=0; iBin<max_number_of_STXS_bins; iBin++) {
      float integral_nominal = histo->GetBinContent (iBin+1);
      if (integral_nominal != 0) {
        number_of_STXS_bins++;
        histo_useful_scale[i] -> SetBinContent (number_of_STXS_bins,  integral_nominal / (integrals.at(i))[iBin]);
      }
    }
    
  }
  
  TCanvas* cc_useful = new TCanvas ("cc_useful" , "", 900,600);
  cc_useful->SetRightMargin(0.2);
  
  
  TLegend* legend_useful = new TLegend(0.81,0.25,0.99,0.90);
  
  for (int i=0; i<9; i++) {
    setupHisto( histo_useful_scale[i], i);
    if (i==0 || i==8) {
      histo_useful_scale[i]->SetLineWidth(2.0);
    }
    if (i==2 || i==6) continue;
    if (i==0) {
      histo_useful_scale[i] -> Draw();
      histo_useful_scale[i] -> GetYaxis() -> SetRangeUser(0.5, 1.5);
      histo_useful_scale[i] -> GetYaxis() -> SetTitle("#sigma nominal / #sigma varied");
    }
    else      histo_useful_scale[i] -> Draw("same");
  }
  
  
  number_of_STXS_bins = 0;
  for (int iBin=0; iBin<max_number_of_STXS_bins; iBin++) {
    float integral_nominal = histo->GetBinContent (iBin+1);
    if (integral_nominal != 0) {
      number_of_STXS_bins++;
      histo_useful_scale[0]->GetXaxis()->SetBinLabel(number_of_STXS_bins, (std::to_string(iBin)).c_str() );
    }  
  }
  
  
  //   # Gluon fusion
  //   'GG2H_FWDH' : 100,                             |   |eta_h| > 2.5
  //   'GG2H_VBFTOPO_JET3VETO' : 101,                 |    2 jet
  //   'GG2H_VBFTOPO_JET3' : 102,                     |    3 jet
  //   'GG2H_0J'   : 103,                             |    0 jet
  //   'GG2H_1J_PTH_0_60' : 104,                      |    1 jet
  //   'GG2H_1J_PTH_60_120' : 105,                    |    1 jet
  //   'GG2H_1J_PTH_120_200' : 106,                   |    1 jet
  //   'GG2H_1J_PTH_GT200' : 107,                     |    1 jet
  //   'GG2H_GE2J_PTH_0_60' : 108,                    |    2 jet
  //   'GG2H_GE2J_PTH_60_120' : 109,                  |    2 jet
  //   'GG2H_GE2J_PTH_120_200' : 110,                 |    2 jet
  //   'GG2H_GE2J_PTH_GT200' : 111,                   |    2 jet
  //   
  
  
  
  legend_useful->AddEntry(histo_useful_scale[0],"#mu_{r} = 0.5, #mu_{f} = 0.5","f");
  legend_useful->AddEntry(histo_useful_scale[1],"#mu_{r} = 0.5, #mu_{f} = 1.0","f");
//   legend_useful->AddEntry(histo_useful_scale[2],"#mu_{r} = 0.5, #mu_{f} = 2.0","f");
  legend_useful->AddEntry(histo_useful_scale[3],"#mu_{r} = 1.0, #mu_{f} = 0.5","f");
  legend_useful->AddEntry(histo_useful_scale[4],"#mu_{r} = 1.0, #mu_{f} = 1.0","f");
  legend_useful->AddEntry(histo_useful_scale[5],"#mu_{r} = 1.0, #mu_{f} = 2.0","f");
//   legend_useful->AddEntry(histo_useful_scale[6],"#mu_{r} = 2.0, #mu_{f} = 0.5","f");
  legend_useful->AddEntry(histo_useful_scale[7],"#mu_{r} = 2.0, #mu_{f} = 1.0","f");
  legend_useful->AddEntry(histo_useful_scale[8],"#mu_{r} = 2.0, #mu_{f} = 2.0","f");
  legend_useful->Draw();
  
  
  
  
  
}





