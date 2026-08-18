#include <algorithm>
#include <functional>
#include <iostream>
#include <cmath>
#include <vector>
#include "TFile.h"
#include "TChain.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TVector2.h"
#include "TLorentzVector.h"
#include "AnalysisPhysics.h"

void WithoutCutsFA(){
    TH1::AddDirectory(kFALSE);

    TChain *t1 = new TChain("Events");
    t1->Add("root://eospublic.cern.ch//eos/opendata/cms/derived-data/NanoAODRun1/01-Jul-22/MonteCarlo11_Summer11LegDR_DYJetsToLL_M-50_7TeV-madgraph-pythia6-tauola_merged.root");

    UInt_t nMuon;
    Int_t Muon_charge[1000];
    Int_t Muon_tightCharge[1000];
    Float_t Muon_pt[1000]; 
    Float_t Muon_ptErr[1000];
    Float_t Muon_eta[1000];
    Float_t Muon_phi[1000];
    Float_t Muon_mass[1000];
    Float_t Muon_dxy[1000]; 
    Float_t Muon_pfRelIso04_all[1000]; 
    Float_t Muon_pfRelIso03_all[1000];
    
    UInt_t nJet;
    Float_t Jet_pt[1000];
    Float_t Jet_eta[1000];
    Float_t Jet_phi[1000];
    Float_t Jet_mass[1000];

    UInt_t nTau;
    UInt_t nGenJet;

    Float_t GenJet_pt[1000], GenJet_eta[1000], GenJet_phi[1000], GenJet_mass[1000];

    UInt_t nGenPart;
    Float_t GenPart_pt[5000];
    Float_t GenPart_phi[5000];
    Int_t GenPart_pdgId[5000];
    Int_t GenPart_status[5000];
    Float_t GenPart_eta[5000];
    Float_t GenPart_mass[5000];
    Int_t GenPart_genPartIdxMother[5000];

    Float_t MET_pt, MET_phi, MET_sumEt, MET_significance;
    Float_t MET_covXX, MET_covXY, MET_covYY;
    Float_t CaloMET_pt, CaloMET_phi, CaloMET_sumEt;

    Float_t Muon_leadingPt = -1.;

    TFile *fout = new TFile("hgr_wo_cutsJET.root", "RECREATE");

    t1->SetBranchStatus("*", 0);
    
    t1->SetBranchStatus("nMuon", 1); t1->SetBranchAddress("nMuon", &nMuon);
    t1->SetBranchStatus("Muon_charge", 1); t1->SetBranchAddress("Muon_charge", Muon_charge);
    t1->SetBranchStatus("Muon_tightCharge", 1); t1->SetBranchAddress("Muon_tightCharge", Muon_tightCharge);
    t1->SetBranchStatus("Muon_pt", 1); t1->SetBranchAddress("Muon_pt", Muon_pt);
    t1->SetBranchStatus("Muon_ptErr", 1); t1->SetBranchAddress("Muon_ptErr", Muon_ptErr);
    t1->SetBranchStatus("Muon_eta", 1); t1->SetBranchAddress("Muon_eta", Muon_eta);
    t1->SetBranchStatus("Muon_phi", 1); t1->SetBranchAddress("Muon_phi", Muon_phi);
    t1->SetBranchStatus("Muon_mass", 1); t1->SetBranchAddress("Muon_mass", Muon_mass);
    t1->SetBranchStatus("Muon_dxy", 1); t1->SetBranchAddress("Muon_dxy", Muon_dxy);
    t1->SetBranchStatus("Muon_pfRelIso04_all", 1); t1->SetBranchAddress("Muon_pfRelIso04_all", Muon_pfRelIso04_all);
    t1->SetBranchStatus("Muon_pfRelIso03_all", 1); t1->SetBranchAddress("Muon_pfRelIso03_all", Muon_pfRelIso03_all);
    
    t1->SetBranchStatus("nJet", 1); t1->SetBranchAddress("nJet", &nJet);
    t1->SetBranchStatus("Jet_pt", 1); t1->SetBranchAddress("Jet_pt", Jet_pt);
    t1->SetBranchStatus("Jet_eta", 1); t1->SetBranchAddress("Jet_eta", Jet_eta);
    t1->SetBranchStatus("Jet_phi", 1); t1->SetBranchAddress("Jet_phi", Jet_phi);
    t1->SetBranchStatus("Jet_mass", 1); t1->SetBranchAddress("Jet_mass", Jet_mass);

    t1->SetBranchStatus("nGenJet", 1); t1->SetBranchAddress("nGenJet", &nGenJet);
    t1->SetBranchStatus("GenJet_pt", 1); t1->SetBranchAddress("GenJet_pt", GenJet_pt);
    t1->SetBranchStatus("GenJet_eta", 1); t1->SetBranchAddress("GenJet_eta", GenJet_eta);
    t1->SetBranchStatus("GenJet_phi", 1); t1->SetBranchAddress("GenJet_phi", GenJet_phi);
    t1->SetBranchStatus("GenJet_mass", 1); t1->SetBranchAddress("GenJet_mass", GenJet_mass);

    t1->SetBranchStatus("nGenPart", 1); t1->SetBranchAddress("nGenPart", &nGenPart);
    t1->SetBranchStatus("GenPart_pt", 1); t1->SetBranchAddress("GenPart_pt", GenPart_pt);
    t1->SetBranchStatus("GenPart_phi", 1); t1->SetBranchAddress("GenPart_phi", GenPart_phi);
    t1->SetBranchStatus("GenPart_pdgId", 1); t1->SetBranchAddress("GenPart_pdgId", GenPart_pdgId);
    t1->SetBranchStatus("GenPart_status", 1); t1->SetBranchAddress("GenPart_status", GenPart_status);
    t1->SetBranchStatus("GenPart_eta", 1); t1->SetBranchAddress("GenPart_eta", GenPart_eta);
    t1->SetBranchStatus("GenPart_mass", 1); t1->SetBranchAddress("GenPart_mass", GenPart_mass);
    t1->SetBranchStatus("GenPart_genPartIdxMother", 1); t1->SetBranchAddress("GenPart_genPartIdxMother", GenPart_genPartIdxMother);

    t1->SetBranchStatus("nTau", 1); t1->SetBranchAddress("nTau", &nTau);
    
    t1->SetBranchStatus("MET_pt", 1); t1->SetBranchAddress("MET_pt", &MET_pt);
    t1->SetBranchStatus("MET_phi", 1); t1->SetBranchAddress("MET_phi", &MET_phi);
    t1->SetBranchStatus("MET_sumEt", 1); t1->SetBranchAddress("MET_sumEt", &MET_sumEt);
    t1->SetBranchStatus("MET_significance", 1); t1->SetBranchAddress("MET_significance", &MET_significance);
    t1->SetBranchStatus("MET_covXX", 1); t1->SetBranchAddress("MET_covXX", &MET_covXX);
    t1->SetBranchStatus("MET_covXY", 1); t1->SetBranchAddress("MET_covXY", &MET_covXY);
    t1->SetBranchStatus("MET_covYY", 1); t1->SetBranchAddress("MET_covYY", &MET_covYY);
    t1->SetBranchStatus("CaloMET_pt", 1); t1->SetBranchAddress("CaloMET_pt", &CaloMET_pt);
    t1->SetBranchStatus("CaloMET_phi", 1); t1->SetBranchAddress("CaloMET_phi", &CaloMET_phi);
    t1->SetBranchStatus("CaloMET_sumEt", 1); t1->SetBranchAddress("CaloMET_sumEt", &CaloMET_sumEt);

    TH1F *hnMuon = new TH1F("hnMuon", "hnMuon", 50, 0.5, 50.5);
    TH1F *hMuon_charge = new TH1F("hMuon_charge", "hMuon_charge", 3, -1.5, 1.5);
    TH1F *hMuon_tightCharge = new TH1F("hMuon_tightCharge", "hMuon_tightCharge", 5, -1., 4);
    TH1F *hMuon_pt = new TH1F("hMuon_pt", "hMuon_pt", 100, 0., 100.);
    TH1F *hMuon_ptErr = new TH1F("hMuon_ptErr", "hMuon_ptErr", 10, 0., 2.);
    TH1F *hMuon_eta = new TH1F("hMuon_eta", "hMuon_eta", 50, -5., 5.);
    TH1F *hMuon_phi = new TH1F("hMuon_phi", "hMuon_phi", 50, -5., 5.);
    TH1F *hMuon_mass = new TH1F("hMuon_mass", "hMuon_mass", 100, -2., 2.);
    TH1F *hMuon_dxy = new TH1F("hMuon_dxy", "hMuon_dxy", 100, -4., 4.);
    TH1F *hMuon_pfRelIso04_all = new TH1F("hMuon_pfRelIso04_all", "PF relIso04;Iso;Events", 500, 0, 100);
    TH1F *hMuon_pfRelIso03_all = new TH1F("hMuon_pfRelIso03_all", "PF relIso03;Iso;Events", 500, 0, 100);
    TH1F *hMuon_leadingPt = new TH1F("hMuon_leadingPt", "hMuon_leadingPt", 100, 0., 200.);
    TH1F *hMuon_eta1 = new TH1F("hMuon_eta1", "hMuon_eta1", 50, -5., 5.);
    TH1F *hMuon_deltaPhi = new TH1F("hMuon_deltaPhi", "hMuon_deltaPhi", 50, -5., 5.);
    TH1F *hMuon_pt_plan = new TH1F("hMuon_pt_plan", "p_{T} of all muons;p_{T} [GeV];Events", 100, 0, 150);
    TH1F *hMuon_phi_correct = new TH1F("hMuon_phi_correct", "#phi of muons (correct range);#phi [rad];Events", 64, -3.2, 3.2);
    TH1F *hDeltaEta = new TH1F("hDeltaEta", "#Delta#eta = #eta(#mu^{-}) - #eta(#mu^{+});#Delta#eta;Events", 50, -5, 5);
    TH1F *hCosDeltaPhi = new TH1F("hCosDeltaPhi", "cos(#Delta#phi);cos(#Delta#phi);Events", 50, -1.1, 1.1);
    TH1F *hCosDeltaPhiJets = new TH1F("hCosDeltaPhiJets", "cos(#Delta#phi_{jj}) between leading jets;cos(#Delta#phi_{jj});Events", 50, -1.1, 1.1);

    TH1F *hMET_pt = new TH1F("hMET_pt","hMET_pt", 250, 0., 50.);
    TH1F *hMET_phi = new TH1F("hMET_phi", "hMET_phi", 50, -5., 5.);
    TH1F *hMET_sumEt = new TH1F("hMET_sumEt", "hMET_sumEt", 250, -5., 50.);
    TH1F *hMET_significance = new TH1F("hMET_significance", "hMET_significance", 100, 0., 25.);
    TH1F *hMET_covXX = new TH1F("hMET_covXX", "hMET_covXX", 100, -0., 50.);
    TH1F *hMET_covXY = new TH1F("hMET_covXY", "hMET_covXY", 400, -20., 20.);
    TH1F *hMET_covYY = new TH1F("hMET_covYY", "hMET_covYY", 100, -2., 2.);
    
    TH1F *hCaloMET_pt = new TH1F("hCaloMET_pt", "hCaloMET_pt", 250, 0., 50.);
    TH1F *hCaloMET_phi = new TH1F("hCaloMET_phi", "hCaloMET_phi", 50, -5., 5.);
    TH1F *hCaloMET_sumEt = new TH1F("hCaloMET_sumEt", "hCaloMET_sumEt", 250, 5., 55.);
    
    TH1F *hMassDifference = new TH1F("hMassDifference", "Difference (Hand - TLorentzVector)", 200, -0.01, 0.01);
    TH1D *htransMassZ = new TH1D("htransMassZ", "Z Transverse Mass; M_{T} [GeV]; Events", 100, 0, 150);
    TH1F *hZDimuon_MassRuka = new TH1F("hZDimuon_MassRuka", "Invariant Mass Hand Calc", 300, 0, 150);
    TH1F *hZDimuon_mass = new TH1F("hZDimuon_mass", "hZDimuon_mass", 300, 0., 150.);
    TH1F *hDimuon_pt = new TH1F("hDimuon_pt", "hDimuon_pt", 1000, 0., 200.);
    TH1F *hDimuon_pz = new TH1F("hDimuon_pz", "hDimuon_pz", 2000, -200., 200.);

    TH1F *hnJet = new TH1F("hnJet", "Number of Jets;nJet;Events", 20, -0.5, 19.5);
    TH1F *hJet_pt = new TH1F("hJet_pt", "Jet p_{T};p_{T} [GeV];Events", 100, 0., 300.);
    TH1F *hJet_eta = new TH1F("hJet_eta", "Jet #eta;#eta;Events", 50, -5., 5.);
    TH1F *hJet_phi = new TH1F("hJet_phi", "Jet #phi;#phi [rad];Events", 50, -3.2, 3.2);
    TH1F *hJet_mass = new TH1F("hJet_mass", "Jet Mass;Mass [GeV];Events", 50, 0., 100.);

    TH1F *hnGenJet = new TH1F("hnGenJet", "Number of GenJets;nGenJet;Events", 20, -0.5, 19.5);
    TH1F *hGenJet_pt = new TH1F("hGenJet_pt", "GenJet p_{T};p_{T} [GeV];Events", 100, 0., 300.);
    TH1F *hGenJet_eta = new TH1F("hGenJet_eta", "GenJet #eta;#eta;Events", 50, -5., 5.);
    TH1F *hGenJet_phi = new TH1F("hGenJet_phi", "GenJet #phi;#phi [rad];Events", 50, -3.2, 3.2);
    TH1F *hGenJet_mass = new TH1F("hGenJet_mass", "GenJet Mass;Mass [GeV];Events", 50, 0., 100.);
    
    TH1F *hDijet_mass = new TH1F("hDijet_mass", "Dijet Invariant Mass; M_{jj} [GeV]; Events", 100, 0, 300);
    TH2F *hnGenJet_vs_nJet = new TH2F("hnGenJet_vs_nJet", "nGenJet vs nJet; nJet; nGenJet", 20, -0.5, 19.5, 20, -0.5, 19.5);

    TH2F *hnGenJet_vs_GenZPt = new TH2F("hnGenJet_vs_GenZPt", "hnGenJet_vs_GenZPt", 100, 0, 300, 20, -0.5, 19.5);
    TH2F *hnGenJet25_vs_GenZPt = new TH2F("hnGenJet25_vs_GenZPt", "hnGenJet25_vs_GenZPt", 100, 0, 300, 20, -0.5, 19.5);
    TH2F *hSumLeadingJetsPt_vs_GenZPt = new TH2F("hSumLeadingJetsPt_vs_GenZPt", "hSumLeadingJetsPt_vs_GenZPt", 100, 0, 300, 100, 0, 500);
    TH2F *hSumLeadingJets25Pt_vs_GenZPt = new TH2F("hSumLeadingJets25Pt_vs_GenZPt", "hSumLeadingJets25Pt_vs_GenZPt", 100, 0, 300, 100, 0, 500);
    TH2F *hDeltaPhiMuons_vs_DeltaPhiJets = new TH2F("hDeltaPhiMuons_vs_DeltaPhiJets", "hDeltaPhiMuons_vs_DeltaPhiJets", 50, -3.2, 3.2, 50, -3.2, 3.2);

    TH2F *hnGenJet_vs_GenZPz = new TH2F("hnGenJet_vs_GenZPz", "hnGenJet_vs_GenZPz", 100, -500, 500, 20, -0.5, 19.5);
    TH2F *hnGenJet25_vs_GenZPz = new TH2F("hnGenJet25_vs_GenZPz", "hnGenJet25_vs_GenZPz", 100, -500, 500, 20, -0.5, 19.5);
    TH2F *hGenZPt_vs_DiJetPt = new TH2F("hGenZPt_vs_DiJetPt", "hGenZPt_vs_DiJetPt", 100, 0, 300, 100, 0, 300);

    TH2F *hDiJetPt_vs_GenZPt = new TH2F("hDiJetPt_vs_GenZPt", "hDiJetPt_vs_GenZPt", 100, 0, 300, 100, 0, 300);
    TH2F *hDiJetPz_vs_GenZPz = new TH2F("hDiJetPz_vs_GenZPz", "hDiJetPz_vs_GenZPz", 100, -500, 500, 100, -500, 500);
    TH1F *hDeltaPhi_DiJet_GenZ = new TH1F("hDeltaPhi_DiJet_GenZ", "hDeltaPhi_DiJet_GenZ", 50, -3.2, 3.2);
TH2F *hCosDeltaPhiJets_vs_Muons = new TH2F("hCosDeltaPhiJets_vs_Muons", "cos(#Delta#phi_{jj}) vs cos(#Delta#phi_{#mu#mu});cos(#Delta#phi_{#mu#mu});cos(#Delta#phi_{jj})", 50, -1.1, 1.1, 50, -1.1, 1.1);

    TH2F *hnMuonVMuon_leadingPt = new TH2F("hnMuonVMuon_leadingPt", "hnMuonVMuon_leadingPt", 10, -0.5, 9.5, 100, 0., 150.);
    TH2F *hMuon_phiVMuon_eta = new TH2F("hMuon_phiVMuon_eta", "hMuon_phiVMuon_eta", 50, -5., 5., 50, -5., 5.);
    TH2F *hMuon_ptVMuon_etaPlus = new TH2F("hMuon_ptVMuon_etaPlus", "hMuon_ptVMuon_etaPlus", 100, 0., 100., 50, -5., 5.);
    TH2F *hMuon_ptVMuon_etaMinus = new TH2F("hMuon_ptVMuon_etaMinus", "hMuon_ptVMuon_etaMinus", 100, 0., 100., 50, -5., 5.);
    TH2F *hEtaMuMinus_vs_EtaMuPlus = new TH2F("hEtaMuMinus_vs_EtaMuPlus", "#eta(#mu^{-}) vs #eta(#mu^{+});#eta(#mu^{+});#eta(#mu^{-})", 50, -2.5, 2.5, 50, -2.5, 2.5);
    TH2F *hLeadingMuPt_vs_Mass = new TH2F("hLeadingMuPt_vs_Mass", "Leading Muon p_{T} vs Invariant Mass;M_{#mu#mu} [GeV];Leading muon p_{T} [GeV]", 100, 0, 150, 100, 0, 150);
    TH2F *hCosDeltaPhi_vs_Mass = new TH2F("hCosDeltaPhi_vs_Mass", "cos(#Delta#phi) vs M_{#mu#mu};M_{#mu#mu} [GeV];cos(#Delta#phi)", 100, 0, 150, 50, -1.1, 1.1);
    TH2F *hRecoil1VsMass = new TH2F("hRecoil1VsMass", "Recoil 1 vs Mass;M_{ll};(MET+Pt)/M", 100, 0, 150, 100, 0, 3);
    TH2F *hMETvsMuonPt = new TH2F("hMETvsMuonPt", "MET vs Muon p_{T};Muon p_{T} [GeV];MET [GeV]", 100, 0, 200, 100, 0, 200);
    TH2F *hMETvsLeadingMuPt = new TH2F("hMETvsLeadingMuPt", "MET vs Leading Muon p_{T};Leading Muon p_{T} [GeV];MET [GeV]", 100, 0, 200, 100, 0, 200);
    TH2F *hnMuonVMET = new TH2F("hnMuonVMET", "nMuon vs MET;nMuon;MET pt [GeV]", 10, -0.5, 9.5, 100, 0, 200);
    TH2F *hDimuon_massVMuon_dxy = new TH2F("hDimuon_massVMuon_dxy", "hDimuon_massVMuon_dxy", 300, 0., 150., 100, -4., 4.);
    TH2F *hMET_significanceVMET_phi = new TH2F("hMET_significanceVMET_phi", "hMET_significanceVMET_phi", 100, 0., 25., 50, -5., 5.);
    TH2F *hMuon_deltaPhiVDimuon_mass = new TH2F("Muon_deltaPhiVDimuon_mass", "Muon_deltaPhiVDimuon_mass", 60, -6., 6., 300, 0., 150.);
    TH2F *hDimuon_ptVDimuon_mass = new TH2F("hDimuon_ptVDimuon_mass", "hDimuon_ptVDimuon_mass", 1000, 0., 200., 300, 0., 150.);
    TH2F *hDimuon_pzVDimuon_mass = new TH2F("hDimuon_pzVDimuon_mass", "hDimuon_pzVDimuon_mass", 2000, -200., 200., 300, 0., 150.);

    TH2F *hnJets_vs_nMuons = new TH2F("hnJets_vs_nMuons", "nJets vs nMuons (No Cuts); nMuon; nJet", 10, -0.5, 9.5, 20, -0.5, 19.5);
    TH2F *hnJets_vs_Mass = new TH2F("hnJets_vs_Mass", "nJets vs Invariant Mass (Opposite Charge); M_{#mu#mu} [GeV]; nJet", 100, 0, 150, 20, -0.5, 19.5);
    TH2F *hnJets_vs_LeadingJetPt = new TH2F("hnJets_vs_LeadingJetPt", "nJets vs Leading Jet p_{T} (Opposite Charge); Leading Jet p_{T} [GeV]; nJet", 100, 0, 300, 20, -0.5, 19.5);
    TH2F *hnJets_vs_nTau = new TH2F("hnJets_vs_nTau", "nJets vs nTau; nTau; nJet", 10, -0.5, 9.5, 20, -0.5, 19.5);
    TH2F *hGenJet_ptVsMass = new TH2F("hGenJet_ptVsMass", "GenJet p_{T} as a function of Mass; Mass [GeV]; p_{T} [GeV]", 50, 0, 50, 100, 0, 300);

    Int_t nentries = (Int_t)t1->GetEntries();
    Int_t maxEvents = 1000000; 
    Int_t eventsToProcess = std::min(nentries, maxEvents);
    
    std::cout << "Events to process: " << eventsToProcess << std::endl;

    for (int i = 0; i < eventsToProcess; i++) {
        t1->GetEntry(i);
      
        if (i % 100000 == 0) { 
            float progress = (float)i / eventsToProcess * 100; 
            std::cout << "Progress: " << progress << "% (" << i << " events)\r" << std::flush;
        }

        if (i < 100) {
            std::cout << "Event " << i << " nJet: " << nJet << std::endl;
            for (UInt_t j = 0; j < nJet; j++) {
                std::cout << "  Jet " << j << " pt: " << Jet_pt[j] << std::endl;
            }
        }

        hnJets_vs_nMuons->Fill(nMuon, nJet);
        hnJets_vs_nTau->Fill(nTau, nJet);
        
        hnJet->Fill(nJet);
        for(UInt_t j = 0; j < nJet; j++) {
            hJet_pt->Fill(Jet_pt[j]);
            hJet_eta->Fill(Jet_eta[j]);
            hJet_phi->Fill(Jet_phi[j]);
            hJet_mass->Fill(Jet_mass[j]);
        }

        hnGenJet->Fill(nGenJet);
        for(UInt_t gj = 0; gj < nGenJet; gj++) {
            hGenJet_pt->Fill(GenJet_pt[gj]);
            hGenJet_eta->Fill(GenJet_eta[gj]);
            hGenJet_phi->Fill(GenJet_phi[gj]);
            hGenJet_mass->Fill(GenJet_mass[gj]);
            hGenJet_ptVsMass->Fill(GenJet_mass[gj], GenJet_pt[gj]);
        }

        if (nJet >= 2) {
            TLorentzVector j1, j2, dijet;
            j1.SetPtEtaPhiM(Jet_pt[0], Jet_eta[0], Jet_phi[0], Jet_mass[0]);
            j2.SetPtEtaPhiM(Jet_pt[1], Jet_eta[1], Jet_phi[1], Jet_mass[1]);
            dijet = j1 + j2;
            hDijet_mass->Fill(dijet.M());
            double deltaPhiJets = TVector2::Phi_mpi_pi(Jet_phi[0] - Jet_phi[1]);
            double cosDeltaPhiJets = cos(deltaPhiJets);
            hCosDeltaPhiJets->Fill(cosDeltaPhiJets);
            hCosDeltaPhiJets_vs_Muons->Fill(cosDeltaPhi, cosDeltaPhiJets);
        }

        hnMuon->Fill(nMuon);
        hMET_pt->Fill(MET_pt);
        hMET_phi->Fill(MET_phi);
        hMET_sumEt->Fill(MET_sumEt);
        hMET_significance->Fill(MET_significance);
        hMET_covXX->Fill(MET_covXX);
        hMET_covXY->Fill(MET_covXY);
        hMET_covYY->Fill(MET_covYY);
        hCaloMET_pt->Fill(CaloMET_pt);
        hCaloMET_phi->Fill(CaloMET_phi);
        hCaloMET_sumEt->Fill(CaloMET_sumEt);
        hMET_significanceVMET_phi->Fill(MET_significance, MET_phi);

        for(UInt_t mu = 0; mu < nMuon; mu++) {
            hMuon_charge->Fill(Muon_charge[mu]);
            hMuon_tightCharge->Fill(Muon_tightCharge[mu]);
            hMuon_pt->Fill(Muon_pt[mu]);
            hMuon_ptErr->Fill(Muon_ptErr[mu]);
            hMuon_eta->Fill(Muon_eta[mu]);
            hMuon_phi->Fill(Muon_phi[mu]);
            hMuon_mass->Fill(Muon_mass[mu]);
            hMuon_dxy->Fill(Muon_dxy[mu]);
            hMuon_pfRelIso04_all->Fill(Muon_pfRelIso04_all[mu]);
            hMuon_pfRelIso03_all->Fill(Muon_pfRelIso03_all[mu]);
        }

        float genZ_pt = -1.0;
        float genZ_pz = -9999.0;
        TLorentzVector zVec;
        for (UInt_t gp = 0; gp < nGenPart; gp++) {
            if (GenPart_pdgId[gp] == 23 && GenPart_status[gp] == 3) {
                genZ_pt = GenPart_pt[gp];
                zVec.SetPtEtaPhiM(GenPart_pt[gp], GenPart_eta[gp], GenPart_phi[gp], GenPart_mass[gp]);
                genZ_pz = zVec.Pz();
                break;
            }
        }

        int nGenJet25 = 0;
        for (UInt_t gj = 0; gj < nGenJet; gj++) {
            if (GenJet_pt[gj] > 25.0) {
                nGenJet25++;
            }
        }

        if (genZ_pt >= 0.0) {
            hnGenJet_vs_GenZPt->Fill(genZ_pt, nGenJet);
            hnGenJet25_vs_GenZPt->Fill(genZ_pt, nGenJet25);
            hnGenJet_vs_GenZPz->Fill(genZ_pz, nGenJet);
            hnGenJet25_vs_GenZPz->Fill(genZ_pz, nGenJet25);

            if (nJet >= 2) {
                float sumJetsPt = Jet_pt[0] + Jet_pt[1];
                hSumLeadingJetsPt_vs_GenZPt->Fill(genZ_pt, sumJetsPt);

                TLorentzVector j1, j2, dijet;
                j1.SetPtEtaPhiM(Jet_pt[0], Jet_eta[0], Jet_phi[0], Jet_mass[0]);
                j2.SetPtEtaPhiM(Jet_pt[1], Jet_eta[1], Jet_phi[1], Jet_mass[1]);
                dijet = j1 + j2;
                hGenZPt_vs_DiJetPt->Fill(genZ_pt, dijet.Pt());
                
                hDiJetPt_vs_GenZPt->Fill(genZ_pt, dijet.Pt());
                hDiJetPz_vs_GenZPz->Fill(genZ_pz, dijet.Pz());
                
                double deltaPhiDiJetZ = TVector2::Phi_mpi_pi(dijet.Phi() - zVec.Phi());
                hDeltaPhi_DiJet_GenZ->Fill(deltaPhiDiJetZ);

                if (Jet_pt[0] > 25.0 && Jet_pt[1] > 25.0) {
                    hSumLeadingJets25Pt_vs_GenZPt->Fill(genZ_pt, sumJetsPt);

                    if (nMuon >= 2) {
                        double deltaPhiJets = TVector2::Phi_mpi_pi(Jet_phi[0] - Jet_phi[1]);
                        double deltaPhiMuons = TVector2::Phi_mpi_pi(Muon_phi[0] - Muon_phi[1]);
                        hDeltaPhiMuons_vs_DeltaPhiJets->Fill(deltaPhiJets, deltaPhiMuons);
                    }
                }
            }
        }

        int genMu1_idx = -1;
        int genMu2_idx = -1;
        for (UInt_t gp = 0; gp < nGenPart; gp++) {
            if (std::abs(GenPart_pdgId[gp]) == 13 && GenPart_status[gp] == 2) {
                int momIdx = GenPart_genPartIdxMother[gp];
                if (momIdx >= 0 && GenPart_pdgId[momIdx] == 23) {
                    if (genMu1_idx == -1) {
                        genMu1_idx = gp;
                    } else if (genMu2_idx == -1) {
                        genMu2_idx = gp;
                    }
                }
            }
        }


        if (nMuon < 2) continue; 

        Muon_leadingPt = Muon_pt[0];
        for (UInt_t mu = 1; mu < nMuon; mu++) {
            if (Muon_pt[mu] > Muon_leadingPt) {
                Muon_leadingPt = Muon_pt[mu];
            }
        }

        hnMuonVMET->Fill(nMuon, MET_pt);
        hMETvsLeadingMuPt->Fill(Muon_leadingPt, MET_pt);
        hMuon_leadingPt->Fill(Muon_leadingPt);
        hnMuonVMuon_leadingPt->Fill(nMuon, Muon_leadingPt);
        
        hMuon_eta1->Fill(Muon_eta[0]);
        hMuon_eta1->Fill(Muon_eta[1]);
        hMuon_phi_correct->Fill(Muon_phi[0]);
        hMuon_phi_correct->Fill(Muon_phi[1]);
        hMuon_pt_plan->Fill(Muon_pt[0]);
        hMuon_pt_plan->Fill(Muon_pt[1]);

        hMuon_phiVMuon_eta->Fill(Muon_phi[0], Muon_eta[0]);
        hMuon_phiVMuon_eta->Fill(Muon_phi[1], Muon_eta[1]);

        if (Muon_charge[0] > 0) {
            hMuon_ptVMuon_etaPlus->Fill(Muon_pt[0], Muon_eta[0]);
            hMuon_ptVMuon_etaMinus->Fill(Muon_pt[1], Muon_eta[1]);
            hEtaMuMinus_vs_EtaMuPlus->Fill(Muon_eta[0], Muon_eta[1]);
        } else {
            hMuon_ptVMuon_etaMinus->Fill(Muon_pt[0], Muon_eta[0]);
            hMuon_ptVMuon_etaPlus->Fill(Muon_pt[1], Muon_eta[1]);
            hEtaMuMinus_vs_EtaMuPlus->Fill(Muon_eta[1], Muon_eta[0]);
        }

        double deltaPhi = TVector2::Phi_mpi_pi(Muon_phi[0] - Muon_phi[1]);
        double cosDeltaPhi = cos(deltaPhi);
        double deltaEta = Muon_eta[0] - Muon_eta[1];

        hCosDeltaPhi->Fill(cosDeltaPhi);
        hMuon_deltaPhi->Fill(deltaPhi);
        hDeltaEta->Fill(deltaEta);

        double invMass = AnalysisPhysics::CalculateInvMass_Hand(
            Muon_pt[0], Muon_eta[0], Muon_phi[0], Muon_mass[0],
            Muon_pt[1], Muon_eta[1], Muon_phi[1], Muon_mass[1]
        );

        double transMassZ = AnalysisPhysics::CalculateTransMassZ_Hand(
            Muon_pt[0], Muon_phi[0], Muon_mass[0],
            Muon_pt[1], Muon_phi[1], Muon_mass[1]
        );

        hZDimuon_MassRuka->Fill(invMass);
        htransMassZ->Fill(transMassZ);
        hLeadingMuPt_vs_Mass->Fill(invMass, Muon_leadingPt);
        hCosDeltaPhi_vs_Mass->Fill(invMass, cosDeltaPhi);
        
        TLorentzVector mu1, mu2, dimuon;
        mu1.SetPtEtaPhiM(Muon_pt[0], Muon_eta[0], Muon_phi[0], Muon_mass[0]);
        mu2.SetPtEtaPhiM(Muon_pt[1], Muon_eta[1], Muon_phi[1], Muon_mass[1]);
        dimuon = mu1 + mu2;
        
        double pt_ll   = dimuon.Pt();
        double mass_ll = dimuon.M();
        
        double rec1 = AnalysisPhysics::CalculateRecoil1(MET_pt, pt_ll, mass_ll);
        double diff_Z = invMass - mass_ll;
        
        hMassDifference->Fill(diff_Z);
        hZDimuon_mass->Fill(mass_ll);
        hRecoil1VsMass->Fill(mass_ll, rec1);
        
        hDimuon_massVMuon_dxy->Fill(mass_ll, Muon_dxy[0]);
        hDimuon_massVMuon_dxy->Fill(mass_ll, Muon_dxy[1]);
        hMuon_deltaPhiVDimuon_mass->Fill(deltaPhi, mass_ll);
        
        hDimuon_pt->Fill(pt_ll);
        hDimuon_pz->Fill(dimuon.Pz());
        hDimuon_ptVDimuon_mass->Fill(pt_ll, mass_ll);
        hDimuon_pzVDimuon_mass->Fill(dimuon.Pz(), mass_ll);

        if (Muon_charge[0] * Muon_charge[1] < 0) {
            hnJets_vs_Mass->Fill(invMass, nJet);

            if (nJet > 0) {
                float leadingJetPt = -1.0;
                for (UInt_t j = 0; j < nJet; j++) {
                    if (Jet_pt[j] > leadingJetPt) {
                        leadingJetPt = Jet_pt[j];
                    }
                }
                hnJets_vs_LeadingJetPt->Fill(leadingJetPt, nJet);
            }
        }
    } 
    
    std::cout << "\nAnalysis completed." << std::endl;

    fout->mkdir("Mu_Plots");
    fout->mkdir("MET_Plots");
    fout->mkdir("CaloMET_Plots");
    fout->mkdir("Dimuon_Ana");
    fout->mkdir("Jet_Plots");
    fout->mkdir("GenJet_Plots");
    fout->mkdir("Tau_Plots");

    fout->cd("Mu_Plots");
    hnMuon->Write();
    hMuon_charge->Write();
    hMuon_tightCharge->Write();
    hMuon_pt->Write();
    hMuon_ptErr->Write();
    hMuon_eta->Write();
    hMuon_phi->Write();
    hMuon_mass->Write();
    hMuon_dxy->Write();
    hMuon_pfRelIso04_all->Write();
    hMuon_pfRelIso03_all->Write();

    fout->cd("MET_Plots");
    hMET_pt->Write();
    hMET_phi->Write();
    hMET_sumEt->Write();
    hMET_significance->Write();
    hMET_covXX->Write();
    hMET_covXY->Write();
    hMET_covYY->Write();
    hMET_significanceVMET_phi->Write();
    
    fout->cd("CaloMET_Plots");
    hCaloMET_pt->Write();
    hCaloMET_phi->Write();
    hCaloMET_sumEt->Write();

    fout->cd("Dimuon_Ana");
    hMuon_leadingPt->Write();
    hMuon_eta1->Write();
    hMuon_deltaPhi->Write();
    hMuon_pt_plan->Write();
    hMuon_phi_correct->Write();
    hDeltaEta->Write();
    hZDimuon_mass->Write();
    hZDimuon_MassRuka->Write();
    hDimuon_pt->Write();
    hDimuon_pz->Write();
    hMassDifference->Write(); 
    htransMassZ->Write();
    
    hnMuonVMuon_leadingPt->Write();
    hMuon_phiVMuon_eta->Write();
    hMuon_ptVMuon_etaPlus->Write();
    hMuon_ptVMuon_etaMinus->Write();
    hEtaMuMinus_vs_EtaMuPlus->Write();
    hLeadingMuPt_vs_Mass->Write();
    hCosDeltaPhi_vs_Mass->Write();
    hRecoil1VsMass->Write();
    hMETvsMuonPt->Write();
    hMETvsLeadingMuPt->Write();
    hnMuonVMET->Write();
    hDimuon_massVMuon_dxy->Write();
    hMuon_deltaPhiVDimuon_mass->Write();
    hDimuon_ptVDimuon_mass->Write();
    hDimuon_pzVDimuon_mass->Write();
    hCosDeltaPhi->Write();

    fout->cd("Jet_Plots");
    hnJet->Write();
    hJet_pt->Write();
    hJet_eta->Write();
    hJet_phi->Write();
    hJet_mass->Write();
    hDijet_mass->Write();
    hnJets_vs_nMuons->Write();
    hnJets_vs_Mass->Write();
    hnJets_vs_LeadingJetPt->Write();
    hCosDeltaPhiJets->Write();
    hCosDeltaPhiJets_vs_Muons->Write();
    
    fout->cd("GenJet_Plots");
    hnGenJet->Write();
    hGenJet_pt->Write();
    hGenJet_eta->Write();
    hGenJet_phi->Write();
    hGenJet_mass->Write();
    hnGenJet_vs_nJet->Write();
    hGenJet_ptVsMass->Write();
    
    hnGenJet_vs_GenZPt->Write();
    hnGenJet25_vs_GenZPt->Write();
    hSumLeadingJetsPt_vs_GenZPt->Write();
    hSumLeadingJets25Pt_vs_GenZPt->Write();
    hDeltaPhiMuons_vs_DeltaPhiJets->Write();

    hnGenJet_vs_GenZPz->Write();
    hnGenJet25_vs_GenZPz->Write();
    hGenZPt_vs_DiJetPt->Write();
    
    hDiJetPt_vs_GenZPt->Write();
    hDiJetPz_vs_GenZPz->Write();
    hDeltaPhi_DiJet_GenZ->Write();

    fout->cd("Tau_Plots");
    hnJets_vs_nTau->Write();
  
    fout->Close(); 
}