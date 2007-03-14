TLegend* gLegend;

void DrawRes()
{
  gStyle->SetOptStat(0);
  gInterpreter->LoadMacro("libValidation.C");

  gChi2Max = 10;

  gMeanMax = 5; gWidthMin = 5E-2; gWidthMax = 2E+1;
  DrawFitHisto("Seed", "EtaVsErrQPt", "+", "plots/QPt");
  DrawFitHisto("Seed", "EtaVsErrQPt", "-", "plots/QPt");

  gMeanMax = 3; gWidthMin = 5E-2; gWidthMax = 2E+1;
  DrawFitHisto("Sta" , "EtaVsErrQPt", "+", "plots/QPt");
  DrawFitHisto("Sta" , "EtaVsErrQPt", "-", "plots/QPt");

  gMeanMax = 0.2; gWidthMin = 5E-3; gWidthMax = 1E+0;
  DrawFitHisto("Glb" , "EtaVsErrQPt", "+", "plots/QPt");
  DrawFitHisto("Glb" , "EtaVsErrQPt", "-", "plots/QPt");
}

void DrawFitHisto(TString muonType, TString histoName, TString charge, TString prefix)
{
  gLineColor = 1;
  TString name = muonType + (charge=="+"?"Plus":"Minus");
  TCanvas* cMean = new TCanvas(name+"MeanCanvas", histoName+"Muon "+charge+" Mean sigma(q/pT)", 1024, 768);
  TCanvas* cReso = new TCanvas(name+"ResoCanvas", histoName+"Muon "+charge+" Resolution sigma(q/pT)", 1024, 768);
  TCanvas* cChi2 = new TCanvas(name+"Chi2Canvas", histoName+"Muon "+charge+" sigma(q/pT) Fit Chi2", 1024, 768);

  cMean->SetGridx(); cMean->SetGridy(); 
  cReso->SetGridx(); cReso->SetGridy(); 
  cChi2->SetGridx(); cChi2->SetGridy(); 
  cReso->SetLogy();

  gLegend = new TLegend(.85, .85, 1.0, 1.0, "");

  DrawFitSlice("Mu"+charge+"Pt10"  , muonType, histoName, cMean, cReso, cChi2);
  DrawFitSlice("Mu"+charge+"Pt50"  , muonType, histoName, cMean, cReso, cChi2);
  DrawFitSlice("Mu"+charge+"Pt100" , muonType, histoName, cMean, cReso, cChi2);
  DrawFitSlice("Mu"+charge+"Pt500" , muonType, histoName, cMean, cReso, cChi2);
  DrawFitSlice("Mu"+charge+"Pt1000", muonType, histoName, cMean, cReso, cChi2);

  cMean->cd(); gLegend->Draw("same");
  cReso->cd(); gLegend->Draw("same");
  cChi2->cd(); gLegend->Draw("same");

  cMean->Print(prefix+"Mean"+name+".gif");
  cReso->Print(prefix+"Reso"+name+".gif");
  cChi2->Print(prefix+"Chi2"+name+".gif");
}

