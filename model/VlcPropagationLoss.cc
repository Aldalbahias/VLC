/*
 * VlcPropagationLoss.cc
 *
 *  Created on: Mar 27, 2016
 *      Author: Adel Aldalbahi
 */

#include "ns3/VlcPropagationLoss.h"

namespace vlc {


VLCPropagationLossModel::VLCPropagationLossModel() {
	m_TxPowerMAX = 0;
	m_TxPower = 0;
	m_FilterGain = 0;
	m_ConcentratorGain = 0;
	m_RxPower = 0;

	m_RXGain = 0 ;
	m_TXGain = 0;

}

void VLCPropagationLossModel::SetTxPower(double watt){
	this->m_TxPower = watt;
}
void VLCPropagationLossModel::SetTxPowerMAX(double MAX){
	this->m_TxPowerMAX = MAX;
}

double VLCPropagationLossModel::GetTxPower(){
	return this->m_TxPower;
}

double VLCPropagationLossModel::GetTxPowerMAX(){
	return this->m_TxPowerMAX;
}


void VLCPropagationLossModel::SetFilterGain(double gain){
	this->m_FilterGain = gain;
}

double VLCPropagationLossModel::GetFilterGain(){
	return this->m_FilterGain;
}

void VLCPropagationLossModel::SetConcentratorGain(double cGain){
	this->m_ConcentratorGain = cGain;
}

double VLCPropagationLossModel::GetConcentratorGain(){
	return this->m_ConcentratorGain;
}

double VLCPropagationLossModel::DoCalcRxPower(double txPowerDbm, ns3::Ptr<ns3::MobilityModel> aTX,ns3::Ptr<ns3::MobilityModel> bRX) const{
	double distance = this->GetDistance(aTX,bRX);
	double pRX = txPowerDbm*this->m_RXGain*this->m_TXGain*this->m_FilterGain*this->m_ConcentratorGain ;
	pRX /= std::pow(distance,2);

	return pRX;
}

double VLCPropagationLossModel::GetRxPower(){
	return this->m_RxPower;
}

void VLCPropagationLossModel::SetRXPower(double wattTX, ns3::Ptr<ns3::MobilityModel> aTX,
			ns3::Ptr<ns3::MobilityModel> bRX){
	this->m_RxPower = this->DoCalcRxPower(wattTX,aTX,bRX);
}

int64_t VLCPropagationLossModel::DoAssignStreams(int64_t stream){
	return stream;
}

double VLCPropagationLossModel::GetDistance(ns3::Ptr<ns3::MobilityModel> aTX, ns3::Ptr<ns3::MobilityModel> bRX) const{
	double dist = 0;
	Vector tx = aTX->GetPosition();
	Vector rx = bRX->GetPosition();
	dist = std::pow((tx.x-rx.x),2) + std::pow((tx.y-rx.y),2) + std::pow((tx.z-rx.z),2) ;
	dist = std::sqrt(dist);
	return dist;
}

void VLCPropagationLossModel::SetTXGain(double txgain){
	this->m_TXGain = txgain;
}

double VLCPropagationLossModel::GetTXGain(){
	return this->m_TXGain;
}

void VLCPropagationLossModel::SetRXGain(double rxgain){
	this->m_RXGain = rxgain;
}

double VLCPropagationLossModel::GetRXGain(){
	return this->m_RXGain;
}

VLCPropagationLossModel::~VLCPropagationLossModel() {

}

} /* namespace vlc */

