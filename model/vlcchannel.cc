/*
 * vlcchannel.cpp
 *
 *  Created on: Mar 23, 2016
 *      Author: Adel Aldalbahi
 */

#include "ns3/vlcchannel.h"
#include "ns3/log.h"

namespace vlc {

vlc_channel::vlc_channel():m_distanceBWTXandRX(0) {
	//NS_LOG_FUNCTION(this);
	this->m_loss = CreateObject< vlc::VLCPropagationLossModel > ();
	m_AvgPower = 0;
	this->m_SNR = CreateObject<VLC_SNR> ();
}

void vlc_channel::SetPropagationLossModel(ns3::Ptr<ns3::PropagationLossModel> loss){
	//NS_LOG_FUNCTION(this<<loss);
	this->m_loss = loss;
}

ns3::Ptr<ns3::PropagationLossModel> vlc_channel::GetPropagationLossModel(){
	//NS_LOG_FUNCTION(this);
	return this->m_loss;
}

void vlc_channel::SetPropagationDelayModel(ns3::Ptr<ns3::PropagationDelayModel> delay){
	//NS_LOG_FUNCTION(this<<delay);
	this->m_delay = delay;
}
ns3::Ptr<ns3::PropagationDelayModel> vlc_channel::GetPropagationDelayModel(){
	//NS_LOG_FUNCTION(this);
	return this->m_delay;
}

double vlc_channel::GetDistance(){
	//NS_LOG_FUNCTION(this);
	return this->m_distanceBWTXandRX;
}

void vlc_channel::SetDistance(){
	//NS_LOG_FUNCTION(this);
	ns3::Ptr<vlc_NetDevice> first =  ns3::DynamicCast< vlc_NetDevice >( this->GetDevice(0));
	ns3::Ptr<vlc_NetDevice> second =  ns3::DynamicCast< vlc_NetDevice >( this->GetDevice(1));

	ns3::Ptr<VLCPropagationLossModel>  l = ns3::DynamicCast< VLCPropagationLossModel >(this->m_loss);
	this->m_distanceBWTXandRX = l->GetDistance(first->GetMobilityModel(),second->GetMobilityModel());
}

void vlc_channel::DoCalcPropagationLoss(){
	//NS_LOG_FUNCTION(this);
	ns3::Ptr<vlc_NetDeviceTX> first =  ns3::DynamicCast<vlc_NetDeviceTX> ( this->GetDevice(0) );
	ns3::Ptr<vlc_NetDeviceRX> second =  ns3::DynamicCast<vlc_NetDeviceRX>( this->GetDevice(1) );
	double loss = 0;

	for(unsigned int i=0; i<first->GetTXOpticalPowerSignal().size();i++){
		loss = m_loss->CalcRxPower(first->GetTXOpticalPowerSignal().at(i) , first->GetMobilityModel(), second->GetMobilityModel());
		second->GetRXOpticalPowerSignal().at(i) = loss ;
	}

}

void vlc_channel::SetPropagationDelay(double delay){
	//NS_LOG_FUNCTION(this<<delay);
	//this->m_delay->set
}

double vlc_channel::DoCalcPropagationLossForSignal(int timeInstant){
	//NS_LOG_FUNCTION(this);
	ns3::Ptr<vlc_NetDeviceTX> first =  ns3::DynamicCast<vlc_NetDeviceTX> ( this->GetDevice(0));
	ns3::Ptr<vlc_NetDeviceRX> second =  ns3::DynamicCast<vlc_NetDeviceRX>( this->GetDevice(1));
	double loss = m_loss->CalcRxPower(first->GetTXOpticalPowerSignal().at(timeInstant), first->GetMobilityModel(), second->GetMobilityModel() );
	m_SNR->SetReceivedPower(loss);

	return loss;
}

void vlc_channel::SetPorpagationLossParametersFromTX(){
	//NS_LOG_FUNCTION(this);
	ns3::Ptr<vlc_NetDeviceTX> tx =  ns3::DynamicCast< vlc_NetDeviceTX >( this->GetDevice(0));
	ns3::Ptr<vlc::VLCPropagationLossModel> loss =  ns3::DynamicCast< vlc::VLCPropagationLossModel >( this->m_loss);
	loss->SetTxPowerMAX(tx->GetTXPowerMax());
	loss->SetTXGain(tx->GetTXGain());
}

void vlc_channel::SetPorpagationLossParametersFromRX(){
	//NS_LOG_FUNCTION(this);
	ns3::Ptr<vlc_NetDeviceRX> rx =  ns3::DynamicCast< vlc_NetDeviceRX >( this->GetDevice(1));
	ns3::Ptr<vlc::VLCPropagationLossModel> loss =  ns3::DynamicCast< vlc::VLCPropagationLossModel >( this->m_loss);
	loss->SetFilterGain(rx->GetFilterGain());
	loss->SetConcentratorGain(rx->GetConcentrationGain());
	loss->SetRXGain(rx->GetRXGain());

}

void vlc_channel::SetWavelength (int lower, int upper){	// sets upper and lower bound wavelength [nm]
	//NS_LOG_FUNCTION(this);
	this->m_SNR->SetWavelength(lower,upper);
}
void vlc_channel::SetTemperature (double t){		// sets the blackbody temperature of LED
	//NS_LOG_FUNCTION(this<<t);
	this->m_SNR->SetTemperature(t);
}

double vlc_channel::GetTemperature(){
	return this->m_SNR->GetTemperature();
}
void vlc_channel::SetReceivedPower (double p){	// sets the average received optical signal power
	//NS_LOG_FUNCTION(this<<p);
	this->m_SNR->SetReceivedPower(p);
}
void vlc_channel::CalculateNoiseVar (){	//calculates the noise variance
	//NS_LOG_FUNCTION(this<<A<<B<<Tk );
	ns3::Ptr<vlc_NetDeviceRX> rx = DynamicCast<vlc_NetDeviceRX>(this->GetDevice(1));
	this->m_SNR->CalculateNoiseVar(rx->GetPhotoDetectorArea() );

}
void vlc_channel::CalculateSNR (){		// caluclates the SNR value
	//NS_LOG_FUNCTION(this);
	this->m_SNR->CalculateSNR();
}

double vlc_channel::GetSNR () const{		// returns the signal-to-noise ratio (SNR)
	//NS_LOG_FUNCTION(this);
	ns3::Ptr<vlc_NetDeviceRX> rx = DynamicCast<vlc_NetDeviceRX>(this->GetDevice(1));
	this->m_SNR->CalculateNoiseVar(rx->GetPhotoDetectorArea());
	m_SNR->CalculateSNR();
	return this->m_SNR->GetSNR();
}


void vlc_channel::SetAveragePower(double power){
	//NS_LOG_FUNCTION(this<<power);
	m_AvgPower = power;
}

double vlc_channel::GetAveragePower(){
	//NS_LOG_FUNCTION(this);
	return m_AvgPower;
}

void vlc_channel::SetElectricNoiseBandWidth (double b){	// sets the noise bandwidth
	this->m_SNR->SetElectricNoiseBandWidth(b);
}

double vlc_channel::GetNoiseBandwidth(){			//return the noise bandwidth
	return m_SNR->GetNoiseBandwidth();
}

vlc_channel::~vlc_channel() {

}


} /* namespace vlc */
