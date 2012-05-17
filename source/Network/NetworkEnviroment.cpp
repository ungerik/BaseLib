/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#include "BaseLib/Network/NetworkEnviroment.h"



namespace BaseLib {
namespace Network {



void NetworkEnviroment::enumNetworkEnviromentProtocolPorts(const Enumerator<uint16>& enumerator)
{
}



void NetworkEnviroment::addNetworkEnviromentProtocolPort(uint16 port)
{
}



void NetworkEnviroment::removeNetworkEnviromentProtocolPort(uint16 port)
{
}



int NetworkEnviroment::getDownloadBandwidth()
{
	return -1;
}



int NetworkEnviroment::getUploadBandwidth()
{
	return -1;
}



int NetworkEnviroment::getDownloadBandwidthLimit()
{
	return -1;
}



void NetworkEnviroment::setDownloadBandwidthLimit(int newDownloadBandwidth)
{
}



int NetworkEnviroment::getUploadBandwidthLimit()
{
	return -1;
}



void NetworkEnviroment::setUploadBandwidthLimit(int newUploadBandwidth)
{
}



void NetworkEnviroment::enumPeersInLan(const Enumerator<String>& enumerator)
{
}



void NetworkEnviroment::addPeer(const String& peerName)
{
}



void NetworkEnviroment::removePeer(const String& peerName)
{
}



int NetworkEnviroment::getPeerDownloadBandwidthLimit(const String& peerName)
{
	return -1;
}



void NetworkEnviroment::setPeerDownloadBandwidthLimit(const String& peerName, int newDownloadBandwidth)
{
}



int NetworkEnviroment::getPeerUploadBandwidthLimit(const String& peerName)
{
	return -1;
}



void NetworkEnviroment::setPeerUploadBandwidthLimit(const String& peerName, int newUploadBandwidth)
{
}



void NetworkEnviroment::addOwnProtocol(const String& protocol, uint16 port)
{
}



void NetworkEnviroment::removeOwnProtcol(const String& protocol)
{
}



void NetworkEnviroment::enumOwnProtocols(const Enumerator<String>& enumerator)
{
}



uint16 NetworkEnviroment::getOwnProtocolPort(const String& protocol)
{
	return -1;
}



void NetworkEnviroment::enumPeerProtocols(const String& peerName, const Enumerator<String>& enumerator)
{
}



uint16 NetworkEnviroment::getPeerProtocolPort(const String& peerName, const String& protocol)
{
	return -1;
}



int NetworkEnviroment::getGatewayCountOfPeer(const String& peerName)
{
	return -1;
}



int NetworkEnviroment::getDownloadBandwidthOfGateway(const String& peerName, int gatewayIndex)
{
	return -1;
}



int NetworkEnviroment::getUploadBandwidthOfGateway(const String& peerName, int gatewayIndex)
{
	return -1;
}



void NetworkEnviroment::enumPeersBehindGateway(const String& peerName, const Enumerator<String>& enumerator)
{
}



int NetworkEnviroment::getOwnGatewayCount()
{
	return -1;
}



void NetworkEnviroment::addGateway(int downloadBandwidth, int uploadBandwidth)
{
}



void NetworkEnviroment::removeGateway(int gatewayIndex)
{
}



int NetworkEnviroment::getOwnGatewayDownloadBandwidth(int gatewayIndex)
{
	return -1;
}



void NetworkEnviroment::setOwnGatewayDownloadBandwidth(int gatewayIndex, int newDownloadBandwidth)
{
}



int NetworkEnviroment::getOwnGatewayUploadBandwidth(int gatewayIndex)
{
	return -1;
}



void NetworkEnviroment::setOwnGatewayUploadBandwidth(int gatewayIndex, int newUploadBandwidth)
{
}



int NetworkEnviroment::getPeerCountBehindOwnGateway(int gatewayIndex)
{
	return -1;
}



void NetworkEnviroment::addPeerBehindOwnGateway(const String& peerName, int gatewayIndex)
{
}



void NetworkEnviroment::removePeerBehindOwnGateway(const String& peerName, int gatewayIndex)
{
}



} // namespace Network
} // namespace BaseLib
