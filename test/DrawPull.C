TLegend* gLegend;

TString gSampleLoc;

void DrawPull(TString sampleLoc)
{
  gSampleLoc = sampleLoc;

  gStyle->SetPalette(1);
  gStyle->SetOptStat(0);
  gInterpreter->LoadMacro("libValidation.C");

  DrawPull2DHists("Pt10"  );
  DrawPull2DHists("Pt50"  );
  DrawPull2DHists("Pt100" );
  DrawPull2DHists("Pt500" );
  DrawPull2DHists("Pt1000");

  gChi2Max = 10;

  gMeanMax = 3; gWidthMin = 0; gWidthMax = 5;
  DrawFitHisto("Seed", "EtaVsPullPt", "+", "plots/PullPt");
  DrawFitHisto("Seed", "EtaVsPullPt", "-", "plots/PullPt");

  DrawFitHisto("Sta" , "EtaVsPullPt", "+", "plots/PullPt");
  DrawFitHisto("Sta" , "EtaVsPullPt", "-", "plots/PullPt");

  DrawFitHisto("Glb" , "EtaVsPullPt", "+", "plots/PullPt");
  DrawFitHisto("Glb" , "EtaVsPullPt", "-", "plots/PullPt");
}

void DrawFitHisto(TString muonType, TString histoName, TString charge, TString prefix)
{
  gLineColor = 1;
  TString name = muonType + (charge=="+"?"Plus":"Minus");
  
  TCanvas* c = new TCanvas(name+"_MeanCanvas"+"_PullCanvas"+"_Chi2Canvas",histoName+"Muon "+charge+" Mean,width of Pull, chi2" , 1024, 768);
  c->Divide(1,3);
  
//   TCanvas* cMean  = new TCanvas(name+"MeanCanvas", histoName+"Muon "+charge+" Mean Pull p_{T}", 1024, 768);
//   TCanvas* cWidth = new TCanvas(name+"PullCanvas", histoName+"Muon "+charge+" Width Pull p_{T}", 1024, 768);
//   TCanvas* cChi2  = new TCanvas(name+"Chi2Canvas", histoName+"Muon "+charge+" Pull Gaussian Fit Chi2", 1024, 768);
  
//    cMean ->SetGridx(); cMean ->SetGridy(); 
//    cWidth->SetGridx(); cWidth->SetGridy(); 
//    cChi2 ->SetGridx(); cChi2 ->SetGridy(); 
  c->GetPad(1)->SetGridx(); c->GetPad(1)->SetGridy();
  c->GetPad(1)->SetName(histoName+"Muon "+charge+" Mean Pull p_{T}");

  c->GetPad(2)->SetGridx(); c->GetPad(2)->SetGridy();
  c->GetPad(2)->SetName(histoName+"Muon "+charge+" Width Pull p_{T}");
  
  c->GetPad(3)->SetGridx(); c->GetPad(3)->SetGridy();
  c->GetPad(3)->SetName(histoName+"Muon "+charge+" Pull Gaussian Fit Chi2");

//  cWidth->SetLogy();

  gLegend = new TLegend(.85, .85, 1.0, 1.0, "");

  DrawFitSlice(gSampleLoc+"Mu"+charge+"Pt10"  , muonType, histoName, c->cd(1), c->cd(2), c->cd(3));
  DrawFitSlice(gSampleLoc+"Mu"+charge+"Pt50"  , muonType, histoName, c->cd(1), c->cd(2), c->cd(3));
  DrawFitSlice(gSampleLoc+"Mu"+charge+"Pt100" , muonType, histoName, c->cd(1), c->cd(2), c->cd(3));
  DrawFitSlice(gSampleLoc+"Mu"+charge+"Pt500" , muonType, histoName, c->cd(1), c->cd(2), c->cd(3));
  DrawFitSlice(gSampleLoc+"Mu"+charge+"Pt1000", muonType, histoName, c->cd(1), c->cd(2), c->cd(3));

  c->cd(1); gLegend->Draw("same");
  c->cd(2); gLegend->Draw("same");
  c->cd(3); gLegend->Draw("same");

  c->GetPad(1)->Print(prefix+"Mean"+name+".gif");
  c->GetPad(2)->Print(prefix+"Pull"+name+".gif");
  c->GetPad(3) ->Print(prefix+"Chi2"+name+".gif");
}

void DrawPull2DHists(TString sample)
{
  TCanvas* c = new TCanvas(sample+"Canvas", sample+" sigma(q/pT)", 1024, 768);
  c->Divide(2,3);

  DrawPullVsEta(gSampleLoc+TString("Mu+")+sample, "Seed", c->cd(1));
  DrawPullVsEta(gSampleLoc+TString("Mu-")+sample, "Seed", c->cd(2));
  DrawPullVsEta(gSampleLoc+TString("Mu+")+sample, "Sta" , c->cd(3));
  DrawPullVsEta(gSampleLoc+TString("Mu-")+sample, "Sta" , c->cd(4));
  DrawPullVsEta(gSampleLoc+TString("Mu+")+sample, "Glb" , c->cd(5));
  DrawPullVsEta(gSampleLoc+TString("Mu-")+sample, "Glb" , c->cd(6));

  c->Print(TString("plots/Pull2DMu")+sample+".gif");
}

void DrawPullVsEta(TString sampleName, TString muonType, TVirtualPad* pad)
{
  pad->SetGridx(); pad->SetGridy();
  TFile file(sampleName+".root"); file.cd();
  if(file.IsZombie()) return;

  gROOT->cd();
  TH2F* his = (TH2F*)(file.Get(muonType+"EtaVsPullPt")->Clone());
  his->Rebin2D(1,2);

  his->SetTitle(sampleName+muonType+" Muon #eta vs Pull p_{T}");
  his->GetXaxis()->SetTitle("Psuedorapidity #eta");
  his->GetYaxis()->SetTitle("Pull");
  his->Draw("COLZ");

  file.Close();
}

