/*
 * vlcMobilityModel.h
 *
 *  Created on: Mar 26, 2016
 *      Author: Adel Aldalbahi
 */

#ifndef VLCMOBILITYMODEL_H_
#define VLCMOBILITYMODEL_H_

#include "ns3/mobility-model.h"
#include "ns3/vector.h"
#include "ns3/enum.h"
#include "ns3/double.h"
#include "ns3/string.h"
#include "ns3/pointer.h"
#include "ns3/simulator.h"
#include "ns3/log.h"
#include <cmath>

namespace vlc {

class VlcMobilityModel : public ns3::MobilityModel {
public:
  /**
   * Register this type with the TypeId system.
   * \return the object TypeId
   */
  static ns3::TypeId GetTypeId (void);
  /**
   * Create position located at coordinates (0,0,0) with
   * speed (0,0,0).
   */
  VlcMobilityModel ();
  virtual ~VlcMobilityModel ();
  /**
   * Set the model's velocity and acceleration
   * \param velocity the velocity (m/s)
   * \param acceleration the acceleration (m/s^2)
   */
  void SetVelocityAndAcceleration (const ns3::Vector &velocity, const ns3::Vector &acceleration);

  void SetAzimuth(double angle);
  double GetAzimuth(void);

  void SetElevation (double angle);
  double GetElevation (void);

private:
  virtual ns3::Vector DoGetPosition (void) const;
  virtual void DoSetPosition (const ns3::Vector &position);
  virtual ns3::Vector DoGetVelocity (void) const;

  ns3::Time m_baseTime;  //!< the base time
  ns3::Vector m_basePosition; //!< the base position
  ns3::Vector m_baseVelocity; //!< the base velocity
  ns3::Vector m_acceleration;  //!< the acceleration
  double m_azimuth;    //Rotation (left/;; and Right)
  double m_elevation; //Rotation Angle};
};

} /* namespace vlc */


#endif /* VLC_MOBILITY_MODEL_H */
