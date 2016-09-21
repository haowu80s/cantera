/**
 * @file RxnActiveMgr.h
 * @ingroup chemkinetics
 */

// Copyright 2016  Hao Wu (wuhao@stanford.edu)

#ifndef CT_RXNACTIVEMGR_H
#define CT_RXNACTIVEMGR_H

#include <Eigen/Sparse>
#include <Eigen/Dense>

#include "Kinetics.h"

namespace Cantera
{
class RxnActiveMgr
{
public:

  typedef Eigen::SparseMatrix<double,Eigen::ColMajor> SpCMat;
  typedef Eigen::SparseMatrix<double,Eigen::RowMajor> SpRMat;
  typedef Eigen::VectorXd VecType;

  RxnActiveMgr(Kinetics* _kin) : m_kinetics(_kin), m_nSpecs(0), m_nRxns(0) {}

  Kinetics& kinetics() {
    return *m_kinetics;
  }

  const Kinetics& kinetics() const {
    return *m_kinetics;
  }

  // Update the stoich. matrix from the Kinetics
  void updateStoichMatrix();

  // Choose active reactions
  void updateActiveRxns(const double relTol, const double absTol);

  // get m_iactive
  const std::vector<bool>& iActive() { return m_iactive; }
  
protected:
  //! pointer to the Kinetics object
  Kinetics* m_kinetics;
  size_t m_nSpecs;
  size_t m_nRxns;

  //! Record of reaction activation
  std::vector<bool> m_iactive;

  //! Sparse matrices for adaptive chemistry
  //! Stoich. matrix
  SpCMat m_stoich_mol; // kmol

  //! Workign array of size m_nRxns
  VecType m_wa_nr; // Net rate of progress [kmol/m^3/s]
  //! Workign array of size m_nSpecs
  VecType m_wa_ns; // Internal energy per mol
  //! Workign array of same size as stoich. matrix
  SpCMat m_wm;

  // ! Resize matrices and vectors
  void resizeData(const size_t _nSpecs, const size_t _nRxns);
};
}

#endif