#ifndef EJSANALYSIS_LINKDEF_H
#define EJSANALYSIS_LINKDEF_H

#include <EJsAnalysis/SecondaryVertexSelector.h>
#include <EJsAnalysis/TruthVertexSelector.h>
#include <EJsAnalysis/VertexMatcher.h>
#include <EJsAnalysis/ObjectMatcher.h>
#include <EJsAnalysis/EJsxAODAnalysis.h>
#include <EJsAnalysis/EJsMiniNtuple.h>
#include <EJsAnalysis/EJsNtupleToHists.h>

#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;
#pragma link C++ nestedclass;

#pragma link C++ class SecondaryVertexSelector+;
#pragma link C++ class TruthVertexSelector+;
#pragma link C++ class VertexMatcher+;
#pragma link C++ class ObjectMatcher+;
#pragma link C++ class EJsxAODAnalysis+;
#pragma link C++ class EJsMiniNtuple+;
#pragma link C++ class EJsNtupleToHists+;

#endif // EJSANALYSIS_LINKDEF_H
