//
// Copyright (C) 2013 OpenSim Ltd.
// Copyright (C) 2021 Emre Atik
// Copyright (C) 2022 Ipek Gokce
//
// SPDX-License-Identifier: LGPL-3.0-or-later
//

/* In standard p.56, Switch Specification->Frame Filtering:
 * The frame path: whether the destination requested by the content
 *  of the Destination Address field (which in case of the AFDX is
 *  the Virtual Link Identifier) of the arriving frame is permitted or not
 *
 *  -> TODO If VL-ID is not found in the VL-table, it should be deleted.
 * */
#include "VLRouter.h"
#include <fstream>

#define APPLY_PACKET_DROP_TEST  0

namespace afdx {

Define_Module(VLRouter);

void VLRouter::initialize()
{
    this->configTableName = par("configTableName").str();
    this->configTableName = this->configTableName.substr(1, this->configTableName.length() - 2);
    this->getVirtualLinkToPortMappings(this->vlToOutPortMappings, configTableName.c_str());
}

void VLRouter::handleMessage(cMessage *msg)
{
    AFDXMessage *afdx_msg = check_and_cast<AFDXMessage*>(msg);
    this->routePacket(this->vlToOutPortMappings, afdx_msg);
    delete afdx_msg;
}

void VLRouter::getVirtualLinkToPortMappings(VirtualLinkIdToPortMap_t &VLToPortMapping, const char *fileName)
{
    std::ifstream fileStream(fileName);

    if (!(fileStream.good())) {
        throw std::runtime_error(std::string("VL Table Not Found!"));
    }

    std::size_t indexBegin;
    std::size_t indexEnd;

    int key, value;

    for (std::string line; std::getline(fileStream, line);) {
        indexBegin = 0;
        indexEnd = 0;

        if (line.empty() || line.at(0) == '*') {
            continue;
        }

        if ((indexEnd = line.find(':')) == line.npos) {
            throw std::runtime_error(std::string("Invalid VL Table!"));
        }

        key = std::stoi(line.substr(indexBegin, indexEnd), 0, 16);

        if ((indexEnd = line.find('{')) == line.npos) {
            throw std::runtime_error(std::string("Invalid VL Table!"));
        }

        indexBegin = indexEnd + 1;

        while (((indexEnd = line.find(',', indexBegin)) != line.npos)) {
            value = std::stoi(line.substr(indexBegin, indexEnd));
            indexBegin = indexEnd + 1;

            VLToPortMapping.insert(std::pair<int, int>(key, value));
        }

        if ((indexEnd = line.find('}', indexBegin)) != line.npos) {
            value = std::stoi(line.substr(indexBegin, indexEnd));

            VLToPortMapping.insert(std::pair<int, int>(key, value));
        }
        else {
            throw std::runtime_error(std::string("Invalid VL Table!"));
        }
    }

    fileStream.close();
}

void VLRouter::routePacket(VirtualLinkIdToPortMap_t &vlToPortMapping, AFDXMessage *afdxMessage)
{
    int vlId = afdxMessage->getVirtualLinkId();
    auto keyValuePairs = vlToPortMapping.equal_range(vlId);

    if (keyValuePairs.first != keyValuePairs.second) {
        for (auto itr = keyValuePairs.first; itr != keyValuePairs.second; ++itr) {
            EV_INFO << "VL Routing... [ ID: 0x" << std::hex << itr->first << " - PORT:" << std::dec << itr->second
                    << " ]" << std::endl;
            send((cMessage*) afdxMessage->dup(), "out", itr->second);
        }
    }
    else {
        throw std::runtime_error(std::string("Key Not Found in VL Table!"));
    }
}

}
;
// namespace afdx

