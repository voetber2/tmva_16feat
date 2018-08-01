#include <iostream>                                                             
#include <cstdlib>                                                              
#include <map>                                                                  
#include <string>                                                               
                                                                                
#include <TChain.h>                                                             
#include <TFile.h>                                                              
#include <TTree.h>                                                         
#include <TString.h>                                                            
#include <TObjString.h>                                                         
#include <TSystem.h>                                                            
                                                                                
#include <TMVA/Factory.h>                                                       
#include <TMVA/DataLoader.h>                                                    
#include <TMVA/Tools.h>                                                         
                                                                                
using namespace std;                                                            
                                                                                
int main(){                                                                     
  TMVA::Tools::Instance();                                                      
  map<string, int> Use;

  TFile* out = TFile::Open("tmva_bdt16_ptcuts.root", "RECREATE"); 
  TMVA::Factory* factory = new TMVA::Factory("TMVAClassification", out, 
    "!V:!Silent:Color:DrawProgressBar:AnalysisType=Classification");

  //========================================================================
  vector<TString>num; 
  num.emplace_back("50");
  num.emplace_back("100");
  num.emplace_back("150");
  num.emplace_back("200");
  num.emplace_back("200p");

  TMVA::DataLoader*data[5] = {
    new TMVA::DataLoader("data_pt50"),
    new TMVA::DataLoader("data_pt100"),
    new TMVA::DataLoader("data_pt150"),
    new TMVA::DataLoader("data_pt200"),
    new TMVA::DataLoader("data_pt200p")
  };
  
  for (int i=0; i<5; ++i){
    TFile* in_s = new TFile("$TMPDIR/data16_pt"+num[i]+"_sig.root"); 
    TFile* in_b = new TFile("$TMPDIR/data16_pt"+num[i]+"_back.root"); 
    
    data[i]->AddVariable("s",'F');       
    data[i]->AddVariable("yydr",'F');     
    data[i]->AddVariable("y1dr",'F');      
    data[i]->AddVariable("y2dr",'F');      
    data[i]->AddVariable("ptratio",'F');        
    data[i]->AddVariable("y1y",'F');  
    data[i]->AddVariable("y2y",'F');  
    data[i]->AddVariable("jety",'F');   
    data[i]->AddVariable("yydy",'F');   
                                     
    data[i]->AddVariable("y1E",'F'); 
    data[i]->AddVariable("y1pt",'F');
                                     
    data[i]->AddVariable("y2E",'F'); 
    data[i]->AddVariable("y2pt",'F');

    data[i]->AddVariable("yyE",'F'); 
    data[i]->AddVariable("yypt",'F');
                                     
    data[i]->AddVariable("jetE",'F');     
  
    TTree* sigTrain = (TTree*)in_s->Get("sigTrain");                             
    TTree* bgTrain = (TTree*)in_b->Get("bgTrain");                               
    TTree* sigTest = (TTree*)in_s->Get("sigTest");                               
    TTree* bgTest = (TTree*)in_b->Get("bgTest"); 
  
    Float_t sig_w = 1./(sigTrain->GetEntries() + sigTest->GetEntries());  
    Float_t bg_w = 1./(bgTrain->GetEntries() + bgTest->GetEntries());   
  
    data[i]->AddSignalTree(sigTrain, sig_w, "Training"); 
    data[i]->AddSignalTree(sigTest, sig_w, "Testing"); 
    data[i]->AddBackgroundTree(bgTrain, bg_w, "Training"); 
    data[i]->AddBackgroundTree(bgTest, bg_w, "Testing"); 
  
    //Add weights 
    //Loading in weights 
    TMVA::DataLoader* weight_data = new TMVA::DataLoader("weight_data"); 
    weight_data->AddVariable("weights", 'F'); 
  
    weight_data->AddSignalTree(sigTrain, sig_w, "Training"); 
    weight_data->AddSignalTree(sigTest, sig_w, "Testing"); 
    weight_data->AddBackgroundTree(bgTrain, bg_w, "Training"); 
    weight_data->AddBackgroundTree(bgTest, bg_w, "Testing"); 
  
    data[i]->SetWeightExpression("weights"); 
  }
  //============================================================================
  //Factories 
  TString settings = "NTrees=600:MaxDepth=3:nCuts=20:BoostType=AdaBoost:AdaBoostBeta=.5:!UseRandomisedTrees:UseYesNoLeaf";
  
  factory->BookMethod(data[0], TMVA::Types::kBDT, "BDT_50", settings);
  factory->BookMethod(data[1], TMVA::Types::kBDT, "BDT_100", settings);
  factory->BookMethod(data[2], TMVA::Types::kBDT, "BDT_150", settings);
  factory->BookMethod(data[3], TMVA::Types::kBDT, "BDT_200", settings);
  factory->BookMethod(data[4], TMVA::Types::kBDT, "BDT_200p", settings);
  
  factory->TrainAllMethods(); 
  factory->TestAllMethods(); 
  factory->EvaluateAllMethods(); 
  
  out->Write(); 
  out->Close(); 
  
  delete factory; 
  
  for (int i=0; i<5; ++i){
    delete data[i]; 
  }
}
