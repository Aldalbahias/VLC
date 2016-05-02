/*
 * vlcNetDeviceRX.cpp
 *
 *  Created on: Mar 25, 2016
 *      Author: Adel Aldalbahi
 */

#include "ns3/vlcNetDeviceRX.h"

namespace vlc {

vlc_NetDeviceRX::vlc_NetDeviceRX() {

	//NS_LOG_FUNCTION(this);

	m_filterGain = 0;
	m_photodetectorArea = 0;
	m_FOVangle = 0;
	m_refIndex = 0;
	m_angleOfIncidence = 0;
	m_concentrationGain = 0;
	m_RXGain = 0;
	m_bias = 0;
	this->m_error = ns3::CreateObject<ns3::VLC_ErrorModel>();


}


//use this function after setting up FOV and refractive index
void vlc_NetDeviceRX::SetConcentrationGain(){
	//NS_LOG_FUNCTION(this);
	this->m_concentrationGain = std::pow(this->m_refIndex,2)/std::pow((float)std::sin((float)m_FOVangle),2);
}

void vlc_NetDeviceRX::AddRXOpticalPowerSignal(double power){
	//NS_LOG_FUNCTION(this<<power);
	this->m_RXOpticalPower.push_back(power);
}
std::vector<double>& vlc_NetDeviceRX::GetRXOpticalPowerSignal(){
	//NS_LOG_FUNCTION(this);
	return this->m_RXOpticalPower;
}
double vlc_NetDeviceRX::GetOpticalPowerSignalAtInstant(int time){
	//NS_LOG_FUNCTION(this<<time);
	return this->m_RXOpticalPower.at(time);
}
void vlc_NetDeviceRX::SetRXOpticalPowerSignal(std::vector<double> &powerSignal){
	//NS_LOG_FUNCTION(this<<powerSignal);
	this->m_RXOpticalPower = powerSignal;
}



void vlc_NetDeviceRX::SetCapacity(int size){
	//NS_LOG_FUNCTION(this<<size);
	this->m_signal.reserve(size);
	this->m_RXOpticalPower.reserve(size);
}

double vlc_NetDeviceRX::GetFilterGain(){
	//NS_LOG_FUNCTION(this);
	return this->m_filterGain;
}
void vlc_NetDeviceRX::SetFilterGain(double fgain){
	//NS_LOG_FUNCTION(this<<fgain);
	this->m_filterGain = fgain;
}

double vlc_NetDeviceRX::GetPhotoDetectorArea(){
	//NS_LOG_FUNCTION(this);
	return this->m_photodetectorArea;
}

void vlc_NetDeviceRX::SetPhotoDectectorArea(double pArea){
	//NS_LOG_FUNCTION(this<<pArea);
	this->m_photodetectorArea = pArea;
}

double vlc_NetDeviceRX::GetFOVAngle(){
	//NS_LOG_FUNCTION(this);
	return this->m_FOVangle;
}

void vlc_NetDeviceRX::SetFOVAngle(double angle){
	//NS_LOG_FUNCTION(this<<angle);
	this->m_FOVangle = angle*M_PI/180;
}

double vlc_NetDeviceRX::GetRefractiveIndex(){
	//NS_LOG_FUNCTION(this);
	return this->m_refIndex;
}
void vlc_NetDeviceRX::SetRefractiveIndex(double angle){
	//NS_LOG_FUNCTION(this << angle);
	this->m_refIndex = angle;
}


double vlc_NetDeviceRX::GetConcentrationGain(){
	//NS_LOG_FUNCTION(this);
	return this->m_concentrationGain;
}


double vlc_NetDeviceRX::GetRXGain(){
	//NS_LOG_FUNCTION(this);
	return this->m_RXGain;
}
void vlc_NetDeviceRX::SetRXGain(){
	//NS_LOG_FUNCTION(this);
	this->m_RXGain = std::cos(this->m_angleOfIncidence);
}


void vlc_NetDeviceRX::SetIncidenceAngle(double angle){
	//NS_LOG_FUNCTION(this << angle);
	this->m_angleOfIncidence = angle*M_PI/180;
}

ns3::VLC_ErrorModel::ModScheme vlc_NetDeviceRX::GeModulationtScheme (void) const{	 // returns the modulation scheme used
	//NS_LOG_FUNCTION(this);
	return this->m_error->GetScheme();
}

void vlc_NetDeviceRX::SetScheme (std::string scheme){ // sets the value of the modulation scheme used
	//NS_LOG_FUNCTION(this<<scheme);
	this->m_error->SetScheme(scheme);

}

void vlc_NetDeviceRX::SetRandomVariableForErrorModel(ns3::Ptr<ns3::RandomVariableStream> ranVar){	// assigns a random variable stream to be used by this model
	//NS_LOG_FUNCTION(this<<ranVar);
	this->m_error->SetRandomVariable(ranVar);
}

int64_t vlc_NetDeviceRX::AssignStreamsForErrorModel (int64_t stream){	// assigns a fixed stream number to the random variables used by this model
	//NS_LOG_FUNCTION(this);
	return this->m_error->AssignStreams(stream);
}

double vlc_NetDeviceRX::GetSNRFromErrorModel (void) const{		// returns the signal-to-noise ratio (SNR)
	//NS_LOG_FUNCTION(this);
	return this->m_error->GetSNR();
}

void vlc_NetDeviceRX::SetSNRForErrorModel (double snr){		// sets the SNR value
	//NS_LOG_FUNCTION(this<<snr);
	this->m_error->SetSNR(snr);
}

double vlc_NetDeviceRX::CalculateErrorRateForErrorModel (){		// calculates the error rate value according to modulation scheme
	//NS_LOG_FUNCTION(this);
	return this->m_error->CalculateErrorRate();
}

bool vlc_NetDeviceRX::IsCorrupt (ns3::Ptr<ns3::Packet> pkt){	// determines if the packet is corrupted according to the error model
	//NS_LOG_FUNCTION(this<<pkt);
	return this->m_error->IsCorrupt(pkt);
}

// methods for PAM
int vlc_NetDeviceRX::GetModulationOrder (void) const{	// returns the modulation order (M)
	//NS_LOG_FUNCTION(this);
	return this->m_error->GetModulationOrder();
}

void vlc_NetDeviceRX::SetModulationOrder (int m_order){	// sets the modulation order value
	//NS_LOG_FUNCTION(this<<m_order);
	return this->m_error->SetModulationOrder(m_order);
}

// methods for VPPM
double vlc_NetDeviceRX::GetAlpha(void) const{	// returns alpha value
	//NS_LOG_FUNCTION(this);
	return this->m_error->GetAlpha();
}
void vlc_NetDeviceRX::SetAlpha (double a){		// sets alpha value
	//NS_LOG_FUNCTION(this);
	this->m_error->SetAlpha(a);
}

double vlc_NetDeviceRX::GetBeta(void) const{		// returns beta value
	//NS_LOG_FUNCTION(this);
	return this->m_error->GetBeta();
}
void vlc_NetDeviceRX::SetBeta (double b){		// sets beta value
	//NS_LOG_FUNCTION(this<<b);
	return this->m_error->SetBeta(b);
}


double vlc_NetDeviceRX::GetIncidenceAngle(){
	return this->m_angleOfIncidence;
}


vlc_NetDeviceRX::~vlc_NetDeviceRX() {
	// TODO Auto-generated destructor stub
}

} /* namespace vlc */
