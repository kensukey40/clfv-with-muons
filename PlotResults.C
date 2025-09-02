//______________________________________________________________________________
TGraph* GetGraph(TString txtfile)
{
   std::ifstream ifs(txtfile);
   if (ifs.fail()) {
      std::cout << Form("Fail to open %s", txtfile.Data()) << std::endl;
      return 0;
   }

   auto gr = new TGraph();

   Double_t year, ul;
   while (ifs >> year >> ul) {
      gr->SetPoint(gr->GetN(), year, ul);
   }

   ifs.close();
   return gr;
}

//______________________________________________________________________________
void PlotResults()
{
   gStyle->SetOptStat(0);
   gStyle->SetPadGridX(0);
   gStyle->SetPadGridY(0);
   gStyle->SetMarkerSize(1.2);

   auto h = new TH1D("h", ";Year;90% C.L. upper limit", 100, 1940, 2030);
   h->GetYaxis()->SetRangeUser(1.e-14, 1.);
   h->GetYaxis()->SetNdivisions(508);

   auto grMuEGamma = GetGraph("muegamma_beforeMEGA.txt");
   grMuEGamma->SetName("grMuEGamma");
   grMuEGamma->SetMarkerStyle(24);
   grMuEGamma->SetMarkerColor(kRed);

   auto grMEG = GetGraph("muegamma_MEG.txt");
   grMEG->SetName("grMEG");
   grMEG->SetMarkerStyle(20);
   grMEG->SetMarkerColor(kRed);

   auto grMEG2 = GetGraph("muegamma_MEG2.txt");
   grMEG2->SetName("grMEG2");
   grMEG2->SetMarkerStyle(20);
   grMEG2->SetMarkerColor(kRed);

   auto grMEGLatest = GetGraph("muegamma_latest.txt");
   grMEGLatest->SetName("grMEGLatest");
   grMEGLatest->SetMarkerStyle(29);
   grMEGLatest->SetMarkerColor(kRed);
   grMEGLatest->SetMarkerSize(2.5);

   auto grMuEConv = GetGraph("mueconv.txt");
   grMuEConv->SetName("grMuEConv");
   grMuEConv->SetMarkerStyle(25);
   grMuEConv->SetMarkerColor(kGreen+1);

   auto grMu3e = GetGraph("mueee.txt");
   grMu3e->SetName("grMu3e");
   grMu3e->SetMarkerStyle(32);
   grMu3e->SetMarkerColor(kBlue);

   auto c = new TCanvas("c", "c", 800, 600);
   c->SetLogy(1);
   h->Draw();

   grMuEGamma->Draw("P");
   grMEG->Draw("P");
   grMEG2->Draw("P");
   grMEGLatest->Draw("P");

   grMu3e->Draw("P");

   grMuEConv->Draw("P");

   auto legend = new TLegend(0.55, 0.83, 0.85, 0.6);
   legend->AddEntry(grMuEGamma, "#mu #rightarrow e#gamma", "P");
   legend->AddEntry(grMu3e, "#mu #rightarrow eee", "P");
   legend->AddEntry(grMuEConv, "#muN #rightarrow eN", "P");
   legend->Draw();

}
