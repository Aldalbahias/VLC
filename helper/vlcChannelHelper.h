/*
 * vlcChannelHelper.h
 *
 *  Created on: Apr 10, 2016
 *      Author: adel
 */

#ifndef VLCCHANNELHELPER_H_
#define VLCCHANNELHELPER_H_

#include <map>
#include <iostream>
#include <string>
#include "ns3/core-module.h"
#include "ns3/vlcchannel.h"
#include "ns3/vlcDeviceHelper.h"
#include "ns3/net-device-container.h"
#include "ns3/queue.h"
#include "ns3/vlcNetDevice.h"
#include "ns3/vlcNetDeviceRX.h"
#include "ns3/vlcNetDeviceTX.h"
#include "ns3/object-factory.h"




namespace vlc {

class vlcChannelHelper : public Object {
public:
	vlcChannelHelper();

	void CreateChannel(std::string channelName);

	void SetChannelWavelength(std::string channelName, int lower, int upper);

	void SetPropagationLoss(std::string channelName, std::string propagationLossType);

	void SetPropagationDelay(std::string channelName, double value);

	void AttachTransmitter(std::string chName,std::string TXDevName, ns3::Ptr<vlc_DeviceHelper> devHelper);

	void AttachReceiver(std::string chName,std::string RXDevName, ns3::Ptr<vlc_DeviceHelper> devHelper);

	double GetChannelSNR(std::string chName);

	void SetChannelParameter(std::string chName,std::string paramName, double value);

	ns3::Ptr<vlc_channel> GetChannel(std::string chName);

	ns3::Ptr< vlc_NetDevice > GetDevice(std::string chName,uint32_t idx);

	ns3::NetDeviceContainer Install(std::string chName,Ptr<Node> a, Ptr<Node> b);

	virtual ~vlcChannelHelper();

private:

	std::map< std::string, ns3::Ptr<vlc_channel> > m_channel;

	ObjectFactory m_queueFactory;

};

} /* namespace vlc */

#endif /* VLCCHANNELHELPER_H_ */
