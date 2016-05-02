/*
 * vlcNetDevice.h
 *
 *  Created on: Mar 25, 2016
 *      Author: Adel Aldalbahi
 */

#ifndef VLCNETDEVICE_H_
#define VLCNETDEVICE_H_

#include "ns3/point-to-point-net-device.h"
#include "ns3/point-to-point-channel.h"
#include "ns3/vlcMobilityModel.h"
#include "ns3/mobility-model.h"
#include "ns3/pointer.h"
#include "ns3/ptr.h"
#include "ns3/core-module.h"
#include "ns3/object.h"

namespace vlc {

class vlc_NetDevice: public ns3::PointToPointNetDevice {

public:
	vlc_NetDevice();

	virtual ~vlc_NetDevice();

	//returns the azmuth, i.e. facing of the device
	double GetAzmuth();
	//sets the azmuth,i.e. facing of the device
	void SetAzmuth(double az);

	//returns the x,y,z co-ordinates of the device
	ns3::Vector GetPosition();

	//sets the position of the device to a particular x,y,z value
	void SetPosition(ns3::Vector position);

	//returns the elevation of the device
	double GetElevation();

	//sets the elevation of the device
	void SetElevation(double elevation);

	//returns a pointer to the mobility model of the device
	ns3::Ptr<VlcMobilityModel> GetMobilityModel();

	//sets the mobility model of the device
	void SetMobilityModel(ns3::Ptr<VlcMobilityModel> model);



private:
	ns3::Ptr<VlcMobilityModel> m_mobilityModel;

};

} /* namespace vlc */

#endif /* VLCNETDEVICE_H_ */
