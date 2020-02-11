
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



void setupTGraph(TGraph* graph, int icolor) {
  
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
  
  
  
  graph->SetLineWidth(3);
  graph->SetLineStyle(2);
  graph->SetLineColor(color[icolor]);
  graph->SetMarkerColor(color[icolor]);
  graph->SetMarkerSize(1);
  graph->SetMarkerStyle(20+icolor);
}






void CheckReweight (std::string input_file_root = "nanoAOD__Fall2017_nAOD_v2_94X__GluGluHToWWTo2L2NuPowheg_M125_1.root") {
  
  gStyle->SetOptStat(0);
  setTDRStyle();
  
  //---- defined in weight2MINLO.cc
  initialize_weight2MINLO();
  
  
  TFile *file = TFile::Open(input_file_root.c_str());
  TTree* Events = (TTree*) file->Get("Events");
  
  TH1F* histo[4];
    
  for (int iJet=0; iJet<4; iJet++) {
   
    histo[iJet] = new TH1F (TString::Format("histo_pt_%djet", iJet), "", 200, 0, 1000);
    
    Events->Draw((TString::Format("HTXS_Higgs_pt >> histo_pt_%djet", iJet)), (TString::Format("HTXS_njets30 == %d", iJet)) , "goff");
    
    setupHisto( histo[iJet], iJet);
    
   }
  
  
  
  
  TCanvas* cc_useful = new TCanvas ("cc_useful" , "", 900,600);
  cc_useful->Divide(1,2);
  cc_useful->SetRightMargin(0.2);
  
  
  TLegend* legend_useful = new TLegend(0.81,0.25,0.99,0.90);
  
  cc_useful->cd(1);
  
  for (int iJet=0; iJet<4; iJet++) {
 
    if (iJet==0){
      histo[iJet]->DrawNormalized();
      histo[iJet]->GetXaxis()->SetTitle("Higgs p_{T}");
    }
    else {
      histo[iJet]->DrawNormalized("same");      
    }
   
    legend_useful->AddEntry(histo[iJet], TString::Format("jet = %d", iJet) ,"f");
  }
  
  legend_useful->Draw();
  
  cc_useful->cd(2);
  
  
  for (int iJet=3; iJet>=0; iJet--) {
    setupTGraph( _weightSources[iJet], iJet);
    if (iJet==3){ 
      _weightSources[iJet]->Draw("APL");
      _weightSources[iJet]->GetXaxis()->SetRangeUser(0,1000);
      _weightSources[iJet]->GetXaxis()->SetTitle("Higgs p_{T}");
    }
    else {
      _weightSources[iJet]->Draw("PL");
    }
    
  }
  
  
  
  
  
  TCanvas* cc_separate = new TCanvas ("cc_separate" , "", 900,600);
  cc_separate->Divide(2,2);
  
  for (int iJet=0; iJet<4; iJet++) {
    cc_separate-> cd( iJet+1 );
    
    float integral = histo[iJet]->Integral();
    histo[iJet]->Scale(10./ integral);
    
    histo[iJet]->Draw("histo");
    histo[iJet]->GetXaxis()->SetTitle("Higgs p_{T}");
    histo[iJet]->GetYaxis()->SetRangeUser(0.0, 3.0);
    
    _weightSources[iJet]->Draw("PL");
    
  }


  
  
  
}





