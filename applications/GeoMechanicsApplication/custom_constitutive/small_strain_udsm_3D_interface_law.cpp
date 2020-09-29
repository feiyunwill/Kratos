// KRATOS___
//     //   ) )
//    //         ___      ___
//   //  ____  //___) ) //   ) )
//  //    / / //       //   / /
// ((____/ / ((____   ((___/ /  MECHANICS
//
//  License:         geo_mechanics_application/license.txt
//
//  Main authors:    Vahid Galavi
//

// System includes

// External includes

#include "custom_constitutive/small_strain_udsm_3D_interface_law.hpp"


namespace Kratos
{

//******************************CONSTRUCTOR*******************************************
//************************************************************************************

SmallStrainUDSM3DInterfaceLaw::SmallStrainUDSM3DInterfaceLaw()
   : SmallStrainUDSM3DLaw()
   {
    KRATOS_TRY;
    //KRATOS_INFO("SmallStrainUDSM3DInterfaceLaw()") << std::endl;

    KRATOS_CATCH("")

   }

//******************************COPY CONSTRUCTOR**************************************
//************************************************************************************
SmallStrainUDSM3DInterfaceLaw::
   SmallStrainUDSM3DInterfaceLaw(const SmallStrainUDSM3DInterfaceLaw &rOther)
   : SmallStrainUDSM3DLaw(rOther)
{
   KRATOS_TRY;
   //KRATOS_INFO("SmallStrainUDSM3DInterfaceLaw(const...)") << std::endl;

   KRATOS_CATCH("");
}

//********************************CLONE***********************************************
//************************************************************************************

ConstitutiveLaw::Pointer SmallStrainUDSM3DInterfaceLaw::Clone() const
{
   KRATOS_TRY;
   //KRATOS_INFO("Clone()") << std::endl;

   return Kratos::make_shared<SmallStrainUDSM3DInterfaceLaw>(*this);

   KRATOS_CATCH("");
}

//********************************ASSIGNMENT******************************************
//************************************************************************************
SmallStrainUDSM3DInterfaceLaw 
  &SmallStrainUDSM3DInterfaceLaw::operator=(SmallStrainUDSM3DInterfaceLaw const &rOther)
{
   KRATOS_TRY;

   SmallStrainUDSM3DLaw::operator=(rOther);

   //KRATOS_INFO("operator=") << std::endl;

   return *this;

   KRATOS_CATCH("");
}

//*******************************DESTRUCTOR*******************************************
//************************************************************************************

SmallStrainUDSM3DInterfaceLaw::~SmallStrainUDSM3DInterfaceLaw()
{
   //KRATOS_INFO("~SmallStrainUDSM3DLaw()") << std::endl;
}


//************************************************************************************
//************************************************************************************

void SmallStrainUDSM3DInterfaceLaw::UpdateInternalDeltaStrainVector(ConstitutiveLaw::Parameters &rValues)
{
   const Vector& rStrainVector = rValues.GetStrainVector();

   mDeltaStrainVector[INDEX_3D_ZZ] = rStrainVector(INDEX_3D_INTERFACE_ZZ) - mStrainVectorFinalized[INDEX_3D_ZZ];
   mDeltaStrainVector[INDEX_3D_YZ] = rStrainVector(INDEX_3D_INTERFACE_YZ) - mStrainVectorFinalized[INDEX_3D_YZ];
   mDeltaStrainVector[INDEX_3D_XZ] = rStrainVector(INDEX_3D_INTERFACE_XZ) - mStrainVectorFinalized[INDEX_3D_XZ];

}

void SmallStrainUDSM3DInterfaceLaw::SetExternalStressVector(Vector& rStressVector)
{
   //KRATOS_INFO("mStressVector") << mStressVector << std::endl;

   rStressVector(INDEX_3D_INTERFACE_ZZ) = mStressVector[INDEX_3D_ZZ];
   rStressVector(INDEX_3D_INTERFACE_YZ) = mStressVector[INDEX_3D_YZ];
   rStressVector(INDEX_3D_INTERFACE_XZ) = mStressVector[INDEX_3D_XZ];
}


void SmallStrainUDSM3DInterfaceLaw::SetInternalStressVector(const Vector& rStressVector)
{
   // KRATOS_INFO("SetInternalStressVector:rStressVector") << rStressVector << std::endl;
   KRATOS_TRY;
   std::fill(mStressVectorFinalized.begin(), mStressVectorFinalized.end(), 0.0);

   mStressVectorFinalized[INDEX_3D_ZZ] = rStressVector(INDEX_3D_INTERFACE_ZZ);
   mStressVectorFinalized[INDEX_3D_YZ] = rStressVector(INDEX_3D_INTERFACE_YZ);
   mStressVectorFinalized[INDEX_3D_XZ] = rStressVector(INDEX_3D_INTERFACE_XZ);
   KRATOS_CATCH("")
}

void SmallStrainUDSM3DInterfaceLaw::SetInternalStrainVector(const Vector& rStrainVector)
{
   // KRATOS_INFO("SetInternalStrainVector:rStrainVector") << rStrainVector << std::endl;
   std::fill(mStrainVectorFinalized.begin(), mStrainVectorFinalized.end(), 0.0);

   mStrainVectorFinalized[INDEX_3D_ZZ] = rStrainVector(INDEX_3D_INTERFACE_ZZ);
   mStrainVectorFinalized[INDEX_3D_YZ] = rStrainVector(INDEX_3D_INTERFACE_YZ);
   mStrainVectorFinalized[INDEX_3D_XZ] = rStrainVector(INDEX_3D_INTERFACE_XZ);

}


void SmallStrainUDSM3DInterfaceLaw::CopyConstitutiveMatrix( ConstitutiveLaw::Parameters &rValues,
                                                            Matrix& rConstitutiveMatrix )
{
   if (rValues.GetMaterialProperties()[IS_FORTRAN_UDSM])
   {
      // transfer fortran style matrix to C++ style
      for (unsigned int i = 0; i < VoigtSize; i++) {
         for (unsigned int j = 0; j < VoigtSize; j++) {
            rConstitutiveMatrix(i,j) = mMatrixD[getIndex3D(static_cast<intexStress3DInterface>(j))][getIndex3D(static_cast<intexStress3DInterface>(i))];
         }
      }
   }
   else
   {
      for (unsigned int i = 0; i < VoigtSize; i++) {
         for (unsigned int j = 0; j < VoigtSize; j++) {
            rConstitutiveMatrix(i,j) = mMatrixD[getIndex3D(static_cast<intexStress3DInterface>(i))][getIndex3D(static_cast<intexStress3DInterface>(j))];
         }
      }
   }
}

intexStress3D SmallStrainUDSM3DInterfaceLaw::getIndex3D(intexStress3DInterface index3D)
{
   switch (index3D)
   {
      case INDEX_3D_INTERFACE_ZZ:
        return INDEX_3D_ZZ;
      case INDEX_3D_INTERFACE_YZ:
        return INDEX_3D_YZ;
      case INDEX_3D_INTERFACE_XZ:
        return INDEX_3D_XZ;
      default:
        KRATOS_THROW_ERROR(std::invalid_argument, "invalid index: ", index3D);
   }
}

void SmallStrainUDSM3DInterfaceLaw::UpdateInternalStrainVectorFinalized(ConstitutiveLaw::Parameters &rValues)
{
   const Vector& rStrainVector = rValues.GetStrainVector();
   std::fill(mStrainVectorFinalized.begin(), mStrainVectorFinalized.end(), 0.0);

   mStrainVectorFinalized[INDEX_3D_ZZ] = rStrainVector(INDEX_3D_INTERFACE_ZZ);
   mStrainVectorFinalized[INDEX_3D_YZ] = rStrainVector(INDEX_3D_INTERFACE_YZ);
   mStrainVectorFinalized[INDEX_3D_XZ] = rStrainVector(INDEX_3D_INTERFACE_XZ);

   // KRATOS_INFO("UpdateInternalStrainVectorFinalized:rStrainVector") << rStrainVector << std::endl;

}

/***********************************************************************************/
/***********************************************************************************/

void SmallStrainUDSM3DInterfaceLaw::
   CalculateCauchyGreenStrain( ConstitutiveLaw::Parameters& rValues,
                               Vector& rStrainVector )
{
   KRATOS_ERROR << "CalculateCauchyGreenStrain is not implemented in SmallStrainUDSM3DInterfaceLaw" << std::endl;
}

//----------------------------------------------------------------------------------------
Vector& SmallStrainUDSM3DInterfaceLaw::
   GetValue( const Variable<Vector> &rThisVariable,
             Vector &rValue )
{
   // KRATOS_INFO("0-SmallStrainUDSM3DInterfaceLaw::GetValue()") << std::endl;

   if (rThisVariable == STATE_VARIABLES)
   {
      SmallStrainUDSM3DLaw::GetValue(rThisVariable, rValue );
   }
   else if (rThisVariable == CAUCHY_STRESS_VECTOR)
   {
      if (rValue.size() != VoigtSize)
         rValue.resize(VoigtSize);

      rValue[INDEX_3D_INTERFACE_ZZ] = mStressVectorFinalized[INDEX_3D_ZZ];
      rValue[INDEX_3D_INTERFACE_YZ] = mStressVectorFinalized[INDEX_3D_YZ];
      rValue[INDEX_3D_INTERFACE_XZ] = mStressVectorFinalized[INDEX_3D_XZ];

   }

   // KRATOS_INFO("1-SmallStrainUDSM3DInterfaceLaw::GetValue()") << std::endl;

    return rValue;
}

//----------------------------------------------------------------------------------------
void SmallStrainUDSM3DInterfaceLaw::SetValue( const Variable<Vector>& rThisVariable,
                                                const Vector& rValue,
                                                const ProcessInfo& rCurrentProcessInfo )
{
   // KRATOS_INFO("02-SmallStrainUDSM3DInterfaceLaw::SetValue()") << std::endl;

   if (rThisVariable == STATE_VARIABLES)
   {
      SmallStrainUDSM3DLaw::SetValue(rThisVariable, rValue, rCurrentProcessInfo );
   }
   else if (rThisVariable == CAUCHY_STRESS_VECTOR)
   {
      if (rValue.size() == VoigtSize) 
      {
         this->SetInternalStressVector(rValue);
      }
   }

   // KRATOS_INFO("12-SmallStrainUDSM2DInterfaceLaw::SetValue()") << std::endl;
}

} // Namespace Kratos
