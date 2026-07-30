#ifndef ANALYSISPHYSICS_H
#define ANALYSISPHYSICS_H

#include <cmath>
#include "TVector2.h"
#include "TLorentzVector.h"

class AnalysisPhysics {
public:
    // Изчисление за W бозон
    static inline double CalculateMT_TVector(double ptMu, double phiMu, double met, double phiMet) {
        double dPhi_TVector = TVector2::Phi_mpi_pi(phiMu - phiMet);
        return std::sqrt(2 * ptMu * met * (1 - std::cos(dPhi_TVector)));
    }

    static inline double CalculateMT_Hand(double ptMu, double phiMu, double met, double phiMet) {
        const double PI = 3.1415926535;
        double dPhi_Hand = phiMu - phiMet;
        while (dPhi_Hand >  PI) dPhi_Hand -= 2 * PI;
        while (dPhi_Hand < -PI) dPhi_Hand += 2 * PI;
        return std::sqrt(2 * ptMu * met * (1 - std::cos(dPhi_Hand)));
    }
    
    // Изчисления за Dimuon (Z)
    static inline double CalculateInvMass_Hand(double pt1, double eta1, double phi1, double m1,
                                               double pt2, double eta2, double phi2, double m2) {
        double mu1Et = std::sqrt(pt1 * pt1 + m1 * m1);
        double mu2Et = std::sqrt(pt2 * pt2 + m2 * m2);
        double dPhi = phi1 - phi2;
        double dEta = eta1 - eta2;
        
        double M2 = (m1 * m1) + (m2 * m2) + 2 * (mu1Et * mu2Et * std::cosh(dEta) - pt1 * pt2 * std::cos(dPhi));
        return std::sqrt(M2);
    }

    static inline double CalculateTransMassZ_Hand(double pt1, double phi1, double m1,
                                                  double pt2, double phi2, double m2) {
        double mu1Et = std::sqrt(pt1 * pt1 + m1 * m1);
        double mu2Et = std::sqrt(pt2 * pt2 + m2 * m2);
        double dPhi = phi1 - phi2;
        
        double M2_trans = (m1 * m1) + (m2 * m2) + 2 * (mu1Et * mu2Et - pt1 * pt2 * std::cos(dPhi));
        return std::sqrt(M2_trans);
    }
    static inline double CalculateRecoil1(double met, double pt_ll, double mass_ll) {
    if (mass_ll <= 0) return 0;
    return (met + pt_ll) / mass_ll;
}

};

#endif


