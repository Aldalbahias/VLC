/*
 * vlcChannelHelper.cc
 *
 *  Created on: Apr 10, 2016
 *      Author: Adel
 */

#include "vlcChannelHelper.h"

namespace vlc {

vlcChannelHelper::vlcChannelHelper() {
	//NS_LOG_FUNCTION(this);
}

void vlcChannelHelper::CreateChannel(std::string channelName){
	//NS_LOG_FUNCTION(this);
	this->m_channel[channelName] = CreateObject<vlc_channel>();
}

void vlcChannelHelper::SetChannelParameter(std::string chName,std::string paramName, double value){
	if(paramName=="TEMP"){
		this->m_channel[chName]->SetTemperature(value);
	}
	else if(paramName=="ElectricNoiseBandWidth"){
		this->m_channel[chName]->SetElectricNoiseBandWidth(value);
	}
}

void vlcChannelHelper::SetPropagationLoss(std::string channelName, std::string propagationLossType){
	//NS_LOG_FUNCTION(this);
	if(propagationLossType=="VLCPropagationLoss"){
		this->m_channel[channelName]->SetPropagationLossModel(CreateObject<VLCPropagationLossModel>());
	}
}

void vlcChannelHelper::SetPropagationDelay(std::string channelName, double value){
	//NS_LOG_FUNCTION(this);
	this->m_channel[channelName]->SetPropagationDelay(value);

}

double vlcChannelHelper::GetChannelSNR(std::string chName){
	ns3::Ptr<vlc_NetDeviceRX> rx = DynamicCast<vlc_NetDeviceRX>(m_channel[chName]->GetDevice(1));
	this->m_channel[chName]->DoCalcPropagationLossForSignal(0);
	this->m_channel[chName]->CalculateNoiseVar();
	double snr =  this->m_channel[chName]->GetSNR();
	rx->SetSNRForErrorModel(snr);
	return snr;
}

void vlcChannelHelper::SetChannelWavelength(std::string channelName, int lower, int upper){
	this->m_channel[channelName]->SetWavelength(lower,upper);
}

void vlcChannelHelper::AttachTransmitter(std::string chName,std::string TXDevName, ns3::Ptr<vlc_DeviceHelper> devHelper){
	//NS_LOG_FUNCTION(this);
	this->m_channel[chName]->Attach(devHelper->GetTransmitter(TXDevName));
	this->m_channel[chName]->SetPorpagationLossParametersFromTX();
}

void vlcChannelHelper::AttachReceiver(std::string chName,std::string RXDevName, ns3::Ptr<vlc_DeviceHelper> devHelper){
	//NS_LOG_FUNCTION(this);
	this->m_channel[chName]->Attach(devHelper->GetReceiver(RXDevName));
	this->m_channel[chName]->SetPorpagationLossParametersFromRX();
}

ns3::Ptr<vlc_channel> vlcChannelHelper::GetChannel(std::string chName){
	//NS_LOG_FUNCTION(this);
	return m_channel[chName];
}

ns3::Ptr< vlc_NetDevice > vlcChannelHelper::GetDevice(std::string chName,uint32_t idx){
	//NS_LOG_FUNCTION(this);
	ns3::Ptr<vlc_NetDevice> ans = DynamicCast<vlc_NetDevice>(m_channel[chName]->GetDevice(idx));

	return ans;
}

NetDeviceContainer vlcChannelHelper::Install(std::string chName,Ptr<Node> a, Ptr<Node> b){

	//NS_LOG_FUNCTION(this);

	NetDeviceContainer container;
	Ptr<vlc_channel> ch = this->m_channel[chName];

	Ptr<vlc_NetDevice> devTX =  DynamicCast<vlc_NetDevice>(ch->GetDevice(0) );
	Ptr<vlc_NetDevice> devRX =  DynamicCast<vlc_NetDevice>(ch->GetDevice(1) );


	a->AddDevice(devTX);
	//Ptr < Queue > queueA = m_queueFactory.Create<Queue>();
	//Ptr < DropTailQueue > queueA = CreateObject<DropTailQueue>();
	//devTX->SetQueue(queueA);

	b->AddDevice(devRX);
	//Ptr < Queue > queueB = m_queueFactory.Create<Queue>();
	//devRX->SetQueue(queueB);

	/*bool useNormalChannel = true;
	ch = 0;

	if (MpiInterface::IsEnabled()) {
		uint32_t n1SystemId = a->GetSystemId();
		uint32_t n2SystemId = b->GetSystemId();
		uint32_t currSystemId = MpiInterface::GetSystemId();

		if (n1SystemId != currSystemId || n2SystemId != currSystemId) {
			useNormalChannel = false;
		}
	}*/


	container.Add(devTX);
	container.Add(devRX);

	return container;

}

vlcChannelHelper::~vlcChannelHelper() {

}

} /* namespace vlc */
