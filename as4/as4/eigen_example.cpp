typedef Matrix<float, 3, 3> Matrix3f;

Matrix3f first; 
first(0, 0, 0) = 1;
first(0, 0, 1) = 3;

Matrix3f second;
second << 1, 2, 3,
4, 5, 6,
7, 8, 9;

Matrix3f sum = first + second;


//CREATING dynamic matrix stuff
typedef Matrix<double, Dynamic, Dynamic> MatrixXd;
MatrixXf third(10,15); 

//transposition and conjugation
MatrixXf a = MatrixXf::Random(2,2);
cout << "Here is the matrix a\n" << a << endl;
cout << "Here is the matrix a^T\n" << a.transpose() << endl;
cout << "Here is the conjugate of a\n" << a.conjugate() << endl;
cout << "Here is the matrix a^*\n" << a.adjoint() << endl;

//jacobian stuff
JACOBIAN_goodie = matrix transposed * INVERSE OF (matrix * matrix transposed)
// http://math.ucsd.edu/~sbuss/ResearchWeb/ikmethods/iksurvey.pdf FOR MORE INFO


^^ if the above does not work!
e.g. 
MatrixXf m = MatrixXf::Random(3,2);
cout << "Here is the matrix m:" << endl << m << endl;
JacobiSVD<MatrixXf> svd(m, ComputeThinU | ComputeThinV);
cout << "Its singular values are:" << endl << svd.singularValues() << endl;
cout << "Its left singular vectors are the columns of the thin U matrix:" << endl << svd.matrixU() << endl;
cout << "Its right singular vectors are the columns of the thin V matrix:" << endl << svd.matrixV() << endl;
Vector3f rhs(1, 0, 0);
cout << "Now consider this rhs vector:" << endl << rhs << endl;
cout << "A least-squares solution of m*x = rhs is:" << endl << svd.solve(rhs) << endl;

OR 

void RotationJoint::computeJacobianEntries(mat& jacobian,
                                           vec& state,
                                           const size_t effectorId,
                                           const Context& ctx,
                                           const vec3& desired,
                                           const vec3& effector,
                                           const vec3& direction) const {
  vec3 rotAxis = ctx.getVectorInContext(axis);
  state.rows(3 * jointId, 3 * jointId + 2) = rotAxis;
  vec3 jacobianEntry = cross(rotAxis, direction); 
  jacobian(3 * effectorId,     jointId) = jacobianEntry[0];
  jacobian(3 * effectorId + 1, jointId) = jacobianEntry[1];
  jacobian(3 * effectorId + 2, jointId) = jacobianEntry[2];
}

void AxisBallAndSocketJoint::computeJacobianEntries(mat& jacobian,
                                                    vec& state,
                                                    const size_t effectorId,
                                                    const Context& ctx,
                                                    const vec3& desired,
                                                    const vec3& effector,
                                                    const vec3& direction) const {
  vec3 rotAxis;
  if (vec3_equals(desired, effector))
    rotAxis = makeVec3(1, 0, 0);
  else {
    rotAxis = cross(effector - ctx.getCurrentOrigin(),
                    desired - ctx.getCurrentOrigin());
    rotAxis = normalize_vec3(rotAxis);
  }

  state.rows(3 * jointId, 3 * jointId + 2) = rotAxis;
  vec3 jacobianEntry = cross(rotAxis, direction); 
  jacobian(3 * effectorId,     jointId) = jacobianEntry[0];
  jacobian(3 * effectorId + 1, jointId) = jacobianEntry[1];
  jacobian(3 * effectorId + 2, jointId) = jacobianEntry[2];
}


^^ DO NOT USE THOSE! They are examples that I found when I googled









