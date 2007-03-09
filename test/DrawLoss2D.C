void DrawLoss2D()
{
  gStyle->SetPalette(1);
  gStyle->SetOptStat(0);

  TCanvas* cStaLoss2D = new TCanvas("cStaLoss2D", "StaMuon Loss2D rates", 1024, 768); 
  cStaLoss2D->Divide(5,2);
  DrawLoss2D("Mu-Pt10"  , "Sta", "Sim", cStaLoss2D->cd( 1));
  DrawLoss2D("Mu-Pt50"  , "Sta", "Sim", cStaLoss2D->cd( 2));
  DrawLoss2D("Mu-Pt100" , "Sta", "Sim", cStaLoss2D->cd( 3));
  DrawLoss2D("Mu-Pt500" , "Sta", "Sim", cStaLoss2D->cd( 4));
  DrawLoss2D("Mu-Pt1000", "Sta", "Sim", cStaLoss2D->cd( 5));

  DrawLoss2D("Mu+Pt10"  , "Sta", "Sim", cStaLoss2D->cd( 6));
  DrawLoss2D("Mu+Pt50"  , "Sta", "Sim", cStaLoss2D->cd( 7));
  DrawLoss2D("Mu+Pt100" , "Sta", "Sim", cStaLoss2D->cd( 8));
  DrawLoss2D("Mu+Pt500" , "Sta", "Sim", cStaLoss2D->cd( 9));
  DrawLoss2D("Mu+Pt1000", "Sta", "Sim", cStaLoss2D->cd(10));

  cStaLoss2D->Print("plots/Eff2DSta.gif");

  TCanvas* cGlbLoss2D = new TCanvas("cGlbLoss2D", "GlbMuon Loss2D rates", 1024, 768); 
  cGlbLoss2D->Divide(5,2);
  DrawLoss2D("Mu-Pt10"  , "Glb", "Sim", cGlbLoss2D->cd( 1));
  DrawLoss2D("Mu-Pt50"  , "Glb", "Sim", cGlbLoss2D->cd( 2));
  DrawLoss2D("Mu-Pt100" , "Glb", "Sim", cGlbLoss2D->cd( 3));
  DrawLoss2D("Mu-Pt500" , "Glb", "Sim", cGlbLoss2D->cd( 4));
  DrawLoss2D("Mu-Pt1000", "Glb", "Sim", cGlbLoss2D->cd( 5));
                                               
  DrawLoss2D("Mu+Pt10"  , "Glb", "Sim", cGlbLoss2D->cd( 6));
  DrawLoss2D("Mu+Pt50"  , "Glb", "Sim", cGlbLoss2D->cd( 7));
  DrawLoss2D("Mu+Pt100" , "Glb", "Sim", cGlbLoss2D->cd( 8));
  DrawLoss2D("Mu+Pt500" , "Glb", "Sim", cGlbLoss2D->cd( 9));
  DrawLoss2D("Mu+Pt1000", "Glb", "Sim", cGlbLoss2D->cd(10));

  cGlbLoss2D->Print("plots/Eff2DGlb.gif");

  TCanvas* cGlbStaLoss2D = new TCanvas("cGlbStaLoss2D", "GlbMuon/StaMuon Loss2D rates", 1024, 768); 
  cGlbStaLoss2D->Divide(5,2);
  DrawLoss2D("Mu-Pt10"  , "Glb", "Sta", cGlbStaLoss2D->cd( 1));
  DrawLoss2D("Mu-Pt50"  , "Glb", "Sta", cGlbStaLoss2D->cd( 2));
  DrawLoss2D("Mu-Pt100" , "Glb", "Sta", cGlbStaLoss2D->cd( 3));
  DrawLoss2D("Mu-Pt500" , "Glb", "Sta", cGlbStaLoss2D->cd( 4));
  DrawLoss2D("Mu-Pt1000", "Glb", "Sta", cGlbStaLoss2D->cd( 5));
                                                  
  DrawLoss2D("Mu+Pt10"  , "Glb", "Sta", cGlbStaLoss2D->cd( 6));
  DrawLoss2D("Mu+Pt50"  , "Glb", "Sta", cGlbStaLoss2D->cd( 7));
  DrawLoss2D("Mu+Pt100" , "Glb", "Sta", cGlbStaLoss2D->cd( 8));
  DrawLoss2D("Mu+Pt500" , "Glb", "Sta", cGlbStaLoss2D->cd( 9));
  DrawLoss2D("Mu+Pt1000", "Glb", "Sta", cGlbStaLoss2D->cd(10));

  cGlbStaLoss2D->Print("plots/Eff2DGlbSta.gif");
  
}

void DrawLoss2D(TString sampleName, TString muonType1, TString muonType2, TVirtualPad* pad)
{
  pad->SetGridx(); pad->SetGridy();
  TFile file(sampleName+".root"); file.cd();

  TH2F* hRec = (TH2F*)file.Get(muonType1+"PhiVsEta");
  TH2F* hSim = (TH2F*)file.Get(muonType2+"PhiVsEta");

//  hRec->RebinX(2); 
//  hSim->RebinX(2);

  gROOT->cd();
  TH2F* his  = new TH2F(sampleName+muonType1+muonType2+"his", sampleName+muonType1+muonType2, 
                        hRec->GetNbinsX(), hRec->GetXaxis()->GetXmin(), hRec->GetXaxis()->GetXmax(), 
                        hRec->GetNbinsY(), hRec->GetYaxis()->GetXmin(), hRec->GetYaxis()->GetXmax());
  his->SetMinimum(0); his->SetMaximum(1);
  his->Divide(hRec, hSim, 1, -1);

  TF1 f1("f1", "1", hRec->GetXaxis()->GetXmin(), hRec->GetXaxis()->GetXmax());
  his->Add(&f1);

  his->SetTitle(sampleName+muonType1+muonType2+" Muon loss rate");
  his->GetXaxis()->SetTitle("Angle #phi"); 
  his->GetYaxis()->SetTitle("Psuedorapidity #eta");
  his->Draw("COLZ");

  file.Close();
}
