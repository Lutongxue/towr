/*
 * problem_specification.h
 *
 *  Created on: Apr 13, 2016
 *      Author: winklera
 */

#ifndef USER_TASK_DEPENDS_XPP_OPT_INCLUDE_XPP_ZMP_PROBLEM_SPECIFICATION_H_
#define USER_TASK_DEPENDS_XPP_OPT_INCLUDE_XPP_ZMP_PROBLEM_SPECIFICATION_H_

#include <xpp/hyq/support_polygon_container.h>
#include <xpp/zmp/continuous_spline_container.h>

namespace xpp {
namespace zmp {

/**
 * Serves as a base class for all modules that give higher level input to the
 * optimizer (cost function, constraints) and bundles all this information.
 * All methods that could be used as cost functions AND constraints should be
 * defined in this class.
 * This class does NOT include any NLP/Ipopt specific information.
 */
class ProblemSpecification {

public:
  typedef xpp::hyq::SupportPolygonContainer SupportPolygonContainer;
  typedef SupportPolygonContainer::VecFoothold VecFoothold;
  typedef Eigen::VectorXd VectorXd;
  typedef Eigen::Vector2d Vector2d;
  typedef xpp::hyq::Foothold Foothold;
  typedef xpp::utils::StdVecEigen2d StdVecEigen2d;
  typedef xpp::hyq::LegID LegID;

public:
  explicit ProblemSpecification (const SupportPolygonContainer& supp_poly_container,
                                 const ContinuousSplineContainer& cog_spline_container);
  virtual ~ProblemSpecification ();

  ContinuousSplineContainer GetSplineContainer() const { return zmp_spline_container_; };
  LegID GetLegID(int step) const { return supp_polygon_container_.GetLegID(step); };
  VecFoothold GetStartStance() const { return supp_polygon_container_.GetStartStance(); };


protected:
  SupportPolygonContainer supp_polygon_container_;
  ContinuousSplineContainer zmp_spline_container_;

  void UpdateCurrentState(const VectorXd& x_coeff, const StdVecEigen2d& footholds);
  VectorXd DistanceFootToNominalStance(const VectorXd& x_coeff, const StdVecEigen2d& footholds) const;

  VectorXd DistanceSquareFootToGapboarder(const StdVecEigen2d& footholds,
                                          double gap_center_x,
                                          double gap_width_x) const;

private:
  Eigen::VectorXd DistanceFootToNominalStance(const SupportPolygonContainer& supp_polygon_container,
                                              const ContinuousSplineContainer& zmp_spline_container) const;
};

} /* namespace zmp */
} /* namespace xpp */

#endif /* USER_TASK_DEPENDS_XPP_OPT_INCLUDE_XPP_ZMP_PROBLEM_SPECIFICATION_H_ */