/*
 * vlcNetDevice.cc
 *
 *  Created on: Mar 25, 2016
 *      Author: Adel Aldalbahi
 */

#include "ns3/vlcNetDevice.h"

namespace vlc {

vlc_NetDevice::vlc_NetDevice() {
	m_mobilityModel = ns3::CreateObject<VlcMobilityModel>();
	m_mobilityModel->SetAzimuth(0);
	m_mobilityModel->SetElevation(0);
	m_mobilityModel->SetPosition(ns3::Vector(0.0,0.0,0.0));
}


double vlc_NetDevice::GetAzmuth(){
	return this->m_mobilityModel->GetAzimuth();
}

void vlc_NetDevice::SetAzmuth(double az){
	this->m_mobilityModel->SetAzimuth(az);
}

ns3::Vector vlc_NetDevice::GetPosition(){
	return this->m_mobilityModel->GetPosition();
}

void vlc_NetDevice::SetPosition(ns3::Vector position){
	m_mobilityModel->SetPosition(position);
}

double vlc_NetDevice::GetElevation(){
	return m_mobilityModel->GetElevation();
}

void vlc_NetDevice::SetElevation(double elevation){

	m_mobilityModel->SetElevation(elevation);
}

ns3::Ptr<VlcMobilityModel> vlc_NetDevice::GetMobilityModel(){
	return m_mobilityModel;
}
void vlc_NetDevice::SetMobilityModel(ns3::Ptr<VlcMobilityModel> model){
	m_mobilityModel = model;
}


vlc_NetDevice::~vlc_NetDevice() {

}

} /* namespace vlc */

