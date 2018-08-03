#include <iostream>         
#include <vector>           
#include <cstdlib>          
                            
#include <TChain.h>         
#include <TFile.h>          
#include <TTree.h>          
#include <TString.h>        
#include <TSystem.h>        
#include <TROOT.h>          
                            
#include <TMVA/Tools.h>     
#include <TMVA/Reader.h>    
#include <TMVA/MethodCuts.h>

#include <fstream>                                              
 
using namespace std; 

int main(){
  TMVA::Tools::Instance(); 
  map<string,int> Use; 

  TMVA::Reader* reader[5] = {
    new TMVA::Reader("Color:!Silent"), 
    new TMVA::Reader("Color:!Silent"), 
    new TMVA::Reader("Color:!Silent"), 
    new TMVA::Reader("Color:!Silent"), 
    new TMVA::Reader("Color:!Silent")
  };

  cout<<"Made Readers"<<endl; 
  
  vector<TString> num; 
  num.emplace_back("50");
  num.emplace_back("100");
  num.emplace_back("150");
  num.emplace_back("200");
  num.emplace_back("200p");

  //==============================================================
  Float_t yydr, y1dr, y2dr, ptratio, y1y, y2y, jety, s; 
  Float_t yydy, y1E, y2E, yyE, jetE; 
  Float_t y1pt, y2pt, yypt, jetpt; 

  for (int i=0; i<5; ++i){
    TString outname = "TrainingResult16_pt" + num[i] + ".root";
    TFile* out_root = new TFile(outname, "RECREATE"); 
    
    cout<<""<<endl; 
    cout<<"Made outfile"<<endl; 

    reader[i]->AddVariable("s", &s); 
    reader[i]->AddVariable("yydr", &yydr); 
    reader[i]->AddVariable("y1dr", &y1dr); 
    reader[i]->AddVariable("y2dr", &y2dr); 
    reader[i]->AddVariable("ptratio", &ptratio); 
    reader[i]->AddVariable("y1y", &y1y); 
    reader[i]->AddVariable("y2y", &y2y); 
    reader[i]->AddVariable("jety", &jety); 
    reader[i]->AddVariable("yydy", &yydy); 
    
    reader[i]->AddVariable("y1E", &y1E); 
    reader[i]->AddVariable("y1pt", &y1pt); 
    reader[i]->AddVariable("y2E", &y2E); 
    reader[i]->AddVariable("y2pt", &y2pt);
    reader[i]->AddVariable("yyE", &yyE); 
    reader[i]->AddVariable("yypt", &yypt); 
    reader[i]->AddVariable("jetE", &jetE); 

    cout<<"Reader Variables Added"<<endl;
      
    //=========================================================
  
    //Add method to the reader
    TString w = "/home/voetberg/voetberg/bdt_tmva_outputs/data_pt" + num[i] + "/weights/TMVAClassification_BDT_" + num[i] + ".weights.xml"; 
    reader[i]->BookMVA("method", w); 
  
    cout<<"Method Added to the Reader"<<endl; 
  
    //Output Histograms 
    TH1D* h_sig = new TH1D("Signal", "Signal", 200.,-1.,1.); 
    TH1D* h_bg = new TH1D("Background", "Background", 200.,-1.,1.); 
    TH1D* h_res_s = new TH1D("Res_Signal", "Res_Signal", 200, -1., 1.); 
    TH1D* h_res_b = new TH1D("Res_Background", "Res_Background", 200, -1., 1.); 
    TH1D* h_res_d = new TH1D("Res_Data", "Res_Data", 200, -1., 1.); 
  
    //Read data 
    TFile* in_s = TFile::Open("/msu/data/t3work9/voetberg/tmva_input/16vari/data16_pt" + num[i] + "_sig.root"); 
    TFile* in_b = TFile::Open("/msu/data/t3work9/voetberg/tmva_input/16vari/data16_pt" + num[i] + "_back.root");    TFile* in2 = TFile::Open("/msu/data/t3work9/voetberg/tmva_input/data16_pt" + num[i] + "_reader.root"); 
  
    cout<<"Opened read data"<<endl; 
  
    //===========================================================
 
    TTree* sig = (TTree*)in_s->Get("sigTest"); 
    TTree* bg = (TTree*)in_b->Get("bgTest"); 
    TTree* res_s = (TTree*)in2->Get("sig"); 
    TTree* res_b = (TTree*)in2->Get("bg"); 
    TTree* res_d = (TTree*)in2->Get("data"); 
  
    //===========================================================
    //Signal 
    sig->SetBranchAddress("yydr", &yydr); 
    sig->SetBranchAddress("y1dr", &y1dr); 
    sig->SetBranchAddress("y2dr", &y2dr); 
    sig->SetBranchAddress("yydy", &yydy); 
    sig->SetBranchAddress("y1y", &y1y); 
    sig->SetBranchAddress("y2y", &y2y); 
    sig->SetBranchAddress("jety", &jety); 
    sig->SetBranchAddress("ptratio", &ptratio); 
    sig->SetBranchAddress("s", &s); 
    
    sig->SetBranchAddress("yyE", &yyE); 
    sig->SetBranchAddress("y1E", &y1E); 
    sig->SetBranchAddress("y2E", &y2E); 
    sig->SetBranchAddress("jetE", &jetE); 
  
    sig->SetBranchAddress("yypt", &yypt); 
    sig->SetBranchAddress("y1pt", &y1pt); 
    sig->SetBranchAddress("y2pt", &y2pt); 
  
    //Background
    bg->SetBranchAddress("yydr", &yydr); 
    bg->SetBranchAddress("y1dr", &y1dr); 
    bg->SetBranchAddress("y2dr", &y2dr); 
    bg->SetBranchAddress("yydy", &yydy); 
    bg->SetBranchAddress("y1y", &y1y); 
    bg->SetBranchAddress("y2y", &y2y); 
    bg->SetBranchAddress("jety", &jety); 
    bg->SetBranchAddress("ptratio", &ptratio); 
    bg->SetBranchAddress("s", &s); 
    
    bg->SetBranchAddress("yyE", &yyE); 
    bg->SetBranchAddress("y1E", &y1E); 
    bg->SetBranchAddress("y2E", &y2E); 
    bg->SetBranchAddress("jetE", &jetE); 
  
    bg->SetBranchAddress("yypt", &yypt); 
    bg->SetBranchAddress("y1pt", &y1pt); 
    bg->SetBranchAddress("y2pt", &y2pt); 
  
    //Responses
    //Sig
    res_s->SetBranchAddress("yydr", &yydr); 
    res_s->SetBranchAddress("y1dr", &y1dr); 
    res_s->SetBranchAddress("y2dr", &y2dr); 
    res_s->SetBranchAddress("yydy", &yydy); 
    res_s->SetBranchAddress("y1y", &y1y); 
    res_s->SetBranchAddress("y2y", &y2y); 
    res_s->SetBranchAddress("jety", &jety); 
    res_s->SetBranchAddress("ptratio", &ptratio); 
    res_s->SetBranchAddress("s", &s); 
    
    res_s->SetBranchAddress("yyE", &yyE); 
    res_s->SetBranchAddress("y1E", &y1E); 
    res_s->SetBranchAddress("y2E", &y2E); 
    res_s->SetBranchAddress("jetE", &jetE); 
  
    res_s->SetBranchAddress("yypt", &yypt); 
    res_s->SetBranchAddress("y1pt", &y1pt); 
    res_s->SetBranchAddress("y2pt", &y2pt); 
    
    //Background
    res_b->SetBranchAddress("yydr", &yydr); 
    res_b->SetBranchAddress("y1dr", &y1dr); 
    res_b->SetBranchAddress("y2dr", &y2dr); 
    res_b->SetBranchAddress("yydy", &yydy); 
    res_b->SetBranchAddress("y1y", &y1y); 
    res_b->SetBranchAddress("y2y", &y2y); 
    res_b->SetBranchAddress("jety", &jety); 
    res_b->SetBranchAddress("ptratio", &ptratio); 
    res_b->SetBranchAddress("s", &s); 
    
    res_b->SetBranchAddress("yyE", &yyE); 
    res_b->SetBranchAddress("y1E", &y1E); 
    res_b->SetBranchAddress("y2E", &y2E); 
    res_b->SetBranchAddress("jetE", &jetE); 
  
    res_b->SetBranchAddress("yypt", &yypt); 
    res_b->SetBranchAddress("y1pt", &y1pt); 
    res_b->SetBranchAddress("y2pt", &y2pt); 
    
    //Data
    res_d->SetBranchAddress("yydr", &yydr); 
    res_d->SetBranchAddress("y1dr", &y1dr); 
    res_d->SetBranchAddress("y2dr", &y2dr); 
    res_d->SetBranchAddress("yydy", &yydy); 
    res_d->SetBranchAddress("y1y", &y1y); 
    res_d->SetBranchAddress("y2y", &y2y); 
    res_d->SetBranchAddress("jety", &jety); 
    res_d->SetBranchAddress("ptratio", &ptratio); 
    res_d->SetBranchAddress("s", &s); 
    
    res_d->SetBranchAddress("yyE", &yyE); 
    res_d->SetBranchAddress("y1E", &y1E); 
    res_d->SetBranchAddress("y2E", &y2E); 
    res_d->SetBranchAddress("jetE", &jetE); 
  
    res_d->SetBranchAddress("yypt", &yypt); 
    res_d->SetBranchAddress("y1pt", &y1pt); 
    res_d->SetBranchAddress("y2pt", &y2pt); 
    
    cout<<"Read in Trees"<<endl; 
  
    //==========================================================
  
    const Long64_t sig_entries = sig->GetEntries(); 
    const Long64_t bg_entries = bg->GetEntries(); 
    const Long64_t res_s_entries = res_s->GetEntries(); 
    const Long64_t res_b_entries = res_b->GetEntries(); 
    const Long64_t res_d_entries = res_d->GetEntries(); 
    
    cout<<num[i]<<endl;  
    cout<<"Signal Events: "<<sig_entries<<endl; 
    cout<<"Background Events: "<<bg_entries<<endl; 
    cout<<"Classify Evnts, Pure Signal: "<<res_s_entries<<endl; 
    cout<<"Classify Evnts, Pure Background: "<<res_b_entries<<endl; 
    cout<<"Classify Evnts, Data: "<<res_d_entries<<endl; 
  
    //=============================================================
  
    for (long j=0; j<sig_entries; ++j){
      sig->GetEntry(j); 
      h_sig->Fill(reader[i]->EvaluateMVA("method"));    
    }
  
    cout<<"Filled Signal Histogram"<<endl; 
    
    //=============================================================
    
    for (long j=0; j<bg_entries; ++j){
      bg->GetEntry(j); 
      h_bg->Fill(reader[i]->EvaluateMVA("method")); 
    }
  
    cout<<"Filled Background Histogram"<<endl; 
    
    //==============================================================
    
    float sig_n_s=0, bg_n_s=0;
    for (long j=0; j<res_s_entries; ++j){
      res_s->GetEntry(j); 
      
      float result = reader[i]->EvaluateMVA("method"); 
      h_res_s->Fill(result);
  
      if (result>0){
        sig_n_s+=1; 
      }
      else{
        bg_n_s+=1; 
      }
    }
    cout<<""<<endl; 
    cout<<"Filled Signal Response Histogram:"<<endl;
    cout<<"Signal Ratio: "<<sig_n_s/(res_s_entries)<<endl; 
    cout<<"Background Ratio: "<<bg_n_s/(res_s_entries)<<endl; 
    
    //================================================================
  
    float sig_n_b=0, bg_n_b=0;
    for (long j=0; j<res_b_entries; ++j){
      res_b->GetEntry(j); 
      
      float result = reader[i]->EvaluateMVA("method"); 
      h_res_b->Fill(result);
  
      if (result>0){
        sig_n_b+=1; 
      }
      else{
        bg_n_b+=1; 
      }
    }
    cout<<""<<endl; 
    cout<<"Filled Background Response Histogram"<<endl;
    cout<<"Signal Ratio: "<<sig_n_b/(res_b_entries)<<endl; 
    cout<<"Background Ratio: "<<bg_n_b/(res_b_entries)<<endl; 
  
    //================================================================
  
    float sig_n_d=0, bg_n_d=0;
    for (long j=0; j<res_d_entries; ++j){
      res_d->GetEntry(j); 
      
      float result = reader[i]->EvaluateMVA("method"); 
      h_res_d->Fill(result);
  
      if (result>0){
        sig_n_d+=1; 
      }
      else{
        bg_n_d+=1; 
      }
    }
    cout<<""<<endl; 
    cout<<"Filled Data Response Histogram"<<endl;
    cout<<"Signal Ratio: "<<sig_n_d/(res_d_entries)<<endl; 
    cout<<"Background Ratio: "<<bg_n_d/(res_d_entries)<<endl; 
    
    //==================================================================
  
    out_root->Write(); 
    out_root->Close();
  
    delete reader[i]; 

  }
}
