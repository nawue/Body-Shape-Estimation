#pragma once

#include "ceres/ceres.h"
#include "igl/point_mesh_squared_distance.h"
#include "igl/signed_distance.h"

#include <GeneralMesh/GeneralMesh.h>
#include "SMPLWrapper.h"

class AbsoluteDistanceForShape : public ceres::CostFunction
{
public:
    AbsoluteDistanceForShape(SMPLWrapper*, GeneralMesh *, const double param);
    ~AbsoluteDistanceForShape();

    // parameters[0] <-> shape, parameters[1] <-> translation
    // Main idea for point-to-surface distance jacobian: 
    // Gradient for each vertex correspondes to the distance from this vertex to the input mesh.
    virtual bool Evaluate(double const* const* parameters,
        double* residuals,
        double** jacobians) const;

private:
    GeneralMesh * toMesh_;
    SMPLWrapper * smpl_;

    // optional
    double inside_coef_ = 0.;
    double outside_coef_ = 1.;
};

