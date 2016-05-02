/*
 * vlcDeviceHelper.h
 *
 *  Created on: Apr 9, 2016
 *      Author: adel
 */

#ifndef VLCDEVICEHELPER_H_
#define VLCDEVICEHELPER_H_

#include <map>
#include <iostream>
#include <string>
#include <vector>
#include "ns3/vlcNetDeviceRX.h"
#include "ns3/vlcNetDeviceTX.h"
#include "ns3/core-module.h"
#include "ns3/VLC-error-model.h"


namespace vlc {


class vlc_DeviceHelper : public Object{
public:
	vlc_DeviceHelper();

	~vlc_DeviceHelper();

	void CreateTransmitter(std::string TXName);

	void CreateReceiver(std::string RXName);

	ns3::Ptr<vlc_NetDeviceTX> GetTransmitter(std::string devName);

	ns3::Ptr<vlc_NetDeviceRX> GetReceiver(std::string devName);


	std::vector<double> GenerateSignal(int size,double dutyRatio,double bias, double VMax,double VMin);

	void SetTXSignal(std::string devName,int size,double dutyRatio,double bias, double VMax,double VMin);

	void SetTrasmitterParameter(std::string devName, std::string paramName, double value );

	void SetTrasmitterBoost(std::string devName);

	void SetTrasmitterPosition(std::string devName, double x, double y, double z);

	void SetReceiverPosition(std::string devName, double x, double y, double z);

	void SetReceiverParameter(std::string devName, std::string paramName, double value );

	double GetReceiverParameter(std::string devName,std::string paramName);

private:
	std::map<std::string, ns3::Ptr<vlc_NetDeviceTX> > m_TXDevices;
	std::map<std::string, ns3::Ptr<vlc_NetDeviceRX> > m_RXDevices;

};

} /* namespace vlc */

#endif /* VLCDEVICEHELPER_H_ */
