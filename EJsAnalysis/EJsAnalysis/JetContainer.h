#ifndef EJsAnalysis_JetContainer_H
#define EJsAnalysis_JetContainer_H

#include <xAODAnaHelpers/JetContainer.h>

namespace EJs {

  class JetContainer : public xAH::JetContainer
  {
  public:
    JetContainer( const std::string& name = "jet", const std::string& detailStr = "", float units = 1e3, bool mc = false );
    virtual ~JetContainer();

    virtual void setTree     ( TTree* tree );
    virtual void setBranches ( TTree* tree );
    virtual void clear       ( );
    virtual void FillJet     ( const xAOD::Jet* jet );


  private:
    // vector branches
    std::vector<int>*   m_ID;
    std::vector<float>* m_radius;

    std::vector<std::vector<float>>* m_constit_E;
    std::vector<std::vector<float>>* m_constit_pt;
    std::vector<std::vector<float>>* m_constit_eta;
    std::vector<std::vector<float>>* m_constit_phi;
  };

  #define AUXDYN( obj, type, varname ) \
  ( obj->isAvailable<type>(varname) ? obj->auxdataConst<type>(varname) : std::numeric_limits<type>::quiet_NaN() )

}

#endif // EJsAnalysis_JetContainer_H
