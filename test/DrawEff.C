bool gDoFolding = false;

void DrawEff(bool doFolding = false)
{
  gInterpreter->LoadMacro("libValidation.C");
  gStyle->SetOptStat(0);
  gDoFolding = doFolding;

  TCanvas* c;

  gLineColor = 1;
  gLegend = new TLegend(.85, .15, 1.0, .30, "");
  c = new TCanvas("cSeedMinusEff", "Seed Minus Efficiency", 1024, 768); 
  c->cd(); c->SetGridx(); c->SetGridy();
  DrawEff("Mu-Pt10"  , "Seed", "Sim");
  DrawEff("Mu-Pt50"  , "Seed", "Sim");
  DrawEff("Mu-Pt100" , "Seed", "Sim");
  DrawEff("Mu-Pt500" , "Seed", "Sim");
  DrawEff("Mu-Pt1000", "Seed", "Sim");
  gLegend->Draw("same");
  c->Print("plots/EffSeedMinus.gif");
                                   
  gLineColor = 1;
  gLegend = new TLegend(.85, .15, 1.0, .30, "");
  c = new TCanvas("cSeedPlusEff", "Seed Plus Efficiency", 1024, 768); 
  c->cd(); c->SetGridx(); c->SetGridy();
  DrawEff("Mu+Pt10"  , "Seed", "Sim");
  DrawEff("Mu+Pt50"  , "Seed", "Sim");
  DrawEff("Mu+Pt100" , "Seed", "Sim");
  DrawEff("Mu+Pt500" , "Seed", "Sim");
  DrawEff("Mu+Pt1000", "Seed", "Sim");
  gLegend->Draw("same");
  c->Print("plots/EffSeedPlus.gif");
 
  gLineColor = 1;
  gLegend = new TLegend(.85, .15, 1.0, .30, "");
  c = new TCanvas("cStaMinusEff", "StaMuon Minus Efficiency", 1024, 768); 
  c->cd(); c->SetGridx(); c->SetGridy();
  DrawEff("Mu-Pt10"  , "Sta", "Sim");
  DrawEff("Mu-Pt50"  , "Sta", "Sim");
  DrawEff("Mu-Pt100" , "Sta", "Sim");
  DrawEff("Mu-Pt500" , "Sta", "Sim");
  DrawEff("Mu-Pt1000", "Sta", "Sim");
  gLegend->Draw("same");
  c->Print("plots/EffStaMinus.gif");

  gLineColor = 1;
  gLegend = new TLegend(.85, .15, 1.0, .30, "");
  c = new TCanvas("cStaPlusEff", "StaMuon Plus Efficiency", 1024, 768); 
  c->cd(); c->SetGridx(); c->SetGridy();
  DrawEff("Mu+Pt10"  , "Sta", "Sim");
  DrawEff("Mu+Pt50"  , "Sta", "Sim");
  DrawEff("Mu+Pt100" , "Sta", "Sim");
  DrawEff("Mu+Pt500" , "Sta", "Sim");
  DrawEff("Mu+Pt1000", "Sta", "Sim");
  gLegend->Draw("same");
  c->Print("plots/EffStaPlus.gif");

  gLineColor = 1;
  gLegend = new TLegend(.85, .15, 1.0, .30, "");
  c = new TCanvas("cGlbMinusEff", "GlbMuon Minus Efficiency", 1024, 768); 
  c->cd(); c->SetGridx(); c->SetGridy();
  DrawEff("Mu-Pt10"  , "Glb", "Sim");
  DrawEff("Mu-Pt50"  , "Glb", "Sim");
  DrawEff("Mu-Pt100" , "Glb", "Sim");
  DrawEff("Mu-Pt500" , "Glb", "Sim");
  DrawEff("Mu-Pt1000", "Glb", "Sim");
  gLegend->Draw("same");
  c->Print("plots/EffGlbMinus.gif");
 
  gLineColor = 1;
  gLegend = new TLegend(.85, .15, 1.0, .30, "");
  c = new TCanvas("cGlbPlusEff", "GlbMuon Minus Efficiency", 1024, 768); 
  c->cd(); c->SetGridx(); c->SetGridy();
  DrawEff("Mu+Pt10"  , "Glb", "Sim");
  DrawEff("Mu+Pt50"  , "Glb", "Sim");
  DrawEff("Mu+Pt100" , "Glb", "Sim");
  DrawEff("Mu+Pt500" , "Glb", "Sim");
  DrawEff("Mu+Pt1000", "Glb", "Sim");
  gLegend->Draw("same");
  c->Print("plots/EffGlbPlus.gif");

  gLineColor = 1;
  gLegend = new TLegend(.85, .15, 1.0, .30, "");
  c = new TCanvas("cGlbAlgMinusEff", "GlbMuon Minus Alg Efficiency", 1024, 768);
  c->cd(); c->SetGridx(); c->SetGridy();
  DrawEff("Mu-Pt10"  , "Glb", "Tk");
  DrawEff("Mu-Pt50"  , "Glb", "Tk");
  DrawEff("Mu-Pt100" , "Glb", "Tk");
  DrawEff("Mu-Pt500" , "Glb", "Tk");
  DrawEff("Mu-Pt1000", "Glb", "Tk");
  gLegend->Draw("same");
  c->Print("plots/EffGlbAlgMinus.gif");

  gLineColor = 1;
  gLegend = new TLegend(.85, .15, 1.0, .30, "");
  c = new TCanvas("cGlbAlgPlusEff", "GlbMuon Minus Alg Efficiency", 1024, 768);
  c->cd(); c->SetGridx(); c->SetGridy();
  DrawEff("Mu+Pt10"  , "Glb", "Tk");
  DrawEff("Mu+Pt50"  , "Glb", "Tk");
  DrawEff("Mu+Pt100" , "Glb", "Tk");
  DrawEff("Mu+Pt500" , "Glb", "Tk");
  DrawEff("Mu+Pt1000", "Glb", "Tk");
  gLegend->Draw("same");
  c->Print("plots/EffGlbAlgPlus.gif");


}

void DrawEff(TString sampleName, TString muonType1, TString muonType2)
{

  TFile file(sampleName+".root"); file.cd();

  TH1F* hRec = (TH1F*)((TH2F*)file.Get(muonType1+"EtaVsPhi"))->ProjectionX();
  TH1F* hSim = (TH1F*)((TH2F*)file.Get(muonType2+"EtaVsPhi"))->ProjectionX();

  if ( gDoFolding ) {
    hRec = FoldH1(hRec);
    hSim = FoldH1(hSim);
  }
 
  hRec->Sumw2();
  hSim->Sumw2();

  gROOT->cd();
  TH1F* his  = new TH1F(sampleName+muonType1+muonType2+"his", sampleName+muonType1+muonType2, 
                        hRec->GetNbinsX(), hRec->GetXaxis()->GetXmin(), hRec->GetXaxis()->GetXmax()); 

  his->Divide(hRec, hSim, 1, 1, "B");
  his->SetMinimum(0.8); his->SetMaximum(1.0);

  his->SetTitle(muonType1+muonType2+" Muon Efficiency");
  his->GetXaxis()->SetTitle("Psuedorapidity #eta");
  his->GetYaxis()->SetTitle("Efficiency"); 
  his->SetLineColor(gLineColor);
  his->Draw(TString("E1X0")+(gLineColor==1?"":"same"));
  ConnectLines(his, sampleName);

  if ( ++gLineColor==kYellow ) gLineColor++;
  file.Close();
}

