#ifndef EJsAnalysis_VertexContainer_H
#define EJsAnalysis_VertexContainer_H

#include <vector>
#include <string>

#include <TTree.h>

namespace EJs {

  class VertexContainer
  {
  public:
    VertexContainer ( const std::string& name, float units = 1e3 )
      : m_name  ( name ),
        m_units ( units ),
        m_debug ( false )
    {
      m_n = 0;
    }

    
    virtual ~VertexContainer() {};

    
    virtual void setTree ( TTree* tree )
    {
      std::string counterName  = "n" + m_name;
      tree->SetBranchStatus  ( counterName.c_str(), 1 );
      tree->SetBranchAddress ( counterName.c_str(), &m_n );  
    }

    
    virtual void setBranches ( TTree* tree )
    {
      std::string counterName  = "n" + m_name;
      tree->Branch( counterName.c_str(), &m_n, (counterName+"/I").c_str() );
    }

    
    virtual void clear ()
    {
      m_n = 0;
    }

    
    virtual void FillVertex ()
    {
      m_n++;
    }

    // updateEntry, at_nonConst, at, operator, size ... do we need these ??

    
  protected:
    std::string branchName ( const std::string& varName )
    {
      std::string name  = m_name + "_" + varName;
      return name;
    }

    
    template <typename T_BR> void connectBranch ( TTree* tree, const std::string& branch,
						 std::vector<T_BR> **variable )
    {
      std::string name = branchName( branch );  
      if ( *variable ) { delete (*variable); (*variable) = 0; }
      if ( tree->GetBranch( name.c_str() ) ) {
	(*variable) = new std::vector<T_BR>();
	tree->SetBranchStatus  ( name.c_str(), 1 );
	tree->SetBranchAddress ( name.c_str(), variable );
      }
    }

    
    template <typename T> void setBranch ( TTree* tree, std::string varName,
					   std::vector<T>* localVectorPtr )
    {
      std::string name = branchName( varName );
      tree->Branch( name.c_str(), localVectorPtr );
    }

    
    // safe*Fill, updateParticle ... may want to add later...

    
    std::string m_name;
    // m_vertices ...

    
  public:
    int   m_n;
    float m_units; 
    bool  m_debug; 

  };

} // EJs

#endif // EJsAnalysis_VertexContainer_H
